/*
The Template Method pattern is a behavioral design pattern that defines the skeleton
of an algorithm in a base class but allows subclasses to override specific steps of
the algorithm without changing its structure.

Key Concepts

    Abstract Base Class → Defines the template method (algorithm structure) and provides default implementations for some steps.
    Concrete Subclasses → Implement specific steps of the algorithm while keeping the structure intact.
    Final Template Method → Calls various steps in a predefined sequence, ensuring consistency.
*/

#include <iostream>

// Abstract Base Class (Template)
class Beverage
{
public:
    // Template Method (Defines the algorithm structure)
    void prepareBeverage()
    {
        boilWater();
        brew();
        pourIntoCup();
        addCondiments();
    }

    // Common steps (final implementation)
    void boilWater()
    {
        std::cout << "Boiling water...\n";
    }

    void pourIntoCup()
    {
        std::cout << "Pouring into cup...\n";
    }

    // Steps that subclasses must implement
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    virtual ~Beverage() = default;
};

// Concrete Class: Tea
class Tea : public Beverage
{
public:
    void brew() override
    {
        std::cout << "Steeping the tea...\n";
    }

    void addCondiments() override
    {
        std::cout << "Adding lemon...\n";
    }
};

// Concrete Class: Coffee
class Coffee : public Beverage
{
public:
    void brew() override
    {
        std::cout << "Dripping coffee through filter...\n";
    }

    void addCondiments() override
    {
        std::cout << "Adding sugar and milk...\n";
    }
};

int main()
{
    std::cout << "Making Tea:\n";
    Tea tea;
    tea.prepareBeverage();

    std::cout << "\nMaking Coffee:\n";
    Coffee coffee;
    coffee.prepareBeverage();

    return 0;
}
