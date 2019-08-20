cmake_minimum_required(VERSION 3.14)
project(cs61c_proj1_johnschulz)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs61c_proj1_johnschulz
        nbproject/private/c_standard_headers_indexer.c
        nbproject/private/cpp_standard_headers_indexer.cpp
        flight_structs.h
        flights.c
        flights.h
        RouteTime.c
        timeHM.c
        timeHM.h)
