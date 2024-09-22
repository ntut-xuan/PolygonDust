#include <pybind11/pybind11.h>
#include <pybind11/detail/common.h>

#include "polygon.hpp"

namespace py = pybind11;

inline void BindPolygonClass(::pybind11::module_ &m){
    py::class_<Polygon>(m, "Polygon")
        .def(py::init())
        .def("GetArea", &Polygon::GetArea, "Get the area of polygon")
        .doc() = "A Polygon class for create a polygon";
}