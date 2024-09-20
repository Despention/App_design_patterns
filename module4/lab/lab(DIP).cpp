#include <iostream>
#include <memory>

using namespace std;

class INotificationService {
public:
    virtual void sendNotification(const string& message) = 0;
};

class EmailService : public INotificationService {
public:
    void sendNotification(const string& message) override {
        cout << "Отправка электронной почты: " << message << endl;
    }
};

class Notification {
public:
    Notification(shared_ptr<INotificationService> service) : service(service) {}

    void send(const string& message) {
        service->sendNotification(message);
    }

private:
    shared_ptr<INotificationService> service;
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    auto emailService = make_shared<EmailService>();
    Notification notification(emailService);

    notification.send("Привет из примера DIP!"); 

    return 0;
}
