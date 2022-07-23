#pragma once
#include <string>
#include <memory>
#include "opencv2/core.hpp"

namespace AuthMe
{

const int IDX_X1 = 0;
const int IDX_Y1 = 1;
const int IDX_X2 = 2;
const int IDX_Y2 = 3;
const int IDX_CENTER_X = 0;
const int IDX_CENTER_Y = 1;
const int IDX_WIDTH = 2;
const int IDX_HEIGHT = 3;

typedef struct T_ANCHOR_BOX
{
    cv::Point2f center;
    cv::Size2f size;
    float stride;
} TAnchorBox;

}