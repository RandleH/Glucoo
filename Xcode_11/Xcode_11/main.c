//
//  main.c
//  Xcode_11
//
//  Created by Randle Helmslay on 2021/3/6.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//


#include <stdio.h>
#include "RH_common.h"
#include "RH_lib.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_neuron.h"
#define MAKE_TYPE( file, name )   file##name

typedef uint8_t MAKE_TYPE( __FILE_NAME__, U8 ) ;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    size_t arrPtron[] = {748,15,10};
    __FF_Layer_t* pL_in =  __FF_Net_create( arrPtron, 3 );
    
    printf("%ld\n",pL_in->pNext->object->_nPtrons_thisLayer );

    
    
    return 0;
}
