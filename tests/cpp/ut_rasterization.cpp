#include "point.hpp"
#include "polygon.hpp"
#include "rasterization.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(RASTERIZATION_TEST, test_rasterization_with_valid_polygon_should_transfrom_correct_cells){
    std::shared_ptr<Polygon> polygon = std::make_shared<Polygon>(std::vector<Point>{Point(1, 1), Point(3, 5), Point(6, 3)});
    Rasterization rasterization(polygon, 1);

    std::shared_ptr<std::vector<Point>> cells = rasterization.GetCells();
    ASSERT_EQ(*cells.get(), std::vector<Point>({
        Point(1, 1),
        Point(2, 2), Point(3, 2), 
        Point(2, 3), Point(3, 3), Point(4, 3), Point(5, 3),
        Point(3, 4), Point(4, 4),
    }));
}