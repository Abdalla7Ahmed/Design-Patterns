#include <iostream>
#include <string>
using namespace std;

// Product (Car)
class Car
{
public:
    string engine;
    string wheels;
    string seats;

    void showCar() const
    {
        cout << "Car with Engine: " << engine << ", Wheels: " << wheels << ", Seats: " << seats << endl;
    }
};

// Abstract Builder
class CarBuilder
{
public:
    virtual void buildEngine() = 0;
    virtual void buildWheels() = 0;
    virtual void buildSeats() = 0;
    virtual Car *getCar() = 0;
    virtual ~CarBuilder() {}
};

// Concrete Builder (Sports Car)
class SportsCarBuilder : public CarBuilder
{
private:
    Car *car;

public:
    SportsCarBuilder() { car = new Car(); }

    void buildEngine() override
    {
        car->engine = "V8 Engine";
    }

    void buildWheels() override
    {
        car->wheels = "Racing Wheels";
    }

    void buildSeats() override
    {
        car->seats = "Racing Seats";
    }

    Car *getCar() override
    {
        return car;
    }
};

// Concrete Builder (SUV Car)
class SUVCarBuilder : public CarBuilder
{
private:
    Car *car;

public:
    SUVCarBuilder() { car = new Car(); }

    void buildEngine() override
    {
        car->engine = "V6 Engine";
    }

    void buildWheels() override
    {
        car->wheels = "Offroad Wheels";
    }

    void buildSeats() override
    {
        car->seats = "Leather Seats";
    }

    Car *getCar() override
    {
        return car;
    }
};

// Director
class CarDirector
{
private:
    CarBuilder *builder;

public:
    CarDirector(CarBuilder *b) : builder(b) {}

    void constructCar()
    {
        builder->buildEngine();
        builder->buildWheels();
        builder->buildSeats();
    }
};

int main()
{
    // Building a Sports Car
    CarBuilder *sportsCarBuilder = new SportsCarBuilder();
    CarDirector director(sportsCarBuilder);
    director.constructCar();
    Car *sportsCar = sportsCarBuilder->getCar();
    sportsCar->showCar();

    // Building an SUV
    CarBuilder *suvCarBuilder = new SUVCarBuilder();
    CarDirector director2(suvCarBuilder);
    director2.constructCar();
    Car *suvCar = suvCarBuilder->getCar();
    suvCar->showCar();

    delete sportsCar;
    delete sportsCarBuilder;
    delete suvCar;
    delete suvCarBuilder;

    return 0;
}
