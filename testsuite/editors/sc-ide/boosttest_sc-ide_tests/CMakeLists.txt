set(exe_name "boosttest_sc-ide_tests")

add_executable(${exe_name}
        main.cpp
        )

target_link_libraries( ${exe_name} libscide boost_test )

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
