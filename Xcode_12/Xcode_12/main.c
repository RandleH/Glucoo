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
#include "RH_graphic.h"



int main(int argc, const char * argv[]) {
    // insert code here...
    
    Simul_API_Init();
    
    __UNION_PixelBIN_t GRAM[3][ GUI_Y_WIDTH>>3 ][ GUI_X_WIDTH ] = {0};
    
    __GraphInfo_t GInfo = {
        .pBuffer = GRAM[0][0]  ,
        .height  = GUI_Y_WIDTH ,
        .width   = GUI_X_WIDTH
    };
    
//    __Graph_rect_raw( 30, 30, 80, 50, &GInfo, kApplyPixel_fill );
//    __Graph_rect_fill(30, 30, 80, 50, &GInfo, kApplyPixel_fill );
//    __Graph_line_raw (30, 30, 80, 50, &GInfo, kApplyPixel_fill );
//    __Graph_circle_raw(45, 32, 20, &GInfo, kApplyPixel_fill );
//    __Graph_circle_fill(45, 32, 40, &GInfo, kApplyPixel_fill );
//    __Graph_circle_edged(45, 32, 40, &GInfo, kApplyPixel_fill );
    __Graph_set_penSize(10);
    __Graph_line_sausage(30, 30, 80, 50, &GInfo, kApplyPixel_fill );
//    __Graph_line_fill(30, 30, 80, 50, &GInfo, kApplyPixel_fill );
 

    GUI_RefreashScreenArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
    

    
    __ImgBIN_out_bmp("/Users/randle_h/desktop/BIN4.bmp", &GInfo);
    
    return 0;
}


