#ifndef VECTOR_CONTEXT_HPP
#define VECTOR_CONTEXT_HPP

#include "point.hpp"
#include "polygon.hpp"
#include "polygon_clipping.hpp"
#include <climits>
#include <cstddef>
#include <memory>
#include <vector>

class VectorizationContext {
  private:
    double min_x = INT_MAX;
    double max_x = INT_MIN;
    double min_y = INT_MAX;
    double max_y = INT_MIN;
    std::vector<std::shared_ptr<std::vector<Point>>> polygons_cells;
    std::shared_ptr<Polygon> polygon;

    void UpdateMinMax(Polygon polygon) {
        min_x = std::min(polygon.GetMinX(), min_x);
        max_x = std::max(polygon.GetMaxX(), max_x);
        min_y = std::min(polygon.GetMinY(), min_y);
        max_y = std::max(polygon.GetMaxY(), max_y);
    }

  public:
    VectorizationContext(Polygon first_polygon) { polygon = std::make_shared<Polygon>(first_polygon); }

    void ClipPolygon(Polygon other) {
        PolygonClipping clipping(polygon, std::make_shared<Polygon>(other));
        polygon = std::make_shared<Polygon>(clipping.Produce());
    }

    Polygon GetResult() { return *polygon.get(); }
};

#endif