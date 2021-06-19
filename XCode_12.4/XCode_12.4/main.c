//
//  main.c
//  XCode_12.4
//
//  Created by Randle.Helmslay on 2021/2/18.
//

#include <stdio.h>
#include "RH_data.h"
#include "RH_GUI.h"
#include "API.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();
    GUI_Init();
    
    GUI_SetPenColor(GUI_COLOR_RED);
    GUI_AutoDisplayMode();
    GUI_FillAll(GUI_COLOR_SILVER);
    GUI_SetBlurMethod(GUI_BLUR_Average);
    GUI_BlurRoundCornerRect(100, 100, 600, 300, 30U, 60000U, 70U);
    
    GUI_SetPenSize(14);
//    GUI_DrawLine(200, 300, 492, 90);
//
//    GUI_DrawLine(100, 100, 200, 200);
//    GUI_DrawLine(200, 100, 100, 200);
//    GUI_DrawLine(150, 100, 150, 200);
//    GUI_DrawLine(100, 150, 200, 150);
//
//
//    GUI_DrawLine(200, 200, 200-50, 200+50 );
//    GUI_DrawLine(200, 200, 200+50, 200+50 );
    struct  GUI_IconConfig_t icon1 = {
        .x_pos = 90,
        .y_pos = 90,
        .size  = 140,
        .GUI_ICON_xxxx = GUI_ICON_WIN10,
        .ID = 0x01 ,
        .themeColor = GUI_COLOR_WHITE,
        .dispFrame = true
    };
    
    GUI_CreateIconSocket(&icon1);
    GUI_ShowIcon(0x01);
    
    printf("Hello, World!\n");
    return 0;
}
