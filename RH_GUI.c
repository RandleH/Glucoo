
#include "RH_GUI.h"
#include "RH_Utility.h"
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>




#if defined ( __CC_ARM )
  #pragma anon_unions
#endif

//===================================================== Common =======================================================//
//===================================================== Common =======================================================//
//===================================================== Common =======================================================//

#define M_SCREEN_MAIN       (0)
#define M_SCREEN_COPY       (1)
#define M_SCREEN_BLUR       (2)
#define M_SCREEN_03         (3) // Unused
#define M_SCREEN_04         (4) // Unused
#define M_SCREEN_05         (5) // Unused
#define M_SCREEN_06         (6) // Unused
#define M_SCREEN_07         (7) // Unused
#define M_SCREEN_08         (8) // Unused
#define M_SCREEN_09         (9) // Unused

#define M_SCREEN_CNT        (3U)

//================================================= End of Common ====================================================//
//================================================= End of Common ====================================================//
//================================================= End of Common ====================================================//

//==================================================== API Handle =====================================================//
//==================================================== API Handle =====================================================//
//==================================================== API Handle =====================================================//

void __attribute__((weak)) GUI_DrawArea(int x1,int y1,int x2,int y2,const Pixel_t* pixData){
// THIS MAY COST SOME TIME.
}

void __attribute__((weak)) GUI_DummyDrawPixel(int x,int y,const Pixel_t pixData){
// IF U DONT GIVE ME A PEN, HOW CAN I DRAW !?
}

void __attribute__((weak)) GUI_AsserParam(bool expression,const char* WHAT_IS_WRONG){
// DONT KEEP MY MOTH SHUT, I GOT A PROBLEM TO REPORT.
}

void (*GUI_API_DrawArea)      (int x1,int y1,int x2,int y2,const Pixel_t* pixData) = GUI_DrawArea;

void (*GUI_API_DrawPixel)     (int x ,int y ,const Pixel_t pixData) = GUI_DummyDrawPixel;

void (*GUI_API_DelayMs)       (unsigned long ms) = NULL;

 #if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
void (*GUI_API_DrawPageColumn)(unsigned int page,unsigned int column_start,unsigned int column_num,const Pixel_t* data) = NULL;
#endif

void (*GUI_API_AssertParam)   (bool expression,const char* WHAT_IS_WRONG )  = NULL;



//================================================ End of API Handle ==================================================//
//================================================ End of API Handle ==================================================//
//================================================ End of API Handle ==================================================//

//==================================================  Pixel Config ====================================================//
//==================================================  Pixel Config ====================================================//
//==================================================  Pixel Config ====================================================//

#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
union PixelUnit_t{
    struct __BYTE_BIT{
        Pixel_t bit0 : 1;
        Pixel_t bit1 : 1;
        Pixel_t bit2 : 1;
        Pixel_t bit3 : 1;
        Pixel_t bit4 : 1;
        Pixel_t bit5 : 1;
        Pixel_t bit6 : 1;
        Pixel_t bit7 : 1;
    };
    Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;

#elif ( GUI_DISPLAY_MODE == GUI_SINGLE_PIXEL )

#if ( GUI_COLOR_TYPE == GUI_1Bit)

union PixelUnit_t{
    struct{
        uint8_t bit : 1;
    };
      Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;


#elif ( GUI_COLOR_TYPE == GUI_RGB565 )

#ifndef RH_UTILITY_H
union PixelUnit_t{
    struct{
        uint8_t B : 5;
        uint8_t G : 6;
        uint8_t R : 5;
    };
      Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;
#else
typedef __UNION_PixelRGB565_t PixelUnit_t;
#endif  //  <<-- Condition for < PixelUnit_t >

#elif ( GUI_COLOR_TYPE == GUI_RGB888 )

#ifndef RH_UTILITY_H
union PixelUnit_t{
    struct{
        uint8_t B : 8;
        uint8_t G : 8;
        uint8_t R : 8;
    };
      Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;
#else
typedef __UNION_PixelRGB888_t PixelUnit_t;
#endif  //  <<-- Condition for < PixelUnit_t >

#endif  //  <<-- Condition for < GUI_COLOR_TYPE >

#endif  //  <<-- Condition for < GUI_DISPLAY_MODE >

//=============================================== End of Pixel Config ===============================================//
//=============================================== End of Pixel Config ===============================================//
//=============================================== End of Pixel Config ===============================================//

//==================================================  Font Config ===================================================//
//==================================================  Font Config ===================================================//
//==================================================  Font Config ===================================================//

 #include "RH_Font.h"

extern __FontChar_t __FONT_STD6X8[];
extern __FontChar_t __FONT_STD8X16[];

#if GUI_FONT_EXTENTION
extern __FontChar_t __FONT_BRADLEY_LARGE[];
extern __FontChar_t __FONT_COURIERNEW13X16[];
extern __FontChar_t __FONT_COURIERNEW10X12[];
#endif


//================================================ End of Font Config ================================================//
//================================================ End of Font Config ================================================//
//================================================ End of Font Config ================================================//

//================================================= Internal Config ==================================================//
//================================================= Internal Config ==================================================//
//================================================= Internal Config ==================================================//

 #include <stdlib.h>

#ifndef __malloc
 #define __malloc(size)             malloc(size)
#endif

#ifndef __memcpy
 #define __memcpy(des,src,size)     memcpy(des,src,size)
#endif

#ifndef __free
 #define __free(p)                  free(p)
#endif

#ifndef __exit
 #define __exit(express)            if(express) return
#endif

#ifndef __exitReturn
 #define __exitReturn(express,res)  if(express) return res
#endif

struct __GUI_XY_t{
    unsigned int x;
    unsigned int y;
};
typedef struct __GUI_XY_t __GUI_XY_t;

#if GUI_ANIMATION_DISPLAY
struct __AnimationConfigChain{
    struct GUI_AnimConfig_t config;
    struct __AnimationConfigChain* nextConfig;
    void (*insertFunc)(struct __AnimationConfigChain*,uint fp);
    void (*removeFunc)(struct __AnimationConfigChain*);
};

typedef struct __AnimationConfigChain __AnimationConfigChain;
#endif

#if GUI_ICON_DISPLAY
struct __IconConfigChain{
    struct GUI_IconConfig_t  config;
    struct __IconConfigChain* nextConfig;
    void (*insertFunc)(struct __IconConfigChain*);
    void (*removeFunc)(struct __IconConfigChain*);
};

typedef struct __IconConfigChain __IconConfigChain;
#endif

#if GUI_TRACE_WATCH_DISPLAY
struct __TraceWatchConfigChain{
    struct GUI_TraceConfig_t config;
    int* buffer;
    struct __TraceWatchConfigChain* nextConfig;
    void (*insertFunc)(struct __TraceWatchConfigChain*);
    void (*removeFunc)(struct __TraceWatchConfigChain*);
};

typedef struct __TraceWatchConfigChain __TraceWatchConfigChain;
#endif

#if GUI_MENU_DISPLAY
struct __MenuConfigChain{
    struct __MenuConfigChain* nextConfig;
};
#endif

struct __AreaRefreashChain{
    int xs;
    int ys;
    int xe;
    int ye;
    struct __AreaRefreashChain* nextAreaRefreash;
};
typedef struct __AreaRefreashChain __AreaRefreashChain;

static struct __Screen_t{
#if   ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    PixelUnit_t buffer[M_SCREEN_CNT][ GUI_PAGEs  ][ GUI_X_WIDTH ];
 #elif ( GUI_DISPLAY_MODE == GUI_SINGLE_PIXEL )
    PixelUnit_t buffer[M_SCREEN_CNT][ GUI_Y_WIDTH][ GUI_X_WIDTH ];
#endif
    Pixel_t          bkColor;
    Pixel_t          penColor;
    uint             penSize;
    
    __GUI_XY_t       txtPos;
    __FontChar_t*    pFont;
    E_BlurMethod_t   BlurMethod;
    
    size_t           allocated_byte;

    bool             autoDisplayMode;

    __AreaRefreashChain*     areaNeedRefreashHeadNode;
    size_t                   areaNeedRefreashNodeCnt;
    size_t                   areaNeedRefreashPixelCnt;
//仅适用于动画功能
#if GUI_ANIMATION_DISPLAY
    __AnimationConfigChain*  cfgAnimationHeadNode;
    size_t                   cfgAnimationNodeCnt;
#endif
//仅适用于图标功能
#if GUI_ICON_DISPLAY
    __IconConfigChain*       cfgIconHeadNode;
    size_t                   cfgIconNodeCnt;
#endif
//仅适用于数据跟踪功能
#if GUI_TRACE_WATCH_DISPLAY
    __TraceWatchConfigChain* cfgTraceHeadNode;
    size_t                   cfgTraceNodeCnt;
#endif

}Screen;


// 声明: 插入一个像素点的函数接口
typedef void (*func_ApplyPixelMethod)  (int x,int y,Pixel_t param             ,BufferInfo_t* pBufferInfo);
static  void __ApplyPixel_mark         (int x,int y,Pixel_t nan               ,BufferInfo_t* pBufferInfo);
static  void __ApplyPixel_fill         (int x,int y,Pixel_t color             ,BufferInfo_t* pBufferInfo);
static  void __ApplyPixel_lightness    (int x,int y,Pixel_t br_100            ,BufferInfo_t* pBufferInfo);
static  void __ApplyPixel_unzero       (int x,int y,Pixel_t color             ,BufferInfo_t* pBufferInfo);
static  void __ApplyPixel_moveBlur     (int x,int y,Pixel_t nan               ,BufferInfo_t* pBufferInfo);
static  void __ApplyPixel_reverse      (int x,int y,Pixel_t color             ,BufferInfo_t* pBufferInfo);

/*===========================================
 > 在指定缓存区,标记一个点
============================================*/
static void __ApplyPixel_mark(int x,int y,Pixel_t color,BufferInfo_t* pBufferInfo){
    bool* p        = pBufferInfo->pBuffer;
    size_t width   = pBufferInfo->width;
    size_t height  = pBufferInfo->height;

    __exit( x>=width || y>=height || x<0 || y<0 );

    *(p+(y*width)+x) = 1;
}

/*===========================================
 > 在指定缓存区,填充一个像素点,颜色随设定
============================================*/
static void __ApplyPixel_fill(int x,int y,Pixel_t color,BufferInfo_t* pBufferInfo){
    
    PixelUnit_t* p = pBufferInfo->pBuffer;
    size_t width   = pBufferInfo->width;
    size_t height  = pBufferInfo->height;

    __exit( x>=width || y>=height || x<0 || y<0 );

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    int temp = y&0x07;
    switch(temp){
        case 0:(p+(y*height)+x)->bit0 = (color&0x01);break;
        case 1:(p+(y*height)+x)->bit1 = (color&0x01);break;
        case 2:(p+(y*height)+x)->bit2 = (color&0x01);break;
        case 3:(p+(y*height)+x)->bit3 = (color&0x01);break;
        case 4:(p+(y*height)+x)->bit4 = (color&0x01);break;
        case 5:(p+(y*height)+x)->bit5 = (color&0x01);break;
        case 6:(p+(y*height)+x)->bit6 = (color&0x01);break;
        case 7:(p+(y*height)+x)->bit7 = (color&0x01);break;
        default:break;
    }
#else
    p[y*width+x].data = color;
#endif
}

/*===========================================
 > 在指定缓冲区,如果为0,则填充像素
============================================*/
static void __ApplyPixel_unzero(int x,int y,Pixel_t color,BufferInfo_t* pBufferInfo){
    PixelUnit_t* p = pBufferInfo->pBuffer;
    size_t width   = pBufferInfo->width;
    size_t height  = pBufferInfo->height;

    __exit( x>=width || y>=height || x<0 || y<0 );
    
    if((p+(y*height)+x)->data == 0){
        (p+(y*height)+x)->data = color;
    }
}

/*===========================================
 > 从虚化显存区拷贝一个像素至指定缓冲区 「耦合」
============================================*/
static void __ApplyPixel_moveBlur(int x,int y,Pixel_t color,BufferInfo_t* pBufferInfo){

    size_t width   = pBufferInfo->width;
    size_t height  = pBufferInfo->height;
    __exit( x>=width || y>=height || x<0 || y<0 || width>GUI_X_WIDTH || height>GUI_Y_WIDTH);
    Screen.buffer[M_SCREEN_MAIN][y][x].data = Screen.buffer[M_SCREEN_BLUR][y][x].data;
}

/*===========================================
 > 在主屏显存区调节像素的亮度 「耦合」
============================================*/
static void __ApplyPixel_lightness(int x,int y,Pixel_t br_100,BufferInfo_t* pBufferInfo){
    size_t width   = pBufferInfo->width;
    size_t height  = pBufferInfo->height;
    __exit( x>=width || y>=height || x<0 || y<0 || width>GUI_X_WIDTH || height>GUI_Y_WIDTH);
    
    Screen.buffer[M_SCREEN_MAIN][y][x].R = GUI_LIMIT((signed)(Screen.buffer[M_SCREEN_MAIN][y][x].R*br_100/100) , 0 , ((1<<8)-1));
    Screen.buffer[M_SCREEN_MAIN][y][x].G = GUI_LIMIT((signed)(Screen.buffer[M_SCREEN_MAIN][y][x].G*br_100/100) , 0 , ((1<<8)-1));
    Screen.buffer[M_SCREEN_MAIN][y][x].B = GUI_LIMIT((signed)(Screen.buffer[M_SCREEN_MAIN][y][x].B*br_100/100) , 0 , ((1<<8)-1));
}

/*===========================================
 > 在主屏显存区像素颜色取反 「耦合」
============================================*/
static void __ApplyPixel_reverse(int x,int y,Pixel_t color,BufferInfo_t* pBufferInfo){
    size_t width   = pBufferInfo->width;
    size_t height  = pBufferInfo->height;
    __exit( x>=width || y>=height || x<0 || y<0 || width>GUI_X_WIDTH || height>GUI_Y_WIDTH);
    
    PixelUnit_t temp = {.data = Screen.buffer[M_SCREEN_MAIN][y][x].data};
#if ( GUI_COLOR_TYPE == GUI_RGB888 )
    temp.B = 0xff - temp.B;
    temp.G = 0xff - temp.G;
    temp.R = 0xff - temp.R;
#else
    while(1);
#endif
    Screen.buffer[M_SCREEN_MAIN][y][x].data = temp.data;
}


static void      __Clear_gram_all  (void                                      );
static void      __Clear_gram_part (               int xs,int ys,int xe,int ye);
static Pixel_t*  __Clone_gram_part (Pixel_t* __dst,int xs,int ys,int xe,int ye);
static Pixel_t*  __Clone_gram_all  (Pixel_t* __dst                            );
#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
static void      __Clear_gram_page (               int ps,int pe,int cs,int ce);
#endif
/*====================================
 > 清空显存
=====================================*/
static void __Clear_gram_all(void){
    if(sizeof(Pixel_t) == 1 || Screen.bkColor == GUI_COLOR_BLACK)
 #if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
        memset(Screen.buffer[M_SCREEN_MAIN], Screen.bkColor ,sizeof(Pixel_t)*(GUI_PAGEs   * GUI_X_WIDTH));
#else
        memset(Screen.buffer[M_SCREEN_MAIN], Screen.bkColor ,sizeof(Pixel_t)*(GUI_X_WIDTH * GUI_Y_WIDTH));
#endif
    else
        for(size_t i=0;i<GUI_Y_WIDTH*GUI_X_WIDTH;i++){
            *(&(Screen.buffer[M_SCREEN_MAIN][0][0].data)+i) = Screen.bkColor;
        }
}

static void __Clear_gram_part(int xs,int ys,int xe,int ye){
    if(sizeof(Pixel_t) == 1 || Screen.bkColor == GUI_COLOR_BLACK)
 #if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
        //...//
#else
        for(size_t y=ys;y<=ye;y++){
            memset(&(Screen.buffer[M_SCREEN_MAIN][y][xs].data), Screen.bkColor ,sizeof(Pixel_t)*(xe-xs+1));
        }
#endif
    else
        for(int y=ys;y<=ye;y++){
#if (GUI_COLOR_TYPE == GUI_RGB565)
            __memsetWORD(&(Screen.buffer[M_SCREEN_MAIN][y][xs].data),Screen.bkColor,xe-xs+1);
#else
            //...//
#endif
        }
}

/*====================================
 > 清空显存,仅限Page-Column模式
=====================================*/
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
static void __Clear_gram_page(int ps,int pe,int cs,int ce){
    Pixel_t* p;
    int length = ce - cs+1;
    for(int page=ps;page<=pe;page++){
        p  = (Pixel_t*)&Screen.buffer[M_SCREEN_MAIN][page];
        p += cs;
        memset(p, Screen.bkColor ,(length)*sizeof(Screen.buffer[M_SCREEN_MAIN][0][0].data));
    }
}
#endif

/*===================================
 > 取出显存一片区域,数据类型为通用Pixel_t
=====================================*/

static Pixel_t* __Clone_gram_part(Pixel_t* __dst,int xs,int ys,int xe,int ye){
    if(sizeof(Pixel_t) == sizeof(PixelUnit_t))
        return (Pixel_t*)__memgrab_Area(__dst, Screen.buffer[M_SCREEN_MAIN][0], sizeof(PixelUnit_t), GUI_X_WIDTH, xs, ys, xe, ye);
    else{
        while(1);// Error, memory should be aligned in bytes.
    }
}

static Pixel_t* __Clone_gram_all(Pixel_t* __dst){
    return (Pixel_t*)memmove(__dst, Screen.buffer[M_SCREEN_MAIN][0], GUI_X_WIDTH*GUI_Y_WIDTH*sizeof(PixelUnit_t));
}

/*====================================
 > 挂起一块待显示区域
=====================================*/
static void __addAreaNeedRefreash(int xs,int ys,int xe,int ye){
    __AreaRefreashChain* pConfig    = Screen.areaNeedRefreashHeadNode;
    __AreaRefreashChain* pTmpConfig = (__AreaRefreashChain*)__malloc(sizeof(struct __AreaRefreashChain));

    //...//
    pTmpConfig->xs = xs;
    pTmpConfig->ys = ys;
    pTmpConfig->xe = xe;
    pTmpConfig->ye = ye;
    pTmpConfig->nextAreaRefreash = NULL;

    if(pConfig == NULL)
        Screen.areaNeedRefreashHeadNode = pTmpConfig;
    else{
        do{
            if(pConfig->nextAreaRefreash == NULL){
                pConfig->nextAreaRefreash = pTmpConfig;
                break;
            }
            pConfig = pConfig->nextAreaRefreash;
        }while(1);
    }

    Screen.areaNeedRefreashPixelCnt += (xe-xs+1)*(ye-ys+1);
    Screen.areaNeedRefreashNodeCnt++;
}

/*====================================
 > 矢量基本图形
=====================================*/
//           [内部][图形功能函数]          [相关属性参数]                                            [画笔粗细]     [画笔颜色]        [画布属性]                 [绘图方法]
static void __Graph_circle_raw     (int x ,int y ,int d ,                                   /************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_circle_edged   (int x ,int y ,int d ,                                   size_t penSize,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_circle_fill    (int x ,int y ,int d ,                                   /************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);


static void __Graph_line_raw       (int x1,int y1,int x2,int y2,                            /************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_line_edged     (int x1,int y1,int x2,int y2,                            size_t penSize,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_line_sausage   (int x1,int y1,int x2,int y2,                            size_t penSize,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);

static void __Graph_quad_raw       (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,/************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_quad_fill      (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,/************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);

static void __Graph_triangle_raw   (int x1,int y1,int x2,int y2,int x3,int y3,              /************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_triangle_fill  (int x1,int y1,int x2,int y2,int x3,int y3,              /************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);


static void __Graph_rect_raw       (int xs,int ys,int xe,int ye,                            /************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_rect_edged     (int xs,int ys,int xe,int ye,                            size_t penSize,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);
static void __Graph_rect_fill      (int xs,int ys,int xe,int ye,                            /************/ Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx);


/*====================================
 > 局部高斯虚化
=====================================*/
static void __Blur_gus_part      (int xs,int ys,int xe,int ye, uint16_t radSize, uint16_t br_100, BufferInfo_t* pBufferInfo);
static void __Blur_avg_part      (int xs,int ys,int xe,int ye, uint16_t radSize, uint16_t br_100, BufferInfo_t* pBufferInfo);

static void __Blur_gus_part      (int xs,int ys,int xe,int ye, uint16_t radSize, uint16_t br_100, BufferInfo_t* pBufferInfo){
    
    int width   = xe-xs+1;
    int height = ye-ys+1;
    
    Pixel_t* pBuffer = (Pixel_t*)__malloc((width)*(height)*sizeof(PixelUnit_t));
    
#if ( GUI_COLOR_TYPE == GUI_RGB888 )
    // [!] <__UNION_PixelRGB888_t> should share the same size with <PixelUnit_t>
    
    __ImageRGB888_t src = {
        .pBuffer = (__UNION_PixelRGB888_t*)__Clone_gram_part(pBuffer, xs, ys, xe, ye),
        .width   = width,
        .height  = height
    };
    __ImageRGB888_t* pDst = __Create_ImgRGB888(width, height);
    __Blur_Gussian_ImgRGB888(&src, pDst, radSize, br_100);
    for(int y=ys;y<=ye;y++){
        memcpy(&Screen.buffer[M_SCREEN_BLUR][y][xs], &pDst->pBuffer[(y-ys)*(pDst->width)], pDst->width*sizeof(__UNION_PixelRGB888_t));
    }
    
    __Free_ImgRGB888(pDst);
#endif
    
}

static void __Blur_avg_part      (int xs,int ys,int xe,int ye, uint16_t radSize, uint16_t br_100, BufferInfo_t* pBufferInfo){
    int width   = xe-xs+1;
    int height = ye-ys+1;
    
    
    Pixel_t* pBuffer = (Pixel_t*)__malloc((width)*(height)*sizeof(PixelUnit_t));
#if ( GUI_COLOR_TYPE == GUI_RGB888 )
    // [!] <__UNION_PixelRGB888_t> should share the same size with <PixelUnit_t>
    __ImageRGB888_t src = {
        .pBuffer = (__UNION_PixelRGB888_t*)__Clone_gram_part(pBuffer, xs, ys, xe, ye),
        .width   = width,
        .height  = height
    };
    __ImageRGB888_t* pDst = __Create_ImgRGB888(width, height);
    __Blur_Average_ImgRGB888(&src, pDst, radSize, br_100);
    for(int y=ys;y<=ye;y++){
        memcpy(&Screen.buffer[M_SCREEN_BLUR][y][xs], &pDst->pBuffer[(y-ys)*(pDst->width)], pDst->width*sizeof(__UNION_PixelRGB888_t));
    }
    
    __Free_ImgRGB888(pDst);
#endif
}


/*====================================
 > 插入一个填充圆
=====================================*/
static void __Graph_circle_fill(int x, int y, int d,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    int r = d>>1;
    int p = 3-(r<<1);
    int x_tmp = 0,y_tmp = r;
    bool eps  = (d%2==0);
    
    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x     + x_tmp ,y     + cnt,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - x_tmp ,y     + cnt,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + x_tmp ,y+eps - cnt,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - x_tmp ,y+eps - cnt,penColor,pBufferInfo );
        }

