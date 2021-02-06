//
//  main.c
//  XCode_11.1
//
//  Created by Randle Helmslay on 2021/2/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//


#include "RH_Utility.h"
#include "RH_GUI.h"
#include <stdio.h>


static void Simul_DrawArea(int x1,int y1,int x2,int y2,const Pixel_t* pixData){
    const char* dst_path = "/Users/randle_h/Desktop/screen.bmp";
    static __ImageRGB888_t* pTmpScreenShot = NULL;
    if( pTmpScreenShot == NULL )
        pTmpScreenShot = __Create_ImgRGB888(GUI_X_WIDTH,GUI_Y_WIDTH);
    const size_t width   = __abs(x2 - x1) + 1;
    const size_t height  = __abs(y2 - y1) + 1;
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            pTmpScreenShot->pBuffer[(y1+y)*GUI_X_WIDTH + (x1+x)].data = pixData[ y*height+x];
        }
    }
    __OutBMP_ImgRGB888(dst_path,pTmpScreenShot);
//    __Free_ImgRGB888(pTmpScreenShot);
}

static void Simul_AssertParam(bool expression,const char* WHAT_IS_WRONG){
    printf("%s\n",WHAT_IS_WRONG);
}

union TT_t{
    struct{
        uint8_t B : 8;
        uint8_t G : 8;
        uint8_t R : 8;
    };
    uint32_t data;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    GUI_API_DrawArea     = Simul_DrawArea;
    GUI_API_AssertParam  = Simul_AssertParam;
    GUI_Init();
    GUI_ManualDisplayMode();
    GUI_SetPenColor(GUI_RED);
    GUI_FillCircle(200, 400, 40);
    GUI_RefreashScreen();
//    GUI_SetPenSize(1);
//    GUI_DrawLine(120, 20, 9, 114);
//    GUI_RefreashScreen();
    
    printf("Hello, World!\n");
    return 0;
}
