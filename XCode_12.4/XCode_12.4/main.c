//
//  main.c
//  XCode_12.4
//
//  Created by Randle Helmslay on 2021/2/7.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <limits.h>
#include <stdio.h>
#include "../../RH_Utility.h"
#include "../../RH_GUI.h"
#include "../../API.h"



void MAKE_FUNC( __LINK , create) (void){
    
}

#if 1
int main(int argc, const char * argv[]) {
    // insert code here...

//    Simul_API_Init();
//    GUI_Init();
    
    __LinkLoopNode *pHead = NULL;
    __LinkLoopNode *P1,*P2,*P3,*P4,*P5,*P6;
    
    __LINK_Loop_createHeadNode(&pHead);
    __LINK_Loop_createNode(&P1);
    __LINK_Loop_createNode(&P2);
    __LINK_Loop_createNode(&P3);
    __LINK_Loop_createNode(&P4);
    __LINK_Loop_createNode(&P5);
    __LINK_Loop_createNode(&P6);
    
    __LINK_Loop_addNode_tail(&pHead, &P1);
    __LINK_Loop_addNode_tail(&pHead, &P3);
    __LINK_Loop_addNode_tail(&pHead, &P5);
    __LINK_Loop_addNode_tail(&pHead, &P4);
    __LINK_Loop_addNode_tail(&pHead, &P2);
    __LINK_Loop_removeNode(&pHead, &P3);
    __LINK_Loop_addNode_front(&pHead, &P3);
    __LINK_Loop_printAllNodesAdr(&pHead, printf);
    
    return 0;
}


#endif
