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
#include "BLK_time.h"

#define DICE_NUM_MAX      6
#define DICE_NUM_MIN      1

#define PROJ_MIN(a,b)                           (((a)<(b))?(a):(b))

#define PROJ_MAX(a,b)                           (((a)>(b))?(a):(b))

size_t
GLU_FUNC( Font, out_ttf_array )( const char* ttf_path, const char* dst );

int main(int argc, const char * argv[]) {

    Simul_API_Init();

    GLU_FUNC( GUI, init        )();
    GLU_FUNC( GUI, setPenSize  )(5);
    GLU_FUNC( GUI, setPenColor )(M_COLOR_WHITE);
    
    printf("%ld\n", GLU_FUNC( Font, out_ttf_array )( "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/NewYorkItalic.ttf"     ,\
                                                     "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/GLU_font_NewYork_Italic.c" ) );
    
#if 0
    
    __GUI_Object_t a  = {0};
    ID_t           id = 0;
    
    GLU_FUNC(Object, template)( &a, kGUI_ObjStyle_text );
    
    a.font = kGUI_FontStyle_Unscii;
    a.area.width = 34;
    
    id = GLU_FUNC(Object,create  )( &a, NULL );
    GLU_FUNC(Object, insert)( id );
    
    GLU_FUNC( GUI, refreashScreen )();
    
#endif

    return 0;
}




