

    
#include <stdio.h>
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "ssd1306.h"
#ifdef __cplusplcus
extern "C"{
#endif


void API_Init__STM32F103C8T6 (void){
    GUI_API_DrawArea     = SSD1306_API_DrawArea;
    
}


#ifdef __cplusplcus
}
#endif



