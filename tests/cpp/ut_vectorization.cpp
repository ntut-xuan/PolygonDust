#include "point.hpp"
#include "vectorization_context.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(VECTORIZATION_TEST, test_vectorization_should_return_correct_clipping_polygon) {
    Polygon polygon1({Point(1, 5), Point(3, 2), Point(6, 6), Point(10, 4), Point(12, 12), Point(6, 12)});
    Polygon polygon2({Point(6, 2), Point(14, 2), Point(16, 10), Point(8, 10)});
    VectorizationContext vectorization(polygon1);

    vectorization.ClipPolygon(polygon2);

    Polygon result = vectorization.GetResult();

    std::vector<Point> expected_vec = {
        Point(1, 5),  Point(3, 2),     Point(6, 6),   Point(6.88888888888888888888, 5.5555555555555555555),
        Point(8, 10), Point(11.5, 10), Point(12, 12), Point(6, 12)};
    ASSERT_EQ(result.GetVertexsVector(), expected_vec);
}