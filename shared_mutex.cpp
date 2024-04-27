#include <iostream>
#include <mutex>
#include <thread>
#include <shared_mutex>

std::shared_mutex shared_mutex;
int shared_data = 11;

void readData() {
    std::shared_lock<std::shared_mutex> lock(shared_mutex);
    std::cout << "Thread " << std::this_thread::get_id() << ": ";
    std::cout << shared_data << std::endl;
}

void writeData(int n) {
    std::unique_lock<std::shared_mutex> lock(shared_mutex);
    shared_data = n;
    std::cout << "Thread " << std::this_thread::get_id() << ": \n";
}

int main() {
    
    std::thread t1(readData);
    std::thread t2(writeData, 128);
    std::thread t3(writeData, 10);
    std::thread t4(readData);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}