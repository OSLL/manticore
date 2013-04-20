project(manticore CXX)

cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS unit_test_framework program_options regex REQUIRED)
message(STATUS "Boost Libraries: " ${Boost_LIBRARIES})
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
message(STATUS "Protobuf Libraries: " ${PROTOBUF_LIBRARIES})

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -Werror -Wall")
set(ARCH i386)
ADD_DEFINITIONS(-DARCH=${ARCH})

set(MANTICORE_BIN ${CMAKE_BINARY_DIR})
set(MANTICORE_PROTO_GEN ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
set(MANTICORE_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/inc)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MANTICORE_BIN}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MANTICORE_BIN}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${MANTICORE_INCLUDE_PATH})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_subdirectory(src)
