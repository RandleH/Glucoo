//
//  main.c
//  Xcode_11
//
//  Created by Randle Helmslay on 2021/4/18.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include "GLU_glucoo.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    GLU_FUNC(GUI,init)();
    
    GLU_FUNC(Font,set_style)( kGLU_Font_NewYork_Italic );
    GLU_FUNC(Font,set_size )(23);
    
    GLU_FUNC(Font,out_str_Img)("Hello world.");

    return 0;
}



