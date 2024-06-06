#pragma once

#include <cstddef>
#include "Queue.h"
#include <unordered_map>
#include "EvictionPolicy.h"

template <typename Key, typename Value>
class FIFOEvictionPolicy : public EvictionPolicy<Key, Value>
{
public:
    FIFOEvictionPolicy(std::size_t capacity);
    ~FIFOEvictionPolicy();
    void onGet(Key key);
    void onPut(Key key, Value value);
    void onEvict();
    Key evict();
    std::size_t size() const;

private:
    std::size_t capacity;
    Queue<Key> queue;
    std::unordered_map<Key, Value> map;
};

template <typename Key, typename Value>
FIFOEvictionPolicy<Key, Value>::FIFOEvictionPolicy(std::size_t capacity) : capacity(capacity) {}

template <typename Key, typename Value>
FIFOEvictionPolicy<Key, Value>::~FIFOEvictionPolicy() {}

template <typename Key, typename Value>
void FIFOEvictionPolicy<Key, Value>::onGet(Key key) {
    // FIFO does not update on get
}

template <typename Key, typename Value>
void FIFOEvictionPolicy<Key, Value>::onPut(Key key, Value value) {
    if (map.find(key) == map.end()) {
        if (queue.size() == capacity) {
            onEvict();
        }
        queue.push(key);
        map[key] = queue.front();
    }
}

template <typename Key, typename Value>
void FIFOEvictionPolicy<Key, Value>::onEvict() {
    if (!queue.empty()) {
        Key evictedKey = queue.front();
        queue.pop();
        map.erase(evictedKey);
    }
}

template <typename Key, typename Value>
Key FIFOEvictionPolicy<Key, Value>::evict() {
    if (!queue.empty()) {
        return queue.front();
    }
    throw std::logic_error("Eviction policy is empty");
}

template <typename Key, typename Value>
std::size_t FIFOEvictionPolicy<Key, Value>::size() const {
    return queue.size();
}
