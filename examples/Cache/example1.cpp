#include <iostream>
#include "Cache/LRUCache.h"
#include <Poco/SharedPtr.h>

using namespace std;
using namespace SquidKit::Cache;
using namespace Poco;

int main()
{
    // Create an LRUCache with a maximum size of 3 elements
    LRUCache<int, string> myCache(3);
    
    // Add the first element with a key of 1 and a value of "Lousy"
    myCache.add(1, "Lousy");
    cout << "Cache after adding element with key 1:" << endl;
    for (auto key : myCache.getAllKeys())
        cout << key << " => " << *myCache.get(key) << endl;
    
    // Retrieve the element with key 1 and store it in a shared pointer
    SharedPtr<string> ptrElem = myCache.get(1);
    cout << "Cache after retrieving element with key 1:" << endl;
    for (auto key : myCache.getAllKeys())
        cout << key << " => " << *myCache.get(key) << endl;
    
    // Add two more elements to the cache
    myCache.add(2, "Morning");
    myCache.add(3, "USA");
    cout << "Cache after adding elements with keys 2 and 3:" << endl;
    for (auto key : myCache.getAllKeys())
        cout << key << " => " << *myCache.get(key) << endl;
    
    // Add a fourth element, causing the least popular element "Lousy" to be removed
    myCache.add(4, "Good");
    cout << "Cache after adding element with key 4:" << endl;
    for (auto key : myCache.getAllKeys())
        cout << key << " => " << *myCache.get(key) << endl;
    
    // Verify that the content of the shared pointer is still valid
    poco_assert (*ptrElem == "Lousy");
    
    // Retrieve the element with key 2 and store it in the shared pointer
    ptrElem = myCache.get(2);
    cout << "Cache after retrieving element with key 2:" << endl;
    for (auto key : myCache.getAllKeys())
        cout << key << " => " << *myCache.get(key) << endl;
    
    // Replace the value of the element with key 2 with "Evening"
    myCache.add(2, "Evening");
    cout << "Cache after replacing element with key 2:" << endl;
    for (auto key : myCache.getAllKeys())
        cout << key << " => " << *myCache.get(key) << endl;
    
    return 0;
}

