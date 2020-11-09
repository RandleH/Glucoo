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


#define GUI_FONT_6X8        &GUI_Font6x8
#define GUI_FONT_8X16       &GUI_Font8x16

#define GUI_ALIGN_LEFT      (0)
#define GUI_ALIGN_CENTER    (1)
#define GUI_ALIGN_RIGHT     (2)


extern void (*GUI_API_DrawArea)       (unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,const Pixel_t* pixData);
extern void (*GUI_API_DrawPixel)      (unsigned int x ,unsigned int y ,const Pixel_t pixData);
extern void (*GUI_API_DelayMs)        (unsigned long ms);

#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
extern void (*GUI_API_DrawPageColumn) (unsigned int page,unsigned int column_start,unsigned int column_num,const Pixel_t* columnData);
#endif


#if GUI_ASSERT
extern void (*GUI_API_AssertParam)    (bool expression,const char* WHAT_IS_WRONG );
#endif

void    GUI_SetPenSize(unsigned int penSize);
unsigned int GUI_GetPenSize(void);
void    GUI_SetPenColor(Pixel_t color);
Pixel_t GUI_GetPenColor(void);
void    GUI_SetBackColor(Pixel_t color);
Pixel_t GUI_GetBackColor(void);

void    GUI_ClearPageArea   (unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end,...);
void    GUI_RefreashPageArea(unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end);
void    GUI_RefreashScreen(void);


void    GUI_FillRect        (unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,...);
void    GUI_FillCircle      (unsigned int x ,unsigned int y ,int r ,...);
void    GUI_FillEllipse     (unsigned int x ,unsigned int y ,int rx, int ry,...);
void    GUI_FillAll         (Pixel_t columnData); 
void    GUI_ClearAll        (void);

void    GUI_FillTriangle    (int x1,int y1,int x2,int y2,int x3,int y3,...);

void    GUI_DrawPixel       (unsigned int x ,unsigned int y ,...);
void    GUI_DrawLine        (int          x1,int          y1,int          x2 ,int          y2,...);
void    GUI_DrawRect        (unsigned int x1,unsigned int y1,unsigned int x2 ,unsigned int y2,...);
void    GUI_DrawCircle      (unsigned int x ,unsigned int y ,int          r  ,...);
void    GUI_DrawEllipse     (unsigned int x ,unsigned int y ,int          rx ,int          ry,...);
void    GUI_DrawWave        (int          A ,float        w ,float        phi,int          x_start,int          x_end,int          y_level,...);
void    GUI_DrawTriangle    (unsigned int x1,unsigned int y1,unsigned int x2 ,unsigned int y2     ,unsigned int x3   ,unsigned int y3     ,...);

void    GUI_CONTI_DrawLine  (unsigned int (*p)[2],const size_t num,...);

void    GUI_DispChar        (unsigned char c,...);
void    GUI_DispCharAt      (unsigned char c,int x,int y,...);//
void    GUI_DispChars       (unsigned char c,int cnt);//

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
#endif



#endif



