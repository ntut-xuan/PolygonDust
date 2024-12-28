#include "polygon.hpp"
#include "point.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>
#include <vector>

#include "shared.hpp"

double Polygon::GetArea() {
    double v = 0;
    for (int index = 0; index < (int)vertexs->size(); index++) {
        v += GetMatrixComputationValue(
            vertexs->at(index).GetX(), vertexs->at((index + 1) % (int)(vertexs->size())).GetX(),
            vertexs->at(index).GetY(), vertexs->at((index + 1) % (int)(vertexs->size())).GetY());
    }
    return 0.5 * abs(v);
}

std::shared_ptr<std::vector<Point>> Polygon::GetVertexs() const { return this->vertexs; }

std::vector<Point> Polygon::GetVertexsVector() { return *this->vertexs; }

std::shared_ptr<std::vector<Line>> Polygon::GetLines() { return this->lines; }

std::shared_ptr<std::vector<Point>> Polygon::GetLocalMinMaxVertexs() {
    return std::make_shared<std::vector<Point>>(localminmaxs->begin(), localminmaxs->end());
}

std::vector<double> Polygon::localminmax_x_set_optimization(std::vector<double> x_set, double y) {

    if (x_set.size() == 0) {
        return x_set;
    }

    std::vector<double> minmax_fix_x_set;

    for (size_t i = 0; i < x_set.size(); i++) {
        if ((i != x_set.size() - 1) && IsHorizontalLine(Line(Point(x_set[i], y), Point(x_set[i + 1], y))) &&
            !IsHorizontalMinMaxLine(Line(Point(x_set[i], y), Point(x_set[i + 1], y)))) {
            minmax_fix_x_set.push_back(x_set[i + 1]);
            i += 1;
        } else if ((i != x_set.size() - 1) && IsHorizontalLine(Line(Point(x_set[i], y), Point(x_set[i + 1], y)))) {
            minmax_fix_x_set.push_back(x_set[i]);
            minmax_fix_x_set.push_back(x_set[i + 1]);
            i += 1;
        } else if (IsLocalMinMaxPoint(Point(x_set[i], y))) {
            minmax_fix_x_set.push_back(x_set[i]);
            minmax_fix_x_set.push_back(x_set[i]);
        } else {
            minmax_fix_x_set.push_back(x_set[i]);
        }
    }

    return minmax_fix_x_set;
}

bool Polygon::IsLocalMinMaxPoint(Point point) { return localminmaxs->find(point) != localminmaxs->end(); }

bool Polygon::IsPointInPolygon(Point point) {
    std::vector<double> x_set;
    double x = point.GetX();
    double y = point.GetY();
    for (size_t i = 0; i < vertexs->size(); i++) {
        Point start = vertexs->at(i);
        Point end = vertexs->at((i + 1) % vertexs->size());
        Line line(start, end);

        std::optional<Point> intersect_point = line.GetYRayIntersectPoint(y);

        if (!intersect_point.has_value()) {
            continue;
        }

        if (std::find(x_set.begin(), x_set.end(), intersect_point->GetX()) == x_set.end()) {
            x_set.push_back(intersect_point->GetX());
        }
    }

    std::sort(x_set.begin(), x_set.end());

    x_set = localminmax_x_set_optimization(x_set, y);

    return DeterminePointInPolygonByXSet(x_set, x);
}