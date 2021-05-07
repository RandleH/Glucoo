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
    
    Simul_API_Init();

    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_RED);

//    GUI_sausage_raw( 30,30, 70, 50 );

    __GUI_Object_t cfg = {0};

    GUI_object_template( &cfg, kGUI_ObjStyle_switch );
    ID_t ID_Text = GUI_object_create( &cfg );

    GUI_object_insert( ID_Text );
    GUI_RefreashScreen();
    
    struct __GUI_ObjDataScr_switch data = {
        .cmd = true
    };
    
    GUI_object_adjust( ID_Text, &data, sizeof(data));
    GUI_RefreashScreen();
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
