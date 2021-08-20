
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

    GLU_GUI_screen_fill( M_COLOR_COAL );
    
    GLU_SRCT(Object) config;
    GLU_Object_template( &config, kGUI_ObjStyle_button );
    
    config.text.align  = kGLU_Align_Middle;
    config.text.color  = M_COLOR_BLACK;
    config.area.h = 300;
    config.area.w = 600;
    config.showFrame   = false;
    
    GLU_Utility_optimal_text( &config.area, "Glucoo", kGLU_Font_ArialRounded_Bold, &config.text );
    
    __GUI_ObjDataScr_button dataSrc = {
        .cmd    = true,
        .active = false,
        .radius = 100,
    };
    
    ID_t obj = GLU_Object_create( &config, &dataSrc );
    
    GLU_Object_insert(obj);

    
    GLU_Object_adjust(obj, &dataSrc, sizeof(dataSrc));
    
    GLU_GUI_refreashScreen();
    


#endif
    


    return 0;
}
