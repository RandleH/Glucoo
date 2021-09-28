#include "BLK_dsp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================================================================
 > DSP Reference
============================================================================================================================*/

void BLK_FUNC( DSP, DFT_r     ) (const float* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex* X  = dst_c;
    const float*   _x = src;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( X == NULL ){
        X = (float complex*)BLK_DSP_MALLOC(dftLen*sizeof(float complex));
        if( X == NULL ){
            return;
        }
    }
    memset(X,0,dftLen*sizeof(float complex));
    
    for(size_t k=0;k<((dftLen+2)>>1);k++){
        for(size_t n=0;n<dftLen;n++){
            double wt = 2*M_PI*k*n/dftLen;
            X[k] += _x[n]*cexp(-I*wt);
        }
        if(dst_m != NULL)
            dst_m[k] = sqrt(creal(X[k])*creal(X[k])+cimag(X[k])*cimag(X[k]));
        // Since the result of DFT is symmetrical, just copy the previous value.
        if(k!=0){
            X[dftLen-k] = conj(X[k]);
            if(dst_m != NULL)
                dst_m [dftLen-k] = dst_m[k];
        }
        
    }
//    for(size_t k=0;k<dftLen;k++) printf("| %f + \tj*%f | = \t%f\n",creal(X[k]),cimag(X[k]),dst_m[k]);
    
    if(dst_c == NULL)
        BLK_DSP_FREE(X);
    
}

void BLK_FUNC( DSP, FFT_c     ) (const float complex* src,float_t* dst_m,float complex* dst_c,size_t fftLen){

    float complex* _x = dst_c;
    
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    
    if( _x == NULL ){
        _x = (float complex*)BLK_DSP_MALLOC(fftLen*sizeof(float complex));
        if( _x == NULL ){
            return;
        }
    }
    
    memcpy(_x, src, sizeof(float complex)*fftLen);
    
    for(int i = 0, j = 0; i != fftLen; ++i){
        if(i > j){
            float complex temp = _x[i];
            _x[i] = _x[j];
            _x[j] = temp;
        }
        for(size_t l = fftLen >> 1; (j ^= l) < l; l >>= 1);
    }

    for(int i = 2; i <= fftLen; i <<= 1){
        int m = i >> 1;
        for(int j = 0; j < fftLen; j += i){
            for(int k = 0; k != m; ++k){
                float complex z = _x[j + m + k] * cexp(-I*2.0*M_PI*k/i);
                _x[j + m + k] = _x[j + k] - z;
                _x[j + k] += z;
            }
        }
    }
    if(dst_m != NULL){
        for(size_t k=0;k<fftLen;k++){
            dst_m[k] = sqrt(creal(_x[k])*creal(_x[k])+cimag(_x[k])*cimag(_x[k]));
            // printf("| %.4f + j* %.4f | = \t%f\n",creal(dst_c[k]),cimag(dst_c[k]),dst_m[k]);
        }
    }
    
    if(dst_c == NULL)
        BLK_DSP_FREE(_x);
    
}

void BLK_FUNC( DSP, DFT_c     ) (const float complex* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex*        X = dst_c;
    const float complex* _x = src;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( X == NULL ){
        X = (float complex*)BLK_DSP_MALLOC(dftLen*sizeof(float complex));
        if( X == NULL ){
            return;
        }
    }
    
    memset(X,0,dftLen*sizeof(sizeof(float complex)));
    
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double        wt  = 2*M_PI*k*n/((double)(dftLen));
            X[k] += _x[n] * (cos(wt) - sin(wt)*I);
        }
        if(dst_m != NULL)
            dst_m[k] = sqrt(creal(X[k])*creal(X[k]) + cimag(X[k])*cimag(X[k]));
    }
    
    // for(size_t k=0;k<dftLen;k++) printf("| %.4f + j* %.4f | = \t%f\n",creal(X[k]),cimag(X[k]),dst_m[k]);
    
    if(dst_c == NULL)
        BLK_DSP_FREE(X);
}

void BLK_FUNC( DSP, IDFT_r    ) (const float* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    
}
         
void BLK_FUNC( DSP, IFFT_c    ) (const float complex* src,float_t* dst_m,float complex* dst_c,size_t dftLen){}

void BLK_FUNC( DSP, IDFT_c    ) (const float complex* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex*       _x   = dst_c;
    const float complex* X    = src;
    if( (dst_m == NULL&& dst_c == NULL) || src == NULL )
        return;
    if( _x == NULL ){
        _x = (float complex*)BLK_DSP_MALLOC(dftLen*sizeof(float complex));
    }
    memset(_x,0,dftLen*sizeof(float complex));
    
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double wt = 2*M_PI*k*n/((double)(dftLen));
            _x[k]    += X[n] * cexp(I*wt); // Same Effect: _x[k] += X[n] * (cos(wt) + sin(wt)*I)
        }
        
        _x[k] /= (double)(dftLen);
        
        if(dst_m != NULL)
            dst_m[k] = sqrt(creal(_x[k])*creal(_x[k])+cimag(_x[k])*cimag(_x[k]));
        
    }
    
    // for(size_t k=0;k<dftLen;k++) printf("| %.4f + \tj*%.4f | = \t%.4f\n",creal(_x[k]),cimag(_x[k]),dst_m[k]);
    
    if(dst_c == NULL)
        BLK_DSP_FREE(_x);
}

    



    
    