        cnt = x_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x     + y_tmp ,y     + cnt,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - y_tmp ,y     + cnt,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + y_tmp ,y+eps - cnt,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - y_tmp ,y+eps - cnt,penColor,pBufferInfo );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
}

/*====================================
 > 插入一个空心圆,线宽随设定
=====================================*/
static void __Graph_circle_edged(int x, int y, int d,size_t penSize,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){
    int r = d>>1;
    int r_ex  = r;
    int r_in  = (int)(r-penSize);
    
    int x_ex_tmp = 0;
    int y_ex_tmp = r_ex;
    int x_in_tmp = 0;
    int y_in_tmp = r_in;
    int p_ex  = 3-2*r_ex;
    int p_in  = 3-2*r_in;
    
    bool eps  = (d%2==0);
    
    for(;x_ex_tmp<y_ex_tmp;x_ex_tmp++,x_in_tmp++){
        for(int Y = y_in_tmp;Y<y_ex_tmp;Y++){
            (*Call_ApplyPixel_xxxx)(x     + x_ex_tmp ,y     + Y        ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - x_ex_tmp ,y     + Y        ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + x_ex_tmp ,y+eps - Y        ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - x_ex_tmp ,y+eps - Y        ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + Y        ,y     + x_ex_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - Y        ,y     + x_ex_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + Y        ,y+eps - x_ex_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - Y        ,y+eps - x_ex_tmp ,penColor,pBufferInfo );
        }

        if(p_ex <= 0){
            p_ex += (x_ex_tmp<<2) + 6;
        }else{
            p_ex += ((x_ex_tmp-y_ex_tmp)<<2) + 10;
            y_ex_tmp--;
        }
        if(p_in <= 0){
            p_in += (x_in_tmp<<2) + 6;
        }else{
            p_in += ((x_in_tmp-y_in_tmp)<<2) + 10;
            y_in_tmp--;
        }
    }
}

/*====================================
 > 插入一个空心圆,线宽为1
=====================================*/
static void __Graph_circle_raw(int x ,int y ,int d ,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    int r    = d>>1;
    int p    = 3-2*r;
    bool eps = (d%2==0);
    for(int x_tmp=0,y_tmp = r;x_tmp<=y_tmp;x_tmp++){
            (*Call_ApplyPixel_xxxx)(x     + x_tmp ,y     + y_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - x_tmp ,y     + y_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + x_tmp ,y+eps - y_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - x_tmp ,y+eps - y_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + y_tmp ,y     + x_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - y_tmp ,y     + x_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x     + y_tmp ,y+eps - x_tmp ,penColor,pBufferInfo );
            (*Call_ApplyPixel_xxxx)(x+eps - y_tmp ,y+eps - x_tmp ,penColor,pBufferInfo );

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
}

/*====================================
 > 插入一个四分之一填充圆,第1象限
=====================================*/
static void __insertFilledQuartCircle_1(int x ,int y ,int r ,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    int p = 3-(r<<1);
    int x_tmp = 0,y_tmp = r;

    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x+x_tmp,y-cnt,penColor,pBufferInfo );
        }

        cnt = x_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x+y_tmp,y-cnt,penColor,pBufferInfo );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
}

/*====================================
 > 插入一个四分之一填充圆,第2象限
=====================================*/
static void __insertFilledQuartCircle_2(int x ,int y ,int r ,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    int p = 3-(r<<1);
    int x_tmp = 0,y_tmp = r;

    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x-x_tmp,y-cnt,penColor,pBufferInfo );
        }

        cnt = x_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x-y_tmp,y-cnt,penColor,pBufferInfo );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
}

/*====================================
 > 插入一个四分之一填充圆,第3象限
=====================================*/
static void __insertFilledQuartCircle_3(int x ,int y ,int r ,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    int p = 3-(r<<1);
    int x_tmp = 0,y_tmp = r;

    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x-x_tmp,y+cnt,penColor,pBufferInfo );
        }

        cnt = x_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x-y_tmp,y+cnt,penColor,pBufferInfo );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
}

/*====================================
 > 插入一个四分之一填充圆,第4象限
=====================================*/
static void __insertFilledQuartCircle_4(int x ,int y ,int r ,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    int p = 3-(r<<1);
    int x_tmp = 0,y_tmp = r;

    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x+x_tmp,y+cnt,penColor,pBufferInfo );
        }

        cnt = x_tmp+1;
        while(cnt--){
            (*Call_ApplyPixel_xxxx)(x+y_tmp,y+cnt,penColor,pBufferInfo );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
}


/*====================================
 > 插入直线，线宽为1
=====================================*/
static void __Graph_line_raw(int x1 ,int y1 ,int x2 ,int y2 ,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){

    int x_min = (int)(GUI_MIN(x1,x2));
    int x_max = (int)(GUI_MAX(x1,x2));
    int y_min = (int)(GUI_MIN(y1,y2));
    int y_max = (int)(GUI_MAX(y1,y2));
    int delta_x    = (int)( x_max - x_min );
    int delta_y    = (int)( y_max - y_min );

    int type = (int)(( ((y2-y1)*(x2-x1)<0) << 1 ) | (delta_y > delta_x));

    if(delta_y > delta_x){
        int temp = delta_x;
        delta_x = delta_y;
        delta_y = temp;
    }
    
    int j = 0;
    int e = 0;
    (*Call_ApplyPixel_xxxx)(x1,y1,penColor,pBufferInfo);
    (*Call_ApplyPixel_xxxx)(x2,y2,penColor,pBufferInfo);
    for(int i = 0;i < delta_x;i++){
        switch(type){
            case 0:(*Call_ApplyPixel_xxxx)(x_min+i,y_min+j,penColor,pBufferInfo);break;
            case 1:(*Call_ApplyPixel_xxxx)(x_min+j,y_min+i,penColor,pBufferInfo);break;
            case 2:(*Call_ApplyPixel_xxxx)(x_min+i,y_max-j,penColor,pBufferInfo);break;
            case 3:(*Call_ApplyPixel_xxxx)(x_min+j,y_max-i,penColor,pBufferInfo);break;
        }
        e += delta_y;
        if( 2*( e + delta_y ) > delta_x){
            j++;
            e -= delta_x;
        }
    }
}

/*====================================
 > 插入直线,线宽随设定
=====================================*/
static void __Graph_line_edged(int x1,int y1,int x2,int y2,size_t penSize,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    __Graph_line_raw(x1,y1,x2,y2,penColor,pBufferInfo,Call_ApplyPixel_xxxx);

    if(penSize > 1){

        //                -----------------------------------         ----------------------------------------------
        //              /       penSize * penSize * K^2              /     0.25 * penSize * penSize * (y1-y2)^2
        // x_offset =  /    -------------------------------    =    /   -----------------------------------------
        //           \/             4 * ( K^2 + 1 )               \/        ( K^2 + 1 ) * (x1-x2)^2
        
        //                -----------------------------------
        //              /         penSize * penSize
        // y_offset =  /    -------------------------------
        //           \/             4 * ( K^2 + 1 )

        int x_offset = 0;
        int y_offset = 0;
        int x11=0,y11=0,x22=0,y22=0,x33=0,y33=0,x44=0,y44=0;
        switch(__Dir_Line(x1,y1,x2,y2)){
            case  1://斜率为正
            case  0://水平直线
                x_offset = (int)lround(sqrt( (0.25*(y1-y2)*(y1-y2)*penSize*penSize/((x1-x2)*(x1-x2))) / (1.0*(y1-y2)*(y1-y2)/((x1-x2)*(x1-x2))+1) ));
                y_offset = (int)lround(sqrt( 0.25*penSize*penSize/((y1-y2)*(y1-y2)/(1.0*(x1-x2)*(x1-x2))+1) ));
        
                x11 = x1+x_offset; y11 = y1-y_offset;
                x22 = x1-x_offset; y22 = y1+y_offset;
                x33 = x2-x_offset; y33 = y2+y_offset;
                x44 = x2+x_offset; y44 = y2-y_offset;
                break;
            case -1://斜率为负
                x_offset = (int)lround(sqrt( (0.25*(y1-y2)*(y1-y2)*penSize*penSize/((x1-x2)*(x1-x2))) / (1.0*(y1-y2)*(y1-y2)/((x1-x2)*(x1-x2))+1) ));
                y_offset = (int)lround(sqrt( 0.25*penSize*penSize/((y1-y2)*(y1-y2)/(1.0*(x1-x2)*(x1-x2))+1) ));
        
                x11 = x1+x_offset; y11 = y1+y_offset;
                x22 = x1-x_offset; y22 = y1-y_offset;
                x33 = x2-x_offset; y33 = y2-y_offset;
                x44 = x2+x_offset; y44 = y2+y_offset;
                break;
            case 65535://垂直直线
                x11 = (int)(x1-(penSize>>1)); y11 = y1;
                x22 = (int)(x1+(penSize>>1)); y22 = y1;
                x33 = (int)(x2-(penSize>>1)); y33 = y2;
                x44 = (int)(x2+(penSize>>1)); y44 = y2;
                break;
        }
        (*Call_ApplyPixel_xxxx)(x11,y11,penColor,pBufferInfo );
        (*Call_ApplyPixel_xxxx)(x22,y22,penColor,pBufferInfo );
        (*Call_ApplyPixel_xxxx)(x33,y33,penColor,pBufferInfo );
        (*Call_ApplyPixel_xxxx)(x44,y44,penColor,pBufferInfo );

        __Graph_quad_fill(  x11,y11, \
                                      x22,y22, \
                                      x33,y33, \
                                      x44,y44, \
                                      penColor  , \
                                      pBufferInfo,Call_ApplyPixel_xxxx  );
        // GUI_RefreashArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
    }
}

