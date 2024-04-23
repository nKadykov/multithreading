#include <iostream>
#include <mutex>
#include <thread>

int main() {
    std::mutex m1;
    std::mutex m2;

    auto f1 = [&](){
        std::lock(m1, m2);
        std::lock_guard<std::mutex> lk1(m1, std::adopt_lock);
        std::lock_guard<std::mutex> lk2(m2, std::adopt_lock);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    };

    auto f2 = [&](){
        std::lock(m1, m2);
        std::lock_guard<std::mutex> lk1(m1, std::adopt_lock);
        std::lock_guard<std::mutex> lk2(m2, std::adopt_lock);
        std::this_thread::sleep_for(std::chrono::seconds(2));
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