#include <pybind11/pybind11.h>
#include <pybind11/detail/common.h>

#include "point_pyb.hpp"
#include "polygon_pyb.hpp"

PYBIND11_MODULE(PolygonDust, m){
    m.doc() = R"pbdoc(
        PolygonDust
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           Polygon
    )pbdoc";

    BindPointClass(m);
    BindPolygonClass(m);
}