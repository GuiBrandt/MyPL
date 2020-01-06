include_directories(include)

add_subdirectory(util)

link_libraries(util)

add_subdirectory(lexer)
add_subdirectory(parser)

add_subdirectory(tests)
