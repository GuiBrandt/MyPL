add_library(lexer OBJECT token.c)

add_executable(ilexer main.c)
target_link_libraries(ilexer lexer)