set(exe_name "catch2_sc-ide_tests")

# TODO If we keep using catch, add Catch2 to external_libraries - as a sub-module
add_executable(${exe_name}
        main.cpp
        test_helpers/catch_qt_string_makers.hpp
        widgets/util/color_widget_tests.cpp
        catch.hpp)
target_link_libraries( ${exe_name} libscide)
target_include_directories(${exe_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/test_helpers
        )

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
