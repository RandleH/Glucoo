//
//  main.c
//  XCode_12.4
//
//  Created by Randle.Helmslay on 2021/2/18.
//

#include <stdio.h>
#include "RH_data.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    __LinkBiTreeNode *PH,*P1,*P2,*P3,*P4;
    __LINK_BiTree_createHeadNode(&PH);
    __LINK_BiTree_createNode(&P1);
    __LINK_BiTree_createNode(&P2);
    __LINK_BiTree_createNode(&P3);
    __LINK_BiTree_createNode(&P4);
    
    printf("%d\n",__LINK_BiTree_addNode_l2r(&PH, &PH, &P1));
    printf("%d\n",__LINK_BiTree_addNode_l2r(&PH, &P1, &P2));
    printf("%d\n",__LINK_BiTree_addNode_r2l(&PH, &P2, &P3));
    
    printf("%d\n",__LINK_BiTree_findNode(&PH, &P3));
    
    
    return 0;
}
