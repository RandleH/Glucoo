
#include <unistd.h>

#include "RH_common.h"
#include "RH_color.h"

#include "GLU_api.h"
#include "GLU_glucoo.h"
#include "GLU_area.h"


#include "GLU_image.h"
#include "GLU_object.h"

static void open_img(void){
    char path[255] = {0};
    const char* name = "snapshot";
    sprintf( path, "%s/%s.bmp", RH_DIR, name );
    
    char cmd[255+5] = {0};
    sprintf( cmd, "open %s", path);
    system(cmd);
}

int main(int argc, char const *argv[]){
    
#if 1

    GLU_GUI_init();
    
    GLU_GUI_autoDisplay(true);
    
    
    S_GLU_Object_t config = {0};
    GLU_Object_template( &config, kGLU_ObjWidget_button);
    
    __GUI_ObjDataScr_button dataSrc = {
        .cmd    = true ,
        .active = false,
        .radius = 100,
    };
    
    ID_t obj1 = GLU_Object_create( &config, &dataSrc);
    
    GLU_Object_insert(obj1);
    
    GLU_GUI_refreashEntireScreen();
    
#endif
    

    open_img();
    
    return 0;
}



