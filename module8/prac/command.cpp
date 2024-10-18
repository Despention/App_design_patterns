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
       cout << "Light is ON" <<endl;
    }
    void off() {
       cout << "Light is OFF" <<endl;
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
   vector<std::shared_ptr<ICommand>> history;
   shared_ptr<ICommand> lastCommand;
public:
    void setCommand(std::shared_ptr<ICommand> command) {
        command->execute();
        lastCommand = command;
        history.push_back(command);
    }

    void undoLastCommand() {
        if (lastCommand) {
            lastCommand->undo();
        }
    }

    void showHistory() {
       cout << "Command history:" <<endl;
        for (const auto& cmd : history) {
           cout << "- Executed command" <<endl;
        }
    }
};

int main() {
    Light livingRoomLight;

   shared_ptr<ICommand> lightOn =make_shared<LightOnCommand>(livingRoomLight);
   shared_ptr<ICommand> lightOff =make_shared<LightOffCommand>(livingRoomLight);

    RemoteControl remote;
    remote.setCommand(lightOn); 
    remote.setCommand(lightOff); 
    remote.undoLastCommand();    

    return 0;
}
