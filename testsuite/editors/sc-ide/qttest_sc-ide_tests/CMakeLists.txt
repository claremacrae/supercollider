set(exe_name "qttest_sc-ide_tests")

set(CMAKE_AUTOMOC ON)

add_executable(${exe_name}
        main.cpp
        )

find_package(Qt5 COMPONENTS Test REQUIRED)
target_link_libraries( ${exe_name} libscide Qt5::Test )

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
