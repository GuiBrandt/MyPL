cmake_minimum_required(VERSION 3.0)

project(MyPL VERSION 0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    enable_testing()
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -pg")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -pg")
    else()
        message("Profiling and code coverage are only supported for GNU GCC at the moment.")
        message("Please consider changing your compiler if you need this feature.")
    endif()
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mypl/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/mypl/config.h)

file(GLOB public_headers ${CMAKE_CURRENT_SOURCE_DIR}/src/include/public/*.h)
foreach(header IN LISTS public_headers)
    file(READ ${header} contents)
    file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/include/mypl/mypl.h "${contents}")
    unset(contents)
endforeach()

include_directories(include)

add_subdirectory(src)
