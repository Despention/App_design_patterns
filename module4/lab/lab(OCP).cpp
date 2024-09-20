#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

enum class CustomerType { Regular, Silver, Gold, Platinum };

class DiscountCalculator {
public:
    virtual double calculateDiscount(double amount) const = 0;
};

class RegularDiscount : public DiscountCalculator {
public:
    double calculateDiscount(double amount) const override {
        return amount; 
    }
};

class SilverDiscount : public DiscountCalculator {
public:
    double calculateDiscount(double amount) const override {
        return amount * 0.9; 
    }
};

class GoldDiscount : public DiscountCalculator {
public:
    double calculateDiscount(double amount) const override {
        return amount * 0.8; 
    }
};

class PlatinumDiscount : public DiscountCalculator {
public:
    double calculateDiscount(double amount) const override {
        return amount * 0.7; 
    }
};

class DiscountManager {
public:
    void registerDiscountCalculator(CustomerType type, unique_ptr<DiscountCalculator> calculator) {
        calculators[type] = move(calculator);
    }

    double calculateDiscount(CustomerType customerType, double amount) const {
        auto it = calculators.find(customerType);
        if (it != calculators.end()) {
            return it->second->calculateDiscount(amount);
        }
        return amount; 
    }

private:
    unordered_map<CustomerType, unique_ptr<DiscountCalculator>> calculators;
};

int main() {
    DiscountManager manager;
    
    manager.registerDiscountCalculator(CustomerType::Regular, make_unique<RegularDiscount>());
    manager.registerDiscountCalculator(CustomerType::Silver, make_unique<SilverDiscount>());
    manager.registerDiscountCalculator(CustomerType::Gold, make_unique<GoldDiscount>());
    manager.registerDiscountCalculator(CustomerType::Platinum, make_unique<PlatinumDiscount>());

    double amount = 100.0;

    cout << "Regular discount: " << manager.calculateDiscount(CustomerType::Regular, amount) << endl;
    cout << "Silver discount:  " << manager.calculateDiscount(CustomerType::Silver, amount) << endl; 
    cout << "Gold discount:   " << manager.calculateDiscount(CustomerType::Gold, amount) << endl; 
    cout << "Platinum discount: " << manager.calculateDiscount(CustomerType::Platinum, amount) << endl; 

    return 0;
}