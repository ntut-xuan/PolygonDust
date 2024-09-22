cmake_minimum_required(VERSION 3.0)
project(PolygonDust)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(pybind11 REQUIRED)

pybind11_add_module(PolygonDust cpp/Polygon.hpp)
