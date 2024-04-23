#include <iostream>
#include <mutex>
#include <thread>

double val = 0;

std::mutex m;

int count = 0;

void add(double num) {
    m.lock();
    val += num;
    count++;
    std::cout << "Thread " << count << ": " << val << std::endl;
    m.unlock();
}

int main() {
    std::thread t1(add, 300);
    std::thread t2(add, 600);
    t1.join();
    t2.join();
    std::cout << "After addition: " << val << std::endl;
    return 0;
}