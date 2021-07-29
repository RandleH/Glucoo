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
#include "GLU_image.h"
#include "BLK_graphic.h"

#include "BLK_image.h"
#include "BLK_time.h"

extern BLK_TYPE(Canvas) info_MainScreen; //...//

#include <dirent.h>



int main(int argc, const char * argv[]) {
    GLU_API_init();
    GLU_GUI_init();
    
//    for (int i=255,j=0; i>=0; i--,j++) {
//        if( j%14==0 )
//            printf("\n");
//        printf("%3d, ", lround( 255*expf(-(i*i)/11734.688) ));
//
//    }
    
    BLK_SRCT(Img888) *IMG = BLK_Img888_create(3100, 1920);
    BLK_TYPE(Pixel888) colors[4] = {
        M_COLOR_CYAN ,\
        M_COLOR_BLUE ,\
        M_COLOR_GREEN,\
        M_COLOR_RED
    };
    
    RH_RECORD_TIME( BLK_Img888_draw_img_faded(IMG, colors, 4), printf);
    
    BLK_Img888_out_bmp("/Users/randle_h/Desktop/img.bmp", IMG);
    system("open /Users/randle_h/Desktop/img.bmp");
    
# if 0
    GLU_SRCT(Text) text = {
        .align = kGLU_Align_Middle ,
        .size  = 520,
        .str   = "COMMON" ,
        .color = M_COLOR_BLACK,
        .font  = kGLU_Font_Optima
    };

    BLK_TYPE(Pixel888) colors[2] = {
        M_COLOR_CYAN ,\
        M_COLOR_BLUE
    };

    GLU_Image_profile ( kGLU_ImageStyle_blur, colors, sizeof(colors)/sizeof(*colors), &text, 70 );
    
    GLU_Font_set_font(kGLU_Font_SignPrinter);
    GLU_Font_set_size(240);
    GLU_SRCT(FontImg)* pF = GLU_Font_out_str_Img("by Randle.Helmslay");
    BLK_SRCT(ImgGry) img_font = {
        .ptr = (BLK_UION(PixelGry)*)pF->img_buf ,
        .h   = pF->img_h   ,
        .w   = pF->img_w
    };
    BLK_ImgGry_into_Img888(&img_font, &info_MainScreen, 867, 1216, M_COLOR_BLACK, 100);
    
    
    GLU_GUI_refreashEntireScreen ();
#endif
    return 0;
}




