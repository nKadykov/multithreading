#include <chrono>
#include <iostream>
#include <thread>

void foo() {
    std::this_thread::sleep_for(std::chrono::seconds(4));
}

void bar() {
    std::this_thread::sleep_for(std::chrono::seconds(4));
}

int main() {
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);

    std::cout << "starting second helper...\n";
    std::thread helper2(bar);

    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();

    std::cout << "done!\n";
}