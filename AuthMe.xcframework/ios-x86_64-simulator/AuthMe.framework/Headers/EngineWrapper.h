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
