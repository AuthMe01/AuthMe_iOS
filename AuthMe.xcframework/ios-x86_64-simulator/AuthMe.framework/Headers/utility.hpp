#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <tuple>
#include "engine_type.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

template<typename T, size_t size>
std::size_t ArraySize(T(&)[size])
{
    return size;
}

template<typename T>
bool ContentEquals(const T& a, const T& b)
{
    return a == b;
}

template<typename T, size_t size>
bool ContentEquals(const T(&A)[size], const T(&B)[size])
{
    for (size_t i = 0 ; i < size; i++)
    {
        if (!ContentEquals(A[i], B[i]))
        {
            return false;
        }
    }

    return true;
}

template<typename T> inline std::unique_ptr<T> MakeUnique(T* ptr)
{
    return std::unique_ptr<T>(ptr);
}

template <typename K, typename T>
std::ostream &operator<<(std::ostream &os, const std::pair<K, T> &pair)
{
    os << "[" << pair.first << ", " << pair.second << "]";
    return os;
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

template <typename K, typename T>
std::ostream &operator<<(std::ostream &os, const std::map<K, T> &map)
{
    for (auto it = map.begin(); it != map.end(); it++)
    {
        os << "'" << it->first << "': '" << it->second << "'" << std::endl;
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

template <typename T, typename K>
void Reorder(std::vector<T>& vecValue, const std::vector<K>& vecIndex)
{
    if constexpr(std::is_integral<K>::value)
    {
        std::vector<T> vecTmp(vecIndex.size());
        for (size_t i = 0; i < vecIndex.size(); i++)
        {
            vecTmp[i] = vecValue[vecIndex[i]];
        }

        vecValue = vecTmp;
    }
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
class CMovingWindow
{
    public:
        void SetMaxLength(size_t uiMaxLength);
        size_t GetMaxLength() const;
        size_t GetCurrentLength() const;
        bool ReachMaxLength() const;
        void Update(T value);
        T Last() const;
        T Mean() const;
        T Variance() const;
        T Stddev() const;
        void Clear();

    private:
        std::vector<T> m_vecValue;
        size_t m_uiMaxLength = 0;
        int m_iLastElementIdx = 0;
        T m_sum = T(0);
};

template<typename T>
void CMovingWindow<T>::SetMaxLength(size_t uiMaxLength)
{
    m_sum = T(0);
    m_uiMaxLength = uiMaxLength;
    m_vecValue.clear();
    m_vecValue.reserve(m_uiMaxLength);
}

template<typename T>
size_t CMovingWindow<T>::GetMaxLength() const
{
    return m_uiMaxLength;
}

template<typename T>
size_t CMovingWindow<T>::GetCurrentLength() const
{
    return m_vecValue.size();
}

template<typename T>
bool CMovingWindow<T>::ReachMaxLength() const
{
    return m_vecValue.size() == m_uiMaxLength;
}

template<typename T>
void CMovingWindow<T>::Update(T value)
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
}

template<typename T>
T CMovingWindow<T>::Last() const
{
    if (m_vecValue.size() != 0)
    {
        return m_vecValue.back();
    }

    return T();
}

template<typename T>
T CMovingWindow<T>::Mean() const
{
    return m_sum / static_cast<T>(m_vecValue.size());
}

template<typename T>
T CMovingWindow<T>::Variance() const
{
    if (m_vecValue.size() == 0)
    {
        return T();
    }

    auto mean = Mean();
    auto sumSqrDiff = T();
    for (auto value : m_vecValue)
    {
        sumSqrDiff += (value - mean) * (value - mean);
    }

    return sumSqrDiff / static_cast<T>(m_vecValue.size());
}


template<typename T>
T CMovingWindow<T>::Stddev() const
{
    if (m_vecValue.size() == 0)
    {
        return T();
    }

    return static_cast<T>(std::sqrt(Variance()));
}

template<typename T>
void CMovingWindow<T>::Clear()
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
T LinearInterpolation(const std::vector<T>& vecSrc, const std::vector<T>& vecDst, const T value, bool bClip = true)
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

    T interpValue = ((value - vecSrc[idx - 1]) * vecDst[idx] + (vecSrc[idx] - value) * vecDst[idx - 1]) / (vecSrc[idx] - vecSrc[idx - 1]);

    if (bClip)
    {
        interpValue = std::min(interpValue, vecDst.back());
        interpValue = std::max(interpValue, vecDst.front());
    }

    return interpValue;
}

template<typename T>
std::vector<cv::Point_<T>> GetBoundPolygon(cv::Size targetSize)
{
    const std::vector<cv::Point_<T>> vecRefPoints =
    {
        {T(0), T(0)},
        {static_cast<T>(targetSize.width - 1), T(0)},
        {static_cast<T>(targetSize.width - 1), static_cast<T>(targetSize.height - 1)},
        {T(0), static_cast<T>(targetSize.height - 1)}
    };

    return vecRefPoints;
}

// return [warppedimage, matrix]
template <class T>
std::pair<cv::Mat, cv::Mat> WarpPerspectiveWithMatrix(const cv::Mat& image, const std::vector<cv::Point_<T>>& vecVertices, const cv::Size targetSize)
{
    auto vecRefPoints = GetBoundPolygon<float>(targetSize);

    cv::Mat matTmp;
    cv::Mat matrix = cv::getPerspectiveTransform(Convert<cv::Point2f>(vecVertices), vecRefPoints);
    cv::warpPerspective(image, matTmp, matrix, targetSize);

    return {matTmp, matrix};
}

// return warppedimage
template <class T>
cv::Mat WarpPerspective(const cv::Mat& image, const std::vector<cv::Point_<T>>& vecVertices, const cv::Size targetSize)
{
    cv::Mat warppedImage;
    std::tie(warppedImage, std::ignore) = WarpPerspectiveWithMatrix(image, vecVertices, targetSize);
    return warppedImage;
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

template<typename T>
T Clip(const T& value, const T& minValue, const T& maxValue)
{
    return std::max(std::min(value, maxValue), minValue);
}

// remove duplicates form a sorted vector
template<typename T>
void RemoveDuplicates(std::vector<T>& vecValue)
{
    if (vecValue.size() < 2)
    {
        return;
    }

    auto p = vecValue[0];
    int idx = 0;
    for (size_t i = 1; i < vecValue.size(); i++)
    {
        if (vecValue[i] != vecValue[idx])
        {
            vecValue[++idx] = vecValue[i];
        }
    }

    vecValue.resize(idx + 1);
}

std::string GetExtension(const std::string& strPath);

std::string ReplaceExtension(const std::string& strPath, const std::string& strExtension);

std::vector<std::string> Split(const std::string& str, const std::string& delim);

size_t FileSize(const std::string& strFilePath);

bool IsFileExist(const char* szFilePath);

bool IsFileExist(const std::string& strFilePath);

std::vector<unsigned char> ReadFile(const std::string& strFilePath);

AuthMe::EEngineFrameworkType GetFrameworkByFileName(const std::string& strModelPath);

std::string GetTestKey();

std::string GetTestToken();

cv::Mat GetImage(int offset, std::size_t size, int width, int height);