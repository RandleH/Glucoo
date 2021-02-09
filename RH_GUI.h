#ifndef _RH_GUI_H
#define _RH_GUI_H
#include "RH_GUIConfigCheck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef RH_UTILITY_H
  #define GUI_LIMIT(a, lowerbound, upperbound)  (((double)(a) >= (upperbound)) ? upperbound : (((double)(a) <= (lowerbound)) ? (lowerbound) : (a) ))
  #define GUI_MIN(a,b)     (((a)<(b))?(a):(b))
  #define GUI_MAX(a,b)     (((a)>(b))?(a):(b))
  #define GUI_CENTER(a,b)  (((a)<(b))?((a)+(((b)-(a)+1)>>1)):((b)+(((a)-(b)+1)>>1)) )
#else
  #define GUI_LIMIT        __limit
  #define GUI_MIN          __min
  #define GUI_MAX          __max
  #define GUI_CENTER       __mid
#endif

#define GUI_FONT_Standard_Small        0
#define GUI_FONT_Standard_Middle       1

#define GUI_FONT_Bradley_Large         2
#define GUI_FONT_CourierNew_Middle     3
#define GUI_FONT_CourierNew_Large      4

#define GUI_ALIGN_LEFT      (0)
#define GUI_ALIGN_CENTER    (1)
#define GUI_ALIGN_RIGHT     (2)
 
 

// 声明: 无符号整型
typedef unsigned int uint;

// 声明: 以宏形式的索引或功能号
typedef unsigned int Macro_t;

// 声明: 某片区域的缓存信息
struct __BufferInfo_t{
	void*   pBuffer;
	size_t  width;
	size_t  height;
};
typedef struct __BufferInfo_t BufferInfo_t;

enum GUI_DrawMode_t{
	kInsertPixelMode,
	kAddPixelMode,
};
typedef enum GUI_DrawMode_t GUI_DrawMode_t;

extern void (*GUI_API_DrawArea)       (int x1,int y1,int x2,int y2,const Pixel_t* pixData);
extern void (*GUI_API_DrawPixel)      (int x ,int y ,const Pixel_t pixData);
extern void (*GUI_API_DelayMs)        (unsigned long ms);

#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
extern void (*GUI_API_DrawPageColumn) (unsigned int page,unsigned int column_start,unsigned int column_num,const Pixel_t* columnData);
#endif

extern void (*GUI_API_AssertParam)    (bool expression,const char* WHAT_IS_WRONG );


// 声明: 通用绘图函数
void    GUI_Init              (void);

void    GUI_AutoDisplayMode   (void);
void    GUI_ManualDisplayMode (void);

void    GUI_SetPenSize        (uint penSize);
uint    GUI_GetPenSize        (void);
void    GUI_SetPenColor       (Pixel_t color);
Pixel_t GUI_GetPenColor       (void);
void    GUI_SetBackColor      (Pixel_t color);
Pixel_t GUI_GetBackColor      (void);
void    GUI_SetFont           (int GUI_FONT_xxx);
void    GUI_SetTextPos        (uint x,uint y);

void    GUI_ClearPageArea     (uint page_start,uint page_end,uint column_start,uint column_end,...);
void    GUI_RefreashArea      (int x1,int y1,int x2,int y2);
void    GUI_RefreashPageArea  (uint page_start,uint page_end,uint column_start,uint column_end);
void    GUI_RefreashScreen    (void);


void    GUI_FillRect          (int  x1,int  y1,int x2,int y2);
void    GUI_FillCircle        (int  x ,int  y ,int r );
void    GUI_FillEllipse       (int  x ,int  y ,int rx,int ry,...);
void    GUI_FillQuadrilateral (int  x1,int  y1,int x2,int y2,int x3,int y3,int x4,int y4);

void    GUI_FillAll           (Pixel_t columnData); 
void    GUI_ClearScreen       (void);
void    GUI_ClearFrameBuffer  (void);

  
void    GUI_FillTriangle      (int x1,int y1,int x2,int y2,int x3,int y3);
  
void    GUI_DrawPixel         (int  x ,int   y);
void    GUI_DrawLine          (int  x1,int   y1,int   x2 ,int  y2);
void    GUI_DrawRect          (int  x1,int   y1,int   x2 ,int  y2);
void    GUI_DrawCircle        (int  x ,int   y ,int   r  );
void    GUI_DrawEllipse       (int  x ,int   y ,int   rx ,int  ry,...);
void    GUI_DrawWave          (int  A ,float w ,float phi,int  x_start,int  x_end,int  y_level,...);
void    GUI_DrawTriangle      (int  x1,int   y1,int    x2,int       y2,int     x3,int  y3);
 
void    GUI_BlurRect          (int  x1,int  y1,int  x2,int  y2,uint16_t radSize, uint16_t brPersentage);

void    GUI_DispChar          (unsigned char c);
void    GUI_DispCharAt        (unsigned char c,int x,int y,...);
void    GUI_DispChars         (unsigned char c,int num,...);//
void    GUI_DispWord          (const char* word,...);


// 声明: RGB测试功能号
#define GUI_TEST_RGB_HOR_RAINBOW    (0)
#define GUI_TEST_RGB_VER_RAINBOW    (1)
#define GUI_TEST_RGB_ROL_RAINBOW    (2)
#define GUI_TEST_RGB_HOR_BAR        (3)
#define GUI_TEST_RGB_VER_BAR        (4)
#define GUI_TEST_RGB_STEP           (5)     
// 声明: RGB测试的函数
void    GUI_TestRGB           (uint GUI_TEST_RGB_xxxx ,...);


