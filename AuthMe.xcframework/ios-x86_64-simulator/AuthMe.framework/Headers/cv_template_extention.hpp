#pragma once
#include "opencv2/core.hpp"

template <typename T> inline static
cv::Point_<T> operator * (const cv::Point_<T>& point, const cv::Size_<T>& scale)
{
    return cv::Point_<T>(point.x * scale.width, point.y * scale.height);
}

template <typename T> inline static
cv::Rect_<T> operator * (const cv::Rect_<T>& rect, T scale)
{
    return cv::Rect_<T>(rect.tl() * scale, rect.br() * scale);
}

template <typename T> inline static
cv::Rect_<T> operator * (const cv::Rect_<T>& rect, const cv::Size_<T>& scale)
{
    return cv::Rect_<T>(rect.tl() * scale, rect.br() * scale);
}

template <typename T> inline static
cv::Point_<T> operator + (const cv::Point_<T>& point, const cv::Size_<T>& size)
{
    return cv::Point_<T>(point.x + size.width, point.y + size.height);
}

template <typename T> inline static
cv::Point_<T> operator - (const cv::Point_<T>& point, const cv::Size_<T>& size)
{
    return cv::Point_<T>(point.x - size.width, point.y - size.height);
}

template <typename T> inline static
cv::Point_<T> operator * (const cv::Point_<T>& p, const cv::Mat& mat)
{
    auto r0 = mat.ptr<T>(0);
    auto r1 = mat.ptr<T>(1);
    return cv::Point_<T>(r0[0] * p.x + r0[1] * p.y + r0[2],
                         r1[0] * p.x + r1[1] * p.y + r1[2]);
}

template <typename T> inline static
cv::Point_<T> operator * (const cv::Mat& mat, const cv::Point_<T>& p)
{
    return p * mat;
}
template <typename T> inline static
void Scale(cv::Rect_<T>& rect, const cv::Size_<T>& scale, const cv::Point_<T> shift = cv::Point_<T>())
{
    rect = cv::Rect_<T>(rect.tl() * scale, rect.br() * scale) + shift;
}

template <typename T>
void Scale(std::vector<cv::Point_<T>>& vecPoints, T scale, T shift = T())
{
    for (auto& point : vecPoints)
    {
        point = point * scale + shift;
    }
}

template <typename T>
void Scale(std::vector<cv::Point_<T>>& vecPoints, const cv::Size_<T>& scale, const cv::Point_<T> shift = cv::Point_<T>())
{
    for (auto& point : vecPoints)
    {
        point = point * scale + shift;
    }
}

template <typename T, template<class> class cvType>
std::vector<cv::Point_<T>> operator + (const std::vector<cv::Point_<T>>& vecPoints, const cvType<T>& scale)
{
    std::vector<cv::Point_<T>> result(vecPoints.size());
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        result[i] = vecPoints[i] + scale;
    }

    return result;
}

template <typename T, template<class> class cvType>
std::vector<cv::Point_<T>> operator - (const std::vector<cv::Point_<T>>& vecPoints, const cvType<T>& scale)
{
    std::vector<cv::Point_<T>> result(vecPoints.size());
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        result[i] = vecPoints[i] - scale;
    }

    return result;
}

template <typename T, template<class> class cvType>
std::vector<cv::Point_<T>> operator * (const std::vector<cv::Point_<T>>& vecPoints, const cvType<T>& scale)
{
    std::vector<cv::Point_<T>> result(vecPoints.size());
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        result[i] = vecPoints[i] * scale;
    }

    return result;
}

template <typename T, template<class> class cvType>
std::vector<cv::Point_<T>> operator / (const std::vector<cv::Point_<T>>& vecPoints, const cvType<T>& scale)
{
    std::vector<cv::Point_<T>> result(vecPoints.size());
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        result[i] = vecPoints[i] / scale;
    }

    return result;
}

template <typename T>
std::vector<cv::Point_<T>> operator * (const std::vector<cv::Point_<T>>& vecPoints, const T scale)
{
    std::vector<cv::Point_<T>> result(vecPoints.size());
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        result[i] = vecPoints[i] * scale;
    }

    return result;
}

template <typename T>
std::vector<cv::Point_<T>> operator / (const std::vector<cv::Point_<T>>& vecPoints, const T scale)
{
    std::vector<cv::Point_<T>> result(vecPoints.size());
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        result[i] = vecPoints[i] / scale;
    }

    return result;
}

template<typename T>
std::vector<cv::Point_<T>> ToCvPoint(const T* pValue, size_t uiLength)
{
    std::vector<cv::Point_<T>> vecPoints(uiLength / 2);
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        vecPoints[i].x = pValue[i * 2];
        vecPoints[i].y = pValue[i * 2 + 1];
    }

    return vecPoints;
}

template<typename T>
std::vector<cv::Point_<T>> ToCvPoint(const std::vector<T>& vecValues)
{
    return ToCvPoint(vecValues.data(), vecValues.size());
}

template<typename T>
T* ToArray(const std::vector<cv::Point_<T>>& vecPoints)
{
    T *pArray = new T[vecPoints.size() * 2];
    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        pArray[i * 2] = vecPoints[i].x;
        pArray[i * 2 + 1] = vecPoints[i].y;
    }

    return pArray;
}

template<typename T>
std::vector<T> ToValueVector(const std::vector<cv::Point_<T>>& vecPoints)
{
    std::vector<T> vecValues(vecPoints.size() * 2);

    for (size_t i = 0; i < vecPoints.size(); i++)
    {
        vecValues[i * 2] = vecPoints[i].x;
        vecValues[i * 2 + 1] = vecPoints[i].y;
    }

    return vecValues;
}