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

template<typename T> inline std::unique_ptr<T> MakeUnique(T* ptr)
{
    return std::unique_ptr<T>(ptr);
}

std::string GetExtension(const std::string& strPath);

std::string ReplaceExtension(const std::string& strPath, const std::string& strExtension);

std::vector<std::string> Split(const std::string& str, const std::string& delim);

size_t FileSize(const std::string& strFilePath);

bool IsFileExist(const char* szFilePath);

bool IsFileExist(const std::string& strFilePath);

std::vector<unsigned char> ReadFile(const std::string& strFilePath);

void SaveFile(const std::string& strOutputPath, std::vector<unsigned char> buffer);

AuthMe::EEngineFrameworkType GetFrameworkByFileName(const std::string& strModelPath);

std::string GetTestKey();

std::string GetTestToken();

int GetAnswer(const std::string& strTestImagePath);

std::vector<int> GetValues(const std::string& strTestImagePath);

std::vector<cv::Point> GetVertice(const std::string& strTestImagePath);

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

std::vector<cv::Point> GetPolygon(const cv::Mat& image);

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

cv::Mat GetImage(int offset, std::size_t size, int width, int height);


