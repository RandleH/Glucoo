
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "beeper.h"


#define BEEP_GPIO_RCC    RCC_APB2Periph_GPIOA
#define BEEP_GPIO        GPIOA
#define BEEP_GPIO_PIN    GPIO_Pin_2

static void __configGPIO(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( BEEP_GPIO_RCC , ENABLE );
    GPIO_InitStructure.GPIO_Pin   = BEEP_GPIO_PIN;    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(BEEP_GPIO, &GPIO_InitStructure);    
    GPIO_ResetBits(BEEP_GPIO, BEEP_GPIO_PIN);

}

void BEEP_Init(void){
    __configGPIO();
}


void BEEP_Set( int cmd ){
    if( cmd )
        GPIO_ResetBits(BEEP_GPIO, BEEP_GPIO_PIN);
    else
        GPIO_SetBits(BEEP_GPIO, BEEP_GPIO_PIN);
}



