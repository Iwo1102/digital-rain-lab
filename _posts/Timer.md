---
layout: post
title: Timer.h
tags: cpp coding project
categories: demo
---

# Timer
I originally wanted to uses a non-blocking timer so that there wouldn't be a delay when displaying the *drops*.  

## code of Timer.h
```
#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class Timer {
public:
    Timer(size_t time, const std::function<void(void)>& f) : time{ std::chrono::milliseconds{time} }, f{ f } {} 
    ~Timer() { wait_thread.join(); }

private:
    void wait_then_call()
    {
        std::unique_lock<std::mutex> lck{mtx};
        cv.wait_for(lck, time);
        f();
    }
    std::mutex mtx;
    std::condition_variable cv{};
    std::chrono::milliseconds time;
    std::function <void(void)> f;
    std::thread wait_thread{[this]() {wait_then_call(); }};
};


#endif // !TIMER_H
```

## Explanation
The timer is constructed with a blocking time and function you want to delay. When the timer object has been initilised, the thread called `wait_thread` runss `Timer::wait_then_call()` which then waits the set time and then runs the function `f()`
