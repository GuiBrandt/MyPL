remove_definitions(-DNDEBUG)

macro(discover_tests)
    file(GLOB tests *.c)

    set(arg_list "${ARGN}")
    list(JOIN arg_list _ prefix)
    list(JOIN arg_list / hierarchy)

    foreach(test_source IN LISTS tests)
        get_filename_component(test_name ${test_source} NAME_WE)
        
        set(test_executable ${prefix}_${test_name})
        set(test_name ${hierarchy}/${test_name})

        add_executable(${test_executable} ${test_source})
        add_test(NAME ${test_name} COMMAND ${test_executable})
    endforeach()
endmacro()

add_subdirectory(lexer)
add_subdirectory(util)