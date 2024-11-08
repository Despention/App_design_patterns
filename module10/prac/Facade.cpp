#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class RoomBookingSystem {
public:
    void BookRoom(const string& guestName) {
        cout << " " << guestName << "." << endl;
    }
    void CheckAvailability() {
        cout << " " << endl;
    }
    void CancelBooking(const string& guestName) {
        cout << " " << guestName << "." << endl;
    }
};

class Notification{
    public:
    void SendNotification(string message){
        cout<<" ";
    }
};

class RestaurantSystem {
public:
    void BookTable(int numberOfGuests) {
        cout << "" << numberOfGuests << " ." << endl;
    }
    void OrderFood(const string& food) {
        cout << ": " << food << endl;
    }
    void NotificationKitchen(){
        cout<<" ";
    }
};

class EventManagementSystem {
public:
    void BookConferenceRoom(int capacity) {
        cout << "" << capacity << " ." << endl;
    }
    void OrderEquipment(const string& equipment) {
        cout << ": " << equipment << endl;
    }
};

class CleaningService {
public:
    void ScheduleCleaning(const string& room) {
        cout << " " << room << "." << endl;
    }
    void PerformCleaning(const string& room) {
        cout << " " << room << "." << endl;
    }
};

class HotelFacade {
    RoomBookingSystem roomBooking;
    RestaurantSystem restaurant;
    EventManagementSystem eventManagement;
    CleaningService cleaning;

public:
    void BookRoomWithServices(const string& guestName) {
        roomBooking.BookRoom(guestName);
        restaurant.BookTable(1);
        cleaning.ScheduleCleaning("Guest Room");
    }

    void OrganizeEvent(const string& eventName) {
        cout << "Organizing event: " << eventName << endl;
        eventManagement.BookConferenceRoom(100);
        eventManagement.OrderEquipment("Projector and Sound System");
        roomBooking.BookRoom("Event Guests");
    }

    void BookRestaurantTableWithTaxi() {
        restaurant.BookTable(4);
        cout << "Taxi ordered for restaurant guests." << endl;
    }

    void CancelRoomBooking(const string& guestName) {
        roomBooking.CancelBooking(guestName);
    }

    void RequestCleaning(const string& room) {
        cleaning.PerformCleaning(room);
    }
};

int main() {
    HotelFacade hotel;

    hotel.BookRoomWithServices("Nail");
    cout << endl;

    hotel.OrganizeEvent("Corporate Meeting");
    cout << endl;

    hotel.BookRestaurantTableWithTaxi();
    cout << endl;

    hotel.CancelRoomBooking("Nail");
    hotel.RequestCleaning("Conference Room");

    return 0;
}
