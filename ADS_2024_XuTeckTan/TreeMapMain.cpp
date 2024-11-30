#include <iostream>
#include "TreeMap.h"

int main() {
    TreeMap<std::string, int> map;

    map.put("apple", 10);
    map.put("banana", 20);
    map.put("cherry", 30);

    std::cout << "Size: " << map.size() << std::endl;
    std::cout << "Get 'banana': " << map.get("banana") << std::endl;

    map.removeKey("apple");
    std::cout << "Contains 'apple': " << map.containsKey("apple") << std::endl;

    std::cout << "KeySet: ";
    auto keys = map.keySet().toArray();
    for (int i = 0; i < map.size(); i++) {
        std::cout << keys[i] << " ";
    }
    delete[] keys; // Clean up allocated array
    std::cout << std::endl;

    return 0;
}
