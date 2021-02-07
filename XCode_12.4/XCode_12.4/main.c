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
#include <string.h>
#include <stdlib.h>

static void Simul_DrawArea(int x1,int y1,int x2,int y2,const Pixel_t* pixData){
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

static void Simul_AssertParam(bool expression,const char* WHAT_IS_WRONG){
    printf("%s\n",WHAT_IS_WRONG);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    GUI_API_DrawArea     = Simul_DrawArea;
    GUI_API_AssertParam  = Simul_AssertParam;
    
    GUI_Init();
    GUI_ManualDisplayMode();
    
     GUI_SetPenColor(GUI_RED);
     GUI_FillCircle(GUI_X_WIDTH>>1, GUI_Y_WIDTH>>1, 50);
     GUI_RefreashScreen();
    
     GUI_SetPenColor(GUI_GREEN);
     GUI_FillRect(GUI_X_WIDTH/3, GUI_Y_WIDTH/6, GUI_X_WIDTH/2, GUI_Y_WIDTH/4);
     GUI_RefreashScreen();
    
     GUI_SetPenColor(GUI_YELLOW);
     GUI_DrawLine(10, 10, 50, 100);
     GUI_RefreashScreen();
//    GUI_SetPenSize(1);
//    GUI_DrawLine(120, 20, 9, 114);
//    GUI_RefreashScreen();
    
    __UNION_PixelRGB888_t  img[128][128] = {0};
    img[39][42].R = 1;
    img[40][42].G = 1;
    img[41][42].B = 1;
    
    int xs = 42;
    int ys = 39;
    int xe = 52;
    int ye = 48;
    int width   = xe-xs+1;
    int height  = ye-ys+1;
    __UNION_PixelRGB888_t* out  = (__UNION_PixelRGB888_t*)__malloc( (height)*(width)*sizeof(__UNION_PixelRGB888_t) );
    
    __memgrab_Area(out, img, sizeof(__UNION_PixelRGB888_t), 128, xs, ys, xe, ye);
    
    for(int y=ys;y<=ye;y++){
        for(int x=xs;x<=xe;x++){
            printf("[(%2d,%2d)%d%d%d] ",y-ys,x-xs,out[(y-ys)*width+(x-xs)].R,out[(y-ys)*width+(x-xs)].G,out[(y-ys)*width+(x-xs)].B);
        }
        printf("\n");
    }

    printf("\n");
    for(int y=ys;y<=ye;y++){
        for(int x=xs;x<=xe;x++){
            printf("[(%d,%d)%d%d%d] ",y,x,img[y][x].R,img[y][x].G,img[y][x].B);
        }
        printf("\n");
    }
    
    printf("Hello, World!\n");
    return 0;
}
