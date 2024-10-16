#include "polygon.hpp"
#include "point.hpp"
#include <algorithm>
#include <cmath>
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

std::vector<Point> Polygon::GetBoundaryCell(double cellGap){
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
            double floorX = std::floor((currentX) / cellGap) * cellGap;
            double floorY = std::floor((currentY) / cellGap) * cellGap;
            std::pair<double, double> p(floorX, floorY);
            
            boundaryCell.insert(Point(floorX, floorY));

            currentX += unitVectorX * cellGap;
            currentY += unitVectorY * cellGap;
        }
    }

    // std::sort(boundaryCell.begin(), boundaryCell.end());
   
    return std::vector<Point>(boundaryCell.begin(), boundaryCell.end());
}

