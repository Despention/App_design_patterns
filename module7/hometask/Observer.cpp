#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class IObserver {
public:
    virtual void update(float exchangeRate) = 0;
    virtual ~IObserver() = default;
};

class ISubject {
public:
    virtual void addObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void removeObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~ISubject() = default;
};

class CurrencyExchange : public ISubject {
private:
   vector<std::shared_ptr<IObserver>> observers;
    float exchangeRate;

public:
    void setExchangeRate(float rate) {
        exchangeRate = rate;
        notifyObservers();
    }

    void addObserver(std::shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<IObserver> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override {
        for (const auto& observer : observers) {
            observer->update(exchangeRate);
        }
    }
};

class ConsoleObserver : public IObserver {
public:
    void update(float exchangeRate) override {
       cout << "Обновленный курс валют: " << exchangeRate << "\n";
    }
};

class AlertObserver : public IObserver {
public:
    void update(float exchangeRate) override {
       cout << "Предупреждение! Курс изменен на: " << exchangeRate << "\n";
    }
};

class LogObserver : public IObserver {
public:
    void update(float exchangeRate) override {
       cout << "Записано в лог: Курс валют обновлен на " << exchangeRate << "\n";
    }
};

// Клиентский код
int main() {
    auto exchange =make_shared<CurrencyExchange>();

    auto consoleObserver =make_shared<ConsoleObserver>();
    auto logObserver =make_shared<LogObserver>();
    auto alertObserver =make_shared<AlertObserver>();

    exchange->addObserver(consoleObserver);
    exchange->addObserver(logObserver);
    exchange->addObserver(alertObserver);

    exchange->setExchangeRate(78.5);
    exchange->setExchangeRate(79.2);

    exchange->removeObserver(logObserver);

    exchange->setExchangeRate(80.1);

    return 0;
}
