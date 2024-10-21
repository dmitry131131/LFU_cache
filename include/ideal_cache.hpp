#ifndef IDEAL_CACHE_HPP
#define IDEAL_CACHE_HPP

#include <iostream>
#include <queue>
#include <unordered_map>

// Идея -> считываем всю последовательность элементов во внутренний буфер, и начинаем добавлять элементы в кеш
// Как только кеш забит, начинаем искать элемент в кеше, который наиболее удалён от текущей точки ввода, именно его мы и выкидываем
// Таким образом при каждой необходимости внести новый элемент в кеш, нужно будет пробегать циклом по всему кешу и искать наиболее удалённый элемент
// К сожалению двойной цикл(
// После чего считаем количество хитов и сравниваем с LFU кешем

// TODO Переписать входные данные на хеш таблицу с индексом -> элементов, а значением -> позиции, на которых встречается элемент 

template<typename Page_index_type, typename Page_data_type>
class Ideal_Cache {
  public:
    std::unordered_map<Page_index_type, std::queue<size_t>> input_data; // Input data
    size_t                                                  current_position;

  private:
    size_t                                              capacity;        // Cache data
    size_t                                              size;
    std::unordered_map<Page_index_type, Page_data_type> cache;

    void remove_farthest() {
        Page_index_type remove_index;
        size_t max_distance = 0;

        for (auto& elem : cache) {
            auto elem_info = input_data.find(elem.first);
            size_t elem_distance = (elem_info->second).front();

            if (max_distance < elem_distance) {
                max_distance = elem_distance;
                remove_index = elem_info->first;
            }
        }

        cache.erase(remove_index);
    }
  
  public:
    // move size = 0 and current_position = 0 to init list
    // read about explicit keyword
    explicit Ideal_Cache(size_t capacity_) : capacity(capacity_), size(0), current_position(0) {} 

    auto begin() { return cache.begin(); }
    auto end()   { return cache.end();   }

    auto get(Page_index_type& index) { // do not use pointer as return type
        auto found_page = cache.find(index);

        if (found_page == cache.end()) 
            return cache.end();

        auto elem_info = input_data.find(index);
        (elem_info->second).pop();

        return found_page;
    }

    void put(Page_index_type& index, Page_data_type& data) {
        auto found_page = cache.find(index);
        auto elem_info  = input_data.find(index);
        (elem_info->second).pop();

        if (found_page != cache.end()) return;  // if page already in cache

        if ((elem_info->second).empty()) return;    // if page wont meet again

        if (size < capacity) {
            cache.emplace(index, data);
            size++;
            return;
        }

        for (auto& cache_elem : cache) {
            if (((input_data.find(cache_elem.first))->second).front() < (elem_info->second).front()) {
                remove_farthest();
                cache.emplace(index, data);
                size++;
                return;
            }
        }
    }

    void cache_dump() const { // const method
        std::cout << "Capacity: " << capacity << std::endl;
        std::cout << "Size: " << size << std::endl;

        for (auto &[key, page] : cache)
            std::cout << "Index: " << key << " Data: " << page << std::endl;
    }
};

#endif