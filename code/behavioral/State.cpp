/*
The State pattern is a behavioral design pattern that allows an object to change its
behavior dynamically based on its internal state. Instead of using many if or switch statements,
we encapsulate behaviors in different state classes.

When to use ?
when you have an object that behaves differently depending on its current state

Components of the State Pattern

    Context → The main object whose behavior changes based on its state.
    State Interface → Defines the common behavior for all concrete states.
    Concrete States → Implement specific behavior for each state.
*/

#include <iostream>
#include <memory>

// Forward declaration
class TrafficLightContext;

class TrafficLightState
{
public:
    virtual void handle(TrafficLightContext &TrafficLightContext) = 0;
    virtual ~TrafficLightState() = default;
};

// Context Class
class TrafficLightContext
{
private:
    std::shared_ptr<TrafficLightState> state;

public:
    TrafficLightContext(std::shared_ptr<TrafficLightState> initialState) : state(initialState) {}
    void setState(std::shared_ptr<TrafficLightState> newState)
    {
        state = newState;
    }
    void request()
    {
        if (state)
        {
            state->handle(*this);
        }
    }
};

// Concrete State: Red
class RedLight : public TrafficLightState
{
public:
    void handle(TrafficLightContext &context) override;
};

class GreenLight : public TrafficLightState
{
public:
    void handle(TrafficLightContext &context) override;
};

class YellowLight : public TrafficLightState
{
public:
    void handle(TrafficLightContext &context) override;
};

// Implement State Transitions
void RedLight::handle(TrafficLightContext &context)
{
    std::cout << "🔴 Red Light - Stop!\n";
    context.setState(std::make_shared<GreenLight>());
}
void GreenLight::handle(TrafficLightContext &context)
{
    std::cout << "🟢 Green Light - Go!\n";
    context.setState(std::make_shared<YellowLight>());
}

void YellowLight::handle(TrafficLightContext &context)
{
    std::cout << "🟡 Yellow Light - Slow Down!\n";
    context.setState(std::make_shared<RedLight>());
}

int main()
{

    auto trafficLight = std::make_shared<TrafficLightContext>(std::make_shared<RedLight>());

    for (int i = 0; i < 6; ++i)
    {
        trafficLight->request();
    }
}