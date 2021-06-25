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
#include "BLK_data.h"


#include "GLU_glucoo.h"

#include "BLK_poker.h"

#define DICE_NUM_MAX      6
#define DICE_NUM_MIN      1

#define PROJ_MIN(a,b)                           (((a)<(b))?(a):(b))

#define PROJ_MAX(a,b)                           (((a)>(b))?(a):(b))



int main(int argc, const char * argv[]) {

    Simul_API_Init();
    
    GLU_FUNC( GUI, init        )();
    GLU_FUNC( GUI, setPenSize  )(5);
    GLU_FUNC( GUI, setPenColor )(M_COLOR_WHITE);


    printf("%ld\n", BLK_FUNC( Math, combinatorial )( 60, 30 ) );
#if 0
    
    __GUI_Object_t            a    = {0};
    __GUI_ObjDataScr_button   data = {0};
    ID_t                      ID;

    GLU_FUNC(Object,template)( &a, kGUI_ObjStyle_button );
    a.text = "mute";
    a.text_size = 8;
    a.obj_color = M_COLOR_CYAN;
    
    data.active = true;
    data.cmd    = 0;
    data.radius = 3;
    
    ID = GLU_FUNC(Object,create  )( &a, &data );
    
    GLU_FUNC(Object, insert)( ID );
    
    data.cmd = 1;
    GLU_FUNC(Object, adjust)( ID, &data, sizeof(data) );
    
    data.cmd = 0;
    GLU_FUNC(Object, adjust)( ID, &data, sizeof(data) );

    data.cmd = 1;
    GLU_FUNC(Object, adjust)( ID, &data, sizeof(data) );
    
    GLU_FUNC( GUI, refreashScreen )();
    
#endif

    return 0;
}




