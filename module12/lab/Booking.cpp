#include <iostream>
#include <string>

using namespace std;

class Booking {
public:
    enum State { Idle, RoomSelected, BookingConfirmed, Paid, BookingCancelled };

    Booking() : state(Idle) {}

    void selectRoom() {
        if (state == Idle) {
            state = RoomSelected;
            cout << "State changed to: RoomSelected\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

    void confirmBooking() {
        if (state == RoomSelected) {
            state = BookingConfirmed;
            cout << "State changed to: BookingConfirmed\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

    void pay() {
        if (state == BookingConfirmed) {
            state = Paid;
            cout << "State changed to: Paid\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

    void cancel() {
        if (state == RoomSelected || state == BookingConfirmed) {
            state = BookingCancelled;
            cout << "State changed to: BookingCancelled\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

private:
    State state;
};
