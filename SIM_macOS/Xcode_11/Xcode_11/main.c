//
//  main.c
//  Xcode_11
//
//  Created by Randle Helmslay on 2021/4/18.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>


#include "RH_gui.h"
#include "RH_color.h"
#include "RH_gui_api.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    GUI_Init();
    Simul_API_Init();
    
//    __GUI_Object_t cfg_obj = {0};
//
//    GUI_object_quickSet(&cfg_obj);
//
//    cfg_obj.style       = kGUI_ObjStyle_num;
//    cfg_obj.area.xs     = 30;
//    cfg_obj.area.ys     = 30;
//    cfg_obj.area.height = 12;
//    cfg_obj.area.width  = 70;
//    cfg_obj.min[0]      = 0;
//    cfg_obj.max[0]      = 256;
//    cfg_obj.font        = kGUI_FontStyle_ArialRounded_Bold;
//    cfg_obj.text_color  = M_COLOR_WHITE;
//    cfg_obj.text        = "size:";
//    cfg_obj.text_size   = 8;
//    cfg_obj.text_align  = kGUI_FontAlign_Left;
//    cfg_obj.showFrame   = false;
//
//    cfg_obj.bk_color    = M_COLOR_BLACK;
//
//    cfg_obj.val[0]      = 129;
//
//    ID_t ID_Obj1 = GUI_object_create( &cfg_obj );
//    GUI_object_insert(ID_Obj1);
    
    GUI_rect_raw(30,40, 70, 50);
    
    
    GUI_RefreashScreen();
    
    
    
    return 0;
}



