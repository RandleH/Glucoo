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
    
    
    
    __GUI_Window_t cfg2;
    GUI_window_quickSet(&cfg2);
    cfg2.area.xs     = 0;
    cfg2.area.ys     = 0;
    cfg2.area.height = 63;
    cfg2.area.width  = 127;
    cfg2.type        = kGUI_WindowType_macOS;
    cfg2.size        = 8;
    cfg2.appearance  = kGUI_Appearance_Light;
    cfg2.title       = "To: Pr.WenKai";
    cfg2.text_size   = 8;
    cfg2.text_font   = kGUI_FontStyle_ArialRounded_Bold;//kGUI_FontStyle_NewYork;
    cfg2.text        = "Hello, this is not a regular dialog box and either not a snapshot from my computer. It is a simple UI designed for my command desk which is a embedded device targeting on STM32.";
    ID_t ID_Window2 = GUI_window_create(&cfg2);

    GUI_window_insert( ID_Window2 );
    GUI_RefreashScreen();

    return 0;
}
