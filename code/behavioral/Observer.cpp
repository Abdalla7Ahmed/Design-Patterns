/*The Observer pattern is a behavioral design pattern used for a one-to-many dependency between objects.

    When the Subject (Observable) changes, it notifies all Observers (Subscribers) automatically.
    Observers register/unregister themselves from the Subject.

    */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
// Observer Interface
class IObserver
{

public:
    virtual void update(float temperature) = 0;
    virtual ~IObserver() = default;
};

// Create Subject (Observable)
class ISubject
{
public:
    virtual void addObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void removeObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~ISubject() = default;
};

// Concrete Subject (Weather Station)
class WeatherStation : public ISubject
{
private:
    std::vector<std::shared_ptr<IObserver>> observers;
    float temperature;

public:
    void addObserver(std::shared_ptr<IObserver> observer) override
    {
        observers.push_back(observer);
    }
    void removeObserver(std::shared_ptr<IObserver> observer) override
    {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                           [&observer](const std::shared_ptr<IObserver> &o)
                           {
                               return o.get() == observer.get();
                           }),
            observers.end());
    }

    void notifyObservers() override
    {
        for (const auto &observer : observers)
        {
            observer->update(temperature);
        }
    }

    void settemperature(float temperature)
    {
        this->temperature = temperature;
        notifyObservers();
    }
};

// Create Concrete Observers
class MobileApp : public IObserver
{
public:
    void update(float temperature) override
    {
        std::cout << "[MobileApp] New Temperature: " << temperature << "°C\n";
    }
};

class DisplayScreen : public IObserver
{
public:
    void update(float temperature) override
    {
        std::cout << "[DisplayScreen] New Temperature: " << temperature << "°C\n";
    }
};

int main(int argc, const char **argv)
{

    auto weatherstation = std::make_shared<WeatherStation>();
    auto mobileapp = std::make_shared<MobileApp>();
    auto displayscreen = std::make_shared<DisplayScreen>();

    weatherstation->addObserver(mobileapp);
    weatherstation->addObserver(displayscreen);

    weatherstation->settemperature(37.5);
    weatherstation->settemperature(40.5);

    weatherstation->removeObserver(mobileapp);
    weatherstation->settemperature(20);

    return 0;
}