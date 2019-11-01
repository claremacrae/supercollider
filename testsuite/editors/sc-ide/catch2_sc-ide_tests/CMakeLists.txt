set(exe_name "catch2_sc-ide_tests")

# TODO If we keep this approach, add Catch2 to external_libraries
add_executable(${exe_name}
        main.cpp
        catch_qt_string_makers.hpp
        color_widget_tests.cpp
        catch.hpp)
target_link_libraries( ${exe_name} libscide)

add_test(${exe_name} ${EXECUTABLE_OUTPUT_PATH}/${exe_name})
