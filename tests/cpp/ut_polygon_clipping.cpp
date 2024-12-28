#include "polygon.hpp"
#include "polygon_clipping.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(POLYGON_CLIPPING_TEST, test_create_vertex_list_should_return_correct_vertex_list) {
    Polygon polygon1 = Polygon({Point(1, 5), Point(3, 2), Point(6, 6), Point(10, 4), Point(12, 12), Point(6, 12)});
    Polygon polygon2({Point(6, 2), Point(14, 2), Point(16, 10), Point(8, 10), Point(8, 4)});
    std::shared_ptr<Polygon> polygon_ptr1 = std::make_shared<Polygon>(polygon1);
    std::shared_ptr<Polygon> polygon_ptr2 = std::make_shared<Polygon>(polygon2);
    PolygonClipping polygon_clipping(polygon_ptr1, polygon_ptr2);
    std::vector<PointWithState> points;

    polygon_clipping.CreateVertexList(points, polygon_ptr1, polygon_ptr2);

    ASSERT_EQ(points,
              std::vector<PointWithState>({PointWithState(Point(1, 5), false), PointWithState(Point(3, 2), false),
                                           PointWithState(Point(6, 6), false), PointWithState(Point(8, 5), true),
                                           PointWithState(Point(10, 4), true), PointWithState(Point(11.5, 10), true),
                                           PointWithState(Point(12, 12), false), PointWithState(Point(6, 12), false)}));
}

TEST(POLYGON_CLIPPING_TEST,
     test_create_vertex_list_with_multiple_intersect_in_the_same_line_should_return_correct_vertex_list) {
    Polygon polygon1({Point(1, 5), Point(1, 1), Point(4, 1), Point(4, 5)});
    Polygon polygon2(
        {Point(5, 4), Point(3, 4), Point(3, 6), Point(2, 6), Point(2, 0), Point(3, 0), Point(3, 2), Point(5, 2)});
    std::shared_ptr<Polygon> polygon_ptr1 = std::make_shared<Polygon>(polygon1);
    std::shared_ptr<Polygon> polygon_ptr2 = std::make_shared<Polygon>(polygon2);
    PolygonClipping polygon_clipping(polygon_ptr1, polygon_ptr2);
    std::vector<PointWithState> points;

    polygon_clipping.CreateVertexList(points, polygon_ptr2, polygon_ptr1);

    ASSERT_EQ(points,
              std::vector<PointWithState>({PointWithState(Point(5, 4), false), PointWithState(Point(4, 4), true),
                                           PointWithState(Point(3, 4), true), PointWithState(Point(3, 5), true),
                                           PointWithState(Point(3, 6), false), PointWithState(Point(2, 6), false),
                                           PointWithState(Point(2, 5), true), PointWithState(Point(2, 1), true),
                                           PointWithState(Point(2, 0), false), PointWithState(Point(3, 0), false),
                                           PointWithState(Point(3, 1), true), PointWithState(Point(3, 2), true),
                                           PointWithState(Point(4, 2), true), PointWithState(Point(5, 2), false)}));
}

TEST(POLYGON_CLIPPING_TEST, test_create_vertex_list_with_overlap_line_should_return_correct_vertex_list) {
    Polygon polygon1({Point(0, 5), Point(2, 5), Point(2, 3), Point(0, 3)});
    Polygon polygon2({Point(1, 5), Point(3, 5), Point(3, 3), Point(1, 3)});
    std::shared_ptr<Polygon> polygon_ptr1 = std::make_shared<Polygon>(polygon1);
    std::shared_ptr<Polygon> polygon_ptr2 = std::make_shared<Polygon>(polygon2);
    PolygonClipping polygon_clipping(polygon_ptr1, polygon_ptr2);
    std::vector<PointWithState> points;

    polygon_clipping.CreateVertexList(points, polygon_ptr1, polygon_ptr2);

    ASSERT_EQ(points,
              std::vector<PointWithState>({PointWithState(Point(0, 5), false), PointWithState(Point(1, 5), true),
                                           PointWithState(Point(2, 5), true), PointWithState(Point(2, 3), true),
                                           PointWithState(Point(1, 3), true), PointWithState(Point(0, 3), false)}));
}