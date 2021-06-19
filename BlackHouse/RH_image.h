#ifndef _RH_IMAGE_H
#define _RH_IMAGE_H

#include "RH_common.h"
#include "RH_math.h"
#ifdef __cplusplus
extern "C" {
#endif

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

__ImageRGB888_t* __Filter_Gray_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100); //
__ImageRGB888_t* __Filter_Cold_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100); //
__ImageRGB888_t* __Filter_Warm_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100); //
__ImageRGB888_t* __Filter_OTUS_ImgRGB888         (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100); //
 
__ImageRGB888_t* __Trans_Mirror_ImgRGB888        (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint8_t HV);

__ImageRGB888_t* __Blur_Gussian_ImgRGB888        (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t radSize, uint16_t br_100);
__ImageRGB888_t* __Blur_Average_ImgRGB888        (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t radSize, uint16_t br_100);

__ImageRGB888_t* __Interpo_NstNeighbor_ImgRGB888 (const __ImageRGB888_t* src,__ImageRGB888_t* dst,size_t height,size_t width); //

__ImageRGB565_t* __Conv2D_ImgRGB565              (const __ImageRGB565_t* src,__ImageRGB565_t* dst,const __Kernel_t* k,uint16_t br_100);
__ImageRGB888_t* __Conv2D_ImgRGB888              (const __ImageRGB888_t* src,__ImageRGB888_t* dst,const __Kernel_t* k,uint16_t br_100);

void             __Analyze_OTUS_ImgRGB888        (const __ImageRGB888_t* src,uint32_t* threshold);


#ifdef __cplusplus
}
#endif

#endif
