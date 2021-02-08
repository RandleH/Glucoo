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


/*============================================================================================================================================================
 > Color Configuration
============================================================================================================================================================*/

#if (GUI_BPP == GUI_1BitPerPixel) || (GUI_BPP == GUI_8BitPerPixel)
  #define Pixel_t BYTE
#elif (GUI_BPP == GUI_16BitPerPixel)
  #define Pixel_t WORD
#elif (GUI_BPP == GUI_32BitPerPixel)

  #define Pixel_t DWORD
#else
  #error "Unknown number of bits for each pixel."
#endif

#if (GUI_COLOR_TYPE == GUI_1Bit)

  #define GUI_MAKE_COLOR(R_255,G_255,B_255)  (BYTE)(((R+G+B)/3 > 128)?0xff:0x00)
  #define GUI_RED_MASK                       0x01
  #define GUI_GREEN_MASK                     0x01
  #define GUI_BLUE_MASK                      0x01
  
  #define GUI_DARKEN_COLOR_1Bit(C)           (BYTE)((C)&0)
  #define GUI_DARKEN_COLOR_2Bit(C)           (BYTE)((C)&0)

#elif (GUI_COLOR_TYPE == GUI_RGB565)

  #define GUI_MAKE_COLOR(R_255,G_255,B_255)  (WORD)(((R_255>>3)<<11)|((G_255>>2)<<5)|(B_255>>3))
  #define GUI_RED_MASK                       0xF800
  #define GUI_GREEN_MASK                     0x7E00
  #define GUI_BLUE_MASK                      0x001F

  #define GUI_DARKEN_COLOR_1Bit(C)    (WORD)( ((((C)&GUI_RED_MASK)>>1)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>1)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>1)&(GUI_BLUE_MASK)) )
  #define GUI_DARKEN_COLOR_2Bit(C)    (WORD)( ((((C)&GUI_RED_MASK)>>2)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>2)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>2)&(GUI_BLUE_MASK)) )

#elif (GUI_COLOR_TYPE == GUI_RGB888)

  #define GUI_MAKE_COLOR(R_255,G_255,B_255)  (DWORD)((((R_255)&0xff)<<16)|(((G_255)&0xff)<<8)|((B_255)&0xff))
  #define GUI_RED_MASK                       0x00FF0000
  #define GUI_GREEN_MASK                     0x0000FF00
  #define GUI_BLUE_MASK                      0x000000FF
  
  #define GUI_DARKEN_COLOR_1Bit(C)    (DWORD)( ((((C)&GUI_RED_MASK)>>1)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>1)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>1)&(GUI_BLUE_MASK)) )
  #define GUI_DARKEN_COLOR_2Bit(C)    (DWORD)( ((((C)&GUI_RED_MASK)>>2)&(GUI_RED_MASK))|((((C)&GUI_GREEN_MASK)>>2)&(GUI_GREEN_MASK))|((((C)&GUI_BLUE_MASK)>>2)&(GUI_BLUE_MASK)) )

#endif

/*============================================================================================================================================================
 > General Color RGB
============================================================================================================================================================*/
 
// Standard
#define GUI_WHITE             (GUI_MAKE_COLOR(255,255,255))
#define GUI_BLACK             (GUI_MAKE_COLOR(  0,  0,  0))

#define GUI_BLUE              (GUI_MAKE_COLOR(  0,  0,255))
#define GUI_RED               (GUI_MAKE_COLOR(255,  0,  0))
#define GUI_GREEN             (GUI_MAKE_COLOR(  0,255,  0))
#define GUI_YELLOW            (GUI_MAKE_COLOR(255,255,  0))
#define GUI_CYAN              (GUI_MAKE_COLOR(  0,255,255))
#define GUI_MAGENTA           (GUI_MAKE_COLOR(255,  0,255))

