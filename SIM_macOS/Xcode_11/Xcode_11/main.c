

#include <stdio.h>
#include "GLU_glucoo.h"



int main(int argc, const char * argv[]) {

    GLU_FUNC(GUI,init)();
    
    GLU_FUNC(Font,set_font)( kGLU_Font_NewYork_Italic );
    GLU_FUNC(Font,set_size )(23);

   // (967,743)     out (900,740)(1393,740)(1386,826)
    printf("%d\n", BLK_FUNC( Math, pt_triangle )(900,740,  1393,740,  1386,826,  967,743 )   );


#if 1
    GLU_SRCT(Text) text = {
        .align = kGLU_Align_Middle ,
        .size  = 200,
        .str   = "Glucoo" ,
        .color = M_COLOR_RED,
        .font  = kGLU_Font_SignPrinter
    };

    BLK_SRCT(Img888)* IMG = BLK_Img888_create(1800, 1480);
    
    BLK_TYPE(Pixel888) colors[5] = {
        MAKE_COLOR(255,105,180) ,\
        MAKE_COLOR(135,206,235) ,\
        MAKE_COLOR( 64,224,208) ,\
        MAKE_COLOR(173,255, 47) ,\
        MAKE_COLOR(250,250,210) ,\
    };
    
    BLK_FUNC( Img888, draw_img_ )( IMG, colors, 5 );
    
    BLK_FUNC(Img888, out_bmp)("/Users/randle_h/Desktop/screen.bmp", IMG);

#endif

    
    return 0;
}



