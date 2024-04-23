#include <iostream>
#include <thread>

void doWork() {
    for(int i = 0; i < 5; i++) {

        std::cout << "ID: " << std::this_thread::get_id() << " Do work" <<  std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {

    doWork();
    std::thread t(doWork);

    for(int i = 0; i < 5; i++) {
        std::cout << "ID: " << std::this_thread::get_id() << " main" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    t.join();
    return 0;
}