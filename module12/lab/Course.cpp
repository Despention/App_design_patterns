#include <iostream>
#include <vector>
#include <string>

using namespace std;

class User {
public:
    virtual void performAction() const = 0;
    virtual ~User() = default;
};

class Student : public User {
public:
    void performAction() const override {
        cout << "Student Actions: Register, View Courses, Enroll, Take Tests, Leave Reviews.\n";
    }
};

class Teacher : public User {
public:
    void performAction() const override {
        cout << "Teacher Actions: Create/Edit Courses, Add Materials, Create Tests, View Stats, Moderate Reviews.\n";
    }
};

class Admin : public User {
public:
    void performAction() const override {
        cout << "Admin Actions: Manage Accounts, Manage Categories, View Analytics.\n";
    }
};

int main() {
    vector<User*> users;
    users.push_back(new Student());
    users.push_back(new Teacher());
    users.push_back(new Admin());

    for (const auto& user : users) {
        user->performAction();
    }

    for (auto& user : users) {
        delete user;
    }

    return 0;
}
