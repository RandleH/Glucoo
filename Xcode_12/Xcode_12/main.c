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
#include "RH_neuron.h"
#include "RH_time.h"

int main(int argc, const char * argv[]) {
    // insert code here...
#pragma pack(1)
    struct Dummy_t{
        struct{
            uint8_t  a;
            uint32_t b;
            void*    p;
        }*object;
        uint8_t      d;
    }test;
    
    test.object = NULL;
    
    printf("%ld\n",sizeof( *(test.object) ));
    
    
    __ImgRGB888_load_png("/Users/randle_h/desktop/pig.png");
    
    
    return 0;
}


