#include <gtest/gtest.h>

#include "ideal_cache.hpp"

TEST(ideal_test, single_put_get) {
  Ideal_Cache<int, int> cache(5);

  int element = 1;

  cache.put(element, element);

  EXPECT_EQ(cache.get(element)->second, element);
}

TEST(ideal_test, many_put_get) {
  Ideal_Cache<int, int> cache(5);

  int element_1 = 1, element_2 = 2;

  cache.put(element_1, element_1);
  cache.put(element_2, element_2);

  EXPECT_EQ(cache.get(element_1)->second, element_1);
  EXPECT_EQ(cache.get(element_2)->second, element_2);
}

TEST(ideal_test, not_found) {
  Ideal_Cache<int, int> cache(5);

  int element_1 = 1, element_2 = 2;
  cache.put(element_2, element_2);

  EXPECT_EQ(cache.get(element_1), cache.end());
}