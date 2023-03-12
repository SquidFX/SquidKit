<img src="/home/stevenstarr/Downloads/logo.jpeg" alt="logo" style="zoom:25%;" />

## SquidKit Development Process

![test.drawio](/home/stevenstarr/Downloads/test.drawio.png)



### Code Wrapping

In software development, a wrapper is a piece of code that provides a simplified or more convenient interface to another piece of code, often by encapsulating or abstracting away some of its complexity.



**Type Aliasing** (Class A Wrapper)

```c++
#pragma once

#include <Poco/File.h>

namespace SquidKit::Core {
  using File = Poco::File;
}
```



**Derived** (Class B Wrapper)

```c++
#pragma once

#include <Poco/File.h>

namespace SquidKit::Filesystem {

   class File : public Poco::File {
   public:
      using Poco::File::File;
   };

} // namespace SquidKit::Filesystem

```



**Composition**  (Class C Wrapper)

```c++
#pragma once

#include <Poco/File.h>

namespace SquidKit::Filesystem {

   class File {
      public:
         File(const std::string& path) : file_(path) {}
         bool exists() const { return file_.exists(); }
         void remove() { file_.remove(); }
      private:
         Poco::File file_;
   };
   
} // namespace SquidKit::Filesystem
```



**C Library Wrapper** (Class D Wrapper)

```c++
#pragma once

#include <cstdio>
#include <cstring>

class File {
public:
    File(const char* filename, const char* mode = "r") {
        file_ = fopen(filename, mode);
    }

    ~File() {
        if (file_ != nullptr) {
            fclose(file_);
        }
    }

    bool exists() const {
        return (file_ != nullptr);
    }

    bool remove() {
        if (file_ != nullptr) {
            fclose(file_);
        }
        return (std::remove(filename_.c_str()) == 0);
    }

private:
    FILE* file_ = nullptr;
    std::string filename_;
};
```





### Application Module

The Application module offers three distinct classes to suit different programming needs. The **ApplicationServer** class provides a development environment for creating scalable, robust network aware commandline applications. The **ApplicationServer** class is ideal for building console and network based applications, featuring an option parser and string formatter to easily handle user inputs. 



The **Application2D** class is designed to create graphic user interfaces, offering drag-and-drop functionality, customizable widgets, and built-in styling. The **Application3D** class is perfect for developing 2D and 3D games, providing a rich set of game development tools and features, including animation support, a physics engine, and sound effects. the class is perfect for developing audio applications and plug-ins. Overall, the Application module is a powerful and flexible tool for creating a wide range of applications in C++



### Archive Module

The Archive module allows developers to handle a wide range of file formats commonly used for archiving and compression purposes. The module provides support for various compression formats, including gzip, bzip2, compress, uudecode, base64, xz, lzip, and lzma. The module also supports various archive formats such as tar, pax, cpio, ISO9660, zip, mtree, shar, ar, empty, raw, xar, lha/lzh, rar, Microsoft CAB format, 7-Zip, and WARC. The Archive module makes it easy for developers to read and write files in these formats, including support for extensions and variants of each format. 



### Audio Module

The Audio module offers a range of powerful tools for developers to create sophisticated audio applications. The **SoundServer** class simplifies the process of interacting with audio hardware, providing a common API across multiple operating systems. The **SoundEngine** class offers advanced audio features like DSP effects, multichannel mixing, and sample rate conversion. The **Codecs** submodule supports various audio formats for reading and writing, including OGG, Vorbis, FLAC, and WAV. The **Midi** class provides tools for working with MIDI devices and messages. The SynthToolkit submodule offers a range of tools for sound synthesis algorithms, while the **Plugins** submodule provides a framework for developing custom audio processing plugins. 



#### SoundServer Class

The **SoundServer** class provides a common API for real-time audio input and output across various operating systems. It simplifies the process of interacting with computer audio hardware and provides a simple, common API that is easy to include in programming projects.

- Supports simultaneous multi-API support, allowing developers to choose a specific audio API when creating an instance of the **SoundServer** class. This feature makes it possible to support multiple audio devices and audio APIs without the need to rewrite code for each operating system.

- Allows dynamic connection of audio devices, which means that audio devices can be added or removed while the **SoundServer** is running without affecting the audio output or input. It can also provide extensive audio device parameter control, allowing developers to fine-tune audio device settings for optimal performance.

