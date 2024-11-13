#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/detail/common.h>
#include <pybind11/stl_bind.h>

#include "point.hpp"
#include "rasterization_context.hpp"

namespace py = pybind11;

inline void BindRasterizationContextClass(::pybind11::module_ &m){
    py::class_<RasterizationContext>(m, "RasterizationContext")
        .def(py::init<double>())
        .def("AddPolygon", &RasterizationContext::AddPolygon, "Add Polygon")
        .def("GetPolygonCell", &RasterizationContext::GetPolygonCell, "Get the cell of Polygon")
        // .def("GetVertexs", &Polygon::GetVertexs, "Get the vertexs of polygon")
        .doc() = "A RasterizationContext class for add multiple polygon into rasterization";
}