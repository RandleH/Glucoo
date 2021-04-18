
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "led.h"


#define LED_GPIO_RCC    RCC_APB2Periph_GPIOC
#define LED_GPIO        GPIOC
#define LED_GPIO_PIN    GPIO_Pin_13

static void __configGPIO(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( LED_GPIO_RCC , ENABLE );
    GPIO_InitStructure.GPIO_Pin   = LED_GPIO_PIN;    
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(LED_GPIO, &GPIO_InitStructure);    
    GPIO_ResetBits(LED_GPIO, LED_GPIO_PIN);

}


void LED_Init(void){
    __configGPIO();
}


void LED_Set( int cmd ){
    if( cmd )
        GPIO_ResetBits(LED_GPIO, LED_GPIO_PIN);
    else
        GPIO_SetBits(LED_GPIO, LED_GPIO_PIN);
}