#if GUI_DIALOG_DISPLAY

struct GUI_DialogBox_Button_t{
	uint        width;
	uint        height;
	const char* name;
	uint        x_left_top;
	uint        y_left_top;
	struct GUI_DialogBox_Button_t* nextButton;
};

struct GUI_DialogBox_t{
	uint x_start;
	uint x_end;
	uint y_start;
	uint y_end;

	struct GUI_DialogBox_Button_t* firstButton;
};

void    GUI_DialogBox         (struct GUI_DialogBox_t* p , const char* text,...);

#endif

#if GUI_ANIMATION_DISPLAY

// 声明: 动画演示的功能号
#define GUI_ANIM_PROGRESSBAR_STD_LR   (0)
#define GUI_ANIM_PROGRESSBAR_STD_UD   (1)
#define GUI_ANIM_VALUEBAR_IOS_LR      (2)
#define GUI_ANIM_VALUEBAR_IOS_UD      (3)
#define GUI_ANIM_PROGRESSLOOP         (4)

#define GUI_ANIM_SLIDESWITCH          (5)


// 声明: 绘制动画插件所需要的信息
struct GUI_AnimConfig_t{
	const char*  text;
	Macro_t      GUI_ANIM_xxxx;
	BYTE         ID;
	unsigned int x_pos;
	unsigned int y_pos;
	unsigned int height;
	unsigned int width;
	Pixel_t      themeColor;
	Pixel_t      backColor;
};

// 声明: 动画功能的函数
void   GUI_CreateAnimationSocket   (struct GUI_AnimConfig_t* config);
void   GUI_ShowAnimation           (BYTE ID,uint fp_0_255_,...);
void   GUI_HideAnimation           (BYTE ID);
void   GUI_DeleteAnimationSocket   (BYTE ID);

#endif

#if GUI_ICON_DISPLAY

// 声明: 图标演示的功能号
#define GUI_ICON_ARROW_UP    (0)
#define GUI_ICON_ARROW_DN    (1)
#define GUI_ICON_ARROW_LF    (2)
#define GUI_ICON_ARROW_RG    (3)
#define GUI_ICON_WIN10       (4)
// 声明: 绘制图标插件所需要的信息
struct GUI_IconConfig_t{
	const char*  text;
	Macro_t      GUI_ICON_xxxx;
	BYTE         ID;
	unsigned int x_pos;
	unsigned int y_pos;
	unsigned int size;
	Pixel_t      themeColor;
	bool         dispFrame;
};

// 声明: 图标功能的函数
void   GUI_CreateIconSocket        (struct GUI_IconConfig_t* config);
void   GUI_ChangeIconSocket        (struct GUI_IconConfig_t* newConfig,BYTE ID);
void   GUI_ShowIcon                (BYTE ID);


#endif

#if GUI_TRACE_WATCH_DISPLAY

// 声明: 数据跟踪演示的功能号
#define GUI_TRACE_LINEAR    (0)
#define GUI_TRACE_FILL      (1)
#define GUI_TRACE_COLUMN    (2)
#define GUI_TRACE_SCATTER   (3)

struct GUI_TraceData_t{
	int         *dataSource;
	const char  *dataName; 
	Pixel_t     dataColor;
	bool        displayON;
};
typedef struct GUI_TraceData_t GUI_TraceData_t;

struct GUI_TraceConfig_t{
	BYTE                     ID;
	Macro_t                  GUI_TRACE_xxxx;
	const char*              text;
  
	size_t                   recordSize; // !!!

	size_t                   dataNum;
	struct GUI_TraceData_t*  data;

	unsigned int             x_pos;
	unsigned int             y_pos;
	unsigned int             height;
	unsigned int             width;  // !!!
  
	bool                     GridON;
	bool                     LegacyON;
	bool                     ScaleON;
  
	Pixel_t                  themeColor;
    Pixel_t                  backColor;            
};
typedef struct GUI_TraceConfig_t GUI_TraceConfig_t;

void GUI_CreateTraceWatchSocket(struct GUI_TraceConfig_t* config);
void GUI_ShowTraceWatch(BYTE ID,size_t probe);


#endif





// 声明: 示例函数
#if GUI_DEMO
void    GUI_DEMO_MovingRect_1      (void);
void    GUI_DEMO_MovingRect_2      (void);
void    GUI_DEMO_MovingRect_3      (void);
  
void    GUI_DEMO_MovingEllipse_1   (void);

void    GUI_DEMO_MovingWave_1      (void);
void    GUI_DEMO_MovingWave_2      (void);
 
void    GUI_DEMO_Rotation_1        (void);
 
void    GUI_DEMO_Blink_1           (void);
   
void    GUI_DEMO_Pattern_1         (void);

void    GUI_DEMO_Smile             (void);//
void    GUI_DEMO_Rabbit            (void);//
void    GUI_DEMO_Window98          (void);//
void    GUI_DEMO_MacOS             (void);//
void    GUI_DEMO_WindTurbine       (void);//
void    GUI_DEMO_SUES              (void);//


void    GUI_DEMO_Microsoft_1       (void);


#if GUI_ANIMATION_DISPLAY
void    GUI_DEMO_ANIM_ProgressBar  (void);
#endif


#endif


#ifdef __cplusplus
 }
#endif

#endif



