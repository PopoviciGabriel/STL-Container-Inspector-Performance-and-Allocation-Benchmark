#pragma once
#include <cstddef>
#include <new>

struct AllocCounter
{
    inline static std::size_t alloc_calls = 0;
    inline static std::size_t bytes_allocated = 0;
    inline static std::size_t dealloc_calls = 0;

    static void reset() {
        alloc_calls = 0;
        bytes_allocated = 0;
        dealloc_calls = 0;
    }
};

template<typename T>
struct CountingAllocator
{
    using value_type = T;
    // Constructor default
    CountingAllocator() noexcept = default;

    // Constructor copiere
    template<class U>
    CountingAllocator(const CountingAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        AllocCounter::alloc_calls++;
        AllocCounter::bytes_allocated += n*sizeof(T);
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, std::size_t) noexcept {
        AllocCounter::dealloc_calls++;
        ::operator delete(p);
    }
};
template<class T, class U>
bool operator==(const CountingAllocator<T>&, const CountingAllocator<U>&){ return true; }
template<class T, class U>
bool operator!=(const CountingAllocator<T>&, const CountingAllocator<U>&){ return false; }