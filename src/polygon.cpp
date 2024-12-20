#include "polygon.hpp"
#include "point.hpp"
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