//
//  main.c
//  XCode_11.1
//
//  Created by Randle Helmslay on 2021/2/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "API.h"
#include "RH_Utility.h"
#include "RH_GUI.h"



int main(int argc, const char * argv[]) {
    // insert code here...

    Simul_API_Init();
    GUI_Init();
    
    GUI_ManualDisplayMode();
    
    GUI_SetPenColor(GUI_RED);
    GUI_FillCircle(GUI_X_WIDTH>>1, GUI_Y_WIDTH>>1, 50);
    GUI_RefreashScreen();

    GUI_SetPenColor(GUI_GREEN);
    GUI_FillRect(GUI_X_WIDTH/3, GUI_Y_WIDTH/6, GUI_X_WIDTH/2, GUI_Y_WIDTH/4);
    GUI_RefreashScreen();

    GUI_SetPenColor(GUI_YELLOW);
    GUI_SetPenSize(10);

    int ox = 30,oy = 30;
    GUI_DrawLine(10+ox, 10+oy, 50+ox, 50+oy);
    GUI_DrawLine(50+ox, 10+oy, 10+ox, 50+oy);
    GUI_DrawLine(30+ox, 10+oy, 30+ox, 50+oy);
    GUI_DrawLine(10+ox, 30+oy, 50+ox, 30+oy);

    GUI_SetPenSize(3);GUI_SetPenColor(GUI_PINK);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(4);GUI_SetPenColor(GUI_CRIMSON);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(5);GUI_SetPenColor(GUI_LAVENDERBLUSH);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(6);GUI_SetPenColor(GUI_PALEVIOLATRED);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(7);GUI_SetPenColor(GUI_HOTPINK);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(8);GUI_SetPenColor(GUI_MEDIUMVIOLATRED);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(9);GUI_SetPenColor(GUI_ORCHID);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(10);GUI_SetPenColor(GUI_THISTLE);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(11);GUI_SetPenColor(GUI_PLUM);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(12);GUI_SetPenColor(GUI_VOILET);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(13);GUI_SetPenColor(GUI_DARKVOILET);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(14);GUI_SetPenColor(GUI_PURPLE);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(15);GUI_SetPenColor(GUI_PALETURQUOISE);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_RefreashScreen();
    
    printf("Hello, World! 0x%x\n",GUI_MAKE_COLOR(255,240,245));
    return 0;
}
