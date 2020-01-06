include_directories(include)

add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(util)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(tests)
endif()
