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



#if 1
int main(int argc, const char * argv[]) {
    // insert code here...

//    Simul_API_Init();
//    GUI_Init();
    
    __AnyNode_t *pHead = NULL;
    __AnyNode_t *P1,*P2,*P3,*P4,*P5,*P6;
    
    __createHeadNode(&pHead);
    __createNode(&P1);
    __createNode(&P2);
    __createNode(&P3);
    __createNode(&P4);
    __createNode(&P5);
    __createNode(&P6);
    
    __addNode_tail(pHead,P1); P1->object = (void*)"Hello World";
    __addNode_tail(pHead,P2); P2->object = (void*)"Can I help you?";
    __addNode_tail(pHead,P3); P3->object = (void*)"How dare you!";
    __addNode_tail(pHead,P4);
    __addNode_tail(pHead,P5);
    __addNode_tail(pHead,P2);
    __addNode_tail(pHead,P6);
    
//    __deleteNode(pHead, P2);
    
    
    
    printf("%d\n",__findNode(pHead, P2));
    
    __printAllNodesAdr(pHead,printf);
    
    __removeAllNodes(pHead);
    return 0;
}


#endif
