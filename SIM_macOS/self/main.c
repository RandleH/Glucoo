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

int main(int argc, const char * argv[]) {

    Simul_API_Init();

    GLU_GUI_init        ();
    GLU_GUI_setPenSize  (5);
    GLU_GUI_setPenColor (M_COLOR_WHITE);
    
# if 1
    
    GLU_SRCT(Text) text = {
        .align = kGLU_Align_Middle ,
        .size  = 520,
        .str   = "COMMON" ,
        .color = M_COLOR_BLACK,
        .font  = kGLU_Font_Optima

    };


    BLK_TYPE(Pixel888) colors[5] = {
        MAKE_COLOR( 230, 227, 20) ,\
        MAKE_COLOR( 230, 127, 20)
    };

//    ( 80,127, 20)
    
    

    RH_RECORD_TIME( GLU_Image_profile ( kGLU_ImageStyle_blur, colors, 2, &text, 70 ), printf);
    
    GLU_Font_set_font(kGLU_Font_SignPrinter);
    GLU_Font_set_size(240);
    GLU_SRCT(FontImg)* pF = GLU_Font_out_str_Img("by Randle.Helmslay");
    
    BLK_SRCT(ImgGry) img_font = {
        .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf ,
        .height  = pF->img_h   ,
        .width   = pF->img_w
    };
    
    BLK_ImgGry_into_Img888(&img_font, &info_MainScreen, 867, 1216, M_COLOR_BLACK, 100);

    GLU_GUI_refreashEntireScreen ();
    
    
#endif
    return 0;
}




