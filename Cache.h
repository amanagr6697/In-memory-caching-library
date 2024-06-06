// cache.h

#pragma once
#include "EvictionPolicy.h"
#include <unordered_map>
#include <mutex>
#include <memory>
#include <stdexcept>
#include <thread>

// #include "FIFOEvictionPolicy.h"
// #include "LRUEvictionPolicy.h"
// #include "LIFOEvictionPolicy.h"
// #include "RandomEvictionPolicy.h"


// enum class EvictionPolicyType
// {
//     FIFO,
//     LRU,
//     LIFO,
//     Random
// };

template <typename Key, typename Value>
class Cache
{
private:
    std::unordered_map<Key, Value> cache;
    std::shared_ptr<EvictionPolicy<Key, Value>> evictionPolicy;
    size_t capacity;
    std::mutex mtx;

public:
    Cache(size_t cap, std::shared_ptr<EvictionPolicy<Key, Value>> evictionPolicy);

    Value get(Key key);
    void put(Key key, Value value);

// private:
//     std::shared_ptr<EvictionPolicy<Key, Value>> createEvictionPolicy(EvictionPolicyType policyType);
};

#include<iostream>

template <typename Key, typename Value>
Cache<Key, Value>::Cache(size_t cap, std::shared_ptr<EvictionPolicy<Key, Value>> evictionPolicy) : capacity(cap), evictionPolicy(evictionPolicy) {
}

template <typename Key, typename Value>
Value Cache<Key, Value>::get(Key key) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = cache.find(key);
    if (it != cache.end()) {
        evictionPolicy->onGet(key);
        return it->second;
    } else {
        std::cout<<"Key not found"<<std::endl;
        return Value();
    }
}

template <typename Key, typename Value>
void Cache<Key, Value>::put(Key key, Value value) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = cache.find(key);
    if (it != cache.end()) {
        it->second = value;
        evictionPolicy->onPut(key, value);
    } else {
        if (cache.size() == capacity) {
            Key evictedKey = evictionPolicy->evict();
            cache.erase(evictedKey);
        }
        cache[key] = value;
        evictionPolicy->onPut(key, value);
    }
}

// template <typename Key, typename Value>
// std::shared_ptr<EvictionPolicy<Key, Value>> Cache<Key, Value>::createEvictionPolicy(EvictionPolicyType policyType) {
//     switch (policyType) {
//         case EvictionPolicyType::FIFO:
//             return std::make_shared<FIFOEvictionPolicy<Key, Value>>(capacity);
//         case EvictionPolicyType::LRU:
//             return std::make_shared<LRUEvictionPolicy<Key, Value>>(capacity);
//         case EvictionPolicyType::LIFO:
//             return std::make_shared<LIFOEvictionPolicy<Key, Value>>(capacity);
//         case EvictionPolicyType::Random:
//             return std::make_shared<RandomEvictionPolicy<Key, Value>>(capacity);
//         default:
//             throw std::invalid_argument("Invalid eviction policy type");
//     }
// }