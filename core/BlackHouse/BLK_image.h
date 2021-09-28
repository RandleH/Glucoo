#ifndef _BLK_IMAGE_H
#define _BLK_IMAGE_H

#include "RH_common.h"
#include "RH_color.h"
#include "BLK_lib.h"
#include "BLK_math.h"
#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================================================================
 > Image Processing Reference
============================================================================================================================*/

typedef uint32_t BLK_TYPE(Color);

union BLK_UION(PixelBin){
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
typedef uint8_t                  BLK_TYPE(PixelBin);
typedef union BLK_UION(PixelBin) BLK_UION(PixelBin);


struct BLK_SRCT(PixelGry){
    uint8_t BIT0 : 1;
    uint8_t BIT1 : 1;
    uint8_t BIT2 : 1;
    uint8_t BIT3 : 1;
    uint8_t BIT4 : 1;
    uint8_t BIT5 : 1;
    uint8_t BIT6 : 1;
    uint8_t BIT7 : 1;
};
union BLK_UION(PixelGry){
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
typedef uint8_t                   BLK_TYPE(PixelGry);
typedef struct BLK_SRCT(PixelGry) BLK_SRCT(PixelGry);
typedef union  BLK_UION(PixelGry) BLK_UION(PixelGry);


struct BLK_SRCT(Pixel565){
    uint16_t B : 5;
    uint16_t G : 6;
    uint16_t R : 5;
};
union BLK_UION(Pixel565){
    struct{
        uint16_t B : 5;
        uint16_t G : 6;
        uint16_t R : 5;
    };
    uint16_t data;
};
typedef uint16_t                     BLK_TYPE(Pixel565);
typedef struct  BLK_SRCT(Pixel565)   BLK_SRCT(Pixel565);
typedef union   BLK_UION(Pixel565)   BLK_UION(Pixel565);


struct BLK_SRCT(Pixel888){
     uint8_t B ;
     uint8_t G ;
     uint8_t R ;
 };
union BLK_UION(Pixel888){
    struct{
        uint8_t B : 8;
        uint8_t G : 8;
        uint8_t R : 8;
    };
    uint32_t data;
};
typedef uint32_t                     BLK_TYPE(Pixel888);
typedef struct  BLK_SRCT(Pixel888)   BLK_SRCT(Pixel888);
typedef union   BLK_UION(Pixel888)   BLK_UION(Pixel888);

struct BLK_SRCT(ImgBin){
    BLK_UION(PixelBin)*    ptr;
    var      w;
    var      h;
};
typedef struct BLK_SRCT(ImgBin)  BLK_SRCT(ImgBin);

struct BLK_SRCT(Img565){
    BLK_UION(Pixel565)*    ptr;
    var      w;
    var      h;
};
typedef struct BLK_SRCT(Img565)  BLK_SRCT(Img565);

struct BLK_SRCT(ImgGry){
    BLK_UION(PixelGry)*    ptr;
    var      w;
    var      h;
};
typedef struct BLK_SRCT(ImgGry) BLK_SRCT(ImgGry);
 

struct BLK_SRCT(Img888){
    BLK_UION(Pixel888)* ptr;
    var      w;
    var      h;
};
typedef struct BLK_SRCT(Img888)  BLK_SRCT(Img888);

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, create       ) (size_t width,size_t height);
BLK_SRCT(Img565)* BLK_FUNC( Img565, create       ) (var    width,var    height);
BLK_SRCT(Img888)* BLK_FUNC( Img888, create       ) (var    width,var    height);


BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, load_bmp     ) (const char* RH_RESTRICT path);
BLK_SRCT(Img565)* BLK_FUNC( Img565, load_bmp     ) (const char* RH_RESTRICT path);//
BLK_SRCT(Img888)* BLK_FUNC( Img888, load_bmp     ) (const char* RH_RESTRICT path);
BLK_SRCT(Img888)* BLK_FUNC( Img888, load_jpg     ) (const char* RH_RESTRICT path);
BLK_SRCT(Img888)* BLK_FUNC( Img888, load_png     ) (const char* RH_RESTRICT path);//

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, out_bmp      ) (const char* RH_RESTRICT path, const BLK_SRCT(ImgBin)* p);
BLK_SRCT(Img565)* BLK_FUNC( Img565, out_bmp      ) (const char* RH_RESTRICT path, const BLK_SRCT(Img565)* p);//
BLK_SRCT(Img888)* BLK_FUNC( Img888, out_bmp      ) (const char* RH_RESTRICT path, const BLK_SRCT(Img888)* p);
BLK_SRCT(Img888)* BLK_FUNC( Img888, out_png      ) (const char* RH_RESTRICT path, const BLK_SRCT(Img888)* img);

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, copy         ) (const BLK_SRCT(ImgBin)* src,BLK_SRCT(ImgBin)* dst);
BLK_SRCT(Img565)* BLK_FUNC( Img565, copy         ) (const BLK_SRCT(Img565)* src,BLK_SRCT(Img565)* dst);//
BLK_SRCT(Img888)* BLK_FUNC( Img888, copy         ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst);

