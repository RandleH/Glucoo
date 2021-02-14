//
//  main.c
//  XCode_12.4
//
//  Created by Randle Helmslay on 2021/2/7.
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
    GUI_SetPenColor(GUI_COLOR_RED);
    GUI_SetPenSize(3);
    const int width = 20;
    GUI_FillRect( 0         , 0, width * 1  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_PINK             );
    GUI_FillRect( width * 1 , 0, width * 2  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_CRIMSON          );
    GUI_FillRect( width * 2 , 0, width * 3  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_LAVENDERBLUSH    );
    GUI_FillRect( width * 3 , 0, width * 4  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_PALEVIOLATRED    );
    GUI_FillRect( width * 4 , 0, width * 5  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_HOTPINK          );
    GUI_FillRect( width * 5 , 0, width * 6  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_MEDIUMVIOLATRED  );
    GUI_FillRect( width * 6 , 0, width * 7  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_ORCHID           );
    GUI_FillRect( width * 7 , 0, width * 8  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_THISTLE          );
    GUI_FillRect( width * 8 , 0, width * 9  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_PLUM             );
    GUI_FillRect( width * 9 , 0, width * 10 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_VOILET           );
    GUI_FillRect( width * 10, 0, width * 11 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_DARKVOILET       );
    GUI_FillRect( width * 11, 0, width * 12 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_PURPLE           );
    GUI_FillRect( width * 12, 0, width * 13 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_MEDIUMORCHID     );
    GUI_FillRect( width * 13, 0, width * 14 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_DARKVIOLET       );
    GUI_FillRect( width * 14, 0, width * 15 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_INDIGO           );
    GUI_FillRect( width * 15, 0, width * 16 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_BLUEVIOLET       );
    GUI_FillRect( width * 16, 0, width * 17 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_MEDIUMPURPLE     );
    GUI_FillRect( width * 17, 0, width * 18 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_MEDIUMSLATEBLUE  );
    GUI_FillRect( width * 18, 0, width * 19 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_SLATEBLUE        );
    GUI_FillRect( width * 19, 0, width * 20 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_DARKSLATEBLUE    );
    GUI_FillRect( width * 20, 0, width * 21 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_LAVENDER         );
    GUI_FillRect( width * 21, 0, width * 22 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_GHOSTWHITE       );
    GUI_FillRect( width * 22 ,0, width * 23 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_MEDIUMBLUE       );
    GUI_FillRect( width * 23, 0, width * 24 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_MIDNIGHTBLUE     );
    GUI_FillRect( width * 24, 0, width * 25 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_DARKBLUE         );
    GUI_FillRect( width * 25, 0, width * 26 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_NAVY             );
    GUI_FillRect( width * 26, 0, width * 27 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_ROYALBLUE        );
    GUI_FillRect( width * 27, 0, width * 28 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_CORNFLOWERBLUE   );
    GUI_FillRect( width * 28, 0, width * 29 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_LIGHTSTEELBLUE   );
    GUI_FillRect( width * 29, 0, width * 30 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_LIGHTSLATEGRAY   );
    GUI_FillRect( width * 30, 0, width * 31 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_SLATEGRAY        );
    GUI_FillRect( width * 31, 0, width * 32 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_DODGERBLUE       );
    GUI_FillRect( width * 32, 0, width * 33 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_ALICEBLUE        );
    GUI_FillRect( width * 33, 0, width * 34 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_STEELBLUE        );
    GUI_FillRect( width * 34, 0, width * 35 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_LIGHTSKYBLUE     );
    GUI_FillRect( width * 35, 0, width * 36 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_SKYBLUE          );
    GUI_FillRect( width * 36, 0, width * 37 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_DEEPSKYBLUE      );
    GUI_FillRect( width * 37, 0, width * 38 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_LIGHTBLUE        );
    GUI_FillRect( width * 38, 0, width * 39 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_POWDERBLUE       );
    GUI_FillRect( width * 39, 0, width * 40 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_COLOR_CADETBLUE        );
    
    GUI_BlurRoundCornerRect(18 , 20, 200, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(230, 20, 400, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(440, 20, 550, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(600, 20, 700, 200, 17U, 60000U, 40U);
    GUI_BlurRoundCornerRect(18 ,230, 700, 450, 17U, 60000U, 40U);
    
    GUI_RefreashScreen();
    
    
//    __UNION_PixelRGB888_t in_[6][6] = {
//        {{.R =  90},{.R = 100},{.R = 100},{.R =  90},{.R = 100},{.R = 100}},
//        {{.R = 100},{.R = 120},{.R =  80},{.R = 100},{.R = 120},{.R = 100}},
//        {{.R = 100},{.R =  20},{.R = 100},{.R = 100},{.R = 120},{.R = 100}},
//        {{.R =  90},{.R = 100},{.R = 100},{.R =  90},{.R = 100},{.R = 100}},
//        {{.R = 100},{.R = 120},{.R =  70},{.R = 100},{.R = 120},{.R = 100}},
//        {{.R = 100},{.R =  20},{.R = 100},{.R = 100},{.R = 120},{.R = 100}},
//    };
//    __UNION_PixelRGB888_t out_[6][6] = {0};
//
//    __ImageRGB888_t in = {
//        .pBuffer = in_[0],
//        .width   = 6,
//        .height  = 6
//    };
//
//    __ImageRGB888_t out = {
//        .pBuffer = out_[0],
//        .width   = 6,
//        .height  = 6
//    };
    
//    __Blur_Average_ImgRGB888(&in,&out,3,100);
    
//    for(int y=0;y<6;y++){
//        for(int x=0;x<6;x++){
//            printf(" %3d ",out.pBuffer[y*(6)+x].R);
//        }
//        printf("\n");
//    }
    
    
    
    
    
    return 0;
}


#endif
