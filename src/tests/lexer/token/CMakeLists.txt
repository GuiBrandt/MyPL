file(GLOB tests *.c)

foreach(test_source IN LISTS tests)
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(lexer_token_${test_name} ${test_source})
    add_test(NAME lexer/token/${test_name} COMMAND lexer_token_${test_name})
endforeach()