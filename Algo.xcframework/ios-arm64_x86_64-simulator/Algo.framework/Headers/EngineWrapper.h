//
//  EngineWrapper.hpp
//  Algo
//
//  Created by Evan Wu on 2022/10/12.
//

#ifndef EngineWrapper_hpp
#define EngineWrapper_hpp

#ifdef __cplusplus
extern "C" {
#endif

#import <UIKit/UIKit.h>
#import "engine_type.h"

UIImage* convertAuthMeImage(AuthMeImage *image);
UIImage* convertAuthmeDebugImage(AuthMeImage *image);

#ifdef __cplusplus
}
#endif


#endif /* EngineWrapper_hpp */
