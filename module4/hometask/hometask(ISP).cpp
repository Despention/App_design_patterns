#include <iostream>
#include <string>

using namespace std;

class IPrinter {
public:
    virtual void print(const string& content) = 0;
};

class IScanner {
public:
    virtual void scan(const string& content) = 0;
};

class IFax {
public:
    virtual void fax(const string& content) = 0;
};

class BasicPrinter : public IPrinter {
public:
    void print(const string& content) override {
        cout << "Печать: " << content << endl;
    }
};

class AllInOnePrinter : public IPrinter, public IScanner, public IFax {
public:
    void print(const string& content) override {
        cout << "Печать: " << content << endl;
    }
    void scan(const string& content) override {
        cout << "Сканирование: " << content << endl;
    }
    void fax(const string& content) override {
        cout << "Отправка факса: " << content << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    BasicPrinter basicPrinter;
    AllInOnePrinter allInOnePrinter;

    basicPrinter.print("Привет от базового принтера!");
    allInOnePrinter.print("Привет от принтера все в одном!");
    allInOnePrinter.scan("Сканирование документа...");
    allInOnePrinter.fax("Отчет о факсимильной связи...");

    return 0;
}