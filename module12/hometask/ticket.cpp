#include <iostream>
#include <string>

using namespace std;

enum MachineState {
    Idle,
    WaitingForMoney,
    MoneyReceived,
    TicketDispensed,
    TransactionCanceled
};

class TicketMachine {
private:
    MachineState state;

public:
    TicketMachine() : state(Idle) {
        cout << "Автомат готов к работе." << endl;
    }

    void selectTicket() {
        if (state == Idle) {
            state = WaitingForMoney;
            cout << "Билет выбран. Пожалуйста, внесите деньги." << endl;
        } else {
            cout << "Выбор билета невозможен на данном этапе." << endl;
        }
    }

    void insertMoney() {
        if (state == WaitingForMoney) {
            state = MoneyReceived;
            cout << "Деньги внесены. Выдача билета..." << endl;
        } else {
            cout << "Внесение денег невозможно на данном этапе." << endl;
        }
    }

    void dispenseTicket() {
        if (state == MoneyReceived) {
            state = TicketDispensed;
            cout << "Билет выдан. Спасибо за покупку!" << endl;
            reset();
        } else {
            cout << "Выдача билета невозможна на данном этапе." << endl;
        }
    }

    void cancelTransaction() {
        if (state == WaitingForMoney || state == MoneyReceived) {
            state = TransactionCanceled;
            cout << "Транзакция отменена. Возврат в исходное состояние." << endl;
            reset();
        } else {
            cout << "Отмена невозможна на данном этапе." << endl;
        }
    }

    void reset() {
        state = Idle;
        cout << "Автомат готов к следующей операции." << endl;
    }
};

int main() {
    TicketMachine machine;

    machine.selectTicket();
    machine.insertMoney();
    machine.dispenseTicket();

    machine.selectTicket();
    machine.cancelTransaction();

    return 0;
}
