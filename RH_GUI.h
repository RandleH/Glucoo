#ifndef _RH_GUI_H
#define _RH_GUI_H
#include "RH_GUIConfigCheck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define GUI_CLEAN
#define GUI_OVERLAP
#define GUI_DISPLAY_OFF
#define GUI_DISPLAY_ON

#define GUI_LIMIT(a, lowerbound, upperbound)  (((a) >= (upperbound)) ? upperbound : (((a) <= (lowerbound)) ? (lowerbound) : (a) ))
#define GUI_MIN(a,b)  ((a)<(b)?(a):(b))
#define GUI_MAX(a,b)  ((a)>(b)?(a):(b))


#define GUI_FONT_Standard_Small        0
#define GUI_FONT_Standard_Middle       1

#define GUI_FONT_Bradley_Large         2
#define GUI_FONT_CourierNew_Middle     3
#define GUI_FONT_CourierNew_Large      4

#define GUI_ALIGN_LEFT      (0)
#define GUI_ALIGN_CENTER    (1)
#define GUI_ALIGN_RIGHT     (2)



typedef unsigned int uint;
typedef uint         Macro_t;

extern void (*GUI_API_DrawArea)       (unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,const Pixel_t* pixData);
extern void (*GUI_API_DrawPixel)      (unsigned int x ,unsigned int y ,const Pixel_t pixData);
extern void (*GUI_API_DelayMs)        (unsigned long ms);

#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
extern void (*GUI_API_DrawPageColumn) (unsigned int page,unsigned int column_start,unsigned int column_num,const Pixel_t* columnData);
#endif


#if GUI_ASSERT
extern void (*GUI_API_AssertParam)    (bool expression,const char* WHAT_IS_WRONG );
#endif
void    GUI_Init              (void);

void    GUI_SetPenSize        (uint penSize);
uint    GUI_GetPenSize        (void);
void    GUI_SetPenColor       (Pixel_t color);
Pixel_t GUI_GetPenColor       (void);
void    GUI_SetBackColor      (Pixel_t color);
Pixel_t GUI_GetBackColor      (void);
void    GUI_SetFont           (int GUI_FONT_xxx);
void    GUI_SetTextPos        (uint x,uint y);

void    GUI_ClearPageArea     (uint page_start,uint page_end,uint column_start,uint column_end,...);
void    GUI_RefreashPageArea  (uint page_start,uint page_end,uint column_start,uint column_end);
void    GUI_RefreashScreen    (void);


void    GUI_FillRect          (uint x1,uint y1,uint x2,uint y2,...);
void    GUI_FillCircle        (uint x ,uint y ,int r ,...);
void    GUI_FillEllipse       (uint x ,uint y ,int rx, int ry,...);
void    GUI_FillAll           (Pixel_t columnData); 
void    GUI_ClearAll          (void);
void    GUI_ClearBuffer       (void);
  
void    GUI_FillTriangle      (int x1,int y1,int x2,int y2,int x3,int y3,...);
  
void    GUI_DrawPixel         (uint x ,uint  y ,...);
void    GUI_DrawLine          (int  x1,int   y1,int   x2 ,int  y2,...);
void    GUI_DrawRect          (uint x1,uint  y1,uint  x2 ,uint y2,...);
void    GUI_DrawCircle        (int  x ,int   y ,int   r  ,...);
void    GUI_DrawEllipse       (uint x ,uint  y ,int   rx ,int  ry,...);
void    GUI_DrawWave          (int  A ,float w ,float phi,int  x_start,int  x_end,int  y_level,...);
void    GUI_DrawTriangle      (uint x1,uint  y1,uint  x2 ,uint y2     ,uint x3   ,uint y3     ,...);

#define GUI_TEST_RGB_HOR_RAINBOW    (0)
#define GUI_TEST_RGB_VER_RAINBOW    (1)
#define GUI_TEST_RGB_ROL_RAINBOW    (2)
#define GUI_TEST_RGB_HOR_BAR        (3)
#define GUI_TEST_RGB_VER_BAR        (4)
#define GUI_TEST_RGB_STEP           (5)     
void    GUI_TestRGB           (uint GUI_TEST_RGB_xxxx ,...);

void    GUI_CONTI_DrawLine    (unsigned int (*p)[2],const size_t num,...);

void    GUI_DispChar          (unsigned char c,...);
void    GUI_DispCharAt        (unsigned char c,int x,int y,...);
void    GUI_DispChars         (unsigned char c,int num,...);//
void    GUI_DispWord          (const char* word,...);


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

#define GUI_ANIM_ProgressBar   (0)

struct GUI_Anim_t{
	const char*  text;
	Macro_t      GUI_ANIM_xxxx;
	uint         ID;
	uint         x_pos;
	uint         y_pos;
	uint         height;
	uint         width;
	Pixel_t      themeColor;
};

void   GUI_CreateAnimationSocket   (struct GUI_Anim_t* config);
void   GUI_ShowAnimation           (BYTE ID,uint fp_0_255_,...);
void   GUI_HideAnimation           (BYTE ID);
void   GUI_DeleteAnimationSocket   (BYTE ID);

#endif

#if GUI_ICON_DISPLAY

struct GUI_Icon_t{
	uint       size_AxA;
	uint       GUI_ICON_xxxx;
	uint       x_left_top;
	uint       y_left_top;
};

#endif

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



#endif



