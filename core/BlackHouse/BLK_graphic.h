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
typedef __ImageBIN_t           __GraphInfo_t;
typedef uint8_t                __GraphPixel_t;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
typedef __ImageRGB565_t        __GraphInfo_t;
typedef uint16_t               __GraphPixel_t;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
typedef __ImageRGB888_t        __GraphInfo_t;
typedef uint32_t               __GraphPixel_t;
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
}E_ApplyPixel_t;

E_Status_t     MAKE_FUNC( Graph , init               ) (void);

void           MAKE_FUNC( Graph , set_penSize        ) (size_t         penSize      );
void           MAKE_FUNC( Graph , set_penColor       ) (__GraphPixel_t penColor     );
void           MAKE_FUNC( Graph , set_blurSize       ) (size_t         size_0_65535 );
void           MAKE_FUNC( Graph , set_blurBrightness ) (size_t         br_100       );

size_t         MAKE_FUNC( Graph , get_penSize        ) (void);
__GraphPixel_t MAKE_FUNC( Graph , get_penColor       ) (void);
size_t         MAKE_FUNC( Graph , get_blurSize       ) (void);
size_t         MAKE_FUNC( Graph , get_blurBrightness ) (void);

void           MAKE_FUNC( Graph , backup_config      ) (void);
void           MAKE_FUNC( Graph , restore_config     ) (void);

E_Status_t MAKE_FUNC( Graph , circle_raw        ) (int x ,int y ,int d ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_edged      ) (int x ,int y ,int d ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_fill       ) (int x ,int y ,int d ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt1_fill  ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt2_fill  ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt3_fill  ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt4_fill  ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt1_raw   ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt2_raw   ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt3_raw   ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , circle_qrt4_raw   ) (int x ,int y ,int r ,        __GraphInfo_t* pInfo, E_ApplyPixel_t method);

E_Status_t MAKE_FUNC( Graph , rect_raw          ) (int xs,int ys,int xe,int ye, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , rect_edged        ) (int xs,int ys,int xe,int ye, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , rect_fill         ) (int xs,int ys,int xe,int ye, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , rect_round        ) (int xs,int ys,int xe,int ye, __GraphInfo_t* pInfo, E_ApplyPixel_t method);

E_Status_t MAKE_FUNC( Graph , line_raw          ) (int x1,int y1,int x2,int y2, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , line_edged        ) (int x1,int y1,int x2,int y2, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , line_fill         ) (int x1,int y1,int x2,int y2, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , line_sausage      ) (int x1,int y1,int x2,int y2, __GraphInfo_t* pInfo, E_ApplyPixel_t method);


E_Status_t MAKE_FUNC( Graph , quad_raw          ) (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , quad_fill         ) (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4, __GraphInfo_t* pInfo, E_ApplyPixel_t method);

E_Status_t MAKE_FUNC( Graph , sausage_raw       ) (int xs,int ys,int xe,int ye, __GraphInfo_t* pInfo, E_ApplyPixel_t method);
E_Status_t MAKE_FUNC( Graph , sausage_fill      ) (int xs,int ys,int xe,int ye, __GraphInfo_t* pInfo, E_ApplyPixel_t method);

#ifdef __cplusplus
}
#endif

#endif
