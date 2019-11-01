set(exe_name "catch2_sc-ide_tests")
add_executable(${exe_name} main.cpp)
target_link_libraries( ${exe_name} libscide)

# TODO If we keep this approach, add Catch2 to external_libraries

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
