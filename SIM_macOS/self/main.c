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
#include "GLU_area.h"

#include "BLK_data.h"


#include "GLU_glucoo.h"
#include "GLU_image.h"
#include "GLU_glucoo.h"

#include "BLK_graphic.h"

#include "BLK_image.h"
#include "BLK_time.h"

extern BLK_TYPE(Canvas) info_MainScreen; //...//

#include <dirent.h>



int main(int argc, const char * argv[]) {
    GLU_API_init();
    GLU_GUI_init();
    
    __Area_t a = { .xs = 500, .ys = 500, .w = 300, .h = 400 };
    __Area_t b = { 0 };
    
    GLU_Utility_align_screen( 400, 300, &b, M_UTILITY_ALIGN_VM | M_UTILITY_ALIGN_HM );
    
    GLU_GUI_autoDisplay(false);
    
    
    __Area_t c[10] = {
        {.w=10,.h=10},{.w=20,.h=10},{.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10},\
        {.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10}
    };
    

    GLU_Utility_area_hdiv( &a, c, 10);
    
    GLU_GUI_EX_rect_raw(&a);
    
    GLU_GUI_setPenColor(M_COLOR_RED);
    for (int i=0; i<10; i++) {
        GLU_GUI_EX_rect_fill(&c[i]);
        printf("(%d,%d)\n",c[i].xs,c[i].ys);
    }
    GLU_GUI_refreashScreen();
    
    return 0;
}




