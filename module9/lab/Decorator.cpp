#include <iostream>
#include <string>
#include <memory>

using namespace std;

class IBeverage {
public:
    virtual double GetCost() const = 0;
    virtual string GetDescription() const = 0;
    virtual ~IBeverage() = default;
};

class Coffee : public IBeverage {
public:
    double GetCost() const override { return 50.0; }
    string GetDescription() const override { return "Кофе"; }
};

class BeverageDecorator : public IBeverage {
protected:
    unique_ptr<IBeverage> beverage_;
public:
    BeverageDecorator(unique_ptr<IBeverage> beverage) : beverage_(move(beverage)) {}
    virtual double GetCost() const override { return beverage_->GetCost(); }
    virtual string GetDescription() const override { return beverage_->GetDescription(); }
};

class MilkDecorator : public BeverageDecorator {
public:
    MilkDecorator(unique_ptr<IBeverage> beverage) : BeverageDecorator(move(beverage)) {}
    double GetCost() const override { return BeverageDecorator::GetCost() + 100.0; }
    string GetDescription() const override { return BeverageDecorator::GetDescription() + ", Молоко"; }
};

class SugarDecorator : public BeverageDecorator {
public:
    SugarDecorator(unique_ptr<IBeverage> beverage) : BeverageDecorator(move(beverage)) {}
    double GetCost() const override { return BeverageDecorator::GetCost() + 50.0; }
    string GetDescription() const override { return BeverageDecorator::GetDescription() + ", Сахар"; }
};

class ChocolateDecorator : public BeverageDecorator {
public:
    ChocolateDecorator(unique_ptr<IBeverage> beverage) : BeverageDecorator(move(beverage)) {}
    double GetCost() const override { return BeverageDecorator::GetCost() + 150.0; }
    string GetDescription() const override { return BeverageDecorator::GetDescription() + ", Шоколад"; }
};

int main() {
    setlocale(LC_ALL, "rus");
    
    unique_ptr<IBeverage> beverage = make_unique<Coffee>();
    cout << beverage->GetDescription() << " : " << beverage->GetCost() << " тенге.\n";

    beverage = make_unique<MilkDecorator>(move(beverage));
    cout << beverage->GetDescription() << " : " << beverage->GetCost() << " тенге.\n";

    beverage = make_unique<SugarDecorator>(move(beverage));
    cout << beverage->GetDescription() << " : " << beverage->GetCost() << " тенге.\n";

    beverage = make_unique<ChocolateDecorator>(move(beverage));
    cout << beverage->GetDescription() << " : " << beverage->GetCost() << " тенге.\n";

    return 0;
}
