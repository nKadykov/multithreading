#include <iostream>
#include <thread>
#include <atomic>

int main() {
    std::atomic<unsigned long long> g_count{0};

    std::thread t1([&](){
        for(auto i = 0; i < 1'000'000; ++i) {
            g_count.fetch_add(1);
        }
    });

    std::thread t2([&](){
        for(auto i = 0; i < 1'000'000; ++i) {
            g_count.fetch_add(1);
        }
    });

    t1.join();
    t2.join();

    std::cout << g_count;

    return 0;
}