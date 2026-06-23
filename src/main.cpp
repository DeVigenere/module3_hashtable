#include "HashTable.h"
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>

int main() {
    const int N = 100000;
    std::vector<std::string> keys;
    for (int i = 0; i < N; ++i) {
        keys.push_back("element_" + std::to_string(i));
    }
    auto start = std::chrono::high_resolution_clock::now();
    HashTable<std::string, int> my_ht;
    for (int i = 0; i < N; ++i) {
        my_ht.insert(keys[i], i * 2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto my_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, int> std_ht;
    for (int i = 0; i < N; ++i) {
        std_ht[keys[i]] = i * 2;
    }
    end = std::chrono::high_resolution_clock::now();
    auto std_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "my hashtable: " << my_time.count() << "ns" << std::endl;
    std::cout << "unordered_map: " << std_time.count() << "ns" << std::endl;
    my_ht.statistics();

    return 0;
}
