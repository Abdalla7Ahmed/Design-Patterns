/*
The Command pattern is a behavioral design pattern that encapsulates a request as an object.
It allows you to parameterize clients with queues, requests, and operations while supporting
undo and redo functionalities.
*/
#include <iostream>
#include <memory>
#include <vector>
#include <stack>

// Command Interface
class ICommand
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand() = default;
};

// Receivers

// **Receiver 1: Light**
class Light
{
public:
    void turnOn() { std::cout << "Light is ON\n"; }
    void turnOff() { std::cout << "Light is OFF\n"; }
};

// **Receiver 2: Fan**
class Fan
{
public:
    void turnOn() { std::cout << "Fan is ON\n"; }
    void turnOff() { std::cout << "Fan is OFF\n"; }
};

// Concrete Commands
class LightOnCommand : public ICommand
{
private:
    std::shared_ptr<Light> light;

public:
    LightOnCommand(std::shared_ptr<Light> light) : light(light) {}
    void execute() override
    {
        light->turnOn();
    }
    void undo() override
    {
        light->turnOff();
    }
};

class FanOnCommand : public ICommand
{
private:
    std::shared_ptr<Fan> fan;

public:
    FanOnCommand(std::shared_ptr<Fan> fan) : fan(fan) {}
    void execute() override
    {
        fan->turnOn();
    }
    void undo() override
    {
        fan->turnOff();
    }
};

// **Invoker: Remote Control**
class RemoteControl
{
private:
    std::stack<std::shared_ptr<ICommand>> history;

public:
    void executeCommand(std::shared_ptr<ICommand> cmd)
    {
        cmd->execute();
        history.push(cmd);
    }

    void undoLastCommand()
    {
        if (!history.empty())
        {
            history.top()->undo();
            history.pop();
        }
        else
        {
            std::cout << "No commands to undo\n";
        }
    }
};

int main(int argc, const char **argv)
{
    auto light = std::make_shared<Light>();
    auto fan = std::make_shared<Fan>();

    auto lighton = std::make_shared<LightOnCommand>(light);
    auto fanon = std::make_shared<FanOnCommand>(fan);

    auto remotecontrol = std::make_shared<RemoteControl>();

    remotecontrol->executeCommand(lighton); // Light ON
    remotecontrol->executeCommand(fanon);   // Fan ON

    std::cout << "Undoing last action...\n";
    remotecontrol->undoLastCommand(); // Undo Fan ON
    std::cout << "Undoing last action...\n";
    remotecontrol->undoLastCommand(); // Undo Light ON
    std::cout << "Trying to undo with no commands...\n";
    remotecontrol->undoLastCommand(); // No commands left

    return 0;
}