

    
#include <stdio.h>
#include "RH_image.h"


#include "RH_common.h"

#include "RH_gui_api.h"
#include "GLU_glucoo.h"

#ifdef __cplusplcus
extern "C"{
#endif
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
static __ImageBIN_t*    pTmpScreenShot = NULL;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
static __ImageRGB565_t* pTmpScreenShot = NULL;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
static __ImageRGB888_t* pTmpScreenShot = NULL;
#else
  #error "[RH_gui_api]: Unknown color type."
#endif

#if defined __WIN32
const char* dst_path = "C:/Users/asus/Desktop/screen.bmp";
#elif defined  (__APPLE__)
const char* dst_path = "/Users/randle_h/desktop/screen.bmp";
#endif

static void Simul_API_DrawArea(int x1,int y1,int x2,int y2,const __Pixel_t* pixData){

    if( pTmpScreenShot == NULL ){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        pTmpScreenShot = __ImgBIN_create( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        pTmpScreenShot = __ImgRGB565_create( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        pTmpScreenShot = __ImgRGB888_create( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    }

#ifdef RH_DEBUG
    RH_ASSERT( x1<RH_CFG_SCREEN_WIDTH && x1>=0 );
    RH_ASSERT( x2<RH_CFG_SCREEN_WIDTH && x2>=0 );
    RH_ASSERT( y1<RH_CFG_SCREEN_HEIGHT && y1>=0 );
    RH_ASSERT( y2<RH_CFG_SCREEN_HEIGHT && y2>=0 );
#endif
    
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    const int xs = __min(x1, x2);
    const int xe = __max(x1, x2);
    const int ps = ((__min(y1, y2))>>3);
    const int pe = ((__max(y1, y2))>>3);
    for ( int p=ps; p<=pe; p++ ) {
        memcpy(&pTmpScreenShot->pBuffer[ p*RH_CFG_SCREEN_WIDTH + xs ].data, pixData, (xe-xs+1));
        pixData += (xe-xs+1);
    }
        
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    const size_t width   = __abs(x2 - x1) + 1;
    const size_t height  = __abs(y2 - y1) + 1;
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            pTmpScreenShot->pBuffer[(y1+y)*RH_CFG_SCREEN_WIDTH + (x1+x)].data = pixData[ y*width+x];
        }
    }
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    __ImgBIN_out_bmp(dst_path, pTmpScreenShot);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    __ImgRGB565_out_bmp(dst_path,pTmpScreenShot);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    __ImgRGB888_out_bmp(dst_path,pTmpScreenShot);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    
}
    
static void Simul_API_DrawPixel(int x ,int y ,const __Pixel_t pixData){
    if( pTmpScreenShot == NULL ){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        while(1);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        while(1);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        pTmpScreenShot = __ImgRGB888_create(RH_CFG_SCREEN_WIDTH,RH_CFG_SCREEN_HEIGHT);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    }
    pTmpScreenShot->pBuffer[(y)*RH_CFG_SCREEN_WIDTH + (x)].data = pixData;
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        while(1);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        while(1);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    __ImgRGB888_out_bmp(dst_path,pTmpScreenShot);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
}

static void Simul_API_AssertParam(bool expression,const char* WHAT_IS_WRONG){
    printf("%s\n",WHAT_IS_WRONG);
}

void Simul_API_Init(void){
    GUI_API_DrawArea     = Simul_API_DrawArea;
    GUI_API_AssertParam  = Simul_API_AssertParam;
    GUI_API_DrawPixel    = Simul_API_DrawPixel;
}


#ifdef __cplusplcus
}
#endif