/*====================================
 > 插入一个填充四边形
=====================================*/
static void __Graph_quad_fill(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){

    int tmp_y[] = {y1,y2,y3,y4};
    int tmp_x[] = {x1,x2,x3,x4};
    struct IntArray_t tmp;
 // 分析四边形正交化后的长与宽
    tmp = __findMin_INT(tmp_y,4);
    int top_y = tmp.value;
    // int top_x = *((&x1)+((tmp.index)<<1));

    tmp = __findMax_INT(tmp_y,4);
    int bottom_y = tmp.value;
    // int bottom_x = *((&x1)+((tmp.index)<<1));

    tmp = __findMin_INT(tmp_x,4);
    // int left_y = *((&y1)+((tmp.index)<<1));
    int left_x = tmp.value;

    tmp = __findMax_INT(tmp_x,4);
    // int right_y = *((&y1)+((tmp.index)<<1));
    int right_x = tmp.value;

    int area_width  = right_x  - left_x + 1;
    int area_height = bottom_y - top_y  + 1;
 // 分析四边形的边框,任意两点组合去除对角线
    int x11 = x1;
    int y11 = y1;
    int x22,y22,x33,y33,x44,y44;
    
    int tmp_P1P2 = __Point_toLine(x1,y1,x2,y2, x3,y3) + __Point_toLine(x1,y1,x2,y2, x4,y4);
    int tmp_P1P3 = __Point_toLine(x1,y1,x3,y3, x2,y2) + __Point_toLine(x1,y1,x3,y3, x4,y4);

    if(tmp_P1P2 == 0){
        x22 = x3; y22 = y3;
        x33 = x2; y33 = y2;
        x44 = x4; y44 = y4;
    }else if(tmp_P1P3 == 0){
        x22 = x2; y22 = y2;
        x33 = x3; y33 = y3;
        x44 = x4; y44 = y4;
    }else{
        x22 = x2; y22 = y2;
        x33 = x4; y33 = y4;
        x44 = x3; y44 = y3;
    }

 // 创建临时空画布，大小取决于上述分析结果
    bool* pBuffer = (bool*)calloc((area_height*area_width),1);

 // 绘制四边形边框，通过画线程序实现
    BufferInfo_t BufferInfo = {.pBuffer = pBuffer    ,\
                               .height  = area_height,\
                               .width   = area_width };

    __Graph_line_raw( x11-left_x , y11-top_y , x22-left_x , y22-top_y , penColor ,&BufferInfo,__ApplyPixel_mark);
    
    __Graph_line_raw( x22-left_x , y22-top_y , x33-left_x , y33-top_y , penColor ,&BufferInfo,__ApplyPixel_mark);

    __Graph_line_raw( x33-left_x , y33-top_y , x44-left_x , y44-top_y , penColor ,&BufferInfo,__ApplyPixel_mark);
    
    __Graph_line_raw( x44-left_x , y44-top_y , x11-left_x , y11-top_y , penColor ,&BufferInfo,__ApplyPixel_mark);

#if 0
    BufferInfo.pBuffer = Screen.buffer;
    BufferInfo.height  = GUI_Y_WIDTH;
    BufferInfo.width   = GUI_X_WIDTH;

    __Graph_line_raw( x11-left_x , y11-top_y , x22-left_x , y22-top_y ,penColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw( x22-left_x , y22-top_y , x33-left_x , y33-top_y ,penColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw( x33-left_x , y33-top_y , x44-left_x , y44-top_y ,penColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw( x44-left_x , y44-top_y , x11-left_x , y11-top_y ,penColor,&BufferInfo,__ApplyPixel_fill);
    GUI_RefreashArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
#endif

 // 从顶点开始，向下左右画点并搜寻,直到找到边线为止,随后填充
    for(int j = 0;j < area_height;j++){
        int LF = 0,RH = area_width - 1;
        for(;LF < RH;LF++){
            if( *(pBuffer + (j*area_width) + LF) == 1 )
                break;
        }

        for(;RH > LF;RH--){
            if( *(pBuffer + (j*area_width) + RH) == 1 )
                break;
        }
        memset((pBuffer + (j*area_width) + LF) ,1 ,RH-LF );
    }

 // 将画布上的点，存入图像显存，注意偏移量
    // BufferInfo.pBuffer = Screen.buffer;
    // BufferInfo.height  = GUI_Y_WIDTH;
    // BufferInfo.width   = GUI_X_WIDTH;

    for(int j = 0;j < area_height;j++){
        for(int i = 0;i < area_width;i++){
            if( (*(pBuffer + area_width*j + i)) == 1 )
                __ApplyPixel_fill( i+left_x , j+top_y , penColor, pBufferInfo );
        }
    }

 // 释放临时画布
    free(pBuffer);
}

/*====================================
 > 插入一根香肠线,粗细随设定
=====================================*/
static void __Graph_line_sausage(int x1 ,int y1 ,int x2 ,int y2 ,size_t penSize ,Pixel_t penColor ,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){

    __Graph_line_raw(x1,y1,x2,y2,penColor,pBufferInfo,Call_ApplyPixel_xxxx);
    if(penSize > 1){
        int d = (int)(penSize);
        int r = d>>1;
        int p = 3-(r<<1);
        int x_tmp = 0,y_tmp = r;
        bool eps  = (d%2==0);

        int    dis_min = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(2*x_tmp-eps) );
        int    dis_tmp = dis_min;
        
        int    py1=0,px1=0,py2=0,px2=0;
        
        for(;x_tmp<=y_tmp;x_tmp++){
            int cnt = y_tmp+1;

            while(cnt--){
                (*Call_ApplyPixel_xxxx)(x1     + x_tmp ,y1     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x1+eps - x_tmp ,y1     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x1     + x_tmp ,y1+eps - cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x1+eps - x_tmp ,y1+eps - cnt,penColor,pBufferInfo );

                (*Call_ApplyPixel_xxxx)(x2     + x_tmp ,y2     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x2+eps - x_tmp ,y2     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x2     + x_tmp ,y2+eps - cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x2+eps - x_tmp ,y2+eps - cnt,penColor,pBufferInfo );
            }

            cnt = x_tmp+1;
            while(cnt--){
                (*Call_ApplyPixel_xxxx)(x1     + y_tmp ,y1     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x1+eps - y_tmp ,y1     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x1     + y_tmp ,y1+eps - cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x1+eps - y_tmp ,y1+eps - cnt,penColor,pBufferInfo );

                (*Call_ApplyPixel_xxxx)(x2     + y_tmp ,y2     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x2+eps - y_tmp ,y2     + cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x2     + y_tmp ,y2+eps - cnt,penColor,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x2+eps - y_tmp ,y2+eps - cnt,penColor,pBufferInfo );
            }
//            Screen.buffer[M_SCREEN_MAIN][y1     + y_tmp][x1     + x_tmp].data = GUI_COLOR_RED;
//            Screen.buffer[M_SCREEN_MAIN][y1+eps - y_tmp][x1+eps - x_tmp].data = GUI_COLOR_RED;
            dis_tmp = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(eps-2*x_tmp) );;
            if( dis_tmp < dis_min ){
                dis_min = dis_tmp;
                py1 =  y_tmp ; px1 =  x_tmp;
                py2 = eps-y_tmp ; px2 = eps-x_tmp;
            }
            
//            Screen.buffer[M_SCREEN_MAIN][y1     + y_tmp][x1+eps - x_tmp].data = GUI_COLOR_GREEN;
//            Screen.buffer[M_SCREEN_MAIN][y1+eps - y_tmp][x1     + x_tmp].data = GUI_COLOR_GREEN;
            dis_tmp = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(2*x_tmp-eps) );
            if( dis_tmp < dis_min ){
                dis_min = dis_tmp;
                py1 =  y_tmp ; px1 = eps-x_tmp;
                py2 = eps-y_tmp ; px2 =  x_tmp;
            }

//            Screen.buffer[M_SCREEN_MAIN][y1     + x_tmp][x1     + y_tmp].data = GUI_COLOR_BLUE;
//            Screen.buffer[M_SCREEN_MAIN][y1+eps - x_tmp][x1+eps - y_tmp].data = GUI_COLOR_BLUE;
            dis_tmp = __abs( (y2-y1)*(eps-2*x_tmp) + (x2-x1)*(eps-2*y_tmp) );
            if( dis_tmp < dis_min ){
                dis_min = dis_tmp;
                py1 =  x_tmp ; px1 =  y_tmp;
                py2 = eps-x_tmp ; px2 = -y_tmp;
            }
            
//            Screen.buffer[M_SCREEN_MAIN][y1     + x_tmp][x1+eps - y_tmp].data = GUI_COLOR_TAN;
//            Screen.buffer[M_SCREEN_MAIN][y1+eps - x_tmp][x1     + y_tmp].data = GUI_COLOR_TAN;
            dis_tmp = __abs( (y2-y1)*(eps-2*x_tmp) + (x2-x1)*(2*y_tmp-eps) );
            if( dis_tmp < dis_min ){
                dis_min = dis_tmp;
                py1 =  x_tmp ; px1 = eps-y_tmp;
                py2 = eps-x_tmp ; px2 =  y_tmp;
            }
            
            if(p <= 0){
                p += (x_tmp<<2) + 6;
            }else{
                p += ((x_tmp-y_tmp)<<2) + 10;
                y_tmp--;
            }
        }
        
        Screen.buffer[M_SCREEN_MAIN][y1     + py1][x1     + px1].data = GUI_COLOR_BLACK;
        Screen.buffer[M_SCREEN_MAIN][y1     + py2][x1     + px2].data = GUI_COLOR_BLACK;

        __Graph_quad_fill(x1+px1, y1+py1, x1+px2, y1+py2, x2+px1, y2+py1, x2+px2, y2+py2, penColor, pBufferInfo, Call_ApplyPixel_xxxx);
    
    }
    
}

static void __Graph_triangle_raw(int x1,int y1,int x2,int y2,int x3,int y3,Pixel_t penColor ,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){

}

static void __Graph_triangle_fill(int x1,int y1,int x2,int y2,int x3,int y3,Pixel_t penColor ,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){
    int xs = GUI_MIN( ( GUI_MIN(x1,x2) ) ,x3);
    int xe = GUI_MAX( ( GUI_MAX(x1,x2) ) ,x3);
    int ys = GUI_MIN( ( GUI_MIN(y1,y2) ) ,y3);
    int ye = GUI_MAX( ( GUI_MAX(y1,y2) ) ,y3);
    for(int y=ys;y<=ye;y++){
        for(int x=xs;x<=xe;x++){
            if( -1 != __Point_toTriangle(x1,y1,x2,y2,x3,y3 ,x,y) ){
                (*Call_ApplyPixel_xxxx)(x,y,penColor,pBufferInfo);
            }
        }
    }
}

/*====================================
 > 插入一个空心长方形,线宽为1
=====================================*/
static void __Graph_rect_raw(int xs,int ys,int xe,int ye,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    for(int x=xs;x<=xe;x++){
        (*Call_ApplyPixel_xxxx)(x,ys,penColor,pBufferInfo);
        (*Call_ApplyPixel_xxxx)(x,ye,penColor,pBufferInfo);
    }
    for(int y=ys+1;y<ye;y++){
        (*Call_ApplyPixel_xxxx)(xs,y,penColor,pBufferInfo);
        (*Call_ApplyPixel_xxxx)(xe,y,penColor,pBufferInfo);
    }
}

/*====================================
 > 插入一个填充长方形
=====================================*/
static void __Graph_rect_fill(int xs,int ys,int xe,int ye,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){

    if(pBufferInfo->pBuffer == Screen.buffer && Call_ApplyPixel_xxxx == __ApplyPixel_fill){
        for(unsigned int y = ys;y <= ye;y++){
            if(y == ys){
                for(unsigned int x = xs;x <= xe;x++)
                    Screen.buffer[M_SCREEN_MAIN][y][x].data = penColor;
            }else{
                memcpy(&(Screen.buffer[M_SCREEN_MAIN][y ][xs].data),\
                       &(Screen.buffer[M_SCREEN_MAIN][ys][xs].data),\
                       ((xe-xs+1)*sizeof(Pixel_t)) );
            }
        }
    }else{
        for(unsigned int y = ys;y <= ye;y++){
            for(unsigned int x = xs;x <= xe;x++){
                (*Call_ApplyPixel_xxxx)(x,y,penColor,pBufferInfo);
            }
        }
    }
}

/*====================================
 > 插入一个圆角长方形
=====================================*/
static void __insertRoundCornerRectangular(int xs,int ys,int xe,int ye,int r,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod Call_ApplyPixel_xxxx){
    
    r = GUI_LIMIT((signed)r, 0, (GUI_MIN((xe-xs), (ye-ys)))/2 );
    
    __Graph_rect_fill(xs+r+1, ys    , xe-r-1, ye    , penColor, pBufferInfo, Call_ApplyPixel_xxxx);
    __Graph_rect_fill(xs    , ys+r+1, xs+r  , ye-r-1, penColor, pBufferInfo, Call_ApplyPixel_xxxx);
    __Graph_rect_fill(xe-r  , ys+r+1, xe    , ye-r-1, penColor, pBufferInfo, Call_ApplyPixel_xxxx);
    
    __insertFilledQuartCircle_1(xe-r, ys+r, r, penColor, pBufferInfo, Call_ApplyPixel_xxxx);
    __insertFilledQuartCircle_2(xs+r, ys+r, r, penColor, pBufferInfo, Call_ApplyPixel_xxxx);
    __insertFilledQuartCircle_3(xs+r, ye-r, r, penColor, pBufferInfo, Call_ApplyPixel_xxxx);
    __insertFilledQuartCircle_4(xe-r, ye-r, r, penColor, pBufferInfo, Call_ApplyPixel_xxxx);
}

/*====================================
 > 插入一个空心长方形,线宽随设定
=====================================*/
static void __Graph_rect_edged(int xs,int ys,int xe,int ye ,size_t penSize,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){

    int loop = 0;
    while(loop < penSize){
        uint x = xs+loop, y = ys+loop;

        while(x<=(xe-loop) && y<=(ye-loop)){
            if( x < (xe-loop) ){
                (*Call_ApplyPixel_xxxx)(x,ys + loop, penColor ,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(x,ye - loop, penColor ,pBufferInfo );
                x++;
            }
            else{
                (*Call_ApplyPixel_xxxx)(xs + loop,y, penColor ,pBufferInfo );
                (*Call_ApplyPixel_xxxx)(xe - loop,y, penColor ,pBufferInfo );
                y++;
            }
        }
        loop++;
    }
}

/*====================================
 > 插入一个空心四边形
=====================================*/
static void __Graph_quad_raw(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,Pixel_t penColor,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_ApplyPixel_xxxx){

 // 分析四边形的边框,任意两点组合去除对角线
    int x11 = x1;
    int y11 = y1;
    int x22,y22,x33,y33,x44,y44;
    
    int tmp_P1P2 = __Point_toLine(x1,y1,x2,y2, x3,y3) + __Point_toLine(x1,y1,x2,y2, x4,y4);
    int tmp_P1P3 = __Point_toLine(x1,y1,x3,y3, x2,y2) + __Point_toLine(x1,y1,x3,y3, x4,y4);

    if(tmp_P1P2 == 0){
        x22 = x3; y22 = y3;
        x33 = x2; y33 = y2;
        x44 = x4; y44 = y4;
    }else if(tmp_P1P3 == 0){
        x22 = x2; y22 = y2;
        x33 = x3; y33 = y3;
        x44 = x4; y44 = y4;
    }else{
        x22 = x2; y22 = y2;
        x33 = x4; y33 = y4;
        x44 = x3; y44 = y3;
    }

 // 绘制四边形边框，通过画线程序实现

    __Graph_line_raw( x11 , y11 , x22 , y22 , penColor ,pBufferInfo,__ApplyPixel_mark);
    
    __Graph_line_raw( x22 , y22 , x33 , y33 , penColor ,pBufferInfo,__ApplyPixel_mark);

    __Graph_line_raw( x33 , y33 , x44 , y44 , penColor ,pBufferInfo,__ApplyPixel_mark);
    
    __Graph_line_raw( x44 , y44 , x11 , y11 , penColor ,pBufferInfo,__ApplyPixel_mark);

}

//============================================= End of Internal Config ===============================================//
//============================================= End of Internal Config ===============================================//
//============================================= End of Internal Config ===============================================//

//================================================== Display Config ==================================================//
//================================================== Display Config ==================================================//
//================================================== Display Config ==================================================//

void GUI_RefreashArea(int x1,int y1,int x2,int y2){
    int xe   = GUI_MAX(x1,x2);
    int xs   = GUI_MIN(x1,x2);
    int ye   = GUI_MAX(y1,y2);
    int ys   = GUI_MIN(y1,y2);
    int x_width = xe-xs+1;
    int y_width = ye-ys+1;

    if(GUI_API_DrawArea != NULL){
        Pixel_t* p = (Pixel_t*)__malloc((x_width)*(y_width)*sizeof(Pixel_t));
        (*GUI_API_DrawArea)(xs,ys,xe,ye, __Clone_gram_part(p, xs, ys, xe, ye) );
        __free(p);
    }
    else{
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*GUI_API_DrawPixel)(x,y,Screen.buffer[M_SCREEN_MAIN][y][x].data);
    }
}

void GUI_Init(void){
    Screen.allocated_byte = 0;

    Screen.txtPos.x   = 0;
    Screen.txtPos.y   = 0;
    Screen.pFont      = __FONT_STD6X8;
    Screen.penColor   = GUI_COLOR_WHITE;
    Screen.bkColor    = GUI_COLOR_BLACK;
    Screen.penSize    = 3;
    Screen.BlurMethod = GUI_BLUR_Average;

    __Clear_gram_all();
    Screen.autoDisplayMode = true;
    Screen.areaNeedRefreashHeadNode = NULL;
    Screen.areaNeedRefreashNodeCnt  = 0;
    Screen.areaNeedRefreashPixelCnt = 0;

#if GUI_ANIMATION_DISPLAY
    Screen.cfgAnimationHeadNode     = NULL;
    Screen.cfgAnimationNodeCnt      = 0;
#endif
#if GUI_ICON_DISPLAY
    Screen.cfgIconHeadNode          = NULL;
    Screen.cfgIconNodeCnt           = 0;
#endif
#if GUI_TRACE_WATCH_DISPLAY
    Screen.cfgTraceHeadNode          = NULL;
    Screen.cfgTraceNodeCnt           = 0;
#endif
    if(GUI_API_DelayMs == NULL){
        //...//
    }

    GUI_RefreashArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
}

