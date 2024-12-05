#include <gtest/gtest.h>
#include <optional>

#include "line.hpp"
#include "point.hpp"

TEST(LINE_TEST, test_Y_ray_intersection_with_intersect_line_and_one_point_intersect_should_return_correct_point) {
    Line line(Point(2, 3), Point(7, 9));

    std::optional<Point> intersect_point = line.GetYRayIntersectPoint(5);

    ASSERT_EQ(intersect_point.has_value(), true);
    ASSERT_NEAR(intersect_point->GetX(), 3.6667, 0.0001);
    ASSERT_EQ(intersect_point->GetY(), 5);
}

TEST(LINE_TEST, test_Y_ray_intersection_with_intersect_line_and_no_point_intersect_should_return_false_optional) {
    Line line(Point(2, 3), Point(7, 9));

    std::optional<Point> intersect_point = line.GetYRayIntersectPoint(50);

    ASSERT_EQ(intersect_point.has_value(), false);
}

TEST(LINE_TEST, test_Y_ray_intersection_with_zero_length_line_should_return_false_optional) {
    Line line(Point(2, 3), Point(2, 3));

    std::optional<Point> intersect_point = line.GetYRayIntersectPoint(3);

    ASSERT_EQ(intersect_point.has_value(), false);
}

TEST(LINE_TEST, test_Y_ray_intersection_with_one_intersection_and_same_x_but_different_y_should_return_correct_point) {
    Line line(Point(2, 3), Point(2, 6));

    std::optional<Point> intersect_point = line.GetYRayIntersectPoint(3);

    ASSERT_EQ(intersect_point.has_value(), true);
    ASSERT_NEAR(intersect_point->GetX(), 2, 0.0001);
    ASSERT_EQ(intersect_point->GetY(), 3);
}

TEST(
    LINE_TEST,
    test_Y_ray_intersection_with_one_intersection_and_same_x_but_different_y_and_no_intersection_should_return_false_optional) {
    Line line(Point(2, 3), Point(2, 6));

    std::optional<Point> intersect_point = line.GetYRayIntersectPoint(9);

    ASSERT_EQ(intersect_point.has_value(), false);
}

TEST(LINE_TEST, test_Y_ray_intersection_with_intersect_line_and_infinite_point_intersect_should_return_false_optional) {
    Line line(Point(2, 3), Point(6, 3));

    std::optional<Point> intersect_point = line.GetYRayIntersectPoint(3);

    ASSERT_EQ(intersect_point.has_value(), false);
}

TEST(LINE_TEST, test_get_minimal_point_of_line_should_return_correct_value) {
    Line line(Point(2, 3), Point(7, 9));

    ASSERT_EQ(line.GetMinimalPoint(), Point(2, 3));
}

TEST(LINE_TEST, test_get_minimal_point_of_line_with_v1_greater_than_v2_should_return_correct_value) {
    Line line(Point(7, 9), Point(2, 3));

    ASSERT_EQ(line.GetMinimalPoint(), Point(2, 3));
}

TEST(LINE_TEST, test_get_maximal_point_of_line_should_return_correct_value) {
    Line line(Point(2, 3), Point(7, 9));

    ASSERT_EQ(line.GetMaximalPoint(), Point(7, 9));
}

TEST(LINE_TEST, test_get_maximal_point_of_line_with_v1_greater_than_v2_should_return_correct_value) {
    Line line(Point(7, 9), Point(2, 3));

    ASSERT_EQ(line.GetMaximalPoint(), Point(7, 9));
}

TEST(LINE_TEST, test_equal_with_two_line_with_same_start_and_end_point_should_return_true) {
    Line l1 = Line(Point(2, 5), Point(7, 9));
    Line l2 = Line(Point(2, 5), Point(7, 9));

    ASSERT_EQ(l1, l2);
}

TEST(LINE_TEST, test_equal_with_two_line_with_differnt_start_point_should_return_false) {
    Line l1 = Line(Point(3, 7), Point(7, 9));
    Line l2 = Line(Point(2, 5), Point(7, 9));

    ASSERT_FALSE(l1 == l2);
}

TEST(LINE_TEST, test_equal_with_two_line_with_differnt_end_point_should_return_false) {
    Line l1 = Line(Point(2, 5), Point(7, 9));
    Line l2 = Line(Point(2, 5), Point(17, 19));

    ASSERT_FALSE(l1 == l2);
}

TEST(LINE_TEST, test_equal_with_two_line_with_all_differnt_point_should_return_false) {
    Line l1 = Line(Point(4, 4), Point(7, 9));
    Line l2 = Line(Point(2, 5), Point(17, 19));

    ASSERT_FALSE(l1 == l2);
}

TEST(LINE_TEST, test_get_intersection_with_one_intersection_should_return_correct_point) {
    Line line1(Point(2, 3), Point(2, 6));
    Line line2(Point(0, 6), Point(5, 2));

    std::optional<Point> intersect_point = line1.GetIntersectPoint(line2);

    ASSERT_EQ(intersect_point.has_value(), true);
    ASSERT_NEAR(intersect_point->GetX(), 2, 0.0001);
    ASSERT_NEAR(intersect_point->GetY(), 4.4, 0.0001);
}

TEST(LINE_TEST, test_get_intersection_with_the_same_line_should_return_empty_optional) {
    Line line1(Point(2, 3), Point(2, 6));
    Line line2(Point(2, 3), Point(2, 6));

    std::optional<Point> intersect_point = line1.GetIntersectPoint(line2);

    ASSERT_EQ(intersect_point.has_value(), false);
}

TEST(LINE_TEST, test_get_intersection_with_zero_intersection_should_return_empty_optional) {
    Line line1(Point(2, 3), Point(2, 6));
    Line line2(Point(0, 1), Point(5, 2));

    std::optional<Point> intersect_point = line1.GetIntersectPoint(line2);

    ASSERT_EQ(intersect_point.has_value(), false);
}