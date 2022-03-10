#pragma once
#include "engine_type_v3.h"
#include "opencv2/core.hpp"
#include <vector>

namespace AuthMe
{

class CardMatch
{
    public:
        // input points in normalized coordinate
        static std::vector<EAuthMeCardMatchStatus> PointMatch(const std::vector<cv::Point2f>&vecPointsN1,
                const std::vector<cv::Point2f>& vecPointsN2,
                const cv::Size imageSize,
                float fThreshold);

        // input points in normalized coordinate, clockwise or counterclockwise
        static EAuthMeCardMatchStatus DIOUMatch(const std::vector<cv::Point2f>&vecPointsN1,
                                                const std::vector<cv::Point2f>& vecPointsN2,
                                                const cv::Size imageSize,
                                                float fThreshold);
};

}
