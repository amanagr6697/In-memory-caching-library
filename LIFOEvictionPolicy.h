#pragma once

#include <cstddef>
#include "stack.h"
#include <unordered_map>
#include "EvictionPolicy.h"
#include<iostream>

template <typename Key, typename Value>
class LIFOEvictionPolicy: public EvictionPolicy<Key, Value> {
public:
    LIFOEvictionPolicy(std::size_t capacity);
    ~LIFOEvictionPolicy();
    void onGet(Key key);
    void onPut(Key key, Value value);
    void onEvict();
    Key evict();
    std::size_t size() const;

private:
    std::size_t capacity;
    Stack<Key> stack;
    std::unordered_map<Key, Value> map;
};


template <typename Key, typename Value>
LIFOEvictionPolicy<Key, Value>::LIFOEvictionPolicy(std::size_t capacity) : capacity(capacity) {}

template <typename Key, typename Value>
LIFOEvictionPolicy<Key, Value>::~LIFOEvictionPolicy() {}

template <typename Key, typename Value>
void LIFOEvictionPolicy<Key, Value>::onGet(Key key) {
    // No update
}

template <typename Key, typename Value>
void LIFOEvictionPolicy<Key, Value>::onPut(Key key, Value value) {
    if (map.find(key) == map.end()) {
        if (stack.size() == capacity) {
            onEvict();
        }
        stack.push(key);
        map[key] = stack.top();
    }
}

template <typename Key, typename Value>
void LIFOEvictionPolicy<Key, Value>::onEvict() {
    if (!stack.empty()) {
        Key evictedKey = stack.top();
        stack.pop();
        map.erase(evictedKey);
    }
}

template <typename Key, typename Value>
Key LIFOEvictionPolicy<Key, Value>::evict() {
    if (!stack.empty()) {
        return stack.top();
    }
    throw std::logic_error("Eviction policy is empty");
}

template <typename Key, typename Value>
std::size_t LIFOEvictionPolicy<Key, Value>::size() const {
    return stack.size();
}
