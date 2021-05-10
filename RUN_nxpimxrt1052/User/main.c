
#include <stdio.h>

#include "fsl_debug_console.h"
#include "fsl_elcdif.h"


#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "./led/bsp_led.h" 
#include "./lcd/bsp_lcd.h" 
#include "./systick/bsp_systick.h"
#include "./touch/bsp_touch_gtxx.h"
#include "./touch/bsp_i2c_touch.h"
#include "./delay/core_delay.h"   

#include "RH_gui.h"
#include "RH_color.h"

extern void LCD_Test(void);


int main(void)
{

    BOARD_ConfigMPU();

    BOARD_InitPins();

    BOARD_BootClockRUN();

    BOARD_InitDebugConsole();

    CPU_TS_TmrInit();
    LED_GPIO_Config();

    SysTick_Init();
    GTP_Init_Panel();
    LCD_Init(LCD_INTERRUPT_ENABLE);

    GUI_Init();
    GUI_set_penSize(5);
    GUI_set_penColor(M_COLOR_CYAN);

    extern pixel_t s_psBufferLcd[1][LCD_PIXEL_HEIGHT][LCD_PIXEL_WIDTH];

    RGB_LED_COLOR_RED;
    // LCD_Clear(CL_RED);
    // GUI_rect_round (100,200,400,300 );
    // GUI_rect_fill  ( 40, 40, 80, 80 );


    __Pixel_t p[2] = {M_COLOR_YELLOW,M_COLOR_BLUE};
    int i = 0;
    while(1){
        if(g_TouchPadInputSignal ){
            GTP_TouchProcess();    
            g_TouchPadInputSignal = false;
            if( TouchData.track[0].ID != -1 ){
                GUI_set_penColor(p[i%2]);
                GUI_rect_fill (50,100,500,400 ); 

                s_psBufferLcd[0][100][50] = 0x001f;
                s_psBufferLcd[0][100][51] = 0x001f;
                s_psBufferLcd[0][100][52] = 0x001f;
                s_psBufferLcd[0][100][53] = 0x001f;
                s_psBufferLcd[0][100][54] = 0x001f;
                PutPixel( 50, 100 );
                i++;
            }
        }
        
        for( uint16_t y=0; y<300; y++ ){
            for( uint16_t x=0; x<5
            00; x++ ){
            
                s_psBufferLcd[0][y][x] = CL_BLUE;
            }
        }
                
        // CPU_TS_Tmr_Delay_MS(100);
    }
}


