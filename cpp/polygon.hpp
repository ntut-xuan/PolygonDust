#ifndef POLYGON_H
#define POLYGON_H

#include "point.hpp"
#include <vector>
#include <set>

class Polygon {
private:
    std::vector<Point> vertexs;
    std::vector<Point> GetErosionPoints();
public:
    Polygon() = default;
    Polygon(std::vector<Point> vertexs){
        this->vertexs = vertexs;
    }
    ~Polygon() = default;
    std::vector<Point> GetVertexs();
    double GetArea();
};

#endif
