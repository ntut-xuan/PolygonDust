#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"
#include "shared.hpp"

#include <cmath>
#include <iostream>
#include <optional>
#include <string>

class Line {
  private:
    Point start;
    Point end;

  public:
    Line() = default;

    Line(Point start, Point end) {
        this->start = start;
        this->end = end;
    }

    Point GetMinimalPoint() {
        if (this->start <= this->end) {
            return this->start;
        } else {
            return this->end;
        }
    }

    Point GetMaximalPoint() {
        if (this->start >= this->end) {
            return this->start;
        } else {
            return this->end;
        }
    }

    bool operator==(const Line &other) const { return this->start == other.start && this->end == other.end; }

    /**
     * This is a function for get the intersect point of two lines.
     * These case will not present kf two line have 0 or more than 1 point
     * intersection.
     */
    std::optional<Point> GetYRayIntersectPoint(double y) {
        if (this->start.GetY() == this->end.GetY()) {
            return std::optional<Point>();
        }
        if (this->start.GetX() == this->end.GetX()) {
            if (Between<double>(y, this->start.GetY(), this->end.GetY())) {
                return std::optional<Point>({this->start.GetX(), y});
            } else {
                return std::optional<Point>();
            }
        }
        double m = (this->start.GetY() - this->end.GetY()) / (this->start.GetX() - this->end.GetX());
        double x = this->start.GetX() + (y - this->start.GetY()) / m;
        if (!Between(x, std::min(this->start.GetX(), this->end.GetX()),
                     std::max(this->start.GetX(), this->end.GetX()))) {
            return std::optional<Point>();
        }
        return std::optional<Point>({x, y});
    }

    /**
     * This is a function for get the intersect point of two lines.
     * These case will not present if two line have 0 or more than 1 point
     * intersection.
     */
    std::optional<Point> GetIntersectPoint(Line other) {
        double a1 = this->end.GetY() - this->start.GetY();
        double b1 = this->start.GetX() - this->end.GetX();
        double c1 = a1 * this->start.GetX() + b1 * this->start.GetY();

        double a2 = other.end.GetY() - other.start.GetY();
        double b2 = other.start.GetX() - other.end.GetX();
        double c2 = a2 * other.start.GetX() + b2 * other.start.GetY();

        double determine = a1 * b2 - a2 * b1;

        if (determine == 0) {
            return std::optional<Point>();
        }

        double x = (b2 * c1 - b1 * c2) / determine;
        double y = (a1 * c2 - a2 * c1) / determine;

        double this_min_x = std::min(this->start.GetX(), this->end.GetX());
        double this_max_x = std::max(this->start.GetX(), this->end.GetX());
        double this_min_y = std::min(this->start.GetY(), this->end.GetY());
        double this_max_y = std::max(this->start.GetY(), this->end.GetY());

        double other_min_x = std::min(other.start.GetX(), other.end.GetX());
        double other_max_x = std::max(other.start.GetX(), other.end.GetX());
        double other_min_y = std::min(other.start.GetY(), other.end.GetY());
        double other_max_y = std::max(other.start.GetY(), other.end.GetY());

        if (Between<double>(std::floor(x * 1e6), std::floor(this_min_x * 1e6), std::floor(this_max_x * 1e6)) &&
            Between<double>(std::floor(y * 1e6), std::floor(this_min_y * 1e6), std::floor(this_max_y * 1e6)) &&
            Between<double>(std::floor(x * 1e6), std::floor(other_min_x * 1e6), std::floor(other_max_x * 1e6)) &&
            Between<double>(std::floor(y * 1e6), std::floor(other_min_y * 1e6), std::floor(other_max_y * 1e6))) {
            return std::optional<Point>({x, y});
        }

        return std::optional<Point>();
    }
};

#endif