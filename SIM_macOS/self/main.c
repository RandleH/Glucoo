//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/4/7.
//

#include <stdio.h>
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_color.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    Simul_API_Init();
    
    GUI_Init();
    GUI_set_penSize(5);
    
    __GUI_Window_t cfg;
    GUI_window_quickSet(&cfg);
    cfg.area.xs     = 20;
    cfg.area.ys     = 20;
    cfg.area.height = 40;
    cfg.area.width  = 90;
    cfg.type        = kGUI_WindowType_win10;
    cfg.size        = 9;
    cfg.appearance  = kGUI_Appearance_Light;
    cfg.title       = "Text";
    cfg.text        = NULL;
    cfg.text_size   = 8;

    ID_t ID_Window1 = GUI_window_create(&cfg);
    GUI_window_insert( ID_Window1 );
    
    
    __GUI_Object_t cfg_obj = {0};
    
    GUI_object_quickSet(&cfg_obj);
    
    cfg_obj.area.xs     = 30;
    cfg_obj.area.ys     = 30;
    cfg_obj.area.height = 10;
    cfg_obj.area.width  = 30;
    cfg_obj.min = 0;
    cfg_obj.max = 1;
    cfg_obj.font = kGUI_FontStyle_ArialRounded_Bold;
    cfg_obj.color = M_COLOR_BLACK;
    cfg_obj.style = kGUI_ObjStyle_text;
    cfg_obj.text  = "size:";
    cfg_obj.text_size = 8;
    
    ID_t ID_Obj1 = GUI_object_create( &cfg_obj );
    GUI_object_show(ID_Obj1);
    
    GUI_RefreashScreen();
    return 0;
}
