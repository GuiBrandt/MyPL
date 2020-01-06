cmake_minimum_required(VERSION 3.0)

project(MyPL VERSION 0.0)

enable_testing()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mypl/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/mypl/config.h)

include_directories(include)

add_subdirectory(src)
