//
//  main.c
//  Xcode_11
//
//  Created by Randle Helmslay on 2021/3/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//


#include <stdio.h>
#include "RH_common.h"
#include "RH_lib.h"
#include "RH_gui.h"
#include "RH_gui_api.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();
    
    GUI_RefreashScreen();

    __GUI_Window_t cfg;
    cfg.area.xs     = 30;
    cfg.area.ys     = 40;
    cfg.area.height = 300;
    cfg.area.width  = 500;
    cfg.type        = kGUI_WindowType_macOS;
    cfg.size        = 40;
    cfg.appearance  = kGUI_Appearance_Dark;
    cfg.title       = "Text";

    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    ID_t ID_Window1 = GUI_create_window(&cfg);
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    GUI_insert_window( ID_Window1 );
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    GUI_RefreashScreen();
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    GUI_delete_window( ID_Window1 );
    
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    
    return 0;
}
