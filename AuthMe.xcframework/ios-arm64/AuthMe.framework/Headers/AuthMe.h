//
//  AuthMe.h
//  AuthMe
//
//  Created by Mikimoto on 2021/8/21.
//

#import <Foundation/Foundation.h>

//! Project version number for AuthMe.
FOUNDATION_EXPORT double AuthMeVersionNumber;

//! Project version string for AuthMe.
FOUNDATION_EXPORT const unsigned char AuthMeVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <AuthMe/PublicHeader.h>

#include "FaceDetector.hpp"
#include "ImageConverter.h"
#include "MNNModel.hpp"

#include "EngineWrapper.h"

#import "MoicaFuncion.h"
#import "pkcs11.h"

#import "laser_tag_detection.h"
#import "taiwan_hole_detection.h"
#import "engine_base.h"
#import "engine_type.h"
#import "face_detection.h"
#import "face_anti_spoofing.h"
#import "image_assessment.h"
//#include "engine.hpp"
