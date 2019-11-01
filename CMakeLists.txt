# Setup project
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Foxie-Geometry VERSION 0.1.0 LANGUAGES CXX)

# switchboard
set(ENABLE_CUDA 0)

# Must use GNUInstallDirs to install libraries into correct locations on all platforms.
include(GNUInstallDirs)

# Build with C++11 (for threading)
set(CMAKE_CXX_STANDARD 11)

# set build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ffast-math -fPIC -DARMA_DONT_USE_HDF5 -fvisibility=hidden -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -O3 -DNDEBUG -DARMA_NO_DEBUG")

# set modules directory-std=c++11
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# find armadillo library
find_package(Armadillo REQUIRED)
set(LIBS ${LIBS} ${ARMADILLO_LIBRARY})
include_directories(${ARMADILLO_INCLUDE_DIRS})

# find posix threads package
set(CMAKE_THREAD_LIBS_INIT "-lpthread") # needed for osx?
find_package(Threads REQUIRED)
set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})

# find blas
find_package(BLAS)
set(LIBS ${LIBS} ${BLAS_LIBRARIES})
find_package(LAPACK)
set(LIBS ${LIBS} ${LAPACK_LIBRARIES})

# Disable armadillo wrapper (for using custom BLAS)
if((BLAS_FOUND AND LAPACK_FOUND) OR NVBLAS_FOUND)
	message(STATUS "Disabling armadillo blas wrapper.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARMA_DONT_USE_WRAPPER -DARMA_USE_BLAS")
else()
	message(STATUS "Using armadillo blas wrapper.")
endif()

# CUDA GPU Kernels
if(ENABLE_CUDA)
	# enable cuda
	enable_language(CUDA)
	
	# check if cuda available
	include(CheckLanguage)
	check_language(CUDA)

	# check if nvidia
	if(CMAKE_CUDA_COMPILER_ID STREQUAL "NVIDIA")
		# inform user
		message(STATUS "CUDA found, building GPU kernels.")

		# set standard
		if(NOT DEFINED CMAKE_CUDA_STANDARD)
		    set(CMAKE_CUDA_STANDARD 11)
		    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
		endif()

		# set libraries specific to cuda
		set(CUDA_LIBRARIES -lcublas)

		# add to libraries to be linked to mlfmm
		set(LIBS ${LIBS} ${CUDA_LIBRARIES})

		# let cpp know that cuda kernels are available
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_CUDA_KERNELS")
	else()
		message(STATUS "CUDA not found.")
	endif()
endif()

# visualisation toolkit
find_package(VTK REQUIRED COMPONENTS 
	vtkCommonCore vtkCommonDataModel 
	vtkIOXML vtkFiltersCore vtkFiltersGeneral QUIET)
include_directories(${VTK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${VTK_LIBRARIES})

# find common files
find_package(RatCommon REQUIRED)
include_directories(${RAT_COMMON_INCLUDE_DIR})
set(LIBS ${LIBS} ${RAT_COMMON_LIBRARY})

# find mlfmm
find_package(RatMLFMM REQUIRED)
include_directories(${RAT_MLFMM_INCLUDE_DIR})
set(LIBS ${LIBS} ${RAT_MLFMM_LIBRARY})

# find models
find_package(RatModels REQUIRED)
include_directories(${RAT_MODELS_INCLUDE_DIR})
set(LIBS ${LIBS} ${RAT_MODELS_LIBRARY})

# find distmesh
find_package(DistMesh REQUIRED)
include_directories(${DISTMESH_INCLUDE_DIR})
set(LIBS ${LIBS} ${DISTMESH_LIBRARY})

# find json cpp library
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
#include_directories(${JSONCPP_INCLUDE_DIRS})
set(LIBS ${LIBS} ${JSONCPP_LIBRARIES})

# add header directory
include_directories(include)

# multipole-method library
add_subdirectory(src)
