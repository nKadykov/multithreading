#include <future>
#include <iostream>
#include <thread>

void EvenNosFind(std::promise<int>&& EvenPromise, int begin, int end) {
    int evenNo = 0;
    for(int i = begin; i <= end; i++) {
        if(i % 2 == 0) {
            evenNo += 1;
        }
    }
    EvenPromise.set_value(evenNo);
}

int main() {
    int begin = 0;
    int end = 1000;
    std::promise<int> evenNo;
    std::future<int> evenFuture = evenNo.get_future();
    std::cout << "My thread is created!!!" << std::endl;
    std::thread t1(EvenNosFind, std::move(evenNo), begin, end);
    std::cout << "Waiting........" << std::endl;

    std::cout << "The no. of even numbers are: " << evenFuture.get() << std::endl;

    t1.join();
    
    return 0;
}