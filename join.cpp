#include <iostream>
#include <thread>

void thread_function() {
    for(int i = 0; i < 20; i++) {
        std::cout << "Thread function Execution" << std::endl;
    }
}

int main() {
    std::thread threadObj(thread_function);

    for(int i = 0; i < 10; i++) {
        std::cout << "Display from main thread" << std::endl;
    }
    threadObj.join();
    std::cout << "Exit of main function" << std::endl;
    return 0;
}