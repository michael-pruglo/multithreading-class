//
// Created by Michael on 10/14/17.
//

#ifndef MULTITHREADING_LAB1_TEST_HPP
#define MULTITHREADING_LAB1_TEST_HPP

#include <vector>
#include <iostream>

class Test
{
    const unsigned int VECTOR_SIZE = 100000;
    const std::vector<double> A = std::vector<double>(VECTOR_SIZE, 3.1415);
    const std::vector<double> B = std::vector<double>(VECTOR_SIZE, 2.7183);

    void printResults(const std::string& header, double result, double ms);

public:
    void run(const std::string& header,
             double (*calcFunction)(const std::vector<double>&, const std::vector<double>&, int));
};


#endif //MULTITHREADING_LAB1_TEST_HPP
