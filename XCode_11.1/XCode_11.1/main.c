//
//  main.c
//  XCode_11.1
//
//  Created by Randle Helmslay on 2021/2/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include "../../RH_Utility.h"
#include "../../RH_GUI.h"
#include "../../API.h"



#if 1
int main(int argc, const char * argv[]) {
    // insert code here...

//    Simul_API_Init();
//    GUI_Init();
    
    const char* __restrict__ src  = "/Users/randle_h/desktop/lenna.bmp";
    const char* __restrict__ des  = "/Users/randle_h/desktop/lenna_.bmp";

    __ImageRGB888_t* IMG_IN  = __LoadBMP_ImgRGB888(src);

    __ImageRGB888_t* IMG_OUT = __Create_ImgRGB888(IMG_IN->width, IMG_IN->height);
    __Filter_OTUS_ImgRGB888(IMG_IN, IMG_OUT, 100);
    __OutBMP_ImgRGB888(des, IMG_OUT);
    __Free_ImgRGB888(IMG_IN);
    __Free_ImgRGB888(IMG_OUT);
// RH_Dummy.c
// RH_Utility.c
// RH_Utility.h
    
    
    return 0;
}


#endif
