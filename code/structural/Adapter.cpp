
#include <iostream>
class ILogger
{
public:
    virtual void logInfo(const std::string &message) = 0;
    virtual void logError(const std::string &message) = 0;
    virtual ~ILogger() = default;
};

class LegacyLogger
{
public:
    void writeToLog(const std::string &message)
    {
        std::cout << "Legacy Log: " << message << std::endl;
    }
};

class LoggerAdapter : public ILogger
{
private:
    LegacyLogger &legacyLogger; // Reference to the legacy logger

public:
    LoggerAdapter(LegacyLogger &logger) : legacyLogger(logger) {}

    void logInfo(const std::string &message) override
    {
        legacyLogger.writeToLog("INFO: " + message);
    }

    void logError(const std::string &message) override
    {
        legacyLogger.writeToLog("ERROR: " + message);
    }
};

int main()
{
    LegacyLogger legacyLogger;
    LoggerAdapter adapter(legacyLogger);

    adapter.logInfo("This is an information message");
    adapter.logError("This is an error message");

    return 0;
}
