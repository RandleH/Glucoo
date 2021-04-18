

#include "delay.h"
#include "ssd1306.h"
#include "joystick.h"
#include "led.h"
#include "beeper.h"
#include "RH_gui_api.h"
#include "RH_gui.h"
#include "RH_color.h"


#include "system_stm32f10x.h"
#include "cpu.h"  
#include "os.h"
#include "lib_mem.h"
#include "cpu_core.h"

OS_ERR          OS_err_code;

OS_TCB          TCB_FillScreen;
CPU_STK         STK_FillScreen[768];
void Task_FillScreen(void* param){
    //...//
    while(1){
        GUI_rect_raw( 10,10,40,40 );
        GUI_RefreashScreen();
        OSTimeDly (500,OS_OPT_TIME_DLY,&OS_err_code);
    }
}

OS_TCB          TCB_LedBlink;
CPU_STK         STK_LedBlink[128];
void Task_LedBlink(void* param){
    while(1){
        LED_Set(0);
        OSTimeDly (500,OS_OPT_TIME_DLY,&OS_err_code);
        LED_Set(1);
        OSTimeDly (500,OS_OPT_TIME_DLY,&OS_err_code);
    }
}

OS_TCB          TCB_BeepBlink;
CPU_STK         STK_BeepBlink[128];
void Task_BeepBlink(void* param){
    while(1){
        BEEP_Set(0);
        OSTimeDly (10,OS_OPT_TIME_DLY,&OS_err_code);
        BEEP_Set(1);
        OSTimeDly (1000,OS_OPT_TIME_DLY,&OS_err_code);
    }
}


int main(void){

    delay_init(72);
    SSD1306_Init();
    JoyStick_Init();
    LED_Init();
    BEEP_Init();
    GUI_API_Init ();
    GUI_Init();

    Mem_Init();

    
    OSInit(&OS_err_code);    
    CPU_Init(); 
    OS_CPU_SysTickInit(SystemCoreClock / (CPU_INT32U)OSCfg_TickRate_Hz);
    // CPU_IntDisMeasMaxCurReset();

    OSTaskCreate((OS_TCB     *)&TCB_FillScreen,                /* Create the Led1 task                                */
                 (CPU_CHAR   *)"Fill Screen",
                 (OS_TASK_PTR ) Task_FillScreen,
                 (void       *) 0,
                 (OS_PRIO     ) 3,
                 (CPU_STK    *)&STK_FillScreen[0],
                 (CPU_STK_SIZE) sizeof(STK_FillScreen) / 10,
                 (CPU_STK_SIZE) sizeof(STK_FillScreen),
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK ),
                 (OS_ERR     *)&OS_err_code);

    OSTaskCreate((OS_TCB     *)&TCB_LedBlink,                /* Create the Led1 task                                */
                 (CPU_CHAR   *)"Led Blink",
                 (OS_TASK_PTR ) Task_LedBlink,
                 (void       *) 0,
                 (OS_PRIO     ) 3,
                 (CPU_STK    *)&STK_LedBlink[0],
                 (CPU_STK_SIZE) sizeof(STK_LedBlink) / 10,
                 (CPU_STK_SIZE) sizeof(STK_LedBlink),
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK ),
                 (OS_ERR     *)&OS_err_code);

    OSTaskCreate((OS_TCB     *)&TCB_BeepBlink,                /* Create the Led1 task                                */
                 (CPU_CHAR   *)"Beeper Blink",
                 (OS_TASK_PTR ) Task_BeepBlink,
                 (void       *) 0,
                 (OS_PRIO     ) 3,
                 (CPU_STK    *)&STK_BeepBlink[0],
                 (CPU_STK_SIZE) sizeof(STK_BeepBlink) / 10,
                 (CPU_STK_SIZE) sizeof(STK_BeepBlink),
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK ),
                 (OS_ERR     *)&OS_err_code);             
                 
    OSStart(&OS_err_code);

    
    /* Determine nbr SysTick increments */
    
    
     /* Init μC/OS periodic time src (SysTick). */


    
}


int main_old(void){
    SSD1306_Init();
    JoyStick_Init();

    GUI_API_Init ();
    
    SSD1306_Clean();
    
    GUI_Init();

    __GUI_Object_t cfg_obj = {0};

    GUI_object_quickSet(&cfg_obj);

    cfg_obj.style       = kGUI_ObjStyle_joystick;
    cfg_obj.area.xs     = 10;
    cfg_obj.area.ys     = 10;
    cfg_obj.area.height = 45;
    cfg_obj.area.width  = 45;
    cfg_obj.min[0]      = 0;
    cfg_obj.max[0]      = 4096;
    cfg_obj.min[1]      = 0;
    cfg_obj.max[1]      = 4096;
    cfg_obj.font        = kGUI_FontStyle_ArialRounded_Bold;
    cfg_obj.text_color  = M_COLOR_WHITE;
    cfg_obj.text_size   = 8;
    cfg_obj.text_align  = kGUI_FontAlign_Middle;
    cfg_obj.showFrame   = true;
    cfg_obj.bk_color    = M_COLOR_BLACK;
    cfg_obj.val[0]      = joystick_data[0];
    cfg_obj.val[1]      = joystick_data[1];
    
    ID_t ID_JOY         = GUI_object_create( &cfg_obj );
    
    cfg_obj.style       = kGUI_ObjStyle_num;
    cfg_obj.area.xs     = 90;
    cfg_obj.area.ys     = 20;
    cfg_obj.area.width  = 35;
    cfg_obj.area.height = 12;
    ID_t ID_NUM_1       = GUI_object_create( &cfg_obj );
    
    cfg_obj.area.ys    += cfg_obj.area.height;
    ID_t ID_NUM_2       = GUI_object_create( &cfg_obj );

    cfg_obj.style       = kGUI_ObjStyle_text;
    
    
    cfg_obj.area.width  = 10;
    cfg_obj.area.xs    -= cfg_obj.area.width-1;
    cfg_obj.text        = "Y";
    ID_t ID_TXT_Y       = GUI_object_create( &cfg_obj );
    
    cfg_obj.area.ys    -= cfg_obj.area.height;
    cfg_obj.text        = "X";
    ID_t ID_TXT_X       = GUI_object_create( &cfg_obj );

    GUI_object_insert(ID_JOY);
    GUI_object_insert(ID_NUM_1);
    GUI_object_insert(ID_NUM_2);
    
    GUI_object_insert(ID_TXT_X);
    GUI_object_insert(ID_TXT_Y);

    while(0){
        // GUI_object_adjust(ID_JOY, 2066, 0); 
        GUI_object_adjust(ID_JOY, joystick_data[0], joystick_data[1]);
        GUI_object_adjust(ID_NUM_1, joystick_data[0], 0);
        GUI_object_adjust(ID_NUM_2, joystick_data[1], 0);
        GUI_RefreashScreen();
    }
    return 0;
}



