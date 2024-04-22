#include <iostream>
#include <thread>

int main() {
    unsigned long long g_count = 0;

    std::thread t1([&](){
        ++g_count;
    });

    std::thread t2([&](){
        for(auto i = 0; i < 1'000'000; ++i) {
            ++g_count;
        }
    });

    t1.join();
    t2.join();

    std::cout << g_count;

    return 0;
}