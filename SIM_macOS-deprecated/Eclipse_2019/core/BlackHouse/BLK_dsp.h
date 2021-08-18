#ifndef _BLK_DSP_H
#define _BLK_DSP_H

#include "RH_common.h"
#include "RH_config.h"
#ifdef __cplusplus
extern "C" {
#endif

void BLK_FUNC( DSP, DFT_r     )  (const float*            src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void BLK_FUNC( DSP, DFT_c     )  (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void BLK_FUNC( DSP, IDFT_r    )  (const float*            src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void BLK_FUNC( DSP, IDFT_c    )  (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t dftLen);

void BLK_FUNC( DSP, FFT_c     )  (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t fftLen);

#ifdef __cplusplus
}
#endif

#endif
