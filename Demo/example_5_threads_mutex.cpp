// use compiler flag -pthread
#include <iostream>
#include <mutex>
#include <thread>
std::mutex mutex;

class Guard {
   public:
    explicit Guard(std::mutex &mut) : _mutex(mut) {
        // lock mutex object
        _mutex.lock();
        std::cout << "Mutex locked" << std::endl;
    }
    ~Guard() {
        // unlock mutex object
        _mutex.unlock();
        std::cout << "Mutex unlocked" << std::endl;
    }

   private:
    std::mutex &_mutex;
};
void printBlock(int n, char c) {
    // when g goes out of scope, its deconstructor is called.
    // Thus, the mutex will be unlocked
    Guard g = Guard(mutex);
    for (int i = 0; i < n; ++i) {
        std::cout << c;
    }
    std::cout << '\n';
}
int main() {
    std::thread thread1(printBlock, 250, '|');
    std::thread thread2(printBlock, 250, '-');

    thread1.join();
    thread2.join();
    return 0;
}