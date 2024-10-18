#include <iostream>
#include <string>

using namespace std;

class ReportGenerator {
public:
    void generateReport() {
        prepareData();
        formatData();
        createHeader();
        createBody();
        saveToFile();
        if (customerWantsHook()) {
            customHook();
        }
    }

    virtual void prepareData() = 0;
    virtual void formatData() = 0; 
    virtual void createHeader() = 0;
    virtual void createBody() = 0; 

    void saveToFile() {
        cout << "Saving report to file..." << endl;
    }

    virtual bool customerWantsHook() { return false; }

    virtual void customHook() {}
};

class PdfReport : public ReportGenerator {
public:
    void prepareData() override {
        cout << "Preparing data for PDF report..." << endl;
    }
    void formatData() override {
        cout << "Formatting data as PDF..." << endl;
    }
    void createHeader() override {
        cout << "Creating PDF header..." << endl;
    }
    void createBody() override {
        cout << "Creating PDF body..." << endl;
    }
};

class ExcelReport : public ReportGenerator {
public:
    void prepareData() override {
        cout << "Preparing data for Excel report..." << endl;
    }
    void formatData() override {
        cout << "Formatting data as Excel..." << endl;
    }
    void createHeader() override {
        cout << "Creating Excel header..." << endl;
    }
    void createBody() override {
        cout << "Creating Excel body..." << endl;
    }

    bool customerWantsHook() override {
        return true; 
    }

    void customHook() override {
        cout << "Adding custom steps for Excel report..." << endl;
    }
};

class HtmlReport : public ReportGenerator {
public:
    void prepareData() override {
        cout << "Preparing data for HTML report..." << endl;
    }
    void formatData() override {
        cout << "Formatting data as HTML..." << endl;
    }
    void createHeader() override {
        cout << "Creating HTML header..." << endl;
    }
    void createBody() override {
        cout << "Creating HTML body..." << endl;
    }
};

int main() {
    cout << "Generating PDF report:" << endl;
    PdfReport pdfReport;
    pdfReport.generateReport();

    cout << "\nGenerating Excel report:" << endl;
    ExcelReport excelReport;
    excelReport.generateReport();

    cout << "\nGenerating HTML report:" << endl;
    HtmlReport htmlReport;
    htmlReport.generateReport();

    return 0;
}
