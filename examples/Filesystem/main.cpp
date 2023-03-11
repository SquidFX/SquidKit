#include <iostream>
#include <string>
#include "Filesystem/DirectoryIterator.h"

using namespace SquidKit::Filesystem;

int main() {
    DirectoryIterator it(std::string("/"));
    while (it != DirectoryIterator()) {
        std::cout << it->path() << std::endl;
        ++it;
    }

    return 0;
}
