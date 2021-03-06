#include "GLU_image.h"
#include "BLK_image.h"
#include "BLK_graphic.h"


#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH

extern BLK_TYPE(Canvas) info_MainScreen; //...//



void GLU_FUNC( Image, profile )( GLU_ENUM(ImageStyle) style, const GLU_TYPE(Pixel)* colors, uint8_t size, const GLU_SRCT(Text)* text, uint8_t alpha_100 ){
    
    RH_ASSERT(colors);
    RH_ASSERT(size);
    
    switch( style ){
        default:
            break;
        case kGLU_ImageStyle_aurora:{
            #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                BLK_FUNC( ImgBin, draw_img_aurora )( &info_MainScreen, colors, size );
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                BLK_FUNC( Img565, draw_img_aurora )( &info_MainScreen, colors, size );
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                BLK_FUNC( Img888, draw_img_aurora )( &info_MainScreen, colors, size );
            #else
                 //...//
            #endif
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
                            .height  = pF->img_h,
                            .width   = pF->img_w,
                            .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
                        };
                        size_t w,h;
                        GLU_FUNC(Font, get_str_ImgInfo)(&w, &h, text->str);
                        
                        int fs_x = RH_LIMIT( ((int)(info_MainScreen.width  - w)>>1), 0, GUI_X_WIDTH-1);;
                        int fs_y = RH_LIMIT( ((int)(info_MainScreen.height - h)>>1), 0, GUI_Y_WIDTH-1);
                        
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
            break;
        }
    }

}


