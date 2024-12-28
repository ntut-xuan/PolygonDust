#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "vectorization_context.hpp"

#include "polygon.hpp"

namespace py = pybind11;

inline void BindVectorizationContextClass(::pybind11::module_ &m) {
    py::class_<VectorizationContext>(m, "VectorizationContext")
        .def(py::init<Polygon>())
        .def("ClipPolygon", &VectorizationContext::ClipPolygon, "Clip polygon")
        .def("GetResult", &VectorizationContext::GetResult, "Get clipped polygon result")
        .def("GetIntersectPoint", &VectorizationContext::GetIntersectPoints, "Get intersect points")
        .def("__enter__", [](VectorizationContext &self) { return &self; })
        .def("__exit__",
             [](VectorizationContext, py::object, py::object, py::object) {

             })
        // .def("GetVertexs", &Polygon::GetVertexs, "Get the vertexs of polygon")
        .doc() = "A VectorizationContext class for add multiple polygon into vectorization";
}