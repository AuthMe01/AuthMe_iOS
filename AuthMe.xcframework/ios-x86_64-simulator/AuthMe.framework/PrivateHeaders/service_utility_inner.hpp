#pragma once
#include "engine_service_type.h"
#include "utility.hpp"
#include "utility_format_adapter.hpp"
#include <memory>


namespace AuthMe
{

#ifdef __clang__
#define INIT_CHAR_ARRAY(buffer, str) buffer = str
#else
#define INIT_CHAR_ARRAY(buffer, str) {buffer = str}
#endif

bool operator == (const cv::Size& cvSize, const AuthMeSize& aSize);
bool operator != (const cv::Size& cvSize, const AuthMeSize& aSize);
bool operator == (const AuthMeSize& aSize, const cv::Size& cvSize);
bool operator != (const AuthMeSize& aSize, const cv::Size& cvSize);

}