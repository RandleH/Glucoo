#ifndef _GLU_OBJECT_H
#define _GLU_OBJECT_H

#include "GLU_font.h"

/*===============================================================================================================
 * 各个object插件的widget列表
===============================================================================================================*/
typedef enum{
    kGUI_ObjStyle_text     ,
    kGUI_ObjStyle_num      ,
    kGUI_ObjStyle_fnum     ,
    
    kGUI_ObjStyle_switch   ,
    kGUI_ObjStyle_barH     ,
    kGUI_ObjStyle_barV     ,//
    
    kGUI_ObjStyle_joystick ,
    NUM_kGUI_ObjWidgets    ,
}E_GUI_ObjWidget_t;


/*===============================================================================================================
 * 声明object插件的信息数据结构
===============================================================================================================*/
struct __GUI_Object_t{
    __Area_t             area;
    E_GUI_ObjWidget_t    widget;
    E_GUI_FontStyle_t    font;
    
    const char*          text;
    int16_t              text_size;
    
    E_GUI_FontAlign_t    text_align;
    
    __Pixel_t            obj_color;
    __Pixel_t            bk_color;
    
    float                min[2];
    float                val[2];
    float                max[2];
    
    void*                dataScr;
    
    bool                 showFrame;
    
    void (*insert_func)(const struct __GUI_Object_t*);  // DO NOT MODIFY
    void (*remove_func)(const struct __GUI_Object_t*);  // DO NOT MODIFY
    void (*adjust_func)(const struct __GUI_Object_t*);  // DO NOT MODIFY
    const void*   const  history;                       // DO NOT MODIFY
};
typedef struct __GUI_Object_t __GUI_Object_t;

/*===============================================================================================================
 * 声明各个object所适配的输入数据结构
===============================================================================================================*/

struct __GUI_ObjDataScr_text{
    const char* text;
};
typedef struct __GUI_ObjDataScr_text __GUI_ObjDataScr_text;

struct __GUI_ObjDataScr_num{
    int32_t value;
};
typedef struct __GUI_ObjDataScr_num __GUI_ObjDataScr_num;

struct __GUI_ObjDataScr_fnum{
    float_t value;
};
typedef struct __GUI_ObjDataScr_fnum __GUI_ObjDataScr_fnum;

struct __GUI_ObjDataScr_switch{
    bool    cmd;
};
typedef struct __GUI_ObjDataScr_switch __GUI_ObjDataScr_switch;

struct __GUI_ObjDataScr_barH{
    int32_t value;
    int32_t max;
    int32_t min;
};
typedef struct __GUI_ObjDataScr_barH __GUI_ObjDataScr_barH;

struct __GUI_ObjDataScr_barV{
    int32_t value;
    int32_t max;
    int32_t min;
};
typedef struct __GUI_ObjDataScr_barV __GUI_ObjDataScr_barV;

struct __GUI_ObjDataScr_joystick{
    int32_t value[2];
    int32_t max  [2];
    int32_t min  [2];
};
typedef struct __GUI_ObjDataScr_joystick __GUI_ObjDataScr_joystick;

#endif
