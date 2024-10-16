#ifndef VECTOR_H
#define VECTOR_H

#include "point.hpp"
#include <cmath>

class Vector {
private:
    double x;
    double y;
public:
    Vector(double x, double y) : x(x), y(y) {};
    Vector(Point a, Point b) {
        x = (b.GetX() - a.GetX()) / std::sqrt(std::pow(a.GetX() - b.GetX(), 2.0) + std::pow(a.GetY() - b.GetY(), 2));
        y = (b.GetY() - a.GetY()) / std::sqrt(std::pow(a.GetX() - b.GetX(), 2.0) + std::pow(a.GetY() - b.GetY(), 2));
    }
    double GetX() { return x; };
    double GetY() { return y; };

    Vector operator+(const Vector &vector){
        x += vector.x;
        y += vector.y;
        return *this;
    }
};

#endif // VECTOR_H;