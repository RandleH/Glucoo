
#include <unistd.h>

#include "RH_common.h"
#include "RH_color.h"

#include "GLU_api.h"
#include "GLU_glucoo.h"
#include "GLU_area.h"

#include "GLU_object.h"



int main(int argc, char const *argv[]){
    
#if 1
    GLU_GUI_init();
    
    GLU_GUI_autoDisplay(false);
    
    GLU_SRCT(Object) config;
    GLU_Object_template( &config, kGUI_ObjStyle_button );
    
    config.text.align  = kGLU_Align_Middle;
    config.text.color  = M_COLOR_BLACK;
    
    config.showFrame   = false;
    
    GLU_Utility_optimal_text( &config.area, "Check", kGLU_Font_ArialRounded_Bold, &config.text );
    
    __GUI_ObjDataScr_button dataSrc = {
        .cmd    = true,
        .active = false,
        .radius = 400,
    };
    
    ID_t obj = GLU_Object_create( &config, &dataSrc );
    
    GLU_Object_insert(obj);
    

    
    GLU_Object_adjust(obj, &dataSrc, sizeof(dataSrc));
    
    GLU_GUI_refreashScreen();
    
#endif
    
//#include "BLK_image.h"
//#include "BLK_graphic.h"
//    BLK_Graph_init();
//    S_BLK_Img888_t* IMG = BLK_Img888_create(3210, 1920);
//    BLK_Graph_set_penColor(M_COLOR_CYAN);
//    BLK_Graph_rect_round_raw         ( 300 ,\
//                                       300 ,\
//                                       700 ,\
//                                       500 ,\
//                                       IMG, NULL );
//
//
//    BLK_Img888_out_png( "/Users/randle_h/Desktop/output.png", IMG );
    

    return 0;
}
