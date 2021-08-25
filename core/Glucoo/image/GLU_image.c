#include "GLU_image.h"
#include "BLK_image.h"
#include "BLK_graphic.h"


#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH

extern BLK_TYPE(Canvas) info_MainScreen; //...//
extern void GLU_FUNC( GUI, refreashScreenArea    )   ( var xs,var ys,var xe,var ye );
extern void GLU_FUNC( GUI, addScreenArea         )   ( var xs,var ys,var xe,var ye );
extern void GLU_FUNC( GUI, EX_refreashScreenArea )   ( const __Area_t* area );
extern void GLU_FUNC( GUI, EX_addScreenArea      )   ( const __Area_t* area );

static void __draw_aurora( const GLU_TYPE(Color)* colors, uint8_t size ){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_TYPE(Pixel)* colors_1Bit = alloca(sizeof(GLU_TYPE(Pixel))*size);
    for( uint8_t i=0; i<size; i++){
        colors_1Bit[i] = COLOR_1BIT(colors[i]);
    }
    BLK_FUNC( ImgBin, draw_img_aurora )( &info_MainScreen, colors_1Bit, size );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_TYPE(Pixel)* colors_16Bit = alloca(sizeof(GLU_TYPE(Pixel))*size);
    for( uint8_t i=0; i<size; i++){
        colors_16Bit[i] = COLOR_16BIT(colors[i]);
    }
    BLK_FUNC( Img565, draw_img_aurora )( &info_MainScreen, colors_16Bit, size );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    BLK_FUNC( Img888, draw_img_aurora )( &info_MainScreen, colors, size );
#else
    
#endif
}

static void __draw_blur( const GLU_TYPE(Color)* colors, uint8_t size ){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_TYPE(Pixel)* colors_1Bit = alloca(sizeof(GLU_TYPE(Pixel))*size);
    for( uint8_t i=0; i<size; i++){
        colors_1Bit[i] = COLOR_1BIT(colors[i]);
    }
    BLK_FUNC( ImgBin, draw_img_blur )( &info_MainScreen, colors_1Bit, size );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_TYPE(Pixel)* colors_16Bit = alloca(sizeof(GLU_TYPE(Pixel))*size);
    for( uint8_t i=0; i<size; i++){
        colors_16Bit[i] = COLOR_16BIT(colors[i]);
    }
    BLK_FUNC( Img565, draw_img_blur )( &info_MainScreen, colors_16Bit, size );
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    BLK_FUNC( Img888, draw_img_blur )( &info_MainScreen, colors, size );
#else
    
#endif
}

void GLU_FUNC( Image, profile )( GLU_ENUM(ImageStyle) style, const GLU_TYPE(Color)* colors, uint8_t size, const GLU_SRCT(Text)* text, uint8_t alpha_100 ){
    
    RH_ASSERT(colors);
    RH_ASSERT(size);
    
    switch( style ){
        default:
            break;
        case kGLU_ImageStyle_aurora:{
            __draw_aurora( colors, size );
            break;
        }
        case kGLU_ImageStyle_blur:{
            __draw_blur( colors, size );
            break;
        }
    }
    
    
    if( text!=NULL && text->str!=NULL ){
        GLU_FUNC( Font, backupCache )();
        GLU_FUNC( Font, set_font )( text->font );
        GLU_FUNC( Font, set_size )( text->size );
        
        switch( text->align ){
            case kGLU_Align_Left:
                break;
            case kGLU_Align_Middle:{
                GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )( text->str );
                
                // 引用灰度字体图像(类型信息复制转换)
                BLK_SRCT(ImgGry) img_font = {
                    .h   = pF->img_h,
                    .w   = pF->img_w,
                    .ptr = (BLK_UION(PixelGry)*)pF->img_buf
                };
                var w,h;
                GLU_FUNC(Font, get_str_ImgInfo)(&w, &h, text->str);
                
                var fs_x = RH_LIMIT( ((info_MainScreen.w - w)>>1), 0, GUI_X_WIDTH-1);
                var fs_y = RH_LIMIT( ((info_MainScreen.h - h)>>1), 0, GUI_Y_WIDTH-1);
                
            #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, fs_x, fs_y, text->color, alpha_100 );
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, fs_x, fs_y, text->color, alpha_100 );
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, fs_x, fs_y, text->color, alpha_100 );
            #else
                 
            #endif
                break;
            }
            case kGLU_Align_Right:
                break;
            case kGLU_Align_Justify:
                break;
        }
        GLU_FUNC( Font , restoreCache )();
    }

    GLU_FUNC( GUI, isAutoDisplay ) ? GLU_FUNC( GUI, refreashScreen )():GLU_FUNC( GUI, addScreenArea )(0,0,RH_CFG_SCREEN_WIDTH-1,RH_CFG_SCREEN_HEIGHT-1);

}


