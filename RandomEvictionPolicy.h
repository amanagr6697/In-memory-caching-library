#pragma once

#include <cstddef>
#include <unordered_map>
#include <random>
#include "EvictionPolicy.h"

template <typename Key, typename Value>
class RandomEvictionPolicy: public EvictionPolicy<Key, Value> {
public:
    RandomEvictionPolicy(std::size_t capacity);
    ~RandomEvictionPolicy();
    void onGet(Key key);
    void onPut(Key key, Value value);
    void onEvict();
    Key evict();
    std::size_t size() const;
    void displayContents() const;

private:
    std::size_t capacity;
    std::unordered_map<Key, Value> map;
    std::vector<Key> keys;
    std::random_device rd;
    std::mt19937 gen;
};

template <typename Key, typename Value>
RandomEvictionPolicy<Key, Value>::RandomEvictionPolicy(std::size_t capacity) : capacity(capacity), gen(rd()) {}

template <typename Key, typename Value>
RandomEvictionPolicy<Key, Value>::~RandomEvictionPolicy() {}

template <typename Key, typename Value>
void RandomEvictionPolicy<Key, Value>::onGet(Key key) {
}

template <typename Key, typename Value>
void RandomEvictionPolicy<Key, Value>::onPut(Key key, Value value) {
    if (map.find(key) == map.end()) {
        if (keys.size() == capacity) {
            onEvict();
        }
        keys.push_back(key);
        map[key] = value;
    }
}

template <typename Key, typename Value>
void RandomEvictionPolicy<Key, Value>::onEvict() {
    if (!keys.empty()) {
        std::uniform_int_distribution<> dis(0, keys.size() - 1);
        int index = dis(gen);
        Key evictedKey = keys[index];
        keys.erase(keys.begin() + index);
        map.erase(evictedKey);
    }
}

template <typename Key, typename Value>
Key RandomEvictionPolicy<Key, Value>::evict() {
    if (!keys.empty()) {
        std::uniform_int_distribution<> dis(0, keys.size() - 1);
        int index = dis(gen);
        return keys[index];
    }
    throw std::logic_error("Eviction policy is empty");
}

template <typename Key, typename Value>
std::size_t RandomEvictionPolicy<Key, Value>::size() const {
    return keys.size();
}

template <typename Key, typename Value>
void RandomEvictionPolicy<Key, Value>::displayContents() const {
    std::cout << "Contents of RandomEvictionPolicy:" << std::endl;
    for (const auto& pair : map) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
