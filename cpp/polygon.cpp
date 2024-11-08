#include "polygon.hpp"
#include "point.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "utility.hpp"

double Polygon::GetArea(){
    double v = 0;
    for(int index = 0; index < (int) vertexs.size(); index++){
        v += GetMatrixComputationValue(
            vertexs.at(index).GetX(),
            vertexs.at((index + 1) % (int) (vertexs.size())).GetX(),
            vertexs.at(index).GetY(),
            vertexs.at((index + 1) % (int) (vertexs.size())).GetY()
        );
    }
    return 0.5 * abs(v);
}

std::vector<Point> Polygon::GetVertexs(){
    return this->vertexs;
}