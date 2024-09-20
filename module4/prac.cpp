#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Продукты
class Product {
public:
    string name;
    double price;

    Product(const string& name, double price) : name(name), price(price) {}
};

// Интерфейс для оплаты
class IPayment {
public:
    virtual void processPayment(double amount) const = 0;
};

// Интерфейс для доставки
class IDelivery {
public:
    virtual void deliverOrder(int orderId) const = 0;
};

// Оплата
class CreditCardPayment : public IPayment {
public:
    void processPayment(double amount) const override {
        cout << "Обработка платежа по кредитной карте на сумму " << amount << " RUB" << endl;
    }
};

class PayPalPayment : public IPayment {
public:
    void processPayment(double amount) const override {
        cout << "Обработка платежа через PayPal на сумму " << amount << " RUB" << endl;
    }
};

// Доставка
class CourierDelivery : public IDelivery {
public:
    void deliverOrder(int orderId) const override {
        cout << "Доставка заказа #" << orderId << " курьером." << endl;
    }
};

class PostDelivery : public IDelivery {
public:
    void deliverOrder(int orderId) const override {
        cout << "Доставка заказа #" << orderId << " почтой." << endl;
    }
};

// Заказы
class Order {
public:
    int id; 
    vector<Product> products;
    shared_ptr<IDelivery> delivery;
    shared_ptr<IPayment> payment; 

    Order(int id) : id(id) {}

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& product : products) {
            total += product.price;
        }
        return total;
    }

    void setDelivery(shared_ptr<IDelivery> delivery) {
        this->delivery = delivery;
    }

    void setPayment(shared_ptr<IPayment> payment) {
        this->payment = payment;
    }

    void processOrder() {
        double total = calculateTotal();
        cout << "Обработка заказа #" << id << endl;
        cout << "Итого: " << total << " RUB" << endl;

        if (payment) {
            payment->processPayment(total);
        } else {
            cout << "Способ оплаты не выбран." << endl;
        }

        if (delivery) {
            delivery->deliverOrder(id);
        } else {
            cout << "Способ доставки не выбран." << endl;
        }
    }
};

// Уведомления
class INotification {
public:
    virtual void sendNotification(const string& message) const = 0;
};

class EmailNotification : public INotification {
public:
    void sendNotification(const string& message) const override {
        cout << "Отправка уведомления по электронной почте: " << message << endl;
    }
};

class SmsNotification : public INotification {
public:
    void sendNotification(const string& message) const override {
        cout << "Отправка SMS уведомления: " << message << endl;
    }
};

// Скидки 
class DiscountCalculator {
public:
    virtual double applyDiscount(double amount) const = 0;
};

class NoDiscount : public DiscountCalculator {
public:
    double applyDiscount(double amount) const override {
        return amount; 
    }
};

class TenPercentDiscount : public DiscountCalculator {
public:
    double applyDiscount(double amount) const override {
        return amount * 0.9;  
    }
};

int main() {
    Product product1("Футболка", 500.0);
    Product product2("Брюки", 1000.0);

    Order order(1);
    order.addProduct(product1);
    order.addProduct(product2);

    auto payment = make_shared<CreditCardPayment>(); 
    order.setPayment(payment);

    auto delivery = make_shared<CourierDelivery>();
    order.setDelivery(delivery);

    order.processOrder(); 

    return 0;
}
