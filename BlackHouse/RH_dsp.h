#ifndef _RH_DSP_H
#define _RH_DSP_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif

void      __rDFT_Float    (const float*            src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void      __cDFT_Float    (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void      __cFFT_Float    (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t fftLen);
void      __rIDFT_Float   (const float*            src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void      __cIDFT_Float   (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t dftLen);

#ifdef __cplusplus
}
#endif

#endif
