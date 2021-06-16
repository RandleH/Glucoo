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
    kGUI_ObjStyle_barV     ,
    kGUI_ObjStyle_trunk    ,//
    
    kGUI_ObjStyle_joystick ,
    kGUI_ObjStyle_spinbox  ,
    NUM_kGUI_ObjWidgets    ,
}E_GUI_ObjWidget_t;


/*===============================================================================================================
 * 声明object插件的信息数据结构
===============================================================================================================*/
struct __GUI_Object_t{
    
    /*===================================================================================
     * Area --- This is a REQUIRED param. You must give a valid display area on screen.
                Once you submit the object infomation by using GUI_object_create, it
                can not be modified.
     ===================================================================================*/
    __Area_t             area;
    
    /*===================================================================================
     * widget --- This is a REQUIRED param. You must give a valid widget in the form of
                  <E_GUI_ObjWidget_t> enumeration. The widget determine lots of
                  attributions of an object.
     ===================================================================================*/
    E_GUI_ObjWidget_t    widget;
    
    /*===================================================================================
     * FontStyle --- This is an optional param. Only available when this widget has text
                     (or number) to show.
     ===================================================================================*/
    E_GUI_FontStyle_t    font;
    
    /*===================================================================================
     * text --- This is an optional param. Only available when this widget has text to
                show.
     ===================================================================================*/
    const char*          text;
    int16_t              text_size;
    E_GUI_FontAlign_t    text_align;
    
    /*===================================================================================
     * Color --- Every objects has its background color.
     ===================================================================================*/
    GLU_TYPE(Pixel)      obj_color;
    GLU_TYPE(Pixel)      bk_color;
    
    /*===================================================================================
     * Old Data Source(Deprecated)
     ===================================================================================*/
    float                min[2];
    float                val[2];
    float                max[2];
    
    /*===================================================================================
     * Data Source --- This parameter is speacifiled with widgets. It is a point to the
                       type like "__GUI_ObjDataSrc_xxxx" listed as following code.
     ===================================================================================*/
    void*                dataScr;
    
    /*===================================================================================
     * Shoe Frame (Deprecated)
     ===================================================================================*/
    bool                 showFrame;
    
    /*===================================================================================
     * NO MODIFY --- Do NOT modify the following parameters. It will be generated by
                     internal functions.
     ===================================================================================*/
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
typedef struct __GUI_ObjDataScr_barH __GUI_ObjDataScr_barV;
typedef struct __GUI_ObjDataScr_barH __GUI_ObjDataScr_trunk;

struct __GUI_ObjDataScr_joystick{
    int32_t value[2];   // 0:X; 1:Y
    int32_t max  [2];
    int32_t min  [2];
};
typedef struct __GUI_ObjDataScr_joystick __GUI_ObjDataScr_joystick;

struct __GUI_ObjDataScr_spinbox{
    int32_t     max;           // 数据上限
    int32_t     min;           // 数据下限
    int32_t     value;         // 数据值
    int16_t     text_offset;   // 以xs为起始量的偏移量
    int8_t      margin;        // 文字边缘留白量
};
typedef struct __GUI_ObjDataScr_spinbox __GUI_ObjDataScr_spinbox;

#endif
