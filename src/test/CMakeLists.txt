cmake_minimum_required(VERSION 2.8)

add_executable(test_casts casts.cpp)
target_link_libraries(test_casts ${Boost_LIBRARIES})

add_executable(test_registers registers.cpp)
target_link_libraries(test_registers ${Boost_LIBRARIES})

add_executable(test_protobuf protobuf.cpp)
target_link_libraries(test_protobuf mantibase ${Boost_LIBRARIES} ${Protobuf_LIBRARIES})

add_test(test_manticore_casts test_casts)
add_test(test_manticore_registers test_registers)
add_test(test_manticore_protobuf test_protobuf)
