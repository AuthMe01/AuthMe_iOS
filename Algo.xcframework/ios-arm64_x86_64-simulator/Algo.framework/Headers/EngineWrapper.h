
#ifndef EngineWrapper_hpp
#define EngineWrapper_hpp

#ifdef __cplusplus
extern "C" {
#endif

#import <UIKit/UIKit.h>
#import "engine_type.h"
#import "authme_ml_engine_type.h"

//UIImage* convertAuthMeImage(AuthMeImage *image);
//UIImage* convertAuthmeDebugImage(AuthMeImage *image);
UIImage* convertAuthmeImg_3ch(AuthmeImg *image);
UIImage* convertAuthmeImg_4ch(AuthmeImg *image);

#ifdef __cplusplus
}
#endif


#endif /* EngineWrapper_hpp */
