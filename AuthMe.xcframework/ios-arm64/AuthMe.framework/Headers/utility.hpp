#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <numeric>
#include <algorithm>
#include "engine_type.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

template<typename T> inline std::unique_ptr<T> MakeUnique(T* ptr)
{
    return std::unique_ptr<T>(ptr);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vecValue)
{
    if (vecValue.size() > 0)
    {
        auto it = vecValue.begin();
        os << "[" << *it++;
        for (; it != vecValue.end(); it++)
        {
            os << ", " << *it;
        }
        os << "]";
    }
    return os;
}

template <typename T>
T MultAll(const std::vector<T> &vecNum)
{
    T val = 1;
    for (auto &n : vecNum)
    {
        val *= n;
    }
    return val;
}

template <typename T, typename P>
std::vector<T> Convert(const std::vector<P>& vecSrc)
{
    std::vector<T> vecDst(vecSrc.size());
    for (size_t i = 0; i < vecSrc.size(); i++)
    {
        vecDst[i] = T(vecSrc[i]);
    }

    return vecDst;
}

/// return a vector of index which ( vecValue[index[0]] < vecValue[index[1]] < ... )
/// type T must have operator "<"
template <typename T>
std::vector<int> SortIndex(const std::vector<T>& vecValue)
{
    std::vector<int> vecIndex(vecValue.size());
    std::iota(vecIndex.begin(), vecIndex.end(), 0);
    std::sort(vecIndex.begin(), vecIndex.end(), [&](int i, int j)
    {
        return vecValue[i] < vecValue[j];
    });

    return vecIndex;
}

template <typename T>
void CominationLoop(std::vector<std::vector<T>>& vecConbimations,
                    const std::vector<T>& vecElements,
                    std::vector<T>& vecOutput,
                    size_t N, int iIdx, int iIdxBeg)
{
    if (N == 0)
    {
        vecConbimations.push_back(vecOutput);
        return;
    }

    for (size_t i = iIdxBeg; i <= vecElements.size() - N; i++)
    {
        vecOutput[iIdx] = vecElements[i];
        CominationLoop(vecConbimations, vecElements, vecOutput, N - 1, iIdx + 1, i + 1);
    }
}

/// retrun all combination of choosing N element from vecElement
/// ex: vecElements = { a, b, c, d}, N = 2
/// return = { {a, b}, {a, c}, {a, d}, {b, c}, {b, d}, {c, d} }
template <typename T>
std::vector<std::vector<T>> GenCombinations(const std::vector<T>& vecElements, size_t N)
{
    std::vector<std::vector<T>> vecConbimations;

    if (vecElements.size() >= N)
    {
        std::vector<T> vecBuffer(N);
        CominationLoop(vecConbimations, vecElements, vecBuffer, N, 0, 0);
    }

    return vecConbimations;
}

template<typename T>
void ExtractTopK(std::vector<T>& vecIndex, size_t K)
{
    if (vecIndex.size() > (K))
    {
        vecIndex = std::vector<T>(vecIndex.begin(), vecIndex.begin() + K);
    }
}

template<typename T>
class CMovingAverage
{
    public:
        void SetMaxLength(size_t uiMaxLength);
        size_t GetCurrentLength();
        bool ReachMaxLength();
        T Update(T value);
        void Clear();

    private:
        std::vector<T> m_vecValue;
        size_t m_uiMaxLength = 0;
        int m_iLastElementIdx = 0;
        T m_sum = T(0);
};

template<typename T>
void CMovingAverage<T>::SetMaxLength(size_t uiMaxLength)
{
    m_sum = T(0);
    m_uiMaxLength = uiMaxLength;
    m_vecValue.clear();
    m_vecValue.reserve(m_uiMaxLength);
}

template<typename T>
size_t CMovingAverage<T>::GetCurrentLength()
{
    return m_vecValue.size();
}

template<typename T>
bool CMovingAverage<T>::ReachMaxLength()
{
    return m_vecValue.size() == m_uiMaxLength;
}

template<typename T>
T CMovingAverage<T>::Update(T value)
{
    m_sum += value;

    if (m_vecValue.size() < m_uiMaxLength)
    {
        m_vecValue.push_back(value);
    }
    else
    {
        m_sum -= m_vecValue[m_iLastElementIdx];
        m_vecValue[m_iLastElementIdx] = value;
        m_iLastElementIdx = (m_iLastElementIdx + 1) % m_vecValue.size();
    }

    return m_sum / static_cast<T>(m_vecValue.size());
}

template<typename T>
void CMovingAverage<T>::Clear()
{
    SetMaxLength(m_uiMaxLength);
}

template<typename T>
std::vector<T> ReadValues(const std::string& strFilePath)
{
    std::ifstream fs;
    fs.open(strFilePath, std::ios::in);
    if (!fs.is_open())
    {
        return std::vector<T>();
    }

    T value;
    std::vector<T> vecValues;
    while (fs >> value)
    {
        vecValues.push_back(value);
    }

    return vecValues;
}

template<typename T>
T LinearInterpolation(const std::vector<T>& vecSrc, const std::vector<T>& vecDst, const T value)
{
    if (vecSrc.size() != vecDst.size())
    {
        return std::numeric_limits<T>::min();
    }

    auto it = std::lower_bound(vecSrc.begin(), vecSrc.end(), value);
    size_t idx = std::distance(vecSrc.begin(), it);

    if (idx == 0)
    {
        idx = 1;
    }
    else if (idx == vecSrc.size())
    {
        idx -= 1;
    }

    return ((value - vecSrc[idx - 1]) * vecDst[idx] + (vecSrc[idx] - value) * vecDst[idx - 1]) / (vecSrc[idx] - vecSrc[idx - 1]);
}

template <class T>
cv::Mat WarpPerspective(const cv::Mat& image, const std::vector<cv::Point_<T>>& vecVertices, const cv::Size targetSize)
{
    const std::vector<cv::Point2f> vecRefPoints =
    {
        {0.0f, 0.0f},
        {static_cast<float>(targetSize.width - 1), 0.0f},
        {static_cast<float>(targetSize.width - 1), static_cast<float>(targetSize.height - 1)},
        {0.0f, static_cast<float>(targetSize.height - 1)}
    };

    cv::Mat matTmp;
    cv::Mat matrix = cv::getPerspectiveTransform(Convert<cv::Point2f>(vecVertices), vecRefPoints);
    cv::warpPerspective(image, matTmp, matrix, targetSize);

    return matTmp;
}

template<typename T>
T Sum(const std::vector<T>& vecValue)
{
    T sum = T();
    for (auto v : vecValue)
    {
        sum += v;
    }

    return sum;
}

std::string GetExtension(const std::string& strPath);

std::string ReplaceExtension(const std::string& strPath, const std::string& strExtension);

std::vector<std::string> Split(const std::string& str, const std::string& delim);

size_t FileSize(const std::string& strFilePath);

bool IsFileExist(const std::string& strFilePath);

std::vector<unsigned char> ReadFile(const std::string& strFilePath);

AuthMe::EEngineFrameworkType GetFrameworkByFileName(const std::string& strModelPath);

std::string GetTestKey();

std::string GetTestToken();

cv::Mat GetImage(int offset, std::size_t size, int width, int height);