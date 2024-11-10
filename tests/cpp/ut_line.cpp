#include <gtest/gtest.h>
#include <optional>

#include "line.hpp"
#include "point.hpp"

TEST(LINE_TEST, test_Y_ray_intersection_with_intersect_line_and_one_point_intersect_should_return_correct_point){
    Line line(Point(2, 3), Point(7, 9));

    std::optional<Point> intersect_point = line.GetYRayIntersectPoint(5);

    ASSERT_EQ(intersect_point.has_value(), true);
    ASSERT_NEAR(intersect_point->GetX(), 3.6667, 0.0001);
    ASSERT_EQ(intersect_point->GetY(), 5);
}

TEST(LINE_TEST, test_get_minimal_point_of_line_should_return_correct_value){
    Line line(Point(2, 3), Point(7, 9));

    ASSERT_EQ(line.GetMinimalPoint(), Point(2, 3));
}

TEST(LINE_TEST, test_get_maximal_point_of_line_should_return_correct_value){
    Line line(Point(2, 3), Point(7, 9));

    ASSERT_EQ(line.GetMaximalPoint(), Point(7, 9));
}