BLK_SRCT(Img565)* BLK_FUNC( Img565, conv2D       ) (const BLK_SRCT(Img565)* src,BLK_SRCT(Img565)* dst,const BLK_SRCT(Kernel)* k,uint16_t br_100);
BLK_SRCT(Img888)* BLK_FUNC( Img888, conv2D       ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,const BLK_SRCT(Kernel)* k,uint16_t br_100);

void              BLK_FUNC( Img565, free         ) (      BLK_SRCT(Img565)* ptr);
BLK_SRCT(Img565)* BLK_FUNC( Img565, free_buffer  ) (      BLK_SRCT(Img565)* ptr);
void              BLK_FUNC( Img888, free         ) (      BLK_SRCT(Img888)* ptr);
BLK_SRCT(Img888)* BLK_FUNC( Img888, free_buffer  ) (      BLK_SRCT(Img888)* ptr);
 
BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_gray  ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100);
BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_cold  ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100);//
BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_warm  ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100);//
BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_OTUS  ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100);

BLK_SRCT(Img888)* BLK_FUNC( Img888, trans_mirror ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint8_t HV);

BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_gussian ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100);
BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_average ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100);
BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_fast    ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100);//


BLK_SRCT(Img888)* BLK_FUNC( Img888, insert_NstNeighbor ) (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,size_t height,size_t width);

BLK_SRCT(ImgBin)* BLK_FUNC( ImgGry, into_ImgBin  ) (const BLK_SRCT(ImgGry)* src,BLK_SRCT(ImgBin)* dst,int xs, int ys,BLK_TYPE(Color) obj_color, uint8_t br_100);
BLK_SRCT(Img565)* BLK_FUNC( ImgGry, into_Img565  ) (const BLK_SRCT(ImgGry)* src,BLK_SRCT(Img565)* dst,int xs, int ys,BLK_TYPE(Color) obj_color, uint8_t br_100);
BLK_SRCT(Img888)* BLK_FUNC( ImgGry, into_Img888  ) (const BLK_SRCT(ImgGry)* src,BLK_SRCT(Img888)* dst,int xs, int ys,BLK_TYPE(Color) obj_color, uint8_t br_100);



void              BLK_FUNC( Img888, data_OTUS    ) (const BLK_SRCT(Img888)* src,uint8_t* threshold);

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, draw_img_aurora      )( BLK_SRCT(ImgBin)* dst, const BLK_TYPE(PixelBin)* colors, size_t size );
BLK_SRCT(Img565)* BLK_FUNC( Img565, draw_img_aurora      )( BLK_SRCT(Img565)* dst, const BLK_TYPE(Pixel565)* colors, size_t size );
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_aurora      )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size );

BLK_SRCT(ImgGry)* BLK_FUNC( ImgGry, draw_img_radar       )( BLK_SRCT(ImgGry)* dst, const BLK_TYPE(PixelGry)* colors, size_t size );//
BLK_SRCT(Img565)* BLK_FUNC( Img565, draw_img_radar       )( BLK_SRCT(Img565)* dst, const BLK_TYPE(Pixel565)* colors, size_t size );//
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_radar       )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size );

BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_faded       )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size );
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_gradient_v  )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size );
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_gradient_h  )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size );
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_blur        )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size );

BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_       )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size );

BLK_SRCT(Img888)* BLK_FUNC( Img888, spy_img_blur    )( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size, const __Area_t* area );

#ifdef __cplusplus
}
#endif

#endif
