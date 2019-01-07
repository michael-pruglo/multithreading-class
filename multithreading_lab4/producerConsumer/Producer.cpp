//
// Created by Michael on 12/20/17.
//

#include "Producer.hpp"

void Producer::run()
{
    std::mutex cout_mu;
    for (int i = 0; i < 10; ++i)
    {
        int num = rand() % 100;
        buffer.add(num);
        cout_mu.lock();
        std::cout << "Produced: " << num << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cout_mu.unlock();
    }
}
