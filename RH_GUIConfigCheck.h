#ifndef _RH_GUI_CONFGICHECK
#define _RH_GUI_CONFGICHECK 
#include "RH_GUIConfig.h"
#include <stdint.h>

#ifndef BYTE
typedef uint8_t  BYTE;
#endif

#ifndef WORD
typedef uint16_t WORD;
#endif

#ifndef DWORD
typedef uint32_t DWORD;
#endif



#include <stdint.h>
#if (GUI_BPP == GUI_1BitPerPixel) || (GUI_BPP == GUI_8BitPerPixel)
  // typedef uint8_t  Pixel_t;
  #define Pixel_t BYTE
#elif (GUI_BPP == GUI_16BitPerPixel)
  // typedef uint16_t Pixel_t;
  #define Pixel_t WORD
#elif (GUI_BPP == GUI_32BitPerPixel)
  // typedef uint32_t Pixel_t;
  #define Pixel_t DWORD
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

  #define GUI_MAKE_COLOR(R_255,G_255,B_255)  (BYTE)(((R+G+B)/3 > 128)?0xff:0x00)

#elif (GUI_COLOR_TYPE == GUI_RGB565)
  #define GUI_WHITE         	0xFFFF
  #define GUI_BLACK         	0x0000	  
  #define GUI_BLUE         	 	0x001F  
  #define GUI_BRED              0xF81F
  #define GUI_GRED 			 	0xFFE0
  #define GUI_GBLUE			 	0x07FF
  #define GUI_RED           	0xF800
  #define GUI_MAGENTA       	0xF81F
  #define GUI_GREEN         	0x07E0
  #define GUI_CYAN          	0x7FFF
  #define GUI_YELLOW        	0xFFE0
  #define GUI_BROWN 			0xBC40 //棕色
  #define GUI_BRRED 			0xFC07 //棕红色
  #define GUI_GRAY  			0x2945 //灰色
 
  #define GUI_DARKBLUE      	0x01CF //深蓝色
  #define GUI_LIGHTBLUE      	0x7D7C //浅蓝色  
  #define GUI_GRAYBLUE       	0x5458 //灰蓝色
   
  #define GUI_LIGHTGREEN     	0x841F //浅绿色
  #define GUI_LIGHTGRAY         0xEF5B //浅灰色(PANNEL)
  #define GUI_LGRAY 			0xC618 //浅灰色(PANNEL),窗体背景色
  #define GUI_LGRAYBLUE         0xA651 //浅灰蓝色(中间层颜色)
  #define GUI_LBBLUE            0x2B12 //浅棕蓝色(选择条目的反色)

  #define GUI_MAKE_COLOR(R_255,G_255,B_255)  (WORD)(((R_255>>3)<<11)|((G_255>>2)<<5)|(B_255>>3))
  #define GUI_RED_MASK        GUI_RED
  #define GUI_GREEN_MASK      GUI_GREEN
  #define GUI_BLUE_MASK       GUI_BLUE

  #define GUI_DARKEN_COLOR_1Bit(C)    (WORD)( ((((C)&GUI_RED_MASK)>>1)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>1)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>1)&(GUI_BLUE_MASK)) )
  #define GUI_DARKEN_COLOR_2Bit(C)    (WORD)( ((((C)&GUI_RED_MASK)>>2)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>2)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>2)&(GUI_BLUE_MASK)) )

#elif (GUI_COLOR_TYPE == GUI_RGB888)
//  #error "RGB888 is not supported yet. :-("
  #define GUI_WHITE             0xFFFFFFFF
  #define GUI_BLACK             0x00000000
  #define GUI_BLUE              0x000000FF
  #define GUI_RED               0x00FF0000
  #define GUI_GREEN             0x0000FF00
  #define GUI_YELLOW            0x00FFFF00
  #define GUI_CYAN              0x00000000 // TEMP
  #define GUI_LBBLUE            0x00000000 // TEMP
  #define GUI_LIGHTGREEN        0x00000000 // TEMP
  #define GUI_MAGENTA           0x00000000 // TEMP
  #define GUI_LIGHTGRAY         0x00000000 // TEMP

  #define GUI_MAKE_COLOR(R_255,G_255,B_255)  (WORD)(((R_255)<<16)|((G_255)<<8)|(B_255))
  #define GUI_RED_MASK        GUI_RED
  #define GUI_GREEN_MASK      GUI_GREEN
  #define GUI_BLUE_MASK       GUI_BLUE
  
  #define GUI_DARKEN_COLOR_1Bit(C)    (WORD)( ((((C)&GUI_RED_MASK)>>1)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>1)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>1)&(GUI_BLUE_MASK)) )
  #define GUI_DARKEN_COLOR_2Bit(C)    (WORD)( ((((C)&GUI_RED_MASK)>>2)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>2)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>2)&(GUI_BLUE_MASK)) )

#endif


#endif






