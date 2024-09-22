#ifndef POINT_H
#define POINT_H

class Point {
private:
    int x;
    int y;
public:
    Point(int x, int y);
    ~Point() = default;
    int GetX();
    int GetY();
};

#endif