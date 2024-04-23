#include <iostream>
#include <mutex>
#include <thread>

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    unsigned long long g_count = 0;
    std::mutex g_count_mutex;

    std::thread t([&](){
        for(auto i = 0; i < 1'000'000'000; ++i) {
            g_count_mutex.lock();
            g_count += 1;
            g_count_mutex.unlock();
        }
    });

    t.join();

    std::cout << g_count << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "1 thread: " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();

    unsigned long long g_count1 = 0;
    std::mutex g_count_mutex1;

    std::thread t1([&](){
        for(auto i = 0; i < 500'000'000; ++i) {
            g_count_mutex1.lock();
            g_count1 += 1;
            g_count_mutex1.unlock();
        }
    });

    std::thread t2([&](){
        for(auto i = 0; i < 500'000'000; ++i) {
            g_count_mutex1.lock();
            g_count1 += 1;
            g_count_mutex1.unlock();
        }
    });

    t1.join();
    t2.join();

    std::cout << g_count1 << std::endl;

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "2 threads: " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();

    unsigned long long g_count2 = 0;
    std::mutex g_count_mutex2;

    std::thread t11([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count_mutex2.lock();
            g_count2 += 1;
            g_count_mutex2.unlock();
        }
    });

    std::thread t12([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count_mutex2.lock();
            g_count2 += 1;
            g_count_mutex2.unlock();
        }
    });

    std::thread t13([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count_mutex2.lock();
            g_count2 += 1;
            g_count_mutex2.unlock();
        }
    });

    std::thread t14([&](){
        for(auto i = 0; i < 250'000'000; ++i) {
            g_count_mutex2.lock();
            g_count2 += 1;
            g_count_mutex2.unlock();
        }
    });

    t11.join();
    t12.join();
    t13.join();
    t14.join();

    std::cout << g_count2 << std::endl;

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "4 threads: " << duration.count() << std::endl;

    return 0;
}