- Can incorporate the concept of audio streams, which represents audio output (playback) and/or input (recording). Developers can enumerate available audio devices and their capabilities and specify them when opening a stream. The **SoundServer** class can also provide audio device capability probing, making it possible to detect audio device capabilities before opening a stream.

- Can provide automatic internal conversion for data format, channel number compensation, (de)interleaving, and byte-swapping, making it possible to work with audio data in various formats.



#### SoundEngine Class

The **SoundEngine** class builds off the **SoundServer** and has a range of advanced features that make it a powerful tool for building sophisticated audio applications. These features include:

- Compatibility with the WebAudio API, which enables developers to create audio applications that work seamlessly in web browsers.
- Audio asset loading via libnyquist, which allows developers to load audio assets in a variety of formats.
- Binaural audio via IRCAM HRTF database, which provides realistic 3D audio spatialization for headphone listening.
- Additional effect and generator nodes (ADSR, noise, stereo delay, and more), which give developers a wide range of processing tools to work with.
- Compile-time arbitrary function node for DSP processing, which allows developers to write custom audio processing algorithms that can be compiled at runtime.
- Basic signal analysis nodes (time and frequency), which enable developers to perform basic analysis of audio signals.
- Input node (microphone), which allows developers to record audio input from a microphone.
- Non-realtime graph processing and WAV export, which enables developers to process audio graphs offline and export the results to a WAV file.
- Thread safety model for multi-threaded apps (e.g. GUI), which ensures that the SoundEngine can be used safely in multi-threaded applications.
- SIMD-accelerated channel mixing routines, which provide high-performance mixing of audio channels using SIMD instructions.



#### Midi Class

#### SynthToolkit Class

#### Codecs Class



### Cache Module

The Cache module provides a framework for caching objects in memory to improve application performance by reducing the need for expensive I/O operations or repeated computations.

- The Cache module provides various cache implementations, including LRUCache, FIFOCache, and PriorityCache. It also provides a GenericCache class that can be extended to implement custom caching strategies. The module supports caching of objects of any type, including built-in types, custom objects, and STL containers.

- The Cache module supports serialization of cache objects to allow for persistence across multiple application instances. It provides a FileCache implementation that can store cached objects on disk, and a CacheStream class that provides a stream-based interface to cache data.

- The Cache module also provides support for cache invalidation based on various policies, including time-based invalidation, maximum size limits, and custom invalidation policies. It supports thread-safe access to the cache, making it suitable for use in multi-threaded applications.



#### AbstractCache Class

AbstractCache class serves as an abstract base class for implementing cache strategies. It defines the interface for caching and retrieving objects in memory and provides a framework for implementing various caching strategies.

AbstractCache provides methods for inserting, retrieving, and removing objects from the cache, as well as for checking the size and capacity of the cache. It also provides methods for setting and retrieving cache expiration times and for checking if an object is present in the cache.

One of the primary benefits of using AbstractCache is that it allows for the implementation of custom cache strategies by extending the class and implementing the necessary methods. This enables developers to tailor the cache implementation to specific application requirements and improve performance by reducing the need for expensive I/O operations or repeated computations.

The AbstractCache class also provides thread-safe access to the cache, making it suitable for use in multi-threaded applications. It supports a variety of cache eviction policies, including time-based, size-based, and custom policies.

Overall, the AbstractCache class is a powerful tool for implementing cache strategies in memory and can help improve application performance by reducing the need for repeated computations or I/O operations.



#### LRUCache Class

LRUCache class implements a Least Recently Used (LRU) caching strategy. The LRUCache class is a templated class that allows for caching objects of any type, including built-in types, custom objects, and STL containers. The class maintains a cache of a maximum size specified at construction time, and objects that are least recently used are evicted when the cache reaches its maximum size.

The LRUCache class provides thread-safe access to the cache, making it suitable for use in multi-threaded applications. It provides methods for adding, removing, and accessing cached objects, as well as for clearing the entire cache. The class also supports cache invalidation based on time-based policies or custom invalidation policies.

One of the advantages of using the LRUCache class is that it can significantly improve application performance by reducing the need for expensive I/O operations or repeated computations. By keeping frequently accessed objects in memory, the LRUCache class can reduce the amount of time required to retrieve these objects from disk or compute them.



### Config Module