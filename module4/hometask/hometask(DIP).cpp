#include <iostream>
#include <string>
#include <memory>

using namespace std;

class INotificationSender {
public:
    virtual void send(const string& message) = 0;
};

class EmailSender : public INotificationSender {
public:
    void send(const string& message) override {
        cout << "Электронная почта отправлена: " << message << endl;
    }
};

class SmsSender : public INotificationSender {
public:
    void send(const string& message) override {
        cout << "Отправленное SMS: " << message << endl;
    }
};

class NotificationService {
public:
    NotificationService(shared_ptr<INotificationSender> sender) : sender(sender) {}

    void sendNotification(const string& message) {
        sender->send(message);
    }

private:
    shared_ptr<INotificationSender> sender;
};

int main() {
    setlocale(LC_ALL, "Russian");

    auto emailSender = make_shared<EmailSender>();
    auto smsSender = make_shared<SmsSender>();

    NotificationService emailNotifier(emailSender);
    NotificationService smsNotifier(smsSender);

    emailNotifier.sendNotification("Получен новый заказ!");
    smsNotifier.sendNotification("Ваш заказ отправлен!");

    return 0;
}