//
// Created by Michael on 12/20/17.
//

#ifndef MULTITHREADING_LAB4_CONSUMER_HPP
#define MULTITHREADING_LAB4_CONSUMER_HPP


#include "Buffer.hpp"

class Consumer
{
public:
    explicit Consumer(Buffer& buf) : buffer(buf) {}
    void run();

private:
    Buffer& buffer;
};


#endif //MULTITHREADING_LAB4_CONSUMER_HPP
