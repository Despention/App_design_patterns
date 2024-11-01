#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Интерфейс для отчетов
class IReport {
public:
    virtual ~IReport() = default;
    virtual string Generate() const = 0;
};

// Классы отчетов
class SalesReport : public IReport {
public:
    string Generate() const override {
        return "Sales Report Data";
    }
};

class UserReport : public IReport {
public:
    string Generate() const override {
        return "User Report Data";
    }
};

class ReportDecorator : public IReport {
protected:
    shared_ptr<IReport> report;
public:
    explicit ReportDecorator(shared_ptr<IReport> r) : report(r) {}
};

class DateFilterDecorator : public ReportDecorator {
public:
    explicit DateFilterDecorator(shared_ptr<IReport> r) : ReportDecorator(r) {}

    string Generate() const override {
        return report->Generate() + " | Filtered by Date";
    }
};

class SortingDecorator : public ReportDecorator {
public:
    explicit SortingDecorator(shared_ptr<IReport> r) : ReportDecorator(r) {}

    string Generate() const override {
        return report->Generate() + " | Sorted by Criteria";
    }
};

class CsvExportDecorator : public ReportDecorator {
public:
    explicit CsvExportDecorator(shared_ptr<IReport> r) : ReportDecorator(r) {}

    string Generate() const override {
        return report->Generate() + " | Exported to CSV";
    }
};

class PdfExportDecorator : public ReportDecorator {
public:
    explicit PdfExportDecorator(shared_ptr<IReport> r) : ReportDecorator(r) {}

    string Generate() const override {
        return report->Generate() + " | Exported to PDF";
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    
    shared_ptr<IReport> report = make_shared<SalesReport>();
    report = make_shared<DateFilterDecorator>(report);
    report = make_shared<SortingDecorator>(report);
    report = make_shared<PdfExportDecorator>(report);

    cout << report->Generate() << endl;

    return 0;
}
