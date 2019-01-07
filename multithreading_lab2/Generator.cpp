//
// Created by Michael on 10/15/17.
//

#include <iostream>
#include "Generator.hpp"

void Generator::operator()()
{
    while (generationsLeft != 0)
    {
        std::mutex mutex;
        std::lock_guard<std::mutex> guard(mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(Random::getInt(minTime, maxTime)));
        std::cout<<"add task "<<type<<"["<<generationsLeft<<"] - ";
        processingManager.addTask(generate());
        --generationsLeft;
    }
    if (type==1)
        processingManager.finished1();
    else
        processingManager.finished2();
}

Task Generator::generate()
{
    return {type, generationsLeft};
}
