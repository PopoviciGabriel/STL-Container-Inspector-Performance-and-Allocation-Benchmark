#pragma once
#include <iostream>

inline void print_iterator_invalidation_rules() {
    std::cout << "\n=== Iterator invalidation (rules) ===\n";

    std::cout << "\n[vector]\n";
    std::cout << "- Reallocation (capacity grows) invalidates ALL iterators, pointers, references.\n";
    std::cout << "- erase(pos) invalidates iterators/references from pos to end.\n";
    std::cout << "- insert can invalidate (especially if reallocation happens).\n";

    std::cout << "\n[deque]\n";
    std::cout << "- insert/erase can invalidate iterators (often many of them), references/pointers may also be invalidated.\n";
    std::cout << "- push_front/push_back may invalidate iterators in some implementations.\n";

    std::cout << "\n[list]\n";
    std::cout << "- insert does NOT invalidate iterators/references.\n";
    std::cout << "- erase invalidates ONLY iterators/references to erased elements.\n";

    std::cout << "\n[unordered_map]\n";
    std::cout << "- rehash/reserve that triggers rehash invalidates ALL iterators.\n";
    std::cout << "- erase(key/it) invalidates ONLY iterators to erased element.\n\n";
}
