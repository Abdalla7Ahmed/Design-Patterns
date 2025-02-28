#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <chrono>
#include <iomanip>
class Logger
{
private:
    Logger();
    ~Logger();

    static Logger *Logger_instance;

    static void Cleanup(); // Function to clean up the singleton instance.
    std::ofstream logFile;
    static std::mutex logMutex; // For thread safety
public:
    static Logger &Get_instance();

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void logInfo(const std::string &message);
    void logWarning(const std::string &message);
    void logError(const std::string &message);

    void WriteLog(const std::string &level, const std::string &message);
};
Logger *Logger::Logger_instance = nullptr;
// Initialize the static mutex
std::mutex Logger::logMutex;
Logger::Logger()
{
    logFile.open("Application.log", std::ios::app);
    if (!logFile.is_open())
    {
        throw std::runtime_error("Failed to open log file");
    }
}
Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

Logger &Logger::Get_instance()
{
    if (!Logger_instance)
    {
        Logger_instance = new Logger();
        std::atexit(Cleanup); // Register cleanup function to delete instance at program exit.
    }

    return *Logger_instance;
}

void Logger::WriteLog(const std::string &level, const std::string &message)
{
    std::lock_guard<std::mutex> lock(logMutex); // Ensure thread safety

    // Get current time
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto localTime = std::localtime(&time_t_now);

    // Write the log entry
    logFile << "[" << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << "] "
            << "[" << level << "] " << message << std::endl;
}

void Logger::logInfo(const std::string &message)
{
    WriteLog("Info", message);
}
void Logger::logWarning(const std::string &message)
{
    WriteLog("Warning", message);
}
void Logger::logError(const std::string &message)
{
    WriteLog("Error", message);
}
void Logger::Cleanup()
{
    delete Logger_instance;
    Logger_instance = nullptr;
}

int main(int argc, const char **argv)
{
    Logger::Get_instance().logError("this is an error message");
    Logger::Get_instance().logWarning("this is a warning message");
    Logger::Get_instance().logInfo("this is an info message");

    return 0;
}
