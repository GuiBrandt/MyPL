include_directories(include)

add_subdirectory(util)
add_subdirectory(common)

link_libraries(util common)

add_subdirectory(lexer)
add_subdirectory(parser)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(tests)
endif()
