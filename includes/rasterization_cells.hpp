#ifndef RASTERIZATION_CELLS_HPP
#define RASTERIZATION_CELLS_HPP

#include "point.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

class RasterizationCells {
private:
    std::set<Point> cellSet;
public:
    RasterizationCells(std::vector<Point> cells){
        cellSet = std::set<Point>(cells.begin(), cells.end());
    }
    void Cut(RasterizationCells &other){
        std::vector<Point> tempSet;
        std::set<Point> other_points = other.GetCellSet();
        std::copy_if(
            cellSet.begin(), 
            cellSet.end(), 
            std::back_inserter(tempSet), 
            [other_points](const Point &a){
                return other_points.find(a) == other_points.end();
            }
        );
        cellSet = std::set<Point>(tempSet.begin(), tempSet.end());
    }
    void Intersect(RasterizationCells &other){
        std::set<Point> tempSet;
        std::set<Point> other_points = other.GetCellSet();
        std::copy_if(
            cellSet.begin(), 
            cellSet.end(), 
            std::inserter(tempSet, tempSet.begin()), 
            [other_points](const Point &a){
                return other_points.find(a) != other_points.end();
            }
        );
        cellSet = tempSet;
    }
    void Union(RasterizationCells &other){
        for(Point point : other.GetCellSet()){
            cellSet.insert(point);
        }
    }
    std::set<Point> GetCellSet(){
        return cellSet;
    }
};

#endif