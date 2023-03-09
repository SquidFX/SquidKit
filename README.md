# SquidKit


The SquidKit is a comprehensive C++ software development toolkit for ARM & X86_64 designed to help developers with limited experance build high-performance and feature-rich applications. It offers a powerful and flexible 2D graphics engine for vector graphics rendering with high accuracy and quality, advanced text rendering capabilities for complex text layout and typography, support for a wide range of image formats and image manipulations, and GPU acceleration for high-performance graphics. The SDK is cross-platform, supporting a variety of operating systems, and includes a rich set of APIs for working with graphics and images.

In addition to its graphics capabilities, the SDK also provides advanced layout features, including support for Flexbox, Grid, and CSS-compatible layout modes. These modes allow developers to create complex, responsive designs and have precise control over rows and columns. The SDK also includes the ability to detect if a point is over a layout, providing information that can be used for hover effects, hit testing, and touch-based interactions.

The SquidKit also provides comprehensive networking capabilities, including classes for network communication such as HTTP, FTP, and SMTP. It includes cryptography classes for encryption, decryption, and digital signatures, as well as XML classes for parsing and generating XML documents. The SDK also provides classes for working with databases, including support for SQLite and MongoDB, and foundation classes for data structures, algorithms, and other fundamental tasks. Additionally, it offers a variety of utility classes such as threading and logging, and platform-independent abstractions for common system-level functionality such as file system access and sockets. The SDK also includes internationalization classes for working with different character encodings and locale-specific data.



## Build System

The SquidKit utilizes CMake and Ninja for its build system. These tools provide a flexible and efficient way to manage the build process, allowing developers to configure and build the components they need for their project. The SDK is designed to be modular, so developers can build only the specific modules or classes they need, reducing the size of the final build and improving build times. This also allows developers to use only the features they require, keeping their code base lean and efficient. The use of CMake and Ninja helps ensure that the SquidKit can be easily integrated into a wide range of build environments, making it a highly versatile and adaptable development solution.

## SquidKit Development Process

The SquidKit employs various techniques to provide seamless integration with third-party libraries. One such technique is type aliasing, which is used extensively throughout the SDK. Additionally, the SDK employs wrapper classes in select cases, both of which are subsequently transformed into C++ modules.

This approach provides the SquidKit with the flexibility to offer a diverse set of features and functionalities, all backed by a consistent API. 

***DirectoryIterator.cxx implementation***
```c++
module;

#include <Poco/DirectoryIterator.h>

export module DirectoryIterator;

export namespace SquidKit::Filesystem {
        using DirectoryIterator = Poco::DirectoryIterator;
}
```

***Example (Uses Poco C++)***
```c++
// g++ -std=c++20 -fmodules-ts -o main main.cpp -L. -lSquidKitCore
import <iostream>;

import DirectoryIterator;
import Path;

using namespace SquidKit::Filesystem;

int main()
{
    Path dir("/");
    
    DirectoryIterator it(dir);
    DirectoryIterator end;
    
    for (; it != end; ++it) {
      std::cout << it.name() << std::endl;
    }

    return 0;
}
```

***Building the Module and Packing it into the Library***
```shell
// Build the DirectoryIterator module into object file
g++ -std=c++20 -fmodules-ts -c DirectoryIterator.cxx -o DirectoryIterator.o

// Unpack the corresponding third-party lib; in this case, it's libPocoFoundation.a
ar x libPocoFoundation.a

// Repack all the object files into the destination lib using the name of our choice
ar rcs libSquidKitCore.a *.o

// Gcc doesn't full support modules so we have to convert some of the std into modules like so.
g++ -std=c++20 -fmodules-ts -xc++-system-header iostream
g++ -std=c++20 -fmodules-ts -xc++-system-header string
g++ -std=c++20 -fmodules-ts -xc++-system-header fstream

// Compile our program using our modules and its library
g++ -std=c++20 -fmodules-ts -o main main.cpp -L. -lSquidKitCore
```

## Contributing



## Documentation

[File](./src/Core/File/)

## Building SquidKit

***Install Build Dependances***

Fedora
```shell
sudo dnf install git curl zip unzip tar ninja-build pkg-config bison \
python3-pip autoconf autoconf-archive mesa-libGL-devel automake libtool \
libudev-devel libX11-devel libXcursor-devel libXrandr-devel libXi-devel \
openssl-devel glibc-devel gcc-c++ libstdc++-devel cmake libXxf86vm-devel \
mesa-libGLU-devel wayland-devel libxkbcommon-devel mesa-libEGL-devel \
libXaw-devel openal-soft-devel libvorbis-devel flac-devel freetype-devel \
libcurl-devel openssl-devel alsa-lib-devel
```

Ubuntu (There maybe errors in pkg names.)
```shell
sudo apt-get install git curl zip unzip tar ninja-build pkg-config bison \
python3-pip autoconf autoconf-archive libglu1-mesa-dev automake libtool \
libudev-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev libssl-dev \
libc6-dev g++ libstdc++-dev cmake libxxf86vm-dev libwayland-dev \
libxkbcommon-dev libxaw7-dev libopenal-dev libvorbis-dev libflac-dev \
libfreetype6-dev libcurl4-openssl-dev libasound2-dev
```

***Build Everything***
```shell
cmake ..
make
```

## 

