

#include "delay.h"
#include "ssd1306.h"
#include "joystick.h"
#include "led.h"
#include "beeper.h"
#include "RH_gui_api.h"
#include "RH_gui.h"
#include "RH_color.h"

int main(void){

    delay_init(72);
    SSD1306_Init();
    JoyStick_Init();
    LED_Init();
    BEEP_Init();
    GUI_API_Init ();
    GUI_Init();

    __GUI_Menu_t cfg = {0};
    
    cfg.area.xs = 10;
    cfg.area.ys = 10;
    cfg.area.height = 50;
    cfg.area.width  = 90;
    cfg.nItem = 10;
    cfg.title = "Title";
    cfg.color_title = M_COLOR_WHITE;
    cfg.size  = 10;
    
    cfg.bk_color = M_COLOR_BLACK;
    cfg.sl_color = M_COLOR_WHITE;
    cfg.text_color = M_COLOR_WHITE;
    
    __GUI_MenuParam_t m[10] = {0};
    m[0].text = "menu_0";
    m[1].text = "menu_1";
    m[2].text = "menu_2";
    m[3].text = "menu_3";
    m[4].text = "menu_4";
    m[5].text = "menu_5";
    m[6].text = "menu_6";
    m[7].text = "menu_7";
    m[8].text = "menu_8";
    m[9].text = "menu_9";
    
    cfg.menuList = m;
    
    ID_t MENU = GUI_menu_create(&cfg);
    GUI_menu_frame( MENU, 1 );
    GUI_menu_insert(MENU);
    GUI_RefreashScreen();

    while(1){
        // GUI_object_adjust(ID_JOY, 2066, 0); 
        // GUI_object_adjust(ID_JOY, joystick_data[0], joystick_data[1]);
        // GUI_object_adjust(ID_NUM_1, joystick_data[0], 0);
        // GUI_object_adjust(ID_NUM_2, joystick_data[1], 0);
        int ans = 0;

        if( joystick_data[1] > 4000 ){
            ans = -1;
        }else if( joystick_data[1] < 1000 ){
            ans = 1;
        }else{
            ans = 0;
        }

        GUI_menu_scroll( MENU, ans );

        GUI_RefreashScreen();
    }

    
}





