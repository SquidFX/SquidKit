#include <iostream>
#include "Cache/LRUCache.h"
#include "Core/SharedPtr.h"

using namespace SquidKit::Cache;
using namespace SquidKit::Core;

int main()
{
    // Create an LRUCache with a maximum size of 3 elements
    LRUCache<int, string> myCache(3);
    
    // Add the first element with a key of 1 and a value of "Lousy"
    myCache.add(1, "Lousy");
    std::cout << "Cache after adding element with key 1:" << std::endl;
    for (auto key : myCache.getAllKeys())
        std::cout << key << " => " << *myCache.get(key) << std::endl;
    
    // Retrieve the element with key 1 and store it in a shared pointer
    SharedPtr<string> ptrElem = myCache.get(1);
    std::cout << "Cache after retrieving element with key 1:" << std::endl;
    for (auto key : myCache.getAllKeys())
        std::cout << key << " => " << *myCache.get(key) << std::endl;
    
    // Add two more elements to the cache
    myCache.add(2, "Morning");
    myCache.add(3, "USA");
    std::cout << "Cache after adding elements with keys 2 and 3:" << std::endl;
    for (auto key : myCache.getAllKeys())
        std::cout << key << " => " << *myCache.get(key) << std::endl;
    
    // Add a fourth element, causing the least popular element "Lousy" to be removed
    myCache.add(4, "Good");
    std::cout << "Cache after adding element with key 4:" << std::endl;
    for (auto key : myCache.getAllKeys())
        std::cout << key << " => " << *myCache.get(key) << std::endl;
    
    // Verify that the content of the shared pointer is still valid
    poco_assert (*ptrElem == "Lousy");
    
    // Retrieve the element with key 2 and store it in the shared pointer
    ptrElem = myCache.get(2);
    std::cout << "Cache after retrieving element with key 2:" << std::endl;
    for (auto key : myCache.getAllKeys())
        std::cout << key << " => " << *myCache.get(key) << std::endl;
    
    // Replace the value of the element with key 2 with "Evening"
    myCache.add(2, "Evening");
    std::cout << "Cache after replacing element with key 2:" << std::endl;
    for (auto key : myCache.getAllKeys())
        std::cout << key << " => " << *myCache.get(key) << std::endl;
    
    return 0;
}

