#pragma once

template <typename Key, typename Value>
class EvictionPolicy {
public:
    virtual void onGet(Key key) = 0;
    virtual void onPut(Key key, Value value) = 0;
    virtual void onEvict() = 0;
    virtual Key evict() = 0;
    virtual ~EvictionPolicy() = default;
};
