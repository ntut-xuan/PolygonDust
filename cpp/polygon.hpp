#ifndef POLYGON_H
#define POLYGON_H

#include "point.hpp"
#include <vector>
#include <set>

class Polygon {
private:
    std::vector<Point> vertexs;
public:
    Polygon() = default;
    Polygon(std::vector<Point> vertexs){
        this->vertexs = vertexs;
    }
    ~Polygon() = default;
    std::vector<Point> GetVertexs();
    std::set<Point> GetBoundaryCell(double cellGap);
    double GetArea();
};

#endif
