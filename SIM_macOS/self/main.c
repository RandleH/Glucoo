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


int main(int argc, const char * argv[]) {

    Simul_API_Init();
    
    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_WHITE);
    
//    GUI_rect_fill(20, 20, 40, 50);
//    GUI_rect_fill(41, 20, 61, 49);
//    GUI_auto_display(0);
//    __RECORD_TIME( GUI_RefreashScreen(), printf );
#if 1
{
    __GUI_Menu_t cfg = {0};
    
    cfg.area.xs = 10;
    cfg.area.ys = 10;
    cfg.area.height = 50;
    cfg.area.width  = 90;
    cfg.nItem = 2;
    cfg.title = "Title";
    cfg.color_title = M_COLOR_WHITE;
    cfg.size  = 10;
    
    cfg.bk_color   = M_COLOR_BLACK;
    cfg.sl_color   = M_COLOR_WHITE;
    cfg.text_color = M_COLOR_WHITE;
    
    __GUI_MenuParam_t m[10] = {0};
    m[0].text = "menu_0";
    m[1].text = "menu_1";
    
    cfg.menuList = m;
    
    ID_t MENU = GUI_menu_create(&cfg);
    GUI_menu_frame( MENU, 1 );
    GUI_menu_insert(MENU);
    __RECORD_TIME( GUI_RefreashScreen(), printf );

    GUI_menu_scroll( MENU, 1 );
    GUI_menu_scroll( MENU, 1 );
    GUI_menu_scroll( MENU, -1 );

    __RECORD_TIME( GUI_RefreashEntireScreen(), printf );
#endif
    
    GUI_menu_delete( MENU );
    __RECORD_TIME( GUI_RefreashEntireScreen(), printf );
}
    
    printf("Remain Allocated Memory: %ld Byte\n",RH_Debug_alloced_byte);
    
    __GUI_Object_t cfg = {0};

    GUI_object_quickSet(&cfg);

    cfg.style       = kGUI_ObjStyle_text;
    cfg.area.xs     = 30;
    cfg.area.ys     = 30;
    cfg.area.height = 12;
    cfg.area.width  = 70;
    cfg.font        = kGUI_FontStyle_ArialRounded_Bold;
    cfg.text_color  = M_COLOR_WHITE;
    cfg.text        = "No preview.";
    cfg.text_size   = 8;
    cfg.text_align  = kGUI_FontAlign_Left;
    cfg.showFrame   = false;

    cfg.bk_color    = M_COLOR_BLACK;
    ID_t ID_Object = 0;
    
    
    ID_Object = GUI_object_create( &cfg );

    GUI_object_insert( ID_Object );
    GUI_RefreashScreen();

    GUI_object_delete( ID_Object );
    GUI_RefreashScreen();
    printf("Remain Allocated Memory: %ld Byte\n",RH_Debug_alloced_byte);
    return 0;
}
