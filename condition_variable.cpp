#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::condition_variable cv;
std::mutex m;

int val = 0;

void add(int num) {
    std::lock_guard<std::mutex> lock(m);
    val += num;
    std::cout << "After addition: " << val << std::endl;
    cv.notify_one();
}

void sub(int num) {
    std::unique_lock<std::mutex> ulock(m);
    cv.wait(ulock, []{ return (val != 0) ? true : false; });
    if(val >= num) {
        val -= num;
        std::cout << "After subtraction: " << val << std::endl;
    }
    else {
        std::cout << "Cannot substract now!" << std::endl;
    }
}

int main() {
    std::thread t2(sub, 600);
    std::thread t1(add, 900);

    t1.join();
    t2.join();

    return 0;
}