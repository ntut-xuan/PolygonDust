#include "polygon.hpp"
#include "point.hpp"
#include <cmath>
#include <vector>

#include "utility.hpp"

double Polygon::GetArea(){
    double v = 0;
    for(int index = 0; index < (int) vertexs.size() + 1; index++){
        v += GetMatrixComputationValue(
            vertexs[(index)].GetX(),
            vertexs[(index + 1) % (vertexs.size())].GetX(),
            vertexs[(index)].GetY(),
            vertexs[(index + 1) % (vertexs.size())].GetY()
        );
    }
    return 0.5 * abs(v);
}

std::vector<Point> Polygon::GetVertexs(){
    return this->vertexs;
}

std::set<Point> Polygon::GetBoundaryCell(double cellGap){
    std::set<Point> boundaryCell;

    for(int index = 0; index < (int) this->vertexs.size(); index++){
        Point firstVertex = vertexs[index];
        Point secondVertex = vertexs[(index + 1) % (this->vertexs.size())];

        double distance = GetDistance(firstVertex, secondVertex);
        double unitVectorX = (secondVertex.GetX() - firstVertex.GetX()) / distance;
        double unitVectorY = (secondVertex.GetY() - firstVertex.GetY()) / distance;

        double currentX = firstVertex.GetX();
        double currentY = firstVertex.GetY();

        for(int i = 0; i < distance / cellGap; i++){
            Point cell(std::floor((currentX) / cellGap) * cellGap, std::floor((currentY) / cellGap) * cellGap);

            boundaryCell.insert(cell);

            currentX += unitVectorX * cellGap;
            currentY += unitVectorY * cellGap;
        }
    }

    return boundaryCell;
}