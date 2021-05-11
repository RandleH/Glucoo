
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
typedef __ImageBIN_t           __PixelInfo_t;
typedef __UNION_PixelBIN_t     __PixelUnit_t;
typedef uint8_t                __Pixel_t;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
typedef __ImageRGB565_t        __PixelInfo_t;
typedef __UNION_PixelRGB565_t  __PixelUnit_t;
typedef uint16_t               __Pixel_t;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
typedef __ImageRGB888_t        __PixelInfo_t;
typedef __UNION_PixelRGB888_t  __PixelUnit_t;
typedef uint32_t               __Pixel_t;
#else
  #error "[RH_gui_config]: Unknown color type."
#endif


typedef void* ID_t;

extern void (*GUI_API_DrawArea)       (int x1,int y1,int x2,int y2,const __Pixel_t* pixData);
extern void (*GUI_API_DrawPixel)      (int x ,int y ,const __Pixel_t pixData);
extern void (*GUI_API_DelayMs)        (unsigned long ms);
extern void (*GUI_API_AssertParam)    (bool expression,const char* WHAT_IS_WRONG );

/*===============================================================================================================
 * 定义于 [ ./GLU_glucoo.c ]
===============================================================================================================*/
void RH_PREMAIN GUI_Init        ( void );

void GUI_set_penSize            ( size_t    penSize  );
void GUI_set_penColor           ( __Pixel_t penColor );
void GUI_auto_display           ( bool      cmd      );


void GUI_RefreashScreenArea     ( int xs,int ys,int xe,int ye );
void GUI_AddScreenArea          ( int xs,int ys,int xe,int ye );

void GUI_RefreashScreen         ( void );
void GUI_RefreashEntireScreen   ( void );

bool GUI_is_AutoDisplay         ( void );
bool GUI_is_InternalGRAM        ( void );
bool GUI_is_CacheIdle           ( void );


/*===============================================================================================================
 * 定义于 [ ./draw/GLU_draw.c ]
===============================================================================================================*/
void GUI_rect_raw               ( int xs,int ys,int xe,int ye );
void GUI_rect_edged             ( int xs,int ys,int xe,int ye );
void GUI_rect_fill              ( int xs,int ys,int xe,int ye );
void GUI_rect_round             ( int xs,int ys,int xe,int ye );

void GUI_circle_raw             ( int x ,int y ,int d );
void GUI_circle_edged           ( int x ,int y ,int d );
void GUI_circle_fill            ( int x ,int y ,int d );
void GUI_circle_qrt1_fill       ( int x ,int y ,int r );
void GUI_circle_qrt2_fill       ( int x ,int y ,int r );
void GUI_circle_qrt3_fill       ( int x ,int y ,int r );
void GUI_circle_qrt4_fill       ( int x ,int y ,int r );
void GUI_circle_qrt1_raw        ( int x ,int y ,int r );
void GUI_circle_qrt2_raw        ( int x ,int y ,int r );
void GUI_circle_qrt3_raw        ( int x ,int y ,int r );
void GUI_circle_qrt4_raw        ( int x ,int y ,int r );

void GUI_sausage_raw            ( int xs, int ys, int xe, int ye );

void GUI_line_raw               ( int x1, int y1, int x2, int y2 );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_object.c ]
===============================================================================================================*/

#include "./object/GLU_object.h"
ID_t            RH_RESULT GUI_object_create    ( const __GUI_Object_t* config );
E_Status_t                GUI_object_template  (       __GUI_Object_t* config  , E_GUI_ObjWidget_t widget );
E_Status_t                GUI_object_adjust    ( ID_t ID  , void*  dataScr, size_t dataSize );
E_Status_t                GUI_object_frame     ( ID_t ID  , bool   cmd   );
E_Status_t                GUI_object_insert    ( ID_t ID );
E_Status_t                GUI_object_delete    ( ID_t ID );//

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_window.c ]
===============================================================================================================*/
#include "./window/GLU_window.h"
ID_t            RH_RESULT GUI_window_create    ( const __GUI_Window_t* config );
__GUI_Window_t*           GUI_window_quickSet  (       __GUI_Window_t* config );
E_Status_t                GUI_window_insert    ( ID_t ID );
E_Status_t                GUI_window_delete    ( ID_t ID );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_menu.c ]
===============================================================================================================*/
#include "./menu/GLU_menu.h"
ID_t            RH_RESULT GUI_menu_create      ( const __GUI_Menu_t* config );
E_Status_t                GUI_menu_insert      ( ID_t ID );
E_Status_t                GUI_menu_frame       ( ID_t ID , bool cmd );
int                       GUI_menu_scroll      ( ID_t ID , int  cmd );
E_Status_t                GUI_menu_delete      ( ID_t ID );

#ifdef __cplusplus
}
#endif

#endif



