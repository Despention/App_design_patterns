#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Transport {
public:
    virtual void Move() const = 0;
    virtual void FuelUp() const = 0;
    virtual ~Transport() = default;
};

class Car : public Transport {
private:
    string model;
    int speed;

public:
    Car(const string& model, int speed) : model(model), speed(speed) {}

    void Move() const override {
        cout << "Автомобиль " << model << " движется со скоростью " << speed << " км/ч.\n";
    }

    void FuelUp() const override {
        cout << "Заправка автомобиля.\n";
    }
};

class Motorcycle : public Transport {
private:
    string model;
    int speed;

public:
    Motorcycle(const string& model, int speed) : model(model), speed(speed) {}

    void Move() const override {
        cout << "Мотоцикл " << model << " движется со скоростью " << speed << " км/ч.\n";
    }

    void FuelUp() const override {
        cout << "Заправка мотоцикла.\n";
    }
};

class Plane : public Transport {
private:
    string model;
    int speed;

public:
    Plane(const string& model, int speed) : model(model), speed(speed) {}

    void Move() const override {
        cout << "Самолет " << model << " летит со скоростью " << speed << " км/ч.\n";
    }

    void FuelUp() const override {
        cout << "Заправка самолета.\n";
    }
};

class Bicycle : public Transport {
private:
    string model;
    int speed;

public:
    Bicycle(const string& model, int speed) : model(model), speed(speed) {}

    void Move() const override {
        cout << "Велосипед " << model << " едет со скоростью " << speed << " км/ч.\n";
    }

    void FuelUp() const override {
        cout << "Велосипед не нуждается в заправке.\n";
    }
};

class TransportFactory {
public:
    virtual unique_ptr<Transport> CreateTransport(const string& model, int speed) const = 0;
    virtual ~TransportFactory() = default;
};

class CarFactory : public TransportFactory {
public:
    unique_ptr<Transport> CreateTransport(const string& model, int speed) const override {
        return make_unique<Car>(model, speed);
    }
};

class MotorcycleFactory : public TransportFactory {
public:
    unique_ptr<Transport> CreateTransport(const string& model, int speed) const override {
        return make_unique<Motorcycle>(model, speed);
    }
};

class PlaneFactory : public TransportFactory {
public:
    unique_ptr<Transport> CreateTransport(const string& model, int speed) const override {
        return make_unique<Plane>(model, speed);
    }
};

class BicycleFactory : public TransportFactory {
public:
    unique_ptr<Transport> CreateTransport(const string& model, int speed) const override {
        return make_unique<Bicycle>(model, speed);
    }
};

void CreateAndUseTransport(const TransportFactory& factory) {
    string model;
    int speed;

    cout << "Введите модель транспорта: ";
    cin >> model;
    cout << "Введите скорость транспорта (км/ч): ";
    cin >> speed;

    auto transport = factory.CreateTransport(model, speed);
    transport->Move();
    transport->FuelUp();
}

int main() {
    setlocale(LC_ALL, "Rus");

    int choice;
    cout << "Выберите тип транспорта:\n1. Автомобиль\n2. Мотоцикл\n3. Самолет\n4. Велосипед\n";
    cin >> choice;

    switch (choice) {
        case 1: {
            CarFactory carFactory;
            CreateAndUseTransport(carFactory);
            break;
        }
        case 2: {
            MotorcycleFactory motorcycleFactory;
            CreateAndUseTransport(motorcycleFactory);
            break;
        }
        case 3: {
            PlaneFactory planeFactory;
            CreateAndUseTransport(planeFactory);
            break;
        }
        case 4: {
            BicycleFactory bicycleFactory;
            CreateAndUseTransport(bicycleFactory);
            break;
        }
        default:
            cout << "Неверный выбор.\n";
            break;
    }

    return 0;
}
