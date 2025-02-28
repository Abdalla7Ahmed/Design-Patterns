#include <iostream>

class Singleton
{
private:
    Singleton();
    ~Singleton();

    int counter;
    static Singleton *singleton_instance;
    static void Cleanup(); // Function to clean up the singleton instance.

public:
    static Singleton &Get_Instance(void);
    void display_Counter();
    void increment_counter();
    void decrement_counter();
};

Singleton *Singleton::singleton_instance = nullptr;

Singleton::Singleton() : counter(0)
{
    std::cout << __FUNCTION__ << std::endl;
}
Singleton::~Singleton()
{
    std::cout << __FUNCTION__ << std::endl;
}
void Singleton::display_Counter()
{
    std::cout << "the counter value is " << counter << std::endl;
}
void Singleton::increment_counter()
{
    std::cout << __FUNCTION__ << std::endl;
    this->counter++;
}
void Singleton::decrement_counter()
{
    std::cout << __FUNCTION__ << std::endl;
    this->counter--;
}

void Singleton::Cleanup()
{
    delete singleton_instance;
    singleton_instance = nullptr;
}
Singleton &Singleton::Get_Instance(void)
{
    if (!singleton_instance)
    {
        singleton_instance = new Singleton();
        std::atexit(Cleanup); // Register cleanup function to delete instance at program exit.
    }

    return *singleton_instance;
}

int main(int argc, const char **argv)
{

    Singleton::Get_Instance().display_Counter(); // 0
    Singleton::Get_Instance().increment_counter();
    Singleton::Get_Instance().increment_counter();
    Singleton::Get_Instance().display_Counter(); // 2
    Singleton::Get_Instance().decrement_counter();
    Singleton::Get_Instance().display_Counter(); // 1

    // Singleton sin0; // error
    Singleton &sin1 = Singleton::Get_Instance();
    Singleton &sin2 = Singleton::Get_Instance();
    Singleton &sin3 = Singleton::Get_Instance();
    Singleton &sin4 = Singleton::Get_Instance();

    sin1.display_Counter(); // 1
    sin2.display_Counter(); // 1
    sin3.display_Counter(); // 1
    sin4.display_Counter(); // 1

    return 0;
}