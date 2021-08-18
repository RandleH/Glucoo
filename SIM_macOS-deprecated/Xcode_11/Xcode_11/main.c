

#include <stdio.h>
#include "GLU_glucoo.h"
#include "GLU_image.h"
#include "GLU_api.h"


static void applyMandelBrotPix_RGB888(int x,int y,uint32_t nIter, void* p){
    BLK_SRCT(Img888)* dst = (BLK_SRCT(Img888)*)p;
    if(nIter == -1)
        nIter = 0;

    nIter = RH_MIN( 0xffffffff, nIter );

    (dst->pBuffer + y*dst->width + x)->R = nIter&0x00ff0000;
    (dst->pBuffer + y*dst->width + x)->G = nIter&0x0000ff00;
    (dst->pBuffer + y*dst->width + x)->B = nIter&0x000000ff;
    
}

int main(int argc, const char * argv[]) {
    Simul_API_Init();
    GLU_FUNC(GUI,init)();
    
    GLU_FUNC(Font,set_font)( kGLU_Font_NewYork_Italic );
    GLU_FUNC(Font,set_size )(23);
    
    GLU_FUNC(GUI, autoDisplay)(true);
    
    BLK_SRCT(Img888)* IMG = BLK_Img888_create(1600, 960);
    
    float scale = 0.000000005;
    BLK_Mandelbrot_image(-0.2501511275768280029297-0.0000001013208930089604*I, 1600, 960, scale, scale,  IMG, applyMandelBrotPix_RGB888 );
    
    BLK_Img888_out_bmp("/Users/randle_h/Desktop/screen0.bmp", IMG );
    
    
    
#if 0
    GLU_SRCT(Text) text = {
        .align = kGLU_Align_Middle ,
        .size  = 200,
        .str   = "RandleH" ,
        .color = M_COLOR_BLACK,
        .font  = kGLU_Font_SignPrinter
    };

//    BLK_SRCT(Img888)* IMG = BLK_Img888_create(1800, 1480);
    
    BLK_TYPE(Pixel888) colors[5] = {
        MAKE_COLOR(255,105,180) ,\
        MAKE_COLOR(250,250,210) ,\
        MAKE_COLOR(135,206,235) ,\
        MAKE_COLOR(173,255, 47) ,\
        MAKE_COLOR( 64,224,208) ,\
        
    };
    
    GLU_Image_profile( kGLU_ImageStyle_aurora, colors, 5, &text, 40 );
    GLU_GUI_refreashEntireScreen();
    
//    BLK_FUNC(Img888, out_bmp)("/Users/randle_h/Desktop/screen.bmp", IMG);

#endif

    
    return 0;
}



