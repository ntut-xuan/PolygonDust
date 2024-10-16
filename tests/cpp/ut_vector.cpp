#include <gtest/gtest.h>

#include "../../cpp/vector.hpp"

TEST(VECTOR_TEST, test_vector_construct_should_have_correct_x_and_y){
    Vector vector(2, 5);

    ASSERT_EQ(vector.GetX(), 2);
    ASSERT_EQ(vector.GetY(), 5);
}

TEST(VECTOR_TEST, test_vector_construct_with_two_point_should_have_correct_x_and_y){
    Point a(0, 0);
    Point b(3, 3);

    Vector vector(a, b);

    ASSERT_NEAR(vector.GetX(), 0.707, 0.001);
    ASSERT_NEAR(vector.GetY(), 0.707, 0.001);
}

TEST(VECTOR_TEST, test_vector_add_operation_with_two_vector_should_have_correct_x_and_y){
    Vector a(0, 0);
    Vector b(3, 3);

    Vector vector = a + b;

    ASSERT_EQ(vector.GetX(), 3);
    ASSERT_EQ(vector.GetY(), 3);
}