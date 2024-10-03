#include <gtest/gtest.h>

#include "LFU_cache.hpp"

TEST(LFU_tests, single_put_get) {
  LFU_cache<int, int> cache(5);

  int element = 1;

  cache.put(element, element);

  EXPECT_EQ(*(cache.get(element)), element);
}

TEST(LFU_tests, many_put_get) {
  LFU_cache<int, int> cache(5);

  int element_1 = 1, element_2 = 2;

  cache.put(element_1, element_1);
  cache.put(element_2, element_2);

  EXPECT_EQ(*(cache.get(element_1)), element_1);
  EXPECT_EQ(*(cache.get(element_2)), element_2);
}

TEST(LFU_tests, not_found) {
  LFU_cache<int, int> cache(5);

  int element_1 = 1;

  EXPECT_EQ(cache.get(element_1), nullptr);
}