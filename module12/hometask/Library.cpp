#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    string genre;

    Book(int id, string title, string author, string genre)
        : id(id), title(title), author(author), genre(genre) {}
};

class User {
public:
    int id;
    string name;
    string role; 
    User(int id, string name, string role) : id(id), name(name), role(role) {}

    virtual void viewBooks(const vector<Book>& books) {
        cout << "Доступные книги:" << endl;
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Название: " << book.title << ", Автор: " << book.author
                 << ", Жанр: " << book.genre << endl;
        }
    }
};

class Reader : public User {
public:
    Reader(int id, string name) : User(id, name, "Reader") {}

    void searchBook(const vector<Book>& books, const string& query) {
        cout << "Результаты поиска для: " << query << endl;
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos) {
                cout << "ID: " << book.id << ", Название: " << book.title << ", Автор: " << book.author
                     << ", Жанр: " << book.genre << endl;
            }
        }
    }
};

class Librarian : public User {
public:
    Librarian(int id, string name) : User(id, name, "Librarian") {}

    void addBook(vector<Book>& books, const Book& book) {
        books.push_back(book);
        cout << "Книга добавлена: " << book.title << endl;
    }

    void removeBook(vector<Book>& books, int bookId) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == bookId) {
                cout << "Книга удалена: " << it->title << endl;
                books.erase(it);
                return;
            }
        }
        cout << "Книга с ID " << bookId << " не найдена." << endl;
    }
};

class Administrator : public Librarian {
public:
    Administrator(int id, string name) : Librarian(id, name) {
        role = "Administrator";
    }

    void manageUsers(vector<User*>& users, User* user, const string& action) {
        if (action == "add") {
            users.push_back(user);
            cout << "Пользователь добавлен: " << user->name << endl;
        } else if (action == "remove") {
            for (auto it = users.begin(); it != users.end(); ++it) {
                if (*it == user) {
                    cout << "Пользователь удален: " << user->name << endl;
                    users.erase(it);
                    return;
                }
            }
            cout << "Пользователь не найден." << endl;
        }
    }
};

int main() {
    vector<Book> books = {
        {1, "Гарри Поттер", "Дж. К. Роулинг", "Фэнтези"},
        {2, "Властелин колец", "Дж. Р. Р. Толкин", "Фэнтези"}
    };

    vector<User*> users;

    Reader reader(1, "Иван");
    Librarian librarian(2, "Мария");
    Administrator admin(3, "Алексей");

    users.push_back(&reader);
    users.push_back(&librarian);
    users.push_back(&admin);

    reader.viewBooks(books);
    reader.searchBook(books, "Гарри");

    librarian.addBook(books, {3, "1984", "Джордж Оруэлл", "Антиутопия"});
    librarian.removeBook(books, 1);

    admin.manageUsers(users, new Reader(4, "Ольга"), "add");

    return 0;
}
