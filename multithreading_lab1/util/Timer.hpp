//
// Created by Michael on 10/14/17.
//

#ifndef MULTITHREADING_LAB1_TIMER_HPP
#define MULTITHREADING_LAB1_TIMER_HPP

#include <windows.h>

class Timer
{
    double PCFreq = 0.0;
    __int64 counterStart = 0;
    __int64 counterStop = 0;

public:
    Timer();

public:
    void start();
    void stop();
    double getMilliseconds();
};


#endif //MULTITHREADING_LAB1_TIMER_HPP
