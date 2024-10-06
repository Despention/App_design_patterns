#include <iostream>
#include <string>
#include <map>
#include <mutex>
#include <memory>
#include <fstream>

using namespace std;

class ConfigurationManager {
private:
    static unique_ptr<ConfigurationManager> instance;
    static mutex mtx;
    map<string, string> settings;
    
    ConfigurationManager() {}

public:
    static ConfigurationManager& GetInstance() {
        lock_guard<mutex> lock(mtx);
        if (!instance) {
            instance.reset(new ConfigurationManager());
        }
        return *instance;
    }

    void LoadSettings(const string& filename) {
        ifstream file(filename);
        string key, value;
        while (file >> key >> value) {
            settings[key] = value;
        }
        file.close();
    }

    string GetSetting(const string& key) {
        return settings[key];
    }

    void SetSetting(const string& key, const string& value) {
        settings[key] = value;
    }

    void SaveSettings(const string& filename) {
        ofstream file(filename);
        for (const auto& setting : settings) {
            file << setting.first << " " << setting.second << endl;
        }
        file.close();
    }
};

unique_ptr<ConfigurationManager> ConfigurationManager::instance = nullptr;
mutex ConfigurationManager::mtx;

int main() {
    ConfigurationManager& config = ConfigurationManager::GetInstance();
    config.LoadSettings("config.txt");
    cout << "Initial setting: " << config.GetSetting("language") << endl;

    config.SetSetting("theme", "dark");
    config.SaveSettings("config.txt");

    return 0;
}
