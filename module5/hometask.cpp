#include <iostream>
#include <string>
#include <memory>

using namespace std;

class IVehicle {
public:
    virtual void Drive() const = 0;
    virtual void Refuel() const = 0;
    virtual ~IVehicle() = default;
};

class Car : public IVehicle {
private:
    string brand;
    string model;
    string fuelType;

public:
    Car(const string& brand, const string& model, const string& fuelType)
        : brand(brand), model(model), fuelType(fuelType) {}

    void Drive() const override {
        cout << "Автомобиль " << brand << " " << model << " едет.\n";
    }

    void Refuel() const override {
        cout << "Заправка автомобиля топливом типа: " << fuelType << ".\n";
    }
};

class Motorcycle : public IVehicle {
private:
    string type;
    int engineCapacity;

public:
    Motorcycle(const string& type, int engineCapacity)
        : type(type), engineCapacity(engineCapacity) {}

    void Drive() const override {
        cout << "Мотоцикл типа " << type << " с объемом двигателя " << engineCapacity << "cc едет.\n";
    }

    void Refuel() const override {
        cout << "Заправка мотоцикла.\n";
    }
};

class Truck : public IVehicle {
private:
    int loadCapacity;
    int axles;

public:
    Truck(int loadCapacity, int axles)
        : loadCapacity(loadCapacity), axles(axles) {}

    void Drive() const override {
        cout << "Грузовик с грузоподъемностью " << loadCapacity << " кг и " << axles << " осями едет.\n";
    }

    void Refuel() const override {
        cout << "Заправка грузовика.\n";
    }
};

class VehicleFactory {
public:
    virtual unique_ptr<IVehicle> CreateVehicle() const = 0;
    virtual ~VehicleFactory() = default;
};

class CarFactory : public VehicleFactory {
public:
    unique_ptr<IVehicle> CreateVehicle() const override {
        string brand, model, fuelType;
        cout << "Введите марку автомобиля: ";
        cin >> brand;
        cout << "Введите модель автомобиля: ";
        cin >> model;
        cout << "Введите тип топлива: ";
        cin >> fuelType;
        return make_unique<Car>(brand, model, fuelType);
    }
};

class MotorcycleFactory : public VehicleFactory {
public:
    unique_ptr<IVehicle> CreateVehicle() const override {
        string type;
        int engineCapacity;
        cout << "Введите тип мотоцикла (спортивный/туристический): ";
        cin >> type;
        cout << "Введите объем двигателя (cc): ";
        cin >> engineCapacity;
        return make_unique<Motorcycle>(type, engineCapacity);
    }
};

class TruckFactory : public VehicleFactory {
public:
    unique_ptr<IVehicle> CreateVehicle() const override {
        int loadCapacity, axles;
        cout << "Введите грузоподъемность грузовика (кг): ";
        cin >> loadCapacity;
        cout << "Введите количество осей: ";
        cin >> axles;
        return make_unique<Truck>(loadCapacity, axles);
    }
};

class Bus : public IVehicle {
private:
    int passengerCapacity;

public:
    Bus(int passengerCapacity) : passengerCapacity(passengerCapacity) {}

    void Drive() const override {
        cout << "Автобус с вместимостью " << passengerCapacity << " пассажиров едет.\n";
    }

    void Refuel() const override {
        cout << "Заправка автобуса.\n";
    }
};

// Фабрика для создания автобусов
class BusFactory : public VehicleFactory {
public:
    unique_ptr<IVehicle> CreateVehicle() const override {
        int passengerCapacity;
        cout << "Введите вместимость автобуса (пассажиров): ";
        cin >> passengerCapacity;
        return make_unique<Bus>(passengerCapacity);
    }
};

void CreateVehicleFromFactory(const VehicleFactory& factory) {
    auto vehicle = factory.CreateVehicle();
    vehicle->Drive();
    vehicle->Refuel();
}

int main() {
    setlocale(LC_ALL, "Rus");
    
    int choice;
    cout << "Выберите тип транспорта:\n1. Автомобиль\n2. Мотоцикл\n3. Грузовик\n4. Автобус\n";
    cin >> choice;

    switch (choice) {
        case 1: {
            CarFactory carFactory;
            CreateVehicleFromFactory(carFactory);
            break;
        }
        case 2: {
            MotorcycleFactory motorcycleFactory;
            CreateVehicleFromFactory(motorcycleFactory);
            break;
        }
        case 3: {
            TruckFactory truckFactory;
            CreateVehicleFromFactory(truckFactory);
            break;
        }
        case 4: {
            BusFactory busFactory;
            CreateVehicleFromFactory(busFactory);
            break;
        }
        default:
            cout << "Неверный выбор.\n";
            break;
    }

    return 0;
}
