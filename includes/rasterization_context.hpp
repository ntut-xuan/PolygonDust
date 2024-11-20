#ifndef RASTERIZATION_CONTEXT_HPP
#define RASTERIZATION_CONTEXT_HPP

#include "point.hpp"
#include "polygon.hpp"
#include "rasterization.hpp"
#include "rasterization_cells.hpp"
#include <algorithm>
#include <climits>
#include <memory>
#include <stdexcept>
#include <vector>

class RasterizationContext {
private:
    double min_x = INT_MAX;
    double max_x = INT_MIN;
    double min_y = INT_MAX;
    double max_y = INT_MIN;
    double edge;
    std::vector<std::shared_ptr<std::vector<Point>>> polygons_cells;

    void UpdateMinMax(Polygon polygon){
        min_x = std::min(polygon.GetMinX(), min_x);
        max_x = std::max(polygon.GetMaxX(), max_x);
        min_y = std::min(polygon.GetMinY(), min_y);
        max_y = std::max(polygon.GetMaxY(), max_y);
    }
public:
    RasterizationContext(double edge){
        this->edge = edge;
    }
    void AddPolygon(Polygon polygon){
        std::shared_ptr<Polygon> polygon_ptr = std::make_shared<Polygon>(polygon);
        Rasterization rasterization(polygon_ptr, edge);
        std::shared_ptr<std::vector<Point>> cells = rasterization.GetCells();
        polygons_cells.push_back(cells);
        UpdateMinMax(polygon);
    }
    double GetMinX(){
        return this->min_x;
    }
    double GetMaxX(){
        return this->max_x;
    }
    double GetMinY(){
        return this->min_y;
    }
    double GetMaxY(){
        return this->max_y;
    }
    RasterizationCells GetPolygonCell(size_t index){
        if(polygons_cells.size() <= index){
            throw std::out_of_range("Index out of range");
        }
        return RasterizationCells(*polygons_cells[index]);
    }
};

#endif