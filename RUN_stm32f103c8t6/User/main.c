

#include "delay.h"
#include "ssd1306.h"
#include "RH_gui_api.h"
#include "RH_gui.h"
#include "RH_color.h"

int main(void){

    delay_init(72);
    SSD1306_Init();

    API_Init__STM32F103C8T6 ();
    
    delay_ms(10);
    SSD1306_Clean();
    

    GUI_Init();

    __GUI_Object_t cfg_obj = {0};

    GUI_object_quickSet(&cfg_obj);

    cfg_obj.style       = kGUI_ObjStyle_text;
    cfg_obj.area.xs     = 0;
    cfg_obj.area.ys     = 5;
    cfg_obj.area.height = 12;
    cfg_obj.area.width  = 70;
    cfg_obj.min         = 0;
    cfg_obj.max         = 256;
    cfg_obj.font        = kGUI_FontStyle_ArialRounded_Bold;
    cfg_obj.text_color  = M_COLOR_WHITE;
    cfg_obj.text        = "size:";
    cfg_obj.text_size   = 8;
    cfg_obj.text_align  = kGUI_FontAlign_Left;
    cfg_obj.showFrame   = true;
    cfg_obj.bk_color    = M_COLOR_BLACK;
    cfg_obj.val         = 129;
    
    ID_t ID_Text_1 = GUI_object_create( &cfg_obj );
    

    cfg_obj.text        = "vol:";
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_Text_2 = GUI_object_create( &cfg_obj );


    cfg_obj.text        = "ip:";
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_Text_3 = GUI_object_create( &cfg_obj );

    cfg_obj.text        = "speed:";
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_Text_4 = GUI_object_create( &cfg_obj );

    GUI_object_insert(ID_Text_1);
    GUI_object_insert(ID_Text_2);
    GUI_object_insert(ID_Text_3);
    GUI_object_insert(ID_Text_4);
    
    cfg_obj.style       = kGUI_ObjStyle_num;
    cfg_obj.area.xs    += cfg_obj.area.width;
    cfg_obj.area.ys     = 5;
    cfg_obj.area.height = 12;
    cfg_obj.area.width  = 30;
    ID_t ID_Num_1       = GUI_object_create( &cfg_obj );

    cfg_obj.val         = 9;
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_Num_2       = GUI_object_create( &cfg_obj );


    cfg_obj.val         = 10;
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_Num_3       = GUI_object_create( &cfg_obj );

    cfg_obj.val         = 11;
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_Num_4       = GUI_object_create( &cfg_obj );

    GUI_object_insert(ID_Num_1);
    GUI_object_insert(ID_Num_2);
    GUI_object_insert(ID_Num_3);
    GUI_object_insert(ID_Num_4);

    GUI_RefreashScreen();

    while(1){
        for( int i=0; i<128; i++ ){
            GUI_object_adjust(ID_Num_1, i);
            GUI_object_adjust(ID_Num_2, i);
            GUI_object_adjust(ID_Num_3, i);
            GUI_object_adjust(ID_Num_4, i);
            GUI_RefreashScreen();
            // delay_ms(10);
        }
    }

}



