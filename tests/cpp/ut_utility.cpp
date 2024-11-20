#include <gtest/gtest.h>
#include <utility>

#include "shared.hpp"

TEST(UTILITY_TEST, test_get_matrix_computation_value_should_have_correct_value){
    int a = 3, b = 4, c = 7, d = 16;

    int val = GetMatrixComputationValue(a, b, c, d);

    ASSERT_EQ(val, 20);
}

TEST(UTILITY_TEST, test_between_with_between_value_should_return_true){
    bool between = Between<int>(5, 2, 8);

    ASSERT_TRUE(between);
}

TEST(UTILITY_TEST, test_between_with_not_between_value_should_return_false){
    bool between = Between<int>(10, 2, 8);

    ASSERT_FALSE(between);
}