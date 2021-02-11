//
//  main.c
//  XCode_11.1
//
//  Created by Randle Helmslay on 2021/2/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "API.h"
#include "RH_Utility.h"
#include "RH_GUI.h"


#if 1
int main(int argc, const char * argv[]) {
    // insert code here...

    Simul_API_Init();
    GUI_Init();

    GUI_ManualDisplayMode();

    __AnyNode_t* pHead = __createHeadNode(); //pHead->ID = 0;
    __AnyNode_t* p1    = __createNode();     //p1->ID    = 1;
    __AnyNode_t* p2    = __createNode();     //p2->ID    = 2;
    __AnyNode_t* p3    = __createNode();     //p3->ID    = 3;
    __AnyNode_t* p4    = __createNode();
    __AnyNode_t* p5    = __createNode();
    __AnyNode_t* p6    = __createNode();
    __AnyNode_t* p7    = __createNode();
    
    __addNode(pHead, p1);
    __addNode(pHead, p2);
    __addNode(pHead, p3);
    __addNode(pHead, p4);
    __addNode(pHead, p5);
    __addNode(pHead, p6);

    __deleteNode(pHead, p4);
    __deleteNode(pHead, p2);
    __deleteNode(pHead, p6);
    
    __addNode(pHead, p3);
    __addNode(pHead, p3);
    __addNode(pHead, p7);
    __AnyNode_t* pTmp = pHead;
    
    // Search the entire chain.
    do{
        printf("ID = %d\n",pTmp->ID);
        pTmp = pTmp->pNext;
    }while(pTmp != pHead);
    
    return 0;
}


#endif
