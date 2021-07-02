//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/4/7.
//

#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "RH_color.h"

#include "GLU_api.h"
#include "BLK_data.h"


#include "GLU_glucoo.h"

#include "BLK_image.h"
#include "BLK_time.h"

#define DICE_NUM_MAX      6
#define DICE_NUM_MIN      1

#define PROJ_MIN(a,b)                           (((a)<(b))?(a):(b))

#define PROJ_MAX(a,b)                           (((a)>(b))?(a):(b))

size_t
GLU_FUNC( Font, out_ttf_array )( const char* ttf_path, const char* dst );

int main(int argc, const char * argv[]) {

    Simul_API_Init();

    GLU_FUNC( GUI, init        )();
    GLU_FUNC( GUI, setPenSize  )(5);
    GLU_FUNC( GUI, setPenColor )(M_COLOR_WHITE);
    
#if 1
    BLK_SRCT(Img888)* IMG = BLK_FUNC( Img888, create )( 320, 200 );
    
    BLK_TYPE(Pixel888) colors[5] = {
        MAKE_COLOR(255,  0,  0) ,\
        MAKE_COLOR(255,255,  0) ,\
        MAKE_COLOR(  0,255,  0) ,\
        MAKE_COLOR(  0,255,255) ,\
        MAKE_COLOR(  0,  0,255) ,\
    };
    
    BLK_FUNC( Img888, draw_img_leopard )( IMG, colors, sizeof(colors)/sizeof(BLK_TYPE(Pixel888)) );
    
//    GLU_FUNC( Font, set_font )( kGLU_Font_Optima );
//    GLU_FUNC( Font, set_size )( 200 );
//    GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )( "Glucoo" );
//
//    // 引用灰度字体图像(类型信息复制转换)
//    BLK_SRCT(ImgGry) img_font = {
//        .height  = pF->img_h,
//        .width   = pF->img_w,
//        .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
//    };
//
//    BLK_FUNC(ImgGry,into_Img888)(&img_font, IMG, 135, 145, M_COLOR_BLACK );
    
    BLK_FUNC( Img888, out_bmp )("/Users/randle_h/Desktop/leopard.bmp", IMG);
#endif
    
    
#if 0
    
    __GUI_Object_t a  = {0};
    ID_t           id = 0;
    
    GLU_FUNC(Object, template)( &a, kGUI_ObjStyle_text );

    a.text_size = 100;
    a.font = kGLU_Font_Optima;
    a.area.xs     = 0;
    a.area.ys     = 0;
    a.area.height = 300;
    a.area.width  = 800;
    a.obj_color   = M_COLOR_GOLDEN;
    a.text        = "GUCCI";
    a.showFrame   = 0;
    
    id = GLU_FUNC(Object,create  )( &a, NULL );
    GLU_FUNC(Object, insert)( id );
    
    GLU_FUNC( GUI, refreashScreen )();
    
#endif

    return 0;
}




