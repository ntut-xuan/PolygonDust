#ifndef POLYGON_CLIPPING_HPP
#define POLYGON_CLIPPING_HPP

#include "line.hpp"
#include "point.hpp"
#include "polygon.hpp"
#include "shared.hpp"
#include "vectorization_result.hpp"
#include <algorithm>
#include <cstddef>
#include <iomanip>
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
    std::map<Point, bool> is_point_used;
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
            is_point_used[clipping_list[query_index].GetPoint()] = true;
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

    std::vector<Point> GetIntersectPoints() {
        std::vector<Point> points;
        for (auto intersect_point_pair : point_to_intersection_index) {
            points.push_back(intersect_point_pair.first);
        }
        return points;
    }

  public:
    PolygonClipping(std::shared_ptr<Polygon> subjectPolygon, std::shared_ptr<Polygon> clippingPolygon)
        : subjectPolygon(subjectPolygon), clippingPolygon(clippingPolygon) {}

    VectorizationResult Produce() {
        CreateVertexList(subject_list, subjectPolygon, clippingPolygon);
        CreateVertexList(clipping_list, clippingPolygon, subjectPolygon);

        // subjectPolygon clockwise should different on clippingPolygon.
        if ((subjectPolygon->IsClockwise() ^ clippingPolygon->IsClockwise()) == 0) {
            std::reverse(clipping_list.begin(), clipping_list.end());
        }

        std::vector<Polygon> polygons;
        std::vector<Point> startPoint;

        while (true) {
            int subject_start_node = -1;

            for (size_t i = 0; i < subject_list.size(); i++) {
                if (is_point_used[subject_list.at(i).GetPoint()] == false && !subject_list.at(i).IsInPolygon()) {
                    subject_start_node = i;
                    break;
                }
            }

            if (subject_start_node == -1) {
                break;
            }

            std::vector<Point> clip_vertexes;

            for (size_t i = subject_start_node, j = 0; j < subject_list.size(); i++, j++) {
                size_t query_node_index = (i) % (subject_list.size());
                Point point = subject_list[query_node_index].GetPoint();

                if (clip_vertexes.size() != 0 && point == subject_list[subject_start_node].GetPoint()) {
                    break;
                }

                is_point_used[point] = true;
                clip_vertexes.push_back(point);

                std::optional<int> subject_intersect_index = GetIntersectionPointIndex(point);

                if (subject_intersect_index.has_value()) {
                    ProcessIntersectPoint(clip_vertexes, i);
                }
            }

            polygons.push_back(Polygon(clip_vertexes));
        }

        return VectorizationResult(polygons, startPoint);
    }

    void CreateVertexList(std::vector<PointWithState> &list, std::shared_ptr<Polygon> major_polygon,
                          std::shared_ptr<Polygon> minor_polygon) {
        Point first_major_point = major_polygon->GetVertexs()->at(0);
        list.push_back(PointWithState(first_major_point, minor_polygon->IsPointInPolygon(first_major_point)));

        size_t major_polygon_vertex_size = major_polygon->GetVertexs()->size();
        size_t minor_polygon_vertex_size = minor_polygon->GetVertexs()->size();
        for (size_t i = 0; i < major_polygon_vertex_size; i++) {
            Point v11 = major_polygon->GetVertexs()->at((i) % major_polygon_vertex_size);
            Point v12 = major_polygon->GetVertexs()->at((i + 1) % major_polygon_vertex_size);
            Line line1(v11, v12);

            std::vector<PointWithState> intersect_points;
            std::set<double> x_set;

            for (size_t j = 0; j < minor_polygon_vertex_size; j++) {
                Point v21 = minor_polygon->GetVertexs()->at((j) % minor_polygon_vertex_size);
                Point v22 = minor_polygon->GetVertexs()->at((j + 1) % minor_polygon_vertex_size);
                Line line2(v21, v22);

                std::optional<Point> intersect_y_ray_optional = line2.GetYRayIntersectPoint(v12.GetY());

                if (intersect_y_ray_optional.has_value()) {
                    if (x_set.find(intersect_y_ray_optional->GetX()) == x_set.end()) {
                        x_set.insert(intersect_y_ray_optional->GetX());
                    }
                }

                std::optional<std::vector<Point>> intersect_point_optional = line1.GetIntersectPoint(line2);

                if (intersect_point_optional.has_value()) {
                    for (Point intersect_point : intersect_point_optional.value()) {
                        if (std::find(intersect_points.begin(), intersect_points.end(),
                                      PointWithState(intersect_point, true)) == intersect_points.end()) {
                            intersect_points.push_back(PointWithState(intersect_point, true));
                        }
                        if (point_to_intersection_index.find(intersect_point) == point_to_intersection_index.end()) {
                            point_to_intersection_index[intersect_point] = point_to_intersection_index.size();
                        }
                    }
                }
            }

            std::sort(intersect_points.begin(), intersect_points.end(),
                      [v11](const PointWithState &a, const PointWithState &b) {
                          return GetDistance(v11, a.GetPoint()) < GetDistance(v11, b.GetPoint());
                      });

            for (PointWithState p : intersect_points) {
                if (std::find(list.begin(), list.end(), p) == list.end()) {
                    list.push_back(p);
                }
            }

            if (i != major_polygon_vertex_size - 1) {

                std::vector<double> x_vec = std::vector<double>(x_set.begin(), x_set.end());

                x_vec = minor_polygon->localminmax_x_set_optimization(x_vec, v12.GetY());

                bool in_polygon = DeterminePointInPolygonByXSet(x_vec, v12.GetX());
                if (std::find(list.begin(), list.end(), PointWithState(v12, true)) == list.end()) {
                    list.push_back(PointWithState(v12, in_polygon));
                }
            }
        }
    }
};

#endif