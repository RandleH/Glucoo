#include "GLU_glucoo.h"
#include "BLK_data.h"
#include "BLK_graphic.h"

#if ( RH_CFG_SCREEN_HEIGHT < 16 )
  #warning "Screen height may be too small."
#endif

#if ( RH_CFG_SCREEN_WIDTH < 16 )
  #warning "Screen width may be too small."
#endif

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH

/*===============================================================================================================
 * 定义对外API函数指针, 合计4个
 * [ GUI_API_DrawArea    ] 给定区域, 以及该片区域的显存数据(内存重组对齐), 绘制在屏幕上
 * [ GUI_API_DrawPixel   ] 给定一个像素点, 在屏幕上绘制一个像素点
 * [ GUI_API_AssertParam ] 断言输出
 * [ GUI_API_DelayMs     ] (未使用)
===============================================================================================================*/
void RH_WEAK GUI_DrawArea       (int x1,int y1,int x2,int y2,const __Pixel_t* pixData){
// THIS MAY COST SOME TIME.
}
void (*GUI_API_DrawArea)                      (int x1,int y1,int x2,int y2,const __Pixel_t* pixData) = GUI_DrawArea;

void RH_WEAK GUI_DummyDrawPixel (int x,int y,const __Pixel_t pixData){
// IF U DONT GIVE ME A PEN, HOW CAN I DRAW !?
}
void (*GUI_API_DrawPixel)                     (int x ,int y ,const __Pixel_t pixData)          = GUI_DummyDrawPixel;

void RH_WEAK GUI_AsserParam     (bool expression,const char* WHAT_IS_WRONG){
// DONT KEEP MY MOTH SHUT, I GOT A PROBLEM TO REPORT.
}
void (*GUI_API_AssertParam)                   (bool expression,const char* WHAT_IS_WRONG)      = GUI_AsserParam;

void RH_WEAK GUI_Delay          (unsigned long ms){
    ms*=1000;
    while(ms--){}
}
void (*GUI_API_DelayMs)                       (unsigned long ms)                               = GUI_Delay;

#define M_SCREEN_MAIN   0
#define M_SCREEN_CNT    1


typedef BLK_SRCT(Stack)    __LINK_AreaRefreash;
typedef BLK_SRCT(LinkLoop) __LINK_WindowCFG;


/*===============================================================================================================
 * 根据配置的显存存放方式 RH_CFG_GRAM_TYPE 分配显存空间
 * [ RH_CFG_GRAM_INTERNAL] 如果配置为内置显存, 则根据颜色深度建立本地显存数组, 并将该数组首地址录入显存信息结构体 .GRAM
 * [ RH_CFG_GRAM_EXTADDR ] 如果配置为外置显存地址, 即给定内存绝对地址, ...
 * [ RH_CFG_GRAM_EXTSECT ] 如果配置为外置显存段, 即给定内存的分配段, ...
 * [ RH_CFG_GRAM_EXTPTR  ] 如果配置为外置显存指针, 即给定一个指针变量, 则直接将该指针录入显存信息结构体成员 .GRAM
===============================================================================================================*/
#pragma pack(1)
#if   ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )

    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        static __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH>>3 ][ GUI_X_WIDTH ];
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        static __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH ][ GUI_X_WIDTH ];
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        static __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH ][ GUI_X_WIDTH ];
    #endif
#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTADDR  )
    
#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTSECT  )

#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTPTR   )

#endif

/*===============================================================================================================
 * 配置显存信息结构体 Screen
 * .GRAM                     显存数据首地址, 由配置的颜色深度和屏幕大小决定其属性
 * .areaNeedRefreashHead     待刷新的区域信息链表头
 * .areaNeedRefreashPixelCnt 待刷新的像素点总数
===============================================================================================================*/
#pragma pack(1)
static struct{
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    __PixelUnit_t    (*GRAM)[GUI_Y_WIDTH>>3][GUI_X_WIDTH];
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    __PixelUnit_t    (*GRAM)[GUI_Y_WIDTH   ][GUI_X_WIDTH];
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    __PixelUnit_t    (*GRAM)[GUI_Y_WIDTH   ][GUI_X_WIDTH];
#endif
    size_t           allocated_byte;

    bool             autoDisplay;

    __LINK_AreaRefreash*     areaNeedRefreashHead;
    size_t                   areaNeedRefreashCnt;
    size_t                   areaNeedRefreashPixelCnt;
    
    __LINK_WindowCFG*        windowCFG;

}Screen;

