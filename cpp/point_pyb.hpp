#include <pybind11/pybind11.h>
#include <pybind11/detail/common.h>

#include "point.hpp"

namespace py = pybind11;

inline void BindPointClass(::pybind11::module_ &m){
    py::class_<Point>(m, "Point")
        .def(py::init<int, int>())
        .def("GetX", &Point::GetX, "Get the X of the point")
        .def("GetY", &Point::GetY, "Get the Y of the point")
        .doc() = "A Point class for create a point";
}