# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/src/yoga"
  "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/src/yoga-build"
  "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga"
  "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/tmp"
  "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/src/yoga-stamp"
  "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/src"
  "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/src/yoga-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/src/yoga-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/stevenstarr/Projects/SquidKit/thirdparty/src/yoga/src/yoga-stamp${cfgdir}") # cfgdir has leading slash
endif()
