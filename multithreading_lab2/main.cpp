#include <iostream>
#include "mingw.thread.h"
#include "Generator.hpp"

int main()
{
    ProcessingManager processingManager(200, 400);
    std::thread generator1( (Generator(processingManager, 1, 15, 200, 700)) );
    std::thread generator2( (Generator(processingManager, 2, 17, 100, 300)) );

    generator1.join();
    generator2.join();

    return 0;
}