__GraphInfo_t info_MainScreen = { //...//
    .height = GUI_Y_WIDTH ,
    .width  = GUI_X_WIDTH ,
};

void RH_PREMAIN GUI_Init        ( void ){
#if   ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    Screen.GRAM = GRAM;
#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTADDR  )
    
#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTSECT  )

#elif ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_EXTPTR   )
    Screen.GRAM = (__PixelUnit_t (*)[GUI_Y_WIDTH][GUI_X_WIDTH])RH_CFG_GRAM_POINTER;
#endif
    
    info_MainScreen.pBuffer = Screen.GRAM[M_SCREEN_MAIN][0];
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        memset( Screen.GRAM , 0, M_SCREEN_CNT*(GUI_Y_WIDTH>>3)*GUI_X_WIDTH*sizeof(__Pixel_t) );
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        memset( Screen.GRAM , 0, M_SCREEN_CNT*GUI_Y_WIDTH*GUI_X_WIDTH*sizeof(__Pixel_t) );
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        memset( Screen.GRAM , 0, M_SCREEN_CNT*GUI_Y_WIDTH*GUI_X_WIDTH*sizeof(__Pixel_t) );
    #endif

    Screen.autoDisplay = false;

    Screen.allocated_byte = 0;
    Screen.areaNeedRefreashHead = BLK_FUNC( Stack, createBase )( NULL );
    Screen.areaNeedRefreashCnt      = 0;
    Screen.areaNeedRefreashPixelCnt = 0;

    Screen.windowCFG = NULL;

    BLK_FUNC( Graph, init )();
    __Font_init();
}


/*===============================================================================================================
 * GUI_RefreashScreenArea
 ================================================================================================================
 * 此函数将会调用显示屏API, 并立即在显示屏上显示图像.
 *
 * 以下情况,当API中支持区域刷新即 GUI_API_DrawArea不为NULL时:
 * 如果配置为内置显存, 那么图像数据将创建该区域的动态缓存,并从内置的 Screen.GRAM 中拷贝到其中(字节宽度对齐),刷新
   屏幕后释放动态缓存.
 * 如果配置为外置显存, 进死循环,暂未开发.
 *
 * 以下情况,当API不支持区域刷新, 仅有单个画点函数时即 GUI_API_DrawPixel :
 * 如果配置为内置显存, 那么图像数据将直接从 Screen.GRAM 逐一画点.
 * 如果配置为外置显存, 进死循环,暂未开发.
===============================================================================================================*/
void GUI_RefreashScreenArea     ( int xs, int ys, int xe, int ye ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    // 内置显存需要向外导出数据
    if(GUI_API_DrawArea != NULL){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        const int x_width = xe-xs+1;
        const int ps      = ys>>3;
        const int pe      = ye>>3;
        const int p_width = (pe-ps+1);
        __Pixel_t* p = (__Pixel_t*)RH_MALLOC((x_width)*(p_width)*sizeof(__Pixel_t));
        
       (*GUI_API_DrawArea)( xs , ys , xe , ye ,
                           BLK_FUNC( Memory, grbArea )(p, Screen.GRAM[M_SCREEN_MAIN][0] ,\
                                             sizeof(__Pixel_t)             ,\
                                             GUI_X_WIDTH                   ,\
                                             xs, ps, xe, pe                ) );

#else
        const int x_width = xe-xs+1;
        const int y_width = ye-ys+1;
        __Pixel_t* p = (__Pixel_t*)RH_MALLOC((x_width)*(y_width)*sizeof(__Pixel_t));
        (*GUI_API_DrawArea)( xs , ys , xe , ye ,
                            BLK_FUNC( Memory, grbArea )(p, Screen.GRAM[M_SCREEN_MAIN][0] ,\
                                              sizeof(__Pixel_t)             ,\
                                              GUI_X_WIDTH                   ,\
                                              xs, ys, xe, ye                ) );
#endif
        RH_FREE(p);
    }
    else{
        
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*GUI_API_DrawPixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y>>3][x].data);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        RH_ASSERT(false);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*GUI_API_DrawPixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y][x].data);
#endif
    }
    
#else
    // 如果配置为外置显存, 则无需软件控制显示屏

#endif
}

