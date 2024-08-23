cmake_minimum_required(VERSION 3.28)
project(Sensor_Database)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(${PROJECT_NAME} main.cpp ez_serialport.h ez_sqlite.h ez_time.h
        ez_random.h)
include(FetchContent)
FetchContent_Declare(
        SQLITE_CPP
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG master
)
FetchContent_MakeAvailable(SQLITE_CPP)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLiteCpp)

find_package(cpr CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)