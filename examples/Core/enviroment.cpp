// g++ enviroment.cpp -o enviroment -I../../include -L../../thirdparty/poco/build/lib  -lPocoFoundation -lPocoUtil

#include "Core/Environment.h"
#include <iostream>

using namespace SquidKit::Core;

int main()
{
    std::string arch = std::to_string(Environment::arch());
    std::string os = std::to_string(Environment::os());
    std::string isUnix = std::to_string(Environment::isUnix());
    std::string osName = Environment::osName();
    std::string nodeName = Environment::nodeName();
    std::string osVersion = Environment::osVersion();
    std::string osArchitecture = Environment::osArchitecture();

    std::cout << "Arch: " << arch << std::endl;
    std::cout << "OS: " << os << std::endl;
    std::cout << "Unix: " << isUnix << std::endl;
    std::cout << "OS Name: " << osName << std::endl;
    std::cout << "Node Name: " << nodeName << std::endl;
    std::cout << "OS Version: " << osVersion << std::endl;
    std::cout << "OS Architecture: " << osArchitecture << std::endl;

    return 0;
}

