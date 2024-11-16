#include "point.hpp"

double Point::GetX() const{
    return std::round(this->x * 1e6) / 1e6;
}

double Point::GetY() const {
    return std::round(this->y * 1e6) / 1e6;
}