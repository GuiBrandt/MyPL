add_library(lexer OBJECT token.c)
target_link_libraries(lexer PUBLIC util)

add_executable(ilexer main.c)
target_link_libraries(ilexer lexer util)