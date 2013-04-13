project(mantibase CXX)

cmake_minimum_required(VERSION 2.8)

set(PROCESS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/process)
set(PTRACE_DIR "${PROCESS_DIR}/ptrace/${ARCH}")
set(PROC_DIR "${PROCESS_DIR}/proc/${ARCH}")

message(STATUS "PROCESS DIR: " ${PROCESS_DIR})
message(STATUS "PTRACE DIR: " ${PTRACE_DIR})
message(STATUS "PROC DIR: " ${PROC_DIR})
message(STATUS "PROTOBUF FILES: " ${PROTO_FILES})

file(GLOB PTRACE_SRC ${PTRACE_DIR}/*.cpp)
file(GLOB PROC_SRC ${PROC_DIR}/*.cpp)
list(APPEND PROCESS_SRC ${PTRACE_SRC} ${PROC_SRC} ${PROTO_FILES} serialize.cpp)

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(LIBMANTICORE_SRC ${PROCESS_SRC} serialize.cpp)
add_library(mantibase STATIC ${LIBMANTICORE_SRC})
target_link_libraries(mantibase ${Boost_LIBRARIES} ${Protobuf_LIBRARIES})
