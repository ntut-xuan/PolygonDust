#ifndef POLYGON_CLIPPING_HPP
#define POLYGON_CLIPPING_HPP

#include "point.hpp"
#include "polygon.hpp"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>

class PolygonClipping {
  private:
    std::shared_ptr<Polygon> subjectPolygon;
    std::shared_ptr<Polygon> clippingPolygon;
    std::vector<Point> subject_list;
    std::vector<Point> clipping_list;
    std::map<Point, int> point_to_intersection_index;

    std::optional<int> GetIntersectionPointIndex(Point point) {
        auto point_iter = point_to_intersection_index.find(point);
        if (point_iter == point_to_intersection_index.end()) {
            return std::optional<int>();
        } else {
            return std::optional<int>({point_iter->second});
        }
    }

    int FindIntersectIndex(std::optional<int> subject_intersect_index) {
        int result = 0;
        std::optional<int> clipping_intersect_index = GetIntersectionPointIndex(clipping_list[result]);
        while (!(subject_intersect_index.value() == clipping_intersect_index.value_or(-1))) {
            result += 1;
            clipping_intersect_index = GetIntersectionPointIndex(clipping_list[result]);
        }
        return result;
    }

    void ProcessIntersectPoint(std::vector<Point> &clip_vertexes, size_t &subject_list_index) {
        int clip_list_intersect_end_id = 0;
        size_t subject_list_size = subject_list.size();
        size_t clipping_list_size = clipping_list.size();

        std::optional<int> subject_intersect_index = GetIntersectionPointIndex(subject_list[subject_list_index]);
        int clip_list_intersect_start_index = FindIntersectIndex(subject_intersect_index);

        std::optional<int> intersect_index = std::optional<int>();
        for (size_t j = 0; !(intersect_index.has_value()); j++) {
            int query_index = (clip_list_intersect_start_index + j + 1) % clipping_list_size;
            clip_vertexes.push_back(clipping_list[query_index]);

            intersect_index = GetIntersectionPointIndex(clipping_list[query_index]);

            if (intersect_index.has_value()) {
                clip_list_intersect_end_id = intersect_index.value();
            }
        }

        intersect_index = std::optional<int>();
        while (!(intersect_index.has_value() && intersect_index.value() == clip_list_intersect_end_id)) {
            subject_list_index += 1;
            int query_index = (subject_list_index) % subject_list_size;
            intersect_index = GetIntersectionPointIndex(subject_list[query_index]);
        }
    }

  public:
    PolygonClipping(std::shared_ptr<Polygon> subjectPolygon, std::shared_ptr<Polygon> clippingPolygon)
        : subjectPolygon(subjectPolygon), clippingPolygon(clippingPolygon) {}

    Polygon Produce() {
        CreateVertexList(subject_list, subjectPolygon, clippingPolygon);
        CreateVertexList(clipping_list, clippingPolygon, subjectPolygon);

        // Assume all polygon order counterwise.
        std::reverse(clipping_list.begin(), clipping_list.end());

        std::vector<Point> clip_vertexes;

        for (size_t i = 0; i < subject_list.size(); i++) {
            clip_vertexes.push_back(subject_list[i]);
            std::optional<int> subject_intersect_index = GetIntersectionPointIndex(subject_list[i]);

            if (subject_intersect_index.has_value()) {
                ProcessIntersectPoint(clip_vertexes, i);
            }
        }

        return Polygon(clip_vertexes);
    }

    void CreateVertexList(std::vector<Point> &list, std::shared_ptr<Polygon> major_polygon,
                          std::shared_ptr<Polygon> minor_polygon) {
        list.push_back(major_polygon->GetVertexs()->at(0));

        size_t major_polygon_vertex_size = major_polygon->GetVertexs()->size();
        size_t minor_polygon_vertex_size = minor_polygon->GetVertexs()->size();
        for (size_t i = 0; i < major_polygon_vertex_size; i++) {
            Point v11 = major_polygon->GetVertexs()->at((i) % major_polygon_vertex_size);
            Point v12 = major_polygon->GetVertexs()->at((i + 1) % major_polygon_vertex_size);
            Line line1(v11, v12);
            for (size_t j = 0; j < minor_polygon_vertex_size; j++) {
                Point v21 = minor_polygon->GetVertexs()->at((j) % minor_polygon_vertex_size);
                Point v22 = minor_polygon->GetVertexs()->at((j + 1) % minor_polygon_vertex_size);
                Line line2(v21, v22);

                std::optional<Point> intersect_point_optional = line1.GetIntersectPoint(line2);

                if (intersect_point_optional.has_value()) {
                    Point intersect_point = intersect_point_optional.value();
                    list.push_back(intersect_point);
                    if (point_to_intersection_index.find(intersect_point) == point_to_intersection_index.end()) {
                        point_to_intersection_index[intersect_point] = point_to_intersection_index.size();
                    }
                }
            }

            if (i != major_polygon_vertex_size - 1) {
                list.push_back(v12);
            }
        }
    }
};

#endif