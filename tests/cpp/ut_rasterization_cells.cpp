#include "point.hpp"
#include "rasterization_cells.hpp"
#include <gtest/gtest.h>
#include <set>

TEST(RASTERIZATION_CELLS_TEST, test_rasterization_cell_with_construct_should_return_correct_rasterization_cells){
    std::vector<Point> points = {Point(1, 1), Point(1, 2), Point(1, 3)};
    RasterizationCells rasterizationCells(points);

    std::set<Point> cellSet = rasterizationCells.GetCellSet();

    ASSERT_EQ(cellSet, std::set<Point>({Point(1, 1), Point(1, 2), Point(1, 3)}));
}

TEST(RASTERIZATION_CELLS_TEST, test_rasterization_cell_with_union_should_return_correct_rasterization_cells){
    RasterizationCells rasterizationCells(std::vector<Point>{Point(1, 1), Point(1, 2), Point(1, 3)});
    RasterizationCells anotherRasterizationCells(std::vector<Point>{Point(1, 2), Point(1, 5), Point(1, 6)});

    rasterizationCells.Union(anotherRasterizationCells);

    std::set<Point> cellSet = rasterizationCells.GetCellSet();
    ASSERT_EQ(cellSet, std::set<Point>({Point(1, 1), Point(1, 2), Point(1, 3), Point(1, 5), Point(1, 6)}));
}

TEST(RASTERIZATION_CELLS_TEST, test_rasterization_cell_with_cut_should_return_correct_rasterization_cells){
    RasterizationCells rasterizationCells(std::vector<Point>{Point(1, 1), Point(1, 2), Point(1, 3)});
    RasterizationCells anotherRasterizationCells(std::vector<Point>{Point(1, 2), Point(1, 5), Point(1, 6)});

    rasterizationCells.Cut(anotherRasterizationCells);

    std::set<Point> cellSet = rasterizationCells.GetCellSet();
    ASSERT_EQ(cellSet, std::set<Point>({Point(1, 1), Point(1, 3)}));
}

TEST(RASTERIZATION_CELLS_TEST, test_rasterization_cell_with_intersect_should_return_correct_rasterization_cells){
    RasterizationCells rasterizationCells(std::vector<Point>{Point(1, 1), Point(1, 2), Point(1, 3)});
    RasterizationCells anotherRasterizationCells(std::vector<Point>{Point(1, 2), Point(1, 5), Point(1, 6)});

    rasterizationCells.Intersect(anotherRasterizationCells);

    std::set<Point> cellSet = rasterizationCells.GetCellSet();
    ASSERT_EQ(cellSet, std::set<Point>({Point(1, 2)}));
}