//
//  main.c
//  XCode_11.1
//
//  Created by Randle Helmslay on 2021/2/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include "RH_Utility.h"
#include "RH_GUI.h"
#include "API.h"



#if 1
int main(int argc, const char * argv[]) {
    // insert code here...

    Simul_API_Init();
    GUI_Init();

    GUI_ManualDisplayMode();

    return 0;
}


#endif
