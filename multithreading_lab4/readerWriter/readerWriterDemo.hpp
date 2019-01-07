//
// Created by Michael on 12/20/17.
//

#ifndef MULTITHREADING_LAB4_READERWRITERDEMO_HPP
#define MULTITHREADING_LAB4_READERWRITERDEMO_HPP

#include <mutex>
//#include "boost/thread/shared_mutex.hpp"
#include "mingw.thread.h"
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"

class readerWriterDemo
{
};

/*
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex sm;
int resourse = 5;

void write(int value)
{
    std::shared_lock<std::shared_mutex> lock(sm);
    resourse = value;
}
int read()
{
    std::unique_lock<std::shared_mutex> lock(sm);
    return resourse;
}

int main()
{
    std::vector<std::thread> readers(5), writers(50);
    for (int i = 0; i < readers.size(); ++i)
        readers[i] = std::thread(read);
    for (int i = 0; i < writers.size(); ++i)
        writers[i] = std::thread(write, i);

    for (auto& x: readers) x.join();
    for (auto& x: writers) x.join();
}
 */


#endif //MULTITHREADING_LAB4_READERWRITERDEMO_HPP
