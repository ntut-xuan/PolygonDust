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
        .def("GetMinX", &RasterizationContext::GetMinX, "Get min X")
        .def("GetMaxX", &RasterizationContext::GetMaxX, "Get max X")
        .def("GetMinY", &RasterizationContext::GetMinY, "Get min Y")
        .def("GetMaxY", &RasterizationContext::GetMaxY, "Get max Y")
        .def("__enter__", [](RasterizationContext &self) {
            return &self;
        })
        .def("__exit__", [](RasterizationContext, py::object, py::object, py::object) {
            
        })
        // .def("GetVertexs", &Polygon::GetVertexs, "Get the vertexs of polygon")
        .doc() = "A RasterizationContext class for add multiple polygon into rasterization";
}