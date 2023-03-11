// g++ example1.cpp -o example1 -I../../include -L../../thirdparty/poco/build/lib  -lPocoFoundation -lPocoUtil

#include "Config/PropertyFileConfiguration.h"
#include "Core/AutoPtr.h"
#include <iostream>

using namespace SquidKit::Config;
using namespace SquidKit::Core;

int main()
{
    AutoPtr<PropertyFileConfiguration> pConf(new PropertyFileConfiguration("test.properties"));

    std::string key1 = pConf->getString("key1");
    int value = pConf->getInt("key2");
    std::string longVal = pConf->getString("key3.longValue");

    std::cout << "key1: " << key1 << std::endl;
    std::cout << "key2: " << value << std::endl;
    std::cout << "key3.longValue: " << longVal << std::endl;

    return 0;
}
