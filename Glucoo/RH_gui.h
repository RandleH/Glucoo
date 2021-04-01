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


void GUI_RefreashScreenArea ( int xs,int ys,int xe,int ye );
void GUI_AddScreenArea      ( int xs,int ys,int xe,int ye );

void GUI_RefreashScreen     (void);

void GUI_rect_raw           ( int xs,int ys,int xe,int ye );

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

typedef enum{
    kGUI_MenuType_macOS  ,
    kGUI_MenuType_win10  ,
    NUM_kGUI_MenuType    ,
}E_GUI_MenuStyle_t;

struct __GUI_MenuCFG_t{
    const char*          text;
};
typedef struct __GUI_MenuCFG_t __GUI_MenuCFG_t;

struct __GUI_Menu_t{
    __Area_t             area;
    E_GUI_MenuStyle_t    style;
    E_GUI_Appearance_t   appearance;
    size_t               size;
    
    __GUI_MenuCFG_t*     config;
    size_t               nitems;
    
    
};
typedef struct __GUI_Menu_t __GUI_Menu_t;



void                      GUI_rect_raw    ( int xs, int ys, int xe, int ye );
void                      GUI_rect_edged  ( int xs, int ys, int xe, int ye );
void                      GUI_rect_fill   ( int xs, int ys, int xe, int ye );
void                      GUI_rect_round  ( int xs, int ys, int xe, int ye );



ID_t            RH_RESULT GUI_create_window  ( const __GUI_Window_t* config );
__GUI_Window_t*           GUI_easySet_window (       __GUI_Window_t* config );
E_Status_t                GUI_insert_window  ( ID_t ID );
E_Status_t                GUI_delete_window  ( ID_t ID );

#endif




#ifdef __cplusplus
}
#endif


#endif




