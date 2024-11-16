#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(string t, string a, string i)
        : title(t), author(a), isbn(i), isAvailable(true) {}

    void markAsLoaned() {
        if (!isAvailable) {
            throw runtime_error("Book is already loaned.");
        }
        isAvailable = false;
    }

    void markAsAvailable() {
        isAvailable = true;
    }

    void displayInfo() const {
        cout << "Title: " << title
             << ", Author: " << author
             << ", ISBN: " << isbn
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class User {
protected:
    int id;
    string name;

public:
    User(int userId, const string& userName) : id(userId), name(userName) {}
    virtual ~User() = default;

    virtual void displayInfo() const {
        cout << "User ID: " << id << ", Name: " << name << endl;
    }

    string getName() const {
        return name;
    }
};

class Reader : public User {
private:
    vector<Book*> borrowedBooks;

public:
    Reader(int userId, const string& userName) : User(userId, userName) {}

    void borrowBook(Book& book) {
        if (!book.isAvailable) {
            throw runtime_error("Book is not available.");
        }
        borrowedBooks.push_back(&book);
        book.markAsLoaned();
        cout << name << " borrowed \"" << book.title << "\"" << endl;
    }

    void returnBook(Book& book) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), &book);
        if (it == borrowedBooks.end()) {
            throw runtime_error("Book not found in borrowed list.");
        }
        borrowedBooks.erase(it);
        book.markAsAvailable();
        cout << name << " returned \"" << book.title << "\"" << endl;
    }

    void displayBorrowedBooks() const {
        cout << name << " has borrowed the following books:" << endl;
        for (const auto& book : borrowedBooks) {
            cout << "- " << book->title << endl;
        }
    }
};

class Librarian : public User {
public:
    Librarian(int userId, const string& userName) : User(userId, userName) {}

    void addBook(vector<Book>& catalog, const Book& book) {
        catalog.push_back(book);
        cout << "Book \"" << book.title << "\" added to the library by " << name << endl;
    }

    void removeBook(vector<Book>& catalog, const string& isbn) {
        auto it = remove_if(catalog.begin(), catalog.end(),
                            [&isbn](const Book& book) { return book.isbn == isbn; });
        if (it != catalog.end()) {
            catalog.erase(it, catalog.end());
            cout << "Book with ISBN \"" << isbn << "\" removed by " << name << endl;
        } else {
            throw runtime_error("Book with the given ISBN not found.");
        }
    }
};

class Loan {
public:
    Book* book;
    Reader* reader;
    string loanDate;
    string returnDate;

    Loan(Book* b, Reader* r, const string& ld, const string& rd)
        : book(b), reader(r), loanDate(ld), returnDate(rd) {}

    void issueLoan() {
        book->markAsLoaned();
        cout << "Loan issued: \"" << book->title << "\" to " << reader->getName()
             << " on " << loanDate << endl;
    }

    void completeLoan() {
        book->markAsAvailable();
        cout << "Loan completed: \"" << book->title << "\" returned by " << reader->getName()
             << " on " << returnDate << endl;
    }
};

class Library {
public:
    vector<Book> catalog;

    void searchBookByTitle(const string& title) const {
        auto it = find_if(catalog.begin(), catalog.end(),
                          [&title](const Book& book) { return book.title == title; });
        if (it != catalog.end()) {
            it->displayInfo();
        } else {
            cout << "Book with title \"" << title << "\" not found." << endl;
        }
    }

    void displayCatalog() const {
        cout << "Library Catalog:" << endl;
        for (const auto& book : catalog) {
            book.displayInfo();
        }
    }
};

int main() {
    try {
        Library library;
        library.catalog.push_back(Book("1984", "George Orwell", "12345"));
        library.catalog.push_back(Book("To Kill a Mockingbird", "Harper Lee", "67890"));

        Librarian librarian(1, "John Smith");
        Reader reader(2, "Alice Johnson");

        librarian.addBook(library.catalog, Book("Brave New World", "Aldous Huxley", "11223"));
        library.displayCatalog();

        reader.borrowBook(library.catalog[0]);
        reader.displayBorrowedBooks();

        reader.returnBook(library.catalog[0]);
        library.displayCatalog();

        Loan loan(&library.catalog[1], &reader, "2024-11-16", "2024-11-30");
        loan.issueLoan();
        loan.completeLoan();

        library.searchBookByTitle("1984");
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
