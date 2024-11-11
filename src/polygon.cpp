#include "polygon.hpp"
#include "point.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "shared.hpp"

double Polygon::GetArea(){
    double v = 0;
    for(int index = 0; index < (int) vertexs->size(); index++){
        v += GetMatrixComputationValue(
            vertexs->at(index).GetX(),
            vertexs->at((index + 1) % (int) (vertexs->size())).GetX(),
            vertexs->at(index).GetY(),
            vertexs->at((index + 1) % (int) (vertexs->size())).GetY()
        );
    }
    return 0.5 * abs(v);
}

std::shared_ptr<std::vector<Point>> Polygon::GetVertexs(){
    return this->vertexs;
}

std::shared_ptr<std::vector<Line>>Polygon::GetLines(){
    return this->lines;
}

std::shared_ptr<std::vector<Point>> Polygon::GetLocalMinMaxVertexs(){
    return this->localminmaxs;
}

bool Polygon::IsLocalMinMaxPoint(Point point){
    return std::binary_search(localminmaxs->begin(), localminmaxs->end(), point);
}