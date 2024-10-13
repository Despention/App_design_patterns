#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class IObserver {
public:
    virtual void Update(string stock, float price) = 0;
    virtual ~IObserver() = default;
};

class ISubject {
public:
    virtual void RegisterObserver(shared_ptr<IObserver> observer) = 0;
    virtual void RemoveObserver(shared_ptr<IObserver> observer) = 0;
    virtual void NotifyObservers(string stock) = 0;
    virtual ~ISubject() = default;
};

class StockExchange : public ISubject {
private:
    vector<shared_ptr<IObserver>> observers;
    float appleStockPrice = 150.0f;
    float googleStockPrice = 2700.0f;

public:
    void SetStockPrice(string stock, float newPrice) {
        if (stock == "Apple") {
            appleStockPrice = newPrice;
        } else if (stock == "Google") {
            googleStockPrice = newPrice;
        }
        NotifyObservers(stock);
    }

    float GetStockPrice(string stock) const {
        if (stock == "Apple") return appleStockPrice;
        else if (stock == "Google") return googleStockPrice;
        return 0.0f;
    }

    void RegisterObserver(shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
    }

    void RemoveObserver(shared_ptr<IObserver> observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void NotifyObservers(string stock) override {
        for (const auto& observer : observers) {
            observer->Update(stock, GetStockPrice(stock));
        }
    }
};

class Trader : public IObserver {
private:
    string name;

public:
    Trader(string n) : name(n) {}

    void Update(string stock, float price) override {
        cout << "Трейдер " << name << " получил уведомление: акция " << stock << " теперь стоит " << price << " долларов.\n";
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    
    auto stockExchange = make_shared<StockExchange>();

    auto trader1 = make_shared<Trader>("Алексей");
    auto trader2 = make_shared<Trader>("Мария");

    stockExchange->RegisterObserver(trader1);
    stockExchange->RegisterObserver(trader2);

    stockExchange->SetStockPrice("Apple", 155.0f);
    stockExchange->SetStockPrice("Google", 2750.0f);

    stockExchange->RemoveObserver(trader2);
    stockExchange->SetStockPrice("Apple", 160.0f);

    return 0;
}
