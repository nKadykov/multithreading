#include <iostream>
#include <mutex>
#include <thread>

int main() {
    std::mutex m1;
    std::mutex m2;

    auto f1 = [&](){
        std::unique_lock<std::mutex> lk1(m1, std::defer_lock);
        std::unique_lock<std::mutex> lk2(m2, std::defer_lock);
        std::lock(lk1, lk2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    };

    auto f2 = [&](){
        std::unique_lock<std::mutex> lk1(m1, std::defer_lock);
        std::unique_lock<std::mutex> lk2(m2, std::defer_lock);
        std::lock(lk1, lk2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    };

    std::thread t1([&](){
        f1();
    });
    std::thread t2([&](){
        f2();
    });

    t1.join();
    t2.join();

    return 0;
}