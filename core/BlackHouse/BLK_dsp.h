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




typedef  float complex cvar;
typedef  float rvar;
    
struct BLK_SRCT(Rseq){
    size_t  len;
    rvar*   D;
};
typedef struct BLK_SRCT(Rseq) BLK_SRCT(Rseq);

struct BLK_SRCT(Cseq){
    size_t  len;
    cvar*   D;
};
typedef struct BLK_SRCT(Cseq) BLK_SRCT(Cseq);


RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_covl        (const cvar x[], size_t xlen, const cvar h[], size_t hlen);
RH_PROTOTYPE BLK_SRCT(Rseq) __BLK_Dsp_dct         (const rvar x[], size_t len);
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_dft         (const cvar x[], size_t len);
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_fft         (const cvar x[], size_t len);//
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_idft        (const cvar x[], size_t len);

RH_PROTOTYPE BLK_SRCT(Rseq) __BLK_Dsp_cseq2rseq   (const cvar x[], size_t len);
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_rseq2cseq   (const rvar x[], size_t len);

RH_PROTOTYPE BLK_SRCT(Rseq) __BLK_Dsp_rseq_create (const rvar x[], size_t len);
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_cseq_create (const cvar x[], size_t len);

RH_PROTOTYPE void           __BLK_Dsp_rseq_free   (BLK_SRCT(Rseq) x);
RH_PROTOTYPE void           __BLK_Dsp_cseq_free   (BLK_SRCT(Cseq) x);

RH_PROTOTYPE void           __BLK_Dsp_rseq_print  (BLK_SRCT(Rseq) x, int (*print)(const char*,...) );
RH_PROTOTYPE void           __BLK_Dsp_cseq_print  (BLK_SRCT(Cseq) x, int (*print)(const char*,...) );

#ifdef __cplusplus
}
#endif

#endif
