#include "RH_dsp.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================================================================
 > DSP Reference
============================================================================================================================*/

void __rDFT_Float(const float* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex* X  = dst_c;
    const float*   _x = src;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( X == NULL ){
        X = (float complex*)RH_MALLOC(dftLen*sizeof(float complex));
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
        RH_FREE(X);
    
}

void __cFFT_Float(const float complex* src,float_t* dst_m,float complex* dst_c,size_t fftLen){

    float complex* _x = dst_c;
    
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    
    if( _x == NULL ){
        _x = (float complex*)RH_MALLOC(fftLen*sizeof(float complex));
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
        RH_FREE(_x);
    
}

void __cDFT_Float(const float complex* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex*        X = dst_c;
    const float complex* _x = src;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( X == NULL ){
        X = (float complex*)RH_MALLOC(dftLen*sizeof(float complex));
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
        RH_FREE(X);
}

void __rIDFT_Float(const float* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    
}
         
void __cIFFT_Float(const float complex* src,float_t* dst_m,float complex* dst_c,size_t dftLen){}

void __cIDFT_Float(const float complex* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex*       _x   = dst_c;
    const float complex* X    = src;
    if( (dst_m == NULL&& dst_c == NULL) || src == NULL )
        return;
    if( _x == NULL ){
        _x = (float complex*)RH_MALLOC(dftLen*sizeof(float complex));
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
        RH_FREE(_x);
}

void __Huffman_Code(const int* __src,int* __dst,size_t len){
#if SHOW_BUG
    ???
#endif
}





#ifdef __cplusplus
}
#endif

