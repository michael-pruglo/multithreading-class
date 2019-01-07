//
// Created by Michael on 12/27/17.
//

#include <iostream>
#include <vector>
#include "mingw.thread.h"
#include "SleepingBarberDemo.hpp"

void SleepingBarberDemo::run()
{
    std::thread barb(&SleepingBarberDemo::barber, this);
    std::vector<std::thread> customers;
    for (int i = 0; i < 10; ++i)
        customers.push_back(std::thread(&SleepingBarberDemo::customer, this));

    barb.join();
    for (auto& x: customers) x.join();
}

void SleepingBarberDemo::barber()
{
    int customersLimit = 10;
    while (customersLimit--)
    {
        custReady.wait();
        accessWRSeats.wait();
        ++numberOfFreeWRSeats;
        barberReady.notify();
        accessWRSeats.notify();
        //cut hair
    }
}

void SleepingBarberDemo::customer()
{
    accessWRSeats.wait();
    if (numberOfFreeWRSeats == 0)
        accessWRSeats.notify();
        //leave
    else
    {
        --numberOfFreeWRSeats;
        custReady.notify();
        accessWRSeats.notify();
        barberReady.wait();
        //get hair cut
    }
}
