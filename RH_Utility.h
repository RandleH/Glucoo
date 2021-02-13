#ifndef RH_UTILITY_H
#define RH_UTILITY_H 

#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define SHOW_BUG 0

/*===========================================================================================================================
> Common
============================================================================================================================*/
#ifndef M_2_SQRTPI
#define M_2_SQRTPI  1.12837916709551257389615890312154517   /* 2/sqrt(pi)     */
#endif

#ifndef M_SQRT2
#define M_SQRT2     1.41421356237309504880168872420969808   /* sqrt(2)        */
#endif
 
#ifndef M_2_PI 
#define M_2_PI      6.28318530717958623199592693708837032   /* 2*pi           */
#endif  

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#endif

#ifndef M_PI_2
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#endif

#ifndef M_PI_4
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#endif
 
#define __map(val,i_min,i_max,o_min,o_max)   (double)( ( ((double)o_max)*(((double)val)-((double)i_min))+((double)o_min)*((double)(i_max)-(double)(val)) )/((double)(i_max)-(double)(i_min)) )

#define __abs(val)                           (((val)>0)?(val):(-(val)))
#define __limit(a, lowerbound, upperbound)   (((a) >= (upperbound)) ? upperbound : (((a) <= (lowerbound)) ? (lowerbound) : (a) ))

#ifndef __min
#define __min(a,b)                           (((a)<(b))?(a):(b))
#endif

#ifndef __max
#define __max(a,b)                           (((a)>(b))?(a):(b))
#endif

#ifndef __mid 
#define __mid(a,b)                           (((a)<(b))?((a)+(((b)-(a)+1)>>1)):((b)+(((a)-(b)+1)>>1)) )
#endif
 
#ifndef __exit
#define __exit(express)                      if( express )   return
#endif

#ifndef __exitReturn
#define __exitReturn(express,res)            if( express )   return res
#endif
 
typedef enum{
    kStatus_Success ,
    kStatus_Error   ,
}B_Status_t;

#pragma anon_unions
 
/*===========================================================================================================================
> Standard
============================================================================================================================*/
uint8_t     __swap_8BIT   (uint8_t   x);
uint16_t    __swap_16BIT  (uint16_t  x);
uint32_t    __swap_32BIT  (uint32_t  x);
uint32_t    __swap_nBIT   (uint32_t  x, size_t n);
uint32_t    __swap_DATA   (uint32_t  x);
 
size_t      __sizeof_BITs (uint32_t  x);
size_t      __sizeof_OCTs (uint32_t  x);
size_t      __sizeof_DECs (uint32_t  x);
size_t      __sizeof_HEXs (uint32_t  x);
 
uint32_t    __Bin2Gray    (uint32_t  x);
uint32_t    __Gray2Bin    (uint32_t  x); //


/*===========================================================================================================================
 > Algebra Reference 
============================================================================================================================*/
long    __sign       (long   x);
long    __step       (long   x);
long    __sqrt       (long   x);
double  __sigmold    (double x);
double  __gussian    (long   x,long __miu  ,double __sigma);
double  __gussian2D  (long   x,long y      ,double __sigma);

struct __Kernel_t{
    uint16_t*   pBuffer; //  <- This buffer array should only be created by "__malloc".
    size_t      order;
    int32_t     sum;
};
typedef struct __Kernel_t       __Kernel_t;
__Kernel_t* __gussianKernel(double __sigma,size_t order,__Kernel_t* pKernel);
 
long    __step_mul   (long   x);

 
/*=====================================================================
 > Quantity Reference 
======================================================================*/
struct IntArray_t{
	size_t  index;
	int     value;
};
typedef struct IntArray_t IntArray_t;
IntArray_t __findMax_INT(const int* pValue,size_t num);
IntArray_t __findMin_INT(const int* pValue,size_t num);

struct UintArray_t{
	size_t        index;
	unsigned int  value;
};
typedef struct UintArray_t UintArray_t;

 /*===========================================================================================================================
 > Geometry Reference 
=============================================================================================================================*/
struct Vector2D_t{
	int x;
	int y;
};
typedef struct Vector2D_t Vector2D_t;
typedef struct Vector2D_t Point2D_t;

struct Vector3D_t{
	int x;
	int y;
	int z;
};
typedef struct Vector3D_t Vector3D_t;
typedef struct Vector3D_t Point3D_t;

