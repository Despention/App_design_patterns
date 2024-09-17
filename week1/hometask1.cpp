#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    int copies;

    Book(string title, string author, int copies) : title(title), author(author), copies(copies) {}
};

class Reader {
public:
    string name;
    int readerId;

    Reader(string name, int readerId) : name(name), readerId(readerId) {}
};

class Library {
private:
    vector<Book> books;
    vector<Reader> readers;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Книга \"" << book.title << "\" добавлена в библиотеку." << endl;
    }

    void removeBook(const string& title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                books.erase(it);
                cout << "Книга \"" << title << "\" удалена из библиотеки." << endl;
                return;
            }
        }
        cout << "Книга \"" << title << "\" не найдена." << endl;
    }

    void registerReader(const Reader& reader) {
        readers.push_back(reader);
        cout << "Читатель \"" << reader.name << "\" зарегистрирован." << endl;
    }

    void issueBook(const string& title, int readerId) {
        for (auto& book : books) {
            if (book.title == title && book.copies > 0) {
                book.copies--;
                cout << "Книга \"" << title << "\" выдана читателю с ID " << readerId << "." << endl;
                return;
            }
        }
        cout << "Книга \"" << title << "\" недоступна." << endl;
    }

    void returnBook(const string& title) {
        for (auto& book : books) {
            if (book.title == title) {
                book.copies++;
                cout << "Книга \"" << title << "\" возвращена." << endl;
                return;
            }
        }
        cout << "Книга \"" << title << "\" не найдена." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    Library library;

    library.addBook(Book("Война и мир", "Л. Толстой", 3));
    library.addBook(Book("Преступление и наказание", "Ф. Достоевский", 2));

    library.registerReader(Reader("Бахтияр", 1));
    library.registerReader(Reader("Наиль", 2));

    library.issueBook("Война и мир", 1);
    library.issueBook("Преступление и наказание", 2);
    library.returnBook("Война и мир");

    library.removeBook("Преступление и наказание");

    return 0;
}