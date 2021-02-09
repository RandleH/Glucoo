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
#define GUI_WHITE             (GUI_MAKE_COLOR(255,255,255))  // 白色
#define GUI_BLACK             (GUI_MAKE_COLOR(  0,  0,  0))  // 黑色

#define GUI_BLUE              (GUI_MAKE_COLOR(  0,  0,255))  // 蓝色
#define GUI_RED               (GUI_MAKE_COLOR(255,  0,  0))  // 红色
#define GUI_GREEN             (GUI_MAKE_COLOR(  0,255,  0))  // 绿色
#define GUI_YELLOW            (GUI_MAKE_COLOR(255,255,  0))  // 黄色
#define GUI_CYAN              (GUI_MAKE_COLOR(  0,255,255))  // 青色
#define GUI_MAGENTA           (GUI_MAKE_COLOR(255,  0,255))  // 洋紫

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
#define GUI_MEDIUMBLUE        (GUI_MAKE_COLOR(  0,  0,205))  // 适中蓝
#define GUI_MIDNIGHTBLUE      (GUI_MAKE_COLOR( 25, 25,112))  // 午夜蓝
#define GUI_DARKBLUE          (GUI_MAKE_COLOR(  0,  0,139))  // 深蓝
#define GUI_NAVY              (GUI_MAKE_COLOR(  0,  0,128))  // 海军蓝
#define GUI_ROYALBLUE         (GUI_MAKE_COLOR( 65,105,225))  // 皇家蓝
#define GUI_CORNFLOWERBLUE    (GUI_MAKE_COLOR(100,149,237))  // 矢车菊蓝
#define GUI_LIGHTSTEELBLUE    (GUI_MAKE_COLOR(176,196,222))  // 淡钢蓝
#define GUI_LIGHTSLATEGRAY    (GUI_MAKE_COLOR(119,136,153))  // 浅板岩灰
#define GUI_SLATEGRAY         (GUI_MAKE_COLOR(112,128,144))  // 石板灰
#define GUI_DODGERBLUE        (GUI_MAKE_COLOR( 30,114,255))  // 道奇蓝
#define GUI_ALICEBLUE         (GUI_MAKE_COLOR(240,248,255))  // 爱丽丝蓝
#define GUI_STEELBLUE         (GUI_MAKE_COLOR( 70,130,180))  // 钢蓝
#define GUI_LIGHTSKYBLUE      (GUI_MAKE_COLOR(135,206,250))  // 淡天蓝
#define GUI_SKYBLUE           (GUI_MAKE_COLOR(135,206,235))  // 天蓝
#define GUI_DEEPSKYBLUE       (GUI_MAKE_COLOR(  0,191,255))  // 深天蓝
#define GUI_LIGHTBLUE         (GUI_MAKE_COLOR(173,216,230))  // 淡蓝
#define GUI_POWDERBLUE        (GUI_MAKE_COLOR(176,224,230))  // 火药蓝
#define GUI_CADETBLUE         (GUI_MAKE_COLOR( 95,158,160))  // 军校蓝
#define GUI_AZURE             (GUI_MAKE_COLOR(245,255,255))  // 蔚蓝
#define GUI_LIGHTCYAN         (GUI_MAKE_COLOR(240,255,255))  // 淡青
#define GUI_PALETURQUOISE     (GUI_MAKE_COLOR(175,238,238))  // 苍白宝石绿
#define GUI_AQUA              (GUI_MAKE_COLOR(  0,255,255))  // 水绿
#define GUI_DARKTURQUOISE     (GUI_MAKE_COLOR(  0,206,209))  // 深宝石绿
#define GUI_DARKSLATEGRAY     (GUI_MAKE_COLOR( 47, 79, 79))  // 深石板灰
#define GUI_DARKCYAN          (GUI_MAKE_COLOR(  0,139,139))  // 深青色
#define GUI_TEAL              (GUI_MAKE_COLOR(  0,128,128))  // 水鸭色
#define GUI_MEDIUMTURQUOISE   (GUI_MAKE_COLOR( 72,209,204))  // 适中宝石绿
#define GUI_LIGHTSEEGREEN     (GUI_MAKE_COLOR( 32,178,170))  // 浅海样绿
#define GUI_TURQUOISE         (GUI_MAKE_COLOR( 64,224,208))  // 宝石绿
#define GUI_AQUAMARINE        (GUI_MAKE_COLOR(127,255,212))  // 碧绿
#define GUI_MEDIUMAQUAMARINE  (GUI_MAKE_COLOR(102,205,170))  // 适中碧绿
#define GUI_MEDIUMSPRINGGREEN (GUI_MAKE_COLOR(  0,250,154))  // 适中春天绿
#define GUI_SPRINGGREEN       (GUI_MAKE_COLOR(  0,255,127))  // 春天绿
#define GUI_MEDIUMSEEGREEN    (GUI_MAKE_COLOR( 60,179,113))  // 适中海洋绿
#define GUI_SEEGREEN          (GUI_MAKE_COLOR( 46,139, 87))  // 海洋绿
#define GUI_LIGHTGREEN        (GUI_MAKE_COLOR(144,238,144))  // 浅绿
#define GUI_PALEGREEN         (GUI_MAKE_COLOR(152,251,152))  // 苍白绿
#define GUI_DARKSEEGREEN      (GUI_MAKE_COLOR(143,188,143))  // 深海洋绿
#define GUI_LIME              (GUI_MAKE_COLOR( 50,205, 50))  // 莱姆色
#define GUI_CHARTREUSE        (GUI_MAKE_COLOR(127,255,  0))  // 查特酒绿

