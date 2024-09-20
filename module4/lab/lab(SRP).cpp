#include <iostream>
#include <vector>

using namespace std;

class Item {
public:
    string name;
    double price;

    Item(const string& name, double price) : name(name), price(price) {}
};

class Invoice {
public:
    int id;
    vector<Item> items;
    double taxRate;

    Invoice(int id, const vector<Item>& items, double taxRate)
        : id(id), items(items), taxRate(taxRate) {}
};

class InvoiceCalculator {
public:
    double calculateTotal(const Invoice& invoice) {
        double subTotal = 0;
        for (const auto& item : invoice.items) {
            subTotal += item.price;
        }
        return subTotal + (subTotal * invoice.taxRate);
    }
};

class InvoiceRepository {
public:
    void saveToDatabase(const Invoice& invoice) {
        cout << "Счет-фактура #" << invoice.id << " сохранено в базе данных." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    vector<Item> items = {Item("1", 10.0), Item(" 2", 25.5)};
    Invoice invoice(1, items, 0.05);

    InvoiceCalculator calculator;
    double total = calculator.calculateTotal(invoice);

    InvoiceRepository repository;
    repository.saveToDatabase(invoice);

    cout << "Итого по счету-фактуре: " << total << endl;

    return 0;
}
