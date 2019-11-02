# TODO Would be nice to remove autogen targets from CLion's list of available targets
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Test REQUIRED)

# Work out how to add include multiple tests in one executable
# https://stackoverflow.com/questions/12194256/qt-how-to-organize-unit-test-with-more-than-one-class

set(exe_name "qttest_goto_line_tool_tests")
add_executable(${exe_name} widgets/goto_line_tool_tests.cpp)
target_link_libraries( ${exe_name} libscide Qt5::Test )
add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})


set(exe_name "qttest_color_widget_tests")
add_executable(${exe_name}
        widgets/util/color_widget_tests.cpp
        )
target_link_libraries( ${exe_name} libscide Qt5::Test )
add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
