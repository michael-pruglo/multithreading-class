//
// Created by Michael on 10/15/17.
//

#ifndef MULTITHREADING_LAB2_PROCESSINGMANAGER_HPP
#define MULTITHREADING_LAB2_PROCESSINGMANAGER_HPP

#include <deque>
#include "Processor.hpp"
#include "Task.hpp"
#include "mingw.thread.h"
#include "mingw.mutex.h"

class ProcessingManager
{
    Processor cpu;
    std::deque<Task> cpuQueue;
    std::thread processorThread;
    std::mutex processingMutex;
    bool fin1 = false, fin2 = false;

    int processedTasks1 = 0, processedTasks2 = 0;
    int destroyedTasks1 = 0;
    int interruptedTasks2 = 0;
    int maxQueueLen = 0;

    void runProcessing();

    void showQueue();
public:
    ProcessingManager(int minProcessingTime, int maxProcessingTime):
            cpu(minProcessingTime, maxProcessingTime)
    {
        processorThread = std::thread(&ProcessingManager::runProcessing, this);
    }
    ~ProcessingManager()
    {
        processorThread.join();
        std::cout<<"Statistics:\n";
        std::cout<<"  processed tasks: "<<processedTasks1<<"\t\t"<<processedTasks2<<"\n";
        std::cout<<"  destroyed tasks: "<<destroyedTasks1<<"("<<(100.0*destroyedTasks1/(processedTasks1+destroyedTasks1))<<"%)\n";
        std::cout<<"  interrupted tasks: "<<interruptedTasks2<<"\n";
        std::cout<<"  max queue length: "<<maxQueueLen<<"\n";
    }
    void addTask(const Task& task);
    bool finished1() {fin1 = true;}
    bool finished2() {fin2 = true;}
};


#endif //MULTITHREADING_LAB2_PROCESSINGMANAGER_HPP
