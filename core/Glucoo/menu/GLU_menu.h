#ifndef _GLU_MENU_H
#define _GLU_MENU_H

#include "GLU_font.h"

struct __GUI_MenuParam_t{
    const char* text;
};
typedef struct __GUI_MenuParam_t __GUI_MenuParam_t;

struct __GUI_Menu_t{
    const char*           title;                /* 菜单标题名字 */
    GLU_TYPE(Pixel)       color_title;          /* 菜单标题栏字体颜色 */
    GLU_TYPE(Pixel)       bk_color_title;       /* 菜单标题栏背景色 */
    GLU_TYPE(Pixel)       bk_color;             /* 菜单背景色 */
    GLU_TYPE(Pixel)       text_color;           /* 菜单栏字体颜色 */
    GLU_TYPE(Pixel)       sl_color;             /* 菜单栏选中色 */
    
    E_GUI_FontStyle_t     font;                 /* 菜单字体 */
    
    __Area_t              area;                 /* 菜单屏幕所占区域 */
    int8_t                nItem;                /* 菜单栏目条数 */
    __GUI_MenuParam_t*    menuList;             /* 菜单栏目配置数组 */
    
    bool                  icon_cmd;             /* 菜单是否需要图标 */
    
    int8_t                size;                 /* 菜单显示大小 */
    
    
    const void*  const    history;              /* [内部使用] 缓存入口 */
};
typedef struct __GUI_Menu_t __GUI_Menu_t;

#endif
