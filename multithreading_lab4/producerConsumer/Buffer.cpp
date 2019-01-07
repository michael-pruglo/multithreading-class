//
// Created by Michael on 12/20/17.
//

#include <mutex>
#include "Buffer.hpp"

void Buffer::add(int num)
{
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [this](){return buffer.size() < size;});
    buffer.push_back(num);
    locker.unlock();
    cond.notify_all();
}

int Buffer::remove()
{
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [this](){return buffer.size() > 0;});
    int back = buffer.back();
    buffer.pop_back();
    locker.unlock();
    cond.notify_all();
    return back;
}
