#include <iostream>
#include <string>

using namespace std;

class IReportBuilder {
public:
    virtual void SetHeader(const string& header) = 0;
    virtual void SetContent(const string& content) = 0;
    virtual void SetFooter(const string& footer) = 0;
    virtual string GetReport() const = 0;
};

class TextReportBuilder : public IReportBuilder {
private:
    string report;
public:
    void SetHeader(const string& header) override {
        report += "Header: " + header + "\n";
    }
    
    void SetContent(const string& content) override {
        report += "Content: " + content + "\n";
    }
    
    void SetFooter(const string& footer) override {
        report += "Footer: " + footer + "\n";
    }
    
    string GetReport() const override {
        return report;
    }
};

class ReportDirector {
public:
    void ConstructReport(IReportBuilder& builder) {
        builder.SetHeader("Annual Report 2024");
        builder.SetContent("This is the content of the report.");
        builder.SetFooter("Confidential");
    }
};

int main() {
    TextReportBuilder builder;
    ReportDirector director;
    director.ConstructReport(builder);

    string report = builder.GetReport();
    cout << report << endl;

    return 0;
}
