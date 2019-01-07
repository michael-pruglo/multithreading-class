//
// Created by Michael on 10/15/17.
//

#ifndef MULTITHREADING_LAB2_PROCESSOR_HPP
#define MULTITHREADING_LAB2_PROCESSOR_HPP

#include <iostream>
#include <mutex>
#include "Task.hpp"
#include "util/Random.hpp"
#include "mingw.thread.h"
#include "mingw.condition_variable.h"

class Processor
{
    int minProcessingTime, maxProcessingTime;
    int status; //0 = free, 1 = processing type 1, 2 = processing type 2
    std::condition_variable timeToInterrupt;
    std::mutex procMutex;
    Task currentTask;
public:

    Processor(int minProcessingTime, int maxProcessingTime):
            minProcessingTime(minProcessingTime),
            maxProcessingTime(maxProcessingTime),
            status(0),
            currentTask(-1, -1)
    {}
    void compute(const Task& task)
    {
        std::cout<<"\t\t[PROCESSOR]Processing task "<<task.getType()<<"["<<task.getId()<<"]\n";
        currentTask = task;
        status = task.getType();
        std::unique_lock<std::mutex> guard(procMutex);
        timeToInterrupt.wait_for(guard,
                                 std::chrono::milliseconds(Random::getInt(minProcessingTime, maxProcessingTime)));
        status = 0;
        std::cout<<"\t\t[PROCESSOR] ... finished"<<task.getType()<<"\n";
    }
    int getStatus() const {return status;}
    Task interrupt()
    {
        timeToInterrupt.notify_all();
        std::cout<<"\t\t[PROCESSOR]Interrupt processing "<<currentTask.getType()<<"["<<currentTask.getId()<<"]\n";
        return currentTask;
    }
};


#endif //MULTITHREADING_LAB2_PROCESSOR_HPP
