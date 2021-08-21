
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
    
    // config.text.align  = kGLU_Align_Middle;
    // config.text.color  = M_COLOR_BLACK;
    // config.area.xs = 100;
    // config.area.ys = 100;
    // config.area.h  = 1600;
    // config.area.w  = 2900;
    // config.showFrame   = false;
    
    // GLU_Utility_optimal_text( &config.area, "Check", kGLU_Font_NewYork, &config.text );
    
    __GUI_ObjDataScr_button dataSrc = {
        .cmd    = true,
        .active = false,
        .radius = 100,
    };
    
    ID_t obj = GLU_Object_create( &config, &dataSrc );
    
    GLU_Object_insert(obj);

    
    GLU_Object_adjust(obj, &dataSrc, sizeof(dataSrc));
    
    GLU_GUI_refreashScreen();
    
#error    "dataSrc is not included in func <GLU_Object_template>."
#warning  "I dont't like the enumeration name: <E_GUI_ObjWidget_t>."

#endif
    


    return 0;
}
