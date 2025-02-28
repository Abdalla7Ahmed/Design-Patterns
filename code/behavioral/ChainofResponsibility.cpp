/*
The Chain of Responsibility (CoR) pattern is a behavioral design pattern that allows
multiple objects to handle a request without the sender knowing which object will handle it.
Instead of having a single object handle the request, it creates a chain of handlers where each handler decides either to:
    Process the request (if it's responsible for it).
    Pass the request to the next handler in the chain.

*/

#include <iostream>
#include <memory>

class Logger
{
private:
    std::shared_ptr<Logger> nextLogger;

public:
    virtual ~Logger() = default;
    void setNextLogger(std::shared_ptr<Logger> next)
    {
        nextLogger = next;
    }
    void LogMessage(int level, const std::string &message)
    {
        if (canHandle(level))
        {
            write_message(message);
        }
        else if (nextLogger)
        {
            nextLogger->LogMessage(level, message);
        }
        else
        {
            std::cout << "No logger could handle this message: " << message << std::endl;
        }
    }

    virtual bool canHandle(int level) = 0;
    virtual void write_message(const std::string &message) = 0;
};

class InfoLogger : public Logger
{
public:
    bool canHandle(int level) override
    {
        return level == 1;
    }
    void write_message(const std::string &message) override
    {
        std::cout << "[INFO] : " << message << std::endl;
    }
};

class WarningLogger : public Logger
{
public:
    bool canHandle(int level) override
    {
        return level == 2;
    }
    void write_message(const std::string &message) override
    {
        std::cout << "[WARNING] : " << message << std::endl;
    }
};

class ErrorLogger : public Logger
{
public:
    bool canHandle(int level) override
    {
        return level == 3;
    }
    void write_message(const std::string &message) override
    {
        std::cout << "[ERROR] : " << message << std::endl;
    }
};

int main(int argc, const char **argv)
{

    auto infologger = std::make_shared<InfoLogger>();
    auto warninglogger = std::make_shared<WarningLogger>();
    auto errorlogger = std::make_shared<ErrorLogger>();

    infologger->setNextLogger(warninglogger);
    warninglogger->setNextLogger(errorlogger);

    infologger->LogMessage(1, "System started successfully.");
    infologger->LogMessage(2, "Memory usage is high.");
    infologger->LogMessage(3, "Application crashed!");
    infologger->LogMessage(4, "Unknown issue detected.");

    return 0;
}