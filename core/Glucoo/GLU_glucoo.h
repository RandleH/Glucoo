
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
    GLU_TYPE(Color)  color;
    GLU_ENUM(Align)  align;
    const char*      str;
    bool             ul;
    bool             ml;
};
typedef struct GLU_SRCT(Text) GLU_SRCT(Text);

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
    NUM_kGUI_ObjWidgets    ,
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
void GLU_FUNC( GUI, init )        ( void );

void GLU_FUNC( GUI, setPenSize  )            ( size_t           penSize  );
void GLU_FUNC( GUI, setPenColor )            ( GLU_TYPE(Color)  penColor );
void GLU_FUNC( GUI, autoDisplay )            ( bool             cmd      );


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
void GLU_FUNC( GUI, rect_round_fill  )       ( int xs,int ys,int xe,int ye );

void GLU_FUNC( GUI, EX_rect_raw      )       ( const __Area_t* pArea );
void GLU_FUNC( GUI, EX_rect_edged    )       ( const __Area_t* pArea );
void GLU_FUNC( GUI, EX_rect_fill     )       ( const __Area_t* pArea );

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

void GLU_FUNC( GUI, capsule_raw      )       ( int xs,int ys,int xe,int ye );
void GLU_FUNC( GUI, line_raw         )       ( int x1,int y1,int x2,int y2 );
void GLU_FUNC( GUI, quad_raw         )       ( int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4 );

void GLU_FUNC( GUI, screen_fill      )       ( GLU_TYPE(Color) M_COLOR_xxxx );

void* GLU_FUNC( GUI, yield_GRAM      )       ( void );

/*===============================================================================================================
 * 定义于 [ ./draw/GLU_object.c ]
===============================================================================================================*/
#include "./object/GLU_object.h"
ID_t            RH_RESULT GLU_FUNC( Object, create   )  ( const GLU_SRCT(Object)* config, const void* RH_NULLABLE dataScr );
E_Status_t                GLU_FUNC( Object, template )  (       GLU_SRCT(Object)* config, GLU_ENUM(ObjWidget) widget );
E_Status_t                GLU_FUNC( Object, adjust   )  ( ID_t ID  , void*  dataScr, size_t dataSize );
E_Status_t                GLU_FUNC( Object, frame    )  ( ID_t ID  , bool   cmd   );
E_Status_t                GLU_FUNC( Object, insert   )  ( ID_t ID );
E_Status_t                GLU_FUNC( Object, delete   )  ( ID_t ID );

E_Status_t                GLU_FUNC( Object, preferred_area ) ( __Area_t* preferred_area, GLU_ENUM(ObjWidget) widget );

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



