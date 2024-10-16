#include <gtest/gtest.h>
#include <utility>

#include "../../cpp/utility.hpp"

TEST(UTILITY_TEST, test_get_matrix_computation_value_should_have_correct_value){
    int a = 3, b = 4, c = 7, d = 16;

    int val = GetMatrixComputationValue(a, b, c, d);

    ASSERT_EQ(val, 20);
}

TEST(UTILITY_TEST, test_get_angle_with_three_point_should_have_correct_value){
    Point a(6, 6);
    Point b(2, 4);
    Point c(4, 3);

    double slope = GetBisectorUnitSlope(a, b, c);

    ASSERT_NEAR(slope, 0, 0.001);
}

TEST(UTILITY_TEST, test_get_angle_with_three_point_and_obtuse_angel_should_have_correct_value){
    Point a(2, 4);
    Point b(4, 3);
    Point c(4, 1);

    double slope = GetBisectorUnitSlope(a, b, c);
    
    ASSERT_NEAR(slope, 0.618, 0.001);
}

TEST(UTILITY_TEST, test_get_line_cell_should_return_correct_cells){
    Point a(0, 0);
    Point b(2, 4);

    std::set<Point> cells = GetLineCell(a, b, 1);

    std::set<Point> expectedCells = {Point(0, 0), Point(0, 1), Point(1, 2), Point(1, 3)};
    ASSERT_EQ(cells, expectedCells);
}