

#include "delay.h"
#include "ssd1306.h"
#include "joystick.h"
#include "RH_gui_api.h"
#include "RH_gui.h"
#include "RH_color.h"


#include "system_stm32f10x.h"
#include "cpu.h"  
#include "os.h"

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

#if 0
    void     OSInit         (OS_ERR         *p_err);
    void     OS_RdyListInit (void);

    OSRdyList[]

    void  OSTaskCreate   (OS_TCB       *p_tcb,        /* 任务块指针   */
                         CPU_CHAR      *p_name,       /* 任务名字     */
                         OS_TASK_PTR    p_task,       /* 任务函数     */
                         void          *p_arg,        /* 任务形参     */ 
                         OS_PRIO        prio,         /* 任务优先级   */ 
                         CPU_STK       *p_stk_base,   /* 任务栈基地址 */
                         CPU_STK_SIZE   stk_limit,    /* 设置栈深度的限制位置 */
                         CPU_STK_SIZE   stk_size,     /* 任务栈大小 */
                         OS_MSG_QTY     q_size,       /* 发送任务的最大消息数 */
                         OS_TICK        time_quanta,  /* 在任务之间循环时的时间片的时间量（以滴答为单位）。指定0 则使用默认值。 */
                         void          *p_ext,        /* 是指向用户提供的内存位置的指针，用作TCB 扩展。例如，该用户存储器可以保存浮点寄存器的内容在上下文切换期间，每个任务执行的时间，次数、任务已经切换等 */
                         OS_OPT         opt,          /* 任务创建可选参数  os.h [Ln 282] */
                         OS_ERR        *p_err)        /* 错误码变量地址 */

    CPU_STK  *OSTaskStkInit (OS_TASK_PTR    p_task,
                         void          *p_arg,
                         CPU_STK       *p_stk_base,
                         CPU_STK       *p_stk_limit,
                         CPU_STK_SIZE   stk_size,
                         OS_OPT         opt);

    OS_CPU_SysTickInit

#endif

    CPU_INT32U cpu_clk_freq = SystemCoreClock;
    /* Determine nbr SysTick increments */
    CPU_INT32U cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;
    
    OS_CPU_SysTickInit(cnts); /* Init μC/OS periodic time src (SysTick). */


    while(1){
        // GUI_object_adjust(ID_JOY, 2066, 0); 
        GUI_object_adjust(ID_JOY, joystick_data[0], joystick_data[1]);
        GUI_object_adjust(ID_NUM_1, joystick_data[0], 0);
        GUI_object_adjust(ID_NUM_2, joystick_data[1], 0);
        GUI_RefreashScreen();
    }
}



