#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>

#include "point_pyb.hpp"
#include "polygon_pyb.hpp"
#include "rasterization_cells_pyb.hpp"
#include "rasterization_context_pyb.hpp"
#include "vectorization_context_pyb.hpp"

PYBIND11_MODULE(PolygonDust, m) {
    m.doc() = R"pbdoc(
        PolygonDust
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           Polygon
           Point
           RasterizationContext
           RasterizationCells
    )pbdoc";

    BindPointClass(m);
    BindPolygonClass(m);
    BindRasterizationContextClass(m);
    BindRasterizationCellsClass(m);
    BindVectorizationContextClass(m);
}