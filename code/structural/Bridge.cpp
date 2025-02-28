#include <iostream>
#include <memory>
class OSImplementation
{
public:
    virtual void drawButton(void) = 0;

private:
};

class windows : public OSImplementation
{
public:
    void drawButton(void) override
    {
        std::cout << "Doing Operation in windows Platform" << std::endl;
    }
};
class Linux : public OSImplementation
{
public:
    void drawButton(void) override
    {
        std::cout << "Doing Operation in Linux Platform" << std::endl;
    }
};
class IOS : public OSImplementation
{
public:
    void drawButton(void) override
    {
        std::cout << "Doing Operation in IOS Platform" << std::endl;
    }
};

class CommonUI
{
protected:
    std::shared_ptr<OSImplementation> OSImpl;

public:
    CommonUI() {}
    CommonUI(std::shared_ptr<OSImplementation> OSImpl) : OSImpl(OSImpl) {}
    virtual void render(void) = 0;
};

class Button : public CommonUI
{

public:
    Button(std::shared_ptr<OSImplementation> OSImpl) : CommonUI(OSImpl) {}
    void render(void) override
    {
        OSImpl->drawButton();
    }
};

int main(int argc, const char **argv)
{
    std::shared_ptr<OSImplementation> Linux_OS = std::make_shared<Linux>();
    std::shared_ptr<CommonUI> LinButton1 = std::make_shared<Button>(Linux_OS);
    LinButton1->render();

    // or
    std::shared_ptr<CommonUI> LinButton2 = std::make_shared<Button>(std::make_shared<Linux>());
    LinButton2->render();

    std::shared_ptr<CommonUI> winButton = std::make_shared<Button>(std::make_shared<windows>());
    winButton->render();

    std::shared_ptr<CommonUI> IOSButton = std::make_shared<Button>(std::make_shared<IOS>());
    IOSButton->render();

    return 0;
}
