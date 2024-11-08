#include <gtest/gtest.h>
#include <utility>

#include "shared.hpp"

TEST(UTILITY_TEST, test_get_matrix_computation_value_should_have_correct_value){
    int a = 3, b = 4, c = 7, d = 16;

    int val = GetMatrixComputationValue(a, b, c, d);

    ASSERT_EQ(val, 20);
}