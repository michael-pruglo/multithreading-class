//
// Created by Michael on 12/21/17.
//

#ifndef MULTITHREADING_LAB4_DININGPHILOSOPHERSDEMO_HPP
#define MULTITHREADING_LAB4_DININGPHILOSOPHERSDEMO_HPP

#include <iostream>
#include <mutex>
#include <algorithm>
#include <vector>
#include <sstream>
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"
#include "mingw.thread.h"

struct Chopstick { std::mutex m; };

class diningPhilosophersDemo
{
public:
    void run()
    {
        auto eat = [](Chopstick* leftChopstick, Chopstick* rightChopstick, int philosopherNumber, int leftChopstickNumber, int rightChopstickNumber)
        {
            if (leftChopstick == rightChopstick)
                throw std::exception();

            lock(leftChopstick->m, rightChopstick->m);

            std::lock_guard<std::mutex> a(leftChopstick->m, std::adopt_lock);
            std::stringstream sl; sl<< "   Philosopher "<<philosopherNumber<<" picked " <<leftChopstickNumber<<" chopstick.\n";
            std::cout << sl.str();

            std::lock_guard<std::mutex> b(rightChopstick->m, std::adopt_lock);
            std::stringstream sr; sr<<"   Philosopher "<<philosopherNumber<<" picked "<<rightChopstickNumber<<" chopstick.\n";
            std::cout << sr.str();

            std::stringstream pe; pe<<"Philosopher "<<philosopherNumber<<" eats.\n";
            std::cout << pe.str();
        };

        static const int numPhilosophers = 5;

        std::vector< std::unique_ptr<Chopstick> > chopsticks(numPhilosophers);

        for (int i = 0; i < numPhilosophers; ++i)
        {
            auto c1 = std::unique_ptr<Chopstick>(new Chopstick());
            chopsticks[i] = move(c1);
        }

        std::vector<std::thread> tasks(numPhilosophers);

        tasks[0] = std::thread(eat,
                          chopsticks[0].get(),
                          chopsticks[numPhilosophers - 1].get(),
                          0 + 1,
                          1,
                          numPhilosophers
        );

        for (int i = 1; i < numPhilosophers; ++i)
        {
            tasks[i] = std::thread(eat,
                               chopsticks[i - 1].get(),
                               chopsticks[i].get(),
                               i + 1,
                               i,
                               i + 1
            );
        }

        for_each(tasks.begin(), tasks.end(), std::mem_fn(&std::thread::join));
    }
};


#endif //MULTITHREADING_LAB4_DININGPHILOSOPHERSDEMO_HPP
