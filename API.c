
//
//  API.c
//  XCode_12.4
//
//  Created by Randle Helmslay on 2021/2/8.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//



#ifdef __cplusplcus
extern "C"{
#endif
#include <stdio.h>
#include "RH_Utility.h"
#include "RH_GUI.h"
#include "API.h"

static void Simul_API_DrawArea(int x1,int y1,int x2,int y2,const Pixel_t* pixData){
    const char* dst_path = "/Users/randle_h/desktop/screen.bmp";
    static __ImageRGB888_t* pTmpScreenShot = NULL;
    if( pTmpScreenShot == NULL )
        pTmpScreenShot = __Create_ImgRGB888(GUI_X_WIDTH,GUI_Y_WIDTH);
    const size_t width   = __abs(x2 - x1) + 1;
    const size_t height  = __abs(y2 - y1) + 1;
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            pTmpScreenShot->pBuffer[(y1+y)*GUI_X_WIDTH + (x1+x)].data = pixData[ y*width+x];
        }
    }
    __OutBMP_ImgRGB888(dst_path,pTmpScreenShot);
//    __Free_ImgRGB888(pTmpScreenShot);
}

static void Simul_API_AssertParam(bool expression,const char* WHAT_IS_WRONG){
    printf("%s\n",WHAT_IS_WRONG);
}

void Simul_API_Init(void){
    GUI_API_DrawArea     = Simul_API_DrawArea;
    GUI_API_AssertParam  = Simul_API_AssertParam;
}


#ifdef __cplusplcus
}
#endif
