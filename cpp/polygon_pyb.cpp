#include <pybind11/pybind11.h>
#include <pybind11/detail/common.h>

#include "polygon.hpp"

namespace py = pybind11;

PYBIND11_MODULE(PolygonDust, m){
    m.doc() = R"pbdoc(
        PolygonDust
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           Polygon
    )pbdoc";

    py::class_<Polygon>(m, "Polygon")
        .def(py::init())
        .def("GetArea", &Polygon::GetArea, "Get the area of polygon")
        .doc() = "A Polygon class for create a polygon";
}