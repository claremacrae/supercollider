set(exe_name "qttest_sc-ide_tests")

# TODO Would be nice to remove autogen targets from CLion's list of available targets
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CLion
# to always look for includes there, to stop it complaining about
# missing .moc files in tests that use Qt Test.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${exe_name}
        main.cpp
        test_helpers/auto_test.hpp
        # All of these files must register their tests using "auto_test.hpp":
        widgets/goto_line_tool_tests.cpp
        widgets/util/color_widget_tests.cpp
        )

target_include_directories(${exe_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test_helpers
        )

find_package(Qt5 COMPONENTS Test REQUIRED)
target_link_libraries( ${exe_name} libscide Qt5::Test common_test_code)

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
