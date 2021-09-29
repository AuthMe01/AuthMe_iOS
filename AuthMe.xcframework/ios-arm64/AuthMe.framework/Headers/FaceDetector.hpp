//
//  FaceDetector.h
//  AuthMeSDK
//
//  Created by Leon Lee on 2020/12/10.
//  Copyright © 2020 Leon Lee. All rights reserved.
//

#ifndef FaceDetector_h
#define FaceDetector_h

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

void initFaceDetector(const char *path);
const int* detectFace(const unsigned char *imageBytes);

#ifdef __cplusplus
}
#endif

#endif /* FaceDetector_h */
