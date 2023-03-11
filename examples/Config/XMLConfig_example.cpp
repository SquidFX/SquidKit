// g++ example3.cpp -o example3 -I../../include -L../../thirdparty/poco/build/lib  -lPocoFoundation -lPocoUtil

#include <string>
#include <iostream>
#include "Config/XMLConfiguration.h"
#include "Core/AutoPtr.h"

using namespace SquidKit::Config;
using namespace SquidKit::Core;

int main()
{
    try
    {
        AutoPtr<XMLConfiguration> pConf(new XMLConfiguration("test.xml"));

        std::string prop1 = pConf->getString("prop1");
        int prop2 = pConf->getInt("prop2");
        std::string prop3 = pConf->getString("prop3"); // ""
        std::string prop4 = pConf->getString("prop3.prop4"); // ""
        prop4 = pConf->getString("prop3.prop4[@attr]"); // "value3"
        prop4 = pConf->getString("prop3.prop4[1][@attr]"); // "value4"

        std::cout << "prop1: " << prop1 << std::endl;
        std::cout << "prop2: " << prop2 << std::endl;
        std::cout << "prop3: " << prop3 << std::endl;
        std::cout << "prop4: " << prop4 << std::endl;

    }
    catch (Poco::Exception& exc)
    {
        std::cerr << exc.displayText() << std::endl;
        return 1;
    }

    return 0;
}

