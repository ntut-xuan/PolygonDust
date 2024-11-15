#ifndef RASTERIZATION_HPP
#define RASTERIZATION_HPP

#include "point.hpp"
#include "polygon.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>

#include "line.hpp"

class Rasterization {
private:
    double edge;
    std::shared_ptr<Polygon> polygon;
    std::vector<Line> activeLines;
    std::vector<Point> intersectPoints;
    std::shared_ptr<std::vector<Point>> cells;

    void UpdateIntersectPoints(double y){
        activeLines.clear();
        intersectPoints.clear();

        std::set<int> intersectX;
        for(Line line : *(polygon->GetLines())){
            std::optional<Point> intersectPointOptional = line.GetYRayIntersectPoint(y);
            if(intersectPointOptional.has_value()){
                Point intersectPoint = intersectPointOptional.value();

                // The point already in intersectPoints
                if(intersectX.find(intersectPoint.GetX()) != intersectX.end()){
                    continue;
                }

                intersectX.insert(intersectPoint.GetX());

                // Deal the edge case of ray-casting. 
                // Duplicate the intersectPoint only if y1 <= y2 <= y3 or y3 <= y2 <= y1 
                intersectPoints.push_back(intersectPoint);
                if(polygon->IsLocalMinMaxPoint(intersectPoint)){
                    intersectPoints.push_back(intersectPoint);
                }
            }
        }
        std::sort(intersectPoints.begin(), intersectPoints.end(), [](Point a, Point b){ return a.GetX() < b.GetX(); });
    }
    void transform(){
        int xCellSize = ((polygon->GetMaxX() - polygon->GetMinX()) / edge);
        int yCellSize = ((polygon->GetMaxY() - polygon->GetMinY()) / edge);

        for(int i = 0; i < yCellSize + 5; i++){
            double y = polygon->GetMinY() + edge * i;
            int xIntersecPointIndex = 0;
            UpdateIntersectPoints(y);
            for(int j = 0; j < xCellSize; j++){
                double x = polygon->GetMinX() + edge * j;

                if(xIntersecPointIndex < (int) intersectPoints.size() && x >= intersectPoints[xIntersecPointIndex].GetX()){
                    xIntersecPointIndex += 1;
                }

                if((intersectPoints.size() - xIntersecPointIndex) % 2 == 1 && xIntersecPointIndex % 2 == 1){
                    cells->push_back(Point(x, y));
                }
            }
        }
    }
public:
    Rasterization(std::shared_ptr<Polygon> polygon, double edge){
        this->edge = edge;
        this->polygon = polygon;
        cells = std::make_shared<std::vector<Point>>();
        transform();
    }
    std::shared_ptr<std::vector<Point>> GetCells() { return cells; }
};

#endif