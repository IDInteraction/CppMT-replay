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

project(cmt-replay)

cmake_minimum_required(VERSION 2.6)

find_package(OpenCV REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

add_definitions ("-Wall")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cmt-replay replay.cpp)

target_link_libraries(cmt-replay ${OpenCV_LIBS})
