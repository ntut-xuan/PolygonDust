#ifndef UTILITY_H
#define UTILITY_H

#include "point.hpp"
#include <cmath>
#include <vector>

inline double GetMatrixComputationValue(double a, double b, double c, double d) { return a * d - b * c; }

inline static double GetDistance(Point first, Point second) {
    double dx = (first.GetX() - second.GetX());
    double dy = (first.GetY() - second.GetY());
    return std::sqrt(dx * dx + dy * dy);
}

template <class T> inline static bool Between(T val, T min, T max) {
    if (min <= val && val <= max) {
        return true;
    }
    return false;
}

inline static bool DeterminePointInPolygonByXSet(std::vector<double> x_set, double x) {
    int less_than_x = 0;
    for (size_t i = 0; i < x_set.size(); i++) {
        if (x_set[i] < x) {
            less_than_x += 1;
        }
    }
    int larger_than_x = x_set.size() - less_than_x;
    return larger_than_x % 2 == 1 && less_than_x % 2 == 1;
}

#endif