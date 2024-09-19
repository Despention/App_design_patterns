#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class User {
 public:
  string name;
  string email;
  string role;
};

class UserManager {
 public:
  void AddUser(const User& user) {
    users.push_back(user);
  }

  void RemoveUser(const string& email) {
    users.erase(
        remove_if(users.begin(), users.end(),
                       [&email](const User& u) { return u.email == email; }),
        users.end());
  }

  void UpdateUser(const User& user) {
    for (auto& u : users) {
      if (u.email == user.email) {
        u = user;
        return;
      }
    }
  }
  
  void PrintUsers() const {
    for (const auto& user : users) {
      cout << "Имя: " << user.name 
                << ", Почта: " << user.email
                << ", Роль: " << user.role << endl;
    }
  }

 private:
  vector<User> users;
};

int main() {
    setlocale(LC_ALL, "Russian");

    UserManager manager;

    manager.AddUser({"Акимов Бахтияр", "akim@gmail.com", "user"});
    manager.AddUser({"Наиль Салманов", "nail@gmail.com", "admin"});

    cout << "Список пользователей:\n";
    manager.PrintUsers();

    manager.UpdateUser({"Акимов Бахтияр", "akim@gmail.com", "admin"});

    manager.RemoveUser("nail@gmail.com");

    cout << "\nОбновленный список пользователей:\n";
    manager.PrintUsers();

  return 0;
}