void GUI_Debug(void){
	BufferInfo_t BufferInfo = {
        .pBuffer = Screen.buffer[M_SCREEN_MAIN],
        .width   = GUI_X_WIDTH,
        .height  = GUI_Y_WIDTH
	};
    int xs = 213;
    int ys = 284;
    int xe = 215;
    int ye = 400;
    
    __Graph_rect_raw(xs, ys, xe, ye, 200, &BufferInfo, __ApplyPixel_lightness);
//    __insertRoundCornerRectangular(xs, ys, xe, ye, 20, Screen.penColor, &BufferInfo, __ApplyPixel_fill);
    
	if( Screen.autoDisplayMode == true ){
		GUI_RefreashArea(xs,ys,xe,ye);
	}else{
		__addAreaNeedRefreash(xs,ys,xe,ye);
	}
}

void GUI_RefreashScreen(void){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    for(unsigned int page=0;page<GUI_PAGEs;page++)  {
        (*GUI_API_DrawPageColumn)(page,0,GUI_X_WIDTH,(Pixel_t*)&Screen.buffer[ page ]);
    }
#else

    __AreaRefreashChain* pNow  = Screen.areaNeedRefreashHeadNode;
    __AreaRefreashChain* pNext;
    bool refreashAll = (Screen.areaNeedRefreashPixelCnt >= (GUI_X_WIDTH*GUI_Y_WIDTH));

    if(refreashAll == true)
        GUI_RefreashArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);

    while(pNow != NULL){
        pNext = pNow->nextAreaRefreash;
        if( refreashAll == false ){
            if(GUI_API_DrawArea != NULL){
                GUI_RefreashArea(pNow->xs,pNow->ys,pNow->xe,pNow->ye);
            }else{
                for(int x = pNow->xs;x <= pNow->xe;x++)
                    for(int y = pNow->ys;y <= pNow->ye;y++)
                        (*GUI_API_DrawPixel)(x,y,Screen.buffer[M_SCREEN_MAIN][y][x].data);
            }
        }
        __free(pNow);
        pNow = pNext;
    }
#endif
    Screen.areaNeedRefreashPixelCnt = 0;
    Screen.areaNeedRefreashHeadNode = NULL;
}

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
void GUI_RefreashPageArea(unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end){
    Pixel_t* p;
    unsigned int column_num = column_end-column_start+1;
    for(unsigned int page=page_start;page<=page_end;page++){
        p  = (Pixel_t*)&Screen.buffer[ page ];
        p += column_start;
        (*GUI_API_DrawPageColumn)(page,column_start,column_num,p);
    }
}
#endif

