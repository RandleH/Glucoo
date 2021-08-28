#ifndef _RH_COLOR_H
#define _RH_COLOR_H

#include "RH_common.h"
#include "RH_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RH_COLOR_RECORD_VERSION            "RH_COLOR - 08/18/2021"

#if ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
  #define REVERSE_COLOR( M_COLOR )         (((M_COLOR)==0)?(0xff):(0x00))
  
  #define COLOR_MASK_RED                   0xff
  #define COLOR_MASK_GREEN                 0xff
  #define COLOR_MASK_BLUE                  0xff
  
  #define DARKEN_COLOR_1Bit(C)             (uint8_t)((C)&0)
  #define DARKEN_COLOR_2Bit(C)             (uint8_t)((C)&0)

#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565    )
  
  #define COLOR_MASK_RED                   0xF800
  #define COLOR_MASK_GREEN                 0x7E00
  #define COLOR_MASK_BLUE                  0x001F
  
  #define REVERSE_COLOR( M_COLOR )         (uint16_t)( (0xF800-((M_COLOR)&(0xF800))) | (0x7E00-((M_COLOR)&(0x7E00))) | (0x001F-((M_COLOR)&0x001F)) )
  
  #define DARKEN_COLOR_1Bit(C)             (uint16_t)( ((((C)&COLOR_MASK_RED)>>1)&(COLOR_MASK_RED))|((((C)&COLOR_MASK_GREEN)>>1)&(COLOR_MASK_GREEN))|((((C)&COLOR_MASK_BLUE)>>1)&(COLOR_MASK_BLUE)) )
  #define DARKEN_COLOR_2Bit(C)             (uint16_t)( ((((C)&COLOR_MASK_RED)>>2)&(COLOR_MASK_RED))|((((C)&COLOR_MASK_GREEN)>>2)&(COLOR_MASK_GREEN))|((((C)&COLOR_MASK_BLUE)>>2)&(COLOR_MASK_BLUE)) )

#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888    )

  #define COLOR_MASK_RED                   0x00FF0000
  #define COLOR_MASK_GREEN                 0x0000FF00
  #define COLOR_MASK_BLUE                  0x000000FF
  
  #define REVERSE_COLOR( M_COLOR )         (uint32_t)( (0x00FF0000-((M_COLOR)&(0x00FF0000))) | (0x0000FF00-((M_COLOR)&(0x0000FF00))) | (0x000000FF-((M_COLOR)&0x000000FF)) )

  #define DARKEN_COLOR_1Bit(C)             (uint32_t)( ((((C)&COLOR_MASK_RED)>>1)&(COLOR_MASK_RED))|((((C)&COLOR_MASK_GREEN)>>1)&(COLOR_MASK_GREEN))|((((C)&COLOR_MASK_BLUE)>>1)&(COLOR_MASK_BLUE)) )
  #define DARKEN_COLOR_2Bit(C)             (uint32_t)( ((((C)&COLOR_MASK_RED)>>2)&(COLOR_MASK_RED))|((((C)&COLOR_MASK_GREEN)>>2)&(COLOR_MASK_GREEN))|((((C)&COLOR_MASK_BLUE)>>2)&(COLOR_MASK_BLUE)) )
#else
  #error "[RH_color]: Unknown color type."
#endif


#define MAKE_COLOR_1BIT(R_255,G_255,B_255)     (uint8_t)(((R_255+G_255+B_255)/3 > 128)?0xff:0x00)
#define MAKE_COLOR_16BIT(R_255,G_255,B_255)    (uint16_t)((((R_255)>>3)<<11)|(((G_255)>>2)<<5)|((B_255)>>3))
#define MAKE_COLOR_24BIT(R_255,G_255,B_255)    (uint32_t)((((R_255)&0xff)<<16)|(((G_255)&0xff)<<8)|((B_255)&0xff))
#define MAKE_COLOR                             MAKE_COLOR_24BIT

#define COLOR_16BIT(color)                     (uint16_t)((0xf800&(((color)>>19)<<11)) | (0x07e0&(((color)>>10)<<5 )) | (0x001f&(((color)>>3 ))))
#define COLOR_1BIT(color)                      ((color)==0)?((uint8_t)(0x00)):((uint8_t)(0xff))
#define COLOR_24BIT(color)                     (uint32_t)((color)&0x00ffffff)


// Standard
#define M_COLOR_WHITE                        (MAKE_COLOR(255,255,255))  // 白色
#define M_COLOR_BLACK                        (MAKE_COLOR(  0,  0,  0))  // 黑色
           
