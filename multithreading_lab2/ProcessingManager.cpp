//
// Created by Michael on 10/15/17.
//

//#include <mutex>
#include "ProcessingManager.hpp"

void ProcessingManager::addTask(const Task& task)
{
    std::lock_guard<std::mutex> guard(processingMutex);
    if (task.getType() == 2)
    {
        std::cout<<"adding case 2\n";
        cpuQueue.push_back(task);
        maxQueueLen = std::max(maxQueueLen, (int)cpuQueue.size());
    }
    else
    {
        switch (cpu.getStatus())
        {
            case 0:
                if (cpuQueue.empty())
                {
                    std::cout<<"adding case 1 in idle empty\n";
                    cpuQueue.push_front(task);
                    maxQueueLen = std::max(maxQueueLen, (int)cpuQueue.size());
                }
                else if (cpuQueue.front().getType() == 1)
                {
                    std::cout<<"adding case 1 in idle, 1 next in queue\n";
                    ++destroyedTasks1;
                    std::cout<<"skip\n";
                    showQueue();
                }
                else
                {
                    std::cout<<"adding case 1 in idle, 2 next in queue\n";
                    cpuQueue.push_front(task);
                    maxQueueLen = std::max(maxQueueLen, (int)cpuQueue.size());
                }
                break;
            case 1:
                ++destroyedTasks1;
                std::cout<<"skip\n";
                showQueue();
                return;
            case 2:
                std::cout<<"adding case 1 interrupt\n";
                {
                    Task interrupted = cpu.interrupt();
                    cpuQueue.push_front(interrupted);
                    cpuQueue.push_front(task);
                }
                ++interruptedTasks2;
                --processedTasks2;
                maxQueueLen = std::max(maxQueueLen, (int)cpuQueue.size());
                break;
            default:break;
        }
    }
    showQueue();
}

void ProcessingManager::runProcessing()
{
    while (!(fin1&&fin2&&cpuQueue.empty()))
    {
        processingMutex.lock();
        if (!cpuQueue.empty())
        {
            Task currentTask = cpuQueue.front();
            cpuQueue.pop_front();
            showQueue();
            processingMutex.unlock();
            cpu.compute(currentTask);
            processingMutex.lock();
            showQueue();
            ++(currentTask.getType()==1?processedTasks1:processedTasks2);
        }
        processingMutex.unlock();
    }
}

void ProcessingManager::showQueue()
{
    if (cpuQueue.empty())
        std::cout<<"\tQUEUE EMPTY\n\n";
    else
    {
        std::cout<<"\t"; for (auto& x: cpuQueue) std::cout<<x.getType()<<"["<<x.getId()<<"]  "; std::cout<<"\n\n";
    }
}


