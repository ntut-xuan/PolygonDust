#include <gtest/gtest.h>

#include "polygon.hpp"
#include "point.hpp"

TEST(POLYGON_TEST, test_constructor_should_have_correct_vertex){
    std::vector<Point> expected_vertexs = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Polygon polygon(expected_vertexs);

    std::vector<Point> vertexs = polygon.GetVertexs();

    
    ASSERT_EQ(expected_vertexs, vertexs);
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