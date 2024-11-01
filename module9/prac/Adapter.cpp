#include <iostream>
#include <string>
#include <memory>

using namespace std;

class IInternalDeliveryService {
public:
    virtual ~IInternalDeliveryService() = default;
    virtual void DeliverOrder(const string& orderId) = 0;
    virtual string GetDeliveryStatus(const string& orderId) const = 0;
};

class InternalDeliveryService : public IInternalDeliveryService {
public:
    void DeliverOrder(const string& orderId) override {
        cout << "Internal delivery for order " << orderId << endl;
    }

    string GetDeliveryStatus(const string& orderId) const override {
        return "Internal delivery status for order " + orderId;
    }
};

class ExternalLogisticsServiceA {
public:
    void ShipItem(int itemId) {
        cout << "Shipping item with ID " << itemId << " via Service A" << endl;
    }

    string TrackShipment(int shipmentId) const {
        return "Tracking Service A shipment " + to_string(shipmentId);
    }
};

class ExternalLogisticsServiceB {
public:
    void SendPackage(const string& packageInfo) {
        cout << "Sending package: " << packageInfo << " via Service B" << endl;
    }

    string CheckPackageStatus(const string& trackingCode) const {
        return "Status for package with tracking code " + trackingCode;
    }
};

class LogisticsAdapterA : public IInternalDeliveryService {
private:
    ExternalLogisticsServiceA serviceA;
public:
    void DeliverOrder(const string& orderId) override {
        int itemId = stoi(orderId);
        serviceA.ShipItem(itemId);
    }

    string GetDeliveryStatus(const string& orderId) const override {
        int shipmentId = stoi(orderId);
        return serviceA.TrackShipment(shipmentId);
    }
};

class LogisticsAdapterB : public IInternalDeliveryService {
private:
    ExternalLogisticsServiceB serviceB;
public:
    void DeliverOrder(const string& orderId) override {
        serviceB.SendPackage(orderId);
    }

    string GetDeliveryStatus(const string& orderId) const override {
        return serviceB.CheckPackageStatus(orderId);
    }
};

class DeliveryServiceFactory {
public:
    static shared_ptr<IInternalDeliveryService> CreateDeliveryService(const string& type) {
        if (type == "internal") {
            return make_shared<InternalDeliveryService>();
        } else if (type == "A") {
            return make_shared<LogisticsAdapterA>();
        } else if (type == "B") {
            return make_shared<LogisticsAdapterB>();
        }
        return nullptr;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    shared_ptr<IInternalDeliveryService> deliveryService;

    deliveryService = DeliveryServiceFactory::CreateDeliveryService("A");
    deliveryService->DeliverOrder("123");
    cout << deliveryService->GetDeliveryStatus("123") << endl;

    return 0;
}
