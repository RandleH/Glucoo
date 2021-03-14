#ifndef _RH_GUI_H
#define _RH_GUI_H

#include "RH_common.h"
#include "RH_gui_config.h"

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
    
}E_GUI_WindowType_t;

struct __GUI_Window_t{
    __Area_t           area;
    E_GUI_WindowType_t type;
    E_GUI_Appearance_t  appearance;
    size_t             size;
    const char*        title;
    
    //...//
};
typedef struct __GUI_Window_t __GUI_Window_t;

ID_t       __attribute__ ((warn_unused_result)) GUI_create_window  ( __GUI_Window_t* config );
E_Status_t                                      GUI_insert_window  ( ID_t ID );
E_Status_t                                      GUI_delete_window  ( ID_t ID );
#endif




#ifdef __cplusplus
}
#endif


#endif




