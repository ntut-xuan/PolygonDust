#ifndef POLYGON_CLIPPING_HPP
#define POLYGON_CLIPPING_HPP

#include "point.hpp"
#include "polygon.hpp"
#include "shared.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

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
        while (!(clipping_intersect_index.has_value() &&
                 subject_intersect_index.value() == clipping_intersect_index.value())) {
            result += 1;
            clipping_intersect_index = GetIntersectionPointIndex(clipping_list[result]);
        }
        return result;
    }

    void ProcessIntersectPoint(std::vector<Point> &clip_vertexes, size_t &subject_list_index) {
        int clip_list_intersect_end_id = 0;
        size_t subject_list_size = subject_list.size();
        size_t clipping_list_size = clipping_list.size();
        size_t query_node_index = (subject_list_index) % (subject_list.size());

        std::optional<int> subject_intersect_index = GetIntersectionPointIndex(subject_list[query_node_index]);

        int clip_list_intersect_start_index = FindIntersectIndex(subject_intersect_index);

        for (size_t j = 0; j < clipping_list_size; j++) {
            int query_index = (clip_list_intersect_start_index + j + 1) % clipping_list_size;
            clip_vertexes.push_back(clipping_list[query_index]);

            std::cout << "Rounding clipping_list node " << clipping_list[query_index].ToString() << std::endl;

            std::optional<int> intersect_index = GetIntersectionPointIndex(clipping_list[query_index]);

            if (intersect_index.has_value()) {
                std::cout << "Found next intersect point." << std::endl;
                clip_list_intersect_end_id = intersect_index.value();
                break;
            }
        }

        for (size_t j = 0; j < subject_list_size; j++) {
            subject_list_index += 1;
            subject_list_index %= subject_list_size;
            int query_index = (subject_list_index) % subject_list_size;
            std::optional<int> intersect_index = GetIntersectionPointIndex(subject_list[query_index]);

            if (intersect_index.has_value() && intersect_index.value() == clip_list_intersect_end_id) {
                std::cout << "Move to next subject list node." << std::endl;
                break;
            }
        }
    }

  public:
    PolygonClipping(std::shared_ptr<Polygon> subjectPolygon, std::shared_ptr<Polygon> clippingPolygon)
        : subjectPolygon(subjectPolygon), clippingPolygon(clippingPolygon) {}

    Polygon Produce() {

        std::cout << "Process Create Vertex List." << std::endl;

        CreateVertexList(subject_list, subjectPolygon, clippingPolygon);
        CreateVertexList(clipping_list, clippingPolygon, subjectPolygon);

        for (Point point : subject_list) {
            if (GetIntersectionPointIndex(point).has_value()) {
                std::cout << "Subject Polygon have intersect point " << point.ToString() << std::endl;
            } else {
                std::cout << "Subject Polygon have point " << point.ToString() << std::endl;
            }
        }

        for (Point point : clipping_list) {
            if (GetIntersectionPointIndex(point).has_value()) {
                std::cout << "Clipping Polygon have intersect point " << point.ToString() << std::endl;
            } else {
                std::cout << "Clipping Polygon have point " << point.ToString() << std::endl;
            }
        }

        // subjectPolygon clockwise should different on clippingPolygon.
        if ((subjectPolygon->IsClockwise() ^ clippingPolygon->IsClockwise()) == 0) {
            std::reverse(clipping_list.begin(), clipping_list.end());
        }

        std::cout << "Process Polygon." << std::endl;

        std::vector<Point> clip_vertexes;

        std::cout << "Finding Start Node." << std::endl;

        int subject_start_node = 0;

        for (size_t i = 0; i < subject_list.size(); i++) {
            Point point = subject_list[i];
            if (!(Between<double>(point.GetX(), clippingPolygon->GetMinX(), clippingPolygon->GetMaxX()) &&
                  Between<double>(point.GetY(), clippingPolygon->GetMinY(), clippingPolygon->GetMaxY()))) {
                subject_start_node = i;
                break;
            }
        }

        std::cout << "Found start node, start rounding." << std::endl;

        for (size_t i = subject_start_node, j = 0; j < subject_list.size(); i++, j++) {
            size_t query_node_index = (i) % (subject_list.size());
            clip_vertexes.push_back(subject_list[query_node_index]);

            std::cout << "Rounding subject node " << subject_list[query_node_index].ToString() << std::endl;

            std::optional<int> subject_intersect_index = GetIntersectionPointIndex(subject_list[query_node_index]);

            if (subject_intersect_index.has_value()) {
                std::cout << "Found intersect point, switch list into clip_vertexes." << std::endl;
                ProcessIntersectPoint(clip_vertexes, i);
            }
        }

        int duplicate_index = clip_vertexes.size();

        for (size_t i = 1; i < clip_vertexes.size(); i++) {
            if (clip_vertexes[0] == clip_vertexes[i]) {
                duplicate_index = i;
                break;
            }
        }

        return Polygon(std::vector<Point>(clip_vertexes.begin(), clip_vertexes.begin() + duplicate_index));
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

            std::vector<Point> intersect_points;

            for (size_t j = 0; j < minor_polygon_vertex_size; j++) {
                Point v21 = minor_polygon->GetVertexs()->at((j) % minor_polygon_vertex_size);
                Point v22 = minor_polygon->GetVertexs()->at((j + 1) % minor_polygon_vertex_size);
                Line line2(v21, v22);

                std::optional<Point> intersect_point_optional = line1.GetIntersectPoint(line2);

                if (intersect_point_optional.has_value()) {
                    std::cout << "Create Intersect Point " << intersect_point_optional.value().ToString() << std::endl;
                    Point intersect_point = intersect_point_optional.value();
                    intersect_points.push_back(intersect_point);
                    if (point_to_intersection_index.find(intersect_point) == point_to_intersection_index.end()) {
                        point_to_intersection_index[intersect_point] = point_to_intersection_index.size();
                    }
                }
            }

            std::sort(intersect_points.begin(), intersect_points.end(),
                      [v11](const Point &a, const Point &b) { return GetDistance(v11, a) < GetDistance(v11, b); });

            for (Point p : intersect_points) {
                list.push_back(p);
            }

            if (i != major_polygon_vertex_size - 1) {
                list.push_back(v12);
            }
        }
    }
};

#endif