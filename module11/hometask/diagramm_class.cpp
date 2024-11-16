#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(string t, string a, string isbn) 
        : title(t), author(a), ISBN(isbn), isAvailable(true) {}
};

class Reader {
public:
    string name;
    vector<Book*> rentedBooks;

    Reader(string n) : name(n) {}

    void rentBook(Book& book) {
        if (book.isAvailable) {
            rentedBooks.push_back(&book);
            book.isAvailable = false;
            cout << name << " rented " << book.title << "\n";
        } else {
            cout << book.title << " is not available\n";
        }
    }

    void returnBook(Book& book) {
        auto it = find(rentedBooks.begin(), rentedBooks.end(), &book);
        if (it != rentedBooks.end()) {
            rentedBooks.erase(it);
            book.isAvailable = true;
            cout << name << " returned " << book.title << "\n";
        }
    }
};

class Librarian {
public:
    string name;

    Librarian(string n) : name(n) {}

    void manageBooks(vector<Book>& books) {
        cout << name << " manages the library books.\n";
    }
};

class Library {
public:
    vector<Book> books;

    void addBook(const Book& book) {
        books.push_back(book);
    }

    void displayBooks() {
        cout << "Library Books:\n";
        for (const auto& book : books) {
            cout << "- " << book.title << " by " << book.author
                 << " (" << (book.isAvailable ? "Available" : "Rented") << ")\n";
        }
    }
};

int main() {
    Library library;
    library.addBook({"1984", "George Orwell", "123456789"});
    library.addBook({"The Catcher in the Rye", "J.D. Salinger", "987654321"});

    Reader reader("Alice");
    Librarian librarian("Mr. Smith");

    library.displayBooks();

    reader.rentBook(library.books[0]);
    library.displayBooks();

    reader.returnBook(library.books[0]);
    library.displayBooks();

    return 0;
}
