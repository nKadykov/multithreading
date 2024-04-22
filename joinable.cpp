#include <iostream>
#include <thread>

void thread_function() {
    for(int i = 0; i < 2; i++) {
        std::cout << "Thread function Executing" << std::endl;
    }
}

int main() {
    std::thread threadObj(thread_function);

    for(int i = 0; i < 10; i++) {
        std::cout << "Display from main thread" << std::endl;
    }

    threadObj.detach();

    if(threadObj.joinable()) {
        threadObj.join();
        std::cout << "Thread is joined" << std::endl;
    }
    else {
        std::cout << "Thread is not joinable" << std::endl;
    }

    std::cout << "Exit of main function" << std::endl;

    return 0;
}