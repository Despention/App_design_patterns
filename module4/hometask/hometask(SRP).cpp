#include <iostream>
#include <string>

using namespace std;

class Order {
public:
    string productName;
    int quantity;
    double price;

    Order(const string& productName, int quantity, double price)
        : productName(productName), quantity(quantity), price(price) {}
};

class OrderCalculator {
public:
    double calculateTotalPrice(const Order& order) {
        return order.quantity * order.price * 0.9;
    }
};

class PaymentProcessor {
public:
    void processPayment(const string& paymentDetails) {
        cout << "Оплата производится с помощью: " << paymentDetails << endl;
    }
};

class NotificationService {
public:
    void sendConfirmationEmail(const string& email) {
        cout << "Подтверждение отправлено по электронной почте: " << email << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Order order("A", 2, 10.0);
    OrderCalculator calculator;
    PaymentProcessor processor;
    NotificationService notifier;

    double totalPrice = calculator.calculateTotalPrice(order);
    processor.processPayment("Кредитная карта");
    notifier.sendConfirmationEmail("akim@gmail.com");

    return 0;
}