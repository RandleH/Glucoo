

    
#include <stdio.h>
#include "RH_common.h"
#include "./RH_config.h"

#include "./GLU_api.h"
#include "GLU_glucoo.h"

#include "BLK_image.h"

#ifdef __cplusplcus
extern "C"{
#endif
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
static BLK_SRCT(ImgBin)* pTmpScreenShot = NULL;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
static BLK_SRCT(Img565)* pTmpScreenShot = NULL;
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
static BLK_SRCT(Img888)* pTmpScreenShot = NULL;
#else
  #error "[RH_gui_api]: Unknown color type."
#endif


char* dst_path = NULL;
    
static void Simul_API_DrawArea(var x1,var y1,var x2,var y2,const GLU_TYPE(Pixel)* pixData){

    if( pTmpScreenShot == NULL ){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        pTmpScreenShot = BLK_FUNC( ImgBin, create )( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        pTmpScreenShot = BLK_FUNC( Img565, create )( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        pTmpScreenShot = BLK_FUNC( Img888, create )( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    }

#ifdef RH_DEBUG
    RH_ASSERT( x1<(var)RH_CFG_SCREEN_WIDTH && x1>=0 );
    RH_ASSERT( x2<(var)RH_CFG_SCREEN_WIDTH && x2>=0 );
    RH_ASSERT( y1<(var)RH_CFG_SCREEN_HEIGHT && y1>=0 );
    RH_ASSERT( y2<(var)RH_CFG_SCREEN_HEIGHT && y2>=0 );
#endif
    
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    const var xs = RH_MIN(x1, x2);
    const var xe = RH_MAX(x1, x2);
    const var ps = ((RH_MIN(y1, y2))>>3);
    const var pe = ((RH_MAX(y1, y2))>>3);
    for ( var p=ps; p<=pe; p++ ) {
        memcpy(&pTmpScreenShot->pBuffer[ p*RH_CFG_SCREEN_WIDTH + xs ].data, pixData, (xe-xs+1));
        pixData += (xe-xs+1);
    }
        
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    const var width   = __abs(x2 - x1) + 1;
    const var height  = __abs(y2 - y1) + 1;
    for(var y=0;y<height;y++){
        for(var x=0;x<width;x++){
            pTmpScreenShot->ptr[(y1+y)*RH_CFG_SCREEN_WIDTH + (x1+x)].data = pixData[ y*width+x];
        }
    }
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    BLK_FUNC( ImgBin, out_bmp )(dst_path, pTmpScreenShot);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    BLK_FUNC( Img565, out_bmp )(dst_path,pTmpScreenShot);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    BLK_FUNC( Img888, out_bmp )(dst_path,pTmpScreenShot);
    RH_MESSAGE("export: %s size=%ld byte\n",dst_path, (long)pTmpScreenShot->h*pTmpScreenShot->w);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
    char cmd[255] = {0};
    sprintf(cmd, "open %s",dst_path);
    system(cmd);
}
    
static void Simul_API_DrawPixel(var x ,var y ,const GLU_TYPE(Pixel) pixData){
    RH_ASSERT( pTmpScreenShot );

    pTmpScreenShot->ptr[(y)*RH_CFG_SCREEN_WIDTH + (x)].data = pixData;
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        while(1);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        while(1);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    BLK_FUNC( Img888, out_bmp )(dst_path,pTmpScreenShot);
#else
  #error "[RH_gui_api]: Unknown color type."
#endif
}

static void Simul_API_AssertParam(bool expr,const char* WHAT_IS_WRONG){
    UNUSED(expr);
    printf("%s\n",WHAT_IS_WRONG);
}

void GLU_FUNC( API, init )(void){
    char temp[] = {'/','S','I','M','_','m','a','c','O','S','/','o','u','t','p','u','t','/','s','n','a','p','s','h','o','t','.','b','m','p','\0' };
    
    dst_path = RH_MALLOC(sizeof(temp)+strlen(RH_DIR_PRJ)-1);
    
    sprintf( dst_path, "%s%s", RH_DIR_PRJ, temp);
    
    GLU_API_DrawArea     = Simul_API_DrawArea;
    GLU_API_AssertParam  = Simul_API_AssertParam;
    GLU_API_DrawPixel    = Simul_API_DrawPixel;
}


#ifdef __cplusplcus
}
#endif



