

#include "RH_common.h"
#include "RH_config.h"
#include "GLU_pixel.h"

#ifdef __cplusplcus
extern "C"{
#endif

/*=======================================================================
 * The following code is only for demonstration.
 * You can wirte your own api starting from < GLU_api_template.c >.
 * Please remove the "_template" first.
 * All you need to do is to complete the "// ... //".
========================================================================*/
GLU_SRCT(Canvas)* canvas = NULL;

GLU_API void GLU_API_draw_area( var x1, var y1, var x2, var y2, const GLU_TYPE(Pixel)* pixData ){
    RH_ASSERT( x1<(var)RH_CFG_SCREEN_WIDTH  && x1>=0 );
    RH_ASSERT( x2<(var)RH_CFG_SCREEN_WIDTH  && x2>=0 );
    RH_ASSERT( y1<(var)RH_CFG_SCREEN_HEIGHT && y1>=0 );
    RH_ASSERT( y2<(var)RH_CFG_SCREEN_HEIGHT && y2>=0 );
    RH_ASSERT( canvas );
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    const var xs = RH_MIN(x1, x2);
    const var xe = RH_MAX(x1, x2);
    const var ps = ((RH_MIN(y1, y2))>>3);
    const var pe = ((RH_MAX(y1, y2))>>3);
    for ( var p=ps; p<=pe; p++ ) {
        memcpy(&canvas->pBuffer[ p*RH_CFG_SCREEN_WIDTH + xs ].data, pixData, (xe-xs+1));
        pixData += (xe-xs+1);
    }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    const var width   = __abs(x2 - x1) + 1;
    const var height  = __abs(y2 - y1) + 1;
    for(var y=0;y<height;y++){
        for(var x=0;x<width;x++){
            canvas->ptr[(y1+y)*RH_CFG_SCREEN_WIDTH + (x1+x)].data = pixData[ y*width+x];
        }
    }
  
#else
  #error "Unknown color depth."
#endif
    
}
    
GLU_API void GLU_API_draw_pixel( var x, var y, const GLU_TYPE(Pixel) pixData ){
    canvas->ptr[(y)*RH_CFG_SCREEN_WIDTH + (x)].data = pixData;
}
    
GLU_API void GLU_API_user_init( void ){
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    canvas = BLK_FUNC( ImgBin, create )( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    canvas = BLK_FUNC( Img565, create )( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    canvas = BLK_FUNC( Img888, create )( RH_CFG_SCREEN_WIDTH, RH_CFG_SCREEN_HEIGHT );
#else
#  error "Unknown color depth."
#endif
    
}
    
GLU_API void GLU_API_user_disp( void ){
    char path[255] = {0};
    const char* name = "snapshot";
    sprintf( path, "%s/%s.bmp", RH_DIR, name );
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    BLK_ImgBin_out_bmp( path, canvas);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    BLK_Img565_out_bmp( path, canvas );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    BLK_Img888_out_bmp( path, canvas );
#endif
    
    printf("Export bmp image: %s; size=%ld\n", path, (size_t)canvas->h*canvas->w);
    
}


#ifdef __cplusplcus
}
#endif



