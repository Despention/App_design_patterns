#include <iostream>
#include <memory>

using namespace std;

class ICostCalculationStrategy {
public:
    virtual double CalculateCost(double distance, int passengers, string serviceClass) const = 0;
    virtual ~ICostCalculationStrategy() = default;
};

class AirplaneStrategy : public ICostCalculationStrategy {
public:
    double CalculateCost(double distance, int passengers, string serviceClass) const override {
        double baseCost = distance * 0.5;  // базовая стоимость
        double classMultiplier = (serviceClass == "business") ? 2.0 : 1.0;
        return baseCost * passengers * classMultiplier;
    }
};

class TrainStrategy : public ICostCalculationStrategy {
public:
    double CalculateCost(double distance, int passengers, string serviceClass) const override {
        double baseCost = distance * 0.2;
        double classMultiplier = (serviceClass == "business") ? 1.5 : 1.0;
        return baseCost * passengers * classMultiplier;
    }
};

class BusStrategy : public ICostCalculationStrategy {
public:
    double CalculateCost(double distance, int passengers, string serviceClass) const override {
        double baseCost = distance * 0.1;
        double classMultiplier = (serviceClass == "business") ? 1.2 : 1.0;
        return baseCost * passengers * classMultiplier;
    }
};

class TravelBookingContext {
private:
    unique_ptr<ICostCalculationStrategy> strategy;

public:
    void SetStrategy(unique_ptr<ICostCalculationStrategy> newStrategy) {
        strategy = move(newStrategy);
    }

    double CalculateTravelCost(double distance, int passengers, string serviceClass) const {
        if (!strategy) {
            throw logic_error("Стратегия расчета не установлена.");
        }
        return strategy->CalculateCost(distance, passengers, serviceClass);
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    
    TravelBookingContext context;

    cout << "Выберите транспорт: 1 - Самолет, 2 - Поезд, 3 - Автобус: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            context.SetStrategy(make_unique<AirplaneStrategy>());
            break;
        case 2:
            context.SetStrategy(make_unique<TrainStrategy>());
            break;
        case 3:
            context.SetStrategy(make_unique<BusStrategy>());
            break;
        default:
            cout << "Неверный выбор." << endl;
            return 1;
    }

    cout << "Введите расстояние поездки (км): ";
    double distance;
    cin >> distance;

    cout << "Введите количество пассажиров: ";
    int passengers;
    cin >> passengers;

    cout << "Введите класс обслуживания (economy/business): ";
    string serviceClass;
    cin >> serviceClass;

    try {
        double cost = context.CalculateTravelCost(distance, passengers, serviceClass);
        cout << "Стоимость поездки: " << cost << " единиц" << endl;
    } catch (const logic_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
