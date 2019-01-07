//
// Created by Michael on 12/20/17.
//

#ifndef MULTITHREADING_LAB4_PRODUCER_HPP
#define MULTITHREADING_LAB4_PRODUCER_HPP

#include <iostream>
#include "mingw.thread.h"
#include "Buffer.hpp"

class Producer
{
public:
    explicit Producer(Buffer& buf) : buffer(buf) {}
    void run();

private:
    Buffer& buffer;
};


#endif //MULTITHREADING_LAB4_PRODUCER_HPP
