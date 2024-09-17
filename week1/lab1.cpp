#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee {
protected:
    string name;
    int employeeId;
    string position;

public:
    Employee(string name, int employeeId, string position) : name(name), employeeId(employeeId), position(position) {}

    virtual double calculateSalary() const = 0; 
    
    void displayInfo() const {
        cout << "Имя: " << name << endl;
        cout << "ID: " << employeeId << endl;
        cout << "Должность: " << position << endl;
    }
};

class Worker : public Employee {
private:
    double hourlyRate;
    int hoursWorked;

public:
    Worker(string name, int employeeId, double hourlyRate, int hoursWorked)
        : Employee(name, employeeId, "Рабочий"), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}

    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
};

class Manager : public Employee {
private:
    double fixedSalary;
    double bonus;

public:
    Manager(string name, int employeeId, double fixedSalary, double bonus)
        : Employee(name, employeeId, "Менеджер"), fixedSalary(fixedSalary), bonus(bonus) {}

    double calculateSalary() const override {
        return fixedSalary + bonus;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    vector<Employee*> employees;

    employees.push_back(new Worker("Бахтияр", 1, 20.0, 160));
    employees.push_back(new Manager("Наиль", 2, 3000.0, 500.0));

    for (Employee* employee : employees) {
        employee->displayInfo();
        cout << "Зарплата: " << employee->calculateSalary() << endl;
        cout << "--------------------" << endl;
    }

    for (Employee* employee : employees) {
        delete employee;
    }

    return 0;
}