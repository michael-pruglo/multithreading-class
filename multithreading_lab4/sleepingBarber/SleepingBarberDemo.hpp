//
// Created by Michael on 12/27/17.
//

#ifndef MULTITHREADING_LAB4_SLEEPINGBARBERDEMO_HPP
#define MULTITHREADING_LAB4_SLEEPINGBARBERDEMO_HPP


#include "../util/Semaphore.hpp"

class SleepingBarberDemo
{
    Semaphore barberReady;
    Semaphore accessWRSeats;
    Semaphore custReady;
    int numberOfFreeWRSeats;

    void barber();
    void customer();
public:
    SleepingBarberDemo()
            : barberReady(0),
              accessWRSeats(1),
              custReady(0),
              numberOfFreeWRSeats(4) {}
    void run();
};


#endif //MULTITHREADING_LAB4_SLEEPINGBARBERDEMO_HPP
