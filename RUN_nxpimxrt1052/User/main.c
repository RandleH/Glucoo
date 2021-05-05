
#include <stdio.h>

#include "fsl_debug_console.h"
#include "fsl_elcdif.h"


#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "./led/bsp_led.h" 
#include "./lcd/bsp_lcd.h" 
#include "./systick/bsp_systick.h"

#include "RH_gui.h"
#include "RH_color.h"

extern void LCD_Test(void);


int main(void)
{

    BOARD_ConfigMPU();

    BOARD_InitPins();

    BOARD_BootClockRUN();

    BOARD_InitDebugConsole();


    LED_GPIO_Config();

    SysTick_Init();
    
    LCD_Init(LCD_INTERRUPT_ENABLE);

    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_WHITE);

    extern pixel_t s_psBufferLcd[2][LCD_PIXEL_HEIGHT][LCD_PIXEL_WIDTH];

    RGB_LED_COLOR_RED;
    LCD_Clear(CL_RED);
    GUI_rect_round (100,200,400,300 );
    GUI_rect_fill  ( 40, 40, 80, 80 );



    while(1){
        s_psBufferLcd[0][40][40] = M_COLOR_BLUE;
    }
}


