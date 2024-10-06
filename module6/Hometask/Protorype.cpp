#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class ICloneable {
public:
    virtual unique_ptr<ICloneable> Clone() const = 0;
};

class Product : public ICloneable {
private:
    string name;
    double price;
public:
    Product(string n, double p) : name(n), price(p) {}

    unique_ptr<ICloneable> Clone() const override {
        return make_unique<Product>(*this);
    }

    void Show() const {
        cout << "Product: " << name << ", Price: " << price << endl;
    }
};

class Order : public ICloneable {
private:
    vector<unique_ptr<Product>> products;
    double shippingCost;
    string paymentMethod;

public:
    Order(double shipping, const string& payment) 
        : shippingCost(shipping), paymentMethod(payment) {}

    void AddProduct(unique_ptr<Product> product) {
        products.push_back(move(product));
    }

    unique_ptr<ICloneable> Clone() const override {
        unique_ptr<Order> clone = make_unique<Order>(shippingCost, paymentMethod);
        for (const auto& product : products) {
            clone->AddProduct(unique_ptr<Product>(dynamic_cast<Product*>(product->Clone().release())));
        }
        return clone;
    }

    void Show() const {
        for (const auto& product : products) {
            product->Show();
        }
        cout << "Shipping Cost: " << shippingCost << endl;
        cout << "Payment Method: " << paymentMethod << endl;
    }
};

int main() {
    unique_ptr<Order> original = make_unique<Order>(5.99, "Credit Card");
    original->AddProduct(make_unique<Product>("Laptop", 999.99));
    original->AddProduct(make_unique<Product>("Mouse", 49.99));

    unique_ptr<Order> clone = unique_ptr<Order>(dynamic_cast<Order*>(original->Clone().release()));

    original->Show();
    clone->Show();

    return 0;
}
