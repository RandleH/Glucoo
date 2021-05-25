//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/4/7.
//

#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "RH_color.h"

#include "GLU_api.h"
#include "BLK_data.h"


#include "GLU_glucoo.h"

#include "BLK_poker.h"

#define DICE_NUM_MAX      6
#define DICE_NUM_MIN      1

#define PROJ_MIN(a,b)                           (((a)<(b))?(a):(b))

#define PROJ_MAX(a,b)                           (((a)>(b))?(a):(b))



int main(int argc, const char * argv[]) {
//    printf("%f\n",hypotf(64,128));
    Simul_API_Init();
    
    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_WHITE);
    
//    BLK_Poker_option( M_BLK_POKER_OPT_NO_JOKER );
//    
//    S_PokerDeck_t *deck = NULL;
//    
//    deck = BLK_FUNC( Poker, create )();
//    BLK_FUNC( Poker, print)( deck, printf );
    
    __GUI_Menu_t cfg = {0};
    
    cfg.area.height = 200;
    cfg.area.width  = 320;
    cfg.area.xs     = 0;
    cfg.area.ys     = 0;
    
    cfg.bk_color       = M_COLOR_BLACK;
    cfg.bk_color_title = M_COLOR_BLACK;
    cfg.color_title    = M_COLOR_RED;
    cfg.font           = kGUI_FontStyle_ArialRounded_Bold;
    
    __GUI_MenuParam_t menuList[5] = {0};
    menuList[0].text = "Param 0";
    menuList[1].text = "Param 1";
    menuList[2].text = "Param 2";
    menuList[3].text = "Param 3";
    menuList[4].text = "Param 4";
    cfg.menuList     = menuList;
    
    cfg.nItem = 5;
    cfg.size  = 8;
    cfg.sl_color = M_COLOR_WHITE;
    cfg.text_color = M_COLOR_WHITE;
    cfg.title    = "Bad";
    
    ID_t ID_Menu = GUI_menu_create(&cfg);
    GUI_menu_insert(ID_Menu);
    GUI_menu_scroll(ID_Menu, 1);
    GUI_menu_scroll(ID_Menu, 1);
    GUI_menu_scroll(ID_Menu, -1);
    GUI_RefreashEntireScreen();
    
#if 0
    const char* pStrs[] = {
        "Jd" , // Jade
        "Gs" , // Ginseng
        "Sl" , // Silk
        "Ng"   // Nutmeg
    };
    
    ID_t ID_BoatStatus[3] = {0};
    ID_t ID_CargoName[3]  = {0};
    ID_t ID_DiceRound_txt = 0;
    ID_t ID_DiceRound_num = 0;
    __GUI_Object_t cfg = {0};

    GUI_object_template( &cfg, kGUI_ObjStyle_trunk );
    cfg.obj_color  = M_COLOR_WHITE;
    cfg.area.xs    = 10;
    cfg.area.ys    = 3;
    cfg.area.width = 14;
    
    ID_BoatStatus[0] = GUI_object_create( &cfg );
    cfg.area.xs += cfg.area.width+2;
    ID_BoatStatus[1] = GUI_object_create( &cfg );
    cfg.area.xs += cfg.area.width+2;
    ID_BoatStatus[2] = GUI_object_create( &cfg );
    
    GUI_object_insert( ID_BoatStatus[0] );
    GUI_object_insert( ID_BoatStatus[1] );
    GUI_object_insert( ID_BoatStatus[2] );
    GUI_RefreashEntireScreen();
    

    __GUI_ObjDataScr_barV data = {
        .min   = 0,
        .max   = 14,
        .value = 5//...//
    };
    GUI_object_adjust( ID_BoatStatus[0], &data, sizeof(data));
    
    data.value = 4; //...//
    GUI_object_adjust( ID_BoatStatus[1], &data, sizeof(data));

    data.value = 5;//...//
    GUI_object_adjust( ID_BoatStatus[2], &data, sizeof(data));

    
    data.value = 5;
    GUI_object_adjust( ID_BoatStatus[1], &data, sizeof(data));
    
    GUI_RefreashScreen();
#endif

    return 0;
}




