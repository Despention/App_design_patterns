#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Event {
public:
    int id;
    string name;
    string date;
    string location;

    Event(int id, string name, string date, string location)
        : id(id), name(name), date(date), location(location) {}
};

class User {
public:
    int id;
    string name;
    string role; 

    User(int id, string name, string role) : id(id), name(name), role(role) {}
};

class Booking {
public:
    int id;
    User user;
    Event event;
    string status; 

    Booking(int id, User user, Event event, string status)
        : id(id), user(user), event(event), status(status) {}
};

class System {
private:
    vector<Event> events;
    vector<Booking> bookings;

public:
    void addEvent(Event e) {
        events.push_back(e);
        cout << "Мероприятие добавлено: " << e.name << endl;
    }

    void listEvents() {
        cout << "Доступные мероприятия:" << endl;
        for (auto &e : events) {
            cout << "ID: " << e.id << ", Название: " << e.name << ", Дата: " << e.date
                 << ", Место: " << e.location << endl;
        }
    }

    void bookEvent(User u, int eventId) {
        for (auto &e : events) {
            if (e.id == eventId) {
                bookings.push_back(Booking(bookings.size() + 1, u, e, "Booked"));
                cout << "Мероприятие забронировано: " << e.name << " для пользователя " << u.name << endl;
                return;
            }
        }
        cout << "Мероприятие с ID " << eventId << " не найдено." << endl;
    }

    void cancelBooking(int bookingId) {
        for (auto &b : bookings) {
            if (b.id == bookingId) {
                b.status = "Cancelled";
                cout << "Бронирование отменено: " << b.event.name << endl;
                return;
            }
        }
        cout << "Бронирование с ID " << bookingId << " не найдено." << endl;
    }
};

int main() {
    System system;
    User user1(1, "Иван", "User");
    Event event1(1, "Концерт", "2024-12-01", "Москва");
    Event event2(2, "Конференция", "2024-12-05", "Санкт-Петербург");

    system.addEvent(event1);
    system.addEvent(event2);

    system.listEvents();
    system.bookEvent(user1, 1);
    system.cancelBooking(1);

    return 0;
}
