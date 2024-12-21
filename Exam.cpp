#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class AdCampaign {
public:
    string companyName;
    string audience;
    int budget;
    string schedule;
    vector<string> channels;
    string targetingOptions;
    vector<string> metrics;

    void Show() const {
        cout << "Рекламная кампания: " << companyName << endl;
        cout << "Целевая аудитория: " << audience << endl;
        cout << "Бюджет: " << budget << " тенге" << endl;
        cout << "Расписание: " << schedule << endl;
        cout << "Каналы распространения: ";
        for (const auto& channel : channels) {
            cout << channel << " ";
        }
        cout << endl;
        cout << "Параметры таргетинга: " << targetingOptions << endl;
        cout << "Метрики: ";
        for (const auto& metric : metrics) {
            cout << metric << " ";
        }
        cout << endl << endl;
    }
};


class CampaignBuilder {
public:
    virtual ~CampaignBuilder() = default;
    virtual void SetCompanyName(const string& companyName) = 0;
    virtual void SetAudience(const string& audience) = 0;
    virtual void SetBudget(int budget) = 0;
    virtual void AddChannel(const string& channel) = 0;
    virtual void SetSchedule(const string& schedule) = 0;
    virtual void SetTargetingOptions(const string& options) = 0;
    virtual void DefineMetrics(const vector<string>& metrics) = 0;
    virtual shared_ptr<AdCampaign> GetResult() = 0;
};


class UniversalCampaignBuilder : public CampaignBuilder {
private:
    shared_ptr<AdCampaign> campaign;

public:
    UniversalCampaignBuilder() {
        Reset();
    }

    void Reset() {
        campaign = make_shared<AdCampaign>();
    }

    void SetCompanyName(const string& companyName) override {
        campaign->companyName = companyName;
    }

    void SetAudience(const string& audience) override {
        campaign->audience = audience;
    }

    void SetBudget(int budget) override {
        campaign->budget = budget;
    }

    void AddChannel(const string& channel) override {
        campaign->channels.push_back(channel);
    }

    void SetSchedule(const string& schedule) override {
        campaign->schedule = schedule;
    }

    void SetTargetingOptions(const string& options) override {
        campaign->targetingOptions = options;
    }

    void DefineMetrics(const vector<string>& metrics) override {
        campaign->metrics = metrics;
    }

    shared_ptr<AdCampaign> GetResult() override {
        return campaign;
    }
};


class CampaignDirector {
public:
    void ConstructDefaultCampaign(CampaignBuilder& builder) {
        builder.SetCompanyName("OLX");
        builder.SetAudience("18-50 лет, Казахстан");
        builder.SetBudget(1000000);
        builder.AddChannel("Instagram и");
        builder.AddChannel("TikTok");
        builder.SetSchedule("01.01.2024 - 31.01.2024");
        builder.SetTargetingOptions("Интересы: товары и услуги, скидки");
        builder.DefineMetrics({"Клики и", "Конверсии"});
    }
};


int main() {
    UniversalCampaignBuilder builder;
    CampaignDirector director;

    director.ConstructDefaultCampaign(builder);
    auto campaign = builder.GetResult();


    campaign->Show();

    builder.Reset();
    builder.SetCompanyName("URBO Coffee");
    builder.SetAudience("20-35 лет, Алматы");
    builder.SetBudget(500000);
    builder.AddChannel("Instagram и");
    builder.AddChannel("TikTok");
    builder.SetSchedule("01.02.2024 - 15.02.2024");
    builder.SetTargetingOptions("Интересы: кофе, заведения, скидки");
    builder.DefineMetrics({"Просмотры и", "взаимодействия."});

    auto customCampaign = builder.GetResult();
    customCampaign->Show();

    return 0;
}
