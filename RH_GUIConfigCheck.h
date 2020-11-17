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
  #define GUI_BLUE        0xff
  #define GUI_BRED        0xff
  #define GUI_GRED        0xff
  #define GUI_GBLUE       0xff
  #define GUI_RED         0xff
  #define GUI_MAGENTA     0xff
  #define GUI_GREEN       0xff
  #define GUI_CYAN        0xff
  #define GUI_YELLOW      0xff
  #define GUI_BROWN       0xff
  #define GUI_BRRED       0xff
  #define GUI_GRAY        0xff
 
  #define GUI_DARKBLUE    0xff
  #define GUI_LIGHTBLUE   0xff
  #define GUI_GRAYBLUE    0xff
   
  #define GUI_LIGHTGREEN  0xff
  #define GUI_LIGHTGRAY   0xff
  #define GUI_LGRAY       0xff 
  #define GUI_LGRAYBLUE   0xff
  #define GUI_LBBLUE      0xff
#elif (GUI_COLOR_TYPE == GUI_RGB565)
  #define GUI_WHITE         	0xFFFF
  #define GUI_BLACK         	0x0000	  
  #define GUI_BLUE         	 	0x001F  
  #define GUI_BRED            0xF81F
  #define GUI_GRED 			 	    0xFFE0
  #define GUI_GBLUE			 	    0x07FF
  #define GUI_RED           	0xF800
  #define GUI_MAGENTA       	0xF81F
  #define GUI_GREEN         	0x07E0
  #define GUI_CYAN          	0x7FFF
  #define GUI_YELLOW        	0xFFE0
  #define GUI_BROWN 			    0xBC40 //棕色
  #define GUI_BRRED 			    0xFC07 //棕红色
  #define GUI_GRAY  			    0x8430 //灰色
 
  #define GUI_DARKBLUE      	0x01CF //深蓝色
  #define GUI_LIGHTBLUE      	0x7D7C //浅蓝色  
  #define GUI_GRAYBLUE       	0x5458 //灰蓝色
   
  #define GUI_LIGHTGREEN     	0x841F //浅绿色
  #define GUI_LIGHTGRAY       0xEF5B //浅灰色(PANNEL)
  #define GUI_LGRAY 			    0xC618 //浅灰色(PANNEL),窗体背景色  
  #define GUI_LGRAYBLUE       0xA651 //浅灰蓝色(中间层颜色)
  #define GUI_LBBLUE          0x2B12 //浅棕蓝色(选择条目的反色)

#elif (GUI_COLOR_TYPE == GUI_RGB888)
  #error "RGB888 is not supported yet. :-("
#endif


#endif






