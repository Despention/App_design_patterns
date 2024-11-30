#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Product {
public:
    int id;
    string name;
    double price;

    Product(int id, string name, double price)
        : id(id), name(name), price(price) {}
};

class Order {
private:
    vector<Product> products;
    bool paymentConfirmed;

public:
    Order() : paymentConfirmed(false) {}

    void addProduct(Product p) {
        products.push_back(p);
        cout << "Товар добавлен в корзину: " << p.name << endl;
    }

    void checkout() {
        cout << "Оформление заказа..." << endl;
        for (auto &p : products) {
            cout << "Товар: " << p.name << ", Цена: " << p.price << endl;
        }
    }

    void pay() {
        paymentConfirmed = true;
        cout << "Оплата подтверждена." << endl;
    }

    void processOrder() {
        if (paymentConfirmed) {
            cout << "Заказ обработан и отправлен на доставку." << endl;
        } else {
            cout << "Оплата не подтверждена. Невозможно обработать заказ." << endl;
        }
    }
};

int main() {
    Order order;
    Product p1(1, "Ноутбук", 1000.0);
    Product p2(2, "Смартфон", 500.0);

    order.addProduct(p1);
    order.addProduct(p2);

    order.checkout();
    order.pay();
    order.processOrder();

    return 0;
}
