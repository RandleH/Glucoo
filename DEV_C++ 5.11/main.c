

#include <stdio.h>
#include "RH_common.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_gui_font.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();
    
    // GUI_RefreashScreen();
    
    // __GUI_Window_t cfg = {0};
    // cfg.area.xs = 30;
    // cfg.area.ys = 40;
    // cfg.area.height = 300;
    // cfg.area.width  = 600;
    // cfg.type = kGUI_WindowType_macOS;
    // cfg.size = 40;
    
    // ID_t ID_Window1 = GUI_create_window(&cfg);
    
    // GUI_show_window( ID_Window1 );
    
    // GUI_RefreashScreen();
    
    // GUI_delete_window( ID_Window1 );
    const char* path_in  = "D:\\Personal\\Desktop\\temp.bmp";
    const char* path_out = "D:\\Personal\\Desktop\\out.bmp";
    __ImageRGB565_t* IMG_IN  = __ImgRGB565_load_bmp(path_in);
    __ImageRGB565_t* IMG_OUT = __ImgRGB565_create( IMG_IN->width , IMG_IN->height );
    __ImgRGB565_copy( IMG_IN, IMG_OUT );
    __ImgRGB565_out_bmp( path_out, IMG_OUT );
    return 0;
}
