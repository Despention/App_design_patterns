#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Hotel {
public:
    string name;
    string location;
    unordered_map<string, bool> rooms; // Room number and availability

    Hotel(string n, string loc) : name(n), location(loc) {}

    void addRoom(string roomNumber) {
        rooms[roomNumber] = true;
    }

    bool isRoomAvailable(string roomNumber) {
        return rooms.count(roomNumber) && rooms[roomNumber];
    }

    void bookRoom(string roomNumber) {
        if (isRoomAvailable(roomNumber)) {
            rooms[roomNumber] = false;
            cout << "Room " << roomNumber << " in " << name << " is booked.\n";
        } else {
            cout << "Room " << roomNumber << " is not available.\n";
        }
    }

    void releaseRoom(string roomNumber) {
        if (rooms.count(roomNumber)) {
            rooms[roomNumber] = true;
            cout << "Room " << roomNumber << " in " << name << " is now available.\n";
        }
    }
};

class BookingService {
public:
    void bookRoom(Hotel& hotel, string roomNumber) {
        hotel.bookRoom(roomNumber);
    }

    void releaseRoom(Hotel& hotel, string roomNumber) {
        hotel.releaseRoom(roomNumber);
    }
};

class PaymentService {
public:
    void processPayment(string user, double amount) {
        cout << "Payment of $" << amount << " processed for " << user << ".\n";
    }
};

class NotificationService {
public:
    void sendNotification(string user, string message) {
        cout << "Notification to " << user << ": " << message << "\n";
    }
};

class UserManagementService {
public:
    vector<string> users;

    void registerUser(string user) {
        users.push_back(user);
        cout << user << " registered successfully.\n";
    }

    bool isUserRegistered(string user) {
        return find(users.begin(), users.end(), user) != users.end();
    }
};

class UIComponent {
public:
    void interact() {
        UserManagementService userManager;
        BookingService bookingService;
        PaymentService paymentService;
        NotificationService notificationService;

        Hotel hotel("Grand Hotel", "New York");
        hotel.addRoom("101");
        hotel.addRoom("102");

        string user = "Alice";
        userManager.registerUser(user);

        if (userManager.isUserRegistered(user)) {
            bookingService.bookRoom(hotel, "101");
            paymentService.processPayment(user, 200.0);
            notificationService.sendNotification(user, "Your room is booked!");
        }

        hotel.bookRoom("102"); // Another booking example
        hotel.releaseRoom("101");
    }
};

int main() {
    UIComponent ui;
    ui.interact();
    return 0;
}