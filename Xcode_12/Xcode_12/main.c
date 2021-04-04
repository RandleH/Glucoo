//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/3/5.
//

#include <stdio.h>
#include <time.h>
#include "RH_common.h"
#include "RH_data.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_font.h"
#include "RH_lib.h"
#include "RH_time.h"
#include "RH_graphic.h"



int main(int argc, const char * argv[]) {
    // insert code here...
    
    Simul_API_Init();
    
    GUI_Init();
    GUI_set_penSize(5);
    __GUI_Window_t cfg;
    GUI_easySet_window(&cfg);
    cfg.area.xs     = 20;
    cfg.area.ys     = 20;
    cfg.area.height = 300;
    cfg.area.width  = 600;
    cfg.type        = kGUI_WindowType_macOS;
    cfg.size        = 40;
    cfg.appearance  = kGUI_Appearance_Light;
    cfg.title       = "Text";

    cfg.text        = NULL;
    cfg.text_size   = 40;

    ID_t ID_Window1 = GUI_create_window(&cfg);
    GUI_insert_window( ID_Window1 );

    GUI_RefreashScreen();
//    __Font_init();
//    __Font_exportChar('x');
//    __Font_exportStr("This is a test");
//    __Font_exportStr("xt");
    
    return 0;
}


