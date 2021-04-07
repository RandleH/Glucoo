

    
#include <stdio.h>
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "ssd1351.h"
#ifdef __cplusplcus
extern "C"{
#endif


void API_Init__STM32F407RCT6 (void){
    GUI_API_DrawArea     = SSD1351_API_DrawArea;
    
}


#ifdef __cplusplcus
}
#endif



