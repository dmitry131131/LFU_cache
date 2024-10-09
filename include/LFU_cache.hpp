#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP

#include <iostream>
#include <unordered_map>

template<typename Page_index_type, typename Page_data_type>
class LFU_cache {
    std::unordered_map<Page_index_type, Page_data_type> valueMap;
    std::unordered_map<Page_index_type, size_t>         freqMap;
    size_t                                              capacity;
    size_t                                              size;

  private:
    Page_index_type get_min_freq_index() const {
        size_t min_freq = __LONG_MAX__;
        Page_index_type ret_index = (freqMap.begin())->first;

        for (auto& node : freqMap) {
            if (node.second < min_freq) {
                min_freq = node.second;
                ret_index = node.first;
            }
        }

        return ret_index;
    }

  public:
    explicit LFU_cache(size_t capacity_) : capacity(capacity_), size(0) {}

    auto begin() { return valueMap.begin(); }
    auto end()   { return valueMap.end();   }

    auto get(Page_index_type index) {  // FIXME use iterator as return value
        auto found_page = valueMap.find(index);

        if (found_page == valueMap.end())
            return valueMap.end();
        
        auto page_freq = freqMap.find(index);
        (page_freq->second)++;

        return found_page;
    }

    void put(Page_index_type& index, Page_data_type& data) {
        auto found_page = valueMap.find(index);

        if (found_page == valueMap.end()) {

            if (size >= capacity) {
                Page_index_type del_index = get_min_freq_index();

                valueMap.erase(del_index);
                freqMap.erase(del_index);

                size--;
            }

            valueMap.emplace(index, data);
            freqMap.emplace(index, 1);
        }
        else {
            auto page_freq = freqMap.find(index);
            (page_freq->second)++;
            return;
        }

        size++;
    }

    void dump() const {
        std::cout << "Capacity: " << capacity << std::endl;
        std::cout << "Size: "     << size     << std::endl;
        // Dump ValueMap
        std::cout << "Dump value map" << std::endl;
        for (auto& [key, val] : valueMap) {
            std::cout << "Index: " << key << " Value: " << val << std::endl;
        }

        // Dump freqMap
        std::cout << "Dump frequency map" << std::endl;
        for (auto& [key, val] : freqMap) {
            std::cout << "Index: " << key << " Frequency: " << val << std::endl;
        }
    }
};

#endif