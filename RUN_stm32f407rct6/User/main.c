
#include <stdbool.h>

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "system_stm32f4xx.h"
#include "delay.h"

#include "ssd1351.h"

#include "RH_gui.h"
#include "RH_gui_api.h"

void GUI_AssertParam(bool expression,const char* WHAT_IS_WRONG){
    if(!expression)
        while(1);
}

void BOARD_LED(void){
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_13 ;
    GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}



#include <stdlib.h>
#include <string.h>
#include <math.h>



int main(void)
{
    SystemInit();
    delay_init(168);
    BOARD_LED();
 
    SSD1351_Init();
    SSD1351_Clean();
    API_Init__STM32F407RCT6();

    GUI_Init();

    __GUI_Object_t cfg_obj = {0};

    GUI_object_quickSet(&cfg_obj);

    cfg_obj.style       = kGUI_ObjStyle_num;
    cfg_obj.area.xs     = 30;
    cfg_obj.area.ys     = 30;
    cfg_obj.area.height = 12;
    cfg_obj.area.width  = 70;
    cfg_obj.min         = 0;
    cfg_obj.max         = 256;
    cfg_obj.font        = kGUI_FontStyle_ArialRounded_Bold;
    cfg_obj.text_color  = M_COLOR_RED;
    cfg_obj.text        = "size:";
    cfg_obj.text_size   = 8;
    cfg_obj.text_align  = kGUI_FontAlign_Left;
    cfg_obj.showFrame   = false;
    
    cfg_obj.bk_color    = M_COLOR_TAN;

    cfg_obj.val         = 129;
    
    ID_t ID_Obj1 = GUI_object_create( &cfg_obj );
    GUI_object_insert(ID_Obj1);
    GUI_object_frame(ID_Obj1,true);
    
    
    
    
    
    
    GUI_RefreashScreen();

    while(1){
        for( int i=0; i<128; i++ )
            GUI_object_adjust(ID_Obj1, i);
    }
}




