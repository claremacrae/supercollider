set(lib_name "common_test_code")

add_library(${lib_name} INTERFACE)
target_include_directories(${lib_name}
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
