cmake_minimum_required(VERSION 3.6)
project(CommonTests)

#set variables
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_BUILD_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -g")
endif()

#show settings
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("Working dir = ${CMAKE_CURRENT_SOURCE_DIR}")
message("Build dir = ${CMAKE_CURRENT_SOURCE_DIR}/build")
message("Bin dir = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources")

#build
file(GLOB_RECURSE SOURCE_FILES
        "${INCLUDE_DIR}/*.hpp"
        "${SOURCE_DIR}/*.hpp"
        "${SOURCE_DIR}/*.cpp"
)
list(APPEND SOURCE_FILES "main.cpp")


#message(WARNING ${SOURCE_DIR})
include_directories(${INCLUDE_DIR})
add_executable(CommonTests ${SOURCE_FILES}) 

