#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/detail/common.h>
#include <pybind11/stl_bind.h>

#include "point.hpp"
#include "rasterization_cells.hpp"
#include "rasterization_context.hpp"

namespace py = pybind11;

inline void BindRasterizationCellsClass(::pybind11::module_ &m){
    py::class_<RasterizationCells>(m, "RasterizationCells")
        .def(py::init<std::vector<Point>>())
        .def("GetCellSet", &RasterizationCells::GetCellSet, "Get the cell set")
        .def("Union", &RasterizationCells::Union, "Get the cell set")
        .def("Cut", &RasterizationCells::Cut, "Get the cell set")
        .def("Intersect", &RasterizationCells::Intersect, "Get the cell set")
        .doc() = "A Rasterization Cell class for store the cell and do some operation";
}