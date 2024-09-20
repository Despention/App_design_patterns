#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    string name;
    double baseSalary;
    string employeeType;

    Employee(const string& name, double baseSalary, const string& employeeType)
        : name(name), baseSalary(baseSalary), employeeType(employeeType) {}
};

class EmployeeSalaryCalculator {
public:
    virtual double calculateSalary(const Employee& employee) = 0;
};

class PermanentEmployeeSalaryCalculator : public EmployeeSalaryCalculator {
public:
    double calculateSalary(const Employee& employee) override {
        return employee.baseSalary * 1.2;
    }
};

class ContractEmployeeSalaryCalculator : public EmployeeSalaryCalculator {
public:
    double calculateSalary(const Employee& employee) override {
        return employee.baseSalary * 1.1;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Employee permanentEmployee("Акимов Бахтияр", 5000.0, "Постоянно");
    Employee contractEmployee("Салманов Наиль", 4500.0, "Контракт");

    PermanentEmployeeSalaryCalculator permanentCalculator;
    ContractEmployeeSalaryCalculator contractCalculator;

    double permanentSalary = permanentCalculator.calculateSalary(permanentEmployee);
    double contractSalary = contractCalculator.calculateSalary(contractEmployee);

    cout << "Заработная плата постоянных сотрудников: " << permanentSalary << endl;
    cout << "Заработная плата сотрудников по контракту: " << contractSalary << endl;

    return 0;
}