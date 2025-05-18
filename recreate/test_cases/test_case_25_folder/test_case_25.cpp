#include <thread>
#include <iostream>
void f(int id)
{
    for(int n=0; n<10; ++n)
        std::cout << "Output from thread " << id << '\n';
}
int main()
{
    std::thread t1(f, 1); // launch thread executiong function f() with argument 1
    std::thread t2(f, 2), t3(f, 3); // two more threads, also executing f()
    t1.join(); t2.join(); t3.join(); // wait for all three threads to finish before ending main()
}