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
    std::vector<std::shared_ptr<std::vector<Point>>> polygons_cells;
    Polygon polygon;

  public:
    VectorizationContext(Polygon first_polygon) { polygon = first_polygon; }

    void ClipPolygon(Polygon other) {
        PolygonClipping clipping(std::make_shared<Polygon>(polygon), std::make_shared<Polygon>(other));
        polygon = clipping.Produce();
    }

    Polygon GetResult() { return polygon; }
};

#endif