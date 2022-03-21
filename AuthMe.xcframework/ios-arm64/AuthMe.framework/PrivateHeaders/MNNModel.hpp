//
//  Liveness.hpp
//  MNNTest-iOS
//
//  Created by Leon Lee on 2020/10/23.
//

#ifndef MNNModel_hpp
#define MNNModel_hpp

#ifdef __cplusplus
extern "C" {
#endif

//typedef struct LivenessEncodeData{
//    float data[64];
//} LivenessEncodeData;
//
//
//typedef struct CardEncodeData{
//    float data[1024];
//} CardEncodeData;


typedef struct LandmarkResult{
    float* eyes;
    float* params;
    float mouth;
} LandmarkResult;

void initLocalLiveness(const char *path);
float processLocalLiveness(const unsigned char* image, int inputSize);

void initEncodeLiveness(const char *path);
const float * processEncodeLiveness(const unsigned char* image1, const unsigned char* image2, int inputSize);

void initEncodeCardDetection(const char *path);
const float *processEncodeCardDetection(const unsigned char* image, int w, int h);

void initCardClassifier(const char *path);
const float processCardClassifier(const unsigned char* image, int w, int h);

void initLandmarkModel(const char *path);
LandmarkResult processLandmark(const unsigned char* image, int w, int h);

void initEyeBlinkModel(const char *path);
const int processEyeBlink(const unsigned char* image, int w, int h);

void initMaskModel(const char *path);
const int processIsWearMask(const unsigned char* image, int w, int h);

void initMrzModel(const char *path);
float* processMrzModel(const unsigned char* image, int w, int h);

void initMrzRegModel(const char *path);
unsigned char* processMrzRegModel(const unsigned char* image, int w, int h);

#ifdef __cplusplus
}
#endif

#endif /* Liveness_hpp */
