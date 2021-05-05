//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/4/7.
//

#include <stdio.h>
#include <ctype.h>
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_color.h"
#include <time.h>

#include "RH_data.h"

enum __Dummy_t{
    k0,
    k1,
    k2
};

int main(int argc, const char * argv[]) {
    
    
    printf("%ld\n",sizeof(0xffff));
    Simul_API_Init();

    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_WHITE);

//    ID_t ID_Addr[5]    = {0};
//
//    __GUI_Object_t cfg = {0};
//
//    cfg.style       = kGUI_ObjStyle_num;
//    cfg.area.width  = 23;
//    cfg.area.height = 12;
//    cfg.area.xs     = (int)((RH_CFG_SCREEN_WIDTH - 5*cfg.area.width)>>1);
//    cfg.area.ys     = 32;
//
//    cfg.bk_color    = M_COLOR_BLACK;
//    cfg.font        = kGUI_FontStyle_ArialRounded_Bold;
//    cfg.text_align  = kGUI_FontAlign_Middle;
//    cfg.text_color  = M_COLOR_WHITE;
//    cfg.text_size   = 8;
//    cfg.max[0]      = 255;
//    cfg.min[0]      = 0;
//    cfg.val[0]      = 888;
//    cfg.showFrame   = true;
//    ID_Addr[0] = GUI_object_create( &cfg );
//
//    cfg.showFrame  = false;
//    cfg.area.xs   += cfg.area.width;
//    cfg.val[0]     = 888;
//    ID_Addr[1] = GUI_object_create( &cfg );
//
//    cfg.area.xs   += cfg.area.width;
//    cfg.val[0]     = 888;
//    ID_Addr[2] = GUI_object_create( &cfg );
//
//    cfg.area.xs   += cfg.area.width;
//    cfg.val[0]     = 888;
//    ID_Addr[3] = GUI_object_create( &cfg );
//
//    cfg.area.xs   += cfg.area.width;
//    cfg.val[0]     = 888;
//    ID_Addr[4] = GUI_object_create( &cfg );
//
//
//    GUI_object_insert( ID_Addr[0] );
//    GUI_object_insert( ID_Addr[1] );
//    GUI_object_insert( ID_Addr[2] );
//    GUI_object_insert( ID_Addr[3] );
//    GUI_object_insert( ID_Addr[4] );
//
//    GUI_RefreashScreen();
//
//
    return 0;
}
