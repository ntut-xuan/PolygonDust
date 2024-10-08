cmake_minimum_required(VERSION 3.20)
project(PolygonDust)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -Og")

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
    cpp/polygon.cpp
    cpp/point.cpp
)

set(BINDINGS
    cpp/main_pyb.cpp
)

set(TESTS
    tests/cpp/ut_point.cpp
    tests/cpp/ut_polygon.cpp
    tests/cpp/ut_utility.cpp
)

add_library(PolygonDust MODULE "${SOURCES}" "${BINDINGS}")
target_link_libraries(PolygonDust PRIVATE pybind11::module)
set_target_properties(PolygonDust PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                     SUFFIX "${PYTHON_MODULE_EXTENSION}")



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