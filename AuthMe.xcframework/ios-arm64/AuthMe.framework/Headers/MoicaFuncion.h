//
//  MoicaFuncion.h
//  NFCMOICA
//
//  Created by Leon Lee on 2021/7/6.
//

#ifndef MoicaFuncion_h
#define MoicaFuncion_h

#ifdef __cplusplus
extern "C" {
#endif

unsigned long nativeCardSN(char *cardNumber);

unsigned long nativeSignData(const char *pin,
                    const unsigned char *data,
                    int dataLen,
                    unsigned char* signature,
                    int* signatureLen,
                    const int algorithm,
                    const int type,
                    unsigned long *apduCounter);

unsigned long nativeGetCertificate(char *notBefore,
                                   char *notAfter,
                                   char *issuer,
                                   char *subject);

unsigned long nativeFinalize();
//void test();

#ifdef __cplusplus
}
#endif

#endif
