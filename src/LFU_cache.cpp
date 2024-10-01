#include <iostream>

#include "LFU_cache.hpp"

size_t LFU_cache_driver() {
    size_t CacheSize    = 0;
    size_t ElementCount = 0;
    size_t HitCount     = 0;

    std::cin >> CacheSize;
    std::cin >> ElementCount;

    LFU_cache<int, int> cache(CacheSize);

    for (size_t i = 0; i < ElementCount; i++) {
        int element = 0;
        std::cin >> element;
        if (cache.get(element)) HitCount++;
        else {
            cache.put(element, element);
        }
    }

    return HitCount;
}