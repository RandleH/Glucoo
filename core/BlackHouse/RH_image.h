#ifndef _RH_IMAGE_H
#define _RH_IMAGE_H

#include "RH_common.h"
#include "RH_lib.h"
#include "RH_math.h"
#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================================================================
 > Image Processing Reference
============================================================================================================================*/
typedef uint8_t __PixelBIN_t;
union __UNION_PixelBIN_t{
    struct{
        uint8_t BIT0 : 1;
        uint8_t BIT1 : 1;
        uint8_t BIT2 : 1;
        uint8_t BIT3 : 1;
        uint8_t BIT4 : 1;
        uint8_t BIT5 : 1;
        uint8_t BIT6 : 1;
        uint8_t BIT7 : 1;
    };
    uint8_t data;
};
typedef union __UNION_PixelBIN_t __UNION_PixelBIN_t;

struct __PixelRGB565_t{
    uint16_t B : 5;
    uint16_t G : 6;
    uint16_t R : 5;
};
union __UNION_PixelRGB565_t{
    struct{
        uint16_t B : 5;
        uint16_t G : 6;
        uint16_t R : 5;
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

struct __ImageBIN_t{
    __UNION_PixelBIN_t*    pBuffer;
    size_t      width;
    size_t      height;
};
typedef struct __ImageBIN_t  __ImageBIN_t;

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

__ImageBIN_t*    MAKE_FUNC( ImgBIN    , create       ) (size_t width,size_t height);
__ImageBIN_t*    MAKE_FUNC( ImgBIN    , load_bmp     ) (const char* __restrict__ path);
__ImageBIN_t*    MAKE_FUNC( ImgBIN    , out_bmp      ) (const char* __restrict__ path,__ImageBIN_t* p);

__ImageBIN_t*    MAKE_FUNC( ImgBIN    , copy         ) (const __ImageBIN_t* src,__ImageBIN_t* dst);




__ImageRGB565_t* MAKE_FUNC( ImgRGB565 , create       ) (size_t width,size_t height);//
__ImageRGB565_t* MAKE_FUNC( ImgRGB565 , load_bmp     ) (const char* __restrict__ path);//
__ImageRGB565_t* MAKE_FUNC( ImgRGB565 , out_bmp      ) (const char* __restrict__ path,__ImageRGB565_t* p);//

__ImageRGB565_t* MAKE_FUNC( ImgRGB565 , copy         ) (const __ImageRGB565_t* src,__ImageRGB565_t* dst);//
__ImageRGB565_t* MAKE_FUNC( ImgRGB565 , conv2D       ) (const __ImageRGB565_t* src,__ImageRGB565_t* dst,const __Kernel_t* k,uint16_t br_100);




__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , create       ) (size_t width,size_t height);
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , load_bmp     ) (const char* __restrict__ path);
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , load_png     ) (const char* __restrict__ path);//
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , out_bmp      ) (const char* __restrict__ path,__ImageRGB888_t* p);

__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , copy         ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst);
void             MAKE_FUNC( ImgRGB888 , free         ) (      __ImageRGB888_t* ptr);
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , free_buffer  ) (      __ImageRGB888_t* ptr);
 
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , filter_gray  ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100);
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , filter_cold  ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100);//
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , filter_warm  ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100);//
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , filter_OTUS  ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100);

__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , trans_mirror ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint8_t HV);

__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , blur_gussian ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,__Area_t* area,uint32_t radSize, uint16_t br_100);
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , blur_average ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,__Area_t* area,uint32_t radSize, uint16_t br_100);
__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , blur_fast    ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,__Area_t* area,uint32_t radSize, uint16_t br_100);//


__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , insert_NstNeighbor ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,size_t height,size_t width);

__ImageRGB888_t* MAKE_FUNC( ImgRGB888 , conv2D       ) (const __ImageRGB888_t* src,__ImageRGB888_t* dst,const __Kernel_t* k,uint16_t br_100);

void             MAKE_FUNC( ImgRGB888 , data_OTUS    ) (const __ImageRGB888_t* src,uint32_t* threshold);


#ifdef __cplusplus
}
#endif

#endif
