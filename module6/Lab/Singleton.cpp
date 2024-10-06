#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <string>
#include <thread>

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
            lock_guard<mutex> lock(mtx);
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

void LogMessages() {
    Logger& logger = Logger::GetInstance();
    logger.Log("Thread is running", LogLevel::INFO);
}

int main() {
    Logger& logger = Logger::GetInstance();
    logger.SetLogLevel(LogLevel::INFO);

    thread t1(LogMessages);
    thread t2(LogMessages);

    t1.join();
    t2.join();

    return 0;
}
