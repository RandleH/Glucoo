

    
#include <stdio.h>
#include "RH_image.h"
#include "RH_gui.h"
#include "RH_gui_api.h"

#ifdef __cplusplcus
extern "C"{
#endif

#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
static __ImageBIN_t*    pTmpScreenShot = NULL;
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )
static __ImageRGB565_t* pTmpScreenShot = NULL;
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
static __ImageRGB888_t* pTmpScreenShot = NULL;
#else
  #error "[RH_gui_api]: Unknown color type."
#endif

#if defined __WIN32
const char* dst_path = "D:/Personal/Desktop/screen.bmp";
#elif defined  (__APPLE__)
const char* dst_path = "/Users/randle_h/desktop/screen.bmp";
#endif

static void Simul_API_DrawArea(int x1,int y1,int x2,int y2,const __Pixel_t* pixData){

    if( pTmpScreenShot == NULL ){
#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
        pTmpScreenShot = __ImgBIN_create(GUI_X_WIDTH,GUI_Y_WIDTH);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )
        while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
        pTmpScreenShot = __ImgRGB888_create(GUI_X_WIDTH,GUI_Y_WIDTH);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    }
        
    const size_t width   = __abs(x2 - x1) + 1;
    const size_t height  = __abs(y2 - y1) + 1;
    
#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
    while(1)
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 ) || ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            pTmpScreenShot->pBuffer[(y1+y)*GUI_X_WIDTH + (x1+x)].data = pixData[ y*width+x];
        }
    }
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    
    
#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
    __ImgBIN_out_bmp(dst_path, pTmpScreenShot);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )
    __ImgRGB565_out_bmp(dst_path,pTmpScreenShot);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
    __ImgRGB888_out_bmp(dst_path,pTmpScreenShot);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    
}
    
static void Simul_API_DrawPixel(int x ,int y ,const __Pixel_t pixData){
    if( pTmpScreenShot == NULL ){
#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
        while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )
        while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
        pTmpScreenShot = __ImgRGB888_create(GUI_X_WIDTH,GUI_Y_WIDTH);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    }
    pTmpScreenShot->pBuffer[(y)*GUI_X_WIDTH + (x)].data = pixData;
#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
        while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )
        while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
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



