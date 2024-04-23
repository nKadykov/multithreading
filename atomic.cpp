#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::atomic<unsigned long long> g_count{0};

    std::thread t([&](){
        for(auto i = 0; i < 1'000'000'000; ++i) {
            g_count.fetch_add(1);
        }
    });

    t.join();

    std::cout << g_count << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "1 thread: " << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    std::atomic<unsigned long long> g_count1{0};

    std::thread t1([&](){
        for(auto i = 0; i < 500'000'000; ++i) {
            g_count1.fetch_add(1);
        }
    });

    std::thread t2([&](){
        for(auto i = 0; i < 500'000'000; ++i) {
            g_count1.fetch_add(1);
        }
    });

    t1.join();
    t2.join();

    std::cout << g_count1 << std::endl;

    stop = std::chrono::high_resolution_clock::now();
    
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "2 threads: " << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    std::atomic<unsigned long long> g_count2{0};

    std::thread t11([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count2.fetch_add(1);
        }
    });

    std::thread t12([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count2.fetch_add(1);
        }
    });

    std::thread t13([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count2.fetch_add(1);
        }
    });

    std::thread t14([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count2.fetch_add(1);
        }
    });


    t11.join();
    t12.join();
    t13.join();
    t14.join();

    std::cout << g_count2 << std::endl;

    stop = std::chrono::high_resolution_clock::now();
    
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "4 threads: " << duration.count() << " microseconds" << std::endl;

    return 0;
}