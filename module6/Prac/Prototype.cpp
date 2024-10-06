#include <iostream>
#include <string>
#include <memory>

using namespace std;

class ICloneable {
public:
    virtual unique_ptr<ICloneable> Clone() const = 0;
};

class Weapon : public ICloneable {
private:
    string name;
    int damage;

public:
    Weapon(string name, int damage) : name(name), damage(damage) {}
    
    unique_ptr<ICloneable> Clone() const override {
        return make_unique<Weapon>(*this);
    }
    
    void Show() const {
        cout << "Weapon: " << name << ", Damage: " << damage << endl;
    }
};

class Character : public ICloneable {
private:
    string name;
    int health;
    unique_ptr<Weapon> weapon;

public:
    Character(string name, int health, unique_ptr<Weapon> weapon)
        : name(name), health(health), weapon(move(weapon)) {}
    
    unique_ptr<ICloneable> Clone() const override {
        return make_unique<Character>(name, health, make_unique<Weapon>(*weapon));
    }
    
    void Show() const {
        cout << "Character: " << name << ", Health: " << health << endl;
        weapon->Show();
    }
};

int main() {
    unique_ptr<Character> original = make_unique<Character>("Hero", 100, make_unique<Weapon>("Sword", 50));

    unique_ptr<Character> clone = unique_ptr<Character>(dynamic_cast<Character*>(original->Clone().release()));

    original->Show();
    clone->Show();

    return 0;
}
