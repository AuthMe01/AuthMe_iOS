#pragma once
#include "opencv2/core.hpp"
#include <numeric>

namespace AuthMe
{

typedef enum E_POINT_CONVEX_POLYGON_RELATION
{
    eRelation_None,
    eRelation_PointOutside,
    eRelation_PointOnEdge,
    eRelation_PointInside
} EPointConvexPolygonRelation;

template<typename T>
double ConvexPolygonArea(const std::vector<cv::Point_<T>>& vecPolygon);

template<typename T>
cv::Point_<T> PolygonCenter(const std::vector<cv::Point_<T>>& vecPolygon)
{
    cv::Point_<T> sum;
    for (auto&p : vecPolygon)
    {
        sum += p;
    }

    return sum / static_cast<T>(vecPolygon.size());
}

template<typename T> bool IsZero(T val)
{
    if (std::is_integral<T>::value)
    {
        return val == 0;
    }
    else
    {
        return std::abs(val) <= std::numeric_limits<T>::epsilon();
    }
}

template<typename T>
T Distance(const cv::Point_<T>& a, const cv::Point_<T>& b)
{
    return cv::norm(b - a);
}

template<typename T>
cv::Point_<T> GetLineIntersection(const cv::Point_<T>& a1, const cv::Point_<T>& a2, const cv::Point_<T>& b1, const cv::Point_<T>& b2)
{
    auto a = a2 - a1;
    auto b = b2 - b1;

    auto n = a.cross(b);

    if (IsZero(n))
    {
        return cv::Point_<T>();
    }
    return a1 + a * (b1 - a1).cross(b) / n;
}

template<typename T>
cv::Point_<T> GetLineIntersection(const std::pair<cv::Point_<T>, cv::Point_<T>>& edge1, const std::pair<cv::Point_<T>, cv::Point_<T>>& edge2)
{
    return GetLineIntersection(edge1.first, edge1.second, edge2.first, edge2.second);
}

template<typename T>
bool HasIntersection(const cv::Point_<T>& a1, const cv::Point_<T>& a2, const cv::Point_<T>& b1, const cv::Point_<T>& b2)
{
    auto a = a2 - a1;
    auto b = b2 - b1;

    auto n = a.cross(b);
    return !IsZero(n);
}

template<typename T>
bool HasIntersection(const std::pair<cv::Point_<T>, cv::Point_<T>>& edge1, const std::pair<cv::Point_<T>, cv::Point_<T>>& edge2)
{
    return HasIntersection(edge1.first, edge1.second, edge2.first, edge2.second);
}

// return true if segment has exact one intersection
template<typename T>
bool HasSegmentIntersection(const cv::Point_<T>& a1, const cv::Point_<T>& a2, const cv::Point_<T>& b1, const cv::Point_<T>& b2);

template<typename T>
cv::Point_<T> SegmentIntersection(const cv::Point_<T>& a1, const cv::Point_<T>& a2, const cv::Point_<T>& b1, const cv::Point_<T>& b2);

template<typename T>
EPointConvexPolygonRelation GetPointConvexPolygonRelation(const std::vector<cv::Point_<T>>& vecVertices, const cv::Point_<T>& p);

template<typename T>
std::vector<cv::Point_<T>> ConvexPolygonIntersection(const std::vector<cv::Point_<T>>& polygonA, const std::vector<cv::Point_<T>>& polygonB);

template<typename T>
float CalcDIOU(const std::vector<cv::Point_<T>>& polygonA, const std::vector<cv::Point_<T>>& polygonB);

template<typename T>
cv::Point_<T> ProjectPoint(const cv::Point_<T>& p, const cv::Point_<T>& a1, const cv::Point_<T>& a2)
{
    auto a = a2 - a1;

    T n = cv::norm(a);
    if (IsZero(n))
    {
        return cv::Point_<T>();
    }

    a /= n;
    return  a1 + a * a.dot(p - a1);
}

template<typename T>
cv::Point_<T> ProjectPoint(const cv::Point_<T>& p, const std::pair<cv::Point_<T>, cv::Point_<T>>& edge)
{
    return ProjectPoint(p, edge.first, edge.second);
}


template<typename T>
cv::Point_<T> GetCenter(const std::vector<cv::Point_<T>>vecVertices)
{
    cv::Point_<T> center;
    for (auto& p : vecVertices)
    {
        center += p;
    }

    return center / static_cast<T>(vecVertices.size());
}

template<typename T>
std::vector<cv::Point_<T>> ScaleConvexShape(const std::vector<cv::Point_<T>>& vecVertices, T distance)
{
    if (vecVertices.size() < 3)
    {
        return vecVertices;
    }

    std::vector<std::pair<cv::Point_<T>, cv::Point_<T>>> vecEdges;
    vecEdges.reserve(vecVertices.size());

    for (size_t i = 0; i < vecVertices.size(); i++)
    {
        vecEdges.push_back({vecVertices[i], vecVertices[(i + 1) % vecVertices.size()]});
    }

    auto center = GetCenter(vecVertices);
    for (auto& edge : vecEdges)
    {
        auto p = ProjectPoint(center, edge);
        auto v = p - center;
        v = v * distance / cv::norm(v);
        edge.first += v;
        edge.second += v;
    }

    std::vector<cv::Point_<T>> vecExtendVertices(vecVertices.size());

    auto prev = vecEdges.back();
    for (size_t i = 0; i < vecExtendVertices.size(); i++)
    {
        vecExtendVertices[i] = GetLineIntersection(prev, vecEdges[i]);
        prev = vecEdges[i];
    }

    return vecExtendVertices;
}

}