cmake_minimum_required(VERSION 3.8)
project(multithreading_lab2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp ProcessingManager.cpp ProcessingManager.hpp Task.hpp Generator.cpp Generator.hpp Processor.hpp util/Random.hpp)
add_executable(multithreading_lab2 ${SOURCE_FILES})