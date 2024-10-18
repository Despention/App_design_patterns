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
        cout << "Кипячение воды" << endl;
    }

    void pourInCup() {
        cout << "Наливание в чашку" << endl;
    }
};

class Tea : public Beverage {
public:
    void brew() override {
        cout << "Заваривание чая" << endl;
    }

    void addCondiments() override {
        cout << "Добавление лимона" << endl;
    }
};

class Coffee : public Beverage {
public:
    void brew() override {
        cout << "Заваривание кофе" << endl;
    }

    void addCondiments() override {
        cout << "Добавление сахара и молока" << endl;
    }

    bool customerWantsCondiments() override {
        char answer;
        cout << "Добавить сахар и молоко (y/n)? ";
        cin >> answer;
        return (answer == 'y' || answer == 'Y');
    }
};

int main() {
    Tea tea;
    Coffee coffee;

    cout << "\nПриготовление чая:" << endl;
    tea.prepareRecipe();

    cout << "\nПриготовление кофе:" << endl;
    coffee.prepareRecipe();

    return 0;
}
