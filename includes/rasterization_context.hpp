#ifndef RASTERIZATION_CONTEXT_HPP
#define RASTERIZATION_CONTEXT_HPP

#include "point.hpp"
#include "polygon.hpp"
#include <algorithm>
#include <vector>

class RasterizationContext {
private:
    double min_x;
    double max_x;
    double min_y;
    double max_y;
    double edge;
    std::vector<std::vector<Point>> polygons_cells;
public:
    RasterizationContext(double edge){
        this->edge = edge;
    }
    void AddPolygon(Polygon polygon){
        std::vector<Point> polygon_vertex = polygon.GetVertexs();
    }
};

#endif