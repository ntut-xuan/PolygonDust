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
    Line() = default;

    Line(Point start, Point end){
        this->start = start;
        this->end = end;
    }

    Point GetMinimalPoint(){
        if(this->start <= this->end){
            return this->start;
        }else{
            return this->end;
        }
    }

    Point GetMaximalPoint(){
        if(this->start >= this->end){
            return this->start;
        }else{
            return this->end;
        }
    }

    bool operator==(const Line &other) const {
        return this->start == other.start && this->end == other.end;
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
            }else{
                return std::optional<Point>();
            }
        }
        double m = (this->start.GetY() - this->end.GetY()) / (this->start.GetX() - this->end.GetX());
        double x = this->start.GetX() + (y - this->start.GetY()) / m;
        if(!Between(x, std::min(this->start.GetX(), this->end.GetX()), std::max(this->start.GetX(), this->end.GetX()))){
            return std::optional<Point>();
        }
        return std::optional<Point>({x, y});
    }
};

#endif