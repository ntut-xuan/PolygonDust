#ifndef POINT_H
#define POINT_H

#include <string>

#define IS_NOT_EQUAL(x, y) (long long)((x + 1e-9) * 1e9) != (long long)((y + 1e-9) * 1e9)
#define IS_LESS_THAN(x, y) (long long)((x + 1e-9) * 1e9) < (long long)((y + 1e-9) * 1e9)
#define IS_LESS_EQUAL(x, y) (long long)((x + 1e-9) * 1e9) <= (long long)((y + 1e-9) * 1e9)
#define IS_GREATER_THAN(x, y) (long long)((x + 1e-9) * 1e9) > (long long)((y + 1e-9) * 1e9)
#define IS_GREATER_EQUAL(x, y) (long long)((x + 1e-9) * 1e9) >= (long long)((y + 1e-9) * 1e9)
#define IS_EQUAL(x, y) (long long)((x + 1e-9) * 1e9) == (long long)((y + 1e-9) * 1e9)

class Point {
private:
    double x = 0;
    double y = 0;
public:
    Point() {

    };
    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
    ~Point() = default;
    bool operator<(const Point &other) const{
        if (IS_NOT_EQUAL(y, other.y)) {
            return IS_LESS_THAN(y, other.y);
        }
        return IS_LESS_THAN(x, other.x);
    }
    bool operator>(const Point &other) const{
        if (IS_NOT_EQUAL(y, other.y)) {
            return IS_GREATER_THAN(y, other.y);
        }
        return IS_GREATER_THAN(x, other.x);
    }
    bool operator<=(const Point &other) const{
        if (IS_NOT_EQUAL(y, other.y)) {
            return IS_LESS_EQUAL(y, other.y);
        }
        return IS_LESS_EQUAL(x, other.x);
    }
    bool operator>=(const Point &other) const{
        if (IS_NOT_EQUAL(y, other.y)) {
            return IS_GREATER_EQUAL(y, other.y);
        }
        return IS_GREATER_EQUAL(x, other.x);
    }
    bool operator==(const Point &other) const{
        return IS_EQUAL(x, other.x) && IS_EQUAL(y, other.y);
    }

    friend void PrintTo(const Point& point, std::ostream* os) {
        *os << point.ToString();
    }

    double GetX() const;
    double GetY() const;

    std::string ToString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

#endif