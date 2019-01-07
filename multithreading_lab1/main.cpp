#include "mingw.thread.h"
#include "Test.hpp"

typedef const std::vector<double>& Vect;
double scalarProductSerial(Vect a, Vect b, int size);
double scalarProductParallel(Vect a, Vect b, int size);
double scalarProduct(Vect a, Vect b, int begin, int end);

int main()
{
    Test test;
    test.run("Serial", scalarProductSerial);
    test.run("Parallel", scalarProductParallel);

    return 0;
}

double scalarProductSerial(Vect a, Vect b, int size)
{
    return scalarProduct(a, b, 0, size);
}

double scalarProductParallel(Vect a, Vect b, int size)
{
    const int NUMBER_OF_THREADS = 7;
    std::vector<std::thread> threadsVector(NUMBER_OF_THREADS);

    int chunkSize = size/NUMBER_OF_THREADS;
    double result = 0;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i] = std::thread([&, i](){
            result += scalarProduct(a, b,
                                    i*chunkSize,
                                    i == NUMBER_OF_THREADS-1 ? size : (i+1)*chunkSize);
        });

    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i].join();

    return result;
}

double scalarProduct(Vect a, Vect b, int begin, int end)
{
    double result = 0;
    for (int i = begin; i < end; ++i)
        result += a[i]*b[i];
    return result;
}