/*==============================================================================================================
 * GUI_RefreashScreen
 ===============================================================================================================
 * 此函数将会根据缓存情况进行屏幕刷新.
 *
 * Screen.areaNeedRefreashHead 是用于记载屏幕待刷新区域的链表表头, 表头本身不存储数据, 有效数据从下一节点开始.
   该链表表头于 GUI_Init 中被初始化. 该链表为栈链表, 类型为 <BLK_SRCT(Stack)>.
   GUI_RefreashScreenArea并且完成后将会释放其中的缓存图像数据及结构体自身.
 * 如果配置为内置显存, 那么将会判断屏幕总体待刷新像素点是否超过了屏幕像素总和, 如果超过了, 则释放所有链表节点,并刷新
   全屏幕,没有超过则将链表节点中数据即 <__Area_t> 结构体指针传入给 GUI_RefreashScreenArea, 由于内置显存, 因此
   <__Area_t>结构体指针不会有图像数据.
 * 如果配置为外置显存, 进死循环,暂未开发.
===============================================================================================================*/
void GUI_RefreashScreen         ( void ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    __exit( Screen.areaNeedRefreashHead == NULL );
    __Area_t *p = NULL;
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        GUI_RefreashScreenArea( 0, 0, GUI_X_WIDTH-1, GUI_Y_WIDTH-1 );
        while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
            p = BLK_FUNC( Stack, pop )( Screen.areaNeedRefreashHead );
            RH_FREE(p);
        }
    }else{
        while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
            p = BLK_FUNC( Stack, pop )( Screen.areaNeedRefreashHead );
            GUI_RefreashScreenArea( (int)(p->xs)             ,\
                                    (int)(p->ys)             ,\
                                    (int)(p->xs+p->width-1)  ,\
                                    (int)(p->ys+p->height-1) );
            RH_FREE(p);
        }
    }
    Screen.areaNeedRefreashPixelCnt = 0;
#endif
}

void GUI_AddScreenArea          ( int xs, int ys, int xe, int ye ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        __Area_t *p = NULL;
        while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
            p = BLK_FUNC( Stack, pop )( Screen.areaNeedRefreashHead );
            RH_FREE(p);
        }
        return;
    }
    
    __Area_t* pArea = (__Area_t*)RH_MALLOC( sizeof(__Area_t) );
    pArea->xs      = xs;
    pArea->ys      = ys;
    pArea->width   = xe-xs+1;
    pArea->height  = ye-ys+1;
    Screen.areaNeedRefreashPixelCnt += pArea->width*pArea->height;
    BLK_FUNC( Stack, push )( Screen.areaNeedRefreashHead, (void*)pArea );
#endif
}

/*==============================================================================================================
 * GUI_RefreashEntireScreen
 ===============================================================================================================
 * 此函数将会刷新整屏.
 *
 * 此函数不会查看待刷新区域 Screen.areaNeedRefreashHead 的缓存情况, 直接清空链表, 并将显存内容全部刷新.
 * 如果配置为内置显存, 那么将会把Screen中的显存全部刷新, 无论是否有待刷新区域, 都会执行整屏刷新.
 * 如果配置为外置显存, 进死循环,暂未开发.
===============================================================================================================*/
void GUI_RefreashEntireScreen   ( void ){
#if( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    __Area_t *p = NULL;
    (*GUI_API_DrawArea)( 0, 0, GUI_X_WIDTH-1, GUI_Y_WIDTH-1, (__Pixel_t*)Screen.GRAM[M_SCREEN_MAIN][0] );
    while( !BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) ){
        p = BLK_FUNC( Stack, pop   )( Screen.areaNeedRefreashHead );
        RH_FREE(p);
    }
#endif
}

void GUI_set_penSize            ( size_t    penSize  ){
    BLK_FUNC( Graph, set_penSize ) ( penSize );
}

void GUI_set_penColor           ( __Pixel_t penColor ){
    BLK_FUNC( Graph, set_penColor )(penColor);
}

void GUI_auto_display           ( bool      cmd      ){
    if( cmd ){
        GUI_RefreashScreen();
#ifdef RH_DEBUG
        RH_ASSERT( Screen.areaNeedRefreashCnt      == 0 );
        RH_ASSERT( Screen.areaNeedRefreashPixelCnt == 0 );
        RH_ASSERT( BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead ) );
#endif
    }
    Screen.autoDisplay = cmd;
}

inline bool GUI_is_AutoDisplay  ( void ){
    return (bool)(Screen.autoDisplay==true);
}

inline bool GUI_is_InternalGRAM ( void ){
#if ( RH_CFG_GRAM_TYPE == RH_CFG_GRAM_INTERNAL )
    return true;
#else
    return false;
#endif
}

inline bool GUI_is_CacheIdle    ( void ){
    return BLK_FUNC( Stack, empty )( Screen.areaNeedRefreashHead );
}
