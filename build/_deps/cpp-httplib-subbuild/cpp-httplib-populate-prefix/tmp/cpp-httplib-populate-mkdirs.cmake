# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-src")
  file(MAKE_DIRECTORY "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-build"
  "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-subbuild/cpp-httplib-populate-prefix"
  "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-subbuild/cpp-httplib-populate-prefix/tmp"
  "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-subbuild/cpp-httplib-populate-prefix/src/cpp-httplib-populate-stamp"
  "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-subbuild/cpp-httplib-populate-prefix/src"
  "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-subbuild/cpp-httplib-populate-prefix/src/cpp-httplib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-subbuild/cpp-httplib-populate-prefix/src/cpp-httplib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/adria/Dropbox/minecraft/adri/c++/te-tetris/te-tetris/build/_deps/cpp-httplib-subbuild/cpp-httplib-populate-prefix/src/cpp-httplib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
