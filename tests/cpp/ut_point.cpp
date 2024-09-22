#include <gtest/gtest.h>

#include "../../cpp/point.hpp"

TEST(POINT_TEST, test_point_constructor_should_have_correct_x_value){
    Point point(5, 7);

    ASSERT_EQ(point.GetX(), 5);
}

TEST(POINT_TEST, test_point_constructor_should_have_correct_y_value){
    Point point(5, 7);

    ASSERT_EQ(point.GetY(), 7);
}