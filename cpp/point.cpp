#include "point.hpp"

Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}

int Point::GetX(){
    return this->x;
}

int Point::GetY(){
    return this->y;
}