#include <iostream>

using namespace std;

class IWorker {
public:
    virtual void work() = 0;
};

class IEater {
public:
    virtual void eat() = 0;
};

class ISleeper {
public:
    virtual void sleep() = 0;
};

class HumanWorker : public IWorker, public IEater, public ISleeper {
public:
    void work() override {
        cout << "Человек работает..." << endl;
    }

    void eat() override {
        cout << "Человек ест..." << endl;
    }

    void sleep() override {
        cout << "Человек спит..." << endl;
    }
};

class RobotWorker : public IWorker {
public:
    void work() override {
        cout << "Робот работает..." << endl;
    }
};

int main() {
    HumanWorker humanWorker;
    RobotWorker robotWorker;

    humanWorker.work();
    humanWorker.eat();
    humanWorker.sleep();

    robotWorker.work();

    return 0;
}