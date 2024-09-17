#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Vehicle {
    string brand;
    string model;
    int year;

    Vehicle(string brand, string model, int year) : brand(brand), model(model), year(year) {}

    void displayInfo() const {
        cout << "Марка: " << brand << endl;
        cout << "Модель: " << model << endl;
        cout << "Год выпуска: " << year << endl;
    }
};

struct Car : public Vehicle {
    int doors;
    string transmission;

    Car(string brand, string model, int year, int doors, string transmission)
        : Vehicle(brand, model, year), doors(doors), transmission(transmission) {}

    void displayInfo() const {
        Vehicle::displayInfo();
        cout << "Количество дверей: " << doors << endl;
        cout << "Тип трансмиссии: " << transmission << endl;
    }
};

struct Motorcycle : public Vehicle {
    string bodyType;
    bool hasBox;

    Motorcycle(string brand, string model, int year, string bodyType, bool hasBox)
        : Vehicle(brand, model, year), bodyType(bodyType), hasBox(hasBox) {}

    void displayInfo() const {
        Vehicle::displayInfo();
        cout << "Тип кузова: " << bodyType << endl;
        cout << "Наличие бокса: " << (hasBox ? "Да" : "Нет") << endl;
    }
};

struct Garage {
    vector<Vehicle*> vehicles;

    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
        cout << "Транспортное средство добавлено в гараж." << endl;
    }

    void removeVehicle(Vehicle* vehicle) {
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if (*it == vehicle) {
                vehicles.erase(it);
                cout << "Транспортное средство удалено из гаража." << endl;
                return;
            }
        }
        cout << "Транспортное средство не найдено в гараже." << endl;
    }

    void displayVehicles() const {
        cout << "Транспортные средства в гараже:" << endl;
        for (const auto& vehicle : vehicles) {
            vehicle->displayInfo();
            cout << "--------------------" << endl;
        }
    }
};

struct Autopark {
    vector<Garage*> garages;

    void addGarage(Garage* garage) {
        garages.push_back(garage);
        cout << "Гараж добавлен в автопарк." << endl;
    }

    void removeGarage(Garage* garage) {
        for (auto it = garages.begin(); it != garages.end(); ++it) {
            if (*it == garage) {
                garages.erase(it);
                cout << "Гараж удален из автопарка." << endl;
                return;
            }
        }
        cout << "Гараж не найден в автопарке." << endl;
    }

    void searchVehicle(const Vehicle* vehicle) const {
        for (const auto& garage : garages) {
            for (const auto& v : garage->vehicles) {
                if (v == vehicle) {
                    cout << "Транспортное средство найдено в гараже." << endl;
                    return;
                }
            }
        }
        cout << "Транспортное средство не найдено в автопарке." << endl;
    }

    void displayGarages() const {
        cout << "Гаражи в автопарке:" << endl;
        for (const auto& garage : garages) {
            garage->displayVehicles();
            cout << "--------------------" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    Car car("Toyota", "Camry", 2022, 4, "Automatic");
    Motorcycle motorcycle("Harley-Davidson", "Sportster", 2021, "Cruiser", true);

    Garage garage1;
    Garage garage2;

    garage1.addVehicle(&car);
    garage2.addVehicle(&motorcycle);

    Autopark autopark;
    autopark.addGarage(&garage1);
    autopark.addGarage(&garage2);

    autopark.searchVehicle(&car);
    autopark.displayGarages();

    return 0;
}