#define M_COLOR_BLUE                         (MAKE_COLOR(  0,  0,255))  // 蓝色
#define M_COLOR_RED                          (MAKE_COLOR(255,  0,  0))  // 红色
#define M_COLOR_GREEN                        (MAKE_COLOR(  0,255,  0))  // 绿色
#define M_COLOR_YELLOW                       (MAKE_COLOR(255,255,  0))  // 黄色
#define M_COLOR_CYAN                         (MAKE_COLOR(  0,255,255))  // 青色
#define M_COLOR_MAGENTA                      (MAKE_COLOR(255,  0,255))  // 洋紫
           
// Red-Blue Series           
#define M_COLOR_PINK                         (MAKE_COLOR(255,192,203))  // 粉红
#define M_COLOR_CRIMSON                      (MAKE_COLOR(220, 20, 60))  // 猩红
#define M_COLOR_LAVENDERBLUSH                (MAKE_COLOR(255,240,245))  // 苍白紫罗兰红
#define M_COLOR_PALEVIOLATRED                (MAKE_COLOR(219,112,147))  // 羞涩淡紫红
#define M_COLOR_HOTPINK                      (MAKE_COLOR(255,105,180))  // 热情粉红
#define M_COLOR_MEDIUMVIOLATRED              (MAKE_COLOR(199, 21,133))  // 适中紫罗兰
#define M_COLOR_ORCHID                       (MAKE_COLOR(218,112,214))  // 兰花紫
#define M_COLOR_THISTLE                      (MAKE_COLOR(216,191,216))  // 苍紫
#define M_COLOR_PLUM                         (MAKE_COLOR(221,160,221))  // 轻紫
#define M_COLOR_VOILET                       (MAKE_COLOR(218,112,214))  // 紫罗兰
#define M_COLOR_DARKVOILET                   (MAKE_COLOR(255,  0,255))  // 紫红
#define M_COLOR_PURPLE                       (MAKE_COLOR(128,  0,128))  // 紫
#define M_COLOR_MEDIUMORCHID                 (MAKE_COLOR(255,  0,255))  // 适中兰花紫
#define M_COLOR_DARKVIOLET                   (MAKE_COLOR(148,  0,211))  // 深紫罗兰
#define M_COLOR_INDIGO                       (MAKE_COLOR( 75,  0,130))  // 靓青
#define M_COLOR_BLUEVIOLET                   (MAKE_COLOR(138, 43,226))  // 蓝紫罗兰
#define M_COLOR_MEDIUMPURPLE                 (MAKE_COLOR(147,112,219))  // 适中紫
#define M_COLOR_MEDIUMSLATEBLUE              (MAKE_COLOR(123,104,238))  // 适中板岩蓝
#define M_COLOR_SLATEBLUE                    (MAKE_COLOR(106, 90,205))  // 板岩蓝
#define M_COLOR_DARKSLATEBLUE                (MAKE_COLOR( 72, 61,139))  // 深板岩蓝
#define M_COLOR_LAVENDER                     (MAKE_COLOR(230,230,250))  // 薰衣草淡
#define M_COLOR_GHOSTWHITE                   (MAKE_COLOR(248,248,255))  // 幽灵白
           
