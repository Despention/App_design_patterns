#include <iostream>
#include <memory>

using namespace std;

class IPaymentProcessor {
public:
    virtual void ProcessPayment(double amount) = 0;
    virtual void RefundPayment(double amount) = 0;
    virtual ~IPaymentProcessor() = default;
};

class InternalPaymentProcessor : public IPaymentProcessor {
public:
    void ProcessPayment(double amount) override {
        cout << "Обработка платежа на сумму " << amount << " тенге. через внутреннюю систему.\n";
    }

    void RefundPayment(double amount) override {
        cout << "Возврат платежа на сумму " << amount << " тенге. через внутреннюю систему.\n";
    }
};

class ExternalPaymentSystemA {
public:
    void MakePayment(double amount) {
        cout << "Платеж на сумму " << amount << " тенге. через Внешнюю Платежную Систему A.\n";
    }

    void MakeRefund(double amount) {
        cout << "Возврат на сумму " << amount << " тенге. через Внешнюю Платежную Систему A.\n";
    }
};

class PaymentAdapterA : public IPaymentProcessor {
private:
    ExternalPaymentSystemA externalSystemA;
public:
    void ProcessPayment(double amount) override {
        externalSystemA.MakePayment(amount);
    }

    void RefundPayment(double amount) override {
        externalSystemA.MakeRefund(amount);
    }
};

class ExternalPaymentSystemB {
public:
    void SendPayment(double amount) {
        cout << "Отправка платежа на сумму " << amount << " тенге. через Внешнюю Платежную Систему B.\n";
    }

    void ProcessRefund(double amount) {
        cout << "Возврат на сумму " << amount << " тенге. через Внешнюю Платежную Систему B.\n";
    }
};

class PaymentAdapterB : public IPaymentProcessor {
private:
    ExternalPaymentSystemB externalSystemB;
public:
    void ProcessPayment(double amount) override {
        externalSystemB.SendPayment(amount);
    }

    void RefundPayment(double amount) override {
        externalSystemB.ProcessRefund(amount);
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    unique_ptr<IPaymentProcessor> processor = make_unique<InternalPaymentProcessor>();
    processor->ProcessPayment(10000.0);
    processor->RefundPayment(5000.0);

    processor = make_unique<PaymentAdapterA>();
    processor->ProcessPayment(20000.0);
    processor->RefundPayment(1000.0);

    processor = make_unique<PaymentAdapterB>();
    processor->ProcessPayment(3000.0);
    processor->RefundPayment(1500.0);

    return 0;
}
