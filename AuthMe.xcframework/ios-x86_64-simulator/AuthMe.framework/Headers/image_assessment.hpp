#pragma once
#include "opencv2/core.hpp"
#include "engine_type.hpp"

namespace AuthMe
{

cv::Mat ImageAdjust(const cv::Mat& imageGray, const std::pair<int, int> outputRange = {0, 255}, const double dGamma = 1.0);

float ImageSharpness(const cv::Mat& image, const cv::Size size = cv::Size(256, 256), bool bAdjust = true);

float ImageReflective(const cv::Mat& image, cv::Mat *pDebugImage = nullptr);

float CheckIDCardFrontColor(const cv::Mat& image);

float CheckIDCardFrontColor(const cv::Mat& image, const std::vector<cv::Point>& vecPolygon);

EIDCardMetalTagStatus IDCardMetalTagDetect(const cv::Mat& image, const std::vector<cv::Point>& vecVertices, std::vector<cv::Point> *pvecTagLine = nullptr, cv::Mat *pDebugImage = nullptr);

}