// Blue-Green Series           
#define M_COLOR_MEDIUMBLUE                   (MAKE_COLOR(  0,  0,205))  // 适中蓝
#define M_COLOR_MIDNIGHTBLUE                 (MAKE_COLOR( 25, 25,112))  // 午夜蓝
#define M_COLOR_DARKBLUE                     (MAKE_COLOR(  0,  0,139))  // 深蓝
#define M_COLOR_NAVY                         (MAKE_COLOR(  0,  0,128))  // 海军蓝
#define M_COLOR_ROYALBLUE                    (MAKE_COLOR( 65,105,225))  // 皇家蓝
#define M_COLOR_CORNFLOWERBLUE               (MAKE_COLOR(100,149,237))  // 矢车菊蓝
#define M_COLOR_LIGHTSTEELBLUE               (MAKE_COLOR(176,196,222))  // 淡钢蓝
#define M_COLOR_LIGHTSLATEGRAY               (MAKE_COLOR(119,136,153))  // 浅板岩灰
#define M_COLOR_SLATEGRAY                    (MAKE_COLOR(112,128,144))  // 石板灰
#define M_COLOR_DODGERBLUE                   (MAKE_COLOR( 30,114,255))  // 道奇蓝
#define M_COLOR_ALICEBLUE                    (MAKE_COLOR(240,248,255))  // 爱丽丝蓝
#define M_COLOR_STEELBLUE                    (MAKE_COLOR( 70,130,180))  // 钢蓝
#define M_COLOR_LIGHTSKYBLUE                 (MAKE_COLOR(135,206,250))  // 淡天蓝
#define M_COLOR_SKYBLUE                      (MAKE_COLOR(135,206,235))  // 天蓝
#define M_COLOR_DEEPSKYBLUE                  (MAKE_COLOR(  0,191,255))  // 深天蓝
#define M_COLOR_LIGHTBLUE                    (MAKE_COLOR(173,216,230))  // 淡蓝
#define M_COLOR_POWDERBLUE                   (MAKE_COLOR(176,224,230))  // 火药蓝
#define M_COLOR_CADETBLUE                    (MAKE_COLOR( 95,158,160))  // 军校蓝
#define M_COLOR_AZURE                        (MAKE_COLOR(245,255,255))  // 蔚蓝
#define M_COLOR_LIGHTCYAN                    (MAKE_COLOR(240,255,255))  // 淡青
#define M_COLOR_PALETURQUOISE                (MAKE_COLOR(175,238,238))  // 苍白宝石绿
#define M_COLOR_AQUA                         (MAKE_COLOR(  0,255,255))  // 水绿
#define M_COLOR_DARKTURQUOISE                (MAKE_COLOR(  0,206,209))  // 深宝石绿
#define M_COLOR_DARKSLATEGRAY                (MAKE_COLOR( 47, 79, 79))  // 深石板灰
#define M_COLOR_DARKCYAN                     (MAKE_COLOR(  0,139,139))  // 深青色
#define M_COLOR_TEAL                         (MAKE_COLOR(  0,128,128))  // 水鸭色
#define M_COLOR_MEDIUMTURQUOISE              (MAKE_COLOR( 72,209,204))  // 适中宝石绿
#define M_COLOR_LIGHTSEEGREEN                (MAKE_COLOR( 32,178,170))  // 浅海样绿
#define M_COLOR_TURQUOISE                    (MAKE_COLOR( 64,224,208))  // 宝石绿
#define M_COLOR_AQUAMARINE                   (MAKE_COLOR(127,255,212))  // 碧绿
#define M_COLOR_MEDIUMAQUAMARINE             (MAKE_COLOR(102,205,170))  // 适中碧绿
#define M_COLOR_MEDIUMSPRINGGREEN            (MAKE_COLOR(  0,250,154))  // 适中春天绿
#define M_COLOR_SPRINGGREEN                  (MAKE_COLOR(  0,255,127))  // 春天绿
#define M_COLOR_MEDIUMSEEGREEN               (MAKE_COLOR( 60,179,113))  // 适中海洋绿
#define M_COLOR_SEEGREEN                     (MAKE_COLOR( 46,139, 87))  // 海洋绿
#define M_COLOR_LIGHTGREEN                   (MAKE_COLOR(144,238,144))  // 浅绿
#define M_COLOR_PALEGREEN                    (MAKE_COLOR(152,251,152))  // 苍白绿
#define M_COLOR_DARKSEEGREEN                 (MAKE_COLOR(143,188,143))  // 深海洋绿
#define M_COLOR_LIME                         (MAKE_COLOR( 50,205, 50))  // 莱姆色
#define M_COLOR_CHARTREUSE                   (MAKE_COLOR(127,255,  0))  // 查特酒绿
           
