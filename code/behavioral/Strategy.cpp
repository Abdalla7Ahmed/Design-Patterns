/*
The Strategy Pattern is a behavioral design pattern that allows a class to select
an algorithm at runtime. Instead of implementing multiple algorithms inside a single class,
we encapsulate them into separate classes and make them interchangeable.
Components of the Strategy Pattern

    Strategy Interface → Defines the common behavior for all strategies.
    Concrete Strategies → Implement different variations of the algorithm.
    Context Class → Maintains a reference to a strategy and allows clients to change it dynamically.
*/

#include <iostream>
#include <memory>

// Strategy Interface
class PaymentStrategy
{
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() = default;
};

// Concrete Strategy: Credit Card Payment
class CreditCardPayment : public PaymentStrategy
{
public:
    void pay(int amount) override
    {
        std::cout << "Paid $" << amount << " using Credit Card.\n";
    }
};

// Concrete Strategy: PayPal Payment
class PayPalPayment : public PaymentStrategy
{
public:
    void pay(int amount) override
    {
        std::cout << "Paid $" << amount << " using PayPal.\n";
    }
};

// Concrete Strategy: Bitcoin Payment
class BitcoinPayment : public PaymentStrategy
{
public:
    void pay(int amount) override
    {
        std::cout << "Paid $" << amount << " using Bitcoin.\n";
    }
};

// Context Class: Payment Processor
class PaymentProcessor
{
private:
    std::shared_ptr<PaymentStrategy> strategy;

public:
    void setStrategy(std::shared_ptr<PaymentStrategy> newStrategy)
    {
        strategy = newStrategy;
    }

    void processPayment(int amount)
    {
        if (strategy)
        {
            strategy->pay(amount);
        }
        else
        {
            std::cout << "No payment method selected.\n";
        }
    }
};

int main()
{
    PaymentProcessor paymentProcessor;

    // Set payment strategy dynamically
    paymentProcessor.setStrategy(std::make_shared<CreditCardPayment>());
    paymentProcessor.processPayment(100);

    paymentProcessor.setStrategy(std::make_shared<PayPalPayment>());
    paymentProcessor.processPayment(200);

    paymentProcessor.setStrategy(std::make_shared<BitcoinPayment>());
    paymentProcessor.processPayment(300);

    return 0;
}
