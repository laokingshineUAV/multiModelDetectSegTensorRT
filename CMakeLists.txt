# Copyright (c) 2020  KDylan Corporation

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#      http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.5)

project(detect_seg_sensorrt)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

####################################
## to use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++14 -Wno-dev ${CMAKE_CXX_FLAGS} ")
####################################
set(CMAKE_BUILD_TYPE "Debug")
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    message(STATUS "CMAKE_BUILD_TYPE not defined, 'Release' will be used")
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(NOT(BIN_FOLDER))
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
        set(ARCH intel64)
    else()
        set(ARCH ia32)
    endif()

    set(BIN_FOLDER ${ARCH})
endif()
####################################
## to get verbose log,
## then, uncomment below line
#add_definitions(-DLOG_LEVEL_DEBUG)
####################################
find_package(
    catkin REQUIRED COMPONENTS
    roscpp
    roslint
    std_msgs
    sensor_msgs
    image_transport
    cv_bridge
)
# Find OpenCV libray if exists
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


catkin_package(
   INCLUDE_DIRS include
   LIBRARIES ${PROJECT_NAME}
   CATKIN_DEPENDS
   roscpp
   roslint
   cv_bridge
   image_transport
)

set(DEPENDENCIES ${OpenCV_LIBS})

include_directories(
    ${catkin_INCLUDE_DIRS}
    include
)

add_library(${PROJECT_NAME}_lib SHARED
    lib/inputs/ros_topic_input.cpp
    )
target_link_libraries(${PROJECT_NAME}_lib
    ${catkin_LIBRARIES}
    ${DEPENDENCIES}
    )

