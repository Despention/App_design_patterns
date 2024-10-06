#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <string>

using namespace std;

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
private:
    static unique_ptr<Logger> instance;
    static mutex mtx;
    ofstream logFile;
    LogLevel logLevel;

    Logger() : logLevel(LogLevel::INFO) {
        logFile.open("log.txt", ios_base::app);
    }

public:
    static Logger& GetInstance() {
        lock_guard<mutex> lock(mtx);
        if (!instance) {
            instance.reset(new Logger());
        }
        return *instance;
    }

    void SetLogLevel(LogLevel level) {
        logLevel = level;
    }

    void Log(const string& message, LogLevel level) {
        if (level >= logLevel) {
            logFile << message << endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

unique_ptr<Logger> Logger::instance = nullptr;
mutex Logger::mtx;

int main() {
    Logger& logger = Logger::GetInstance();
    logger.SetLogLevel(LogLevel::WARNING);
    logger.Log("This is an info message", LogLevel::INFO);
    logger.Log("This is a warning message", LogLevel::WARNING);
    logger.Log("This is an error message", LogLevel::ERROR);

    return 0;
}