RH_PROTOTYPE BLK_SRCT(Rseq) __BLK_Dsp_filter         (const rvar Pq[],const rvar Dk[],const rvar x[], size_t len){
    BLK_SRCT(Rseq) y = {0};
    
    return y;
}
    

    
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_covl           (const cvar x[], size_t xlen, const cvar h[], size_t hlen){
    RH_ASSERT(x);
    RH_ASSERT(h);
    
    BLK_SRCT(Cseq) y = {0};
    y.len  = xlen+hlen-1;
    y.D    = RH_CALLOC(sizeof(cvar), y.len);
    
    for(size_t n=0; n<y.len; n++){
        y.D[n] = 0;
        
        size_t ks = RH_MAX( (signed)(n-hlen+1), 0    );
        size_t ke = RH_MIN( (signed)(n+1     ), xlen );
        
        for(size_t k=ks; k<ke; k++){
            y.D[n] += x[k]*h[n-k];
        }
    }
    
    return y;
}
    
RH_PROTOTYPE BLK_SRCT(Rseq) __BLK_Dsp_dct            (const rvar x[], size_t len){
    BLK_SRCT(Rseq) res = {0};
    res.D    = RH_MALLOC(len*sizeof(rvar));
    res.len  = len;
    
    for( size_t k=0; k<len; k++ ){
        res.D[k] = 0;
        for( size_t n=0; n<len; n++ ){
            // w[k,n]*x[n]*cos(...)
            res.D[k] += (rvar)( (k==0) ? (1/sqrt(len)) : (2/sqrt(len)) )* (rvar)(x[n]*cos( (M_PI*(2*n+1)*k) / (2*(rvar)len) ));
        }
    }

    return res;
}

RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_dft            (const cvar x[], size_t len){
    BLK_SRCT(Cseq) X = {0};
    X.D    = RH_MALLOC(len*sizeof(cvar));
    X.len  = len;
    
    for( size_t k=0; k<len; k++ ){
        X.D[k] = 0;
        for( size_t n=0; n<len; n++ ){
            X.D[k] += x[n]*cexpf( (-I*2.0*M_PI*k*n)/(rvar)(len) );
        }
    }
    
    return X;
}
    
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_fft            (const cvar x[], size_t len){
    
    BLK_SRCT(Cseq) X = {0};
    X.D    = RH_MALLOC(len*sizeof(cvar));
    X.len  = len;
    
    size_t radix = 0;
    { // Padding to radix-2
        size_t n = len;
        while( n ){
            n >>= 1;
            radix++;
        }
    }
    
    for( size_t i=0; i<radix; i++){
        for( size_t j=0; j<(1<<(i+1)); j++ ){
            //...//
            printf("(%ld,%ld)\n",i,j);
        }
        printf("\n");
    }
    
    printf("%ld\n", radix);
    return X;
}
    
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_idft           (const cvar x[], size_t len){
    BLK_SRCT(Cseq) X = {0};
    X.D    = RH_MALLOC(len*sizeof(cvar));
    X.len  = len;
    
    for( size_t k=0; k<len; k++ ){
        X.D[k] = 0;
        for( size_t n=0; n<len; n++ ){
            X.D[k] += x[n]*cexpf( (2.0*I*M_PI*k*n)/(rvar)(len) );
        }
        X.D[k] /= (cvar)len;
    }
    
    return X;
}
    
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_rseq2cseq      (const rvar x[], size_t len){
    BLK_SRCT(Cseq) y = {0};
    y.D    = RH_MALLOC(len*sizeof(cvar));
    y.len  = len;
    
    for( size_t k=0; k<len; k++ ){
        y.D[k] = x[k] + 0*I;
    }
    return y;
}
    
RH_PROTOTYPE BLK_SRCT(Rseq) __BLK_Dsp_cseq2rseq      (const cvar x[], size_t len){
    BLK_SRCT(Rseq) y = {0};
    y.D    = RH_MALLOC(len*sizeof(rvar));
    y.len  = len;
    
    for( size_t k=0; k<len; k++ ){
        y.D[k] = (rvar)cabs(x[k]);
    }
    return y;
}
    
RH_PROTOTYPE BLK_SRCT(Rseq) __BLK_Dsp_rseq_create    (const rvar x[], size_t len){
    BLK_SRCT(Rseq) _x = {0};
    _x.D    = RH_MALLOC(len*sizeof(rvar));
    _x.len  = len;
    memcpy( _x.D, x, len*sizeof(rvar));
    return _x;
}
    
RH_PROTOTYPE BLK_SRCT(Cseq) __BLK_Dsp_cseq_create    (const cvar x[], size_t len){
    BLK_SRCT(Cseq) _x = {0};
    _x.D    = RH_MALLOC(len*sizeof(cvar));
    _x.len  = len;
    memcpy( _x.D, x, len*sizeof(cvar));
    return _x;
}
    
RH_PROTOTYPE void           __BLK_Dsp_rseq_free      (BLK_SRCT(Rseq) x){
    if( x.D )
        RH_FREE(x.D);
    x.D   = NULL;
    x.len = 0;
}
    
RH_PROTOTYPE void           __BLK_Dsp_cseq_free      (BLK_SRCT(Cseq) x){
    if( x.D )
        RH_FREE(x.D);
    x.D   = NULL;
    x.len = 0;
}

RH_PROTOTYPE void           __BLK_Dsp_rseq_print     (BLK_SRCT(Rseq) x, int (*print)(const char*,...)){
    for( size_t n=0; n< x.len; n++ ){
        print( "[%d] %.4f\n", n,x.D[n]);
    }
}
    
RH_PROTOTYPE void           __BLK_Dsp_cseq_print     (BLK_SRCT(Cseq) x, int (*print)(const char*,...)){
    RH_ASSERT(print);
    RH_ASSERT(x.D);
    for( size_t n=0; n< x.len; n++ ){
        printf( "[%2ld] %.4f [%.4f]\n", n, crealf(x.D[n]), cimagf(x.D[n]) );
    }
}

#ifdef __cplusplus
}
#endif