// Red-Blue Series
#define GUI_PINK              (GUI_MAKE_COLOR(255,192,203))  // 粉红      
#define GUI_CRIMSON           (GUI_MAKE_COLOR(220, 20, 60))  // 猩红      
#define GUI_LAVENDERBLUSH     (GUI_MAKE_COLOR(255,240,245))  // 苍白紫罗兰红
#define GUI_PALEVIOLATRED     (GUI_MAKE_COLOR(219,112,147))  // 羞涩淡紫红 
#define GUI_HOTPINK           (GUI_MAKE_COLOR(255,105,180))  // 热情粉红   
#define GUI_MEDIUMVIOLATRED   (GUI_MAKE_COLOR(199, 21,133))  // 适中紫罗兰 
#define GUI_ORCHID            (GUI_MAKE_COLOR(218,112,214))  // 兰花紫    
#define GUI_THISTLE           (GUI_MAKE_COLOR(216,191,216))  // 苍紫     
#define GUI_PLUM              (GUI_MAKE_COLOR(221,160,221))  // 轻紫     
#define GUI_VOILET            (GUI_MAKE_COLOR(218,112,214))  // 紫罗兰   
#define GUI_DARKVOILET        (GUI_MAKE_COLOR(255,  0,255))  // 紫红     
#define GUI_PURPLE            (GUI_MAKE_COLOR(128,  0,128))  // 紫       
#define GUI_MEDIUMORCHID      (GUI_MAKE_COLOR(255,  0,255))  // 适中兰花紫
#define GUI_DARKVIOLET        (GUI_MAKE_COLOR(148,  0,211))  // 深紫罗兰  
#define GUI_INDIGO            (GUI_MAKE_COLOR( 75,  0,130))  // 靓青     
#define GUI_BLUEVIOLET        (GUI_MAKE_COLOR(138, 43,226))  // 蓝紫罗兰 
#define GUI_MEDIUMPURPLE      (GUI_MAKE_COLOR(147,112,219))  // 适中紫   
#define GUI_MEDIUMSLATEBLUE   (GUI_MAKE_COLOR(123,104,238))  // 适中板岩蓝
#define GUI_SLATEBLUE         (GUI_MAKE_COLOR(106, 90,205))  // 板岩蓝   
#define GUI_DARKSLATEBLUE     (GUI_MAKE_COLOR( 72, 61,139))  // 深板岩蓝 
#define GUI_LAVENDER          (GUI_MAKE_COLOR(230,230,250))  // 薰衣草淡
#define GUI_GHOSTWHITE        (GUI_MAKE_COLOR(248,248,255))  // 幽灵白  

// Blue-Green Series
#define GUI_MEDIUMBLUE        (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_MIDNIGHTBLUE      (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_DARKBLUE          (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_NAVY              (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_ROYALBLUE         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_CORNFLOWERBLUE    (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIGHTSTEELBLUE    (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIGHTSLATEGRAY    (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_SLATEGRAY         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_DODGERBLUE        (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_ALICEBLUE         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_STEELBLUE         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIGHTSKYBLUE      (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_SKYBLUE           (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_DEEPSKYBLUE       (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIGHTBLUE         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_POWDERBLUE        (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_CADETBLUE         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_AZURE             (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIGHTCYAN         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_PALETURQUOISE     (GUI_MAKE_COLOR(175,238,238))  // 
#define GUI_AQUA              (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_DARKTURQUOISE     (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_DARKSLATEGRAY     (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_DARKCYAN          (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_TEAL              (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_MEDIUMTURQUOISE   (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIGHTSEEGREEN     (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_TURQUOISE         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_AQUAMARINE        (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_MEDIUMAQUAMARINE  (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_MEDIUMSPRINGGREEN (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_SPRINGGREEN       (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_MEDIUMSEEGREEN    (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_SEEGREEN          (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIGHTGREEN        (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_PALEGREEN         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_DARKSEEGREEN      (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIMEGREEN         (GUI_MAKE_COLOR(255,  0,255))  // 
#define GUI_LIME              (GUI_MAKE_COLOR(255,  0,255))  // 

// Green-RED Series
#define GUI_FORESTGREEN       (GUI_MAKE_COLOR(255,  0,255))  // 


#endif






