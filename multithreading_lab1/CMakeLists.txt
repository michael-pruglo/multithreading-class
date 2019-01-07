cmake_minimum_required(VERSION 3.8)
project(multithreading_lab1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp util/Timer.cpp util/Timer.hpp Test.cpp Test.hpp)
add_executable(multithreading_lab1 ${SOURCE_FILES})