#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class IMediator {
public:
    virtual void sendMessage(const string& message, class IUser* user) = 0;
    virtual void addUser(shared_ptr<IUser> user) = 0;
};

class IUser {
protected:
    IMediator* mediator;
    string name;
public:
    IUser(IMediator* m, const string& n) : mediator(m), name(n) {}
    virtual void send(const string& message) = 0;
    virtual void receive(const string& message) = 0;
    string getName() const {
        return name;
    }
};

class ChatMediator : public IMediator {
    vector<shared_ptr<IUser>> users;
public:
    void sendMessage(const string& message, IUser* sender) override {
        for (auto& user : users) {
            if (user.get() != sender) {
                user->receive(message);
            }
        }
    }

    void addUser(shared_ptr<IUser> user) override {
        users.push_back(user);
        cout << user->getName() << " has joined the chat." << endl;
    }
};

class User : public IUser {
public:
    User(IMediator* m, const string& n) : IUser(m, n) {}

    void send(const string& message) override {
        cout << name << " sends: " << message << endl;
        mediator->sendMessage(message, this);
    }

    void receive(const string& message) override {
        cout << name << " receives: " << message << endl;
    }
};

int main() {
    ChatMediator chatMediator;

    auto user1 = make_shared<User>(&chatMediator, "Alice");
    auto user2 = make_shared<User>(&chatMediator, "Bob");
    auto user3 = make_shared<User>(&chatMediator, "Charlie");

    chatMediator.addUser(user1);
    chatMediator.addUser(user2);
    chatMediator.addUser(user3);

    user1->send("Hello, everyone!");
    user2->send("Hi, Alice!");
    user3->send("Hey, Bob!");

    return 0;
}
