cmake_minimum_required(VERSION 3.14)
project(flight_management)

set(CMAKE_CXX_STANDARD 14)

add_executable(flight_management src/main.cpp src/flight_database.cpp
               src/flight_info_read_operations.cpp src/flight_info_write_operations.cpp
               src/flight_management.cpp)
#add_executable(flight_database_test flight_databse_test.cpp source/flight_database.cpp)
include_directories(src)
target_include_directories(flight_management  PUBLIC include)
#target_include_directories(flight_database_test  PUBLIC include)

