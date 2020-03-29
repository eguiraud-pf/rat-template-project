## PROJECT SETUP
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Rat-Template VERSION 1.0.0 LANGUAGES CXX)

# switchboard
option(ENABLE_TESTING "Build unit/system tests" ON)
option(ENABLE_EXAMPLES "Build examples" ON)
option(ENABLE_CUDA "Build with CUDA GPU acceleration" ON)

# set build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -O3")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# find rat-models library
find_package(RatModels)

# set the model
add_executable(solenoid solenoid.cpp)
target_link_libraries(solenoid Rat::Models)
if(CMAKE_CUDA_COMPILER)
	set_target_properties(solenoid PROPERTIES LINKER_LANGUAGE CUDA)
endif()




