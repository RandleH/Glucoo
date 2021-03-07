//
//  main.c
//  Xcode_11
//
//  Created by Randle Helmslay on 2021/3/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//


#include <stdio.h>
#include "RH_common.h"
#include "RH_gui.h"
#include "RH_gui_api.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();
    GUI_Init();
    GUI_rect_raw(130, 230, 680, 450);
    GUI_RefreashScreen();
    return 0;
}
