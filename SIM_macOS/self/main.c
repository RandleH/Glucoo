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

    Simul_API_Init();
    
    GLU_FUNC( GUI, init        )();
    GLU_FUNC( GUI, setPenSize  )(5);
    GLU_FUNC( GUI, setPenColor )(M_COLOR_WHITE);

    
#if 0
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
    
    ID_t ID_Menu = GLU_FUNC( Menu, create )(&cfg);
    GLU_FUNC( Menu, insert )(ID_Menu);
    GLU_FUNC( Menu, scroll )(ID_Menu,  1 );
    GLU_FUNC( Menu, scroll )(ID_Menu,  1 );
    
    GLU_FUNC( GUI, refreashEntireScreen )();

#endif
    
#if 1
    ID_t ID_spinbox = 0;
    __GUI_Object_t cfg = {0};
    
    cfg.widget     = kGUI_ObjStyle_spinbox;
    cfg.obj_color  = M_COLOR_WHITE;
    cfg.area.xs    = 10;
    cfg.area.ys    = 10;
    cfg.area.width = 60;
    cfg.area.height= 40;
    cfg.text       = "MHz";
    cfg.text_size  = 8;
    cfg.obj_color  = M_COLOR_WHITE;
    
    __GUI_ObjDataScr_spinbox data = {
        .min = 2400 ,
        .max = 2525 ,
        .step = 1   ,
        .cmd  = 0   ,
        .text_offset = 35,
        .margin      = 3
    };
    
    ID_spinbox = GLU_FUNC( Object, create )( &cfg, &data );
    
    GLU_FUNC( Object, insert )( ID_spinbox );
//    GLU_FUNC( Object, frame  )( ID_spinbox, 1);
    GLU_FUNC( GUI, refreashEntireScreen )();
    
    data.cmd = 1;
    GLU_FUNC( Object, adjust )( ID_spinbox, &data, sizeof(data) );
    GLU_FUNC( GUI, refreashEntireScreen )();
    
    data.cmd = 1;
    GLU_FUNC( Object, adjust )( ID_spinbox, &data, sizeof(data) );
    GLU_FUNC( GUI, refreashEntireScreen )(); // 2402
    
    data.cmd = -1;
    GLU_FUNC( Object, adjust )( ID_spinbox, &data, sizeof(data) );
    GLU_FUNC( GUI, refreashEntireScreen )(); // 2401
    
    data.cmd = -1;
    GLU_FUNC( Object, adjust )( ID_spinbox, &data, sizeof(data) );
    GLU_FUNC( GUI, refreashEntireScreen )(); // 2400
#endif

    return 0;
}