void GUI_FillAll(Pixel_t data){
    if(sizeof(Pixel_t) == 1)
 #if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
        memset(Screen.buffer[0], data ,(GUI_PAGEs   * GUI_X_WIDTH));
#else
        memset(Screen.buffer[0], data ,(GUI_X_WIDTH * GUI_Y_WIDTH));
#endif
    else
        for(size_t i=0;i<GUI_Y_WIDTH*GUI_X_WIDTH;i++){
            *(&(Screen.buffer[M_SCREEN_MAIN][0][0].data)+i) = data;
        }
    if(Screen.autoDisplayMode == true)
        GUI_RefreashArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
    else
        __addAreaNeedRefreash(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
}

void GUI_ClearScreen(void){
    GUI_FillAll(Screen.bkColor);
}

void GUI_ClearFrameBuffer(void){
        if(sizeof(Pixel_t) == 1)
 #if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
        memset(Screen.buffer[M_SCREEN_MAIN][0], Screen.bkColor ,(GUI_PAGEs   * GUI_X_WIDTH));
#else
        memset(Screen.buffer[M_SCREEN_MAIN][0], Screen.bkColor ,(GUI_X_WIDTH * GUI_Y_WIDTH));
#endif
    else
        for(size_t i=0;i<GUI_Y_WIDTH*GUI_X_WIDTH;i++){
            *(&(Screen.buffer[M_SCREEN_MAIN][0][0].data)+i) = Screen.bkColor;
        }
}

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
void GUI_ClearPageArea(unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end,...){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(page_start <= page_end,"<page_start> should be smaller than <page_end>.");
    (*GUI_API_AssertParam)(page_start < GUI_PAGEs && page_end < GUI_PAGEs,"Page index is out of range.");
#endif
    va_list ap;
    va_start(ap,column_end);
    va_arg(ap,int);
    const int onlyChangeBuffer = va_arg(ap,int);
    va_end(ap);

    __Clear_gram_page(page_start,page_end,column_start,column_end);
    if(onlyChangeBuffer!=true){
        GUI_RefreashScreen();
    }
}
#endif

void GUI_SetPenColor(Pixel_t color){
    Screen.penColor = color;
}

Pixel_t GUI_GetPenColor(void){
    return Screen.penColor;
}

void GUI_SetBackColor(Pixel_t color){
    Screen.bkColor = color;
}

Pixel_t GUI_GetBackColor(void){
    return Screen.bkColor;
}

void GUI_SetPenSize(unsigned int penSize){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(penSize < GUI_MIN(GUI_X_WIDTH,GUI_Y_WIDTH),"Pen size is too big.");
#endif
    Screen.penSize = penSize;
}

unsigned int GUI_GetPenSize(void){
    return Screen.penSize;
}

void GUI_SetFont(int GUI_FONT_xxx){
    switch(GUI_FONT_xxx){
        case GUI_FONT_Standard_Small   : Screen.pFont = __FONT_STD6X8;          break;
        case GUI_FONT_Standard_Middle  : Screen.pFont = __FONT_STD8X16;         break;
#if GUI_FONT_EXTENTION
        case GUI_FONT_Bradley_Large    : Screen.pFont = __FONT_BRADLEY_LARGE;   break;
        case GUI_FONT_CourierNew_Middle: Screen.pFont = __FONT_COURIERNEW10X12; break;
        case GUI_FONT_CourierNew_Large : Screen.pFont = __FONT_COURIERNEW13X16; break;
#endif
#if GUI_ASSERT
        default: (*GUI_API_AssertParam)(false,"Wrong Text Font Type.");         break;
#else
        default: Screen.pFont = __FONT_STD6X8  ;break;
#endif
    }
}

void GUI_SetBlurMethod(E_BlurMethod_t GUI_BLUR_xxxx){
    
}

void GUI_SetTextPos(unsigned int x,unsigned int y){
    Screen.txtPos.x = x;
    Screen.txtPos.y = y;
}

void inline GUI_AutoDisplayMode(void){
    GUI_RefreashScreen();
    Screen.autoDisplayMode = true;
}

void inline GUI_ManualDisplayMode(void){
    Screen.autoDisplayMode = false;
}

//============================================= End of Display Config ==============================================//
//============================================= End of Display Config ==============================================//
//============================================= End of Display Config ==============================================//


//=============================================== Graphic Function =================================================//
//=============================================== Graphic Function =================================================//
//=============================================== Graphic Function =================================================//

void GUI_DrawPixel(int x,int y){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x < GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    __ApplyPixel_fill(x,y,Screen.penColor,&BufferInfo );

    if(Screen.autoDisplayMode == true){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        unsigned char page = y>>3;
        Pixel_t* p = (Pixel_t*)(&Screen.buffer[M_SCREEN_MAIN][page]);
        p+=x;
        (*GUI_API_DrawPageColumn)(page,x,1,p);
#else
        (*GUI_API_DrawPixel)(x,y,Screen.buffer[M_SCREEN_MAIN][y][x].data);
#endif
        
    }else{
        __addAreaNeedRefreash(x,y,x,y);
    }

}

void GUI_FillRect(int x1,int y1,int x2,int y2){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x1 < GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(x2 < GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y1 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y2 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)

    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    unsigned char page_start   = (GUI_MIN(y1,y2))>>3;
    unsigned char page_end     = (GUI_MAX(y1,y2))>>3;
    unsigned char column_start = (GUI_MIN(x1,x2));
    unsigned char column_end   = (GUI_MAX(x1,x2));
    for(size_t page=page_start;page<=page_end;page++){
        unsigned char y_max = GUI_MAX(y1,y2);
        unsigned char y_min = GUI_MIN(y1,y2);
        if(page==page_start){
            while( y_min < ((page+1)<<3) && y_min <= y_max)
                __ApplyPixel_fill(column_start,y_min++ ,&BufferInfo );
            
            memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
            continue;
        }
        if(page==page_end){
            while( y_max >= (page<<3) && y_max >= y_min)
                __ApplyPixel_fill(column_start,y_max-- ,&BufferInfo );

            memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
            continue;
        }
        memset(Screen.buffer[page]+column_start,Screen.penColor,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
    }

#else

    int xe = GUI_MAX(x1,x2);
    int xs = GUI_MIN(x1,x2);
    int ye = GUI_MAX(y1,y2);
    int ys = GUI_MIN(y1,y2);

    for(unsigned int y = ys;y <= ye;y++){
        if(y == ys){
            for(unsigned int x = xs;x <= xe;x++)
                Screen.buffer[M_SCREEN_MAIN][y][x].data = Screen.penColor;
        }else{
            memcpy(&(Screen.buffer[M_SCREEN_MAIN][y ][xs].data),\
                   &(Screen.buffer[M_SCREEN_MAIN][ys][xs].data),\
                   ((xe-xs+1)*sizeof(Pixel_t)) );
        }
    }

#endif

    if(Screen.autoDisplayMode == true){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        Pixel_t* p;
        for(unsigned int page=page_start;page<=page_end;page++){
            p = (Pixel_t*)(&Screen.buffer[page]);
            p += column_start;
            (*GUI_API_DrawPageColumn)(page,column_start,column_end-column_start,p );
        }
#else
        GUI_RefreashArea(xs,ys,xe,ye);
#endif
    }else{
        __addAreaNeedRefreash(xs,ys,xe,ye);
    }
}

void GUI_DrawRect(int x1,int y1,int x2,int y2){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x1 < GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(x2 < GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y1 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y2 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif

    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)

    BYTE penSize      = Screen.penSize;
    unsigned char page_start   = (GUI_MIN(y1,y2))>>3;
    unsigned char page_end     = (GUI_MAX(y1,y2))>>3;
    unsigned char column_start = (GUI_MIN(x1,x2));
    unsigned char column_end   = (GUI_MAX(x1,x2));

    for(size_t page=page_start;page<=page_end;page++){
        unsigned char y_max = GUI_MAX(y1,y2);
        unsigned char y_min = GUI_MIN(y1,y2);
        if(page==page_start){
            while( y_min < ((page+1)<<3) && y_min <= y_max)
                __ApplyPixel_fill(column_start,y_min++,Screen.penColor,&BufferInfo );
            
            memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
            continue;
        }
        if(page==page_end){
            while( y_max >= (page<<3) && y_max >= y_min)
                __ApplyPixel_fill(column_start,y_max--,Screen.penColor,&BufferInfo );

            memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
            continue;
        }
        memset(Screen.buffer[page]+column_start,Screen.penColor,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
    }

    unsigned char x3 = GUI_MIN(x1,x2)+penSize;
    unsigned char x4 = GUI_MAX(x1,x2)-penSize;

    unsigned char y3 = GUI_MIN(y1,y2)+penSize;
    unsigned char y4 = GUI_MAX(y1,y2)-penSize;

    if(y3 < y4 && x3 < x4){
        page_start   = (GUI_MIN(y3,y4))/8;
        page_end     = (GUI_MAX(y3,y4))/8;
        column_start = (GUI_MIN(x3,x4));
        column_end   = (GUI_MAX(x3,x4));

        for(size_t page=page_start;page<=page_end;page++){
            unsigned char y_max = GUI_MAX(y3,y4);
            unsigned char y_min = GUI_MIN(y3,y4);
            if(page==page_start){
                while( y_min < ((page+1)<<3) && y_min <= y_max)
                    __erasePixel(column_start,y_min++,&BufferInfo);
                
                memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
                continue;
            }
            if(page==page_end){
                while( y_max >= (page<<3) && y_max >= y_min)
                    __erasePixel(column_start,y_max--,&BufferInfo);

                memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
                continue;
            }
            memset(Screen.buffer[page]+column_start,Screen.bkColor,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
        }
    }
    page_start   = (GUI_MIN(y1,y2))/8;
    page_end     = (GUI_MAX(y1,y2))/8;
    column_start = (GUI_MIN(x1,x2));
    column_end   = (GUI_MAX(x1,x2));
#else
    int ye = GUI_MAX(y1,y2);
    int ys = GUI_MIN(y1,y2);
    int xe = GUI_MAX(x1,x2);
    int xs = GUI_MIN(x1,x2);
    if(Screen.penSize == 1)
        __Graph_rect_raw(xs,ys,xe,ye,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    else
        __Graph_rect_edged(xs,ys,xe,ye,Screen.penSize,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
#endif

    if(Screen.autoDisplayMode == true){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        Pixel_t* p;
        for(unsigned int page=page_start;page<=page_end;page++){
            p = (Pixel_t*)(&Screen.buffer[page]);
            p += column_start;
            (*GUI_API_DrawPageColumn)(page,column_start,column_end-column_start,p );
        }
#else
        GUI_RefreashArea(xs,ys,xe,ye);
#endif
    }else{
        __addAreaNeedRefreash(xs,ys,xe,ye);
    }
    
}

void GUI_BlurRect(int x1,int y1,int x2,int y2,uint16_t radSize, uint16_t br_100){
    int xe   = GUI_MAX(x1,x2);
    int xs   = GUI_MIN(x1,x2);
    int ye   = GUI_MAX(y1,y2);
    int ys   = GUI_MIN(y1,y2);
    
    xs       = GUI_LIMIT((signed)xs, 0, GUI_X_WIDTH-1);
    xe       = GUI_LIMIT((signed)xe, 0, GUI_X_WIDTH-1);
    ys       = GUI_LIMIT((signed)ys, 0, GUI_Y_WIDTH-1);
    ye       = GUI_LIMIT((signed)ye, 0, GUI_Y_WIDTH-1);
    
    BufferInfo_t BufferInfo = {
        .pBuffer = Screen.buffer,
        .width   = GUI_X_WIDTH  ,
        .height  = GUI_Y_WIDTH
    };
    
    switch(Screen.BlurMethod){
        case GUI_BLUR_Average:
            __Blur_avg_part(xs, ys, xe, ye, radSize, br_100, &BufferInfo);
            break;
        case GUI_BLUR_Gussian:
            __Blur_gus_part(xs, ys, xe, ye, radSize, br_100, &BufferInfo);
            break;
        default:break;
    }
    
    
    for(int y=ys;y<=ye;y++){
        memcpy(&Screen.buffer[M_SCREEN_MAIN][y][xs], &Screen.buffer[M_SCREEN_BLUR][y][xs], (xe-xs+1)*sizeof(PixelUnit_t));
    }
    
    if( Screen.autoDisplayMode == true ){
        GUI_RefreashArea(xs,ys,xe,ye);
    }else{
        __addAreaNeedRefreash(xs, ys, xe, ye);
    }
}

void GUI_BlurRoundCornerRect(int x1,int y1,int x2,int y2,int r,uint16_t radSize, uint16_t br_100){

    int xe   = GUI_MAX(x1,x2);
    int xs   = GUI_MIN(x1,x2);
    int ye   = GUI_MAX(y1,y2);
    int ys   = GUI_MIN(y1,y2);
    
    xs       = GUI_LIMIT((signed)xs, 0, GUI_X_WIDTH-1);
    xe       = GUI_LIMIT((signed)xe, 0, GUI_X_WIDTH-1);
    ys       = GUI_LIMIT((signed)ys, 0, GUI_Y_WIDTH-1);
    ye       = GUI_LIMIT((signed)ye, 0, GUI_Y_WIDTH-1);
    
    BufferInfo_t BufferInfo = {
        .pBuffer = Screen.buffer,
        .width   = GUI_X_WIDTH  ,
        .height  = GUI_Y_WIDTH
    };
    switch(Screen.BlurMethod){
        case GUI_BLUR_Average:
            __Blur_avg_part(xs, ys, xe, ye, radSize, br_100, &BufferInfo);
            break;
        case GUI_BLUR_Gussian:
            __Blur_gus_part(xs, ys, xe, ye, radSize, br_100, &BufferInfo);
            break;
        default:break;
    }
    
    __insertRoundCornerRectangular(xs, ys, xe, ye, r, 0, &BufferInfo, __ApplyPixel_moveBlur);

    
    if( Screen.autoDisplayMode == true ){
        GUI_RefreashArea(xs,ys,xe,ye);
    }else{
        __addAreaNeedRefreash(xs, ys, xe, ye);
    }
}

void GUI_FillCircle(int x,int y, int r){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x<GUI_X_WIDTH ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y<GUI_Y_WIDTH ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(r >= 0        ,"Radius should be bigger than zero.");
#endif
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    int page_start   = (GUI_LIMIT((signed)(y-r),0,GUI_Y_WIDTH))>>3;
    int page_end     = (GUI_LIMIT((signed)(y+r),0,GUI_Y_WIDTH))>>3;
    int column_start = (GUI_LIMIT((signed)(x-r),0,GUI_X_WIDTH));
    int column_end   = (GUI_LIMIT((signed)(x+r),0,GUI_X_WIDTH));

    int r_2 = r*r;
    for(int i = -r;i <= r;i++){
        for(int j = -r;j <= r;j++){
            if(  (x-i)<GUI_X_WIDTH && (y-j)<GUI_Y_WIDTH && i*i+j*j <= r_2 )
                __ApplyPixel_fill(x-i,y-j,Screen.penColor,&BufferInfo );
        }
    }
#else
    int xs = GUI_LIMIT(((signed)(x-r)),0,GUI_X_WIDTH);
    int xe = GUI_LIMIT(((signed)(x+r)),0,GUI_X_WIDTH);
    int ys = GUI_LIMIT(((signed)(y-r)),0,GUI_Y_WIDTH);
    int ye = GUI_LIMIT(((signed)(y+r)),0,GUI_Y_WIDTH);

    __Graph_circle_fill(x,y,r,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
#endif

    if(Screen.autoDisplayMode == true){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        Pixel_t* p;
        for(unsigned int page=page_start;page<=page_end;page++){
            p = (Pixel_t*)(&Screen.buffer[page]);
            p += column_start;
            (*GUI_API_DrawPageColumn)(page,column_start,column_end-column_start,p );
        }
#else
        GUI_RefreashArea(xs,ys,xe,ye);
#endif
    }else{
        __addAreaNeedRefreash(xs,ys,xe,ye);
    }
}

void GUI_DrawCircle(int x,int y, int d){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x<GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y<GUI_Y_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(r >= 0       ,"Radius should be bigger than zero.");
#endif
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    int r = d>>1;
    int xe = GUI_LIMIT((signed)(x+r+1),0,GUI_X_WIDTH-1);
    int xs = GUI_LIMIT((signed)(x-r-1),0,GUI_X_WIDTH-1);
    int ye = GUI_LIMIT((signed)(y+r+1),0,GUI_Y_WIDTH-1);
    int ys = GUI_LIMIT((signed)(y-r-1),0,GUI_Y_WIDTH-1);

    if(Screen.penSize == 1)
        __Graph_circle_raw(x,y,d,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    else
        __Graph_circle_edged(x,y,d,Screen.penSize,Screen.penColor,&BufferInfo,__ApplyPixel_fill);


    if(Screen.autoDisplayMode == true){
        GUI_RefreashArea(xs,ys,xe,ye);
    }else{
        __addAreaNeedRefreash(xs,ys,xe,ye);
    }
}

void GUI_BlueCircle(int x,int y, int r,uint16_t radSize, uint16_t br_100){
    
}

void GUI_FillEllipse(int x, int y,int rx, int ry,...){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x<GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y<GUI_Y_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(rx >= 0      ,"Radius X should be bigger than zero.");
    (*GUI_API_AssertParam)(ry >= 0      ,"Radius Y should be bigger than zero.");
#endif
    int xs = x-rx;
    int ys = y-ry;
    int xe = x+rx;
    int ye = y+ry;
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)

    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    unsigned int page_start   = (GUI_LIMIT((signed)(y-ry),0,GUI_Y_WIDTH))>>3;
    unsigned int page_end     = (GUI_LIMIT((signed)(y+ry),0,GUI_Y_WIDTH))>>3;
    unsigned int column_start = (GUI_LIMIT((signed)(x-rx),0,GUI_X_WIDTH));
    unsigned int column_end   = (GUI_LIMIT((signed)(x+rx),0,GUI_X_WIDTH));

    unsigned int rx_2   = rx*rx;
    unsigned int ry_2   = ry*ry;
    unsigned int rxry_2 = rx_2*ry_2;

    for(int i = -rx;i <= rx;i++){
        for(int j = -ry;j <= ry;j++){
            if(  (x-i)<GUI_X_WIDTH && y-j<GUI_Y_WIDTH && ry_2*i*i+rx_2*j*j < rxry_2 )
                __ApplyPixel_fill(x-i,y-j,Screen.penColor,&BufferInfo );
        }
    }
#else
    
#endif
    if( Screen.autoDisplayMode == true ){
        GUI_RefreashArea(xs, ys, xe, ye);
    }else{
        __addAreaNeedRefreash(xs, ys, xe, ye);
    }
}

void GUI_DrawEllipse(int x, int y,int rx, int ry,...){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x<GUI_X_WIDTH      ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y<GUI_Y_WIDTH      ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(rx >= 0            ,"Radius X should be bigger than zero.");
    (*GUI_API_AssertParam)(ry >= 0            ,"Radius Y should be bigger than zero.");
    (*GUI_API_AssertParam)(Screen.penSize < rx,"Graphic size should be bigger than Pen size or maybe pen size is too big");
    (*GUI_API_AssertParam)(Screen.penSize < ry,"Graphic size should be bigger than Pen size or maybe pen size is too big");
#endif
    // This part has not been well developed.
    while(1);
}

void GUI_DrawLine(int x1,int y1,int x2,int y2){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(0 <= x1         ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(0 <= x2         ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(0 <= y1         ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(0 <= y2         ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(x1 < GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(x2 < GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y1 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y2 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif

    uint penSize = Screen.penSize;
    
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    __Graph_line_sausage(x1,y1,x2,y2,Screen.penSize,Screen.penColor,&BufferInfo,__ApplyPixel_fill);


    size_t tmp = Screen.penSize>>1;

    if(Screen.autoDisplayMode == true){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
        GUI_RefreashArea(    (int)GUI_LIMIT( (signed)(GUI_MIN(x1,x2)-tmp) , 0 , GUI_X_WIDTH ), \
                             (int)GUI_LIMIT( (signed)(GUI_MIN(y1,y2)-tmp) , 0 , GUI_Y_WIDTH ), \
                             (int)GUI_LIMIT( (signed)(GUI_MAX(x1,x2)+tmp) , 0 , GUI_X_WIDTH ), \
                             (int)GUI_LIMIT( (signed)(GUI_MAX(y1,y2)+tmp) , 0 , GUI_Y_WIDTH )    );
#endif
    }else{
        __addAreaNeedRefreash(    (int)GUI_LIMIT( (signed)(GUI_MIN(x1,x2)-tmp) , 0 ,GUI_X_WIDTH ), \
                                  (int)GUI_LIMIT( (signed)(GUI_MIN(y1,y2)-tmp) , 0 ,GUI_Y_WIDTH ), \
                                  (int)GUI_LIMIT( (signed)(GUI_MAX(x1,x2)+tmp) , 0 ,GUI_X_WIDTH ), \
                                  (int)GUI_LIMIT( (signed)(GUI_MAX(y1,y2)+tmp) , 0 ,GUI_Y_WIDTH )    );
    }

    Screen.penSize = penSize;

}

void GUI_DrawWave(int A,float w,float phi,int x_start,int x_end,int y_level,...){
    A = abs(A);

    va_list ap;
    va_start(ap,y_level);
    const int clearScreen      = va_arg(ap,int);
    const int onlyChangeBuffer = va_arg(ap,int);
    va_end(ap);

    if(clearScreen==true)
        __Clear_gram_all();

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    unsigned int page_start   = GUI_LIMIT( (signed)((y_level-A)>>3) ,0 ,GUI_PAGEs);
    unsigned int page_end     = GUI_LIMIT( (signed)((y_level+A)>>3) ,0 ,GUI_PAGEs);
    unsigned int column_start = GUI_LIMIT( (signed)((x_start  )   ) ,0 ,GUI_X_WIDTH-1);
    unsigned int column_end   = GUI_LIMIT( (signed)((x_end    )   ) ,0 ,GUI_X_WIDTH-1);

    unsigned int x = x_start,x_old = x_start ,y_old = y_level,y = y_level;
    for(;x<=x_end;x++){
        y = (unsigned int)(y_level + A*sin(w*x+phi));
        GUI_DrawLine(x_old,y_old,x,y,false,true);
        x_old = x;
        y_old = y;
    }
#else
    //...//
#endif

    if(onlyChangeBuffer!=true){
        if(clearScreen == true){
            GUI_RefreashScreen();
        }else{
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
            GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
            //...//
#endif
        }
    }

}

void GUI_FillTriangle(int x1,int y1,int x2,int y2,int x3,int y3){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    int page_start   = GUI_LIMIT( (signed)((y_start)>>3) ,0 ,GUI_PAGEs);
    int page_end     = GUI_LIMIT( (signed)((y_end  )>>3) ,0 ,GUI_PAGEs);
    int column_start = GUI_LIMIT( (signed)( GUI_MIN( ( GUI_MIN(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
    int column_end   = GUI_LIMIT( (signed)( GUI_MAX( ( GUI_MAX(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
#else
    int xs           = GUI_LIMIT( (signed)( GUI_MIN( ( GUI_MIN(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
    int xe           = GUI_LIMIT( (signed)( GUI_MAX( ( GUI_MAX(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
    int ys           = GUI_LIMIT( (signed)( GUI_MIN( ( GUI_MIN(y1,y2) ) ,y3)  )    ,0 ,GUI_X_WIDTH-1);
    int ye           = GUI_LIMIT( (signed)( GUI_MAX( ( GUI_MAX(y1,y2) ) ,y3)  )    ,0 ,GUI_X_WIDTH-1);
#endif
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    __Graph_line_raw(x1,y1,x2,y2,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw(x2,y2,x3,y3,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw(x3,y3,x1,y1,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    
    GUI_RefreashArea(xs,ys,xe,ye);
    
    __Graph_triangle_fill(x1,y1,x2,y2,x3,y3,Screen.penColor,&BufferInfo,__ApplyPixel_fill);

    if( Screen.autoDisplayMode == true ){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
        GUI_RefreashArea(xs,ys,xe,ye);
#endif
    }else{
        __addAreaNeedRefreash(xs,ys,xe,ye);
    }
}

void GUI_DrawTriangle(int x1,int y1,int x2,int y2,int x3,int y3){
    
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    unsigned int page_start   = GUI_LIMIT( (signed)((y_start)>>3) ,0 ,GUI_PAGEs);
    unsigned int page_end     = GUI_LIMIT( (signed)((y_end  )>>3) ,0 ,GUI_PAGEs);
    unsigned int column_start = GUI_LIMIT( (signed)( GUI_MIN( ( GUI_MIN(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
    unsigned int column_end   = GUI_LIMIT( (signed)( GUI_MAX( ( GUI_MAX(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
#else
    unsigned int xs           = GUI_LIMIT( (signed)( GUI_MIN( ( GUI_MIN(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
    unsigned int xe           = GUI_LIMIT( (signed)( GUI_MAX( ( GUI_MAX(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
    unsigned int ys           = GUI_LIMIT( (signed)( GUI_MIN( ( GUI_MIN(y1,y2) ) ,y3)  )    ,0 ,GUI_X_WIDTH-1);
    unsigned int ye           = GUI_LIMIT( (signed)( GUI_MAX( ( GUI_MAX(y1,y2) ) ,y3)  )    ,0 ,GUI_X_WIDTH-1);
#endif
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    __Graph_line_raw(x1,y1,x2,y2,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw(x2,y2,x3,y3,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw(x3,y3,x1,y1,Screen.penColor,&BufferInfo,__ApplyPixel_fill);

    if( Screen.autoDisplayMode == true ){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
        GUI_RefreashArea(xs,ys,xe,ye);
#endif
    }else{
        __addAreaNeedRefreash(xs,ys,xe,ye);
    }
}

void GUI_FillQuadrilateral(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
#if GUI_ASSERT
    //...//
#endif
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    int tmp_y[] = {y1,y2,y3,y4};
    int tmp_x[] = {x1,x2,x3,x4};

    int xs = __findMin_INT(tmp_x,4).value;
    int xe = __findMax_INT(tmp_x,4).value;
    int ys = __findMin_INT(tmp_y,4).value;
    int ye = __findMax_INT(tmp_y,4).value;


    __Graph_quad_fill(x1,y1,x2,y2,x3,y3,x4,y4,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    if( Screen.autoDisplayMode == true ){
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    //...//
#else
        GUI_RefreashArea(xs,ys,xe,ye);
#endif
    }else{
        __addAreaNeedRefreash(xs,ys,xe,ye);
    }
}

//============================================ End of Graphic Function ==============================================//
//============================================ End of Graphic Function ==============================================//
//============================================ End of Graphic Function ==============================================//
//==================================================== RGB Test =====================================================//
//==================================================== RGB Test =====================================================//
//==================================================== RGB Test =====================================================//
#if GUI_TEST_EXTENTION
void GUI_TestRGB(unsigned int GUI_TEST_RGB_xxxx ,...){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    static double phi = 0.0;
    WORD   penColor   = Screen.penColor;
    uint   penSize    = Screen.penSize;

    const double pi = 3.1415926;

    const uint R_MAX = (uint)(1.414*GUI_MAX(GUI_Y_WIDTH,GUI_X_WIDTH));

    if(phi >= 6.28318530717 )
        phi = 0.0;

    switch(GUI_TEST_RGB_xxxx){
        case GUI_TEST_RGB_VER_RAINBOW:
            for( uint x=0; x<GUI_X_WIDTH;x++ ){
                BYTE R = (BYTE)(128+128*sin(2*pi*x/GUI_X_WIDTH + phi          ));
                BYTE G = (BYTE)(128+128*sin(2*pi*x/GUI_X_WIDTH + phi + 2.0*pi/3));
                BYTE B = (BYTE)(128+128*sin(2*pi*x/GUI_X_WIDTH + phi + 4.0*pi/3));
                
                for( uint y=0; y<GUI_Y_WIDTH;y++){
                    __ApplyPixel_fill(x,y,GUI_MAKE_COLOR( R,G,B ),&BufferInfo );
                }
            }
            break;
        case GUI_TEST_RGB_HOR_RAINBOW:
            for( uint y=0; y<GUI_Y_WIDTH;y++ ){
                BYTE R = (BYTE)(128+128*sin(2*pi*y/GUI_Y_WIDTH + phi          ));
                BYTE G = (BYTE)(128+128*sin(2*pi*y/GUI_Y_WIDTH + phi + 2.0*pi/3));
                BYTE B = (BYTE)(128+128*sin(2*pi*y/GUI_Y_WIDTH + phi + 4.0*pi/3));
                
                for( uint x=0; x<GUI_X_WIDTH;x++){
                    // Screen.penColor = GUI_MAKE_COLOR( R,G,B );
                    __ApplyPixel_fill(x,y,GUI_MAKE_COLOR( R,G,B ),&BufferInfo );
                }
            }
            break;
        case GUI_TEST_RGB_ROL_RAINBOW:
            penSize = 2;
            for( uint r=0; r<R_MAX;r++ ){
                BYTE R = (BYTE)(128+128*sin(2*pi*r/GUI_Y_WIDTH + phi          ));
                BYTE G = (BYTE)(128+128*sin(2*pi*r/GUI_Y_WIDTH + phi + 2.0*pi/3));
                BYTE B = (BYTE)(128+128*sin(2*pi*r/GUI_Y_WIDTH + phi + 4.0*pi/3));
                penColor = GUI_MAKE_COLOR( R,G,B );
                __Graph_circle_edged(GUI_X_WIDTH>>1,GUI_Y_WIDTH>>1,r,penSize,penColor,&BufferInfo,__ApplyPixel_fill);
                
            }
            break;

        default:
            break;
    }
    GUI_RefreashScreen();
    Screen.penColor = penColor;
    Screen.penSize  = penSize;
    phi+=0.1;
}

#endif
//================================================ End of RGB Test ==================================================//
//================================================ End of RGB Test ==================================================//
//================================================ End of RGB Test ==================================================//
//================================================= Text Function ===================================================//
//================================================= Text Function ===================================================//
//================================================= Text Function ===================================================//
struct __WordChain{
    char* sentence;
    char* word;
    struct __WordChain* nextWord;
};

static struct __WordChain* __creatTextSocket(const char* const_pSentence){
    char* pSentence = (char*)malloc(strlen(const_pSentence));
    strcpy(pSentence, const_pSentence);
    
    char* p = strtok(pSentence," ");

    struct __WordChain* pHeadWord        = (struct __WordChain*)malloc(sizeof(struct __WordChain));
    struct __WordChain* pWord            = pHeadWord;

    pWord->sentence = pSentence;
    pWord->word = p;
    pWord->nextWord = NULL;
    while( (p = strtok(NULL," ")) != NULL ){
        pWord->nextWord = (struct __WordChain*)malloc(sizeof(struct __WordChain));
        pWord           = pWord->nextWord;
        pWord->sentence = pSentence;
        pWord->word     = p;
        pWord->nextWord = NULL;
    }

    return pHeadWord;
}

static void __deleteTextSocket(struct __WordChain* p){
    while(p != NULL){
        struct __WordChain* tmp = p;
        
        if(tmp->nextWord == NULL){
            free(tmp->sentence);
        }
        p = tmp->nextWord;
        free(tmp);
    }
}

static void __insertChar(struct __FontChar_t* pChar){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    for(uint y=0;y < pChar->height;y++){
        for(uint x=0;x < pChar->width ;x++){
            if( (Screen.txtPos.x + x) >= GUI_X_WIDTH )
                while(1);
            if( (Screen.txtPos.y + y) >= GUI_Y_WIDTH )
                while(1);

            if(  ( ((*(pChar->byte + (y>>3)*(pChar->width) + x))>>(y&0x07))&0x01  ) == 1 )
        //  if(  (  (*(pChar->byte + (y/8 )*(pChar->width) + x))>>(y%8   ))&0x01  ) Same effect.
                __ApplyPixel_fill(Screen.txtPos.x + x,Screen.txtPos.y + y,Screen.penColor,&BufferInfo );
//            else
//                __erasePixel (Screen.txtPos.x + x,Screen.txtPos.y + y,Screen.bkColor,&BufferInfo );
        }
    }
}

static void __insertWord(const char* word){
    size_t pos = strcspn(word, " ");
    int    num = 0;
    while(pos--){
        struct __FontChar_t* pChar = (Screen.pFont + (*(word+num)) - 32);
        __insertChar(pChar);
        Screen.txtPos.x += pChar->width;
        num++;
    }
}

//...//
void __insertJustifiedText(const char* text,uint xs,uint ys,uint xe,uint ye){
    struct __WordChain* pSentence =  __creatTextSocket(text);

    __deleteTextSocket(pSentence);
}

void GUI_DispChar(unsigned char c){

    c = GUI_LIMIT( (signed)(c) , ' ' , 127 );
    struct __Screen_t*   s     = &Screen;
    struct __FontChar_t* pChar = (s->pFont + c - 32);

    if(s->txtPos.x > GUI_X_WIDTH - pChar->width){
        s->txtPos.x = 0;
        s->txtPos.y += pChar->height;
        if(s->txtPos.y > GUI_Y_WIDTH - pChar->height)
            s->txtPos.y = 0;
    }

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    int page_start    = ((s->txtPos.y)>>3);
    int page_end      = ((s->txtPos.y + pChar->height-1)>>3);
    int column_start  = s->txtPos.x;
    int column_end    = s->txtPos.x + pChar->width -1;
#else
    int xs            = s->txtPos.x;
    int ys            = s->txtPos.y;
    int xe            = s->txtPos.x + pChar->width -1;
    int ye            = s->txtPos.y + pChar->height-1;
#endif
    __insertChar(pChar);
    
    if( Screen.autoDisplayMode == true ){
        GUI_RefreashArea(xs, ys, xe, ye);
    }else{
        __addAreaNeedRefreash(xs, ys, xe, ye);
    }

    s->txtPos.x += pChar->width;
}

void GUI_DispCharAt(unsigned char c,int x,int y,...){
    Screen.txtPos.x = x;
    Screen.txtPos.y = y;
    GUI_DispChar(c);
}

void GUI_DispChars(unsigned char c,int num,...){
    while(num--){
        GUI_DispChar(c);
    }
}

void GUI_DispWord(const char* word,...){
    struct __Screen_t*   s = &Screen;

    const char* p = word;
    struct __FontChar_t* pChar = NULL;
    uint8_t pixLength = 0;
    while(*p!='\0'){
        pChar      = Screen.pFont + (*p - 32);
        pixLength += pChar->width;
        p++;
    }

    if(s->txtPos.x > GUI_X_WIDTH - pixLength){
        s->txtPos.x = 0;
        s->txtPos.y += pChar->height;
        if(s->txtPos.y > GUI_Y_WIDTH - pChar->height)
            s->txtPos.y = 0;
    }

    va_list ap;
    va_start(ap,word);
    const int clearScreen      = va_arg(ap,int);
    const int onlyChangeBuffer = va_arg(ap,int);
    va_end(ap);

    if(clearScreen==true)
        __Clear_gram_all();

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    uint page_start    = ((s->txtPos.y)>>3);
    uint page_end      = ((s->txtPos.y + pChar->height-1)>>3);
    uint column_start  = s->txtPos.x;
    uint column_end    = s->txtPos.x + pChar->width -1;
#else
    int x_start       = s->txtPos.x;
    int y_start       = s->txtPos.y;
    int x_end         = s->txtPos.x + pixLength -1;
    int y_end         = s->txtPos.y + pChar->height-1;
#endif
    __insertWord(word);

    if(onlyChangeBuffer!=true){
        if(clearScreen==true)
            GUI_RefreashScreen();
        else{
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
            GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
            GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
        }
    }

}


//============================================== End of Text Function ================================================//
//============================================== End of Text Function ================================================//
//============================================== End of Text Function ================================================//
//=============================================== Dialog Box Function ================================================//
//=============================================== Dialog Box Function ================================================//
//=============================================== Dialog Box Function ================================================//

#if GUI_DIALOG_DISPLAY
 #define __BAR_HEIGHT__    (uint)((10*GUI_Y_WIDTH)>>7) // 10
 #define __BUT_SIZE__      (uint)(__BAR_HEIGHT__*0.6)  // 3
 #define __BUT_INTERVAL__  (uint)((__BUT_SIZE__)+(__BUT_SIZE__>>1))// 9
 #define __BUT_INDENT__    (uint)(__BAR_HEIGHT__*0.7)//7

static void __insertButton(const char* name,Pixel_t color){

}

void GUI_DialogBox(struct GUI_DialogBox_t* p,const char* text,...){
 // Buffer infomation
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    Pixel_t penColor;
    size_t  penSize;
 // Draw Edge
    penColor = GUI_MAKE_COLOR(232,232,232);
    penSize  = 1;
    __Graph_rect_edged(p->x_start , p->y_start , p->x_end , p->y_end,penSize,penColor,&BufferInfo,__ApplyPixel_fill);
 // Draw Bar
    for(unsigned int y = p->y_start;y <= p->y_start+__BAR_HEIGHT__;y++){
        if(y == p->y_start){
            for(unsigned int x = p->x_start;x <= p->x_end;x++)
                Screen.buffer[M_SCREEN_MAIN][y][x].data = Screen.penColor;
        }else{
            memcpy(&(Screen.buffer[M_SCREEN_MAIN][y         ][p->x_start].data),\
                   &(Screen.buffer[M_SCREEN_MAIN][p->y_start][p->x_start].data),\
                   ((p->x_end - p->x_start + 1)*sizeof(Pixel_t)) );
        }
    }
 // Draw Box Button
    penColor = GUI_MAKE_COLOR(224,99 ,88 );
    __Graph_circle_fill( p->x_start+__BUT_INDENT__                    , p->y_start+(__BAR_HEIGHT__>>1),(__BUT_SIZE__>>1), penColor, &BufferInfo,__ApplyPixel_fill );
    penColor = GUI_MAKE_COLOR(224,193,75 );
    __Graph_circle_fill( p->x_start+__BUT_INDENT__+__BUT_INTERVAL__   , p->y_start+(__BAR_HEIGHT__>>1),(__BUT_SIZE__>>1), penColor, &BufferInfo,__ApplyPixel_fill );
    penColor = GUI_MAKE_COLOR(104,102,98 );
    __Graph_circle_fill( p->x_start+__BUT_INDENT__+__BUT_INTERVAL__*2 , p->y_start+(__BAR_HEIGHT__>>1),(__BUT_SIZE__>>1), penColor, &BufferInfo,__ApplyPixel_fill );
 // Draw User Button
    struct GUI_DialogBox_Button_t* pButton = p->firstButton;
    while(pButton != NULL){
        //...//
        // Screen.penColor = GUI_MAKE_COLOR(232,232,232);
        __insertButton(pButton->name,GUI_COLOR_BLUE);
        pButton = pButton->nextButton;
    }

 // Display
    GUI_RefreashArea(p->x_start , p->y_start , p->x_end , p->y_end);
}
    
#endif

#if GUI_ANIMATION_DISPLAY

//============================================== End of Dialog Box Function ============================================//
//============================================== End of Dialog Box Function ============================================//
//============================================== End of Dialog Box Function ============================================//
//=================================================== Animation Function ===============================================//
//=================================================== Animation Function ===============================================//
//=================================================== Animation Function ===============================================//



static void __remove_animation_ProgressBar_LR(__AnimationConfigChain* p){
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;

    int cnt = p->config.height;
    while(cnt--)
        memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
}

static void __insert_animation_ProgressBar_LR(__AnimationConfigChain* p,uint fp_0_255_){
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;
    uint x_end   = x_start + p->config.width  - 1;
    uint y_end   = y_start + p->config.height - 1;
    // Clear Area ===================//
    {
        int cnt = p->config.height;
        while(cnt--)
            memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
    }
    // Draw Edge ===================//
    {
        uint x = x_start, y = y_start;
        while( x<=x_end && y<=y_end ){
            if( x < x_end ){
                Screen.buffer[M_SCREEN_MAIN][y_start][x].data = GUI_COLOR_WHITE;//...//
                Screen.buffer[M_SCREEN_MAIN][y_end][x].data   = GUI_COLOR_WHITE;//...//
                x++;
            }
            else{
                Screen.buffer[M_SCREEN_MAIN][y][x_start].data = GUI_COLOR_WHITE;//...//
                Screen.buffer[M_SCREEN_MAIN][y][x_end].data   = GUI_COLOR_WHITE;//...//
                y++;
            }
        }
    }

    // Fill Rect ===================//
    {
        uint progress = (fp_0_255_ * (p->config.width-2))>>8;
        for(uint y=y_start+1;y<y_end;y++){
            if(y == y_start+1){
                for(uint x=1;x<=progress;x++)
                    Screen.buffer[M_SCREEN_MAIN][y][x_start+x].data = p->config.themeColor;
            }else{
                memcpy(&(Screen.buffer[M_SCREEN_MAIN][y        ][x_start+1].data),\
                       &(Screen.buffer[M_SCREEN_MAIN][y_start+1][x_start+1].data),\
                       progress*sizeof(Pixel_t) );
            }
        }
    }
}

static void __remove_animation_ProgressBar_UD(__AnimationConfigChain* p){
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;
    int cnt = p->config.height;
    while(cnt--)
        memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
}

static void __insert_animation_ProgressBar_UD(__AnimationConfigChain* p,uint fp_0_255_){
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;
    uint x_end   = x_start + p->config.width  - 1;
    uint y_end   = y_start + p->config.height - 1;

    // Clear Area ===================//
    {
        int cnt = p->config.height;
        while(cnt--)
            memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
    }
    // Draw Edge ===================//
    {
        uint x = x_start, y = y_start;
        while( x<=x_end && y<=y_end ){
            if( x < x_end ){
                Screen.buffer[M_SCREEN_MAIN][y_start][x].data = GUI_COLOR_WHITE;//...//
                Screen.buffer[M_SCREEN_MAIN][y_end][x].data   = GUI_COLOR_WHITE;//...//
                x++;
            }
            else{
                Screen.buffer[M_SCREEN_MAIN][y][x_start].data = GUI_COLOR_WHITE;//...//
                Screen.buffer[M_SCREEN_MAIN][y][x_end].data   = GUI_COLOR_WHITE;//...//
                y++;
            }
        }
    }
    // Fill Rect ===================//
    {
        uint progress = (fp_0_255_ * (p->config.height-2))>>8;
        for(uint y=(y_end-progress-1);y<y_end;y++){
            if(y == (y_end-progress-1)){
                for(uint x=1;x<(p->config.width)-1;x++)
                    Screen.buffer[M_SCREEN_MAIN][y][x_start+x].data = p->config.themeColor;
            }else{
                memcpy(&(Screen.buffer[M_SCREEN_MAIN][y               ][x_start+1].data),\
                       &(Screen.buffer[M_SCREEN_MAIN][y_end-progress-1][x_start+1].data),\
                       ((p->config.width)-2)*sizeof(Pixel_t) );
            }
        }
    }
}

static void __remove_animation_ProgressLoop(__AnimationConfigChain* p){
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;
    int cnt = p->config.height;
    while(cnt--)
        memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
}

static void __insert_animation_ProgressLoop(__AnimationConfigChain* p,uint fp_0_255_){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    uint x_center = p->config.x_pos + ((p->config.width)>>1);
    uint y_center = p->config.x_pos + ((p->config.height)>>1);
    uint radius   = (p->config.width>>1)-2;
    double  phi   = __map(fp_0_255_,0,255,0,M_2_PI);
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;
    size_t penSize;
    // Clear Aream =====================//
    int cnt = p->config.height;
    while(cnt--)
        memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
    // Draw a Circle ===================//
    penSize = 3;
    __Graph_circle_edged(x_center,y_center,radius, penSize,p->config.themeColor,&BufferInfo,__ApplyPixel_fill);
    // Draw Line =======================//

    int x1 = (int)(x_center);
    int y1 = (int)(y_center);


    int x2 = (int)(x_center + ((radius<<3)/10)*(lround(sin(phi))));
    int y2 = (int)(y_center - ((radius<<3)/10)*(lround(cos(phi))));
    __Graph_line_raw(x1,y1,x2,y2,p->config.themeColor,&BufferInfo,__ApplyPixel_fill);
}

static void __remove_animation_ValueBar_iOS(__AnimationConfigChain* p){
    //...//
}

static void __insert_animation_ValueBar_iOS(__AnimationConfigChain* p,uint fp_0_255_){

    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    Pixel_t penColor = Screen.penColor;
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;
    uint x_end   = x_start + p->config.width  - 1;
    uint y_end   = y_start + p->config.height - 1;

    // Remove Bar ==============================//
    {
        uint x_start = p->config.x_pos;
        uint y_start = p->config.y_pos;
        int cnt = p->config.height;
        while(cnt--)
            memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
    }

    // Add Slider
    int  sliderRadius   = (int)(((p->config.height)>>1)*0.8);
    int  sliderDiameter = sliderRadius<<1;
    uint progress       = (fp_0_255_ * (p->config.width-2*sliderRadius))>>8;

    int  sliderX        = x_start + sliderRadius + progress;
    int  sliderY        = ((y_start+y_end)>>1);
    __Graph_circle_fill(sliderX,sliderY,sliderRadius,p->config.themeColor,&BufferInfo,__ApplyPixel_fill);
    
    // Add marginal point
    // __Graph_circle_fill(...);
    // __Graph_circle_fill(...);

    // Add Active Bar
    int  barHeight = ((sliderRadius/2)<3)?(3):(sliderRadius/2);
    int  barStart  = (y_start+y_end-barHeight)/2;
    int  barEnd    = (y_start+y_end+barHeight)/2;
    for(uint y=barStart;y<barEnd;y++){
        if(y == barStart){
            for(uint x=0;x<=progress;x++)
                Screen.buffer[M_SCREEN_MAIN][y][x_start+x].data = p->config.themeColor;
        }else{
            memcpy(&(Screen.buffer[M_SCREEN_MAIN][y       ][x_start].data),\
                   &(Screen.buffer[M_SCREEN_MAIN][barStart][x_start].data),\
                   progress*sizeof(Pixel_t) );
        }
    }

    // Add Inactive Bar
    for(int y=barStart;y<barEnd;y++){
        if(y == barStart){
            for(int x=x_start+progress+sliderDiameter+1;x<=x_end;x++)
                Screen.buffer[M_SCREEN_MAIN][y][x].data = GUI_DARKEN_COLOR_2Bit(p->config.themeColor);
        }else{
            memcpy(&(Screen.buffer[M_SCREEN_MAIN][y       ][x_start+progress+sliderDiameter+1].data),\
                   &(Screen.buffer[M_SCREEN_MAIN][barStart][x_start+progress+sliderDiameter+1].data),\
                   (x_end-progress-sliderDiameter)*sizeof(Pixel_t) );
        }
    }
    Screen.penColor = penColor;
}

static void __remove_animation_SlideSwitch(__AnimationConfigChain* p){

}

static void __insert_animation_SlideSwitch(__AnimationConfigChain* p, uint fp_0_255_){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    int           eps    = 1;
    const int     height = p->config.height - eps;
    const int     width  = p->config.width  - eps;
    

    int radius = (height- eps )>>1;
    int x1     = p->config.x_pos + radius;
    int y1     = p->config.y_pos + radius;

    int x2     = p->config.x_pos + width  - 1 - radius;
    int y2     = y1;

    int ys     = p->config.y_pos;
    int ye     = p->config.y_pos + height - 1;

    uint progress = ( fp_0_255_ * (x2-x1+1) )>>8;

    PixelUnit_t color;
    {
        PixelUnit_t ON_Pixel  = {.data = p->config.themeColor};
        PixelUnit_t OFF_Pixel = {.data = p->config.backColor};

        Point3D_t  ON_Color  = { .x = ON_Pixel.R ,\
                                 .y = ON_Pixel.G ,\
                                 .z = ON_Pixel.B };

        Point3D_t  OFF_Color = { .x = OFF_Pixel.R ,\
                                 .y = OFF_Pixel.G ,\
                                 .z = OFF_Pixel.B };

        Point3D_t  BAR_Color = __findPoint_VectorProportion( &OFF_Color ,&ON_Color , (fp_0_255_/255.0));

        color.R = (int)BAR_Color.x;
        color.G = (int)BAR_Color.y;
        color.B = (int)BAR_Color.z;
    }

    __Graph_circle_fill(x1,y1,radius,color.data,&BufferInfo,__ApplyPixel_fill);
    
    __Graph_circle_fill(x2,y2,radius,color.data,&BufferInfo,__ApplyPixel_fill);
    
    __Graph_rect_fill(x1,ys,x2,ye,color.data,&BufferInfo,__ApplyPixel_fill);

    eps = (p->config.height<<1)/40;
    if(eps == 0) eps = 1;
    __Graph_circle_fill(x1+progress,y1,radius-eps,GUI_COLOR_LIGHTSLATEGRAY,&BufferInfo,__ApplyPixel_fill);

}

static __AnimationConfigChain* __searchAnimationConfigChain(BYTE ID){
    __AnimationConfigChain* p = Screen.cfgAnimationHeadNode;

    while(p != NULL){
        if(p->config.ID == ID)
            break;

        p = p->nextConfig;
    }

    return p;
}

/*====================================
 > 创建一个动画插件
=====================================*/
void GUI_CreateAnimationSocket(struct GUI_AnimConfig_t* config){
    __AnimationConfigChain* pConfig = Screen.cfgAnimationHeadNode;
    __AnimationConfigChain* pTmpConfig;
 // ID should be unique.
    __exit( NULL != __searchAnimationConfigChain(config->ID) );

    switch((int)(config->GUI_ANIM_xxxx)){
        case GUI_ANIM_PROGRESSBAR_STD_LR:
            pTmpConfig = (__AnimationConfigChain*)__malloc(sizeof(struct __AnimationConfigChain));
            pTmpConfig->insertFunc = __insert_animation_ProgressBar_LR;
            pTmpConfig->removeFunc = __remove_animation_ProgressBar_LR;
            break;
        case GUI_ANIM_PROGRESSBAR_STD_UD:
            pTmpConfig = (__AnimationConfigChain*)__malloc(sizeof(struct __AnimationConfigChain));
            pTmpConfig->insertFunc = __insert_animation_ProgressBar_UD;
            pTmpConfig->removeFunc = __remove_animation_ProgressBar_UD;
            break;
        case GUI_ANIM_VALUEBAR_IOS_LR:
            pTmpConfig = (__AnimationConfigChain*)__malloc(sizeof(struct __AnimationConfigChain));
            pTmpConfig->insertFunc = __insert_animation_ValueBar_iOS;
            pTmpConfig->removeFunc = __remove_animation_ValueBar_iOS;
            break;
        // case GUI_ANIM_VALUEBAR_IOS_UD:
        //     break;
        case GUI_ANIM_PROGRESSLOOP:
            pTmpConfig = (__AnimationConfigChain*)__malloc(sizeof(struct __AnimationConfigChain));
            pTmpConfig->insertFunc = __insert_animation_ProgressLoop;
            pTmpConfig->removeFunc = __remove_animation_ProgressLoop;
            break;
        case GUI_ANIM_SLIDESWITCH:
            pTmpConfig = (__AnimationConfigChain*)__malloc(sizeof(struct __AnimationConfigChain));
            pTmpConfig->insertFunc = __insert_animation_SlideSwitch;
            pTmpConfig->removeFunc = __remove_animation_SlideSwitch;
            break;
        default:__exit(true);
    }

    pTmpConfig->config     = *config;
    pTmpConfig->nextConfig = NULL;

    if(pConfig == NULL)
        Screen.cfgAnimationHeadNode = pTmpConfig;
    else{
        do{
            if(pConfig->nextConfig == NULL){
                pConfig->nextConfig = pTmpConfig;
                break;
            }
            pConfig = pConfig->nextConfig;
        }while(1);
    }
}

void GUI_ChangeAnimationSocket(BYTE ID){
    //...//
}

// 显示动画插件
void GUI_ShowAnimation(BYTE ID,uint fp_0_255_,...){
    __AnimationConfigChain* pNow = __searchAnimationConfigChain(ID);

    __exit(pNow == NULL);

    (*(pNow->insertFunc))(pNow,fp_0_255_);

    uint x_start = pNow->config.x_pos;
    uint y_start = pNow->config.y_pos;
    uint x_end   = pNow->config.x_pos + pNow->config.width  - 1;
    uint y_end   = pNow->config.y_pos + pNow->config.height - 1;

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    //...//
#else
    GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
}

// 隐藏动画插件
void GUI_HideAnimation(BYTE ID){
    __AnimationConfigChain* pNow = __searchAnimationConfigChain(ID);

    __exit(pNow == NULL);

    (*(pNow->removeFunc))(pNow);
    
    uint x_start = pNow->config.x_pos;
    uint y_start = pNow->config.y_pos;
    uint x_end   = pNow->config.x_pos + pNow->config.width  - 1;
    uint y_end   = pNow->config.y_pos + pNow->config.height - 1;

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    //...//
#else
    GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
}

// 删除动画插件
void GUI_DeleteAnimationSocket(BYTE ID){
    __AnimationConfigChain* pNow  = Screen.cfgAnimationHeadNode;
    __AnimationConfigChain* pLast = Screen.cfgAnimationHeadNode;
    while(pNow != NULL){
        if(pNow->config.ID == ID){
            pLast->nextConfig = pNow->nextConfig;
            GUI_HideAnimation(ID);
            __free(pNow);
            break;
        }
        pLast = pNow;
        pNow  = pNow->nextConfig;
    }
}

#endif
//============================================= End of Animation Function ==============================================//
//============================================= End of Animation Function ==============================================//
//============================================= End of Animation Function ==============================================//
//=================================================== Icon Function ====================================================//
//=================================================== Icon Function ====================================================//
//=================================================== Icon Function ====================================================//
#if GUI_ICON_DISPLAY

static void __remove_icon_Arrow_UP(struct __IconConfigChain* p){
    uint x_start = p->config.x_pos;
    uint y_start = p->config.y_pos;

    int cnt = p->config.size;
    while(cnt--)
        memset(&(Screen.buffer[M_SCREEN_MAIN][y_start+cnt][x_start].data),0,(p->config.size)*sizeof(Pixel_t) );

}

static void __insert_icon_Arrow_UP(struct __IconConfigChain* p){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    Pixel_t penColor = Screen.penColor;
    uint    penSize  = Screen.penSize;

    int xs = (int)(p->config.x_pos);
    int xe = (int)((p->config.x_pos)+(p->config.size)-1);
    int ys = (int)(p->config.y_pos);
    int ye = (int)((p->config.y_pos)+(p->config.size)-1);

    int width        = (((p->config.size)>>3) == 0 ) ? (1):(((p->config.size)>>3)) ;
    int halfWidth    = (int)(width>>1);

    int xc = GUI_CENTER(xs,xe);

    // Screen.penColor  = p->config.themeColor;
    // Screen.penSize   = width;

    __Graph_line_sausage(    xc            ,\
                            ys + halfWidth,\
                            xc            ,\
                            ye - halfWidth,\
                            width         ,\
                            p->config.themeColor,\
                            &BufferInfo,__ApplyPixel_fill    );
    
    __Graph_line_sausage(    xc            ,\
                            ys + halfWidth,\
                            xs + halfWidth + (p->config.size)/10,\
                            ys + xc - xs   - (p->config.size)/10,\
                            width         ,\
                            p->config.themeColor,\
                            &BufferInfo,__ApplyPixel_fill    );

    __Graph_line_sausage(    xc            ,\
                            ys + halfWidth,\
                            xe - halfWidth - (p->config.size)/10,\
                            ys + xc - xs   - (p->config.size)/10,\
                            width         ,\
                            GUI_COLOR_RED,\
                            &BufferInfo,__ApplyPixel_fill    );

    
    Screen.penColor = penColor;
    Screen.penSize  = penSize;
}

static void __remove_icon_Windows10(struct __IconConfigChain* p){
    

}

static void __insert_icon_Windows10(struct __IconConfigChain* p){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    Pixel_t penColor = Screen.penColor;
    uint    penSize  = Screen.penSize;
    
    int x2 = (int)(p->config.x_pos + p->config.size*69.0/71) - 1;
    int y2 = p->config.y_pos;

    int x1 = p->config.x_pos;
    int y1 = (int)(y2 + p->config.size*9.0/79) - 1;
    
    int x3 = x2;
    int y3 = y2 + p->config.size-1;
    
    int x4 = x1;
    int y4 = (int)(y1 + p->config.size*54.0/72) - 1;

    int line_0  = (int)((y1+y4)>>1);
    int line_90 = (int)((2.5*x2+3*x1)/(2.5+3));

    __Graph_quad_fill(x1,y1,x2,y2,x3,y3,x4,y4,Screen.penColor,&BufferInfo,__ApplyPixel_fill);
    
    Screen.penColor = GUI_COLOR_BLACK;
    Screen.penSize  = (p->config.size)>33 ? (int)((p->config.size)*3/100):1;
    __Graph_line_raw(p->config.x_pos,line_0,p->config.x_pos+p->config.size-1,line_0,p->config.themeColor,&BufferInfo,__ApplyPixel_fill);
    __Graph_line_raw(line_90,p->config.y_pos,line_90,p->config.y_pos+p->config.size-1,p->config.themeColor,&BufferInfo,__ApplyPixel_fill);
    
    Screen.penSize  = penSize;
    Screen.penColor = penColor;
}

static __IconConfigChain* __searchIconConfigChain(BYTE ID){
    __IconConfigChain* p = Screen.cfgIconHeadNode;

    while(p != NULL){
        if(p->config.ID == ID)
            break;

        p = p->nextConfig;
    }

    return p;
}

// 创建一个图标插件
void GUI_CreateIconSocket(struct GUI_IconConfig_t* config){
    __IconConfigChain* pConfig;
    __IconConfigChain* curConfig = Screen.cfgIconHeadNode;

    // ID should be unique.
    __exit( NULL != __searchIconConfigChain(config->ID) );

    switch((int)(config->GUI_ICON_xxxx)){
        case GUI_ICON_ARROW_UP:
            pConfig = (__IconConfigChain*)malloc( sizeof(__IconConfigChain) );
            pConfig->insertFunc = __insert_icon_Arrow_UP;
            pConfig->removeFunc = __remove_icon_Arrow_UP;
            break;
        case GUI_ICON_WIN10:
            pConfig = (__IconConfigChain*)malloc( sizeof(__IconConfigChain) );
            pConfig->insertFunc = __insert_icon_Windows10;
            pConfig->removeFunc = __remove_icon_Windows10;
            break;
        default: __exit(true);
    }

    pConfig->config     = (*config);
    pConfig->nextConfig = NULL;

    if(curConfig == NULL)
        Screen.cfgIconHeadNode = pConfig;
    else{
        do{
            if(curConfig->nextConfig == NULL){
                curConfig->nextConfig = pConfig;
                break;
            }else{
                curConfig = curConfig->nextConfig;
            }
        }while(1);
    }
}

void GUI_ChangeIconSocket(struct GUI_IconConfig_t* newConfig,BYTE ID){

    __IconConfigChain* pNow = __searchIconConfigChain(ID);
    __exit(pNow == NULL);

    pNow->config    = (*newConfig);

    // ID will never be changed!
    pNow->config.ID = ID;
}

// 显示图标
void GUI_ShowIcon(BYTE ID){
    Pixel_t penColor;
    size_t  penSize;
    __IconConfigChain* pNow = __searchIconConfigChain(ID);

    __exit(pNow == NULL);

    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    uint x_start = pNow->config.x_pos;
    uint y_start = pNow->config.y_pos;
    uint x_end   = pNow->config.x_pos + pNow->config.size - 1;
    uint y_end   = pNow->config.y_pos + pNow->config.size - 1;

    if(pNow->config.dispFrame == true){
        penColor = GUI_COLOR_WHITE;
        penSize  = 1;
        __Graph_rect_edged(x_start,y_start,x_end,y_end,penSize,penColor,&BufferInfo,__ApplyPixel_fill);
    }
    (*(pNow->insertFunc))(pNow);

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    //...//
#else
    GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
}

// 隐藏图标
void GUI_HideIcon(BYTE ID){
    __IconConfigChain* pNow = __searchIconConfigChain(ID);
    //...//
    __exit(pNow == NULL);

}

// 删除一个图标插件
void GUI_DeleteIconScoket(BYTE ID){
    __IconConfigChain* pNow  = Screen.cfgIconHeadNode;
    __IconConfigChain* pLast = Screen.cfgIconHeadNode;
    while(pNow != NULL){
        if(pNow->config.ID == ID){
            pLast->nextConfig = pNow->nextConfig;
            GUI_HideIcon(ID);
            __free(pNow);
            break;
        }
        pLast = pNow;
        pNow  = pNow->nextConfig;
    }
}

#endif
//=============================================== End of Icon Function =================================================//
//=============================================== End of Icon Function =================================================//
//=============================================== End of Icon Function =================================================//
//=============================================== Trace Watch Function =================================================//
//=============================================== Trace Watch Function =================================================//
//=============================================== Trace Watch Function =================================================//

#if GUI_TRACE_WATCH_DISPLAY

static void __remove_trace_Linear(struct __TraceWatchConfigChain* p){

}

static void __insert_trace_Linear(struct __TraceWatchConfigChain* p){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };
    __Clear_gram_part( p->config.x_pos                        ,\
                            p->config.y_pos                        ,\
                            p->config.x_pos + p->config.width  - 1 ,\
                            p->config.y_pos + p->config.height - 1 );

 //自适应数据窗口,横向步长取决于记录数据次数RecordSize,纵向步长取决于数据buffer中的最值
    int x_step_pixel = p->config.width / (p->config.recordSize-1);
    int x_step_eps   = p->config.width % (p->config.recordSize-1);
    if(x_step_pixel==0) x_step_pixel = 1;

    double y_step_pixel = __findMax_INT(p->buffer,p->config.dataNum*p->config.recordSize).value*1.3/p->config.height;


    for(size_t dataIndex=0;dataIndex<p->config.dataNum;dataIndex++){
        size_t cnt = 0;
        int    x   = p->config.x_pos     ,y = p->config.y_pos+p->config.height-1;
        do{
            __Graph_line_raw( x                                            ,\
                          y - (int)lround(*(p->buffer+dataIndex*p->config.recordSize+cnt)/y_step_pixel)    ,\
                          x + x_step_pixel + (x_step_eps > cnt)-1      ,\
                          y - (int)lround(*(p->buffer+dataIndex*p->config.recordSize+cnt+1)/y_step_pixel)  ,\
                          p->config.data[dataIndex].dataColor          ,\
                          &BufferInfo                                  ,\
                          __ApplyPixel_fill );
            x += (x_step_pixel + (x_step_eps > cnt));
        }while(++cnt < p->config.recordSize-1);
    }

     //画图表框
    __Graph_line_raw( p->config.x_pos                    ,\
                  p->config.y_pos                    ,\
                  p->config.x_pos                    ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.backColor                ,\
                  &BufferInfo                        ,\
                  __ApplyPixel_fill);
    __Graph_line_raw( p->config.x_pos+p->config.width -1 ,\
                  p->config.y_pos                    ,\
                  p->config.x_pos+p->config.width -1 ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.backColor                ,\
                  &BufferInfo                        ,\
                  __ApplyPixel_fill );
    __Graph_line_raw( p->config.x_pos                    ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.x_pos+p->config.width -1 ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.backColor                ,\
                  &BufferInfo                        ,\
                  __ApplyPixel_fill );

}

static void __remove_trace_Column(struct __TraceWatchConfigChain* p){

}

static void __insert_trace_Column(struct __TraceWatchConfigChain* p){
    BufferInfo_t BufferInfo = {    .pBuffer = Screen.buffer,
                                .height  = GUI_Y_WIDTH  ,
                                .width   = GUI_X_WIDTH };

    __Clear_gram_part( p->config.x_pos                        ,\
                            p->config.y_pos                        ,\
                            p->config.x_pos + p->config.width  - 1 ,\
                            p->config.y_pos + p->config.height - 1 );

    //自适应数据窗口,横向步长取决于记录数据次数RecordSize,纵向步长取决于数据buffer中的最值

    int x_step_pixel = p->config.width / (p->config.recordSize-1);
    int x_step_eps   = p->config.width % (p->config.recordSize-1);
    if(x_step_pixel==0) x_step_pixel = 1;

    double y_step_pixel = __findMax_INT(p->buffer,p->config.dataNum*p->config.recordSize).value*1.3/p->config.height;
    
    for(size_t dataIndex=0;dataIndex<p->config.dataNum;dataIndex++){
        size_t cnt = 0;
        int    x   = p->config.x_pos     ,y = p->config.y_pos+p->config.height-1;
        do{
            int temp = y - (int)lround(*(p->buffer+dataIndex*p->config.recordSize+cnt)/y_step_pixel);
            __Graph_rect_raw( x                                       ,\
                                 temp ,\
                                 x + x_step_pixel + (x_step_eps > cnt)   ,\
                                 y    ,\
                                 p->config.data[dataIndex].dataColor     ,\
                                 &BufferInfo                             ,\
                                 __ApplyPixel_unzero );
            x += (x_step_pixel + (x_step_eps > cnt));
        }while(++cnt < p->config.recordSize-1);
    }

     //画图表框
    __Graph_line_raw( p->config.x_pos                    ,\
                  p->config.y_pos                    ,\
                  p->config.x_pos                    ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.backColor                ,\
                  &BufferInfo                        ,\
                  __ApplyPixel_fill);
    __Graph_line_raw( p->config.x_pos+p->config.width -1 ,\
                  p->config.y_pos                    ,\
                  p->config.x_pos+p->config.width -1 ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.backColor                ,\
                  &BufferInfo                        ,\
                  __ApplyPixel_fill );
    __Graph_line_raw( p->config.x_pos                    ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.x_pos+p->config.width -1 ,\
                  p->config.y_pos+p->config.height-1 ,\
                  p->config.backColor                ,\
                  &BufferInfo                        ,\
                  __ApplyPixel_fill );
}

struct __TraceWatchConfigChain* __searchTraceConfigChain(BYTE ID){
    __TraceWatchConfigChain* p = Screen.cfgTraceHeadNode;

    while(p != NULL){
        if(p->config.ID == ID)
            break;

        p = p->nextConfig;
    }

    return p;
}

void GUI_CreateTraceWatchSocket(struct GUI_TraceConfig_t* config){
    __TraceWatchConfigChain* pConfig    = Screen.cfgTraceHeadNode;
    __TraceWatchConfigChain* pTmpConfig = NULL;
 // ID should be unique.
    __exit( NULL != __searchTraceConfigChain(config->ID) );

    switch((int)(config->GUI_TRACE_xxxx)){
        case GUI_TRACE_FILL:
            break;
        case GUI_TRACE_LINEAR:
            pTmpConfig = (__TraceWatchConfigChain*)__malloc(sizeof(struct __TraceWatchConfigChain));
            pTmpConfig->buffer     = (int*)calloc(config->dataNum*config->recordSize,sizeof(int));
            pTmpConfig->insertFunc = __insert_trace_Linear;
            pTmpConfig->removeFunc = __remove_trace_Linear;
            break;
        case GUI_TRACE_COLUMN:
            pTmpConfig = (__TraceWatchConfigChain*)__malloc(sizeof(struct __TraceWatchConfigChain));
            pTmpConfig->buffer     = (int*)calloc(config->dataNum*config->recordSize,sizeof(int));
            pTmpConfig->insertFunc = __insert_trace_Column;
            pTmpConfig->removeFunc = __remove_trace_Column;
            break;
        case GUI_TRACE_SCATTER:
            break;
        default: break;
    }
    pTmpConfig->config     = *config;
    pTmpConfig->nextConfig = NULL;

    if(pConfig == NULL)
        Screen.cfgTraceHeadNode = pTmpConfig;
    else{
        do{
            if(pConfig->nextConfig == NULL){
                pConfig->nextConfig = pTmpConfig;
                break;
            }
            pConfig = pConfig->nextConfig;
        }while(1);
    }
}

void GUI_ChangeTraceWatchSocket(BYTE ID){

}

void GUI_RecordTrace(BYTE ID){
    __TraceWatchConfigChain* pNow = __searchTraceConfigChain(ID);

    __exit(pNow == NULL);
    for(size_t index=0;index < pNow->config.dataNum;index++){
        int* p = (pNow->buffer+(pNow->config.recordSize*index));
        memmove( p,(p+1),(pNow->config.recordSize-1)*sizeof(*p));
        *(p+pNow->config.recordSize-1) = *((pNow->config.data+index)->dataSource);
    }
}

void GUI_ShowTraceWatch(BYTE ID,size_t probe){
    __TraceWatchConfigChain* pNow = __searchTraceConfigChain(ID);

    __exit(pNow == NULL);

    (*(pNow->insertFunc))(pNow);

    // GUI_RecordTrace(ID);
    /* Buffer can be explained by this:

            |<----- recordSize ----->|
            |------------------------|  ---
            |                        |   ^
            |   * index              | dataNum
            |                        |   v
            |------------------------|  ---
    
    */
    for(size_t index=0;index < pNow->config.dataNum;index++){
        int* p = (pNow->buffer+(pNow->config.recordSize*index));
        memmove( p,(p+1),(pNow->config.recordSize-1)*sizeof(*p));
        *(p+pNow->config.recordSize-1) = *((pNow->config.data+index)->dataSource);
    }

    uint x_start = pNow->config.x_pos;
    uint y_start = pNow->config.y_pos;
    uint x_end   = pNow->config.x_pos + pNow->config.width  - 1;
    uint y_end   = pNow->config.y_pos + pNow->config.height - 1;

 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
    //...//
#else
    GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
}

void GUI_HideTraceWatch(BYTE ID){

}

void GUI_DeleteTraceWatchScoket(BYTE ID){

}

#endif
//=========================================== End of Trace Watch Function ==============================================//
//=========================================== End of Trace Watch Function ==============================================//
//=========================================== End of Trace Watch Function ==============================================//
//=================================================== Demo Function ====================================================//
//=================================================== Demo Function ====================================================//
//=================================================== Demo Function ====================================================//

#if GUI_DEMO

//Put the func into " While(1){ ... } "

inline void GUI_DEMO_MovingRect_1(void){
    const int radius   = 28;
    const int center_y = 32;
    const int center_x = 64;

    register float theater = 360.0;
    register unsigned int x,y;
    register unsigned int mov_x,mov_y;
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetPenSize(3);
    GUI_AutoDisplayMode();
    while(theater > 0){
        x     = center_x+radius*cos(theater);
        y     = center_y+radius*sin(theater);
        mov_x = center_x+0.4*radius*sin(theater);
        mov_y = center_y+0.4*radius*cos(theater);
        GUI_DrawRect(mov_x,mov_y,x,y);

        theater-=(float)0.1;
    }
}

inline void GUI_DEMO_MovingRect_2(void){
    GUI_SetPenSize(3);
    GUI_AutoDisplayMode();
    for(int x = 0;x < GUI_X_WIDTH;x++){
        GUI_ClearFrameBuffer();
        GUI_DrawRect(x,(GUI_Y_WIDTH-1)-(int)(x*(GUI_Y_WIDTH*1.0/GUI_X_WIDTH)),GUI_X_WIDTH>>1,GUI_Y_WIDTH>>1);
    }
    for(int x = 0;x < GUI_X_WIDTH;x++){
        GUI_ClearFrameBuffer();
        GUI_DrawRect(x,(int)(x*(GUI_Y_WIDTH*1.0/GUI_X_WIDTH))                ,GUI_X_WIDTH>>1,GUI_Y_WIDTH>>1);
    }
}
 #include <stdlib.h>
inline void GUI_DEMO_MovingRect_3(void){
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetPenSize(3);
    GUI_AutoDisplayMode();
    GUI_DrawRect(rand()%128,rand()%64,rand()%128,rand()%64);
    GUI_ClearFrameBuffer();
    unsigned long i = 0xffff;
    while(i--);
}

inline void GUI_DEMO_MovingEllipse_1(void){
    const int c = 20;
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetPenSize(3);
    for(int a=1;a<=64-c;a++){
        GUI_FillEllipse(64,32,64-a,c,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif
    }

    for(int b=32-c;b>=0;b--){
        GUI_FillEllipse(64,32,c,32-b,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (0,7,64-c,64+c);
#endif
    }

    for(int b=0;b<=32-c;b++){
        GUI_FillEllipse(64,32,c,32-b,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (0,7,64-c,64+c);
#endif
    }

    for(int a=64-c;a>0;a--){
        GUI_FillEllipse(64,32,64-a,c,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif
    }
}

inline void GUI_DEMO_MovingEllipse_2(void){
    const int c = 20;
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetPenSize(3);
    for(int a=1;a<=64-c;a++){
        GUI_DrawEllipse(64,32,64-a,c,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif
    }

    for(int b=32-c;b>=0;b--){
        GUI_DrawEllipse(64,32,c,32-b,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (0,7,64-c,64+c);
#endif
    }

    for(int b=0;b<=32-c;b++){
        GUI_DrawEllipse(64,32,c,32-b,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (0,7,64-c,64+c);
#endif
    }

    for(int a=64-c;a>0;a--){
        GUI_DrawEllipse(64,32,64-a,c,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif
    }
}

inline void GUI_DEMO_MovingWave_1(void){
    const int x_start = 0;
    const int x_end   = GUI_X_WIDTH-1;
    const int y_level = GUI_Y_WIDTH>>1;
    const int A       = (int)(y_level/1.5);
    GUI_SetPenSize(2);
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetBackColor(GUI_COLOR_BLACK);
    for(double w=0.0;w<1.5;w+=0.01){
        GUI_DrawWave(A,w,0.0,x_start,x_end,y_level,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
#endif
    }
    for(double w=1.5;w>0.0;w-=0.01){
        GUI_DrawWave(A,w,0.0,x_start,x_end,32,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
#endif
    }
}

inline void GUI_DEMO_MovingWave_2(void){
    const int x_start = 0;
    const int x_end   = GUI_X_WIDTH-1;
    const int y_level = GUI_Y_WIDTH>>1;
    const int A       = (int)(y_level/1.5);
    const float w     = 0.2;
    GUI_SetPenSize(1);
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetBackColor(GUI_COLOR_BLACK);
    
    for(int phi=0;phi<=31;phi++){
        GUI_DrawWave(A,w,phi,x_start,x_end,y_level,true,true);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
        GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
#endif
    }
}

inline void GUI_DEMO_Rotation_1(void){
    
    const unsigned int radius = (int)(((GUI_MIN(GUI_X_WIDTH,GUI_Y_WIDTH))>>2)-2);
    const unsigned int x      = GUI_X_WIDTH>>1;
    const unsigned int y      = GUI_Y_WIDTH>>1;
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetPenSize(3);
    GUI_ManualDisplayMode();
    for(double phi=0;phi<360;phi+=0.1){
        const float pi = 3.1415926;
        GUI_SetPenSize (3);

        GUI_ClearFrameBuffer();
        GUI_DrawCircle (x,y,radius);
        GUI_SetPenSize (1);
        GUI_DrawLine   (x,y,x-(radius-2)*cos(phi)       ,y-(radius-2)*sin(phi)         );
        GUI_DrawLine   (x,y,x-(radius-2)*cos(phi+2*pi/3) ,y-(radius-2)*sin(phi+2*pi/3) );
        GUI_DrawLine   (x,y,x-(radius-2)*cos(phi-2*pi/3) ,y-(radius-2)*sin(phi-2*pi/3) );
        GUI_SetPenSize (3);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN) && (GUI_COLOR_TYPE == GUI_1Bit)
        GUI_RefreashPageArea(0,7,64-30,64+30);
#else
        //...//
        // GUI_RefreashArea(x-radius-GUI_GetPenSize(),\
        //                  y-radius-GUI_GetPenSize(),\
        //                  x+radius+GUI_GetPenSize(),\
        //                  y+radius+GUI_GetPenSize());
        GUI_RefreashScreen();
#endif
    }
}

inline void GUI_DEMO_Pennis(void){
    GUI_AutoDisplayMode();
    GUI_SetPenColor(GUI_COLOR_WHITE);
    int x1 = 100,y1 = 30,x2 = 30,y2 = 90;
    GUI_FillCircle(x2-10,y2-10,20);
    GUI_FillCircle(x2+10,y2+10,20);
    for(int i=1;i<=20;i++){
        GUI_SetPenSize(i);
        GUI_DrawLine(x1,y1,x2,y2);
        GUI_RefreashScreen();
    }
}

inline void GUI_DEMO_Blink_1(void){
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetPenSize(3);
    GUI_ManualDisplayMode();
    for(int r=32;r>0;r--){
        GUI_FillCircle(64, 32, r);
 #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN) && (GUI_COLOR_TYPE == GUI_1Bit)
        GUI_RefreashPageArea(0,7,64-r-1,64+r+1);
        GUI_ClearPageArea(0,7,64-r-1,64+r+1,false,true);
#else
        GUI_RefreashScreen();
#endif
    }
}

inline void GUI_DEMO_Pattern_1(void){
    unsigned int penSize = GUI_GetPenSize();
    const int r = 20,ps = 3;
    GUI_SetPenColor(GUI_COLOR_WHITE);
    GUI_SetPenSize(ps);
    GUI_DrawRect(64-r-ps,32-r-ps,64+r+ps,32+r+ps);
    GUI_FillCircle(64,32,r);

    GUI_SetPenSize(penSize);
}

inline void GUI_DEMO_Microsoft_1(void){
    GUI_SetBackColor(GUI_COLOR_BLACK);
    GUI_SetPenSize(3);
    GUI_AutoDisplayMode();
    GUI_SetPenColor(GUI_COLOR_RED);
    GUI_DrawRect(24,24,64,64);
    GUI_SetPenColor(GUI_COLOR_GREEN);
    GUI_DrawRect(94,24,64,64);
    GUI_SetPenColor(GUI_COLOR_BLUE);
    GUI_DrawRect(24,94,64,64);
    GUI_SetPenColor(GUI_COLOR_YELLOW);
    GUI_DrawRect(94,94,64,64);
}

#endif

#if GUI_ANIMATION_DISPLAY
inline void GUI_DEMO_ANIM_ProgressBar(void){
    static bool initFlag = false;
    if(initFlag == false){
        struct GUI_AnimConfig_t config = {
            .GUI_ANIM_xxxx = GUI_ANIM_PROGRESSBAR_STD_LR,
            .themeColor    = GUI_COLOR_LIGHTGREEN,
            .ID            = 0x01,
            .x_pos         = 20,
            .y_pos         = 40,
            .height        = 15,
            .width         = 90,
            .text          = "Progress Bar",
        };
        GUI_CreateAnimationSocket(&config);

        config.themeColor = GUI_COLOR_LIGHTSLATEGRAY;
        config.ID         = 0x02;
        config.height     = 4;
        config.width      = 90;
        config.x_pos      = 20;
        config.y_pos      = 10;
        GUI_CreateAnimationSocket(&config);

        config.themeColor = GUI_COLOR_PALETURQUOISE;
        config.ID         = 0x03;
        config.height     = 5;
        config.width      = 70;
        config.x_pos      = 20;
        config.y_pos      = 24;
        GUI_CreateAnimationSocket(&config);

        config.themeColor = GUI_COLOR_RED;
        config.ID         = 0x04;
        config.height     = 11;
        config.width      = 90;
        config.x_pos      = 20;
        config.y_pos      = 60;
        GUI_CreateAnimationSocket(&config);
    }

    initFlag = true;

    int i = 0;
    while(i++ < 255){
        GUI_ShowAnimation(0x01,i);
        GUI_ShowAnimation(0x02,i);
        GUI_ShowAnimation(0x03,i);
        GUI_ShowAnimation(0x04,i);
    }
}

inline void GUI_DEMO_ANIM_SwitchSlider(void){
    struct GUI_AnimConfig_t config = {
        .text          = "Nicole is fattttttt pig."    ,
        .GUI_ANIM_xxxx = GUI_ANIM_SLIDESWITCH ,
        .ID            = 0x03 ,
        .x_pos         = 20   ,
        .y_pos         = 30   ,
        .height        = 20   ,
        .width         = 35   ,
        .themeColor    = GUI_COLOR_GREEN,
        .backColor     = GUI_COLOR_RED
    };

    GUI_CreateAnimationSocket(&config);

    config.ID    =  0x01;
    config.y_pos += config.height + 5;
    config.themeColor = GUI_COLOR_YELLOW;
    GUI_CreateAnimationSocket(&config);

    config.ID    =  0x02;
    config.y_pos += config.height + 5;
    config.themeColor = GUI_COLOR_RED;
    GUI_CreateAnimationSocket(&config);

    config.ID    =  0x04;
    config.x_pos += config.width + 5;
    config.themeColor = GUI_COLOR_BLUE;
    GUI_CreateAnimationSocket(&config);

    config.ID    =  0x05;
    config.y_pos -= config.height + 5;
    config.themeColor = GUI_COLOR_CYAN;
    GUI_CreateAnimationSocket(&config);

    config.ID    =  0x06;
    config.y_pos -= config.height + 5;
    config.themeColor = GUI_COLOR_MAGENTA;
    GUI_CreateAnimationSocket(&config);
    while(1){
        int i = 0;
        while(i<255){
            GUI_ShowAnimation(0x01,i);
            GUI_ShowAnimation(0x02,i);
            GUI_ShowAnimation(0x03,i);
            GUI_ShowAnimation(0x04,i);
            GUI_ShowAnimation(0x05,i);
            GUI_ShowAnimation(0x06,i);
            i+=10;
            (*GUI_API_DelayMs)(3);
        }
        i=255;
        while(i>0){
            GUI_ShowAnimation(0x01,i);
            GUI_ShowAnimation(0x02,i);
            GUI_ShowAnimation(0x03,i);
            GUI_ShowAnimation(0x04,i);
            GUI_ShowAnimation(0x05,i);
            GUI_ShowAnimation(0x06,i);
            i-=10;
            (*GUI_API_DelayMs)(3);
        }
    }
}
#endif
//================================================ End of Demo Function ================================================//
//================================================ End of Demo Function ================================================//
//================================================ End of Demo Function ================================================//


#if 0

void GUI_Debug(void){

}

#endif



//===================================================== End of File ====================================================//
//===================================================== End of File ====================================================//
//===================================================== End of File ====================================================//