// Green-RED Series
#define GUI_FORESTGREEN       (GUI_MAKE_COLOR( 34,139, 34))  // 森林绿
#define GUI_LAWNGREEN         (GUI_MAKE_COLOR(124,252,  0))  // 草坪绿
#define GUI_GREENYELLOW       (GUI_MAKE_COLOR(173,255, 47))  // 绿黄
#define GUI_DARKOLIVEGREEN    (GUI_MAKE_COLOR( 85,107, 47))  // 深橄榄绿
#define GUI_YELLOWGREEN       (GUI_MAKE_COLOR(154,205, 50))  // 黄绿
#define GUI_OLIVEDRAB         (GUI_MAKE_COLOR( 34,139, 34))  // 橄榄褐
#define GUI_BEIGE             (GUI_MAKE_COLOR(245,245,220))  // 米色
#define GUI_LIGHTRODYELLOW    (GUI_MAKE_COLOR( 34,139, 34))  // 浅秋黄
#define GUI_IVORY             (GUI_MAKE_COLOR(255,255,240))  // 象牙白
#define GUI_OLIVE             (GUI_MAKE_COLOR(128,128,  0))  // 橄榄
#define GUI_DARKKHAKI         (GUI_MAKE_COLOR(189,183,107))  // 深卡其布
#define GUI_LEMONCHIFFON      (GUI_MAKE_COLOR(255,250,205))  // 柠檬沙
#define GUI_PALEGOLDROD       (GUI_MAKE_COLOR(238,232,170))  // 灰秋
#define GUI_KHAKI             (GUI_MAKE_COLOR(240,230,140))  // 卡其布
#define GUI_GOLDEN            (GUI_MAKE_COLOR(255,215,  0))  // 金色
#define GUI_CORNMILK          (GUI_MAKE_COLOR(255,248,220))  // 玉米
#define GUI_GOLDROD           (GUI_MAKE_COLOR(218,165, 32))  // 秋天
#define GUI_DARKGOLDROD       (GUI_MAKE_COLOR(184,134, 11))  // 深秋
#define GUI_FLORALWHITE       (GUI_MAKE_COLOR(255,250,240))  // 白花
#define GUI_OLDLACE           (GUI_MAKE_COLOR(253,245,230))  // 浅米色
#define GUI_WHEAT             (GUI_MAKE_COLOR(245,222,179))  // 小麦
#define GUI_MOCCASIN          (GUI_MAKE_COLOR(255,228,181))  // 鹿皮
#define GUI_ORANGE            (GUI_MAKE_COLOR(255,165,  0))  // 橙色
#define GUI_PAPAYAWHIP        (GUI_MAKE_COLOR(255,239,213))  // 木瓜
#define GUI_BLANCHEDALMOND    (GUI_MAKE_COLOR(255,235,205))  // 漂白的杏仁
#define GUI_NAVAJOWHITE       (GUI_MAKE_COLOR(255,222,173))  // 耐而节白
#define GUI_ANTIQUEWHITE      (GUI_MAKE_COLOR(250,235,215))  // 古白
#define GUI_TAN               (GUI_MAKE_COLOR(210,180,140))  // 晒
#define GUI_BURLYWOOD         (GUI_MAKE_COLOR(222,184,135))  // 树干
#define GUI_BISQUE            (GUI_MAKE_COLOR(255,228,196))  // 乳脂
#define GUI_DARKORANGE        (GUI_MAKE_COLOR(255,140,  0))  // 深橙色
#define GUI_LINEN             (GUI_MAKE_COLOR(255,240,230))  // 亚麻
#define GUI_PERU              (GUI_MAKE_COLOR(205,133, 63))  // 秘鲁
#define GUI_SANDYBROWN        (GUI_MAKE_COLOR(244,164, 96))  // 沙棕
#define GUI_CHOCOLATE         (GUI_MAKE_COLOR(210,105, 30))  // 巧克力
#define GUI_SEASHELL          (GUI_MAKE_COLOR(255,245,238))  // 海贝
#define GUI_SIENNA            (GUI_MAKE_COLOR(160, 82, 45))  // 土黄赭
#define GUI_SALMON            (GUI_MAKE_COLOR(255,160,122))  // 三文鱼
#define GUI_CORAL             (GUI_MAKE_COLOR(255,127, 80))  // 珊瑚红
#define GUI_ORANGERED         (GUI_MAKE_COLOR(255, 69,  0))  // 橙红
#define GUI_TOMATO            (GUI_MAKE_COLOR(255, 99, 71))  // 番茄
#define GUI_MISTYROSE         (GUI_MAKE_COLOR(255,228,225))  // 迷雾玫瑰
#define GUI_BLOODYMEAT        (GUI_MAKE_COLOR(250,128,114))  // 鲜肉
#define GUI_LIGHTCORAL        (GUI_MAKE_COLOR(240,128,128))  // 浅珊瑚红
#define GUI_ROSEBROWN         (GUI_MAKE_COLOR(188,143,143))  // 玫瑰棕
#define GUI_INDIANRED         (GUI_MAKE_COLOR(205, 92, 92))  // 浅粉红
#define GUI_BROWN             (GUI_MAKE_COLOR(165, 42, 42))  // 棕色
#define GUI_FIREBRICK         (GUI_MAKE_COLOR(178, 34, 34))  // 火砖
#define GUI_DARKRED           (GUI_MAKE_COLOR(139,  0,  0))  // 深红
#define GUI_MAROON            (GUI_MAKE_COLOR(128,  0,  0))  // 栗色

// Neutral Series
#define GUI_WHITESMOKE        (GUI_MAKE_COLOR(245,245,245))  // 烟白
#define GUI_GAINSBORO         (GUI_MAKE_COLOR(220,220,220))  // 赶死部落
#define GUI_LIGHTGRAY         (GUI_MAKE_COLOR(211,211,211))  // 浅灰
#define GUI_SILVER            (GUI_MAKE_COLOR(192,192,192))  // 银色
#define GUI_DARKGRAY          (GUI_MAKE_COLOR(169,169,169))  // 深灰
#define GUI_DIMGRAY           (GUI_MAKE_COLOR(105,105,105))  // 暗灰


#endif






