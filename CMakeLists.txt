## PROJECT SETUP
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Rat-Template VERSION 1.100.0 LANGUAGES CXX)

# set build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -O3")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# find rat-models library
find_package(RatModels 1.100.0 REQUIRED)

# set the model
add_executable(solenoid solenoid.cpp)
target_link_libraries(solenoid Rat::Models)
