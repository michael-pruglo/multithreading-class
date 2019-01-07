cmake_minimum_required(VERSION 3.9)
project(multithreading_lab4)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "C:/boost_1_66_0")

find_package(Boost 1.57.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()


add_executable(multithreading_lab4 main.cpp producerConsumer/ProducerConsumerDemo.cpp producerConsumer/ProducerConsumerDemo.hpp producerConsumer/Buffer.cpp producerConsumer/Buffer.hpp producerConsumer/Producer.cpp producerConsumer/Producer.hpp producerConsumer/Consumer.cpp producerConsumer/Consumer.hpp readerWriter/readerWriterDemo.cpp readerWriter/readerWriterDemo.hpp diningPhilosophers/diningPhilosophersDemo.hpp util/Semaphore.hpp sleepingBarber/SleepingBarberDemo.cpp sleepingBarber/SleepingBarberDemo.hpp)