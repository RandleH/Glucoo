//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/4/7.
//

#include <stdio.h>
#include <ctype.h>
#include "RH_gui_api.h"
#include "RH_color.h"
#include <time.h>

#include "RH_data.h"


#include "GLU_glucoo.h"
enum __Dummy_t{
    k0,
    k1,
    k2
};

int main(int argc, const char * argv[]) {
//    printf("%f\n",hypotf(64,128));
    Simul_API_Init();

    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_WHITE);
    int d = 11;
    bool eps = ((d&0x01)==0);
    int x = 32, y = 32;
    GUI_circle_raw( x, y, d );
    
    GUI_set_penColor(M_COLOR_RED);
    int xs = x - (d>>1) + eps;
    int ys = y - (d>>1) + eps;
    GUI_rect_raw( xs, ys, xs+d-1, ys+d-1 );
    
    GUI_RefreashScreen();
    __GUI_Object_t cfg = {0};

    GUI_object_template( &cfg, kGUI_ObjStyle_joystick );
    
//    cfg.area.height++;
//    cfg.area.width++;

    ID_t ID_Text = GUI_object_create( &cfg );

    GUI_object_insert( ID_Text );
    GUI_RefreashScreen();

    struct __GUI_ObjDataScr_joystick data = {
        .value = { 3500, 3000},
        .max   = { 4096, 4096},
        .min   = {    0,    0}
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
