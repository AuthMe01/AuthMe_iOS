//
//  EngineWrapper.hpp
//  IOSTestModel
//
//  Created by Leon Lee on 2021/10/14.
//

#ifndef EngineWrapper_hpp
#define EngineWrapper_hpp

#ifdef __cplusplus
extern "C" {
#endif

#import <UIKit/UIKit.h>

long engine_initModel(const char *path);

void engine_releaseModel(long model_);

long engine_createSession(long model_);

void engine_releaseSession(long model_, long session_);

float engine_laserTagDetection(long model_, long session_, UIImage* image);

void getTransformedLeftPoint(float w,
                             float h,
                             float degree,
                             float *x,
                             float *y);

void getTransformedTopPoint(float w,
                            float h,
                            float degree,
                            float *x,
                            float *y);

float mse(float *squaredDistances, int count);

#ifdef __cplusplus
}
#endif


#endif /* EngineWrapper_hpp */
