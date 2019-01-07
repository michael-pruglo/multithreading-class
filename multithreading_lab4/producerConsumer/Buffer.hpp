//
// Created by Michael on 12/20/17.
//

#ifndef MULTITHREADING_LAB4_BUFFER_HPP
#define MULTITHREADING_LAB4_BUFFER_HPP


#include <deque>
#include <mutex>
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"

class Buffer
{
public:
    void add(int num);
    int remove();
private:
    std::mutex mu;
    std::condition_variable cond;

    std::deque<int> buffer;
    const unsigned int size = 10;
};


#endif //MULTITHREADING_LAB4_BUFFER_HPP
