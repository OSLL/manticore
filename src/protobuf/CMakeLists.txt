cmake_minimum_required(VERSION 2.8)

set(PROTO_SRCS ${MANTICORE_LIBRARY_DIR}/snapshot.pb.cc)
set(PROTO_HDRS ${MANTICORE_LIBRARY_DIR}/snapshot.pb.h)
set(PROTO_FILES_LOCAL ${PROTO_HDRS} ${PROTO_SRCS})
set(PROTO_FILES ${PROTO_SRCS} PARENT_SCOPE)

add_custom_command(OUTPUT ${PROTO_FILES_LOCAL}
                   COMMAND protoc
                   ARGS -I=${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${MANTICORE_LIBRARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/snapshot.proto)
add_custom_target(protobuf_generate DEPENDS ${PROTO_FILES})
