
#ifndef _GLUCOO_H
#define _GLUCOO_H

#include <stdbool.h>
#include "RH_common.h"
#include "RH_config.h"

#include "GLU_pixel.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef void* ID_t;

/*===============================================================================================================
 * GLU_FONT --- Definition as follow
===============================================================================================================*/
typedef enum{
    kGLU_Font_Unscii            ,
    kGLU_Font_ArialRounded_Bold ,
    kGLU_Font_CourierNew        ,
    kGLU_Font_CourierNew_Italic ,
    kGLU_Font_CourierNew_Bold   ,
    kGLU_Font_NewYork           ,
    kGLU_Font_NewYork_Italic    ,
    kGLU_Font_Optima            ,
    kGLU_Font_SignPrinter       ,
    kGLU_NUM_FontStyle
}GLU_ENUM(Font);

typedef enum{
    kGLU_Align_Right   ,
    kGLU_Align_Left    ,
    kGLU_Align_Middle  ,
    kGLU_Align_Justify
}GLU_ENUM(Align);

struct GLU_SRCT(Text){
    GLU_ENUM(Font)   font;
    uint16_t         size;
    gluColor_t       color;
    GLU_ENUM(Align)  align;
    const char*      str;
    bool             ul;
    bool             ml;
};
typedef struct GLU_SRCT(Text) GLU_SRCT(Text);

/*===============================================================================================================
 * GLU_RENDER --- Definition as follow
===============================================================================================================*/
typedef enum{
    kGLU_Render_blur_24bit       ,
    kGLU_Render_gradient_h_16bit ,
    kGLU_Render_gradient_h_24bit ,
    kGLU_Render_gradient_v_16bit ,
    kGLU_Render_gradient_v_24bit ,
    kGLU_Render_centered_24bit   ,
    kGLU_NUM_Render        ,
}GLU_ENUM(Render);

/*===============================================================================================================
 * GLU_OBJECT --- Definition as follow
===============================================================================================================*/
typedef enum{
    kGLU_ObjWidget_text     ,
    kGLU_ObjWidget_num      ,
    kGLU_ObjWidget_fnum     ,
    
    kGLU_ObjWidget_switch   ,
    kGLU_ObjWidget_barH     ,
    kGLU_ObjWidget_barV     ,
    kGLU_ObjWidget_trunk    ,//
    
    kGLU_ObjWidget_joystick ,
    kGLU_ObjWidget_spinbox  ,
    kGLU_ObjWidget_button   ,
    NUM_kGUI_ObjWidgets     ,
}GLU_ENUM(ObjWidget);

/*===============================================================================================================
 * GLU_WINDOW --- Definition as follow
===============================================================================================================*/
typedef enum{
    kGUI_Appearance_Light  ,
    kGUI_Appearance_Dark   ,
    
}E_GUI_Appearance_t;

typedef enum{
    kGUI_WindowType_macOS  ,
    kGUI_WindowType_win10  ,
    NUM_kGUI_WindowType    ,
}E_GUI_WindowStyle_t;


/*===============================================================================================================
 * 定义于 [ ./GLU_glucoo.c ]
===============================================================================================================*/
void glu_gui_init( void) GLU_API;
void glu_gui_set_penSize(size_t penSize) GLU_API;
void glu_gui_set_penColor(gluColor_t penColor) GLU_API;

void glu_dev_auto_refreash(cmnBoolean_t flag) GLU_API;
void glu_dev_refreash_screen(void) GLU_API;
void glu_dev_refreash_partial_screen( int xs, int ys, int xe, int ye) GLU_API;
void glu_dev_refreash_partial_screen_ex( const __Area_t* area) GLU_API;
void glu_dev_refreash_full_screen(void) GLU_API;
void glu_dev_add_refreash_area( int xs, int ys, int xe, int ye) GLU_API;
void glu_dev_add_refreash_area_ex( const __Area_t* area) GLU_API;
void glu_dev_fill_full_screen( const gluColor_t color) GLU_API;

cmnBoolean_t glu_dev_is_auto_refreash(void);
cmnBoolean_t glu_dev_is_refreash_done(void);


/*===============================================================================================================
 * 定义于 [ ./draw/GLU_draw.c ]
===============================================================================================================*/

void glu_draw_rectangle         ( int xs, int ys, int xe, int ye);
void glu_draw_rectangle_edged   ( int xs, int ys, int xe, int ye);
void glu_draw_rectangle_filled  ( int xs, int ys, int xe, int ye);
void glu_draw_rectangle_rounded ( int xs, int ys, int xe, int ye);

void glu_draw_circle           ( int x ,int y ,int d);
void glu_draw_circle_edged     ( int x ,int y ,int d);
void glu_draw_circle_fill      ( int x ,int y ,int d);
void glu_draw_circle_qrt1      ( int x ,int y ,int r);
void glu_draw_circle_qrt2      ( int x ,int y ,int r);
void glu_draw_circle_qrt3      ( int x ,int y ,int r);
void glu_draw_circle_qrt4      ( int x ,int y ,int r);
void glu_draw_circle_qrt1_fill ( int x ,int y ,int r);
void glu_draw_circle_qrt2_fill ( int x ,int y ,int r);
void glu_draw_circle_qrt3_fill ( int x ,int y ,int r);
void glu_draw_circle_qrt4_fill ( int x ,int y ,int r);

void glu_draw_capsule( int xs,int ys,int xe,int ye);

void glu_draw_line( int x1, int y1, int x2, int y2);

void glu_draw_quad( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);


void* GLU_FUNC( GUI, yield_GRAM      )       ( void );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_object.c ]
===============================================================================================================*/
#include "./object/GLU_object.h"
ID_t            RH_RESULT glu_gui_object_create   ( const GLU_SRCT(Object)* config, const void* RH_NULLABLE dataScr );
E_Status_t                glu_gui_object_template (       GLU_SRCT(Object)* config, GLU_ENUM(ObjWidget) widget );
E_Status_t                glu_gui_object_adjust   ( ID_t ID  , void*  dataScr, size_t dataSize );
E_Status_t                glu_gui_object_frame    ( ID_t ID  , bool   cmd   );
E_Status_t                glu_gui_object_insert   ( ID_t ID );
E_Status_t                glu_gui_object_delete   ( ID_t ID );
E_Status_t                glu_gui_object_default_area( __Area_t* preferred_area, GLU_ENUM(ObjWidget) widget );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_window.c ]
===============================================================================================================*/
#include "./window/GLU_window.h"
ID_t            RH_RESULT glu_gui_window_create  ( const __GUI_Window_t* config );
__GUI_Window_t*           glu_gui_window_template(       __GUI_Window_t* config );
E_Status_t                glu_gui_window_insert  ( ID_t ID );
E_Status_t                glu_gui_window_delete  ( ID_t ID );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_menu.c ]
===============================================================================================================*/
#include "./menu/GLU_menu.h"
ID_t            RH_RESULT glu_gui_menu_create( const __GUI_Menu_t* config );
E_Status_t                glu_gui_menu_insert( ID_t ID );
E_Status_t                glu_gui_menu_frame ( ID_t ID , bool cmd );
int                       glu_gui_menu_scroll( ID_t ID , int  cmd );
E_Status_t                glu_gui_menu_delete( ID_t ID );

#ifdef __cplusplus
}
#endif

#endif



