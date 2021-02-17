/*===========================================================================================================================
 > Includes
============================================================================================================================*/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <wchar.h>
#include <setjmp.h>
#include <signal.h>
#include <limits.h>
#include "RH_Utility.h"
 #ifdef __cplusplus
  extern "C" {
 #endif
     
/*===========================================================================================================================
 > Standard
============================================================================================================================*/
     
#define M_SWAP_4BIT(x)    ((0x0f)&((((x)&0x55)<<1|((x)>>1)&0x55)&0x33)<<2|((((x)&0x55)<<1|((x)>>1)&0x55)>>2)&0x33)
#define M_SWAP_8BIT(x)    ((M_SWAP_4BIT((x)&0x0f)<<4)|(M_SWAP_4BIT(((x)&0xf0)>>4)))
#define M_SWAP_16BIT(x)   ((M_SWAP_8BIT((x)&0x00ff)<<8)|(M_SWAP_8BIT(((x)&0xff00)>>8)))
#define M_SWAP_32BIT(x)   ((M_SWAP_16BIT((x)&0x0000ffff)<<16)|(M_SWAP_16BIT(((x)&0xffff0000)>>16)))
     
inline uint8_t __swap_8BIT(uint8_t x){
    return (uint8_t)M_SWAP_8BIT((x&0xff));
}
     
inline uint16_t __swap_16BIT(uint16_t x){
    return (uint16_t)M_SWAP_16BIT((x&0xffff));
}
     
inline uint32_t __swap_32BIT(uint32_t x){
    return (uint32_t)M_SWAP_32BIT((x&0xffffffff));
}
     
inline uint32_t __swap_nBIT(uint32_t x,size_t n){
    return (uint32_t)( M_SWAP_32BIT(x)>>(32-n) );
}

inline uint32_t __swap_DATA(uint32_t x){
    int dummy = 32;
    while((--dummy)&&((1<<dummy)&(x&0xffffffff))==0);
    
    return (uint32_t)( M_SWAP_32BIT(x)>>(32-(dummy+1)) );
}
     
inline size_t __sizeof_BITs(uint32_t x){
    size_t cnt = 1;
    while(x>>=1){cnt++;}
    return cnt;
}
     
inline size_t __sizeof_OCTs(uint32_t x){
    size_t cnt = 1;
    while(x>>=3){cnt++;}
    return cnt;
}

inline size_t __sizeof_DECs(uint32_t x){
    size_t cnt = 1;
    while(x/=10){cnt++;}
    return cnt;
}

inline size_t __sizeof_HEXs(uint32_t x){
    size_t cnt = 1;
    while(x>>=4){cnt++;}
    return cnt;
}
      
//inline uint32_t __Gray2Bin(uint32_t x){
//    return (uint32_t)((x>>1)^x);
//}
      
inline uint32_t __Bin2Gray(uint32_t x){
    return (uint32_t)((x>>1)^x);
}
      
inline long __sum(void* pArray,size_t size,size_t num){
    long res = 0;
    switch(size){
        case 1:// Byte
            while(num--) res += *((int8_t*)pArray+num);
            break;
        case 2:// Word
            while(num--) res += *((int16_t*)pArray+num);
            break;
        case 4:// Dword
            while(num--) res += *((int32_t*)pArray+num);
            break;
        case 8:// Lword
            while(num--) res += *((int64_t*)pArray+num);
            break;
        default:
            break;
    }
    return res;
}
      
inline int __isPrime(long x){
    int res = false;

    static const char prime_128[] = {2,3,5,7,11,13,17,19,23,27,29};
    const char* p     = prime_128;

    size_t iter = sizeof(prime_128);
    while(iter--){
        if( x == *(p) )
            return true;
        if( x > *(p) && x < *(++p) )
            return false;
    }
    //...//
    return res;
}
     
/*===========================================================================================================================
 > Algebra Reference 
============================================================================================================================*/

long __sign(long x){
    return (x>=0)?(1):(-1);
}
      
long __step(long x){
    return (long)( x >= 0 );
}

long __sqrt(long x){
    if(x <= 0) return 0;
    long l   = 1;
    long r   = x;
    long res = 0;
    while(l <= r){
        long mid=(l+r)>>1;
        if(mid <= x/mid){
          l   = mid+1;
          res = mid;
      }else{
          r = mid-1;
      }
    }
    if( ((res+1)*(res+1) - x) > (x - res*res) )
        return res;
    return (res+1);
}
      
double __sigmold(double x){
    return (double)(1.0/(1+exp(-x)));
}

double __gussian(long x,long __miu,double __sigma){
// Same Effect but slower,only suitable when __sigma is a value of double.
    return ((__sigma==0)?(0):(double)((M_2_SQRTPI/((__sigma*2)*(M_SQRT2)))*exp(-(x-__miu)*(x-__miu)/(double)((__sigma*__sigma)*2))));
//    return ((__sigma==0)?(0):(double)((M_2_SQRTPI/((__sigma<<1)*(M_SQRT2)))*exp(-(x-__miu)*(x-__miu)/(double)((__sigma*__sigma)<<1))));
}

double __gussian2D(long x,long y,double __sigma){
// Same Effect but slower,only suitable when __sigma is a value of double.
    return ((__sigma==0)?(0):((double)((1/(2*M_PI*__sigma*__sigma))*exp(-((x*x)+(y*y))/(double)((__sigma*__sigma)*2)))));
//    return ((__sigma==0)?(0):((double)((1/(M_PI*__sigma*(__sigma<<1)))*exp(-((x*x)+(y*y))/(double)((__sigma*__sigma<<1))))));
}

__Kernel_t* __gussianKernel(double __sigma,size_t order,__Kernel_t* pKernel){
    if( pKernel == NULL || pKernel->pBuffer == NULL ){
        return NULL;
    }
    
    if( __sigma == 0){ // In case of divider being zero.
        memset(pKernel->pBuffer,0,order*order*sizeof(*(pKernel->pBuffer)));
        pKernel->order = order;
        pKernel->sum = 0;
        return pKernel;
    }
    
    size_t half_order = ((order-1)>>1); // The index of the middle element. eg:  x x x ^ x x x ,which is "3".
    uint16_t* pCenter = pKernel->pBuffer + (half_order * order) + half_order;
    double coe        = 1.0/__gussian2D(half_order,half_order,__sigma); // Make sure every element is larger than 0.
    
    pKernel->order = order;
    pKernel->sum = 0;
    for(int x=0;x<=half_order;x++){
        for(int y=0;y<=x;y++){
            uint16_t temp = lround(coe*__gussian2D(x,y,__sigma));
            *(pCenter + (y*order) + x) = temp;
            *(pCenter - (y*order) + x) = temp;
            *(pCenter + (y*order) - x) = temp;
            *(pCenter - (y*order) - x) = temp;
            *(pCenter + (x*order) + y) = temp;
            *(pCenter - (x*order) + y) = temp;
            *(pCenter + (x*order) - y) = temp;
            *(pCenter - (x*order) - y) = temp;
            if(x == 0 && y == 0)
                pKernel->sum += temp;
            else if( x==0 || y == 0 || x==y )
                pKernel->sum += (temp<<2);
            else
                pKernel->sum += (temp<<3);
            
        }
    }
    return pKernel;
}
      
long __pascal_triangle(int row, int col){
    __exitReturn(col>row || col<0 || row<0 , -1);
#if SHOW_BUG
    ???
#endif    
    return 0;
}
      
inline long __step_mul(long x){ // [!] Limitation: x should be smaller than 20
    __exitReturn(x<0, -1);
    
    long res = 1;
    while(--x){
        res*=(x+1);
    }
    return res;
}
      
long __comb(long num,long m){
    __exitReturn(m>num || m<0 || num<0 , -1);
#if SHOW_BUG
    ???
#endif
    return 0;
}
      
long __fibonacci(long n){
    __exitReturn(n<0, -1);
    
    if(n==0)
        return 1;
    long res = 0;
    long fnm1 = 1,fnm2 = 0;
    for (int i=2; i<=n+1; i++) {
        res  = fnm1+fnm2;
        fnm2 = fnm1;
        fnm1 = res;
    }
    return res;
}
      

/*===========================================================================================================================
 > Quantity Reference 
============================================================================================================================*/

struct IntArray_t __findMax_INT(const int* pValue,size_t num){
    int max = *pValue;
    int cnt = 0;
    while(num--){
        if(*pValue > max)
            max = *pValue;
        pValue++;
        cnt++;
    }
    struct IntArray_t result = {.index = cnt,.value = max};
    return result;
}

struct IntArray_t __findMin_INT(const int* pValue,size_t num){
    int min = *pValue;
    int cnt = 0;
    while(num--){
        if(*pValue < min)
            min = *pValue;
        pValue++;
        cnt++;
    }
    struct IntArray_t result = {.index = cnt,.value = min};
    return result;
}


/*===========================================================================================================================
 > Geometry Reference 
============================================================================================================================*/

Point3D_t __findPoint_VectorDistance (const Point3D_t*  A,const Point3D_t*  B,int dist_AP){ 
    long dist_AB = lroundl(sqrt( (B->x - A->x)*(B->x - A->x) + \
                                (B->y - A->y)*(B->y - A->y) + \
                                (B->z - A->z)*(B->z - A->z)  ));
    Point3D_t result = {
        .x = (B->x - A->x)*dist_AP/dist_AB + A->x ,
        .y = (B->y - A->y)*dist_AP/dist_AB + A->y ,
        .z = (B->z - A->z)*dist_AP/dist_AB + A->z ,
    };

    return result;
}

Point3D_t __findPoint_VectorProportion (const Point3D_t*  A,const Point3D_t*  B,double scale){ 
    Point3D_t result = {
        .x = (B->x - A->x)*scale + A->x ,
        .y = (B->y - A->y)*scale + A->y ,
        .z = (B->z - A->z)*scale + A->z ,
    };
    return result;
}

int __Vect2D_Dot(const Vector2D_t* vect1,const Vector2D_t* vect2){
    return (int)((vect1->x*vect2->x)+(vect1->y*vect2->y));
}

int __Vect3D_Dot(const Vector3D_t* vect1,const Vector3D_t* vect2){
    return (int)((vect1->x*vect2->x)+(vect1->y*vect2->y)+(vect1->z*vect2->z));
}

Vector3D_t __Vect3D_Cross(const Vector3D_t* vect1,const Vector3D_t* vect2){
    Vector3D_t vecResult = {.x = ( vect1->y*vect2->z - vect1->z*vect2->y),\
                            .y = ( vect1->z*vect2->x - vect1->x*vect2->z),\
                            .z = ( vect1->x*vect2->y - vect1->y*vect2->x)};
    return vecResult;
}

 // -1    = Line is negative.
 //  0    = Line is horizontal.
 //  1    = Line is positive.
 // 65535 = Line is vertical.
int __Dir_Line(int xs,int ys,int xe,int ye){
    if(xs==xe)
        return 65535;
    if(ys==ye)
        return 0;

    return ((xe-xs)*(ye-ys)>0)?(1):(-1);
}

 // -1 = (px,py) is below the line.
 //  0 = (px,py) is at the line.
 //  1 = (px,py) is above the line.
int __Point_toLine(int xs,int ys,int xe,int ye,int px,int py){
    int param_1 = (xe>xs)?( (xe-xs)*py ):( (xs-xe)*py );
    int param_2 = (xe>xs)?( (ye-ys)*px+(ye*(xe-xs)-xe*(ye-ys)) ):( (ys-ye)*px+(ye*(xs-xe)-xe*(ys-ye)) );

    if(param_1 > param_2)
        return 1;
    else if(param_1 < param_2)
        return -1;
    else
        return 0;
}

 // -1 = (px,py) is outside the triangle
 //  0 = (px,py) is at the edge of triangle
 //  1 = (px,py) is inside the triangle
int __Point_toTriangle(int x1,int y1,int x2,int y2,int x3,int y3,int px,int py){
 // Condition:
 // P = A + u*(CA) + v*(BA)
 // u >= 0 && v >= 0 && u+v <= 1
 
 // Any point can be represented by: (PA) = u*(CA) + v*(BA)
 // 
 // When both multiply by (CA) and (BA):
 // (PA)·(CA) = u*[(CA)·(CA)] + v*[(BA)·(CA)]   
 // (PA)·(BA) = u*[(BA)·(CA)] + v*[(BA)·(BA)]  
 
 // Then:
 //         [(BA)·(BA)]*[(PA)·(CA)] - [(BA)·(CA)]*[(PA)·(BA)]
 // u = ---------------------------------------------------------
 //         [(CA)·(CA)]*[(BA)·(BA)] - [(CA)·(BA)]*[(BA)·(CA)]
 
 //         [(CA)·(CA)]*[(PA)·(BA)] - [(CA)·(CA)]*[(PA)·(CA)]
 // v = ---------------------------------------------------------
 //         [(CA)·(CA)]*[(BA)·(BA)] - [(CA)·(BA)]*[(BA)·(CA)]
 
 // Assume A = (x1,y1) | B = (x2,y2) | C = (x3,y3) :
    struct Vector2D_t v0 = {.x = x3-x1,.y = y3-y1};
    struct Vector2D_t v1 = {.x = x2-x1,.y = y2-y1};
    struct Vector2D_t v2 = {.x = px-x1,.y = py-y1};

    int v00 = __Vect2D_Dot(&v0,&v0);
    int v01 = __Vect2D_Dot(&v0,&v1);
    int v02 = __Vect2D_Dot(&v0,&v2);
    int v11 = __Vect2D_Dot(&v1,&v1);
    int v12 = __Vect2D_Dot(&v1,&v2);

    int u = v11*v02-v01*v12;
    int v = v00*v12-v01*v02;
    int d = v00*v11-v01*v01;
    if(u<0 || v<0)
        return -1;
    else if(u==0 || v==0)
        return 0;

    if(u+v > d)
        return -1;
    else if(u+v < d)
        return 1;
    else
        return 0;
}

 // -1 = (px,py) is outside the circle
 //  0 = (px,py) is at the edge of circle
 //  1 = (px,py) is inside the circle
int __Point_toCircle(int xc,int yc,int radius,int px,int py){
    int key = (xc-px)*(xc-px)+(yc-py)*(yc-py);
    int r_2 = radius*radius;
    if(key > r_2)
        return -1;
    else if(key < r_2)
        return 1;
    else
        return 0;
}

/*===========================================================================================================================
 > DSP Reference
============================================================================================================================*/

void __rDFT_Float(const float* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex* X  = dst_c;
    const float*   _x = src;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( X == NULL ){
        X = (float complex*)__malloc(dftLen*sizeof(float complex));
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
        __free(X);
    
}

void __cFFT_Float(const float complex* src,float_t* dst_m,float complex* dst_c,size_t fftLen){

    float complex* _x = dst_c;
    
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    
    if( _x == NULL ){
        _x = (float complex*)__malloc(fftLen*sizeof(float complex));
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
            printf("| %.4f + j* %.4f | = \t%f\n",creal(dst_c[k]),cimag(dst_c[k]),dst_m[k]);
        }
    }
    
    if(dst_c == NULL)
        __free(_x);
    
}

void __cDFT_Float(const float complex* src,float_t* dst_m,float complex* dst_c,size_t dftLen){
    float complex*        X = dst_c;
    const float complex* _x = src;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( X == NULL ){
        X = (float complex*)__malloc(dftLen*sizeof(float complex));
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
    
    for(size_t k=0;k<dftLen;k++) printf("| %.4f + j* %.4f | = \t%f\n",creal(X[k]),cimag(X[k]),dst_m[k]);
    
    if(dst_c == NULL)
        __free(X);
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
        _x = (float complex*)__malloc(dftLen*sizeof(float complex));
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
    
    for(size_t k=0;k<dftLen;k++) printf("| %.4f + \tj*%.4f | = \t%.4f\n",creal(_x[k]),cimag(_x[k]),dst_m[k]);
    
    if(dst_c == NULL)
        __free(_x);
}

void __Huffman_Code(const int* __src,int* __dst,size_t len){
#if SHOW_BUG
    ???
#endif
}

/*===========================================================================================================================
 > Image Processing Reference 
============================================================================================================================*/
#if defined    (_WIN32)
#include <windows.h>
#elif defined  (__APPLE__)
typedef uint8_t   BYTE;
typedef uint16_t  WORD;
typedef uint32_t  DWORD;
typedef int32_t   LONG;
typedef float     FLOAT;
typedef FLOAT     *PFLOAT;
typedef BYTE      *PBYTE;
typedef BYTE      *LPBYTE;
typedef int       *PINT;
typedef int       *LPINT;
typedef WORD      *PWORD;
typedef WORD      *LPWORD;
typedef int32_t   *LPLONG;
typedef DWORD     *PDWORD;
typedef DWORD     *LPDWORD;
typedef void      *LPVOID;
#pragma pack(1)
typedef struct tagBITMAPFILEHEADER {
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
} BITMAPFILEHEADER;

#pragma pack(1)
typedef struct tagBITMAPINFOHEADER {
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} BITMAPINFOHEADER;

#endif
__ImageRGB888_t* __LoadBMP_ImgRGB888(const char* __restrict__ path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    __ImageRGB888_t* pIMG = __malloc(sizeof(__ImageRGB888_t));
    pIMG->height  = 0;
    pIMG->width   = 0;
    pIMG->pBuffer = NULL;
    
    bmp = fopen(path, "r");
    if (bmp == NULL) {
        printf("open error\n");
        return pIMG;
    }
    fseek(bmp, 0L, SEEK_SET);
    fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, bmp);
    fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, bmp);

    if (fileHead.bfType != 0x4D42) {
        printf("This not a *.bmp file\n");
        return pIMG;
    }

    fseek(bmp, fileHead.bfOffBits, SEEK_SET);

    pIMG->pBuffer = (__UNION_PixelRGB888_t*)__malloc(infoHead.biWidth * infoHead.biHeight * sizeof(__UNION_PixelRGB888_t));
    
    for (int row = 0; row < infoHead.biHeight; row++) {
        for (int col = 0; col < infoHead.biWidth; col++) {
            fread(&(pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data), sizeof(__PixelRGB888_t), 1, bmp);

 //           printf("[%d]: ",(infoHead.biHeight - row - 1)*infoHead.biWidth + col);
 //           printf("R=%d G=%d B=%d\n",\
 //                  pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].R,\
 //                  pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].G,\
 //                  pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].B);
        }
        int eps = (4-(infoHead.biWidth*sizeof(__PixelRGB888_t))%4)%4;
        uint8_t dummyByte;
        while(eps--){
            fread(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    fclose(bmp);

    pIMG->width   = infoHead.biWidth;
    pIMG->height  = infoHead.biHeight;

    return pIMG;
}

__ImageRGB888_t* __CopyBMP_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst){
    memcpy(dst->pBuffer, src->pBuffer, (src->height)*(src->width)*sizeof(__UNION_PixelRGB888_t));
    dst->height = src->height;
    dst->width  = src->width;
    return dst;
}

__ImageRGB888_t* __Create_ImgRGB888(size_t width,size_t height){
    __ImageRGB888_t* pIMG = __malloc(sizeof(__ImageRGB888_t));
    if(pIMG == NULL)
        return NULL;
    pIMG->height          = height;
    pIMG->width           = width;
    pIMG->pBuffer         = __malloc((pIMG->height)*(pIMG->width)*sizeof(pIMG->pBuffer[0]));
    if(pIMG->pBuffer == NULL){
        __free(pIMG);
        return NULL;
    }
    memset(pIMG->pBuffer, 0, (pIMG->height)*(pIMG->width)*sizeof(pIMG->pBuffer[0]));
    return pIMG;
}

__ImageRGB888_t* __OutBMP_ImgRGB888(const char* __restrict__ path,__ImageRGB888_t* p){
    FILE* bmp;
    if(p == NULL && p->pBuffer == NULL)
        return NULL;
    int eps = (4-(p->width*sizeof(__PixelRGB888_t))%4)%4;
    BITMAPFILEHEADER fileHead = {
        .bfOffBits      = 40 + 14   ,
        .bfReserved1    = 0         ,
        .bfReserved2    = 0         ,
        .bfSize         = (uint32_t)(p->height * p->width * sizeof(__PixelRGB888_t) + 54),
        .bfType         = 0x4D42    , 
    };
    BITMAPINFOHEADER infoHead = {
        .biSize          = 40        ,
        .biWidth         = (int)(p->width)  ,
        .biHeight        = (int)(p->height) ,
        .biPlanes        = 1         ,
        .biBitCount      = 8+8+8     ,
        .biCompression   = 0         , 
        .biSizeImage     = (uint32_t)(p->height*p->width*sizeof(__PixelRGB888_t) + eps*(p->height)) ,
        .biClrUsed       = 0         ,
        .biClrImportant  = 0         ,
        .biXPelsPerMeter = 0         ,
        .biYPelsPerMeter = 0         ,
    };
    printf("%d\n" ,infoHead.biSizeImage    );
    bmp = fopen(path,"wb");

    if(bmp == NULL) return NULL;

    // RGB Sequence should be reversed.
    fseek(bmp,0L,SEEK_SET);
    fwrite(&fileHead ,1 ,sizeof(BITMAPFILEHEADER) , bmp);
    fwrite(&infoHead ,1 ,sizeof(BITMAPINFOHEADER) , bmp);
    fseek(bmp,54L,SEEK_SET);
    for (int row = 0; row < p->height; row++) {
        for (int col = 0; col < p->width; col++) {
            fwrite( &p->pBuffer[(infoHead.biHeight - row - 1) * infoHead.biWidth + col] ,sizeof(__PixelRGB888_t) ,1 ,bmp );
        }
        int eps = (4-(infoHead.biWidth*sizeof(__PixelRGB888_t))%4)%4;
        uint8_t dummyByte = 0x00;
        while(eps--){
            fwrite(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    
    fclose(bmp);
    return p;
}

__ImageRGB888_t* __FreeBuffer_ImgRGB888(__ImageRGB888_t* ptr){
    __free(ptr->pBuffer);
    ptr->height  = 0;
    ptr->width   = 0;
    ptr->pBuffer = NULL;
    return ptr;
}

void __Free_ImgRGB888(__ImageRGB888_t* ptr){
    __free(__FreeBuffer_ImgRGB888(ptr));
}

__ImageRGB888_t* __Filter_Gray_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    
    if(src != NULL && dst != NULL){
        if(src->pBuffer != NULL && dst->pBuffer != NULL){
            for (int row = 0; row < src->height; row++) {
                for (int col = 0; col < src->width; col++) {
                    long temp = lroundl(0.299 * src->pBuffer[row * src->width + col].R + 0.587 * src->pBuffer[row * src->width + col].G + 0.114 * src->pBuffer[row * src->width + col].B);
                    dst->pBuffer[row * src->width + col].data = (uint32_t)(((temp&0xff)<<16)|((temp&0xff)<<8)|((temp&0xff)));
                }
            }
        }
    }
    return dst;
}

__ImageRGB888_t* __Filter_Warm_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    return dst;
}

__ImageRGB888_t* __Filter_Cold_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    
    return dst;
}

__ImageRGB888_t* __Filter_OTUS_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    uint32_t threshold = 0;
    __exitReturn( src==NULL         , NULL);
    __exitReturn( src->pBuffer==NULL, NULL);
    __exitReturn( dst==NULL         , NULL);
    __exitReturn( dst->pBuffer==NULL, NULL);
    __Analyze_OTUS_ImgRGB888(src, &threshold);
    __exitReturn(threshold == -1, NULL);
    
    for(int y=0;y<src->height;y++){
        for(int x=0;x<src->width;x++){
            uint8_t temp = ( __array1D(src->pBuffer, src->width, y, x)->R*19595 + \
                             __array1D(src->pBuffer, src->width, y, x)->G*38469 + \
                             __array1D(src->pBuffer, src->width, y, x)->B*7472 )>>16;
            if( temp > threshold )
                __array1D(dst->pBuffer, dst->width, y, x)->data = 0x00ffffff;
            else
                __array1D(dst->pBuffer, dst->width, y, x)->data = 0x00000000;
        }
    }
    
//    printf("otus threshold = %d\n", threshold);
    
    
    return NULL;
}
     
__ImageRGB888_t* __Trans_Mirror_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint8_t HV){
    if( src == NULL || src->pBuffer == NULL ){
        return NULL;
    }
    if(dst == NULL){
        dst = (__ImageRGB888_t*)__malloc(sizeof(__ImageRGB888_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB888_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    if(dst->pBuffer == NULL){
        dst->pBuffer = (__UNION_PixelRGB888_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    switch(HV){
        case 0:
            for(size_t y=0;y<src->height;y++){
                for(size_t x=0;x<((src->width+1)>>1);x++){
                    __UNION_PixelRGB888_t tmp_fore = src->pBuffer[y*src->width + x];
                    __UNION_PixelRGB888_t tmp_back = src->pBuffer[y*src->width + src->width - 1 - x];
                    dst->pBuffer[y*src->width+x]                    = tmp_back;
                    dst->pBuffer[y*src->width + src->width - 1 - x] = tmp_fore;
                }
            }

            break;
        case 1:
            for(size_t y=0;y<src->height;y++){
                memmove(&dst->pBuffer[(src->height-1-y)*dst->width], &src->pBuffer[y*src->width], src->width*sizeof(__UNION_PixelRGB888_t));
            }
            break;
        default:
            //...//
            break;
    }
    
    return NULL;
}

__ImageRGB888_t* __Blur_Gussian_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t radSize, uint16_t br_100){
    static __Kernel_t gus_kernel = {
        .pBuffer = NULL,
        .order   = 0,
        .sum     = 0,
    };
    static uint16_t radSize_old      = 0;
    
    if( radSize_old != radSize ){
        if( gus_kernel.pBuffer != NULL ){
            __free( gus_kernel.pBuffer );
        }
        double sigma  = __map(radSize, 0, 65535, 0.0, 10.0); // convert a normal value to sigma
        size_t order  = lround(sigma*6); // 6 times sigma includes 99% area.
        gus_kernel.pBuffer = (uint16_t*)__malloc( order*order*sizeof(uint16_t) );
        
        if((order & 0x01) == 0) // order should be an odd number.
            order--;
        if(order>=31) // too big!!!
            order = 31;
        __gussianKernel(sigma,order,&gus_kernel);
    }

    __ImageRGB888_t* pImg = __Conv2D_ImgRGB888(src, dst, &gus_kernel,br_100);
    
    radSize_old      = radSize;

    return pImg;

}

__ImageRGB888_t* __Blur_Average_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t radSize, uint16_t br_100){
//    __exitReturn(src == NULL || dst == NULL , NULL);
    
    double sigma  = __map(radSize, 0, 65535, 0.0, 10.0); // convert a normal value to sigma
    size_t order  = lround(sigma*6); // 6 times sigma includes 99% area.
    
    order = __limit(order, 3, 101);
    if((order & 0x01) == 0) // order should be an odd number.
        order--;
    
    unsigned long sum_R = 0, sum_G = 0, sum_B = 0;
    unsigned long div = 0;
    
    // Pre-Calculation
    int half_order  = (int)((order+1)>>1); // Kernel
    div = half_order * half_order;
    for(int n=0;n<half_order;n++){
        for(int m=0;m<half_order;m++){
            sum_R += __array1D(src->pBuffer, src->width, n, m)->R;
            sum_G += __array1D(src->pBuffer, src->width, n, m)->G;
            sum_B += __array1D(src->pBuffer, src->width, n, m)->B;
        }
    }
    div = half_order * half_order;
//    printf("div = %ld , sum_R = %ld\n",div,sum_R);
    // Average Filter
    for(int j=0;j<src->height;j++){
        for(int i=0;i<src->width;i++){
            if(j%2 == 0){ // Scan Direction:  [old] -->--> [new]
                
                if(i!=0){ // No need to do when it reachs the left-edge because it has been done when moving to the next row.
                    
                    // Remove leftmost column because it is old.
                    if(i-half_order >= 0){                                          // [!] no cross the broad [0,src->width-1]
                        for(int row=j-half_order+1;row<=j+half_order-1;row++){
                            if( row<src->height && row>=0 ){                       // [!] no cross the broad [0,src->height-1]
                                sum_R -= __array1D(src->pBuffer, src->width, row, i-half_order)->R;
                                sum_G -= __array1D(src->pBuffer, src->width, row, i-half_order)->G;
                                sum_B -= __array1D(src->pBuffer, src->width, row, i-half_order)->B;
                                div--;
                            }
                        }
                    }
                    
                    // Add rightmost column because it is new.
                    if( i+half_order-1 < src->width ){                             // [!] no cross the broad [0,src->width-1]
                        for(int row=j-half_order+1;row<=j+half_order-1;row++){
                            if( row<src->height && row>=0 ){                       // [!] no cross the broad [0,src->height-1]
                                sum_R += __array1D(src->pBuffer, src->width, row, i+half_order-1)->R;
                                sum_G += __array1D(src->pBuffer, src->width, row, i+half_order-1)->G;
                                sum_B += __array1D(src->pBuffer, src->width, row, i+half_order-1)->B;
                                div++;
                            }
                        }
                    }
                    
                }
//                printf("[%2ld , %4ld] ",div,sum_R);
                __array1D(dst->pBuffer, src->width, j, i)->R = sum_R*br_100/(div*100);
                __array1D(dst->pBuffer, src->width, j, i)->G = sum_G*br_100/(div*100);
                __array1D(dst->pBuffer, src->width, j, i)->B = sum_B*br_100/(div*100);
            }else{ // Scan Direction:  [new] <--<-- [old]
                int k = (int)(src->width)-i-1; // reverse i
                // Remove rightmost column because it is old.
                if( k != src->width-1 ){ // No need to do when it reachs the right-edge because it has been done when moving to the next row.
                    if(k+half_order < src->width ){                                // [!] no cross the broad [0,src->width-1]
                        for(int row=j-half_order+1;row<=j+half_order-1;row++){
                            if( row<src->height && row>=0 ){                       // [!] no cross the broad [0,src->height-1]
                                sum_R -= __array1D(src->pBuffer, src->width, row, k+half_order)->R;
                                sum_G -= __array1D(src->pBuffer, src->width, row, k+half_order)->G;
                                sum_B -= __array1D(src->pBuffer, src->width, row, k+half_order)->B;
                                div--;
                            }
                        }
                    }
                    
                    // Add leftmost column because it is new.
                    if(k-half_order+1 >=0 ){                                       // [!] no cross the broad [0,src->width-1]
                        for(int row=j-half_order+1;row<=j+half_order-1;row++){
                            if( row<src->height && row>=0 ){                       // [!] no cross the broad [0,src->height-1]
                                sum_R += __array1D(src->pBuffer, src->width, row, k-half_order+1)->R;
                                sum_G += __array1D(src->pBuffer, src->width, row, k-half_order+1)->G;
                                sum_B += __array1D(src->pBuffer, src->width, row, k-half_order+1)->B;
                                div++;
                            }
                        }
                    }
                }
//                printf("[%2ld , %4ld] ",div,sum_R);
                __array1D(dst->pBuffer, src->width, j, k)->R = sum_R*br_100/(div*100);
                __array1D(dst->pBuffer, src->width, j, k)->G = sum_G*br_100/(div*100);
                __array1D(dst->pBuffer, src->width, j, k)->B = sum_B*br_100/(div*100);
            }
            // End of scanning of this row.
        }
        
//        printf("\n");
        // Remove topmost row because it is old.
        if( j-half_order+1 >= 0 ){         // [!] no cross the broad [0,src->height-1]
            
            if(j%2 == 0){ // Scan Direction:  [old] -->--> [new]. Now it is reaching the rightmost.
                for(int col=(int)(src->width-half_order);col<src->width;col++){
                    sum_R -= __array1D(src->pBuffer, src->width, j-half_order+1, col)->R;
                    sum_G -= __array1D(src->pBuffer, src->width, j-half_order+1, col)->G;
                    sum_B -= __array1D(src->pBuffer, src->width, j-half_order+1, col)->B;
                    div--;
                }
            }else{        // Scan Direction:  [new] <--<-- [old]. Now it is reaching the leftmost.
                for(int col=0;col<half_order;col++){
                    sum_R -= __array1D(src->pBuffer, src->width, j-half_order+1, col)->R;
                    sum_G -= __array1D(src->pBuffer, src->width, j-half_order+1, col)->G;
                    sum_B -= __array1D(src->pBuffer, src->width, j-half_order+1, col)->B;
                    div--;
                }
            }

        }
        // Add downmost row because it is new.
        if(j+half_order < src->height ){         // [!] no cross the broad [0,src->height-1]
            
            if(j%2 == 0){ // Scan Direction:  [old] -->--> [new]. Now it is reaching the rightmost.
                for(int col=(int)(src->width-half_order);col<src->width;col++){
                    sum_R += __array1D(src->pBuffer, src->width, j+half_order, col)->R;
                    sum_G += __array1D(src->pBuffer, src->width, j+half_order, col)->G;
                    sum_B += __array1D(src->pBuffer, src->width, j+half_order, col)->B;
                    div++;
                }
            }else{        // Scan Direction:  [new] <--<-- [old]. Now it is reaching the leftmost.
                for(int col=0;col<half_order;col++){
                    sum_R += __array1D(src->pBuffer, src->width, j+half_order, col)->R;
                    sum_G += __array1D(src->pBuffer, src->width, j+half_order, col)->G;
                    sum_B += __array1D(src->pBuffer, src->width, j+half_order, col)->B;
                    div++;
                }
            }
        }
        
    }
    
    return NULL;
}

__ImageRGB888_t* __Interpo_NstNeighbor_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,size_t height,size_t width){
    if(src == NULL || src->pBuffer == NULL || dst == NULL) // Bad address
        return NULL;
    if(height < src->height || width < src->width) // Image of "dst" should be larger than image of "src" in both dimension.
        return NULL;
    if(dst->pBuffer == NULL){
        dst->pBuffer = (__UNION_PixelRGB888_t*)__malloc(width*height*sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL){
            return NULL;  // There is no space to malloc.
        }
    }
    dst->height = height;
    dst->width  = width;
    memset(dst->pBuffer, 0, width*height*sizeof(__UNION_PixelRGB888_t));
    
    size_t eps_x = 0; // Record errors no bigger than width.
    size_t eps_y = 0; // Record errors no bigger than height.
    size_t fx    = 0; // Pixel cordination of original image in x direction.
    size_t fy    = 0; // Pixel cordination of original image in y direction.
    for(size_t gy=0;gy<height;gy++){
        eps_y += src->height;
        if(eps_y >= height){
            fx = 0;
            for(size_t gx=0;gx<width;gx++){
                eps_x += src->width;
                if( eps_x >= width ){
                    // This is the position to copy pixels from original image.
                    (dst->pBuffer + (width*gy) + gx)->data = (src->pBuffer + (src->width*fy) + fx)->data;
//                    printf("%ld,%ld ",fx,fy);
                    eps_x-=width;
                    fx++;
                }else{
                    // This is the position needs to interpolate.
                    //...//
                }
            }
//            printf("\n");
            eps_y -= height;
            fy++;
        }else
            continue;
    }
    
    return dst;
}

__ImageRGB565_t* __Conv2D_ImgRGB565(const __ImageRGB565_t* src,__ImageRGB565_t* dst,const __Kernel_t* k,uint16_t br_100){
    if( src == NULL || src->pBuffer == NULL || k == NULL){
        return dst;
    }
        
    if(dst == NULL){
        dst = (__ImageRGB565_t*)__malloc(sizeof(__ImageRGB565_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB565_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB565_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst->pBuffer == NULL){
        dst->pBuffer = (__UNION_PixelRGB565_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB565_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst == NULL){
        dst = (__ImageRGB565_t*)__malloc(sizeof(__ImageRGB565_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB565_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB565_t));
    }

    for(int j=0;j<src->height;j++){
        for(int i=0;i<src->width;i++){
            int div = k->sum;
            
            // Here comes the convolution part.
            unsigned long tmp_R = 0,tmp_G = 0,tmp_B = 0; // Preparation for RGB data.
            for(int n=0;n<k->order;n++){
                for(int m=0;m<k->order;m++){
                    size_t offset_y  = j-(k->order>>1)+n;
                    size_t offset_x  = i-(k->order>>1)+m;
                    int selectKernel = *( k->pBuffer + n       * k->order + m       );
                    if(offset_x<0||offset_y<0||offset_x>=src->width||offset_y>=src->height){
                        div -= selectKernel;
                    }else{
                        uint8_t select_R  = (src->pBuffer + offset_y*src->width + offset_x)->R;
                        uint8_t select_G  = (src->pBuffer + offset_y*src->width + offset_x)->G;
                        uint8_t select_B  = (src->pBuffer + offset_y*src->width + offset_x)->B;
                        
                        tmp_R += ( (select_R) * (selectKernel) );
                        tmp_G += ( (select_G) * (selectKernel) );
                        tmp_B += ( (select_B) * (selectKernel) );
                    }
                }
            }
            size_t offset = (j*src->width)+i;
            if(offset < dst->width*dst->height){
                (dst->pBuffer+offset)->R = (div==0)?((1<<5)-1):(tmp_R*br_100/(div*100));
                (dst->pBuffer+offset)->G = (div==0)?((1<<6)-1):(tmp_G*br_100/(div*100));
                (dst->pBuffer+offset)->B = (div==0)?((1<<5)-1):(tmp_B*br_100/(div*100));
            }
        }
    }
    
    return dst;
}

__ImageRGB888_t* __Conv2D_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,const __Kernel_t* k,uint16_t br_100){
    if( src == NULL || src->pBuffer == NULL || k == NULL ){
        return dst;
    }
    
    if(dst == NULL){
        dst = (__ImageRGB888_t*)__malloc(sizeof(__ImageRGB888_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB888_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst->pBuffer == NULL){
        dst->pBuffer = (__UNION_PixelRGB888_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst == NULL){
        dst = (__ImageRGB888_t*)__malloc(sizeof(__ImageRGB888_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB888_t*)__malloc(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
    }

    for(int j=0;j<src->height;j++){
        for(int i=0;i<src->width;i++){
            int div = k->sum;
            
            // Here comes the convolution part.
            unsigned long tmp_R = 0,tmp_G = 0,tmp_B = 0; // Preparation for RGB data.
            for(int n=0;n<k->order;n++){
                for(int m=0;m<k->order;m++){
                    size_t offset_y  = j-(k->order>>1)+n;
                    size_t offset_x  = i-(k->order>>1)+m;
                    int selectKernel = *( k->pBuffer + n       * k->order + m       );
                    if(offset_x<0||offset_y<0||offset_x>=src->width||offset_y>=src->height){
                        div -= selectKernel;
                    }else{
                        uint8_t select_R  = (src->pBuffer + offset_y*src->width + offset_x)->R;
                        uint8_t select_G  = (src->pBuffer + offset_y*src->width + offset_x)->G;
                        uint8_t select_B  = (src->pBuffer + offset_y*src->width + offset_x)->B;
                        
                        tmp_R += ( (select_R) * (selectKernel) );
                        tmp_G += ( (select_G) * (selectKernel) );
                        tmp_B += ( (select_B) * (selectKernel) );
                    }
                }
            }
            size_t offset = (j*src->width)+i;
            if(offset < dst->width*dst->height){
                unsigned long temp = 0;
                
                temp = (tmp_R*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->pBuffer+offset)->R = (uint8_t)((1<<8)-1);
                else                                (dst->pBuffer+offset)->R = (uint8_t)(temp);
                
                temp = (tmp_G*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->pBuffer+offset)->G = (uint8_t)((1<<8)-1);
                else                                (dst->pBuffer+offset)->G = (uint8_t)(temp);
                
                temp = (tmp_B*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->pBuffer+offset)->B = (uint8_t)((1<<8)-1);
                else                                (dst->pBuffer+offset)->B = (uint8_t)(temp);
                
            }
        }
    }
    
    return dst;
}
      
void __Analyze_OTUS_ImgRGB888(const __ImageRGB888_t* src,uint32_t* threshold){
    *threshold = -1;
    __exit( src          == NULL );
    __exit( src->pBuffer == NULL );
    
    int    threshold_temp;
    long   NumOf_bckPixel = 0;    //Number of pixels defined as background
    long   SumOf_bckPixel = 0;    //Sum of pixels defined as background
    float  AvgOf_bckPixel = 0.0;  //Average value of pixels defined as background

    long   NumOf_objPixel = 0;    //Number of pixels defined as background
    long   SumOf_objPixel = 0;    //Sum of pixels defined as background
    float  AvgOf_objPixel = 0.0;  //Average value of pixels defined as background
    
    float  g = 0.0, g_max = 0.0;  //Variance between obj and bck
    
    const long NumOf_allPixel = (src->width) * (src->height);
    
    // Make Statistic...

    long gray_cnt[255] = {0};
    for (int row = 0; row < src->height; row++){
        for (int col = 0; col < src->width; col++){
            uint8_t temp = ( __array1D(src->pBuffer, src->width, row, col)->R*19595 + \
                             __array1D(src->pBuffer, src->width, row, col)->G*38469 + \
                             __array1D(src->pBuffer, src->width, row, col)->B*7472 )>>16;
            gray_cnt[temp]++;
        }
    }
    
    for (threshold_temp = 0; threshold_temp < 255; threshold_temp++){
        NumOf_bckPixel = 0; SumOf_bckPixel = 0;
        NumOf_objPixel = 0; SumOf_objPixel = 0;
        
        // Calculation for Background.
        for (uint8_t i = 0; i < threshold_temp; i++){
            NumOf_bckPixel += gray_cnt[i];
            SumOf_bckPixel += (i * gray_cnt[i]);
        }
        if (NumOf_bckPixel == 0)
            continue;
        AvgOf_bckPixel = SumOf_bckPixel / NumOf_bckPixel;
        
        // Calculation for object.
        NumOf_objPixel = NumOf_allPixel - NumOf_bckPixel;
        for (uint8_t i = threshold_temp; i < 255; i++){
            SumOf_objPixel += (i * gray_cnt[i]);
        }
        if (NumOf_objPixel == 0)
            continue;
        AvgOf_objPixel = SumOf_objPixel / NumOf_objPixel;
        
        //In case of overloading,calculate step by step.
        float w_bck   = (float)NumOf_bckPixel / NumOf_allPixel;
        float w_obj   = (float)NumOf_objPixel / NumOf_allPixel;
        float mu_diff = AvgOf_objPixel - AvgOf_bckPixel;

        g = w_bck * mu_diff * w_obj * mu_diff;
        if (g > g_max){
            g_max = g;
            *threshold = threshold_temp;
        }
    }
}

/*===========================================================================================================================
 > Memory Programming Reference 
============================================================================================================================*/
#ifndef M_ADR_OFFSET
#define M_ADR_OFFSET( ptr1 , ptr2 )   (size_t)((__abs(ptr2 - ptr1)) - 1)
#endif
     
#pragma pack(1)
unsigned char __VERTUAL_HEAP[ __VIRTUAL_HEAP_SIZE_BYTE ];//__attribute__((at()));
static size_t __Allocated_Bytes__  = 0;

struct __MallocNode_t{
    unsigned long            index;
    size_t                   byte;
    void*                    ptr;
    struct __MallocNode_t*   pNextNode;
}*pHeapMemoryHeadNode = NULL;

/*--------------------------------------------------------------------------------------------------------
 * Memory Node Should be odered by the member of index
 *
 *
 *    Node1     ->>   Node2       ->>     Node3             ->>      Node4       Nodes
 *    Memory1   ->>   Memory2     ->>     Memory3           ->>      Memory4     Used Memory
 *       |               |                   |                          |
 *       |               |                   |                          |
 * [ xxxxxxxxx________xxxxxxx_______xxxxxxxxxxxxxxxxxxx____________xxxxxxxxxxx________ ] Virtual Heap
 * index=0                                                                   index=32768
 *
 --------------------------------------------------------------------------------------------------------*/

void* __mallocHEAP(size_t size){
    size_t size_need       = size;
    if( __Allocated_Bytes__ + size_need > __VIRTUAL_HEAP_SIZE_BYTE )
        return NULL;
    else{
        __Allocated_Bytes__ += size_need;
        // It doesn't mean there is enough space to allocate.
    }
    
    void* ptr = NULL;
    struct __MallocNode_t* pNode     = pHeapMemoryHeadNode;
    struct __MallocNode_t* pNewNode  = (struct __MallocNode_t*)malloc(sizeof(struct __MallocNode_t));
    struct __MallocNode_t* pForeward = NULL,*pBackward = NULL;
    size_t minDist                   = __VIRTUAL_HEAP_SIZE_BYTE;
    
    pNewNode->byte      = size_need;
    pNewNode->pNextNode = NULL;
    
    // Only for test.
    for(int i=0;i<__VIRTUAL_HEAP_SIZE_BYTE;i++)
        __VERTUAL_HEAP[i] = i;
    
    // Special Condition. There isn't any allocated memory.
    if(pNode == NULL){
        pHeapMemoryHeadNode = pNewNode;
        pNewNode->index     = 0;
        ptr                 = &__VERTUAL_HEAP[pNewNode->index];
        return ptr;
    }
    
    // Search the optimal memory block for users.
    while(pNode != NULL){
        size_t size_free = 0;
        // All nodes should be ordered by the member of "index". Which means...
        // "pNode->index" is always ahead of "pNextNode->index" or there will be a problem.
        if(pNode->pNextNode != NULL){
            size_free = (pNode->pNextNode->index) - (pNode->index + pNode->byte);
        }else{
            size_free = (__VIRTUAL_HEAP_SIZE_BYTE-1) - ((pNode->index) + (pNode->byte));
        }
        if( size_free - size_need < minDist && size_free >= size_need ){
            minDist             = size_free - size_need;
            ptr                 = &__VERTUAL_HEAP[ (pNode->index + pNode->byte) ];

            pForeward           = pNode;
            pBackward           = pNode->pNextNode;
            pNewNode->index     = (pForeward->index + pForeward->byte);
            pNewNode->pNextNode = pBackward;
            pNewNode->ptr       = ptr;
        }
        // Continue to search...
        pNode = pNode->pNextNode;
    }
    
    if(ptr != NULL && pForeward != NULL && pNewNode != NULL){
        // Found enough space to allocate
        pForeward->pNextNode = pNewNode;
        pNewNode->pNextNode  = pBackward;
    }else{
        // Fail to find enough space to allocate
        free(pNewNode);
        __Allocated_Bytes__ -= size_need;
    }
    return ptr;
}

void __freeHEAP(void* ptr){
    unsigned long index = (unsigned long)((unsigned char*)ptr - __VERTUAL_HEAP);
    struct __MallocNode_t* pNode     = pHeapMemoryHeadNode;
    struct __MallocNode_t* pForeward = NULL;
    while(pNode != NULL){
        if(pNode->index == index && pNode->ptr == ptr){
            if(pForeward != NULL){
                pForeward->pNextNode = pNode->pNextNode;
                __Allocated_Bytes__ -= pNode->byte;
                free(pNode);
            }
            break;
        }
        pForeward = pNode;
        pNode     = pNode->pNextNode;
    }
}

void* __memsetWORD(void* __b,uint16_t value,size_t num){
    uint16_t* src = (uint16_t*)__b;
    if( sizeof(wchar_t) == sizeof(uint16_t) ){
        wmemset((wchar_t*)src, value, num);
    }else{
        size_t remain = num;
        (*((uint16_t*)src)) = value;
        remain--;
        while(1){
            if(num<(remain<<1)){
                memmove((src+(num-remain)),src, (num-remain)*sizeof(uint16_t));
                remain-=(num-remain);
            }else{
                memmove((src+(num-remain)),src, remain*sizeof(uint16_t));
                break;
            }
        }
    }
    return __b;
}

void* __memsetDWORD(void* __b,uint32_t value,size_t num){
    uint32_t* src = (uint32_t*)__b;
    if( sizeof(wchar_t) == sizeof(uint32_t) ){
        wmemset((wchar_t*)src, (int)value, num);
    }else{
        size_t remain = num;
        (*((uint32_t*)src)) = (uint32_t)value;
        remain--;
        while(1){
            if(num<(remain<<1)){
                memmove((src+(num-remain)),src, (num-remain)*sizeof(uint32_t));
                remain-=(num-remain);
            }else{
                memmove((src+(num-remain)),src, remain*sizeof(uint32_t));
                break;
            }
        }
    }
    return __b;
}

void* __memset_Area(void* __b,int value,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
    if(__b == NULL)
        return __b;
    
    const size_t num_objs = (xe-xs+1)*size;
    
    for(size_t y = ys;y <= ye;y++){
        size_t offset = size*(nmenb_line*y + xs);
        memset( (__b + offset) , value, num_objs );
    }
    
    return __b;
}
     
void* __memcpy_Area(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
    if (__dst == NULL){
        return __dst;
    }

    const size_t num_objs = (xe-xs+1)*size;

    for(size_t y = ys;y <= ye;y++){
        size_t offset = size*(nmenb_line*y + xs);
        memcpy( (__dst + offset) , (__src + offset), num_objs );
    }

    return __dst;
}

void* __memgrab_Area(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
    __exitReturn( __dst==NULL || __src==NULL , NULL);
    __exitReturn( xs < 0 || xe < 0 || ys < 0 || ye < 0 , NULL);

    const size_t num_objs = (xe-xs+1)*size;
    char* p = __dst;
    for(size_t y = ys;y <= ye;y++){
        size_t offset = size*(nmenb_line*y + xs);

        memmove( p , (__src+offset), num_objs );
        p += num_objs;
    }
    
    return __dst;
}


/*=====================================================================
 > Data Structure Reference
======================================================================*/
E_Status_t MAKE_FUNC( LINK_Loop , createNode     )         (__LinkLoopNode **      ptr ){
    __exitReturn(ptr==NULL, kStatus_BadAccess);
  
    *ptr =  (__LinkLoopNode*)__malloc(sizeof(__LinkLoopNode));
    if(*ptr == NULL)
        return kStatus_NoSpace;

    return kStatus_Success;
}
      
E_Status_t MAKE_FUNC( LINK_Loop , createHeadNode )         (__LinkLoopNode **      ptr ){
    __LinkLoopNode* pNode = (__LinkLoopNode*)__malloc(sizeof(__LinkLoopNode));
    *ptr = pNode;
  
    if( pNode == NULL )
        return kStatus_NoSpace;

    __SET_STRUCT_MB(__LinkLoopNode,void*       ,pNode,object,NULL );
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNode,pNext ,pNode);
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNode,pPrev ,pNode);

    // Same Effect: pNode->object = NULL;
    // Same Effect: pNode->pNext  = pNode;  // But to cope with <const>.
    // Same Effect: pNode->pPrev  = pNode;  // But to cope with <const>.
    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , addNode_tail   )         (__LinkLoopNode *const* ppHeadNode ,__LinkLoopNode *const* ppNewNode){
  __exitReturn(  ppHeadNode == NULL ||  ppNewNode == NULL , kStatus_BadAccess);
  __exitReturn( *ppHeadNode == NULL || *ppNewNode == NULL , kStatus_BadAccess);
  
  const __LinkLoopNode* pHeadNode = *ppHeadNode;
  const __LinkLoopNode* pNewNode  = *ppNewNode;
  // Check whether it was already exist.
  const __LinkLoopNode* pTmp = pHeadNode;
  do{
      if( pTmp == pNewNode )
          return kStatus_Exist;
      pTmp = pTmp->pNext;
  }while( pTmp != pHeadNode );
  // Every thing is OK.
  
  // Things to do for the new Node.
  __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNewNode        ,pPrev,pHeadNode->pPrev   );
  __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNewNode        ,pNext,pHeadNode          );

  // Things to do for the neighbour.
  __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pHeadNode->pPrev,pNext,pNewNode           );
  __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pHeadNode       ,pPrev,pNewNode           );
  
  // Same Effect: pNewNode->pPrev = pHeadNode->pPrev; // But to cope with <const>.
  // Same Effect: pNewNode->pNext = pHeadNode;        // But to cope with <const>.
  
  // Same Effect: pHeadNode->pPrev->pNext = pNewNode; // But to cope with <const>.
  // Same Effect: pHeadNode->pPrev        = pNewNode; // But to cope with <const>.
  
  return kStatus_Success;
}
      
E_Status_t MAKE_FUNC( LINK_Loop , addNode_tail_newhead  )  (__LinkLoopNode **      ppHeadNode ,__LinkLoopNode *const* ppNewNode){
  
    E_Status_t state = MAKE_FUNC( LINK_Loop , addNode_tail   )(ppHeadNode, ppNewNode);
    __exitReturn(state != kStatus_Success, state);
    
    // New Head
    *ppHeadNode = *ppNewNode;

    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , addNode_front         )  (__LinkLoopNode *const* ppHeadNode ,__LinkLoopNode *const* ppNewNode){
    __exitReturn(  ppHeadNode == NULL ||  ppNewNode == NULL , kStatus_BadAccess);
    __exitReturn( *ppHeadNode == NULL || *ppNewNode == NULL , kStatus_BadAccess);
    
    const __LinkLoopNode* pHeadNode = *ppHeadNode;
    const __LinkLoopNode* pNewNode  = *ppNewNode;
    // Check whether it was already exist.
    const __LinkLoopNode* pTmp = pHeadNode;
    do{
        if( pTmp == pNewNode )
            return kStatus_Exist;
        pTmp = pTmp->pNext;
    }while( pTmp != pHeadNode );
    // Every thing is OK.
    
    // Things to do for the new Node.
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNewNode        ,pPrev,pHeadNode          );
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNewNode        ,pNext,pHeadNode->pNext   );
  
    // Things to do for the neighbour.
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pHeadNode->pNext,pPrev,pNewNode           );
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pHeadNode       ,pNext,pNewNode           );
    
    // Same Effect: pNewNode->pPrev = pHeadNode;        // But to cope with <const>.
    // Same Effect: pNewNode->pNext = pHeadNode->pNext; // But to cope with <const>.
    
    // Same Effect: pHeadNode->pNext->pPrev = pNewNode; // But to cope with <const>.
    // Same Effect: pHeadNode->pNext        = pNewNode; // But to cope with <const>.
    
    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , addNode_front_newhead )  (__LinkLoopNode **      ppHeadNode ,__LinkLoopNode *const* ppNewNode){
    E_Status_t state = MAKE_FUNC(LINK_Loop , addNode_front)(ppHeadNode, ppNewNode);
    __exitReturn(state!=kStatus_Success, state);
    
    // New Head
    *ppHeadNode = *ppNewNode;

    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , findNode              )  (__LinkLoopNode *const* ppHeadNode ,__LinkLoopNode *const* ppTarget ){
    __exitReturn(  ppHeadNode == NULL ||  ppTarget == NULL , kStatus_BadAccess);
    const __LinkLoopNode* pHeadNode = *ppHeadNode;
    const __LinkLoopNode* pTarget   = *ppTarget;
    __exitReturn(pHeadNode==NULL, kStatus_BadAccess);
    __exitReturn(pTarget==NULL  , kStatus_NotFound);
    
    const __LinkLoopNode* pTmp  = pHeadNode;
    
    do{
        if (pTmp == pTarget) {
            return kStatus_Success;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHeadNode );
    return kStatus_NotFound;
}

E_Status_t MAKE_FUNC( LINK_Loop , checkLoopNode         )  (__LinkLoopNode *const* ppHeadNode){
    __exitReturn(ppHeadNode == NULL , kStatus_BadAccess);
    __LinkLoopNode* pHeadNode = *ppHeadNode;
    __exitReturn(pHeadNode == NULL  , kStatus_BadAccess);
    const __LinkLoopNode* pFast = pHeadNode;
    const __LinkLoopNode* pSlow = pHeadNode;
  
    // Search the entire chain. o(n)  :-)
    while(pSlow->pNext != pHeadNode){
        pSlow = pSlow->pNext;
        pFast = pFast->pNext->pNext;
        if( pSlow==pFast )
            return kStatus_Exist;
    }
    
    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , deleteNode            )  (__LinkLoopNode *const* ppHeadNode ,__LinkLoopNode **      ppTarget ){
    E_Status_t state = MAKE_FUNC(LINK_Loop , removeNode)(ppHeadNode, ppTarget);
    __exitReturn(state!=kStatus_Success , state             );
    
    __LinkLoopNode* pTarget   = *ppTarget;
    __free(pTarget);  // You should release anything in this node before deleting it.
    *ppTarget = NULL;
    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , removeNode            )  (__LinkLoopNode *const* ppHeadNode ,__LinkLoopNode *const* ppTarget ){
    __exitReturn( ppHeadNode==NULL || ppTarget==NULL,kStatus_BadAccess );
    __LinkLoopNode* pHeadNode = *ppHeadNode;
    __LinkLoopNode* pTarget   = *ppTarget;
    __exitReturn( pHeadNode==NULL||pTarget==NULL    , kStatus_BadAccess);
    __exitReturn( pHeadNode==pTarget                ,kStatus_Denied    );
    
    E_Status_t state = MAKE_FUNC( LINK_Loop,findNode)(ppHeadNode,ppTarget);
    __exitReturn(state != kStatus_Success           ,state             );
  
    // Connect the neighbour and isolate the <pTarget>.
    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTarget->pPrev, pNext, pTarget->pNext);
    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTarget->pNext, pPrev, pTarget->pPrev);
    // Same Effect: pTarget->pPrev->pNext = pTarget->pNext; // But to cope with <const>.
    // Same Effect: pTarget->pNext->pPrev = pTarget->pPrev; // But to cope with <const>.
    
    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTarget, pNext, NULL);
    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTarget, pPrev, NULL);
    // Same Effect: pTarget->pNext = NULL; // But to cope with <const>.
    // Same Effect: pTarget->pPrev = NULL; // But to cope with <const>.
    
    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , removeAllNodes        )  (__LinkLoopNode *const* ppHeadNode){
    __exitReturn(ppHeadNode==NULL, kStatus_BadAccess);
    
    E_Status_t state = MAKE_FUNC(LINK_Loop,checkLoopNode)(ppHeadNode);
    __exitReturn(state!=kStatus_Success ,state            );
    
    __LinkLoopNode* pHeadNode = *ppHeadNode;
    __LinkLoopNode* pTmpCur  = (__LinkLoopNode*)(pHeadNode->pNext);
    __LinkLoopNode* pTmpNxt  = (__LinkLoopNode*)(pTmpCur->pNext);
    while(pTmpCur != pHeadNode){
//        pTmpCur->pNext  = NULL;
//        pTmpCur->pPrev  = NULL;
        __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmpCur, pNext, NULL);
        __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmpCur, pPrev, NULL);
        pTmpCur = pTmpNxt;
        pTmpNxt = (__LinkLoopNode*)(pTmpNxt->pNext);
    }
  
    
    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pHeadNode, pNext, pHeadNode);
    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pHeadNode, pPrev, pHeadNode);
