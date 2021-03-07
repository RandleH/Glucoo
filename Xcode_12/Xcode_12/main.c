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
    
    __GUI_Window_t cfg;
    cfg.area.xs = 30;
    cfg.area.ys = 40;
    cfg.area.height = 300;
    cfg.area.width  = 600;
    cfg.type = kGUI_WindowType_macOS;
    cfg.size = 40;
    
    ID_t ID_Window1 = GUI_create_window(&cfg);
    
    GUI_show_window( ID_Window1 );
    
    GUI_RefreashScreen();
    
    GUI_delete_window( ID_Window1 );
    
    GUI_SetFontStyle(kGUI_FontStyle_CourierNew_Italic);
    GUI_SetFontSize(100);
    GUI_ExportFontStr("ABCDEFGhijkl");
    
    return 0;
}
