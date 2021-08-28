#ifndef _BLK_GRAPHIC_H
#define _BLK_GRAPHIC_H

#include "RH_common.h"
#include "RH_config.h"
#include "RH_color.h"
#include "BLK_image.h"
#include "BLK_math.h"

#ifdef __cplusplus
extern "C" {
#endif


#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
typedef BLK_SRCT(ImgBin)       BLK_TYPE(Canvas);
typedef BLK_TYPE(PixelBin)     BLK_TYPE(Pixel);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
typedef BLK_SRCT(Img565)       BLK_TYPE(Canvas);
typedef BLK_TYPE(Pixel565)     BLK_TYPE(Pixel);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
typedef BLK_SRCT(Img888)       BLK_TYPE(Canvas);
typedef BLK_TYPE(Pixel888)     BLK_TYPE(Pixel);
#else
  #error "[RH_graphic]: Unknown color type."
#endif

typedef enum{
    kApplyPixel_mark    ,
    kApplyPixel_unmark  ,
    kApplyPixel_fill    ,
    kApplyPixel_light   ,
    kApplyPixel_depix   ,
    kApplyPixel_reverse ,
    kApplyPixel_pick    ,
    kApplyPixel_blur    ,
    kApplyPixel_eor     ,
    NUM_kApplyPixel
}BLK_ENUM(DrawMethod);

typedef enum{
    kBLK_RenderMethod_mark    ,
    kBLK_RenderMethod_unmark  ,
    kBLK_RenderMethod_fill    ,
    kBLK_RenderMethod_light   ,
    kBLK_RenderMethod_depix   ,
    kBLK_RenderMethod_reverse ,
    kBLK_RenderMethod_pick    ,
    kBLK_RenderMethod_blur    ,
    kBLK_RenderMethod_eor     ,
    NUM_kBLK_RenderMethod
}BLK_ENUM(RenderMethod);

typedef enum{
    kBLK_ColorDepth_1Bit  ,
    kBLK_ColorDepth_8Bit  ,
    kBLK_ColorDepth_16Bit ,
    kBLK_ColorDepth_24Bit ,
    kBLK_ColorDepth_32Bit ,
    NUM_kBLK_ColorDepth   ,
}BLK_ENUM(ColorDepth);

E_Status_t      BLK_FUNC( Graph , init              ) (void);
void            BLK_FUNC( Graph , set_penSize       ) (size_t         penSize      );
void            BLK_FUNC( Graph , set_penOpaque     ) (uint8_t        opaque       );
void            BLK_FUNC( Graph , set_penColor      ) (uint32_t       penColor     );
void            BLK_FUNC( Graph , set_blurSize      ) (size_t         size_0_65535 );
void            BLK_FUNC( Graph , set_blurBr        ) (size_t         br_100       );
void            BLK_FUNC( Graph , set_color_depth   ) (BLK_ENUM(ColorDepth)   depth  );
void            BLK_FUNC( Graph , set_render_method ) (BLK_ENUM(RenderMethod) method );
 
BLK_TYPE(Pixel) BLK_FUNC( Graph , get_penColor      ) (void);
size_t          BLK_FUNC( Graph , get_penSize       ) (void);
size_t          BLK_FUNC( Graph , get_blurSize      ) (void);
size_t          BLK_FUNC( Graph , get_blurBr        ) (void);
  
void            BLK_FUNC( Graph , backupCache       ) (void);
void            BLK_FUNC( Graph , restoreCache      ) (void);

typedef void (*F_Render)(int x, int y, void* pIMG);


 
E_Status_t      BLK_FUNC( Graph , circle_raw        ) (int x ,int y ,int d ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_edged      ) (int x ,int y ,int d ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_fill       ) (int x ,int y ,int d ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt1_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt2_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt3_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt4_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt1_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt2_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt3_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , circle_qrt4_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback );
 
E_Status_t      BLK_FUNC( Graph , rect_raw          ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , rect_edged        ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , rect_fill         ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , rect_round_fill   ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , rect_round_raw    ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , EX_rect_raw       ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , EX_rect_edged     ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , EX_rect_fill      ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , EX_rect_round_fill) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , EX_rect_round_raw ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback );
 
E_Status_t      BLK_FUNC( Graph , line_raw          ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , line_edged        ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , line_fill         ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , line_sausage      ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback );
 
 
E_Status_t      BLK_FUNC( Graph , quad_raw          ) (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , quad_fill         ) (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,void* pIMG, F_Render RH_NULLABLE callback );
 
E_Status_t      BLK_FUNC( Graph , capsule_raw       ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , capsule_fill      ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback );

E_Status_t      BLK_FUNC( Graph , triangle_raw      ) (int x1,int y1,int x2,int y2,int x3,int y3, void*pIMG, F_Render RH_NULLABLE callback );
E_Status_t      BLK_FUNC( Graph , triangle_fill     ) (int x1,int y1,int x2,int y2,int x3,int y3, void*pIMG, F_Render RH_NULLABLE callback );//
E_Status_t      BLK_FUNC( Graph , triangle_edged    ) (int x1,int y1,int x2,int y2,int x3,int y3, void*pIMG, F_Render RH_NULLABLE callback );//

#ifdef __cplusplus
}
#endif

#endif
