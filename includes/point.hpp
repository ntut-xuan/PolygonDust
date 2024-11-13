#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <fstream>
#include <string>

class Point {
private:
    double x = 0;
    double y = 0;
public:
    Point() {

    };
    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
    ~Point() = default;
    bool operator<(const Point &other) const{
        if (y != other.y) {
            return y < other.y;
        }
        return x < other.x;
    }
    bool operator>(const Point &other) const{
        if (y != other.y) {
            return y > other.y;
        }
        return x > other.x;
    }
    bool operator<=(const Point &other) const{
        if (y != other.y) {
            return y <= other.y;
        }
        return x <= other.x;
    }
    bool operator>=(const Point &other) const{
        if (y != other.y) {
            return y >= other.y;
        }
        return x >= other.x;
    }
    bool operator==(const Point &other) const{
        return other.x == x && other.y == y;
    }

    friend void PrintTo(const Point& point, std::ostream* os) {
        *os << point.ToString();
    }

    double GetX();
    double GetY();

    std::string ToString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

#endif