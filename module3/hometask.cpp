#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void LogMessage(const string& message, const string& level) {
    cout << level << ": " << message << endl;
}

string connectionString = "Server=myServer;Database=myDb;User Id=myUser;Password=myPass;";

class DatabaseService {
public:
    void Connect() {
    }
};

class LoggingService {
public:
    void Log(const string& message) {
    }
};

void ProcessNumbers(const vector<int>& numbers) {
    for (int number : numbers) {
        if (number > 0) {
            cout << number << endl;
        }
    }
}

void PrintPositiveNumbers(const vector<int>& numbers) {
    for (int number : numbers) {
        if (number > 0) {
            cout << number << endl;
        }
    }
}

int Divide(int a, int b) {
    if (b == 0) {
        return 0; 
    }
    return a / b;
}

class User {
public:
    string Name;
    string Email;
};

string ReadFile(const string& filePath) {
    return "file content";
}

class ReportGenerator {
public:
    void GenerateReport(const string& format) { 
        if (format == "pdf") {
        } else if (format == "excel") {

        } 
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    LogMessage("Произошла ошибка!", "ERROR");
    LogMessage("Внимание!", "WARNING");
    LogMessage("Информация.", "INFO");

    DatabaseService dbService;
    dbService.Connect(); 

    vector<int> numbers = {1, -2, 3, 0, 4};
    ProcessNumbers(numbers);

    PrintPositiveNumbers(numbers);

    int result = Divide(10, 2); 
    cout << "Result: " << result << endl;


    return 0;
}