#include <iostream>
#include <memory>

using namespace std;

class IShippingStrategy {
public:
    virtual double CalculateShippingCost(double weight, double distance) const = 0;
    virtual ~IShippingStrategy() = default;
};

class StandardShippingStrategy : public IShippingStrategy {
public:
    double CalculateShippingCost(double weight, double distance) const override {
        return weight * 0.5 + distance * 0.1;
    }
};

class ExpressShippingStrategy : public IShippingStrategy {
public:
    double CalculateShippingCost(double weight, double distance) const override {
        return (weight * 0.75 + distance * 0.2) + 10; // Дополнительная плата за скорость
    }
};

class InternationalShippingStrategy : public IShippingStrategy {
public:
    double CalculateShippingCost(double weight, double distance) const override {
        return weight * 1.0 + distance * 0.5 + 15; // Дополнительные сборы за международную доставку
    }
};

class DeliveryContext {
private:
    unique_ptr<IShippingStrategy> strategy;

public:
    void SetShippingStrategy(unique_ptr<IShippingStrategy> newStrategy) {
        strategy = move(newStrategy);
    }

    double CalculateCost(double weight, double distance) const {
        if (!strategy) {
            throw logic_error("Стратегия доставки не установлена.");
        }
        return strategy->CalculateShippingCost(weight, distance);
    }
};

int main() {
    DeliveryContext deliveryContext;

    cout << "Выберите тип доставки: 1 - Стандартная, 2 - Экспресс, 3 - Международная: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            deliveryContext.SetShippingStrategy(make_unique<StandardShippingStrategy>());
            break;
        case 2:
            deliveryContext.SetShippingStrategy(make_unique<ExpressShippingStrategy>());
            break;
        case 3:
            deliveryContext.SetShippingStrategy(make_unique<InternationalShippingStrategy>());
            break;
        default:
            cout << "Неверный выбор." << endl;
            return 1;
    }

    cout << "Введите вес посылки (кг): ";
    double weight;
    cin >> weight;

    cout << "Введите расстояние доставки (км): ";
    double distance;
    cin >> distance;

    try {
        double cost = deliveryContext.CalculateCost(weight, distance);
        cout << "Стоимость доставки: " << cost << " единиц" << endl;
    } catch (const logic_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
