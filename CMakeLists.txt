#------------------------------------------------------------------------------
# Copyright (c) 2015 The University of Manchester, UK.
#
# BSD Licenced. See LICENCE for details.
#
# CppMT-replay was developed in the IDInteraction project, funded by the
# Engineering and Physical Sciences Research Council, UK through grant
# agreement number EP/M017133/1.
#
# Author: Robert Haines
#------------------------------------------------------------------------------

project(REPLAY CXX)

cmake_minimum_required(VERSION 2.6)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}
    CACHE
    INTERNAL
    "Build the executable in the root directory"
    FORCE
  )
endif(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

add_definitions ("-Wall")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src)
