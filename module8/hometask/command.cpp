#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
public:
    void on() {
        cout << "Light is ON" << endl;
    }
    void off() {
        cout << "Light is OFF" << endl;
    }
};

class Door {
public:
    void open() {
        cout << "Door is OPEN" << endl;
    }
    void close() {
        cout << "Door is CLOSED" << endl;
    }
};

class Thermostat {
public:
    void increaseTemperature() {
        cout << "Temperature is INCREASED" << endl;
    }
    void decreaseTemperature() {
        cout << "Temperature is DECREASED" << endl;
    }
};

class LightOnCommand : public ICommand {
    Light& light;
public:
    LightOnCommand(Light& l) : light(l) {}
    void execute() override {
        light.on();
    }
    void undo() override {
        light.off();
    }
};

class LightOffCommand : public ICommand {
    Light& light;
public:
    LightOffCommand(Light& l) : light(l) {}
    void execute() override {
        light.off();
    }
    void undo() override {
        light.on();
    }
};

class DoorOpenCommand : public ICommand {
    Door& door;
public:
    DoorOpenCommand(Door& d) : door(d) {}
    void execute() override {
        door.open();
    }
    void undo() override {
        door.close();
    }
};

class DoorCloseCommand : public ICommand {
    Door& door;
public:
    DoorCloseCommand(Door& d) : door(d) {}
    void execute() override {
        door.close();
    }
    void undo() override {
        door.open();
    }
};

class ThermostatIncreaseCommand : public ICommand {
    Thermostat& thermostat;
public:
    ThermostatIncreaseCommand(Thermostat& t) : thermostat(t) {}
    void execute() override {
        thermostat.increaseTemperature();
    }
    void undo() override {
        thermostat.decreaseTemperature();
    }
};

class RemoteControl {
    vector<shared_ptr<ICommand>> history;
    shared_ptr<ICommand> lastCommand;
public:
    void setCommand(shared_ptr<ICommand> command) {
        command->execute();
        lastCommand = command;
        history.push_back(command);
    }

    void undoLastCommand() {
        if (lastCommand) {
            lastCommand->undo();
        }
    }
};

int main() {
    Light livingRoomLight;
    Door frontDoor;
    Thermostat houseThermostat;

    shared_ptr<ICommand> lightOn = make_shared<LightOnCommand>(livingRoomLight);
    shared_ptr<ICommand> lightOff = make_shared<LightOffCommand>(livingRoomLight);
    shared_ptr<ICommand> doorOpen = make_shared<DoorOpenCommand>(frontDoor);
    shared_ptr<ICommand> doorClose = make_shared<DoorCloseCommand>(frontDoor);
    shared_ptr<ICommand> increaseTemp = make_shared<ThermostatIncreaseCommand>(houseThermostat);

    RemoteControl remote;
    remote.setCommand(lightOn);   
    remote.setCommand(doorOpen);  
    remote.setCommand(increaseTemp); 

    remote.undoLastCommand();     
    return 0;
}
