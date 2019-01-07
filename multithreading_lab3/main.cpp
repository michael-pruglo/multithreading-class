#include <iostream>
#include <vector>
#include "mingw.thread.h"
#include <atomic>

typedef std::vector<int> Vect;
void par_sum(const Vect& a, std::atomic<long long>& sum);
void par_conditionalQuantity(const Vect& a, std::atomic<long long>& cond_quantity);
void par_minIndex(const Vect& a, std::atomic<long long>& minI);
void par_maxIndex(const Vect& a, std::atomic<long long>& maxI);
void par_checksum(const Vect& a, std::atomic<long long>& checksum);

int main()
{
    const int SIZE = 1000000;
    Vect a(SIZE);
    for (auto& x: a) x = rand();
    std::atomic<long long> sum(0), cond_quantity(0), minI(0), maxI(0), checksum(0);

    std::thread sum_thread(par_sum, a, std::ref(sum)),
                condQuantity_thread(par_conditionalQuantity, a, std::ref(cond_quantity)),
                minIndex_thread(par_minIndex, a, std::ref(minI)),
                maxIndex_thread(par_maxIndex, a, std::ref(maxI)),
                checksum_thread(par_checksum, a, std::ref(checksum));

    sum_thread.join();
    condQuantity_thread.join();
    minIndex_thread.join();
    maxIndex_thread.join();
    checksum_thread.join();

    std::cout<<"The sum of the elements: "<<sum<<std::endl;
    std::cout<<"Quantity of elements less than 5: "<<cond_quantity<<std::endl;
    std::cout<<"The minimal of the elements: a["<<minI<<"] = "<<a[minI]<<std::endl;
    std::cout<<"The maximum of the elements: a["<<maxI<<"] = "<<a[maxI]<<std::endl;
    std::cout<<"The checksum of the elements: "<<checksum<<std::endl;
}

long long partial_sum(const Vect& a, int begin, int end)
{
    int result = 0;
    for (int i = begin; i < end; ++i)
        result += a[i];
    return result;
}
void par_sum(const Vect& a, std::atomic<long long>& sum)
{
    const int NUMBER_OF_THREADS = 10;
    std::vector<std::thread> threadsVector(NUMBER_OF_THREADS);

    int chunkSize = a.size()/NUMBER_OF_THREADS;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i] = std::thread([&, i](){
            sum += partial_sum(a,
                                i*chunkSize,
                                i == NUMBER_OF_THREADS-1 ? a.size() : (i+1)*chunkSize);
        });

    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i].join();
}

int partial_conditionalQuantity(const Vect& a, int begin, int end)
{
    int result = 0;
    for (int i = begin; i < end; ++i)
        result += a[i] < 5;
    return result;
}
void par_conditionalQuantity(const Vect& a, std::atomic<long long>& cond_quantity)
{
    const int NUMBER_OF_THREADS = 10;
    std::vector<std::thread> threadsVector(NUMBER_OF_THREADS);

    int chunkSize = a.size()/NUMBER_OF_THREADS;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i] = std::thread([&, i](){
            cond_quantity += partial_conditionalQuantity(a,
                               i*chunkSize,
                               i == NUMBER_OF_THREADS-1 ? a.size() : (i+1)*chunkSize);
        });

    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i].join();
}

int partial_minIndex(const Vect& a, int begin, int end)
{
    int result = begin;
    for (int i = begin+1; i < end; ++i)
        if (a[result] > a[i])
            result = i;
    return result;
}
void par_minIndex(const Vect& a, std::atomic<long long>& minI)
{
    const int NUMBER_OF_THREADS = 10;
    std::vector<std::thread> threadsVector(NUMBER_OF_THREADS);

    int chunkSize = a.size()/NUMBER_OF_THREADS;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i] = std::thread([&, i](){
            int tempMinI = partial_minIndex(a,
                                             i*chunkSize,
                                             i == NUMBER_OF_THREADS-1 ? a.size() : (i+1)*chunkSize);
            if (a[minI] > a[tempMinI])
                minI = tempMinI;
        });

    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i].join();
}

int partial_maxIndex(const Vect& a, int begin, int end)
{
    int result = begin;
    for (int i = begin+1; i < end; ++i)
        if (a[result] < a[i])
            result = i;
    return result;
}
void par_maxIndex(const Vect& a, std::atomic<long long>& maxI)
{
    const int NUMBER_OF_THREADS = 10;
    std::vector<std::thread> threadsVector(NUMBER_OF_THREADS);

    int chunkSize = a.size()/NUMBER_OF_THREADS;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i] = std::thread([&, i](){
            int tempMaxI = partial_maxIndex(a,
                                            i*chunkSize,
                                            i == NUMBER_OF_THREADS-1 ? a.size() : (i+1)*chunkSize);
            if (a[maxI] < a[tempMaxI])
                maxI = tempMaxI;
        });

    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i].join();
}

int partial_checksum(const Vect& a, int begin, int end)
{
    int result = 0;
    for (int i = begin; i < end; ++i)
        result ^= a[i];
    return result;
}
void par_checksum(const Vect& a, std::atomic<long long>& checksum)
{
    const int NUMBER_OF_THREADS = 10;
    std::vector<std::thread> threadsVector(NUMBER_OF_THREADS);

    int chunkSize = a.size()/NUMBER_OF_THREADS;
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i] = std::thread([&, i](){
            checksum ^= partial_checksum(a,
                               i*chunkSize,
                               i == NUMBER_OF_THREADS-1 ? a.size() : (i+1)*chunkSize);
        });

    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        threadsVector[i].join();
}


