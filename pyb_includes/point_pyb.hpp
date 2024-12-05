#include <memory>
#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>

#include "point.hpp"

namespace py = pybind11;

inline void BindPointClass(::pybind11::module_ &m) {
    py::class_<Point>(m, "Point")
        .def(py::init<double, double>())
        .def("GetX", &Point::GetX, "Get the X of the point")
        .def("GetY", &Point::GetY, "Get the Y of the point")
        .def("__repr__", [](const Point &d) { return d.ToString(); })
        .doc() = "A Point class for create a point";
}