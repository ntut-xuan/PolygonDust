#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <fstream>

class Point {
private:
    double x = 0;
    double y = 0;
public:
    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
    ~Point() = default;
    bool operator<(const Point &other) const{
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
    bool operator==(const Point &other) const{
        return other.x == x && other.y == y;
    }

    friend void PrintTo(const Point& point, std::ostream* os) {
        *os << "(" << point.x << ", " << point.y << ")";
    }

    double GetX();
    double GetY();
};

#endif