#pragma once
#include <vector>

std::vector<int> make_keys(int N, int M) {
    std::vector<int> keys;
    keys.reserve(M);

    for(int i=0; i<M; i++) {
        int key = (i*37) % N;
        keys.push_back(key);
    }

    return keys;
}