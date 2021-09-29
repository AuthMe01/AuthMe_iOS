//
//  CardProcessFunction.h
//  AuthMeSDK
//
//  Created by Leon Lee on 2020/10/30.
//  Copyright © 2020 Leon Lee. All rights reserved.
//

#ifndef CardProcessFunction_h
#define CardProcessFunction_h

#import <UIKit/UIKit.h>

@interface ImageConverter : NSObject
+(UIImage *)resizeImage:(UIImage *)image toW:(int)w toH:(int)h;
+(UIImage *)resizeImageWithPadding:(UIImage *)image toSize:(int)size;
+(UIImage *)cvtToHsv:(UIImage *)image to:(int) size;
+(UIImage *)cvtToYCrCb:(UIImage *)image to:(int) size;
+(double)calcReflective:(UIImage *)image;
+(double)calcSharpness:(UIImage *)image;
+(UIImage *)calibImage:(UIImage *)image x1:(int)x1 y1:(int)y1 x2:(int)x2 y2:(int)y2 x3:(int)x3 y3:(int)y3 x4:(int)x4 y4:(int)y4 width:(int)width height:(int)height;
+(UIImage *)detectBox:(float *)data image:(UIImage *)image outWidth:(int *)width;
@end


#endif /* CardProcessFunction_h */
