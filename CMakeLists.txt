cmake_minimum_required(VERSION 3.27)
project(PolygonDust)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Werror -Og")

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

set(SOURCES ${SOURCES}
    cpp/Polygon.cpp
)

set(BINDINGS
    cpp/polygon_pyb.cpp
)

add_library(PolygonDust MODULE "${SOURCES}" "${BINDINGS}")
target_link_libraries(PolygonDust PRIVATE pybind11::module)
set_target_properties(PolygonDust PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                     SUFFIX "${PYTHON_MODULE_EXTENSION}")
