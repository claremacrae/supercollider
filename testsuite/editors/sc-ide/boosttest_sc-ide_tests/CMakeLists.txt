set(exe_name "boosttest_sc-ide_tests")

add_executable(${exe_name}
        main.cpp
        test_helpers/boosttest_qt_string_makers.hpp
        widgets/goto_line_tool_tests.cpp
        widgets/util/color_widget_tests.cpp
        )

target_include_directories(${exe_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test_helpers
        )

# We use catch to manage all the test cases and assertions.
# However, Qt Test's QSignalSpy and similar code can also be used to help in writing tests.
# Qt Test's assertions like QVERIFY, QCOMPARE MUST NOT BE USED as any test failures are currently not detected
find_package(Qt5 COMPONENTS Test REQUIRED)
target_link_libraries( ${exe_name} libscide boost_test Qt5::Test )

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
