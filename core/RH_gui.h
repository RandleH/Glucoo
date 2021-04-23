#ifndef _RH_GUI_H
#define _RH_GUI_H

#include "RH_common.h"
#include "RH_gui_config.h"
#include "RH_font.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef void* ID_t;

extern void (*GUI_API_DrawArea)       (int x1,int y1,int x2,int y2,const __Pixel_t* pixData);
extern void (*GUI_API_DrawPixel)      (int x ,int y ,const __Pixel_t pixData);
extern void (*GUI_API_DelayMs)        (unsigned long ms);
extern void (*GUI_API_AssertParam)    (bool expression,const char* WHAT_IS_WRONG );


void RH_PREMAIN GUI_Init        ( void );

void GUI_set_penSize            ( size_t    penSize  );
void GUI_set_penColor           ( __Pixel_t penColor );
void GUI_auto_display           ( bool      cmd      );

void GUI_RefreashScreenArea     ( int xs,int ys,int xe,int ye );
void GUI_AddScreenArea          ( int xs,int ys,int xe,int ye );

void GUI_RefreashScreen         ( void );
void GUI_RefreashEntireScreen   ( void );

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

typedef enum{
    kGUI_Appearance_Light  ,
    kGUI_Appearance_Dark   ,
    
}E_GUI_Appearance_t;


#if GUI_WINDOW_DISPLAY

typedef enum{
    kGUI_WindowType_macOS  ,
    kGUI_WindowType_win10  ,
    NUM_kGUI_WindowType    ,
}E_GUI_WindowStyle_t;

struct __GUI_Window_t{
    __Area_t             area;
    E_GUI_WindowStyle_t  type;
    E_GUI_Appearance_t   appearance;
    size_t               size;
    
    const char*          title;
    E_GUI_FontStyle_t    title_font;
    
    const char*          text;
    E_GUI_FontStyle_t    text_font;
    E_GUI_FontAlign_t    text_align;
    int                  text_size;
    //...//
    
    const void*  const   text_bitMap;  // DO NOT MODIFY
    const size_t         text_bitH;    // DO NOT MODIFY
    const size_t         text_bitW;    // DO NOT MODIFY
    const int            text_rs;      // DO NOT MODIFY
    const int            text_margin;  // DO NOT MODIFY
    
    const int            win_edge;     // DO NOT MODIFY
    
    void (*insert_func)(struct __GUI_Window_t*);  // DO NOT MODIFY
    void (*remove_func)(struct __GUI_Window_t*);  // DO NOT MODIFY
};
typedef struct __GUI_Window_t __GUI_Window_t;

ID_t            RH_RESULT GUI_window_create    ( const __GUI_Window_t* config );
__GUI_Window_t*           GUI_window_quickSet  (       __GUI_Window_t* config );
E_Status_t                GUI_window_insert    ( ID_t ID );
E_Status_t                GUI_window_delete    ( ID_t ID );

#endif


typedef enum{
    kGUI_ObjStyle_text  ,
    kGUI_ObjStyle_num   ,
    kGUI_ObjStyle_fnum  ,
    
    kGUI_ObjStyle_switch,
    kGUI_ObjStyle_barH  ,
    kGUI_ObjStyle_barV  ,//
    
    kGUI_ObjStyle_joystick ,
    NUM_kGUI_ObjStyle   ,
}E_GUI_ObjStyle_t;

struct __GUI_Object_t{
    __Area_t             area;
    E_GUI_ObjStyle_t     style;
    E_GUI_FontStyle_t    font;
    
    const char*          text;
    int16_t              text_size;
    __Pixel_t            text_color;
    E_GUI_FontAlign_t    text_align;
    
    __Pixel_t            bk_color;
    
    float                min[2];
    float                val[2];
    float                max[2];
    
    bool                 showFrame;
    
    void (*insert_func)(const struct __GUI_Object_t*);  // DO NOT MODIFY
    void (*remove_func)(const struct __GUI_Object_t*);  // DO NOT MODIFY
    void (*adjust_func)(const struct __GUI_Object_t*);  // DO NOT MODIFY
    const void*   const  history;                       // DO NOT MODIFY
    
};
typedef struct __GUI_Object_t __GUI_Object_t;

ID_t            RH_RESULT GUI_object_create    ( const __GUI_Object_t* config );
__GUI_Object_t*           GUI_object_quickSet  (       __GUI_Object_t* config );//

E_Status_t                GUI_object_adjust    ( ID_t ID  , float  val_0 , float val_1 );
E_Status_t                GUI_object_frame     ( ID_t ID  , bool   cmd   );
E_Status_t                GUI_object_insert    ( ID_t ID );
E_Status_t                GUI_object_delete    ( ID_t ID );//


struct __GUI_MenuParam_t{
    const char* text;
};
typedef struct __GUI_MenuParam_t __GUI_MenuParam_t;

struct __GUI_Menu_t{
    const char*           title;                /* 菜单标题名字 */
    __Pixel_t             color_title;          /* 菜单标题栏字体颜色 */
    __Pixel_t             bk_color_title;       /* 菜单标题栏背景色 */
    
    __Pixel_t             bk_color;             /* 菜单背景色 */
    __Pixel_t             text_color;           /* 菜单栏字体颜色 */
    __Pixel_t             sl_color;             /* 菜单栏选中色 */
    
    E_GUI_FontStyle_t     font;                 /* 菜单字体 */
    
    __Area_t              area;                 /* 菜单屏幕所占区域 */
    int8_t                nItem;                /* 菜单栏目条数 */
    __GUI_MenuParam_t*    menuList;             /* 菜单栏目配置数组 */
    
    bool                  icon_cmd;             /* 菜单是否需要图标 */
    
    int8_t                size;                 /* 菜单显示大小 */
    
    
    const void*  const    history;              /* [内部使用] 缓存入口 */
};
typedef struct __GUI_Menu_t __GUI_Menu_t;

ID_t            RH_RESULT GUI_menu_create      ( const __GUI_Menu_t* config );
E_Status_t                GUI_menu_insert      ( ID_t ID );
E_Status_t                GUI_menu_frame       ( ID_t ID , bool cmd );
int                       GUI_menu_scroll      ( ID_t ID , int  cmd );




#ifdef __cplusplus
}
#endif


#endif




