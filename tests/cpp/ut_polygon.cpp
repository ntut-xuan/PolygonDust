#include <gtest/gtest.h>

#include "../../cpp/polygon.hpp"
#include "../../cpp/point.hpp"

TEST(POLYGON_TEST, test_constructor_should_have_correct_vertex){
    std::vector<Point> expected_vertexs = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Polygon polygon(expected_vertexs);

    std::vector<Point> vertexs = polygon.GetVertexs();

    
    ASSERT_EQ(expected_vertexs, vertexs);
}

TEST(POLYGON_TEST, test_get_boundary_with_square_polygon_should_return_correct_boundary_points){
    std::vector<Point> vertexs = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Polygon polygon(vertexs);

    std::vector<Point> boundaryCell = polygon.GetBoundaryCell(1);

    std::set<Point> expectedCell = {
        Point(0, 0), Point(1, 0), Point(2, 0), 
        Point(3, 0), Point(3, 1), Point(3, 2), 
        Point(3, 3), Point(2, 3), Point(1, 3), 
        Point(0, 3), Point(0, 2), Point(0, 1)
    };
    ASSERT_EQ(boundaryCell, std::vector<Point>(expectedCell.begin(), expectedCell.end()));
}

TEST(POLYGON_TEST, test_get_boundary_with_inregular_polygon_should_return_correct_boundary_points){
    std::vector<Point> vertexs = {
        Point(0, 0), Point(2, 4), Point(4, 2), 
        Point(6, 4), Point(8, 0), Point(6, 2), 
        Point(4, 1), Point(2, 2)
    };
    Polygon polygon(vertexs);

    std::vector<Point> boundaryCell = polygon.GetBoundaryCell(1);

    std::set<Point> expectedCell = {
        Point(0, 0), Point(0, 1), Point(1, 2), Point(1, 3), Point(2, 4),
        Point(2, 3), Point(3, 2), Point(4, 2),
        Point(4, 2), Point(5, 3), Point(6, 4),
        Point(6, 3), Point(6, 2), Point(7, 1), Point(7, 0), Point(8, 0),
        Point(7, 0), Point(6, 1), Point(6, 2),
        Point(5, 1), Point(4, 1),
        Point(3, 1), Point(2, 1), Point(2, 2),
        Point(1, 1), Point(0, 0),
    };
    ASSERT_EQ(expectedCell.size(), 22);
    ASSERT_EQ(boundaryCell, std::vector<Point>(expectedCell.begin(), expectedCell.end()));
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