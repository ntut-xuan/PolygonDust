#ifndef POLYGON_CLIPPING_HPP
#define POLYGON_CLIPPING_HPP

#include "line.hpp"
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

class PointWithState {
  private:
    Point point;
    bool in_polygon;

  public:
    PointWithState(Point point, bool in_polygon) {
        this->point = point;
        this->in_polygon = in_polygon;
    }
    Point GetPoint() const { return this->point; }
    bool IsInPolygon() const { return this->in_polygon; }
    bool operator==(const PointWithState &other) const {
        return this->point == other.point && this->in_polygon == other.in_polygon;
    }
    friend void PrintTo(const PointWithState &point_with_state, std::ostream *os) {
        *os << point_with_state.ToString();
    }
    std::string ToString() const { return point.ToString() + " - " + (in_polygon ? "InPolygon" : "OutPolygon"); }
};

class PolygonClipping {
  private:
    std::shared_ptr<Polygon> subjectPolygon;
    std::shared_ptr<Polygon> clippingPolygon;
    std::vector<PointWithState> subject_list;
    std::vector<PointWithState> clipping_list;
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
        std::optional<int> clipping_intersect_index = GetIntersectionPointIndex(clipping_list[result].GetPoint());
        while (!(clipping_intersect_index.has_value() &&
                 subject_intersect_index.value() == clipping_intersect_index.value())) {
            result += 1;
            clipping_intersect_index = GetIntersectionPointIndex(clipping_list[result].GetPoint());
        }
        return result;
    }

    void ProcessIntersectPoint(std::vector<Point> &clip_vertexes, size_t &subject_list_index) {
        int clip_list_intersect_end_id = 0;
        size_t subject_list_size = subject_list.size();
        size_t clipping_list_size = clipping_list.size();
        size_t query_node_index = (subject_list_index) % (subject_list.size());

        std::optional<int> subject_intersect_index =
            GetIntersectionPointIndex(subject_list[query_node_index].GetPoint());

        int clip_list_intersect_start_index = FindIntersectIndex(subject_intersect_index);

        for (size_t j = 0; j < clipping_list_size; j++) {
            int query_index = (clip_list_intersect_start_index + j + 1) % clipping_list_size;
            clip_vertexes.push_back(clipping_list[query_index].GetPoint());

            std::optional<int> intersect_index = GetIntersectionPointIndex(clipping_list[query_index].GetPoint());

            if (intersect_index.has_value()) {
                clip_list_intersect_end_id = intersect_index.value();
                break;
            }
        }

        for (size_t j = 0; j < subject_list_size; j++) {
            subject_list_index += 1;
            subject_list_index %= subject_list_size;
            int query_index = (subject_list_index) % subject_list_size;
            std::optional<int> intersect_index = GetIntersectionPointIndex(subject_list[query_index].GetPoint());

            if (intersect_index.has_value() && intersect_index.value() == clip_list_intersect_end_id) {
                break;
            }
        }
    }

  public:
    PolygonClipping(std::shared_ptr<Polygon> subjectPolygon, std::shared_ptr<Polygon> clippingPolygon)
        : subjectPolygon(subjectPolygon), clippingPolygon(clippingPolygon) {}

    Polygon Produce() {
        CreateVertexList(subject_list, subjectPolygon, clippingPolygon);
        CreateVertexList(clipping_list, clippingPolygon, subjectPolygon);

        // subjectPolygon clockwise should different on clippingPolygon.
        if ((subjectPolygon->IsClockwise() ^ clippingPolygon->IsClockwise()) == 0) {
            std::reverse(clipping_list.begin(), clipping_list.end());
        }

        std::vector<Point> clip_vertexes;

        int subject_start_node = 0;

        for (size_t i = 0; i < subject_list.size(); i++) {
            Point point = subject_list[i].GetPoint();
            if (!(Between<double>(point.GetX(), clippingPolygon->GetMinX(), clippingPolygon->GetMaxX()) &&
                  Between<double>(point.GetY(), clippingPolygon->GetMinY(), clippingPolygon->GetMaxY()))) {
                subject_start_node = i;
                break;
            }
        }

        for (size_t i = subject_start_node, j = 0; j < subject_list.size(); i++, j++) {
            size_t query_node_index = (i) % (subject_list.size());
            clip_vertexes.push_back(subject_list[query_node_index].GetPoint());

            std::optional<int> subject_intersect_index =
                GetIntersectionPointIndex(subject_list[query_node_index].GetPoint());

            if (subject_intersect_index.has_value()) {
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

    void CreateVertexList(std::vector<PointWithState> &list, std::shared_ptr<Polygon> major_polygon,
                          std::shared_ptr<Polygon> minor_polygon) {
        Point first_major_point = major_polygon->GetVertexs()->at(0);
        list.push_back(PointWithState(first_major_point, major_polygon->IsPointInPolygon(first_major_point)));

        size_t major_polygon_vertex_size = major_polygon->GetVertexs()->size();
        size_t minor_polygon_vertex_size = minor_polygon->GetVertexs()->size();
        for (size_t i = 0; i < major_polygon_vertex_size; i++) {
            Point v11 = major_polygon->GetVertexs()->at((i) % major_polygon_vertex_size);
            Point v12 = major_polygon->GetVertexs()->at((i + 1) % major_polygon_vertex_size);
            Line line1(v11, v12);

            std::vector<PointWithState> intersect_points;
            std::vector<double> x_set;

            for (size_t j = 0; j < minor_polygon_vertex_size; j++) {
                Point v21 = minor_polygon->GetVertexs()->at((j) % minor_polygon_vertex_size);
                Point v22 = minor_polygon->GetVertexs()->at((j + 1) % minor_polygon_vertex_size);
                Line line2(v21, v22);

                std::optional<Point> intersect_y_ray_optional = line2.GetYRayIntersectPoint(v12.GetY());

                if (intersect_y_ray_optional.has_value()) {
                    if (std::find(x_set.begin(), x_set.end(), intersect_y_ray_optional->GetX()) == x_set.end()) {
                        x_set.push_back(intersect_y_ray_optional->GetX());
                    }
                    if ((std::find(x_set.begin(), x_set.end(), intersect_y_ray_optional->GetX()) != x_set.end()) &&
                        minor_polygon->IsLocalMinMaxPoint(intersect_y_ray_optional.value())) {
                        x_set.push_back(intersect_y_ray_optional->GetX());
                    }
                }

                std::optional<Point> intersect_point_optional = line1.GetIntersectPoint(line2);

                if (intersect_point_optional.has_value()) {
                    Point intersect_point = intersect_point_optional.value();
                    intersect_points.push_back(PointWithState(intersect_point, true));
                    if (point_to_intersection_index.find(intersect_point) == point_to_intersection_index.end()) {
                        point_to_intersection_index[intersect_point] = point_to_intersection_index.size();
                    }
                }
            }

            std::sort(intersect_points.begin(), intersect_points.end(),
                      [v11](const PointWithState &a, const PointWithState &b) {
                          return GetDistance(v11, a.GetPoint()) < GetDistance(v11, b.GetPoint());
                      });

            for (PointWithState p : intersect_points) {
                list.push_back(p);
            }

            if (i != major_polygon_vertex_size - 1) {
                bool in_polygon = DeterminePointInPolygonByXSet(x_set, v12.GetX());
                list.push_back(PointWithState(v12, in_polygon));
            }
        }
    }
};

#endif