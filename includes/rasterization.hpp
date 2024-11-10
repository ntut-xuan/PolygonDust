#ifndef RASTERIZATION_HPP
#define RASTERIZATION_HPP

#include "polygon.hpp"
#include <memory>

class Rasterization {
private:
    double edge;
    std::shared_ptr<Polygon> polygon;
    std::vector<Line> active_line;
public:
    Rasterization(std::shared_ptr<Polygon> polygon, double edge){
        this->edge = edge;
        this->polygon = polygon;
    }

}

#endif