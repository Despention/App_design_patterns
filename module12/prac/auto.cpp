#include <iostream>
#include <string>

using namespace std;

enum OrderState {
    Idle,
    CarSelected,
    OrderConfirmed,
    CarArrived,
    InTrip,
    TripCompleted,
    TripCancelled
};

class CarOrder {
private:
    OrderState state;

public:
    CarOrder() : state(Idle) {}

    void selectCar() {
        if (state == Idle) {
            state = CarSelected;
            cout << "Автомобиль выбран. Ожидание подтверждения заказа." << endl;
        } else {
            cout << "Невозможно выбрать автомобиль на данном этапе." << endl;
        }
    }

    void confirmOrder() {
        if (state == CarSelected) {
            state = OrderConfirmed;
            cout << "Заказ подтвержден. Автомобиль в пути." << endl;
        } else {
            cout << "Невозможно подтвердить заказ на данном этапе." << endl;
        }
    }

    void carArrival() {
        if (state == OrderConfirmed) {
            state = CarArrived;
            cout << "Автомобиль прибыл." << endl;
        } else {
            cout << "Автомобиль не может прибыть на данном этапе." << endl;
        }
    }

    void startTrip() {
        if (state == CarArrived) {
            state = InTrip;
            cout << "Поездка началась." << endl;
        } else {
            cout << "Невозможно начать поездку на данном этапе." << endl;
        }
    }

    void completeTrip() {
        if (state == InTrip) {
            state = TripCompleted;
            cout << "Поездка завершена. Ожидание оплаты." << endl;
        } else {
            cout << "Невозможно завершить поездку на данном этапе." << endl;
        }
    }

    void cancelOrder() {
        if (state != TripCompleted && state != TripCancelled) {
            state = TripCancelled;
            cout << "Заказ отменен." << endl;
        } else {
            cout << "Невозможно отменить заказ на данном этапе." << endl;
        }
    }
};

int main() {
    CarOrder order;
    order.selectCar();
    order.confirmOrder();
    order.carArrival();
    order.startTrip();
    order.completeTrip();
    order.cancelOrder();

    return 0;
}
