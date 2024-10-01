#ifndef IDEAL_CACHE_HPP
#define IDEAL_CACHE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>

// TODO Написать идеальный кеш
// Идея -> считываем всю последовательность элементов во внутренний буфер, и начинаем добавлять элементы в кеш
// Как только кеш забит, начинаем искать элемент в кеше, который наиболее удалён от текущей точки ввода, именно его мы и выкидываем
// Таким образом при каждой необходимости внести новый элемент в кеш, нужно будет пробегать циклом по всему кешу и искать наиболее удалённый элемент
// К сожалению двойной цикл(
// После чего считаем количество хитов и сравниваем с LFU кешем

template<typename Page_index_type, typename Page_data_type>
class Ideal_Cache {
  public:
    std::vector<std::pair<Page_index_type, Page_data_type>> all_data;           // Input data
    size_t                                                  current_position;

  private:
    size_t                                              capacity;               // Cache data
    size_t                                              size;
    std::unordered_map<Page_index_type, Page_data_type> cache;

    std::pair<Page_index_type, Page_data_type> get_farthest_element() {
        size_t max_distance                                             = 0;
        std::pair<Page_index_type, Page_data_type> max_distance_element = {};

        for (auto element : cache) {
            size_t cur_element_distance = 0;

            for (size_t index = current_position; index < all_data.size(); index++) {   // find curent element distance
                if ((all_data[index]).second == element.second) {
                    cur_element_distance = index - current_position;
                    break;
                } 
            }

            if (cur_element_distance > max_distance) {
                max_distance         = cur_element_distance;
                max_distance_element = element;
            }

            if (max_distance >= (all_data.size() - current_position - 1)) return element;
        }

        return max_distance_element;
    }
  
  public:
    Ideal_Cache(size_t capacity_) : capacity(capacity_) {size = 0; current_position = 0;} 

    Page_data_type* get(Page_index_type& index) {
        auto found_page = cache.find(index);

        if (found_page == cache.end()) 
            return nullptr;

        return &(found_page->second);
    }

    void put(Page_index_type& index, Page_data_type& data) {
        auto found_page = cache.find(index);

        if (found_page != cache.end()) return;  // if page already in cache

        if (size >= capacity) {                  // if cache is full
            cache.erase(get_farthest_element().first);
            size--;
        }

        cache.insert(std::make_pair(index, data));
        size++;
    }

    void cache_dump() {
        std::cout << "Capacity: " << capacity << std::endl;
        std::cout << "Size: " << size << std::endl;
        
        for (auto element = cache.begin(); element != cache.end(); element++) {
            std::cout << "Index: " << element->first << " Data: " << element->second << std::endl;
        }
    }
};

size_t ideal_cache_driver();

#endif