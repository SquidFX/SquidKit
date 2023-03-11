 #####                         #    #         
#     #  ####  #    # # #####  #   #  # ##### 
#       #    # #    # # #    # #  #   #   #   
 #####  #    # #    # # #    # ###    #   #   
      # #  # # #    # # #    # #  #   #   #   
#     # #   #  #    # # #    # #   #  #   #   
 #####   ### #  ####  # #####  #    # #   #   


cmake_minimum_required(VERSION 3.24)
project(SquidKit)



option(USE_CLANG            "Build with Clang"      ON)
option(USE_CLANGXX          "Build with Clang++"    ON)
option(USE_LDD              "Use ldd for linking"   ON)
option(USE_LIBCPP           "Use libc++"            ON)

if (USE_CLANG)
  set(CMAKE_C_COMPILER "clang")
endif()

if (USE_CLANGXX)
  set(CMAKE_CXX_COMPILER "clang++")
endif()

if (USE_LDD)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=ldd")
endif()

if (USE_LIBCPP)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_ARCHITECTURE "x86_64-linux-gnu")



include(ExternalProject)

# Individual options
option(C_Compiler       "llvm"              OFF) # Not building correctly
set_property(CACHE      C_Compiler  PROPERTY ADVANCED ON)

option(Build_Generator  "cmake"             OFF)
option(Build_System     "ninja"             OFF)
option(BUILD_LIBARCHIVE "libarchive"        OFF) # Compile errors
option(BUILD_RTAUDIO    "rtAudio"           OFF)
option(BUILD_STK        "stk"               OFF)
option(BUILD_RTMIDI     "rtMidi"            OFF)
option(BUILD_LABSOUND   "labsound"          OFF)
option(BUILD_LIBNYQUIST "libnyquist"        OFF)
option(BUILD_FLAC       "flac"              OFF)
option(BUILD_VORBIS     "vorbis"            OFF)
option(BUILD_OPUS       "opus"              OFF)
option(BUILD_AWS        "aws-sdk"           OFF)
option(BUILD_AZURE      "azure-sdk"         OFF)
option(BUILD_GOOGLE     "google-cloud-sdk"  OFF)
option(BUILD_POCO       "poco"              OFF)
option(BUILD_BOOST      "boost"             OFF)
option(BUILD_FMT        "fmt"               OFF)
option(BUILD_CLI        "cli"               OFF)
option(BUILD_REDIS      "redis"             OFF)
option(BUILD_POSTGRESQL "postgresql"        OFF)
option(BUILD_SQLITE     "sqlite"            OFF)
option(BUILD_LEVELDB    "leveldb"           OFF)
option(BUILD_MCACHED    "memcached"         OFF)
option(BUILD_LMDB       "lmdb"              OFF)
option(BUILD_ARANGODB   "arangodb"          OFF)
option(BUILD_SKIA       "skia"              ON)
option(BUILD_OIIO       "openimageio"       OFF)
option(BUILD_BOX2D      "box2d"             OFF)
option(BUILD_YOGA       "yoga"              ON)
option(BUILD_VSG        "vulkanscenegraph"  OFF)
option(BUILD_PCL        "pcl"               OFF)
option(BUILD_TASK       "taskflow"          OFF)
option(BUILD_THRUST     "thrust"            OFF)
option(BUILD_LIBOSMIUM  "libosmium"         OFF)
option(BUILD_GDAL       "gdal"              OFF)
option(BUILD_OSRM       "osrm"              OFF) 

# Group options
option(Enable_Tools     "Enable tools"      OFF)
if(Enable_Tools)
    set(C_Compiler        "llvm"        CACHE STRING "C compiler")
    set(Build_Generator   "cmake"       CACHE STRING "Build generator")
    set(Build_System      "ninja"       CACHE STRING "Build system")
endif()    

