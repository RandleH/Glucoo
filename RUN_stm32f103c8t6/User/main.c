

#include "delay.h"
#include "ssd1306.h"
#include "joystick.h"
#include "RH_gui_api.h"
#include "RH_gui.h"
#include "RH_color.h"

int main(void){

    delay_init(72);
    SSD1306_Init();
    JoyStick_Init();

    API_Init__STM32F103C8T6 ();
    
    delay_ms(10);
    SSD1306_Clean();
    

    GUI_Init();

    __GUI_Object_t cfg_obj = {0};

    GUI_object_quickSet(&cfg_obj);

    cfg_obj.style       = kGUI_ObjStyle_num;
    cfg_obj.area.xs     = 10;
    cfg_obj.area.ys     = 10;
    cfg_obj.area.height = 12;
    cfg_obj.area.width  = 30;
    cfg_obj.min         = 0;
    cfg_obj.max         = 4096;
    cfg_obj.font        = kGUI_FontStyle_ArialRounded_Bold;
    cfg_obj.text_color  = M_COLOR_WHITE;
    cfg_obj.text        = "size:";
    cfg_obj.text_size   = 8;
    cfg_obj.text_align  = kGUI_FontAlign_Middle;
    cfg_obj.showFrame   = true;
    cfg_obj.bk_color    = M_COLOR_BLACK;
    cfg_obj.val         = 0;
    
    ID_t ID_NUM_1       = GUI_object_create( &cfg_obj );
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_NUM_2       = GUI_object_create( &cfg_obj );

    cfg_obj.style       = kGUI_ObjStyle_barH;
    cfg_obj.area.xs    += cfg_obj.area.width + 5;
    cfg_obj.area.ys     = 10;
    cfg_obj.area.width  = 60;
    cfg_obj.max         = 128;
    ID_t ID_BAR_1 = GUI_object_create( &cfg_obj );



    GUI_object_insert(ID_NUM_1);
    GUI_object_insert(ID_BAR_1);
    GUI_RefreashScreen();
    
    while(1){
        for( int i=0; i<128; i++ ){
            GUI_object_adjust(ID_NUM_1, joystick_data[0]);
            GUI_object_adjust(ID_NUM_2, joystick_data[1]);

            GUI_object_adjust(ID_BAR_1, i);
            GUI_RefreashScreen();
            // delay_ms(1);
        }
    }

}



