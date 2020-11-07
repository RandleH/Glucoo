#ifndef _RH_GUI_CONFGICHECK
#define _RH_GUI_CONFGICHECK 
#include "RH_GUIConfig.h"

#ifndef BYTE
typedef unsigned char BYTE;
#endif
#include <stdint.h>
#if (GUI_BPP == GUI_1BitPerPixel) || (GUI_BPP == GUI_8BitPerPixel)
  // typedef uint8_t  Pixel_t;
  #define Pixel_t uint8_t
#elif (GUI_BPP == GUI_16BitPerPixel)
  // typedef uint16_t Pixel_t;
  #define Pixel_t uint16_t
#elif (GUI_BPP == GUI_32BitPerPixel)
  // typedef uint32_t Pixel_t;
  #define Pixel_t uint32_t
#else
  #error "Unknown number of bits for each pixel."
#endif

#if (GUI_COLOR_TYPE == GUI_1Bit)
  #define GUI_BLACK  			0x00
  #define GUI_WHITE  			0xff
#elif (GUI_COLOR_TYPE == GUI_RGB565)
  #define GUI_WHITE         	0xFFFF
  #define GUI_BLACK         	0x0000	  
  #define GUI_BLUE         	 	0x001F  
  #define GUI_BRED              0XF81F
  #define GUI_GRED 			 	0XFFE0
  #define GUI_GBLUE			 	0X07FF
  #define GUI_RED           	0xF800
  #define GUI_MAGENTA       	0xF81F
  #define GUI_GREEN         	0x07E0
  #define GUI_CYAN          	0x7FFF
  #define GUI_YELLOW        	0xFFE0
  #define GUI_BROWN 			0XBC40 //棕色
  #define GUI_BRRED 			0XFC07 //棕红色
  #define GUI_GRAY  			0X8430 //灰色
 
  #define GUI_DARKBLUE      	0X01CF //深蓝色
  #define GUI_LIGHTBLUE      	0X7D7C //浅蓝色  
  #define GUI_GRAYBLUE       	0X5458 //灰蓝色
   
  #define GUI_LIGHTGREEN     	0X841F //浅绿色
  #define GUI_LIGHTGRAY        	0XEF5B //浅灰色(PANNEL)
  #define GUI_LGRAY 			0XC618 //浅灰色(PANNEL),窗体背景色  
  #define GUI_LGRAYBLUE        	0XA651 //浅灰蓝色(中间层颜色)
  #define GUI_LBBLUE           	0X2B12 //浅棕蓝色(选择条目的反色)
#elif (GUI_COLOR_TYPE == GUI_RGB888)
  #error "RGB888 is not supported yet. :-("
#endif


#endif






