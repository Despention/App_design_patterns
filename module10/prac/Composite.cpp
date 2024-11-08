#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

class OrganizationComponent {
protected:
    string name;

public:
    OrganizationComponent(const string& name) : name(name) {}
    virtual void Display(int depth) const = 0;
    virtual double GetBudget() const = 0;
    virtual int GetEmployeeCount() const = 0;
    virtual ~OrganizationComponent() = default;
};

class Employee : public OrganizationComponent {
    string position;
    double salary;

public:
    Employee(const string& name, const string& position, double salary)
        : OrganizationComponent(name), position(position), salary(salary) {}

    void Display(int depth) const override {
        cout << string(depth, '-') << " Employee: " << name << ", Position: " << position << ", Salary: " << salary << endl;
    }

    double GetBudget() const override {
        return salary;
    }

    int GetEmployeeCount() const override {
        return 1;
    }
};

class Department : public OrganizationComponent {
    vector<OrganizationComponent*> components;

public:
    Department(const string& name) : OrganizationComponent(name) {}

    void Add(OrganizationComponent* component) {
        components.push_back(component);
    }

    void Remove(OrganizationComponent* component) {
        components.erase(remove(components.begin(), components.end(), component), components.end());
    }

    void Display(int depth) const override {
        cout << string(depth, '-') << " Department: " << name << endl;
        for (const auto& component : components) {
            component->Display(depth + 2);
        }
    }

    double GetBudget() const override {
        double totalBudget = 0;
        for (const auto& component : components) {
            totalBudget += component->GetBudget();
        }
        return totalBudget;
    }

    int GetEmployeeCount() const override {
        int totalCount = 0;
        for (const auto& component : components) {
            totalCount += component->GetEmployeeCount();
        }
        return totalCount;
    }

    ~Department() {
        for (auto component : components) {
            delete component;
        }
    }
};

int main() {
    Department* headOffice = new Department("Head Office");

    Employee* emp1 = new Employee("Ardasher", "Manager", 700000);
    Employee* emp2 = new Employee("Bakhtiyar", "Developer", 500000);

    Department* itDepartment = new Department("IT Department");
    itDepartment->Add(emp1);
    itDepartment->Add(emp2);

    Employee* emp3 = new Employee("Ali", "Analyst", 60000);
    Employee* emp4 = new Employee("Nail", "Designer", 45000);

    Department* marketingDepartment = new Department("Marketing Department");
    marketingDepartment->Add(emp3);
    marketingDepartment->Add(emp4);

    headOffice->Add(itDepartment);
    headOffice->Add(marketingDepartment);

    cout << "Corporate Structure:" << endl;
    headOffice->Display(1);

    cout << "\nTotal Budget: $" << headOffice->GetBudget() << endl;
    cout << "Total Employees: " << headOffice->GetEmployeeCount() << endl;

    delete headOffice;
    return 0;
}
