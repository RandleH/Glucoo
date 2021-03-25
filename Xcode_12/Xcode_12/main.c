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

int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();

    GUI_RefreashScreen();


    __GUI_Window_t cfg2;
    GUI_easySet_window(&cfg2);
    cfg2.area.xs     = 100;
    cfg2.area.ys     = 50;
    cfg2.area.height = 360;
    cfg2.area.width  = 600;
    cfg2.type        = kGUI_WindowType_macOS;
    cfg2.size        = 40;
    cfg2.appearance  = kGUI_Appearance_Dark;
    cfg2.title       = "To: Pr.WenKai";
    cfg2.text_size   = 20;
    cfg2.text_font   = kGUI_FontStyle_Arial_Unicode;//kGUI_FontStyle_NewYork;
    cfg2.text        = "Hello, this is not a regular dialog box and either not a snapshot from my computer. It is a simple UI designed for my command desk which is a embedded device targeting on STM32. This UI project named ""Glucoo"". It has been published on my GitHub website and the link is attached in the E-mail. If you view carefully, you will find out an another secrete repository reference from 'Glucoo'. That's right-> BlackHouse!!! Honestly, Glucoo doesn't work very well. Those functions are still limited-useed or poor-proformance. Me now writting English as a Chinese friend is one of those that it doesn't support any charactor beyond the ASCII. Anyway, I made this simply not for any competition, rewords or research. I just assume that I am a novelist or king of my own Digital-Empire. I create my own data structure like building an architecture or managing a beautiful city. This sounds a little bit aggressive. I used to be solo and I tried to work togeither with friends, but maybe I laid the standard so high that no one can meet it even for myself. Anyway, It will be my honor if you take a look of my project. ";
    ID_t ID_Window2 = GUI_create_window(&cfg2);

    GUI_insert_window( ID_Window2 );
    GUI_RefreashScreen();

    GUI_delete_window( ID_Window2 );
    
    

//    printf("%x\n ",__swap_32BIT(0x58010000));
    __ImgRGB888_load_png("/Users/randle_h/desktop/pig.png");
    
    
    return 0;
}
