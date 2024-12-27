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
        if ((std::find(x_set.begin(), x_set.end(), intersect_point->GetX()) != x_set.end()) &&
            this->IsLocalMinMaxPoint(intersect_point.value())) {
            x_set.push_back(intersect_point->GetX());
        }
    }
    return DeterminePointInPolygonByXSet(x_set, x);
}

bool Polygon::IsVertexInPolygon(Point point) {
    return std::find(vertexs->begin(), vertexs->end(), point) != vertexs->end();
}