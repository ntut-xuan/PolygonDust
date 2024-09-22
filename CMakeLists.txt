cmake_minimum_required(VERSION 3.27)
project(PolygonDust)


set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

set(SOURCES ${SOURCES}
    cpp/Polygon.cpp
)

set(BINDINGS
    cpp/polygon_pyb.cpp
)

pybind11_add_module(PolygonDust cpp/polygon_pyb.cpp)
install(TARGETS PolygonDust DESTINATION .)