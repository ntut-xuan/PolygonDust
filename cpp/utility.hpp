#ifndef UTILITY_H
#define UTILITY_H

#include "point.hpp"
#include "vector.hpp"
#include <cmath>
#include <set>

inline double GetMatrixComputationValue(double a, double b, double c, double d){
    return a * d - b * c;
}

inline static double GetDistance(Point first, Point second){
    double dx = (first.GetX() - second.GetX());
    double dy = (first.GetY() - second.GetY());
    return std::sqrt(dx * dx + dy * dy);
}

inline static double GetAngelOfThreePoint(Point a, Point b, Point c){
    if(a == b && b == c){
        return NAN;
    }

    double distanceAB = GetDistance(a, b);
    double distanceBC = GetDistance(b, c);
    double distanceAC = GetDistance(a, c);

    double cosine = (distanceAB*distanceAB + distanceBC*distanceBC - distanceAC*distanceAC) / (2 * distanceAB * distanceBC);

    return acos(cosine);;
}

inline static double GetBisectorUnitSlope(Point a, Point b, Point c){
    if(a == b && b == c){
        return NAN;
    }

    Vector vectorBA(b, a);
    Vector vectorBC(b, c);
    Vector direction = vectorBA + vectorBC;

    if(direction.GetX() == 0){
        return NAN;
    }

    return direction.GetY() / direction.GetX();
}
    
inline static std::set<Point> GetLineCell(Point a, Point b, double cellGap){
    std::set<Point> boundaryCell;

    double distance = GetDistance(a, b);
    double unitVectorX = (b.GetX() - a.GetX()) / distance;
    double unitVectorY = (b.GetY() - a.GetY()) / distance;

    double currentX = a.GetX();
    double currentY = a.GetY();

    for(int i = 0; i < distance / cellGap; i++){
        Point cell(std::floor((currentX) / cellGap) * cellGap, std::floor((currentY) / cellGap) * cellGap);

        boundaryCell.insert(cell);

        currentX += unitVectorX * cellGap;
        currentY += unitVectorY * cellGap;
    }

    return boundaryCell;
}

#endif