#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"
#include "shared.hpp"

#include <optional>


class Line {
private:
    Point start;
    Point end;
public:
    Line(Point start, Point end){
        this->start = start;
        this->end = end;
    }

    Point GetMinimalPoint(){
        return this->start <= this->end ? this->start : this->end;
    }

    Point GetMaximalPoint(){
        return this->start >= this->end ? this->start : this->end;
    }
    
    /**
      * This is a function for get the intersect point of two lines.
      * These case will not present tf two line have 0 or more than 1 point intersection.
      */
    std::optional<Point> GetYRayIntersectPoint(double y){
        if(this->start.GetY() == this->end.GetY()){
            return std::optional<Point>();
        }
        if(this->start.GetX() == this->end.GetX()){
            if(Between<double>(y, this->start.GetY(), this->end.GetY())){
                return std::optional<Point>({this->start.GetX(), y});
            }
            return std::optional<Point>();
        }
        double m = (this->start.GetY() - this->end.GetY()) / (this->start.GetX() - this->end.GetX());
        double x = this->start.GetX() + (y - this->start.GetY()) / m;
        return std::optional<Point>({x, y});
    }
};

#endif