// g++ example2.cpp -o example2 -I../../include -L../../thirdparty/poco/build/lib  -lPocoFoundation -lPocoUtil

#include <string>
#include "Config/IniFileConfiguration.h"
#include "Core/AutoPtr.h"
#include <iostream>

using namespace SquidKit::Config;
using namespace SquidKit::Core;

int main()
{
    AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("test.ini"));

    // Get string value from configuration
    std::string path = pConf->getString("MyApplication.somePath");

    // Get integer value from configuration
    int value = pConf->getInt("MyApplication.someValue");

    // Get integer value with default value
    value = pConf->getInt("myapplication.SomeOtherValue", 456);

    std::cout << "Path: " << path << std::endl;
    std::cout << "Value: " << value << std::endl;

    return 0;
}

