#include <iostream>
#include <string>

using namespace std;

class TicketRequest {
public:
    enum State { Created, WaitingForPayment, Paid, Confirmed, Cancelled };

    TicketRequest() : state(Created) {}

    void sendForPayment() {
        if (state == Created) {
            state = WaitingForPayment;
            cout << "State changed to: WaitingForPayment\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

    void pay() {
        if (state == WaitingForPayment) {
            state = Paid;
            cout << "State changed to: Paid\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

    void confirm() {
        if (state == Paid) {
            state = Confirmed;
            cout << "State changed to: Confirmed\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

    void cancel() {
        if (state == Created || state == WaitingForPayment) {
            state = Cancelled;
            cout << "State changed to: Cancelled\n";
        } else {
            cout << "Invalid action in current state.\n";
        }
    }

private:
    State state;
};
