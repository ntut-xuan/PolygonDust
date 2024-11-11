#include <gtest/gtest.h>
#include <memory>

#include "polygon.hpp"
#include "point.hpp"

TEST(POLYGON_TEST, test_constructor_should_have_correct_vertex){
    std::vector<Point> expected_vertexs = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    
    Polygon polygon(expected_vertexs);

    std::shared_ptr<std::vector<Point>> vertexs = polygon.GetVertexs();
    
    ASSERT_EQ(expected_vertexs, *vertexs.get());
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

TEST(POLYGON_TEST, test_get_local_min_max_point_with_valid_polygon_should_return_correct_points){
    std::vector<Point> vertexs = {
        Point( 0, 0),
        Point(3, 2),
        Point(5, 0)
    };
    Polygon polygon(vertexs);

    ASSERT_EQ(*polygon.GetLocalMinMaxVertexs(), std::vector<Point>{Point(3, 2)});
}


TEST(POLYGON_TEST, test_is_local_min_max_point_with_vertex_point_should_return_true){
    std::vector<Point> vertexs = {
        Point( 0, 0),
        Point(3, 2),
        Point(5, 0)
    };
    Polygon polygon(vertexs);

    ASSERT_TRUE(polygon.IsLocalMinMaxPoint(Point(3, 2)));
}

TEST(POLYGON_TEST, test_is_local_min_max_point_with_not_vertex_point_should_return_false){
    std::vector<Point> vertexs = {
        Point( 0, 0),
        Point(3, 2),
        Point(5, 0)
    };
    Polygon polygon(vertexs);

    ASSERT_FALSE(polygon.IsLocalMinMaxPoint(Point(0, 9)));
}