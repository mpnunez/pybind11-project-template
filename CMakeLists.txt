cmake_minimum_required(VERSION 3.4...3.18)
project(cmake_example)

# Build C++ code only as a static library
add_library(cboo STATIC
    src/interval.cpp
    src/intervalset.cpp
    )
target_compile_features(cboo PRIVATE cxx_std_17)
target_compile_options(cboo PRIVATE -Wall -Wpedantic -Weffc++ -Wextra -Wfatal-errors)
set_property(TARGET cboo PROPERTY POSITION_INDEPENDENT_CODE ON)

# Create binding so file and link to C++ library
add_subdirectory(pybind11)
# pybind11_add_module target name must match python module name
pybind11_add_module(boopyb src/python_binder.cpp)
target_include_directories(boopyb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(boopyb PUBLIC cboo)

