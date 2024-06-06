// LRUEvictionPolicy.h
#pragma once

#include <cstddef>
#include "DoublyLinkedList.h"
#include "EvictionPolicy.h"
#include <unordered_map>
#include <stdexcept>
#include <iostream>

template <typename Key, typename Value>
class LRUEvictionPolicy : public EvictionPolicy<Key, Value>
{
public:
    LRUEvictionPolicy(std::size_t capacity);
    ~LRUEvictionPolicy();
    void onGet(Key key);
    void onPut(Key key, Value value);
    void onEvict();
    Key evict();
    std::size_t size() const;

private:
    std::size_t capacity;
    std::size_t currentSize;
    DoublyLinkedList<Key> list;
    std::unordered_map<Key, ListNode<Key> *> map;
};

#include <stdexcept>

template <typename Key, typename Value>
LRUEvictionPolicy<Key, Value>::LRUEvictionPolicy(size_t capacity) 
    : capacity(capacity), currentSize(0) {}

template <typename Key, typename Value>
LRUEvictionPolicy<Key, Value>::~LRUEvictionPolicy() {
    list.clear();
}

template <typename Key, typename Value>
void LRUEvictionPolicy<Key, Value>::onGet(Key key) {
    if (map.find(key) != map.end()) {
        ListNode<Key>* node = map[key];
        list.push_back(node);
    }
}

template <typename Key, typename Value>
void LRUEvictionPolicy<Key, Value>::onPut(Key key, Value value) {
    if (map.find(key) == map.end()) {
        if (currentSize == capacity) {
            onEvict();
        }
        ListNode<Key>* node = list.addNode(key);
        map[key] = node;
        currentSize++;
    } else {
        ListNode<Key>* node = map[key];
        list.push_back(node);
    }
}

template <typename Key, typename Value>
void LRUEvictionPolicy<Key, Value>::onEvict() {
    if (currentSize > 0) {
        Key evictedKey = list.get_front()->val;
        list.pop_front();
        std::cout<<"Key: "<<evictedKey<<std::endl;
        map.erase(evictedKey);
        currentSize--;
    }
}

template <typename Key, typename Value>
Key LRUEvictionPolicy<Key, Value>::evict() {
    if (currentSize > 0) {
        return list.get_front()->val;
    }
    throw std::logic_error("Eviction policy is empty");
}

template <typename Key, typename Value>
size_t LRUEvictionPolicy<Key, Value>::size() const {
    return currentSize;
}
