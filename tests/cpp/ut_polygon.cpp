#include <gtest/gtest.h>
#include <memory>

#include "point.hpp"
#include "polygon.hpp"

TEST(POLYGON_TEST, test_constructor_should_have_correct_vertex) {
    std::vector<Point> expected_vertexs = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};

    Polygon polygon(expected_vertexs);

    std::shared_ptr<std::vector<Point>> vertexs = polygon.GetVertexs();

    ASSERT_EQ(expected_vertexs, *vertexs.get());
}

TEST(POLYGON_TEST, test_get_area_with_valid_polygon_should_have_correct_value) {
    std::vector<Point> vertexs = {Point(1, 6), Point(5, 4), Point(-3, 3), Point(0, -4), Point(-4, -1), Point(-4, 4)};
    Polygon polygon(vertexs);

    double size = polygon.GetArea();

    ASSERT_EQ(size, 25.5);
}

TEST(POLYGON_TEST, test_get_local_min_max_point_with_valid_polygon_should_return_correct_points) {
    std::vector<Point> vertexs = {Point(0, 0), Point(3, 2), Point(5, 0)};
    Polygon polygon(vertexs);

    ASSERT_EQ(*polygon.GetLocalMinMaxVertexs(), std::vector<Point>{Point(3, 2)});
}

TEST(POLYGON_TEST, test_is_local_min_max_point_with_vertex_point_should_return_true) {
    std::vector<Point> vertexs = {Point(0, 0), Point(3, 2), Point(5, 0)};
    Polygon polygon(vertexs);

    ASSERT_TRUE(polygon.IsLocalMinMaxPoint(Point(3, 2)));
}

TEST(POLYGON_TEST, test_is_local_min_max_point_with_not_vertex_point_should_return_false) {
    std::vector<Point> vertexs = {Point(0, 0), Point(3, 2), Point(5, 0)};
    Polygon polygon(vertexs);

    ASSERT_FALSE(polygon.IsLocalMinMaxPoint(Point(0, 0)));
}

TEST(POLYGON_TEST, test_polygon_lines_with_valid_polygon_should_return_correct_lines) {
    std::shared_ptr<Polygon> polygon =
        std::make_shared<Polygon>(std::vector<Point>{Point(1, 1), Point(3, 5), Point(6, 3)});
    std::shared_ptr<std::vector<Line>> lines = polygon->GetLines();

    ASSERT_EQ(*lines.get(), std::vector<Line>({Line(Point(1, 1), Point(3, 5)), Line(Point(3, 5), Point(6, 3)),
                                               Line(Point(6, 3), Point(1, 1))}));
}

TEST(POLYGON_TEST, test_polygon_with_concave_polygon_should_return_correct_local_minmax) {
    std::shared_ptr<Polygon> polygon = std::make_shared<Polygon>(std::vector<Point>{
        Point(0, 0), Point(2, 4), Point(4, 2), Point(6, 4), Point(8, 0), Point(6, 2), Point(4, 1), Point(2, 2)});
    std::shared_ptr<std::vector<Point>> localminmax = polygon->GetLocalMinMaxVertexs();

    ASSERT_EQ(*localminmax.get(), std::vector<Point>({Point(0, 0), Point(8, 0), Point(4, 1), Point(2, 2), Point(4, 2),
                                                      Point(6, 2), Point(2, 4), Point(6, 4)}));
}

TEST(POLYGON_TEST, test_polygon_with_counterwise_vertex_set_should_determine_counterwise) {
    std::shared_ptr<Polygon> polygon =
        std::make_shared<Polygon>(std::vector<Point>{Point(0, 0), Point(4, 2), Point(2, 5)});

    ASSERT_EQ(polygon->IsClockwise(), true);
}

TEST(POLYGON_TEST, test_polygon_with_clockwise_vertex_set_should_determine_clockwise) {
    std::shared_ptr<Polygon> polygon =
        std::make_shared<Polygon>(std::vector<Point>{Point(0, 0), Point(-5, 0), Point(-2.5, 3)});

    ASSERT_EQ(polygon->IsClockwise(), false);
}