#include <iostream>
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

class ChatRoom : public IMediator {
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
    ChatRoom chatRoom;

    auto user1 = make_shared<User>(&chatRoom, "Alice");
    auto user2 = make_shared<User>(&chatRoom, "Bob");
    auto user3 = make_shared<User>(&chatRoom, "Charlie");

    chatRoom.addUser(user1);
    chatRoom.addUser(user2);
    chatRoom.addUser(user3);

    user1->send("Hello everyone!");
    user2->send("Hi Alice!");
    user3->send("Hey Bob!");

    return 0;
}
