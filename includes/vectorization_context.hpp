#ifndef VECTOR_CONTEXT_HPP
#define VECTOR_CONTEXT_HPP

#include "point.hpp"
#include "polygon.hpp"
#include "polygon_clipping.hpp"
#include "vectorization_result.hpp"
#include <climits>
#include <cstddef>
#include <memory>
#include <vector>

class VectorizationContext {
  private:
    std::vector<std::shared_ptr<std::vector<Point>>> polygons_cells;
    Polygon polygon;
    VectorizationResult result;

  public:
    VectorizationContext(Polygon first_polygon) {
        polygon = first_polygon;
        result = VectorizationResult({first_polygon}, {});
    }

    void ClipPolygon(Polygon other) {
        PolygonClipping clipping(std::make_shared<Polygon>(polygon), std::make_shared<Polygon>(other));
        result = clipping.Produce();
    }

    std::vector<Polygon> GetResult() { return result.GetPolygons(); }
    std::vector<Point> GetIntersectPoints() { return result.GetIntersectPoints(); }
};

#endif