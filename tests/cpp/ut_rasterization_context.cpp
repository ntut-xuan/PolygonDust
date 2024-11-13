#include <gtest/gtest.h>
#include <memory>

#include "point.hpp"
#include "rasterization_context.hpp"

TEST(RASTERIZATION_CONTEXT_TEST, test_rasterization_context_with_one_polygon_should_have_correct_polygon){
    RasterizationContext rasterizationContext(1);
    std::shared_ptr<Polygon> polygon = std::make_shared<Polygon>(std::vector<Point>{Point(1, 1), Point(3, 5), Point(6, 3)});
    rasterizationContext.AddPolygon(*polygon.get());

    std::vector<Point> cells = rasterizationContext.GetPolygonCell(0);

    ASSERT_EQ(cells, std::vector<Point>({
        Point(1, 1),
        Point(2, 2), Point(3, 2), 
        Point(2, 3), Point(3, 3), Point(4, 3), Point(5, 3),
        Point(3, 4), Point(4, 4),
    }));
}

TEST(RASTERIZATION_CONTEXT_TEST, test_rasterization_context_with_multiple_polygon_should_have_correct_minimal_x){
    RasterizationContext rasterizationContext(1);
    std::shared_ptr<Polygon> polygon1 = std::make_shared<Polygon>(std::vector<Point>{Point(1, 1), Point(3, 5), Point(6, 3)});
    std::shared_ptr<Polygon> polygon2 = std::make_shared<Polygon>(std::vector<Point>{Point(0, 0), Point(2, 4), Point(5, 2)});
    rasterizationContext.AddPolygon(*polygon1.get());
    rasterizationContext.AddPolygon(*polygon2.get());

    double min_x = rasterizationContext.GetMinX();

    ASSERT_EQ(min_x, 0);
}

TEST(RASTERIZATION_CONTEXT_TEST, test_rasterization_context_with_multiple_polygon_should_have_correct_maximal_x){
    RasterizationContext rasterizationContext(1);
    std::shared_ptr<Polygon> polygon1 = std::make_shared<Polygon>(std::vector<Point>{Point(1, 1), Point(3, 5), Point(6, 3)});
    std::shared_ptr<Polygon> polygon2 = std::make_shared<Polygon>(std::vector<Point>{Point(0, 0), Point(2, 4), Point(5, 2)});
    rasterizationContext.AddPolygon(*polygon1.get());
    rasterizationContext.AddPolygon(*polygon2.get());

    double max_x = rasterizationContext.GetMaxX();

    ASSERT_EQ(max_x, 6);
}

TEST(RASTERIZATION_CONTEXT_TEST, test_rasterization_context_with_multiple_polygon_should_have_correct_minimal_y){
    RasterizationContext rasterizationContext(1);
    std::shared_ptr<Polygon> polygon1 = std::make_shared<Polygon>(std::vector<Point>{Point(1, 1), Point(3, 5), Point(6, 3)});
    std::shared_ptr<Polygon> polygon2 = std::make_shared<Polygon>(std::vector<Point>{Point(0, 0), Point(2, 4), Point(5, 2)});
    rasterizationContext.AddPolygon(*polygon1.get());
    rasterizationContext.AddPolygon(*polygon2.get());

    double min_y = rasterizationContext.GetMinY();

    ASSERT_EQ(min_y, 0);
}

TEST(RASTERIZATION_CONTEXT_TEST, test_rasterization_context_with_multiple_polygon_should_have_correct_maximal_y){
    RasterizationContext rasterizationContext(1);
    std::shared_ptr<Polygon> polygon1 = std::make_shared<Polygon>(std::vector<Point>{Point(1, 1), Point(3, 5), Point(6, 3)});
    std::shared_ptr<Polygon> polygon2 = std::make_shared<Polygon>(std::vector<Point>{Point(0, 0), Point(2, 4), Point(5, 2)});
    rasterizationContext.AddPolygon(*polygon1.get());
    rasterizationContext.AddPolygon(*polygon2.get());

    double max_y = rasterizationContext.GetMaxY();

    ASSERT_EQ(max_y, 5);
}