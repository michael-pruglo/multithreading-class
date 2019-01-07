//
// Created by Michael on 10/14/17.
//

#include <iostream>
#include "Timer.hpp"

Timer::Timer()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;
}

void Timer::start()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    counterStart = li.QuadPart;
}

void Timer::stop()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    counterStop = li.QuadPart;
}

double Timer::getMilliseconds()
{
    return double(counterStop-counterStart)/PCFreq;
}