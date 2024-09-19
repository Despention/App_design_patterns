#include <iostream>
#include <string>

using namespace std;

class OrderService {
public:
    void CreateOrder(const string& productName, int quantity, double price) {
        CalculateAndPrintOrder(productName, quantity, price, "создан");
    }

    void UpdateOrder(const string& productName, int quantity, double price) {
        CalculateAndPrintOrder(productName, quantity, price, "обновлен");
    }

private:
    void CalculateAndPrintOrder(const string& productName, int quantity, double price, const string& action) {
        double totalPrice = quantity * price;
        cout << "Заказ: " << productName << " " << action << ". Общая стоимость: " << totalPrice << endl;
    }
};

class Vehicle { 
public:
    void Start() {
        cout << GetVehicleType() << endl;
    }
    void Stop() {
        cout << GetVehicleType() << endl;
    }

protected:
    virtual string GetVehicleType() const = 0; 
};

class Car : public Vehicle {
protected:
    string GetVehicleType() const override { return "Машина"; }
};

class Truck : public Vehicle {
protected:
    string GetVehicleType() const override { return "Грузовик"; }
};

class Calculator {
public:
    void Add(int a, int b) {
        cout << a + b << endl;
    }
};

class Circle {
public:
    Circle(double radius) : _radius(radius) {}
    double CalculateArea() const {
        return 3.14159 * _radius * _radius; 
    }
private:
    double _radius;
};

class MathOperations {
public:
    int Add(int a, int b) {
        return a + b;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    OrderService orderService;
    orderService.CreateOrder("А", 2, 10.0);
    orderService.UpdateOrder("Б", 3, 12.0);

    Car car;
    Truck truck;
    car.Start();
    truck.Stop();

    Calculator calc;
    calc.Add(5, 3);

    Circle circle(5);
    cout << "Площадь круга: " << circle.CalculateArea() << endl;

    MathOperations math;
    int sum = math.Add(10, 20);
    cout << "Сумма двух чисел: " << sum << endl; 

    return 0;
}