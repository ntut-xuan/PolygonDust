#include <gtest/gtest.h>

#include "../../cpp/polygon.hpp"
#include "../../cpp/point.hpp"

TEST(POLYGON_TEST, test_get_boundary_with_square_polygon_should_return_correct_boundary_points){
    std::vector<Point> vertexs = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Polygon polygon(vertexs);

    std::set<Point> boundaryCell = polygon.GetBoundaryCell(1);

    std::set<Point> expectedCell = {
        Point(0, 0), Point(1, 0), Point(2, 0), 
        Point(3, 0), Point(3, 1), Point(3, 2), 
        Point(3, 3), Point(2, 3), Point(1, 3), 
        Point(0, 3), Point(0, 2), Point(0, 1)
    };
    ASSERT_EQ(boundaryCell, expectedCell);
}


TEST(POLYGON_TEST, test_get_area_with_valid_polygon_should_have_correct_value){
    std::vector<Point> vertexs = {
        Point( 1,  6), 
        Point( 5,  4), 
        Point(-3,  3), 
        Point( 0, -4), 
        Point(-4, -1), 
        Point(-4,  4)
    };
    Polygon polygon(vertexs);

    double size = polygon.GetArea();

    ASSERT_EQ(size, 25.5);
}