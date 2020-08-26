#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

std::mutex gMutex;

void Test1()
{
     gMutex.lock();
     gMutex.lock();
}

void Test2()
{
    while (true) {
     sleep(1);
    }
}

int main()
{
    std::thread t1(Test1);
    std::thread t2(Test2);

    t1.join();
    t2.join();

    return 0;
}
