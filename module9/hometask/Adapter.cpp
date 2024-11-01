#include <iostream>
#include <string>

using namespace std;

class IPaymentProcessor {
public:
    virtual ~IPaymentProcessor() = default;
    virtual void ProcessPayment(double amount) const = 0;
};

class PayPalPaymentProcessor : public IPaymentProcessor {
public:
    void ProcessPayment(double amount) const override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

class StripePaymentService {
public:
    void MakeTransaction(double totalAmount) const {
        cout << "Processing Stripe payment of $" << totalAmount << endl;
    }
};

class StripePaymentAdapter : public IPaymentProcessor {
private:
    StripePaymentService stripeService;
public:
    void ProcessPayment(double amount) const override {
        stripeService.MakeTransaction(amount);
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    IPaymentProcessor* paypalProcessor = new PayPalPaymentProcessor();
    paypalProcessor->ProcessPayment(50.0);

    IPaymentProcessor* stripeProcessor = new StripePaymentAdapter();
    stripeProcessor->ProcessPayment(75.0);

    delete paypalProcessor;
    delete stripeProcessor;

    return 0;
}
