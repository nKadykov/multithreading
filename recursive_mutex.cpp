#include <iostream>
#include <thread>
#include <mutex>

class X {
    std::recursive_mutex m;
    std::string shared;
public:
    void f1() {
        std::lock_guard<std::recursive_mutex> lk(m);
        shared = "f1";
        std::cout << "in f1, shared variable is now " << shared << std::endl;
    }
    void f2() {
        std::lock_guard<std::recursive_mutex> lk(m);
        shared = "f2";
        std::cout << "in f2, shared variable is now " << shared << std::endl;
        f1();
        std::cout << "back in f2, shared variable is " << shared << std::endl;
    }
};

int main() {
    
    X x;
    std::thread t1(&X::f1, &x);
    std::thread t2(&X::f2, &x);

    t1.join();
    t2.join();

    return 0;
}