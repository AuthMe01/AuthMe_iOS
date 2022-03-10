#pragma once
#include "v3/engine_type_v3.h"
#include "utility.hpp"
#include <memory>


namespace AuthMe
{

template<class T> bool InitialModel(std::unique_ptr<T>& pModel, AuthMeModelInitInfo tInfo)
{
    if (pModel == nullptr)
    {
        return false;
    }

    if (IsFileExist(tInfo.szPath))
    {
        return pModel->Initial(tInfo.szPath);
    }

    return pModel->Initial(tInfo.buffer.pData, tInfo.buffer.iSize);
}

}