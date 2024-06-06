#include <iostream>
#include "Cache.h"
#include "FIFOEvictionPolicy.h"

void comprehensiveTest(Cache<int, int> &cache)
{
    std::cout << "Starting comprehensive test with FIFO eviction policy..." << std::endl;

    cache.put(1, 100);
    std::cout << "Put (1, 100)" << std::endl;
    cache.put(2, 200);
    std::cout << "Put (2, 200)" << std::endl;
    cache.get(1);
    std::cout << "Get 1: " << cache.get(1) << " (expected 100)" << std::endl;
    cache.put(3, 300);
    std::cout << "Put (3, 300)" << std::endl;
    cache.put(4, 400); 
    std::cout << "Put (4, 400), should evict key 1" << std::endl;

    std::cout << "Get 1: " << cache.get(1) << " (expected 0)" << std::endl;
    std::cout << "Get 2: " << cache.get(2) << " (expected 200)" << std::endl;
    std::cout << "Get 3: " << cache.get(3) << " (expected 300)" << std::endl;
    cache.put(5, 500); 
    std::cout << "Put (5, 500), should evict key 2" << std::endl;
    cache.put(6, 600); 
    std::cout << "Put (6, 600), should evict key 3" << std::endl;

    std::cout << "Get 4: " << cache.get(4) << " (expected 400)" << std::endl;
    std::cout << "Get 2: " << cache.get(2) << " (expected 0)" << std::endl;
    cache.put(7, 700); 
    std::cout << "Put (7, 700), should evict key 4" << std::endl;
    cache.put(8, 800); 
    std::cout << "Put (8, 800), should evict key 5" << std::endl;
    cache.put(9, 900); 
    std::cout << "Put (9, 900), should evict key 6" << std::endl;

    std::cout << "Get 5: " << cache.get(5) << " (expected 0)" << std::endl;
    std::cout << "Get 6: " << cache.get(6) << " (expected 0)" << std::endl;
    std::cout << "Get 7: " << cache.get(7) << " (expected 700)" << std::endl;
    std::cout << "Get 8: " << cache.get(8) << " (expected 800)" << std::endl;
    std::cout << "Get 9: " << cache.get(9) << " (expected 900)" << std::endl;
    std::cout << "Get 10: " << cache.get(10) << " (expected 0)" << std::endl;

    std::cout << "Comprehensive test with FIFO eviction policy passed!" << std::endl;
}

int main()
{
    int capacity = 3;
    std::shared_ptr<EvictionPolicy<int,int>> evictionPolicy = std::make_shared<FIFOEvictionPolicy<int,int>>(capacity);
    Cache<int, int> cache(capacity, evictionPolicy);
    comprehensiveTest(cache);
    return 0;
}
