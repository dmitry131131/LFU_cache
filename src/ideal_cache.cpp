#include <iostream>

#include "ideal_cache.hpp"

size_t ideal_cache_driver() {
    size_t CacheSize    = 0;
    size_t ElementCount = 0;
    size_t HitCount     = 0;

    std::cin >> CacheSize;
    std::cin >> ElementCount;

    Ideal_Cache<int, int> cache(CacheSize);

    for (size_t i = 0; i < ElementCount; i++) {
        int element = 0;
        std::cin >> element;
  
        cache.all_data.push_back(std::make_pair(element, element));
    }

    for (auto element : cache.all_data) {
        if (cache.get(element.second)) HitCount++;
        else {
            cache.put(element.first, element.second);
        }

        (cache.current_position)++;

        // cache.cache_dump();
    }

    return HitCount;
}