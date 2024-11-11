#ifndef RASTERIZATION_HPP
#define RASTERIZATION_HPP

#include "polygon.hpp"
#include <algorithm>
#include <memory>
#include <optional>

#include "line.hpp"

class Rasterization {
private:
    double edge;
    std::shared_ptr<Polygon> polygon;
    std::vector<Line> activeLines;
    std::vector<Point> intersectPoints;

    void UpdateIntersectPoints(double y){
        activeLines.clear();
        intersectPoints.clear();
        for(Line line : *(polygon->GetLines())){
            std::optional<Point> intersectPointOptional = line.GetYRayIntersectPoint(y);
            if(intersectPointOptional.has_value()){
                Point intersectPoint = intersectPointOptional.value();

                // Deal the edge case of ray-casting. 
                // Duplicate the intersectPoint only if y1 <= y2 <= y3 or y3 <= y2 <= y1 
                intersectPoints.push_back(intersectPoint);
                if(polygon->IsLocalMinMaxPoint(intersectPoint)){
                    intersectPoints.push_back(intersectPoint);
                }
            }
        }
    }
public:
    Rasterization(std::shared_ptr<Polygon> polygon, double edge){
        this->edge = edge;
        this->polygon = polygon;
    }
    std::vector<Point> transform(){
        int xCellSize = ((polygon->GetMaxX() - polygon->GetMinX()) / edge);
        int yCellSize = ((polygon->GetMaxY() - polygon->GetMinY()) / edge);

        for(int i = 0; i < yCellSize; i++){
            double y = polygon->GetMinY() + edge * i;
            UpdateIntersectPoints(y);
            for(int j = 0; j < xCellSize; j++){
                double x = polygon->GetMinX() + edge * i;
                

            }
        }
    }
};

#endif