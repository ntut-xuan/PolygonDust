#include <gtest/gtest.h>

#include "point.hpp"

TEST(POINT_TEST, test_point_constructor_should_have_correct_x_value){
    Point point(5, 7);

    ASSERT_EQ(point.GetX(), 5);
}

TEST(POINT_TEST, test_point_constructor_should_have_correct_y_value){
    Point point(5, 7);

    ASSERT_EQ(point.GetY(), 7);
}

TEST(POINT_TEST, test_point_less_operation_should_return_correct_point){
    Point point1(2, 3);
    Point point2(5, 7);

    ASSERT_TRUE(point1 < point2);
}

TEST(POINT_TEST, test_point_less_equal_operation_should_return_correct_point){
    Point point1(2, 3);
    Point point2(5, 7);

    ASSERT_TRUE(point1 <= point2);
}

TEST(POINT_TEST, test_point_less_equal_operation_with_two_equal_value_should_return_correct_point){
    Point point1(2, 3);
    Point point2(2, 3);

    ASSERT_TRUE(point1 <= point2);
}

TEST(POINT_TEST, test_point_greater_operation_should_return_correct_point){
    Point point1(2, 3);
    Point point2(5, 7);

    ASSERT_TRUE(point2 > point1);
}

TEST(POINT_TEST, test_point_greater_operation_with_same_y_should_return_correct_point){
    Point point1(2, 7);
    Point point2(5, 7);

    ASSERT_TRUE(point2 > point1);
}

TEST(POINT_TEST, test_point_greater_equal_operation_should_return_correct_point){
    Point point1(2, 3);
    Point point2(5, 7);

    ASSERT_TRUE(point2 >= point1);
}

TEST(POINT_TEST, test_point_greater_equal_operation_with_two_equal_value_should_return_correct_point){
    Point point1(2, 3);
    Point point2(2, 3);

    ASSERT_TRUE(point1 >= point2);
}

TEST(POINT_TEST, test_point_to_string_should_return_correct_point_string){
    Point point1(2, 3);

    ASSERT_EQ(point1.ToString(), "(2.000000, 3.000000)");
}