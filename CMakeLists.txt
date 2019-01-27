cmake_minimum_required(VERSION 2.8)
project(astronomy)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.67.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(include)

enable_testing()

add_subdirectory (test)
