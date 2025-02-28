#include <iostream>
#include <memory>

class IOutput
{
public:
    virtual void TurnOn() = 0;
    virtual void TurnOff() = 0;
    virtual ~IOutput() {}
};

class Led : public IOutput
{
private:
public:
    Led() {}
    void TurnOn() override
    {
        std::cout << "Led Turn On" << std::endl;
    }
    void TurnOff() override
    {
        std::cout << "Led Turn off" << std::endl;
    }
};

class Buzzer : public IOutput
{
private:
public:
    Buzzer() {}
    void TurnOn() override
    {
        std::cout << "Buzzer Turn On" << std::endl;
    }
    void TurnOff() override
    {
        std::cout << "Buzzer Turn off" << std::endl;
    }
};

class IODeviceFactory
{
private:
public:
    enum class Device : unsigned char
    {
        LED,
        BUZZER
    };
    static std::unique_ptr<IOutput> MakeIODeviceFactory(Device object);
};

std::unique_ptr<IOutput> IODeviceFactory::MakeIODeviceFactory(Device object)
{
    if (Device::LED == object)
    {
        return std::make_unique<Led>();
    }
    else if (Device::BUZZER == object)
    {
        return std::make_unique<Buzzer>();
    }
    return nullptr;
}

int main(int argc, const char **argv)
{
    std::unique_ptr<IOutput> led1 = IODeviceFactory().MakeIODeviceFactory(IODeviceFactory::Device::LED);
    std::unique_ptr<IOutput> buzzer1 = IODeviceFactory().MakeIODeviceFactory(IODeviceFactory::Device::BUZZER);

    led1->TurnOn();
    led1->TurnOff();

    buzzer1->TurnOn();
    buzzer1->TurnOff();

    return 0;
}