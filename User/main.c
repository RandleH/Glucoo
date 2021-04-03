

#include "delay.h"
#include "ssd1306.h"
#include "RH_gui_api.h"
#include "RH_gui.h"

int main(void){

    delay_init(72);
    SSD1306_Init();

    API_Init__STM32F103C8T6 ();
    
    delay_ms(10);
    SSD1306_Clean();
    
    GUI_Init();
    GUI_rect_raw( 30, 30, 50, 50 );
    GUI_RefreashScreen();

    while(1);

}



