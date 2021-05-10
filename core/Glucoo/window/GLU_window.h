#ifndef _GLU_WINDOW_H
#define _GLU_WINDOW_H

#include "GLU_font.h"



typedef enum{
    kGUI_Appearance_Light  ,
    kGUI_Appearance_Dark   ,
    
}E_GUI_Appearance_t;

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


#endif

