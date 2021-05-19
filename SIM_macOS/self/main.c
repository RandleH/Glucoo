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




