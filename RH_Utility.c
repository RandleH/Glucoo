/*===========================================================================================================================
 > Includes
============================================================================================================================*/
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>
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
     
/*===========================================================================================================================
 > Algebra Reference 
============================================================================================================================*/

long __sign(long x){
    return (x>=0)?(1):(-1);
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

__ImageRGB888_t* __Filter_Gray_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst){
    
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

__ImageRGB888_t* __Filter_Warm_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst){
    return dst;
}

__ImageRGB888_t* __Filter_Cold_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst){
    
    return dst;
}

__ImageRGB888_t* __Filter_OTUS_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst){
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

__ImageRGB888_t* __Blur_Gussian_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,unsigned int _0_65535_){
    static __Kernel_t gus_kernel = {
        .pBuffer = NULL,
        .order   = 0,
        .sum     = 0,
    };
    static unsigned int old_value = 0;
    
    if( old_value != _0_65535_ ){
        if( gus_kernel.pBuffer != NULL ){
            __free( gus_kernel.pBuffer );
        }
        double sigma  = __map(_0_65535_, 0, 65535, 0.0, 10.0); // convert a normal value to sigma
        size_t order  = lround(sigma*6); // 6 times sigma includes 99% area.
        gus_kernel.pBuffer = (uint16_t*)__malloc( order*order*sizeof(uint16_t) );
        
        if((order & 0x01) == 0) // order should be an odd number.
            order--;
        if(order>=31) // too big!!!
            order = 31;
        __gussianKernel(sigma,order,&gus_kernel);
    }
    
    __ImageRGB888_t* pImg = __Conv2D_ImgRGB888(src, dst, &gus_kernel);
    
    old_value = _0_65535_;
    return pImg;

}

__ImageRGB888_t* __Blur_Average_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,unsigned int _0_65535_){
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

__ImageRGB565_t* __Conv2D_ImgRGB565(const __ImageRGB565_t* src,__ImageRGB565_t* dst,const __Kernel_t* k){
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
                (dst->pBuffer+offset)->R = (div==0)?((1<<5)-1):(tmp_R/div);
                (dst->pBuffer+offset)->G = (div==0)?((1<<6)-1):(tmp_G/div);
                (dst->pBuffer+offset)->B = (div==0)?((1<<5)-1):(tmp_B/div);
            }
        }
    }
    
    return dst;
}

__ImageRGB888_t* __Conv2D_ImgRGB888(const __ImageRGB888_t* src,__ImageRGB888_t* dst,const __Kernel_t* k){
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
                (dst->pBuffer+offset)->R = (div==0)?((1<<8)-1):(tmp_R/div);
                (dst->pBuffer+offset)->G = (div==0)?((1<<8)-1):(tmp_G/div);
                (dst->pBuffer+offset)->B = (div==0)?((1<<8)-1):(tmp_B/div);
            }
        }
    }
    
    return dst;
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

