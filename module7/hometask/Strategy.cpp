#include <iostream>
#include <memory>

using namespace std;

class IPaymentStrategy {
public:
    virtual void pay(int amount) const = 0;
    virtual ~IPaymentStrategy() = default;
};

class CreditCardPayment : public IPaymentStrategy {
public:
    void pay(int amount) const override {
        cout << "Оплата " << amount << " с использованием банковской карты.\n";
    }
};

class PayPalPayment : public IPaymentStrategy {
public:
    void pay(int amount) const override {
        cout << "Оплата " << amount << " с использованием PayPal.\n";
    }
};

class CryptoPayment : public IPaymentStrategy {
public:
    void pay(int amount) const override {
        cout << "Оплата " << amount << " с использованием криптовалюты.\n";
    }
};

class PaymentContext {
private:
    unique_ptr<IPaymentStrategy> strategy;

public:
    void setStrategy(unique_ptr<IPaymentStrategy> newStrategy) {
        strategy = move(newStrategy);
    }

    void pay(int amount) const {
        if (strategy) {
            strategy->pay(amount);
        } else {
            cout << "Стратегия оплаты не выбрана.\n";
        }
    }
};

int main() {
    PaymentContext paymentContext;

    paymentContext.setStrategy(make_unique<CreditCardPayment>());
    paymentContext.pay(100);

    paymentContext.setStrategy(make_unique<PayPalPayment>());
    paymentContext.pay(200);

    paymentContext.setStrategy(make_unique<CryptoPayment>());
    paymentContext.pay(300);

    return 0;
}
