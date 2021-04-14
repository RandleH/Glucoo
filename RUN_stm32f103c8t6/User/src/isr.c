#include "stm32f10x_exti.h"
#include "delay.h"
#include "joystick.h"

#define EXTI_OK_LINE             EXTI_Line7

#define JOYSTICK_IRQHandler      EXTI9_5_IRQHandler

void JOYSTICK_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_OK_LINE)!=RESET){
        //...//
    }
    delay_ms(150);
	EXTI_ClearITPendingBit(EXTI_OK_LINE);
}




