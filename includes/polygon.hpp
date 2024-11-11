#ifndef POLYGON_H
#define POLYGON_H

#include "line.hpp"
#include "point.hpp"
#include "shared.hpp"
#include <algorithm>
#include <climits>
#include <cstddef>
#include <memory>
#include <vector>
#include <set>

class Polygon {
private:
    std::shared_ptr<std::vector<Point>> vertexs;
    std::shared_ptr<std::vector<Line>> lines;
    std::shared_ptr<std::vector<Point>> localminmaxs;
    double min_x = INT_MAX, min_y = INT_MAX, max_x = INT_MIN, max_y = INT_MIN;
    void ConstructLocalMinMaxPoints(){
        for(size_t i = 0; i < vertexs->size(); i++){
            Point startPoint = vertexs->at(i);
            Point middlePoint = vertexs->at((i+1)%(vertexs->size()));
            Point endPoint = vertexs->at((i+2)%(vertexs->size()));
            if(!(Between(middlePoint.GetY(), startPoint.GetY(), endPoint.GetY()) || Between(middlePoint.GetY(), endPoint.GetY(), startPoint.GetY()))){
                localminmaxs->push_back(middlePoint);
            }
        }
        std::sort(localminmaxs->begin(), localminmaxs->end());
    }
    void ConstructLines(){
        for(size_t i = 0; i < vertexs->size(); i++){
            Point startPoint = vertexs->at(i);
            Point endPoint = vertexs->at((i+1) % vertexs->size());
            lines->push_back(Line(startPoint, endPoint));
        }
    }
public:
    Polygon() = default;
    Polygon(std::vector<Point> vertexs){
        this->vertexs = std::make_shared<std::vector<Point>>(vertexs.begin(), vertexs.end());
        this->lines = std::make_shared<std::vector<Line>>();
        this->localminmaxs = std::make_shared<std::vector<Point>>();
        for(Point p : vertexs){
            min_x = std::min(p.GetX(), min_x);
            max_x = std::max(p.GetX(), max_x);
            min_y = std::min(p.GetY(), min_y);
            max_y = std::max(p.GetY(), max_y);
        }
        ConstructLines();
        ConstructLocalMinMaxPoints();
    }
    ~Polygon() = default;
    std::shared_ptr<std::vector<Point>> GetVertexs();
    std::shared_ptr<std::vector<Point>> GetLocalMinMaxVertexs();
    std::shared_ptr<std::vector<Line>> GetLines();
    double GetArea();
    double GetMinX() { return min_x; }
    double GetMinY() { return min_y; }
    double GetMaxX() { return max_x; }
    double GetMaxY() { return max_y; }
    bool IsLocalMinMaxPoint(Point point);
};

#endif
