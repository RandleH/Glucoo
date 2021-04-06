//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/3/5.
//

#include <stdio.h>
#include <time.h>
#include "RH_common.h"
#include "RH_data.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_font.h"
#include "RH_lib.h"
#include "RH_time.h"
#include "RH_graphic.h"



int main(int argc, const char * argv[]) {
    // insert code here...
    
    Simul_API_Init();

    GUI_Init();
    GUI_set_penSize(5);
    __GUI_Window_t cfg;
    GUI_easySet_window(&cfg);
    cfg.area.xs     = 20;
    cfg.area.ys     = 20;
    cfg.area.height = 40;
    cfg.area.width  = 90;
    cfg.type        = kGUI_WindowType_macOS;
    cfg.size        = 9;
    cfg.appearance  = kGUI_Appearance_Light;
    cfg.title       = "Text";
    cfg.text        = "abc def ghi";
    cfg.text        = "abcde fghijk lmnopq rstuvw xyzABC DEFGHI JKLMNOP QRSTU VWXYZ";
    cfg.text_size   = 8;

    ID_t ID_Window1 = GUI_create_window(&cfg);
    GUI_insert_window( ID_Window1 );

    GUI_RefreashScreen();
    
    
//    __Font_init();
//    __Font_setStyle(kGUI_FontStyle_ArialRounded_Bold);
    
//    __Font_setSize(29);
//    __Font_exportChar('G');
    
//    __Font_setSize(7);
//    __Font_exportStr("fuck you!!! Bitch");
//    __Font_exportText_Justify("Hello, this is not a regular dialog box and either not a snapshot from my computer. It is a simple UI designed for my command desk which is a embedded device targeting on STM32. This UI project named ""Glucoo"". It has been published on my GitHub website and the link is attached in the E-mail. If you view carefully, you will find out an another secrete repository reference from 'Glucoo'. That's right-> BlackHouse!!! Honestly, Glucoo doesn't work very well. Those functions are still limited-useed or poor-proformance. Me now writting English as a Chinese friend is one of those that it doesn't support any charactor beyond the ASCII. Anyway, I made this simply not for any competition, rewords or research. I just assume that I am a novelist or king of my own Digital-Empire. I create my own data structure like building an architecture or managing a beautiful city. This sounds a little bit aggressive. I used to be solo and I tried to work togeither with friends, but maybe I laid the standard so high that no one can meet it even for myself. Anyway, It will be my honor if you take a look of my project.", 420);
    printf("%s\n",__PST2BJT("2021-04-08 11:30:00"));
    return 0;
}