//    pHeadNode->pNext  = pHeadNode;
//    pHeadNode->pPrev  = pHeadNode;
  
    return kStatus_Success;
}

E_Status_t MAKE_FUNC( LINK_Loop , printAllNodesAdr      )  (__LinkLoopNode *const* ppHeadNode,int(*PRINTF_FUNC)(const char*,...)){
  
    __exitReturn(ppHeadNode == NULL, kStatus_BadAccess);
    
    const __LinkLoopNode* pHeadNode = *ppHeadNode;
    const __LinkLoopNode* pTmp      = pHeadNode;
    size_t cnt = 0;
    do{
        (*PRINTF_FUNC)("NODE[%d]: %p\n",cnt,pTmp);
        cnt++;
        pTmp = pTmp->pNext;
    }while( pTmp != pHeadNode );
        
    return kStatus_Success;
}
      
      
      
#define MAX_CHARLOG_PER_TIME 100

static const char** __message_buffer = NULL;

static size_t                 msgCnt = 0;

static char __dummy_message_buffer[MAX_CHARLOG_PER_TIME] = {0};
void __logMessage(const char* format,...){
    const char** p = (const char**)malloc((msgCnt+1)*sizeof(void*)); // 重新建指针数组
    va_list arg;
    va_start(arg, format);
    
    size_t len = vsprintf(__dummy_message_buffer, format, arg);      // 计算本次message字符个数
    
    if( __message_buffer != NULL){       
        memmove(p, __message_buffer, msgCnt*sizeof(const char*));    // 拷贝之前存储的指针
        free(__message_buffer);
    }
    
    char* temp = (char*)malloc(len);                                
    strncpy(temp,__dummy_message_buffer,len);                        // 拷贝内容
    p[msgCnt] = temp;
    
    va_end(arg);

    msgCnt++;
    __message_buffer = p;
}
     
void __deleteMessage(void){
    
}

void __showMessage( int(*PRINTF_METHOD)(const char* ,...)  ){
    __exit( __message_buffer == NULL );
    
}
      
      
#ifdef __cplusplus
}
#endif
     
#if 0
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
#endif

