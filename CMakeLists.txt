cmake_minimum_required(VERSION 3.0)

add_library(libregmap STATIC)
target_sources(libregmap PUBLIC ${CMAKE_CURRENT_LIST_DIR}/source/regmap.c)
target_include_directories(libregmap PUBLIC ${CMAKE_CURRENT_LIST_DIR}/source)
target_compile_options(libregmap PUBLIC -Wall)

if(REGMAP_TEST)
  enable_testing()
  add_subdirectory(tests)
endif()
