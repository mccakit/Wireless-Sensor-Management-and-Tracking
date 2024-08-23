# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-src"
  "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-build"
  "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-subbuild/sqlite_cpp-populate-prefix"
  "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-subbuild/sqlite_cpp-populate-prefix/tmp"
  "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-subbuild/sqlite_cpp-populate-prefix/src/sqlite_cpp-populate-stamp"
  "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-subbuild/sqlite_cpp-populate-prefix/src"
  "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-subbuild/sqlite_cpp-populate-prefix/src/sqlite_cpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-subbuild/sqlite_cpp-populate-prefix/src/sqlite_cpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/ASUS/Desktop/Efes Sensor Project/Sensor-Database/cmake-build-debug/_deps/sqlite_cpp-subbuild/sqlite_cpp-populate-prefix/src/sqlite_cpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
