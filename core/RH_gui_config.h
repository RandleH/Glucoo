#ifndef _RH_GUI_CONFIG_H
#define _RH_GUI_CONFIG_H

#include "RH_common.h"
#include "RH_config.h"
#include "RH_image.h"
#ifdef __cplusplus
extern "C"{
#endif

#define GUI_ICON_DISPLAY            1   // 0=Disable   1=Enable

#define GUI_TRACE_WATCH_DISPLAY     1   // 0=Disable   1=Enable

#define GUI_MENU_DISPLAY            1   // 0=Disable   1=Enable

#define GUI_ANIMATION_DISPLAY       1   // 0=Disable   1=Enable

#define GUI_FONT_EXTENTION          1   // 0=Disable   1=Enable

#define GUI_TEST_EXTENTION          1   // 0=Disable   1=Enable

#define GUI_WINDOW_DISPLAY          1   // 0=Disable   1=Enable





#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
typedef __ImageBIN_t           __PixelInfo_t;
typedef __UNION_PixelBIN_t     __PixelUnit_t;
typedef uint8_t                __Pixel_t;
//  #error "[RH_gui_config]: Not support yet."
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


#ifdef __cplusplus
}
#endif


#endif




