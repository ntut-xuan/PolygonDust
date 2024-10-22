#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/detail/common.h>

#include "point.hpp"
#include "polygon.hpp"

namespace py = pybind11;

inline void BindPolygonClass(::pybind11::module_ &m){
    py::class_<Polygon>(m, "Polygon")
        .def(py::init())
        .def(py::init<std::vector<Point>>())
        .def("GetArea", &Polygon::GetArea, "Get the area of polygon")
        .def("GetVertexs", &Polygon::GetVertexs, "Get the vertexs of polygon")
        .def("GetBoundaryCell", &Polygon::GetBoundaryCell, "Get the boundary cell of polygon")
        .doc() = "A Polygon class for create a polygon";
}