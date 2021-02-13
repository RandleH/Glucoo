//
//  main.c
//  XCode_11.1
//
//  Created by Randle Helmslay on 2021/2/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include "RH_Utility.h"
#include "RH_GUI.h"
#include "API.h"



#if 1
int main(int argc, const char * argv[]) {
    // insert code here...

    Simul_API_Init();
    GUI_Init();

    GUI_ManualDisplayMode();
    GUI_SetPenColor(GUI_RED);
    GUI_SetPenSize(3);
//    GUI_Debug();
    const int width = 20;
    GUI_FillRect( 0         , 0, width * 1  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PINK             );
    GUI_FillRect( width * 1 , 0, width * 2  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_CRIMSON          );
    GUI_FillRect( width * 2 , 0, width * 3  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LAVENDERBLUSH    );
    GUI_FillRect( width * 3 , 0, width * 4  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PALEVIOLATRED    );
    GUI_FillRect( width * 4 , 0, width * 5  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_HOTPINK          );
    GUI_FillRect( width * 5 , 0, width * 6  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMVIOLATRED  );
    GUI_FillRect( width * 6 , 0, width * 7  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_ORCHID           );
    GUI_FillRect( width * 7 , 0, width * 8  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_THISTLE          );
    GUI_FillRect( width * 8 , 0, width * 9  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PLUM             );
    GUI_FillRect( width * 9 , 0, width * 10 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_VOILET           );
    GUI_FillRect( width * 10, 0, width * 11 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKVOILET       );
    GUI_FillRect( width * 11, 0, width * 12 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PURPLE           );
    GUI_FillRect( width * 12, 0, width * 13 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMORCHID     );
    GUI_FillRect( width * 13, 0, width * 14 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKVIOLET       );
    GUI_FillRect( width * 14, 0, width * 15 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_INDIGO           );
    GUI_FillRect( width * 15, 0, width * 16 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_BLUEVIOLET       );
    GUI_FillRect( width * 16, 0, width * 17 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMPURPLE     );
    GUI_FillRect( width * 17, 0, width * 18 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMSLATEBLUE  );
    GUI_FillRect( width * 18, 0, width * 19 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_SLATEBLUE        );
    GUI_FillRect( width * 19, 0, width * 20 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKSLATEBLUE    );
    GUI_FillRect( width * 20, 0, width * 21 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LAVENDER         );
    GUI_FillRect( width * 21, 0, width * 22 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_GHOSTWHITE       );
    GUI_FillRect( width * 22 ,0, width * 23 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMBLUE       );
    GUI_FillRect( width * 23, 0, width * 24 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MIDNIGHTBLUE     );
    GUI_FillRect( width * 24, 0, width * 25 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKBLUE         );
    GUI_FillRect( width * 25, 0, width * 26 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_NAVY             );
    GUI_FillRect( width * 26, 0, width * 27 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_ROYALBLUE        );
    GUI_FillRect( width * 27, 0, width * 28 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_CORNFLOWERBLUE   );
    GUI_FillRect( width * 28, 0, width * 29 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTSTEELBLUE   );
    GUI_FillRect( width * 29, 0, width * 30 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTSLATEGRAY   );
    GUI_FillRect( width * 30, 0, width * 31 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_SLATEGRAY        );
    GUI_FillRect( width * 31, 0, width * 32 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DODGERBLUE       );
    GUI_FillRect( width * 32, 0, width * 33 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_ALICEBLUE        );
    GUI_FillRect( width * 33, 0, width * 34 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_STEELBLUE        );
    GUI_FillRect( width * 34, 0, width * 35 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTSKYBLUE     );
    GUI_FillRect( width * 35, 0, width * 36 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_SKYBLUE          );
    GUI_FillRect( width * 36, 0, width * 37 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DEEPSKYBLUE      );
    GUI_FillRect( width * 37, 0, width * 38 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTBLUE        );
    GUI_FillRect( width * 38, 0, width * 39 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_POWDERBLUE       );
    GUI_FillRect( width * 39, 0, width * 40 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_CADETBLUE        );

//    GUI_BlurRect(20, 20, 200, 200, 60000, 60);
    GUI_BlurRoundCornerRect(18 , 20, 200, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(230, 20, 400, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(440, 20, 550, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(600, 20, 700, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(18 ,230, 700, 450, 17U, 60000U, 40U);
    GUI_RefreashScreen();
    
    return 0;
}


#endif
