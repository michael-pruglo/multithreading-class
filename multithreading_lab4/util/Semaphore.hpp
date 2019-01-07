//
// Created by Michael on 12/27/17.
//

#ifndef MULTITHREADING_LAB4_SEMAPHORE_HPP
#define MULTITHREADING_LAB4_SEMAPHORE_HPP

#include <mutex>
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"

class Semaphore
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore (int count_ = 0)
            : count(count_) {}

    inline void notify()
    {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    inline void wait()
    {
        std::unique_lock<std::mutex> lock(mtx);
        while(count == 0)
            cv.wait(lock);
        count--;
    }
};


#endif //MULTITHREADING_LAB4_SEMAPHORE_HPP
