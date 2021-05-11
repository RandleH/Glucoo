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


int main(int argc, const char * argv[]) {
//    printf("%f\n",hypotf(64,128));
    Simul_API_Init();

    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_WHITE);
    
#if 1
    const char* pStrs[] = {
        "Jd" , // Jade
        "Gs" , // Ginseng
        "Sl" , // Silk
        "Ng"   // Nutmeg
    };
    
    ID_t ID_BoatStatus[3] = {0};
    ID_t ID_CargoName[3]  = {0};
    ID_t ID_DiceRound     = {0};
    __GUI_Object_t cfg = {0};

    GUI_object_template( &cfg, kGUI_ObjStyle_trunk );
    cfg.obj_color  = M_COLOR_AQUA;
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
    
    __GUI_ObjDataScr_barV data = {
        .min   = 0,
        .max   = 14,
        .value = 2
    };
    GUI_object_adjust( ID_BoatStatus[0], &data, sizeof(data));
    
    data.value = 14;
    GUI_object_adjust( ID_BoatStatus[1], &data, sizeof(data));

    data.value = 11;
    GUI_object_adjust( ID_BoatStatus[2], &data, sizeof(data));

    GUI_set_penColor(M_COLOR_AQUA);
    GUI_line_raw(67, 7, 67, 57);

    GUI_object_template(&cfg, kGUI_ObjStyle_text);
    cfg.area.xs     = 10;
    cfg.area.ys     = 52;
    cfg.area.height = 12;
    cfg.area.width  = 14;
    cfg.text        = pStrs[0];
    cfg.showFrame   = true;
    cfg.obj_color   = M_COLOR_AQUA;
    ID_CargoName[0] = GUI_object_create( &cfg );

    cfg.text = pStrs[1];
    cfg.area.xs += cfg.area.width +2;
    ID_CargoName[1] = GUI_object_create( &cfg );

    cfg.text = pStrs[2];
    cfg.area.xs += cfg.area.width +2;
    ID_CargoName[2] = GUI_object_create( &cfg );
    GUI_object_insert( ID_CargoName[0] );
    GUI_object_insert( ID_CargoName[1] );
    GUI_object_insert( ID_CargoName[2] );
    GUI_object_frame(ID_BoatStatus[0], true);
    
    cfg.text        = "Round:";
    cfg.area.xs     = 76;
    cfg.area.ys     = 10;
    cfg.area.height = 11;
    cfg.area.width  = strlen(cfg.text)*6+2;
    cfg.showFrame   = false;
    ID_DiceRound    = GUI_object_create( &cfg );
    GUI_object_insert( ID_DiceRound );
    
    GUI_RefreashEntireScreen();
#endif

    return 0;
}




