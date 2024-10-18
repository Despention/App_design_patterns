#include <iostream>

using namespace std;

class Beverage {
public:
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    virtual bool customerWantsCondiments() {
        return true;  
    }

    void boilWater() {
        cout << "Boiling water" << endl;
    }

    void pourInCup() {
        cout << "Pouring into cup" << endl;
    }
};

class Tea : public Beverage {
public:
    void brew() override {
        cout << "Steeping the tea" << endl;
    }

    void addCondiments() override {
        cout << "Adding lemon" << endl;
    }
};

class Coffee : public Beverage {
public:
    void brew() override {
        cout << "Dripping coffee through filter" << endl;
    }

    void addCondiments() override {
        cout << "Adding sugar and milk" << endl;
    }

    bool customerWantsCondiments() override {
        char answer;
        cout << "Do you want sugar and milk with your coffee (y/n)? ";
        cin >> answer;
        return (answer == 'y' || answer == 'Y');
    }
};

int main() {
    Tea tea;
    Coffee coffee;

    cout << "\nMaking tea..." << endl;
    tea.prepareRecipe();

    cout << "\nMaking coffee..." << endl;
    coffee.prepareRecipe();

    return 0;
}
