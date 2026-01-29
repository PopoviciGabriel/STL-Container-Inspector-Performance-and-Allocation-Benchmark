#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <list>
#include <unordered_map>
#include <utility>

#include "counting_allocator.h"
#include "timer.h"
#include "keys.h"
#include "iterator_rules.h"

int main()
{
    print_iterator_invalidation_rules();
    constexpr int N = 1'000'000;
    constexpr int M = 5'000;
    constexpr int L = 100'000;
    constexpr int R = 200'000;
    auto keys = make_keys(N, M);

    // -------------------
    //     std::vector
    // -------------------
    {
    std::vector<int, CountingAllocator<int>> v;
    std::cout << "--- Vector ---\n";

    AllocCounter::reset();
    v.reserve(N); // fara reverse timpul va fi mai mare, dar nu cu mult
    auto push_time = time_us([&]{
        for(int i=0; i<N; i++) v.push_back(i);
    });
    std::cout << "Push duration: " << push_time
              << " | alloc_calls = " << AllocCounter::alloc_calls
              << " | dealloc_calls = " << AllocCounter::dealloc_calls 
              << " | bytes = " << AllocCounter::bytes_allocated << "\n";

    AllocCounter::reset();
    volatile long long sink = 0; // ca sa nu optimizeze compilatorul
    auto find_time = time_us([&]{
        for (int key : keys) {
            auto it = std::find(v.begin(), v.end(), key);
            if (it != v.end()) sink += *it;
        }
    });
    std::cout << "Find duration: " << find_time
          << " | alloc_calls = " << AllocCounter::alloc_calls
          << " | dealloc_calls = " << AllocCounter::dealloc_calls
          << " | bytes = " << AllocCounter::bytes_allocated << "\n";

    AllocCounter::reset();
    auto erase_range_time = time_us([&]{
        v.erase(v.begin() + L, v.begin() + R);
    });
    std::cout << "Erase range duration: " << erase_range_time
              << " | alloc_calls = " << AllocCounter::alloc_calls
              << " | dealloc_calls = " << AllocCounter::dealloc_calls 
              << " | bytes = " << AllocCounter::bytes_allocated << "\n";
    std::cout << "\n";
    }
    

    // --------------------
    //      std::deque     
    // --------------------
    {
    AllocCounter::reset();
    std::deque<int, CountingAllocator<int>> d;
    std::cout << "--- Deque ---\n";

    auto push_time = time_us([&]{
        for(int i=0; i<N; i++) 
            d.push_back(i);
    });
    std::cout << "Push duration: " << push_time
              << " | alloc_calls = " << AllocCounter::alloc_calls
              << " | dealloc_calls = " << AllocCounter::dealloc_calls 
              << " | bytes = " << AllocCounter::bytes_allocated << "\n";

    AllocCounter::reset();
    volatile long long sink = 0; // ca sa nu optimizeze compilatorul
    auto find_time = time_us([&]{
        for (int key : keys) {
            auto it = std::find(d.begin(), d.end(), key);
            if (it != d.end()) sink += *it;
        }
    });
    std::cout << "Find duration: " << find_time
          << " | alloc_calls = " << AllocCounter::alloc_calls
          << " | dealloc_calls = " << AllocCounter::dealloc_calls
          << " | bytes = " << AllocCounter::bytes_allocated << "\n";
    
    AllocCounter::reset();
    auto erase_range_duration = time_us([&]{
        d.erase(d.begin() + L, d.begin() + R);
    });
    std::cout << "Erase range duration: " << erase_range_duration
          << " | alloc_calls = " << AllocCounter::alloc_calls
          << " | dealloc_calls = " << AllocCounter::dealloc_calls
          << " | bytes = " << AllocCounter::bytes_allocated << "\n";
    std::cout << "\n";  
    }

    // -------------------
    //      std::list     
    // -------------------
    {
    AllocCounter::reset();
    std::list<int, CountingAllocator<int>> l;
    std::cout << "--- List ---\n";

    auto push_time = time_us([&]{
        for(int i=0; i<N; i++) l.push_back(i);
    });
    std::cout << "Push duration: " << push_time
              << " | alloc_calls = " << AllocCounter::alloc_calls
              << " | dealloc_calls = " << AllocCounter::dealloc_calls 
              << " | bytes = " << AllocCounter::bytes_allocated << "\n";

    AllocCounter::reset();
    volatile long long sink = 0; // ca sa nu optimizeze compilatorul
    auto find_time = time_us([&]{
        for (int key : keys) {
            auto it = std::find(l.begin(), l.end(), key);
            if (it != l.end()) sink += *it;
        }
    });
    std::cout << "Find duration: " << find_time
          << " | alloc_calls = " << AllocCounter::alloc_calls
          << " | dealloc_calls = " << AllocCounter::dealloc_calls
          << " | bytes = " << AllocCounter::bytes_allocated << "\n";

    // Costul la std::list de a ajunge la it1/it2 cu advance e mare
    // De aceea nu l includem in erase range
    auto it1 = l.begin();
    auto it2 = l.begin();

    auto adv_time = time_us([&]{
        std::advance(it1, L);
        std::advance(it2, R);
    });

    AllocCounter::reset();
    auto erase_range_time = time_us([&]{
        l.erase(it1, it2);
    });
    std::cout << "Advance duration: " << adv_time << "\n";
    std::cout << "Erase range duration: " << erase_range_time
          << " | alloc_calls = " << AllocCounter::alloc_calls
          << " | dealloc_calls = " << AllocCounter::dealloc_calls
          << " | bytes = " << AllocCounter::bytes_allocated << "\n";
    std::cout << "\n";
    }

    // ----------------------------
    //      std::unordered_map     
    // ----------------------------
    {
    AllocCounter::reset();
    using Pair = std::pair<const int, int>;
    std::unordered_map<int, int, std::hash<int>, std::equal_to<int>, CountingAllocator<Pair>> m;
    std::cout << "--- Unordered_map ---\n";

    auto push_time = time_us([&]{
        m.reserve(N);
        for(int i=0; i<N; i++) m.emplace(i, i);
    });
    std::cout << "Push duration: " << push_time
              << " | alloc_calls = " << AllocCounter::alloc_calls
              << " | dealloc_calls = " << AllocCounter::dealloc_calls 
              << " | bytes = " << AllocCounter::bytes_allocated << "\n";

    AllocCounter::reset();
    volatile long long sink = 0; // ca sa nu optimizeze compilatorul
    auto find_time = time_us([&]{
        for (int key : keys) {
            auto it = m.find(key);
            if (it != m.end()) sink += it->second;
        }
    });
    std::cout << "Find duration: " << find_time
          << " | alloc_calls = " << AllocCounter::alloc_calls
          << " | dealloc_calls = " << AllocCounter::dealloc_calls
          << " | bytes = " << AllocCounter::bytes_allocated << "\n";

    AllocCounter::reset();
    auto erase_keys_time = time_us([&]{
        for(int key : keys) {
            m.erase(key);
        }
    });
    std::cout << "Erase keys duration: " << erase_keys_time
          << " | alloc_calls = " << AllocCounter::alloc_calls
          << " | dealloc_calls = " << AllocCounter::dealloc_calls
          << " | bytes = " << AllocCounter::bytes_allocated << "\n";
    std::cout << "\n";
    }
    return 0;
}