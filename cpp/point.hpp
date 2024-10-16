#ifndef POINT_H
#define POINT_H

class Point {
private:
    double x = 0;
    double y = 0;
public:
    Point(int x, int y);
    Point(double x, double y) : x(x), y(y) {}
    ~Point() = default;
    bool operator==(const Point &p2) const{
        return this->x == p2.x && this->y == p2.y;
    }
    bool operator<(const Point &p2) const {
        return this->x == p2.x ? (this->y == p2.y ? false : this->x < p2.x) : this->y < p2.y;
    }
    int GetX();
    int GetY();
};

#endif