
#include <unistd.h>

#include "RH_common.h"
#include "RH_color.h"

#include "GLU_api.h"
#include "GLU_glucoo.h"
#include "GLU_area.h"


#include "GLU_image.h"
#include "GLU_object.h"


int main(int argc, char const *argv[]){
    
#if 1

    GLU_GUI_init();
    
    GLU_GUI_autoDisplay(true);
    

    GLU_SRCT(Text) text = {
        .str   = "Skylee"          ,
        .size  = 700               ,
        .color = M_COLOR_BLACK     ,
        .align = kGLU_Align_Middle ,
        .font  = kGLU_Font_SignPrinter  ,
    };

    GLU_TYPE(Color) color[] = {
        M_COLOR_MAGENTA         ,
        M_COLOR_CADETBLUE       ,
        M_COLOR_POWDERBLUE      ,
    };

    GLU_Image_profile( kGLU_ImageStyle_aurora, &color[0], sizeof(color)/sizeof(*color), &text, 30 );
    // GLU_GUI_refreashEntireScreen();

#endif
    


    return 0;
}
