#pragma once
#include "v3/engine_type_v3.h"
#include "utility.hpp"
#include <memory>


namespace AuthMe
{

template<class T>
std::unique_ptr<T> InitialModel(const AuthMeModelInitInfo& tInfo, T * (*Creator)())
{
    auto pModel = MakeUnique(Creator());
    if (pModel == nullptr)
    {
        return nullptr;
    }

    bool bSuccess = false;
    if (IsFileExist(tInfo.szPath))
    {
        bSuccess = pModel->Initial(tInfo.szPath);
    }

    if (!bSuccess)
    {
        bSuccess = pModel->Initial(tInfo.buffer.pData, tInfo.buffer.iSize);
    }

    if (bSuccess)
    {
        return pModel;
    }

    return nullptr;
}

bool operator == (const cv::Size& cvSize, const AuthMeSize& aSize);
bool operator != (const cv::Size& cvSize, const AuthMeSize& aSize);
bool operator == (const AuthMeSize& aSize, const cv::Size& cvSize);
bool operator != (const AuthMeSize& aSize, const cv::Size& cvSize);
}