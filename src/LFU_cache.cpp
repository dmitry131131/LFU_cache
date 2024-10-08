#include <iostream>

#include "LFU_cache.hpp"

size_t LFU_cache_driver();

int main() {
    size_t HitCount = LFU_cache_driver();
    
    std::cout << HitCount << std::endl;

    return 0;
}

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
        if (cache.get(element) != cache.end()) HitCount++;
        else {
            cache.put(element, element);
        }
    }

    return HitCount;
}