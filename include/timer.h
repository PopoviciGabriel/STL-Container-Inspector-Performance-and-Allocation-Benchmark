#pragma once
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

template<typename T>
long long time_us(T&& t) {
    auto start = Clock::now();
    t();
    auto end = Clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}