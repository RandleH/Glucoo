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

int main(int argc, const char * argv[]) {
    // insert code here...

    __ImageBIN_t* p = __ImgBIN_load_bmp("/Users/randle_h/desktop/BIN5.bmp");
    
    __ImgBIN_out_bmp("/Users/randle_h/desktop/BIN4.bmp", p);
    
    return 0;
}


