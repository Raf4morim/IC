# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-src"
  "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-build"
  "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-subbuild/matplotlib-populate-prefix"
  "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-subbuild/matplotlib-populate-prefix/tmp"
  "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-subbuild/matplotlib-populate-prefix/src/matplotlib-populate-stamp"
  "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-subbuild/matplotlib-populate-prefix/src"
  "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-subbuild/matplotlib-populate-prefix/src/matplotlib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-subbuild/matplotlib-populate-prefix/src/matplotlib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/_deps/matplotlib-subbuild/matplotlib-populate-prefix/src/matplotlib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
