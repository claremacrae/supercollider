set(exe_name "qttest_sc-ide_tests")

set(CMAKE_AUTOMOC ON)

# Work out how to add include multiple tests in one executable
# https://stackoverflow.com/questions/12194256/qt-how-to-organize-unit-test-with-more-than-one-class

add_executable(${exe_name}
        widgets/util/color_widget_tests.cpp
        )

find_package(Qt5 COMPONENTS Test REQUIRED)
target_link_libraries( ${exe_name} libscide Qt5::Test )

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
