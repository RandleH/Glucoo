//
//  main.c
//  Xcode_11
//
//  Created by Randle Helmslay on 2021/4/18.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include "RH_gui.h"
#include "RH_gui_api.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    GUI_Init();
    Simul_API_Init();
    
    GUI_auto_display(0);
    
    GUI_rect_raw(30,30,50,50);
    GUI_RefreashScreen();
    
    return 0;
}



