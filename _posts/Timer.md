---
layout: post
title: Timer.h
tags: cpp coding project
categories: demo
---

# Explanation
I originally wanted to uses a non-blocking timer so that there wouldn't be a delay when displaying the *drops*.  

## code of Timer.h:
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

# Desired Features:

Radomise character string:
rand and convert to ascii

Every 0.1 seconds a new line is created in a random position with a random length

The line does down 1 y position every 0.5 seconds with and once line length is reached it starts deleting top most characters
After y = 0 characters delete

object array where 1 object is a line and deletes itself once all characters are deleted

Change character colour with lowest being brightest

30% chance that the characters in the middle of the string change every 0.5 seconds
