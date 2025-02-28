#include <iostream>

// Abstract product class
class Shape
{
public:
    virtual void draw() = 0;
    virtual ~Shape() {} // Virtual destructor for polymorphism
};

// Concrete product class - Circle
class Circle : public Shape
{
public:
    void draw() override
    {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

// Concrete product class - Square
class Square : public Shape
{
public:
    void draw() override
    {
        std::cout << "Drawing a Square" << std::endl;
    }
};

// Abstract creator class
class ShapeFactory
{
public:
    virtual Shape *createShape() = 0;
    virtual ~ShapeFactory() {} // Virtual destructor for polymorphism
};
// Concrete creator class - CircleFactory
class CircleFactory : public ShapeFactory
{
public:
    Shape *createShape() override
    {
        return new Circle();
    }
};

// Concrete creator class - SquareFactory
class SquareFactory : public ShapeFactory
{
public:
    Shape *createShape() override
    {
        return new Square();
    }
};

class IOutput
{
public:
    virtual void TurnOn() = 0;
    virtual void TurnOff() = 0;
    virtual ~IOutput() {}
};

class Buzzer : public IOutput
{

public:
    void TurnOn() override
    {
        std::cout << "Buzzer TurnOn" << std::endl;
    }
    void TurnOff() override
    {
        std::cout << "Buzzer TurnOff" << std::endl;
    }
};

class LED : public IOutput
{
public:
    void TurnOn() override
    {
        std::cout << "LED TurnOn" << std::endl;
    }
    void TurnOff() override
    {
        std::cout << "LED TurnOff" << std::endl;
    }
};

class DeviceFactory
{
public:
    virtual IOutput *CreateDevice() = 0;
    virtual ~DeviceFactory() {};
};

class LED_Factory : public DeviceFactory
{
public:
    IOutput *CreateDevice() override
    {
        return new LED();
    }
};
class Buzzer_Factory : public DeviceFactory
{
public:
    IOutput *CreateDevice() override
    {
        return new Buzzer();
    }
};

int main(int argc, const char **argv)
{

    ShapeFactory *circleFactory = new CircleFactory();
    ShapeFactory *squareFactory = new SquareFactory();

    Shape *circle = circleFactory->createShape();
    Shape *square = squareFactory->createShape();

    circle->draw(); // Output: Drawing a Circle
    square->draw(); // Output: Drawing a Square

    DeviceFactory *led_factory = new LED_Factory();
    DeviceFactory *buzzer_factory = new Buzzer_Factory();

    IOutput *led1 = led_factory->CreateDevice();
    IOutput *buzzer1 = buzzer_factory->CreateDevice();

    led1->TurnOn();
    buzzer1->TurnOn();

    led1->TurnOff();
    buzzer1->TurnOff();

    delete circleFactory;
    delete squareFactory;
    delete circle;
    delete square;

    delete led_factory;
    delete buzzer_factory;
    delete led1;
    delete buzzer1;
    return 0;
}
