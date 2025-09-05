cmake_minimum_required(VERSION 3.0)

add_executable(test_api_read test_api_read.c)
target_link_libraries(test_api_read libregmap)
add_test(test_api_read test_api_read)

add_executable(test_api_write test_api_write.c)
target_link_libraries(test_api_write libregmap)
add_test(test_api_write test_api_write)

add_executable(test_api_update_bits test_api_update_bits.c)
target_link_libraries(test_api_update_bits libregmap)
add_test(test_api_update_bits test_api_update_bits)

add_executable(test_u8_array test_u8_array.c)
target_link_libraries(test_u8_array libregmap)
add_test(test_u8_array test_u8_array)

add_executable(test_u16_array test_u16_array.c)
target_link_libraries(test_u16_array libregmap)
add_test(test_u16_array test_u16_array)

add_executable(test_access test_u16_array.c)
target_link_libraries(test_access libregmap)
add_test(test_access test_access)
