include_directories(include)

add_subdirectory(util)

link_libraries(util)

add_subdirectory(lexer)
add_subdirectory(parser)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(tests)
endif()