// Green-RED Series           
#define M_COLOR_FORESTGREEN                  (MAKE_COLOR( 34,139, 34))  // 森林绿
#define M_COLOR_LAWNGREEN                    (MAKE_COLOR(124,252,  0))  // 草坪绿
#define M_COLOR_GREENYELLOW                  (MAKE_COLOR(173,255, 47))  // 绿黄
#define M_COLOR_DARKOLIVEGREEN               (MAKE_COLOR( 85,107, 47))  // 深橄榄绿
#define M_COLOR_YELLOWGREEN                  (MAKE_COLOR(154,205, 50))  // 黄绿
#define M_COLOR_OLIVEDRAB                    (MAKE_COLOR( 34,139, 34))  // 橄榄褐
#define M_COLOR_BEIGE                        (MAKE_COLOR(245,245,220))  // 米色
#define M_COLOR_LIGHTRODYELLOW               (MAKE_COLOR( 34,139, 34))  // 浅秋黄
#define M_COLOR_IVORY                        (MAKE_COLOR(255,255,240))  // 象牙白
#define M_COLOR_OLIVE                        (MAKE_COLOR(128,128,  0))  // 橄榄
#define M_COLOR_DARKKHAKI                    (MAKE_COLOR(189,183,107))  // 深卡其布
#define M_COLOR_LEMONCHIFFON                 (MAKE_COLOR(255,250,205))  // 柠檬沙
#define M_COLOR_PALEGOLDROD                  (MAKE_COLOR(238,232,170))  // 灰秋
#define M_COLOR_KHAKI                        (MAKE_COLOR(240,230,140))  // 卡其布
#define M_COLOR_GOLDEN                       (MAKE_COLOR(255,215,  0))  // 金色
#define M_COLOR_CORNMILK                     (MAKE_COLOR(255,248,220))  // 玉米
#define M_COLOR_GOLDROD                      (MAKE_COLOR(218,165, 32))  // 秋天
#define M_COLOR_DARKGOLDROD                  (MAKE_COLOR(184,134, 11))  // 深秋
#define M_COLOR_FLORALWHITE                  (MAKE_COLOR(255,250,240))  // 白花
#define M_COLOR_OLDLACE                      (MAKE_COLOR(253,245,230))  // 浅米色
#define M_COLOR_WHEAT                        (MAKE_COLOR(245,222,179))  // 小麦
#define M_COLOR_MOCCASIN                     (MAKE_COLOR(255,228,181))  // 鹿皮
#define M_COLOR_ORANGE                       (MAKE_COLOR(255,165,  0))  // 橙色
#define M_COLOR_PAPAYAWHIP                   (MAKE_COLOR(255,239,213))  // 木瓜
#define M_COLOR_BLANCHEDALMOND               (MAKE_COLOR(255,235,205))  // 漂白的杏仁
#define M_COLOR_NAVAJOWHITE                  (MAKE_COLOR(255,222,173))  // 耐而节白
#define M_COLOR_ANTIQUEWHITE                 (MAKE_COLOR(250,235,215))  // 古白
#define M_COLOR_TAN                          (MAKE_COLOR(210,180,140))  // 晒
#define M_COLOR_BURLYWOOD                    (MAKE_COLOR(222,184,135))  // 树干
#define M_COLOR_BISQUE                       (MAKE_COLOR(255,228,196))  // 乳脂
#define M_COLOR_DARKORANGE                   (MAKE_COLOR(255,140,  0))  // 深橙色
#define M_COLOR_LINEN                        (MAKE_COLOR(255,240,230))  // 亚麻
#define M_COLOR_PERU                         (MAKE_COLOR(205,133, 63))  // 秘鲁
#define M_COLOR_SANDYBROWN                   (MAKE_COLOR(244,164, 96))  // 沙棕
#define M_COLOR_CHOCOLATE                    (MAKE_COLOR(210,105, 30))  // 巧克力
#define M_COLOR_SEASHELL                     (MAKE_COLOR(255,245,238))  // 海贝
#define M_COLOR_SIENNA                       (MAKE_COLOR(160, 82, 45))  // 土黄赭
#define M_COLOR_SALMON                       (MAKE_COLOR(255,160,122))  // 三文鱼
#define M_COLOR_CORAL                        (MAKE_COLOR(255,127, 80))  // 珊瑚红
#define M_COLOR_ORANGERED                    (MAKE_COLOR(255, 69,  0))  // 橙红
#define M_COLOR_TOMATO                       (MAKE_COLOR(255, 99, 71))  // 番茄
#define M_COLOR_MISTYROSE                    (MAKE_COLOR(255,228,225))  // 迷雾玫瑰
#define M_COLOR_BLOODYMEAT                   (MAKE_COLOR(250,128,114))  // 鲜肉
#define M_COLOR_LIGHTCORAL                   (MAKE_COLOR(240,128,128))  // 浅珊瑚红
#define M_COLOR_ROSEBROWN                    (MAKE_COLOR(188,143,143))  // 玫瑰棕
#define M_COLOR_INDIANRED                    (MAKE_COLOR(205, 92, 92))  // 浅粉红
#define M_COLOR_BROWN                        (MAKE_COLOR(165, 42, 42))  // 棕色
#define M_COLOR_FIREBRICK                    (MAKE_COLOR(178, 34, 34))  // 火砖
#define M_COLOR_DARKRED                      (MAKE_COLOR(139,  0,  0))  // 深红
#define M_COLOR_MAROON                       (MAKE_COLOR(128,  0,  0))  // 栗色
           
// Neutral Series           
#define M_COLOR_WHITESMOKE                   (MAKE_COLOR(245,245,245))  // 烟白
#define M_COLOR_GAINSBORO                    (MAKE_COLOR(220,220,220))  // 赶死部落
#define M_COLOR_LIGHTGRAY                    (MAKE_COLOR(211,211,211))  // 浅灰
#define M_COLOR_SILVER                       (MAKE_COLOR(192,192,192))  // 银色
#define M_COLOR_DARKGRAY                     (MAKE_COLOR( 73, 73, 73))  // 深灰
#define M_COLOR_DIMGRAY                      (MAKE_COLOR( 54, 54, 54))  // 暗灰

#define M_COLOR_COAL                         (MAKE_COLOR( 34, 35, 34))  // 煤炭黑


#ifdef __cplusplus
}
#endif

#endif