option(Enable_Database  "Enable database"    OFF)
if(Enable_Database)
    set(BUILD_REDIS      "redis"        CACHE STRING "Redis Database")
    set(BUILD_POSTGRESQL "postgresql"   CACHE STRING "PostgreSQL Database")
    set(BUILD_SQLITE     "sqlite"       CACHE STRING "SQLite Database")
    set(BUILD_LEVELDB    "leveldb"      CACHE STRING "")
    set(BUILD_MCACHED    "memcached"    CACHE STRING "")
    set(BUILD_LMDB       "lmdb"         CACHE STRING "")
    set(BUILD_ARANGODB   "arangodb"     CACHE STRING "")
endif()   


# LLVM
if(C_Compiler)
# LLVM is a collection of modular and reusable compiler and toolchain technologies, written in C++ and 
# designed for a wide range of programming languages. 
# License: Apache 2.0
ExternalProject_Add(
    llvm
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/llvm
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/llvm/src/llvm/llvm
    GIT_REPOSITORY https://github.com/llvm/llvm-project.git
    GIT_TAG main
    CMAKE_ARGS  
      -DLLVM_ENABLE_PROJECTS=clang;clang-tools-extra
      -DLLVM_ENABLE_LLD=ON
      -DLLVM_ENABLE_LIBCXX=ON
      -DLLVM_ENABLE_LIBCXXABI=ON
      -DLLVM_BUILD_LLVM_DYLIB=ON
      -DLLVM_ENABLE_RTTI=ON
      -DLLVM_TARGETS_TO_BUILD=X86
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/tools
)
endif()



# CMAKE
if(Build_Generator)
# CMake is a cross-platform build system generator that allows developers to specify the build process for 
# their C++ projects in a platform-independent way. It uses a simple scripting language called CMake Language 
# (CMakeLists.txt) to describe the build targets, dependencies, and compiler settings.  
# License: BSD 3-Clause
ExternalProject_Add(
    cmake
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/cmake
    GIT_REPOSITORY https://github.com/llvm/llvm-project.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/tools
)
endif()



# Ninja
if(Build_System)
# Ninja is a build system that is designed to be fast, flexible, and easy to use. It is commonly used in software 
# development to automate the building of software projects, especially large projects with many dependencies.
# License: Apache 2.0
ExternalProject_Add(
    ninja
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/ninja
    GIT_REPOSITORY https://github.com/ninja-build/ninja.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/tools
)
endif()



# Test
option(Build_TEST "TEST Project" OFF)
if(Build_TEST)
#
#
ExternalProject_Add(
    test
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/test
    GIT_REPOSITORY https://github.com/myusername/myexternalproject.git
    GIT_TAG master
    CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/src/myexternalproject/configure --prefix=${CMAKE_BINARY_DIR}/thirdparty/install
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)
endif()



# Libarchive
if(BUILD_LIBARCHIVE)
# Libarchive is a C library that provides a flexible and powerful interface for reading 
# and writing archive files, such as tar and zip files. It is designed to support a wide 
# range of archive formats and options, and it includes features such as streaming decompression, 
# compression levels, and encryption.
# License: MIT
#ExternalProject_Add(
#    libarchive
#    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/libarchive
#    GIT_REPOSITORY https://github.com/libarchive/libarchive.git
#    GIT_TAG v3.6.2
#    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/libarchive-install
#)
endif()