Point3D_t __findPoint_LineCross        (const Point3D_t  line1[2] ,const Point3D_t  line2[2]);
Point3D_t __findPoint_VectorDistance   (const Point3D_t* A        ,const Point3D_t* B     ,int    dist_AP ); 
Point3D_t __findPoint_VectorProportion (const Point3D_t* A        ,const Point3D_t* B     ,double scale   );


int        __Vect2D_Dot    (const Vector2D_t* vect1,const Vector2D_t* vect2);
int        __Vect3D_Dot    (const Vector3D_t* vect1,const Vector3D_t* vect2);
Vector3D_t __Vect3D_Cross  (const Vector3D_t* vect1,const Vector3D_t* vect2);


int        __Dir_Line        (int xs,int ys,int xe,int ye);
int        __Point_toLine    (int xs,int ys,int xe,int ye,               int px,int py);
int        __Point_toTriangle(int x1,int y1,int x2,int y2,int x3,int y3, int px,int py);
int        __Point_toCircle  (int xc,int yc,int radius,                  int px,int py);

/*===========================================================================================================================
 > DSP Reference
============================================================================================================================*/
 struct __ComplexFLOAT_t{
     float_t  real;
     float_t  imag;
 };
 typedef struct __ComplexFLOAT_t __ComplexFLOAT_t;

 struct __ComplexINT_t{
     long  real;
     long  imag;
 };
 typedef struct __ComplexINT_t __ComplexINT_t;
  
void      __rDFT_Float    (const float*            src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void      __cDFT_Float    (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void      __cFFT_Float    (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t fftLen);
void      __rIDFT_Float   (const float*            src, float_t* dst_m, float complex*    dst_c, size_t dftLen);
void      __cIDFT_Float   (const float complex*    src, float_t* dst_m, float complex*    dst_c, size_t dftLen);

/*===========================================================================================================================
 > Image Processing Reference 
============================================================================================================================*/

struct __PixelRGB565_t{
    uint16_t B : 5;
    uint16_t G : 6;
    uint16_t R : 5;
};
union __UNION_PixelRGB565_t{
    struct{
        uint8_t B : 5;
        uint8_t G : 6;
        uint8_t R : 5;
    };
    uint16_t data;
};
typedef struct  __PixelRGB565_t         __PixelRGB565_t;
typedef union   __UNION_PixelRGB565_t   __UNION_PixelRGB565_t;

 struct __PixelRGB888_t{
     uint8_t B ;
     uint8_t G ;
     uint8_t R ;
 };
union __UNION_PixelRGB888_t{
    struct{
        uint8_t B : 8;
        uint8_t G : 8;
        uint8_t R : 8;
    };
    uint32_t data;
};
typedef struct  __PixelRGB888_t         __PixelRGB888_t;
typedef union   __UNION_PixelRGB888_t   __UNION_PixelRGB888_t;

struct __ImageRGB565_t{
    __UNION_PixelRGB565_t* pBuffer;
    size_t      width;
    size_t      height;
};
typedef struct __ImageRGB565_t  __ImageRGB565_t;
 

struct __ImageRGB888_t{
    __UNION_PixelRGB888_t* pBuffer;
    size_t      width;
    size_t      height;
};
typedef struct __ImageRGB888_t  __ImageRGB888_t;

__ImageRGB888_t* __LoadBMP_ImgRGB888             (const char* __restrict__ path);
__ImageRGB888_t* __OutBMP_ImgRGB888              (const char* __restrict__ path,__ImageRGB888_t* p);
__ImageRGB888_t* __Create_ImgRGB888              (size_t width,size_t height);
__ImageRGB888_t* __CopyBMP_ImgRGB888             (const __ImageRGB888_t* src,__ImageRGB888_t* dst);
__ImageRGB888_t* __FreeBuffer_ImgRGB888          (__ImageRGB888_t* ptr);
void             __Free_ImgRGB888                (__ImageRGB888_t* ptr);

__ImageRGB888_t* __Filter_Gray_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst); //
__ImageRGB888_t* __Filter_Cold_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst); //
__ImageRGB888_t* __Filter_Warm_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst); //
__ImageRGB888_t* __Filter_OTUS_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst); //
 
__ImageRGB888_t* __Trans_Mirror_ImgRGB888        (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint8_t HV);

