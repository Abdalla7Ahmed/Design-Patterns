/*
A Facade Pattern provides a simplified interface to a complex system of classes, making it easier to use.
*/

#include <iostream>
#include <memory>
class Light
{
public:
    void turnOn() { std::cout << "Lights are ON\n"; }
    void turnOff() { std::cout << "Lights are OFF\n"; }
};

// Subsystem 2: Air Conditioner
class AirConditioner
{
public:
    void turnOn() { std::cout << "Air Conditioner is ON\n"; }
    void turnOff() { std::cout << "Air Conditioner is OFF\n"; }
    void setTemperature(int temp) { std::cout << "Temperature set to " << temp << "°C\n"; }
};

// Subsystem 3: Security System
class SecuritySystem
{
public:
    void arm() { std::cout << "Security System ARMED\n"; }
    void disarm() { std::cout << "Security System DISARMED\n"; }
};

// Subsystem 4: Entertainment System
class EntertainmentSystem
{
public:
    void turnOn() { std::cout << "TV and Speakers are ON\n"; }
    void turnOff() { std::cout << "TV and Speakers are OFF\n"; }
};

class SmartHomeFacade
{
private:
    std::unique_ptr<Light> m_light;
    std::unique_ptr<AirConditioner> m_airconditioner;
    std::unique_ptr<SecuritySystem> m_securitysystem;
    std::unique_ptr<EntertainmentSystem> m_entertainmentsystem;

public:
    // SmartHomeFacade()
    //     : m_light(std::make_unique<Light>()),
    //       m_airconditioner(std::make_unique<AirConditioner>()),
    //       m_securitysystem(std::make_unique<SecuritySystem>()),
    //       m_entertainmentsystem(std::make_unique<EntertainmentSystem>()) {}
    void leaveHome()
    {

        std::cout << "Light pointer: " << m_light.get() << "\n";

        std::cout << "\nLeaving Home...\n";
        m_light->turnOff();
        m_airconditioner->turnOff();
        m_securitysystem->arm();
        m_entertainmentsystem->turnOff();
        std::cout << "Home is secured!\n";
    }

    void arriveHome()
    {
        std::cout << "\nArriving Home...\n";
        m_light->turnOn();
        m_airconditioner->turnOn();
        m_airconditioner->setTemperature(22);
        m_securitysystem->disarm();
        m_entertainmentsystem->turnOn();
        std::cout << "Welcome Home!\n";
    }
};

int main()
{
    std::unique_ptr<SmartHomeFacade> home = std::make_unique<SmartHomeFacade>();
    int choice = 1;

    do
    {
        std::cout << "\nSmart Home System\n";
        std::cout << "1. Arrive Home\n";
        std::cout << "2. Leave Home\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        // std::cin >> choice;

        switch (choice)
        {
        case 1:
            home->arriveHome();
            break;
        case 2:
            home->leaveHome();
            break;
        case 3:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again!\n";
        }
    } while (choice != 3);

    return 0;
}