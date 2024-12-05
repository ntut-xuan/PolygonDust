#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "point.hpp"
#include "polygon.hpp"

namespace py = pybind11;

inline void BindPolygonClass(::pybind11::module_ &m) {
    py::class_<Polygon>(m, "Polygon")
        .def(py::init())
        .def(py::init<std::vector<Point>>())
        .def("GetArea", &Polygon::GetArea, "Get the area of polygon")
        .def("GetVertex", &Polygon::GetVertexsVector, "Get the vertexs of polygon")
        // .def("GetVertexs", &Polygon::GetVertexs, "Get the vertexs of polygon")
        .doc() = "A Polygon class for create a polygon";
}