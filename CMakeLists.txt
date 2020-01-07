cmake_minimum_required(VERSION 3.0)

project(MyPL VERSION 0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    enable_testing()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mypl/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/mypl/config.h)

include_directories(include)

add_subdirectory(src)
