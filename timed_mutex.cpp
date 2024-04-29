#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <sstream>

std::mutex cout_mutex;
std::timed_mutex mutex;

void job(int id) {
    using ms = std::chrono::milliseconds;
    std::ostringstream stream;

    for(int i = 0; i < 3; ++i) {
        if(mutex.try_lock_for(ms(100))) {
            stream << "success ";
            std::this_thread::sleep_for(ms(100));
            mutex.unlock();
        }
        else {
            stream << "failed ";
        }
        std::this_thread::sleep_for(ms(100));
    }
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "[" << id << "]" << stream.str() << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    for(int i = 0; i < 4; i++) {
        threads.emplace_back(job, i);
    }
    
    for(auto& i : threads) {
        i.join();
    }
}