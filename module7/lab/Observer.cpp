#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class IObserver {
public:
    virtual void Update(float temperature) = 0;
    virtual ~IObserver() = default;
};

class ISubject {
public:
    virtual void RegisterObserver(shared_ptr<IObserver> observer) = 0;
    virtual void RemoveObserver(shared_ptr<IObserver> observer) = 0;
    virtual void NotifyObservers() = 0;
    virtual ~ISubject() = default;
};

class WeatherStation : public ISubject {
private:
    vector<shared_ptr<IObserver>> observers;
    float temperature;

public:
    void SetTemperature(float newTemperature) {
        temperature = newTemperature;
        NotifyObservers();
    }

    void RegisterObserver(shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
    }

    void RemoveObserver(shared_ptr<IObserver> observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void NotifyObservers() override {
        for (const auto& observer : observers) {
            observer->Update(temperature);
        }
    }
};

class WeatherDisplay : public IObserver {
private:
    string name;

public:
    WeatherDisplay(string n) : name(n) {}

    void Update(float temperature) override {
        cout << name << " показывает новую температуру: " << temperature << "°C\n";
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    
    auto weatherStation = make_shared<WeatherStation>();

    auto mobileApp = make_shared<WeatherDisplay>("Мобильное приложение");
    auto digitalBillboard = make_shared<WeatherDisplay>("Электронное табло");

    weatherStation->RegisterObserver(mobileApp);
    weatherStation->RegisterObserver(digitalBillboard);

    weatherStation->SetTemperature(25.0f);
    weatherStation->SetTemperature(30.0f);

    weatherStation->RemoveObserver(digitalBillboard);
    weatherStation->SetTemperature(28.0f);

    return 0;
}
