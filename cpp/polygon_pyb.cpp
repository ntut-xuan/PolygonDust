#include <pybind11/pybind11.h>
#include <pybind11/detail/common.h>

#include "polygon.hpp"

namespace py = pybind11;

PYBIND11_MODULE(PolygonDust, m){
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    py::class_<Polygon>(m, "Polygon")
        .def(py::init())
        .def("GetArea", &Polygon::GetArea);
}