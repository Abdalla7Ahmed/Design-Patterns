

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Component interface - defines the basic ice cream
// operations.
class IceCream
{
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
};

// basic IceCream

// Concrete Component - the basic ice cream class.
class VanillaIceCream : public IceCream
{
public:
    string getDescription() const override
    {
        return "Vanilla Ice Cream";
    }

    double cost() const override { return 160.0; }
};

// Decorator - abstract class that extends IceCream.
class IceCreamDecorator : public IceCream
{
protected:
    std::shared_ptr<IceCream> iceCream;

public:
    IceCreamDecorator(std::shared_ptr<IceCream> ic)
        : iceCream(ic)
    {
    }

    string getDescription() const override
    {
        return iceCream->getDescription();
    }

    double cost() const override
    {
        return iceCream->cost();
    }
};

// Concrete Decorator - adds chocolate topping.
class ChocolateDecorator : public IceCreamDecorator
{
public:
    ChocolateDecorator(std::shared_ptr<IceCream> ic)
        : IceCreamDecorator(ic)
    {
    }

    string getDescription() const override
    {
        return iceCream->getDescription() + " with Chocolate";
    }

    double cost() const override
    {
        return iceCream->cost() + 100.0;
    }
};

// Concrete Decorator - adds caramel topping.
class CaramelDecorator : public IceCreamDecorator
{
public:
    CaramelDecorator(std::shared_ptr<IceCream> ic)
        : IceCreamDecorator(ic)
    {
    }

    string getDescription() const override
    {
        return iceCream->getDescription() + " with Caramel";
    }

    double cost() const override
    {
        return iceCream->cost() + 150.0;
    }
};
int main(int argc, const char **argv)
{
    // basic
    std::shared_ptr<IceCream> vanilla_icecream = std::make_shared<VanillaIceCream>();
    std::cout << vanilla_icecream->getDescription() << std::endl;
    std::cout << vanilla_icecream->cost() << std::endl;

    // or
    std::cout << std::shared_ptr<IceCream>(std::make_shared<VanillaIceCream>())->getDescription() << std::endl;
    std::cout << std::shared_ptr<IceCream>(std::make_shared<VanillaIceCream>())->cost() << std::endl;

    // Wrap it with ChocolateDecorator
    std::shared_ptr<IceCreamDecorator> chocolatedecorator = std::make_shared<ChocolateDecorator>(vanilla_icecream);
    std::cout << chocolatedecorator->getDescription() << std::endl;
    std::cout << chocolatedecorator->cost() << std::endl;

    // or
    std::cout << std::shared_ptr<IceCreamDecorator>(std::make_shared<ChocolateDecorator>(vanilla_icecream))->getDescription() << std::endl;
    std::cout << std::shared_ptr<IceCreamDecorator>(std::make_shared<ChocolateDecorator>(vanilla_icecream))->cost() << std::endl;

    // Wrap it with CaramelDecorator
    std::shared_ptr<IceCreamDecorator> carameldecorator = std::make_shared<CaramelDecorator>(vanilla_icecream);
    std::cout << carameldecorator->getDescription() << std::endl;
    std::cout << carameldecorator->cost() << std::endl;

    // or
    std::cout << std::shared_ptr<IceCreamDecorator>(std::make_shared<CaramelDecorator>(vanilla_icecream))->getDescription() << std::endl;
    std::cout << std::shared_ptr<IceCreamDecorator>(std::make_shared<CaramelDecorator>(vanilla_icecream))->cost() << std::endl;

    // Wrap it with ChocolateDecorator and CaramelDecorator
    std::shared_ptr<IceCreamDecorator> chocolate_carameldecorator = std::make_shared<ChocolateDecorator>(std::make_shared<CaramelDecorator>(vanilla_icecream));
    std::cout << chocolate_carameldecorator->getDescription() << std::endl;
    std::cout << chocolate_carameldecorator->cost() << std::endl;

    // or
    std::cout << std::shared_ptr<IceCreamDecorator>(std::make_shared<ChocolateDecorator>(std::make_shared<CaramelDecorator>(vanilla_icecream)))->getDescription() << std::endl;
    std::cout << std::shared_ptr<IceCreamDecorator>(std::make_shared<ChocolateDecorator>(std::make_shared<CaramelDecorator>(vanilla_icecream)))->cost() << std::endl;

    return 0;
}
