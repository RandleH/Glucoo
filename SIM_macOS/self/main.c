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

#include "BLK_image.h"
#include "BLK_time.h"

#define DICE_NUM_MAX      6
#define DICE_NUM_MIN      1

#define PROJ_MIN(a,b)                           (((a)<(b))?(a):(b))

#define PROJ_MAX(a,b)                           (((a)>(b))?(a):(b))


void d( int son, int div ){
    int m = son%div;
    int k = div - m;
    int base = son/div;
    
    for( bool flag=false; m||k; flag=!flag ){
        if( flag  && m )  {
            m--;
            printf( "%d\n", base+1 );
        }
        if( !flag && k )  {
            k--;
            printf( "%d\n", base );
        }
    }
    
}


int main(int argc, const char * argv[]) {

    Simul_API_Init();

    GLU_GUI_init        ();
    GLU_GUI_setPenSize  (5);
    GLU_GUI_setPenColor (M_COLOR_WHITE);
    
# if 1
    
//    GLU_FUNC( Font, set_size )(200);
//    GLU_FUNC( Font, set_font )( kGLU_Font_SignPrinter );
//
//    size_t w,h;
//    GLU_Font_get_str_ImgInfo(&w, &h, "Glucoo");
//
//    GLU_Font_out_str_Img("Glucoo");
    
    GLU_SRCT(Text) text = {
        .align = kGLU_Align_Middle ,
        .size  = 200,
        .str   = "XingYue" ,
        .color = M_COLOR_BLACK,
        .font  = kGLU_Font_SignPrinter
    };


    BLK_TYPE(Pixel888) colors[5] = {
        MAKE_COLOR(255,105,180) ,\
        MAKE_COLOR(135,206,235) ,\
        MAKE_COLOR( 64,224,208) ,\
        MAKE_COLOR(173,255, 47) ,\
        MAKE_COLOR(250,250,210) ,\
    };


    GLU_Image_profile ( kGLU_ImageStyle_aurora, colors, 5, &text, 30 );

    GLU_GUI_refreashEntireScreen ();
    
    
#endif
    return 0;
}