# RtAudio
if(BUILD_RTAUDIO)
# RtAudio is a C++ library that provides a cross-platform interface for 
# real-time audio input and output. It supports multiple audio API backends, 
# including ALSA, Core Audio, and ASIO, and it can be used for both low-latency 
# audio processing and high-quality audio playback. 
# License: MIT
ExternalProject_Add(
    rtaudio
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/rtaudio
    GIT_REPOSITORY https://github.com/thestk/rtaudio.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# STK
if(BUILD_STK)
# STK (Synthesis ToolKit in C++) is a C++ library designed for creating 
# and manipulating digital audio signals. It provides a wide range of 
# signal processing and synthesis algorithms, including filters, oscillators, 
# envelope generators, and more.
# License: MIT
ExternalProject_Add(
    stk
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/stk
    GIT_REPOSITORY https://github.com/thestk/stk.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# RtMidi
if(BUILD_RTMIDI)
# RtMidi is a C++ library that provides a simple and cross-platform interface 
# for working with MIDI (Musical Instrument Digital Interface) devices. It allows 
# for sending and receiving MIDI messages, such as notes, pitch bends, and control 
# changes, to and from hardware and software instruments. 
# License: MIT
ExternalProject_Add(
    rtmidi
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/rtmidi
    GIT_REPOSITORY https://github.com/thestk/rtmidi.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# LabSound
if(BUILD_LABSOUND)
# LabSound is an open-source C++ library for audio processing that was developed by 
# Google and is now maintained by a community of contributors on GitHub. It provides 
# a comprehensive set of tools for creating, analyzing, and processing audio in real-time 
# or offline applications.s. 
# License: BSD 2-Clause
ExternalProject_Add(
    labsound
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/labsound
    GIT_REPOSITORY https://github.com/LabSound/LabSound.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
    if(BUILD_LABSOUND)
        add_dependencies(labsound flac)
        add_dependencies(labsound vorbis)
        add_dependencies(labsound opus)
    endif()
endif()



# Libnyquist
if(BUILD_LIBNYQUIST)
# Libnyquist is an open-source C++ library for audio processing that was developed by 
# Google and is now maintained by a community of contributors on GitHub. It provides 
# a comprehensive set of tools for creating, analyzing, and processing audio in real-time 
# or offline applications.s. 
# License: BSD 2-Clause
ExternalProject_Add(
    labsound
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/labsound
    GIT_REPOSITORY https://github.com/LabSound/LabSound.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
    if(BUILD_LABSOUND)
        add_dependencies(labsound flac)
        add_dependencies(labsound vorbis)
        add_dependencies(labsound opus)
    endif()
endif()



# Flac
if(BUILD_FLAC)
# FLAC is a software library that provides an API for encoding and decoding audio data in 
# the FLAC (Free Lossless Audio Codec) format. FLAC is an open-source lossless audio compression 
# format that allows for high-quality audio compression without any loss of information, making 
# it popular among audiophiles and music enthusiasts.
# License: BSD 3-Clause
ExternalProject_Add(
    flac
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/flac
    GIT_REPOSITORY https://github.com/xiph/flac.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Vorbis
if(BUILD_VORBIS)
# Vorbis is an open-source audio compression format that is designed to provide high-quality, 
# low-latency audio compression at a low bit rate. It was created as an alternative to other 
# popular audio codecs, such as MP3 and AAC, which are proprietary and often require licensing 
# fees for their use.
# License: BSD 3-Clause
ExternalProject_Add(
    vorbis
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/vorbis
    GIT_REPOSITORY https://github.com/xiph/vorbis.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Opus
if(BUILD_OPUS)
# Opus is a totally open, royalty-free, highly versatile audio codec. Opus is unmatched for 
# interactive speech and music transmission over the Internet, but is also intended for storage 
# and streaming applications. 
# License: BSD 3-Clause
ExternalProject_Add(
    opus
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/opus
    GIT_REPOSITORY https://github.com/xiph/opus.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# AWS
if(BUILD_AWS)
# AWS SDK for C++ is a C++ software development kit that provides a modern and streamlined 
# interface for developers to interact with Amazon Web Services (AWS) services, such as 
# Amazon S3, Amazon EC2, Amazon DynamoDB, and more.
# License: MIT
ExternalProject_Add(
    aws-sdk
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/aws-sdk
    GIT_REPOSITORY https://github.com/aws/aws-sdk-cpp.git
    GIT_TAG 1.11.31
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Azure
if(BUILD_AZURE)
# Azure SDK for C++ is a C++ library that provides a set of APIs for accessing and 
# interacting with various Azure services. It includes modules for working with Azure 
# Storage, Azure Cosmos DB, Azure Key Vault, Azure Event Hubs, and other Azure services. 
# License: MIT
ExternalProject_Add(
    azure-sdk
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/azure-sdk
    GIT_REPOSITORY https://github.com/Azure/azure-sdk-for-cpp.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Google
if(BUILD_GOOGLE)
# The Google Cloud SDK a set of tools and libraries that enable developers to manage and 
# deploy their applications on GCP. With the Google Cloud SDK, developers can interact with 
# GCP resources using the command line, automate tasks, and build custom workflows.
# License: Apache 2.0
ExternalProject_Add(
    google-sdk
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/google-sdk
    GIT_REPOSITORY https://github.com/googleapis/google-cloud-cpp.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Poco
if(BUILD_POCO)
# Poco is a C++ libraries and frameworks collection that provides a variety of useful components 
# and tools for building network-centric, portable, and scalable applications. The Poco libraries 
# include modules for network programming, multithreading, data and time manipulation, and much more.
# License: Boost Software License 1.0

ExternalProject_Add(
    poco
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/poco
    GIT_REPOSITORY https://github.com/pocoproject/poco.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/install
    -DENABLE_ACTIVERECORD=OFF 
    -DENABLE_ACTIVERECORD_COMPILER=OFF 
    -DENABLE_APACHECONNECTOR=OFF 
    -DENABLE_CPPPARSER=OFF 
    -DENABLE_CRYPTO=OFF 
    -DENABLE_DATA=OFF 
    -DENABLE_DATA_MYSQL=OFF 
    -DENABLE_DATA_ODBC=OFF 
    -DENABLE_DATA_POSTGRESQL=OFF 
    -DENABLE_DATA_SQLITE=OFF 
    -DENABLE_ENCODINGS=OFF 
    -DENABLE_ENCODINGS_COMPILER=OFF 
    -DENABLE_FOUNDATION=ON 
    -DENABLE_JSON=OFF 
    -DENABLE_JWT=OFF 
    -DENABLE_MONGODB=OFF 
    -DENABLE_NET=OFF 
    -DENABLE_NETSSL=OFF 
    -DENABLE_NETSSL_WIN=OFF 
    -DENABLE_PAGECOMPILER=OFF 
    -DENABLE_PAGECOMPILER_FILE2PAGE=OFF 
    -DENABLE_PDF=OFF 
    -DENABLE_POCODOC=OFF 
    -DENABLE_PROMETHEUS=OFF 
    -DENABLE_REDIS=OFF 
    -DENABLE_SEVENZIP=OFF 
    -DENABLE_TESTS=OFF 
    -DENABLE_UTIL=ON 
    -DENABLE_XML=OFF 
    -DENABLE_ZIP=ON
    -DBUILD_SHARED_LIBS=OFF  # Disables shared libraries and enables static libraries
    -DBUILD_STATIC=ON 
)
endif()



# Boost
if(BUILD_BOOST)
# Boost is a widely-used set of C++ libraries that provides a broad range of functionality for 
# developing high-quality software applications. The Boost libraries cover a wide range of areas 
# including algorithms, data structures, networking, and more. 
# License: Boost Software License 1.0
ExternalProject_Add(
    boost
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/install
)
endif()



# FMT
if(BUILD_FMT)
# 
# License: MIT
ExternalProject_Add(
    fmt
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Cli
if(BUILD_CLI)
# A cross-platform header only C++14 library for interactive command line interfaces (Cisco style)
# License: Boost Software License 1.0
ExternalProject_Add(
    cli
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/cli
    GIT_REPOSITORY https://github.com/daniele77/cli.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Task
if(BUILD_TASK)
# A General-purpose Parallel and Heterogeneous Task Programming System.
# License: MIT
ExternalProject_Add(
    task
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/task
    GIT_REPOSITORY https://github.com/taskflow/taskflow.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/install
)
endif()



# Thrust
if(BUILD_THRUST)
# Thrust is a parallel algorithms library which resembles the C++ Standard Template Library (STL). 
# Thrust’s high-level interface greatly enhances programmer productivity while enabling performance 
# portability between GPUs and multicore CPUs. 
# License: Apache 2.0
ExternalProject_Add(
    thrust
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/thrust
    GIT_REPOSITORY https://github.com/NVIDIA/thrust.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/install
)
endif()



# Redis
if(BUILD_REDIS)
# Redis is an open-source, in-memory data structure store that is used as a database, 
# cache, and message broker. 
# License: BSD 3-Clause
ExternalProject_Add(
    redis
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/redis
    GIT_REPOSITORY https://github.com/redis/redis.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
    # Build redis before poco c++ so poco will have redis support when its built.
    if(BUILD_POCO)
        add_dependencies(poco redis)
    endif()
endif()



# PostgreSQL
if(BUILD_POSTGRESQL)
# PostgreSQL, often referred to simply as "Postgres," is a powerful open-source relational database management 
# system (RDBMS) that was first released in 1989. It is designed to be highly reliable, scalable, and flexible, 
# and is widely used in many different types of applications, including web applications, mobile applications, 
# and enterprise systems.
# License: PostgreSQL License
ExternalProject_Add(
    postgresql
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/postgresql
    GIT_REPOSITORY https://git.postgresql.org/git/postgresql.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install 
)
    # Build postgresql before poco c++ so poco will have redis support when its built.
    if(BUILD_POCO)
        add_dependencies(poco postgresql)
    endif()
endif()



# Sqlite
if(BUILD_SQLITE)
# SQLite is a free, open-source, serverless relational database management system (RDBMS) that is widely 
# used in many different types of applications, including web browsers, mobile devices, and desktop software. 
# License: Public Domain
ExternalProject_Add(
    sqlite
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/sqlite
    GIT_REPOSITORY https://github.com/sqlite/sqlite.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install 
)
    # Build sqlite before poco c++ so poco will have redis support when its built.
    if(BUILD_POCO)
        add_dependencies(poco sqlite)
    endif()
endif()



# LevelDB
if(BUILD_LEVELDB)
# LevelDB is an open-source, key-value store database that was developed by Google. It is 
# designed to be fast, efficient, and scalable, and is widely used in many different types 
# of applications, including distributed systems, messaging systems, and data analytics platforms.
# License: BSD 3-Clause
ExternalProject_Add(
    leveldb
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/leveldb
    GIT_REPOSITORY https://github.com/google/leveldb.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install 
)
endif()



# Memcached
if(BUILD_MCACHED)
# Memcached is a distributed caching system that is designed to accelerate dynamic web 
# applications by reducing database load.
# License: BSD 3-Clause
ExternalProject_Add(
    memcached
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/memcached
    GIT_REPOSITORY https://github.com/memcached/memcached.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install 
)
endif()



# LMDB
if(BUILD_LMDB)
# LMDB (Lightning Memory-Mapped Database) is a high-performance, transactional, key-value 
# store database that was developed by Symas Corporation.
# License: OpenLDAP Public License
ExternalProject_Add(
    lmdb
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/lmdb
    GIT_REPOSITORY https://github.com/LMDB/lmdb.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install 
)
endif()



# ArangoDB
if(BUILD_ARANGODB)
# ArangoDB is a native multi-model database with flexible data models for documents, 
# graphs, and key-values. Build high performance applications using a convenient SQL-like 
# query language or JavaScript extensions.
# License: Apache 2.0
ExternalProject_Add(
    arangodb
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/arangodb
    GIT_REPOSITORY https://github.com/arangodb/arangodb.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install 
)
endif()



# Skia
if(BUILD_SKIA)
  # Clone depot_tools using add_custom_command and add_custom_target
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/depot_tools
    COMMAND git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src
  )
  add_custom_target(depot_tools_target ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/depot_tools)

  # Add depot_tools to path
  set(PATH "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/depot_tools:$ENV{PATH}" CACHE INTERNAL "")

  # Clone Skia repository using add_custom_command and add_custom_target
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia
    COMMAND git clone https://skia.googlesource.com/skia.git
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src
  )
  add_custom_target(skia_target ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia)

  # Sync dependencies using add_custom_command and add_custom_target
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/.deps
    COMMAND python3 tools/git-sync-deps
    DEPENDS skia_target
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia
  )
  add_custom_target(sync_deps_target ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/.deps)

  # Fetch Ninja using add_custom_command and add_custom_target
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/bin/ninja
    COMMAND python3 tools/git-sync-deps
    DEPENDS sync_deps_target
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia
  )
  add_custom_target(fetch_ninja_target ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/bin/ninja)

  # Generate build files with GN using add_custom_command and add_custom_target
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/out/Static
    COMMAND bin/gn gen out/Static
    DEPENDS fetch_ninja_target
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia
  )
  add_custom_target(generate_build_files_target ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/out/Static)

  # Build with Ninja using add_custom_command and add_custom_target
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/out/Static/libskia.a
    COMMAND ninja -C out/Static
    DEPENDS generate_build_files_target
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia
  )
  add_custom_target(build_target ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/out/Static/libskia.a)

  # Install Skia libraries and include files
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/out/Static/
          DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/install/lib)

  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/skia/include/
          DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/install/include)
endif()



# OIIO
if(BUILD_OIIO)
# OpenImageIO is a C++ library that provides a simple and powerful interface for 
# reading and writing image files. It is designed to support a wide range of image 
# file formats and color spaces, and it includes advanced features such as multi-threaded 
# reading and writing, color space conversion.
# License: MIT
ExternalProject_Add(
    oiio
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/oiio
    GIT_REPOSITORY https://github.com/OpenImageIO/oiio.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Box2D
if(BUILD_BOX2D)
# Box2D is a C++ physics engine library that is designed to simulate 2D rigid-body 
# physics. It is commonly used in video games and other interactive applications to 
# simulate collisions, forces, and motion of objects in a 2D world.
# License: MIT
ExternalProject_Add(
    box2d
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Yoga
if(BUILD_YOGA)
# 
# License: MIT
ExternalProject_Add(
    yoga
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/yoga
    GIT_REPOSITORY https://github.com/facebook/yoga.git
    GIT_TAG main
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# VulkanScenegraph
if(BUILD_VSG)
# 
# License: MIT
ExternalProject_Add(
    vsg
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/vsg
    GIT_REPOSITORY https://github.com/vsg-dev/VulkanSceneGraph.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Point Cloude Library
if(BUILD_PCL)
# 
# License: BSD
ExternalProject_Add(
    pcl
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/pcl
    GIT_REPOSITORY https://github.com/PointCloudLibrary/pcl.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# Libosmium
if(BUILD_LIBOSMIUM)
# Libosmium is a C++ library for working with OpenStreetMap data. 
# It provides tools for reading, writing, and manipulating OSM data 
# in various formats, as well as tools for working with OSM geometries and tags.
# License: Boost Software License 1.0
ExternalProject_Add(
    libosmium
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/libosmium
    GIT_REPOSITORY https://github.com/osmcode/libosmium.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# GDAL
if(BUILD_GDAL)
# GDAL is a C++ library for reading, writing, and manipulating raster 
# and vector geospatial data. It supports a wide variety of file formats 
# used in GIS and remote sensing applications and provides tools for working 
# with spatial referencing, coordinate transformation, and data reprojection.
# License: MIT
ExternalProject_Add(
    gdal
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/gdal
    GIT_REPOSITORY https://github.com/osmcode/libosmium.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()



# OSRM
if(BUILD_OSRM)
# OSRM is a C++ library for routing on OpenStreetMap data. It provides tools 
# for calculating shortest paths and travel times between points on a map, as 
# well as tools for generating isochrones and other routing-related data.
# License: BSD 2 Clause
ExternalProject_Add(
    libosrm
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty/src/libosrm
    GIT_REPOSITORY https://github.com/Project-OSRM/osrm-backend.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty/install
)
endif()
