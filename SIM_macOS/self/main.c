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
    ID_t ID_spinbox[5] = {0};
    __GUI_Object_t cfg = {0};
    
    cfg.widget     = kGUI_ObjStyle_spinbox;
    cfg.obj_color  = M_COLOR_WHITE;
    cfg.area.width = 23;
    cfg.area.height= 30;
    cfg.area.xs    = (int)((RH_CFG_SCREEN_WIDTH - 5*cfg.area.width)>>1);
    cfg.area.ys    = 20;
    
    cfg.text       = NULL;
    cfg.text_size  = 8;
    cfg.obj_color  = M_COLOR_WHITE;
    
    __GUI_ObjDataScr_spinbox data = {
        .min         = 0 ,
        .max         = 255 ,
        .value       = 233,
        .text_offset = cfg.area.width,
        .margin      = 2 ,
        .active      = true
    };
    
    
    
    
    ID_spinbox[0] = GLU_FUNC( Object, create )( &cfg, &data );
    cfg.area.xs += cfg.area.width;
    data.active = false;
    ID_spinbox[1] = GLU_FUNC( Object, create )( &cfg, &data );
    cfg.area.xs += cfg.area.width;
    ID_spinbox[2] = GLU_FUNC( Object, create )( &cfg, &data );
    cfg.area.xs += cfg.area.width;
    ID_spinbox[3] = GLU_FUNC( Object, create )( &cfg, &data );
    cfg.area.xs += cfg.area.width;
    ID_spinbox[4] = GLU_FUNC( Object, create )( &cfg, &data );
    cfg.area.xs += cfg.area.width;
    
    GLU_FUNC( Object, insert )( ID_spinbox[0] );
    GLU_FUNC( Object, insert )( ID_spinbox[1] );
    GLU_FUNC( Object, insert )( ID_spinbox[2] );
    GLU_FUNC( Object, insert )( ID_spinbox[3] );
    GLU_FUNC( Object, insert )( ID_spinbox[4] );
//    GLU_FUNC( Object, frame  )( ID_spinbox, 1);
    GLU_FUNC( GUI, refreashEntireScreen )();
    

#endif

    return 0;
}




