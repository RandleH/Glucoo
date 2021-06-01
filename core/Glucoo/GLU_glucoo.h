
#ifndef _GLUCOO_H
#define _GLUCOO_H

#include <stdbool.h>
#include "RH_common.h"
#include "RH_config.h"
#include "BLK_image.h"

#ifdef __cplusplus
extern "C"{
#endif

#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
typedef BLK_SRCT(ImgBin)       GLU_SRCT(Canvas);
typedef BLK_UION(PixelBin)     GLU_UION(Pixel);
typedef BLK_TYPE(PixelBin)     GLU_TYPE(Pixel);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
typedef BLK_SRCT(Img565)       GLU_SRCT(Canvas);
typedef BLK_UION(Pixel565)     GLU_UION(Pixel);
typedef BLK_TYPE(Pixel565)     GLU_TYPE(Pixel);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
typedef BLK_SRCT(Img888)       GLU_SRCT(Canvas);
typedef BLK_UION(Pixel888)     GLU_UION(Pixel);
typedef BLK_TYPE(Pixel888)     GLU_TYPE(Pixel);
#else
  #error "[RH_gui_config]: Unknown color type."
#endif


typedef void* ID_t;

extern void (*GUI_API_DrawArea)       (int x1,int y1,int x2,int y2,const GLU_TYPE(Pixel)* pixData);
extern void (*GUI_API_DrawPixel)      (int x ,int y ,const GLU_TYPE(Pixel) pixData);
extern void (*GUI_API_DelayMs)        (unsigned long ms);
extern void (*GUI_API_AssertParam)    (bool expression,const char* WHAT_IS_WRONG );

/*===============================================================================================================
 * 定义于 [ ./GLU_glucoo.c ]
===============================================================================================================*/
void RH_PREMAIN GLU_FUNC( GUI, init )        ( void );

void GLU_FUNC( GUI, setPenSize  )            ( size_t    penSize  );
void GLU_FUNC( GUI, setPenColor )            ( GLU_TYPE(Pixel) penColor );
void GLU_FUNC( GUI, autoDisplay )            ( bool      cmd      );


void GLU_FUNC( GUI, refreashScreenArea   )   ( int xs,int ys,int xe,int ye );
void GLU_FUNC( GUI, addScreenArea        )   ( int xs,int ys,int xe,int ye );

void GLU_FUNC( GUI, refreashScreen       )   ( void );
void GLU_FUNC( GUI, refreashEntireScreen )   ( void );

bool GLU_FUNC( GUI, isAutoDisplay        )   ( void );
bool GLU_FUNC( GUI, isInternalGRAM       )   ( void );
bool GLU_FUNC( GUI, isCacheEmpty         )   ( void );


/*===============================================================================================================
 * 定义于 [ ./draw/GLU_draw.c ]
===============================================================================================================*/
void GLU_FUNC( GUI, rect_raw         )       ( int xs,int ys,int xe,int ye );
void GLU_FUNC( GUI, rect_edged       )       ( int xs,int ys,int xe,int ye );
void GLU_FUNC( GUI, rect_fill        )       ( int xs,int ys,int xe,int ye );
void GLU_FUNC( GUI, rect_round       )       ( int xs,int ys,int xe,int ye );

void GLU_FUNC( GUI, circle_raw       )       ( int x ,int y ,int d );
void GLU_FUNC( GUI, circle_edged     )       ( int x ,int y ,int d );
void GLU_FUNC( GUI, circle_fill      )       ( int x ,int y ,int d );
void GLU_FUNC( GUI, circle_qrt1_fill )       ( int x ,int y ,int r );
void GLU_FUNC( GUI, circle_qrt2_fill )       ( int x ,int y ,int r );
void GLU_FUNC( GUI, circle_qrt3_fill )       ( int x ,int y ,int r );
void GLU_FUNC( GUI, circle_qrt4_fill )       ( int x ,int y ,int r );
void GLU_FUNC( GUI, circle_qrt1_raw  )       ( int x ,int y ,int r );
void GLU_FUNC( GUI, circle_qrt2_raw  )       ( int x ,int y ,int r );
void GLU_FUNC( GUI, circle_qrt3_raw  )       ( int x ,int y ,int r );
void GLU_FUNC( GUI, circle_qrt4_raw  )       ( int x ,int y ,int r );

void GLU_FUNC( GUI, sausage_raw      )       ( int xs,int ys,int xe,int ye );
void GLU_FUNC( GUI, line_raw         )       ( int x1,int y1,int x2,int y2 );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_object.c ]
===============================================================================================================*/
#include "./object/GLU_object.h"
ID_t            RH_RESULT GLU_FUNC( Object, create   )  ( const __GUI_Object_t* config );
E_Status_t                GLU_FUNC( Object, template )  (       __GUI_Object_t* config  , E_GUI_ObjWidget_t widget );
E_Status_t                GLU_FUNC( Object, adjust   )  ( ID_t ID  , void*  dataScr, size_t dataSize );
E_Status_t                GLU_FUNC( Object, frame    )  ( ID_t ID  , bool   cmd   );
E_Status_t                GLU_FUNC( Object, insert   )  ( ID_t ID );
E_Status_t                GLU_FUNC( Object, delete   )  ( ID_t ID );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_window.c ]
===============================================================================================================*/
#include "./window/GLU_window.h"
ID_t            RH_RESULT GLU_FUNC( Window, create   )  ( const __GUI_Window_t* config );
__GUI_Window_t*           GLU_FUNC( Window, template )  (       __GUI_Window_t* config );
E_Status_t                GLU_FUNC( Window, insert   )  ( ID_t ID );
E_Status_t                GLU_FUNC( Window, delete   )  ( ID_t ID );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_menu.c ]
===============================================================================================================*/
#include "./menu/GLU_menu.h"
ID_t            RH_RESULT GLU_FUNC( Menu, create     )  ( const __GUI_Menu_t* config );
E_Status_t                GLU_FUNC( Menu, insert     )  ( ID_t ID );
E_Status_t                GLU_FUNC( Menu, frame      )  ( ID_t ID , bool cmd );
int                       GLU_FUNC( Menu, scroll     )  ( ID_t ID , int  cmd );
E_Status_t                GLU_FUNC( Menu, delete     )  ( ID_t ID );

#ifdef __cplusplus
}
#endif

#endif



