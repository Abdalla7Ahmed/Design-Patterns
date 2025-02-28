/*
The Mediator pattern is a behavioral design pattern that reduces direct dependencies
between objects by introducing a mediator that facilitates communication between them.
Instead of objects communicating directly, they send messages through the mediator.

Where is it Used?

    GUI frameworks (e.g., buttons, checkboxes, and input fields communicating through a form manager).
    Chat applications (e.g., users send messages through a central server).
    Air traffic control systems (planes communicate via a control tower).

*/

#include <iostream>
#include <memory>
#include <vector>

class IMediator
{
public:
    virtual void sendMessage(const std::string &message, class User *sender) = 0;
    virtual ~IMediator() = default;
};

class User
{
private:
    std::string name;
    std::weak_ptr<IMediator> chatRoom;

public:
    std::string get_name()
    {
        return name;
    }
    User(std::string name, std::shared_ptr<IMediator> chatRoom) : name(name), chatRoom(chatRoom) {}
    void send(const std::string &message)
    {
        std::cout << "[" << name << "] sends: " << message << std::endl;
        if (auto mediator = chatRoom.lock())
        {
            mediator->sendMessage(message, this);
        }
    }

    void receive(const std::string &message, const std::string &sender)
    {
        std::cout << "[" << name << "] receives from [" << sender << "]: " << message << std::endl;
    }
};

class ChatRoom : public IMediator
{
private:
    std::vector<std::shared_ptr<User>> users;

public:
    void adduser(std::shared_ptr<User> user)
    {
        users.push_back(user);
    }
    void sendMessage(const std::string &message, User *sender) override
    {
        for (const auto &user : users)
        {
            if (user.get() != sender)
            {
                user->receive(message, sender->get_name());
            }
        }
    }
};
int main(int argc, const char **argv)
{
    auto chatRoom = std::make_shared<ChatRoom>();
    auto Alice = std::make_shared<User>("Alice", chatRoom);
    auto ali = std::make_shared<User>("ali", chatRoom);
    auto osman = std::make_shared<User>("osman", chatRoom);

    chatRoom->adduser(Alice);
    chatRoom->adduser(ali);
    chatRoom->adduser(osman);

    Alice->send("Hello, everyone!");
    ali->send("Hi Alice!");
    osman->send("Good morning!");

    return 0;
}