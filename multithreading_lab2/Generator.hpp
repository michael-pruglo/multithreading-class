//
// Created by Michael on 10/15/17.
//

#ifndef MULTITHREADING_LAB2_GENERATOR_HPP
#define MULTITHREADING_LAB2_GENERATOR_HPP

#include "Task.hpp"
#include "ProcessingManager.hpp"

class Generator
{
    int type;
    int minTime, maxTime;
    int generationsLeft;
    ProcessingManager& processingManager;

    Task generate();
public:
    Generator(ProcessingManager& pm, int type, int generations, int minTime, int maxTime):
            processingManager(pm),
            type(type),
            generationsLeft(generations),
            minTime(minTime),
            maxTime(maxTime)
    {}

    void operator()();
};


#endif //MULTITHREADING_LAB2_GENERATOR_HPP
