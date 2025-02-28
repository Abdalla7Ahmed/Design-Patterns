#include <iostream>
#include <thread>
#include <mutex>
long long x = 0;

void inc()
{
    int y = 10;
    for (int i = 0; i < 100000; i++)
    {
        x++;
    }
}

int main()
{
    std::thread t1(inc), t2(inc);
    t1.join();
    t2.join();
    std::cout << x << std::endl;
    return 0;
}
