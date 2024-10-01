#include <iostream>

#include "LFU_cache.hpp"
#include "ideal_cache.hpp"

// #define LFU_MODE

int main() {

    #ifdef LFU_MODE
    
    size_t HitCount = LFU_cache_driver();

    #else

    size_t HitCount = ideal_cache_driver();

    #endif
    
    std::cout << HitCount << std::endl;

    return 0;
}