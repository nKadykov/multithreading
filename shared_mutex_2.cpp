#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <syncstream>
#include <thread>

class ThreadSafeCounter {
private:
    mutable std::shared_mutex m_mutex;
    unsigned int m_value{};
public:
    ThreadSafeCounter() = default;

    unsigned int get() const {
        std::shared_lock lock(m_mutex);
        return m_value;
    }

    void increment() {
        std::unique_lock lock(m_mutex);
        ++m_value;
    }

    void reset() {
        std::unique_lock lock(m_mutex);
        m_value = 0;
    }
};

int main() {

    ThreadSafeCounter counter;

    auto increment_and_print = [&counter](){
        for(int i{}; i != 3; ++i) {
            counter.increment();
            std::osyncstream(std::cout) << std::this_thread::get_id() << ' ' << counter.get() << std::endl;
        }
    };
}