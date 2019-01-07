//
// Created by Michael on 10/15/17.
//

#ifndef MULTITHREADING_LAB2_RANDOM_HPP
#define MULTITHREADING_LAB2_RANDOM_HPP


#include <cstdlib>

class Random
{
public:
    static int getInt(int lower, int upper)
    {
        return lower + rand() % (upper - lower + 1);
    }
};


#endif //MULTITHREADING_LAB2_RANDOM_HPP
