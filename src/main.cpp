#include <cstdint>
#include <map>
#include <iostream>
#include "../inc/allocator.h"
#include "../inc/container.h"
#include "../inc/factorial.h"

int main(int argc, char const *argv[]) {
    constexpr unsigned int elements_count = 10;

    using std_map_t = std::map<int, uint32_t>;
    using mod_map_t = std::map<int, uint32_t, std::less<>, custom::allocator<std::pair<const int, uint32_t>, elements_count> >;

    using std_custom_container_t = custom::container<int>;
    using mod_custom_container_t = custom::container<int, custom::allocator<int, elements_count> >;

    std_map_t              std_map;
    mod_map_t              mod_map;
    std_custom_container_t std_custom_container;
    mod_custom_container_t mod_custom_container;

    for (unsigned int i = 0; i < elements_count; ++i) {
        auto f = factorial(i);
        std_map.emplace(i, f);
        mod_map.emplace(i, f);
        std_custom_container.push_back(i);
        mod_custom_container.push_back(i);
    }

    std::cout << "Map with std::allocator:" << std::endl;
    for (const auto &i: std_map) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    std::cout << std::endl << "Map with allocator:" << std::endl;
    for (const auto &i: mod_map) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    std::cout << std::endl << "Custom container with std::allocator:" << std::endl;
    for (const auto &i: std_custom_container) {
        std::cout << i << std::endl;
    }

    std::cout << std::endl << "Custom container with allocator:" << std::endl;
    for (const auto &i: mod_custom_container) {
        std::cout << i << std::endl;
    }
    return 0;
}