cmake_minimum_required(VERSION 3.14)
project(flight_management)

set(CMAKE_CXX_STANDARD 14)

add_executable(flight_management src/main.cpp src/flight_database.cpp
               src/flight_info_read_operations.cpp src/flight_info_write_operations.cpp
               src/flight_management.cpp)
include_directories(src)
