#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

int main() {
    std::mutex m;
    long long g = 0;

    auto f1 = [&](){
        std::lock_guard<std::mutex> l(m);
        for(int i = 0; i < 1'000'000'000; i++) {
            g++;
        }
    };

    auto f2 = [&](){
        std::lock_guard<std::mutex> l(m);
        for(int i = 0; i < 1'000'000'000; i++) {
            g++;
        }
    };

    std::thread t1([&](){
        f1();
    });
    std::thread t2([&](){
        f2();
    });

    t1.join();
    t2.join();

    std::cout << g << std::endl;

    return 0;
}