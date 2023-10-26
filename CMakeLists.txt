cmake_minimum_required(VERSION 3.4...3.18)
project(boo)

# Build C++ code only as a static library
add_library(cboo STATIC
    src/interval.cpp
    src/intervalset.cpp
    )
target_compile_features(cboo PRIVATE cxx_std_17)
target_compile_options(cboo PRIVATE -Wall -Wpedantic -Weffc++ -Wextra -Wfatal-errors)
set_property(TARGET cboo PROPERTY POSITION_INDEPENDENT_CODE ON)

# Add tests
#enable_testing()
#set(GTEST_ROOT /usr/intel/pkgs/googletest/1.10.0)
#find_package(GTest 1.10 REQUIRED)
add_subdirectory(googletest)



enable_testing()
# Specify target to build
add_executable(cboopyb_unit_tests  src/test_cboo.cpp src/main_tests.cpp)
target_link_libraries(cboopyb_unit_tests PUBLIC cboo GTest::gtest_main)
target_compile_features(cboopyb_unit_tests PRIVATE cxx_std_17)
target_compile_options(cboopyb_unit_tests PRIVATE -Wall -Wpedantic -Weffc++ -Wextra -Wfatal-errors)
target_include_directories(cboopyb_unit_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(cboopyb_unit_tests)

# Create binding so file and link to C++ library
add_subdirectory(pybind11)
# pybind11_add_module target name must match python module name
pybind11_add_module(boopyb src/python_binder.cpp)
target_include_directories(boopyb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(boopyb PUBLIC cboo)

