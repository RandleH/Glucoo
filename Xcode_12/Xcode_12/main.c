//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/3/5.
//

#include <stdio.h>
#include "RH_common.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_gui_font.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();
    
    GUI_RefreashScreen();
    
    __GUI_Window_t cfg1;
    cfg1.area.xs     = 30;
    cfg1.area.ys     = 40;
    cfg1.area.height = 300;
    cfg1.area.width  = 500;
    cfg1.type        = kGUI_WindowType_macOS;
    cfg1.size        = 40;
    cfg1.appearance  = kGUI_Appearance_Dark;
    cfg1.title       = "Text";
    
    __GUI_Window_t cfg2;
    cfg2.area.xs     = 200;
    cfg2.area.ys     = 140;
    cfg2.area.height = 130;
    cfg2.area.width  = 300;
    cfg2.type        = kGUI_WindowType_macOS;
    cfg2.size        = 40;
    cfg2.appearance  = kGUI_Appearance_Light;
    cfg2.title       = "Glucoo";
    
    
    ID_t ID_Window1 = GUI_create_window(&cfg1);
    ID_t ID_Window2 = GUI_create_window(&cfg2);
    
    GUI_insert_window( ID_Window1 );
    GUI_insert_window( ID_Window2 );
    GUI_RefreashScreen();
    
    GUI_delete_window( ID_Window1 );
    
    

    
    return 0;
}
