project(mantibase CXX)

cmake_minimum_required(VERSION 2.8)

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# common variables
set(MANTICORE_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(MANTICORE_PROTOBUF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protobuf)
set(MANTICORE_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)
set(MANTICORE_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(PROCESS_DIR ${MANTICORE_LIBRARY_DIR}/process)
set(PTRACE_DIR "${PROCESS_DIR}/ptrace")
set(PROC_DIR "${PROCESS_DIR}/proc")

# common sources
file(GLOB MANTICORE_LIB_SRC ${MANTICORE_LIBRARY_DIR}/*.cpp)
message(STATUS "MANTICORE_LIB_SRC: " ${MANTICORE_LIB_SRC})

file(GLOB PROCESS_SRC ${PROCESS_DIR}/*.cpp)
message(STATUS "PROCESS_SRC: " ${PROCESS_SRC})

file(GLOB PTRACE_SRC ${PTRACE_DIR}/*.cpp)
message(STATUS "PTRACE_SRC: " ${PTRACE_SRC})

file(GLOB PROC_SRC ${PROC_DIR}/*.cpp)
message(STATUS "PROC_SRC: " ${PROC_SRC})

# arch specific sources
file(GLOB PTRACE_ARCH_SRC ${PTRACE_DIR}/${ARCH}*.cpp)
message(STATUS "PTRACE_ARCH_SRC: " ${PTRACE_ARCH_SRC})

file(GLOB PROC_ARCH_SRC ${PROC_DIR}/${ARCH}*.cpp)
message(STATUS "PROC_ARCH_SRC: " ${PROC_ARCH_SRC})

# generate protobuf sources
set(PROTO_SRC ${MANTICORE_LIBRARY_DIR}/snapshot.pb.cc)
set(PROTO_HDR ${MANTICORE_LIBRARY_DIR}/snapshot.pb.h)
list(APPEND PROTO_FILES_ALL ${PROTO_HDR})
list(APPEND PROTO_FILES_ALL ${PROTO_SRC})
add_custom_target(protogen)
add_custom_command(
	TARGET protogen
	COMMAND protoc
	ARGS -I=${MANTICORE_PROTOBUF_DIR} --cpp_out=${MANTICORE_LIBRARY_DIR} ${MANTICORE_PROTOBUF_DIR}/snapshot.proto
)
message(STATUS "GENERATED SOURCES: " ${PROTO_FILES_ALL})
set_source_files_properties(${PROTO_FILES_ALL} PROPERTIES GENERATED TRUE)

# all sources
list(APPEND MANTICORE_LIB_SOURCES ${MANTICORE_LIB_SRC})
list(APPEND MANTICORE_LIB_SOURCES ${PROTO_SRC})
list(APPEND MANTICORE_LIB_SOURCES ${PROCESS_SRC})
list(APPEND MANTICORE_LIB_SOURCES ${PTRACE_SRC})
list(APPEND MANTICORE_LIB_SOURCES ${PROC_SRC})
list(APPEND MANTICORE_LIB_SOURCES ${PTRACE_ARCH_SRC})
list(APPEND MANTICORE_LIB_SOURCES ${PROC_ARCH_SRC})

message(STATUS "MANTICORE_LIB_SOURCES: " ${MANTICORE_LIB_SOURCES})

# build main library
add_library(mantibase STATIC ${MANTICORE_LIB_SOURCES})
target_link_libraries(mantibase ${Boost_LIBRARIES})
target_link_libraries(mantibase ${PROTOBUF_LIBRARIES})
add_dependencies(mantibase protogen)

# configure test
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)

add_executable(casts_test ${MANTICORE_TEST_DIR}/casts.cpp)
target_link_libraries(casts_test ${Boost_LIBRARIES})
message(STATUS "TEST: casts_test")

add_executable(registers_test ${MANTICORE_TEST_DIR}/registers.cpp)
target_link_libraries(registers_test ${Boost_LIBRARIES})
message(STATUS "TEST: registers_test")

add_executable(protobuf_test ${MANTICORE_TEST_DIR}/protobuf.cpp)
target_link_libraries(protobuf_test mantibase)
target_link_libraries(protobuf_test ${Boost_LIBRARIES})
target_link_libraries(protobuf_test ${PROTOBUF_LIBRARIES})
message(STATUS "TEST: protobuf_test")

add_test(casts_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/casts_test)
add_test(registers_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/registers_test)
add_test(protobuf_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/protobuf_test)
