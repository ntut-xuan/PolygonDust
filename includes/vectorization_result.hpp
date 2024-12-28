#ifndef VECTORIZATION_RESULT_HPP
#define VECTORIZATION_RESULT_HPP

#include "polygon.hpp"

class VectorizationResult {
  private:
    std::vector<Polygon> polygons;
    std::vector<Point> intersect_points;

  public:
    VectorizationResult() = default;
    VectorizationResult(std::vector<Polygon> polygons, std::vector<Point> intersect_points)
        : polygons(polygons), intersect_points(intersect_points) {}

    std::vector<Polygon> GetPolygons() { return polygons; }
    std::vector<Point> GetIntersectPoints() { return intersect_points; }
};

#endif