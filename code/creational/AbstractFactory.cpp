#include <iostream>
#include <memory>

// Abstract Product A
class Button
{
public:
    virtual void paint() const = 0;
};

// Abstract Product B
class Checkbox
{
public:
    virtual void paint() const = 0;
};

// Concrete Product A1
class WindowsButton : public Button
{
public:
    void paint() const override
    {
        std::cout << "Rendering a Windows button.\n";
    }
};

// Concrete Product B1
class WindowsCheckbox : public Checkbox
{
public:
    void paint() const override
    {
        std::cout << "Rendering a Windows checkbox.\n";
    }
};

// Concrete Product A2
class MacOSButton : public Button
{
public:
    void paint() const override
    {
        std::cout << "Rendering a macOS button.\n";
    }
};

// Concrete Product B2
class MacOSCheckbox : public Checkbox
{
public:
    void paint() const override
    {
        std::cout << "Rendering a macOS checkbox.\n";
    }
};

// Abstract Factory
class GUIFactory
{
public:
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// Concrete Factory 1
class WindowsFactory : public GUIFactory
{
public:
    std::unique_ptr<Button> createButton() const override
    {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override
    {
        return std::make_unique<WindowsCheckbox>();
    }
};

// Concrete Factory 2
class MacOSFactory : public GUIFactory
{
public:
    std::unique_ptr<Button> createButton() const override
    {
        return std::make_unique<MacOSButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override
    {
        return std::make_unique<MacOSCheckbox>();
    }
};

// Client
class Application
{
private:
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;

public:
    Application(std::unique_ptr<GUIFactory> factory)
    {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    void renderUI() const
    {
        button->paint();
        checkbox->paint();
    }

    ~Application() = default;
};

// Usage
int main()
{
    std::unique_ptr<GUIFactory> factory;
    std::string osName = "Windows"; // This would typically come from system properties.

    if (osName == "Windows")
    {
        factory = std::make_unique<WindowsFactory>();
    }
    else
    {
        factory = std::make_unique<MacOSFactory>();
    }

    std::unique_ptr<Application> app = std::make_unique<Application>(std::move(factory));
    app->renderUI();

    return 0;
}
