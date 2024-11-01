#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Beverage {
public:
    virtual ~Beverage() = default;
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
};

class Espresso : public Beverage {
public:
    string getDescription() const override {
        return "Espresso";
    }

    double cost() const override {
        return 2.00;
    }
};

class Tea : public Beverage {
public:
    string getDescription() const override {
        return "Tea";
    }

    double cost() const override {
        return 1.50;
    }
};

class BeverageDecorator : public Beverage {
protected:
    shared_ptr<Beverage> beverage;
public:
    explicit BeverageDecorator(shared_ptr<Beverage> b) : beverage(b) {}
};

class Milk : public BeverageDecorator {
public:
    explicit Milk(shared_ptr<Beverage> b) : BeverageDecorator(b) {}

    string getDescription() const override {
        return beverage->getDescription() + ", Milk";
    }

    double cost() const override {
        return beverage->cost() + 0.50;
    }
};

class Sugar : public BeverageDecorator {
public:
    explicit Sugar(shared_ptr<Beverage> b) : BeverageDecorator(b) {}

    string getDescription() const override {
        return beverage->getDescription() + ", Sugar";
    }

    double cost() const override {
        return beverage->cost() + 0.25;
    }
};

class WhippedCream : public BeverageDecorator {
public:
    explicit WhippedCream(shared_ptr<Beverage> b) : BeverageDecorator(b) {}

    string getDescription() const override {
        return beverage->getDescription() + ", Whipped Cream";
    }

    double cost() const override {
        return beverage->cost() + 0.75;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    shared_ptr<Beverage> myDrink = make_shared<Espresso>();
    myDrink = make_shared<Milk>(myDrink);
    myDrink = make_shared<Sugar>(myDrink);
    myDrink = make_shared<WhippedCream>(myDrink);

    cout << "Drink: " << myDrink->getDescription() << endl;
    cout << "Cost: $" << myDrink->cost() << endl;

    return 0;
}
