#ifndef POLYGON_H
#define POLYGON_H

#include "line.hpp"
#include "point.hpp"
#include "shared.hpp"
#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

class Polygon {
  private:
    std::shared_ptr<std::vector<Point>> vertexs;
    std::vector<Polygon> holes;
    std::shared_ptr<std::vector<Line>> lines;
    std::shared_ptr<std::set<Point>> localminmaxs;
    std::vector<Line> localminmax_horizontal_lines;
    std::vector<Line> horizontal_lines;
    bool clockwise;
    double min_x = INT_MAX, min_y = INT_MAX, max_x = INT_MIN, max_y = INT_MIN;
    void ConstructLocalMinMaxPoints() {
        for (size_t i = 0; i < vertexs->size(); i++) {
            Point startPoint = vertexs->at(i);
            Point middlePoint = vertexs->at((i + 1) % (vertexs->size()));
            Point endPoint = vertexs->at((i + 2) % (vertexs->size()));
            if (!(Between(middlePoint.GetY(), startPoint.GetY(), endPoint.GetY()) ||
                  Between(middlePoint.GetY(), endPoint.GetY(), startPoint.GetY()))) {
                localminmaxs->insert(middlePoint);
            }
        }
    }
    void ConstructLocalMinMaxHorizontalLine() {
        for (size_t i = 0; i < vertexs->size(); i++) {
            Point p1 = vertexs->at(i);
            Point p2 = vertexs->at((i + 1) % (vertexs->size()));
            Point p3 = vertexs->at((i + 2) % (vertexs->size()));
            Point p4 = vertexs->at((i + 3) % (vertexs->size()));
            Line l1(p1, p2);
            Line l2(p2, p3);
            Line l3(p3, p4);

            if (l2.IsHorizontalLine()) {
                horizontal_lines.push_back(l2);
            }

            if (l2.IsHorizontalLine() && !((p1.GetY() <= p2.GetY() && p3.GetY() <= p4.GetY()) ||
                                           (p1.GetY() >= p2.GetY() && p3.GetY() >= p4.GetY()))) {
                localminmax_horizontal_lines.push_back(l2);
            }
        }
    }
    void ConstructLines() {
        for (size_t i = 0; i < vertexs->size(); i++) {
            Point startPoint = vertexs->at(i);
            Point endPoint = vertexs->at((i + 1) % vertexs->size());
            lines->push_back(Line(startPoint, endPoint));
        }
    }
    void DetermineClockwise() {
        double a = 0;
        for (size_t i = 0; i < vertexs->size(); i++) {
            double x1 = vertexs->at(i).GetX();
            double y1 = vertexs->at(i).GetY();
            double x2 = vertexs->at((i + 1) % vertexs->size()).GetX();
            double y2 = vertexs->at((i + 1) % vertexs->size()).GetY();
            a += (x1 * y2 - x2 * y1);
        }
        a *= 0.5;
        clockwise = (a > 0);
    }

  public:
    Polygon() = default;
    Polygon(std::vector<Point> vertexs) {
        this->vertexs = std::make_shared<std::vector<Point>>(vertexs.begin(), vertexs.end());
        this->lines = std::make_shared<std::vector<Line>>();
        this->localminmaxs = std::make_shared<std::set<Point>>();
        this->holes = std::vector<Polygon>();
        for (Point p : vertexs) {
            min_x = std::min(p.GetX(), min_x);
            max_x = std::max(p.GetX(), max_x);
            min_y = std::min(p.GetY(), min_y);
            max_y = std::max(p.GetY(), max_y);
        }
        ConstructLines();
        ConstructLocalMinMaxPoints();
        ConstructLocalMinMaxHorizontalLine();
        DetermineClockwise();
    }
    Polygon(std::vector<Point> outbound_vertexs, std::vector<Polygon> holes) : Polygon(outbound_vertexs) {
        this->holes = holes;
    }
    bool operator==(const Polygon &other) const { return this->GetVertexs() == other.GetVertexs(); }
    ~Polygon() = default;
    std::shared_ptr<std::vector<Point>> GetVertexs() const;
    std::vector<Polygon> GetHoles() { return this->holes; };
    std::vector<Point> GetVertexsVector();
    std::shared_ptr<std::vector<Point>> GetLocalMinMaxVertexs();
    std::shared_ptr<std::vector<Line>> GetLines();
    std::vector<double> localminmax_x_set_optimization(std::vector<double> x_set, double y);
    double GetArea();
    double GetMinX() { return min_x; }
    double GetMinY() { return min_y; }
    double GetMaxX() { return max_x; }
    double GetMaxY() { return max_y; }
    bool IsLocalMinMaxPoint(Point point);
    bool IsClockwise() { return clockwise; }
    bool IsPointInPolygon(Point point);
    bool IsVertexInPolygon(Point point);
    bool IsHorizontalLine(Line line) {
        for (Line horizontal_line : horizontal_lines) {
            if (line.GetMinimalPoint() == horizontal_line.GetMinimalPoint() &&
                line.GetMaximalPoint() == horizontal_line.GetMaximalPoint()) {
                return true;
            }
        }
        return false;
    }
    bool IsHorizontalMinMaxLine(Line line) {
        for (Line horizontal_line : localminmax_horizontal_lines) {
            if (line.GetMinimalPoint() == horizontal_line.GetMinimalPoint() &&
                line.GetMaximalPoint() == horizontal_line.GetMaximalPoint()) {
                return true;
            }
        }
        return false;
    }
};
#endif
