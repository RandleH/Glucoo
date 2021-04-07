
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
    GUI_set_penSize(5);
    
    __GUI_Window_t cfg;
    GUI_easySet_window(&cfg);
    cfg.area.xs     = 10;
    cfg.area.ys     = 10;
    cfg.area.height = 60;
    cfg.area.width  = 100;
    cfg.type        = kGUI_WindowType_macOS;
    cfg.size        = 15;
    cfg.appearance  = kGUI_Appearance_Light;
    cfg.title       = NULL;
    cfg.text        = "Hello world";
    cfg.text_size   = 8;

    ID_t ID_Window1 = GUI_create_window(&cfg);
    GUI_insert_window( ID_Window1 );

    GUI_RefreashScreen();

    while(1);	
}




