//
// Created by Michael on 12/20/17.
//

#include "ProducerConsumerDemo.hpp"
#include "Buffer.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"

void ProducerConsumerDemo::run()
{
    Buffer buffer;
    Producer producer(buffer);
    Consumer consumer(buffer);

    std::thread producer_thread(&Producer::run, &producer);
    std::thread consumer_thread(&Consumer::run, &consumer);

    producer_thread.join();
    consumer_thread.join();
}