__ImageRGB888_t* __Blur_Gussian_ImgRGB888        (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint16_t radSize, uint16_t br_100);
__ImageRGB888_t* __Blur_Average_ImgRGB888        (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint16_t radSize, uint16_t br_100);

__ImageRGB888_t* __Interpo_NstNeighbor_ImgRGB888 (const __ImageRGB888_t* src,__ImageRGB888_t* dst,size_t height,size_t width); //

__ImageRGB565_t* __Conv2D_ImgRGB565              (const __ImageRGB565_t* src,__ImageRGB565_t* dst,const __Kernel_t* k,uint16_t br_100);
__ImageRGB888_t* __Conv2D_ImgRGB888              (const __ImageRGB888_t* src,__ImageRGB888_t* dst,const __Kernel_t* k,uint16_t br_100);


/*=====================================================================
 > Memory Programming Reference 
======================================================================*/
#define __malloc(x)                    malloc(x)  //__mallocHEAP(x)
#define __free(x)                      free(x)//__freeHEAP(x)

#define __MEM_BYTE( adr )              ( (*( (uint8_t* )(adr) )) )
#define __MEM_WORD( adr )              ( (*( (uint16_t*)(adr) )) )
 
#define __PTR_BYTE( var )              ( (uint8_t* ) (void* ) (&(var)) )
#define __PTR_WORD( var )              ( (uint8_t* ) (void* ) (&(var)) )

#define __WORD_HI( var )               ( (uint8_t)( (uint16_t)(var) >> 8   ) )
#define __WORD_LO( var )               ( (uint8_t)( (uint16_t)(var) & 0xff ) )

#define __RND4 ( x )                   ( ( ((x)+3)  >>2 )<<2 )
#define __RND8 ( x )                   ( ( ((x)+7)  >>3 )<<3 )
#define __RND16( x )                   ( ( ((x)+15) >>4 )<<4 )

#define __UPCASE( c )                  ( ((c) >= 'a' && (c) <= 'z') ? ((c)-0x20) : (c) )

#define __INC_SAT( val )               ( ( ((val)+1) > (val) ) ? ((val)+1) : (val) )
 
#define __SET_STRUCT_MB( s_type, var_type, s_ptr, s_mem, val )   *( (var_type*) ( ((unsigned char*)(s_ptr))+(offsetof(s_type, s_mem)) ) ) = (var_type)(val)

#define __IN_BYTE  ( port )            ( *((volatile uint8_t*  )(port)) )
#define __IN_WORD  ( port )            ( *((volatile uint16_t* )(port)) )
#define __IN_DWORD ( port )            ( *((volatile uint32_t* )(port)) )

#define __OUT_BYTE  ( port, val )      ( *((volatile uint8_t*  )(port)) = ((uint8_t )(val)) )
#define __OUT_WORD  ( port, val )      ( *((volatile uint16_t* )(port)) = ((uint16_t)(val)) )
#define __OUT_DWORD ( port, val )      ( *((volatile uint32_t* )(port)) = ((uint32_t)(val)) )

#define __VIRTUAL_HEAP_SIZE_BYTE        (0)
#define __MESSAGE_PER_MAXSIZE_BYTE         (255)
 
void* __mallocHEAP(size_t size);
void  __freeHEAP(void* ptr);

void* __memsetWORD  (void* __b, uint16_t value, size_t num);
void* __memsetDWORD (void* __b, uint32_t value, size_t num);

void* __memset_Area (void*                __b,int                      value,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);
void* __memcpy_Area (void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);
void* __memgrab_Area(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);

struct __AnyNode_t{
    void*   object;
    const int           ID;
    const struct __AnyNode_t* pNext;
    const struct __AnyNode_t* pPrev;
};
typedef struct __AnyNode_t __AnyNode_t;

__AnyNode_t* __createNode       (void);
__AnyNode_t* __createHeadNode   (void);
void         __addNode          (__AnyNode_t* pHeadNode ,__AnyNode_t* pNode);
void         __deleteNode       (__AnyNode_t* pHeadNode ,__AnyNode_t* pNode);
void         __deleteAllNodes   (__AnyNode_t* pHeadNode);
 
 
void __logMessage     (const char* format,...);
void __deleteMessage  (void);
void __showMessage    (int(*PRINTF_METHOD)(const char* ,...));
 
#ifdef __cplusplus
}
#endif

#endif

