#include <iostream>
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
        cout << "Свет включен" << endl;
    }
    void off() {
        cout << "Свет выключен" << endl;
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

class RemoteControl {
    shared_ptr<ICommand> onCommand;
    shared_ptr<ICommand> offCommand;
    shared_ptr<ICommand> lastCommand;
public:
    void setCommands(shared_ptr<ICommand> on, shared_ptr<ICommand> off) {
        onCommand = on;
        offCommand = off;
    }

    void pressOnButton() {
        onCommand->execute();
        lastCommand = onCommand;
    }

    void pressOffButton() {
        offCommand->execute();
        lastCommand = offCommand;
    }

    void pressUndoButton() {
        if (lastCommand) {
            lastCommand->undo();
        }
    }
};

int main() {
    Light livingRoomLight;

    auto lightOn = make_shared<LightOnCommand>(livingRoomLight);
    auto lightOff = make_shared<LightOffCommand>(livingRoomLight);

    RemoteControl remote;
    remote.setCommands(lightOn, lightOff);

    remote.pressOnButton();    
    remote.pressOffButton();  
    remote.pressUndoButton();  

    return 0;
}
