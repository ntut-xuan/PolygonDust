cmake_minimum_required(VERSION 3.20)
project(PolygonDust)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -pedantic -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -O3 -g")

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set (GOOGLETEST_LIBRARIES "${CMAKE_BINARY_DIR}/_deps/googletest-src/googletest/include")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set (GOOGLEMOCK_LIBRARIES "${CMAKE_BINARY_DIR}/_deps/googletest-src/googlemock/include")
FetchContent_MakeAvailable(googletest)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

set(SOURCES ${SOURCES}
    src/polygon.cpp
    src/point.cpp
)

set(BINDINGS
    src/main_pyb.cpp
)

set(TESTS
    tests/cpp/ut_point.cpp
    tests/cpp/ut_polygon.cpp
    tests/cpp/ut_utility.cpp
    tests/cpp/ut_line.cpp
    tests/cpp/ut_rasterization.cpp
    tests/cpp/ut_rasterization_context.cpp
    tests/cpp/ut_rasterization_cells.cpp
    tests/cpp/ut_vectorization.cpp
    tests/cpp/ut_polygon_clipping.cpp
)

option(COVERAGE "Enable coverage" OFF)

if(COVERAGE)
    set(CMAKE_C_FLAGS "--coverage -g -O0")
    set(CMAKE_CXX_FLAGS "--coverage -g -O0")

    include(scripts/CodeCoverage.cmake)
    set(CODE_COVERAGE_VERBOSE ON)
    set(COVERAGE_EXCLUDE
            ${CMAKE_BINARY_DIR}/_deps/*
            ${PROJECT_SOURCE_DIR}/test/*
            ${PROJECT_SOURCE_DIR}/pyb_includes/*
            ${PROJECT_SOURCE_DIR}/src/main_pyb.cpp
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(GCOVR_ADDITIONAL_ARGS
                --gcov-executable "llvm-cov gcov"
        )
    endif()

    append_coverage_compiler_flags()
    
    setup_target_for_coverage_gcovr_html(
        NAME polygondust-coverage
        DEPENDENCIES PolygonDust
        EXCLUDE ${COVERAGE_EXCLUDE}
    )

    setup_target_for_coverage_gcovr_xml(
        NAME polygondust-coverage-xml
        DEPENDENCIES PolygonDust
        EXCLUDE ${COVERAGE_EXCLUDE}
    )
endif()

include_directories(PolygonDust "${CMAKE_SOURCE_DIR}/includes")
include_directories(PolygonDust "${CMAKE_SOURCE_DIR}/pyb_includes")

add_library(PolygonDust MODULE "${SOURCES}" "${BINDINGS}")
target_link_libraries(PolygonDust PRIVATE GTest::gtest_main pybind11::module)
set_target_properties(PolygonDust PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")

enable_testing()
add_executable(PolygonDust-gtest "${SOURCES}" "${TESTS}")
target_link_libraries(PolygonDust-gtest PUBLIC GTest::gtest_main pybind11::module)
set_target_properties(PolygonDust-gtest
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)
include(GoogleTest)
gtest_discover_tests(PolygonDust-gtest)