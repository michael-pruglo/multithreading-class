//
// Created by Michael on 10/14/17.
//

#include "Test.hpp"
#include "util/Timer.hpp"

void Test::printResults(const std::string& header, double result, double ms)
{
    std::cout<<header<<"\n";
    std::cout<<"\tresult: "<<result<<"\n";
    std::cout<<"\ttime:   "<<ms<<" ms\n";
}

void Test::run(const std::string& header,
               double (*calcFunction)(const std::vector<double>&, const std::vector<double>&, int))
{
    Timer timer;
    timer.start();

    double result = calcFunction(A, B, VECTOR_SIZE);

    timer.stop();
    printResults(header, result, timer.getMilliseconds());
}