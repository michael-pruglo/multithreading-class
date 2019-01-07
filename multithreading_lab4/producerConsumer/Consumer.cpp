//
// Created by Michael on 12/20/17.
//

#include <iostream>
#include "Consumer.hpp"
#include "mingw.thread.h"

void Consumer::run()
{
    std::mutex cout_mu;
    for (int i = 0; i < 10; ++i)
    {
        int num = buffer.remove();
        cout_mu.lock();
        std::cout << "Consumed: " << num << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cout_mu.unlock();
    }

}
