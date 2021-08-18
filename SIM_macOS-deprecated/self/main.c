//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/4/7.
//

#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "RH_color.h"

#include "GLU_api.h"
#include "GLU_area.h"

#include "BLK_data.h"


#include "GLU_glucoo.h"
#include "GLU_image.h"
#include "GLU_glucoo.h"

#include "BLK_graphic.h"

#include "BLK_image.h"
#include "BLK_time.h"

#include "BLK_math.h"

extern BLK_TYPE(Canvas) info_MainScreen; //...//

#include <dirent.h>



int main(int argc, const char * argv[]) {
    GLU_API_init();
    GLU_GUI_init();
    
    printf("%ld\n", BLK_Math_gcd( 280, 480 ));
    
    RH_RECORD_TIME(BLK_Math_combinatorial(41, 12), printf);
    
    
//    BLK_Math_lcm();
    printf("%ld\n", BLK_Math_combinatorial(41, 12));
    
    return 0;
}




