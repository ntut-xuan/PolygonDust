#ifndef POLYGON_H
#define POLYGON_H

#include "point.hpp"
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class Polygon {
private:
    std::vector<Point> vertexs;
public:
    Polygon() = default;
    Polygon(py::list list){
        for(auto item : list){
            vertexs.push_back(item.cast<Point>());
        }
    }
    Polygon(std::vector<Point> vertexs){
        this->vertexs = vertexs;
    }
    ~Polygon() = default;
    std::vector<Point> GetVertexs();
    std::set<Point> GetBoundaryCell(double cellGap);
    double GetArea();
};

#endif
