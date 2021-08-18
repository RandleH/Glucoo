#include "stm32f10x_conf.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"

#include "delay.h"
#include "joystick.h"

#define ADC_BASE                 ADC1

#define DMAx_CHx                 DMA1_Channel1
#define DMA_RCC                  RCC_AHBPeriph_DMA1

#define ADC_X_CH                 ADC_Channel_8
#define ADC_X_RCC                RCC_APB2Periph_ADC1
#define ADC_X_GPIO_RCC           RCC_APB2Periph_GPIOB
#define ADC_X_GPIO               GPIOB
#define ADC_X_PIN                GPIO_Pin_0
       
#define ADC_Y_CH                 ADC_Channel_9
#define ADC_Y_RCC                RCC_APB2Periph_ADC1
#define ADC_Y_GPIO_RCC           RCC_APB2Periph_GPIOB
#define ADC_Y_GPIO               GPIOB
#define ADC_Y_PIN                GPIO_Pin_1
       
#define EXTI_OK_GPIO_RCC         RCC_APB2Periph_GPIOA
#define EXTI_OK_GPIO             GPIOA
#define EXTI_OK_PIN              GPIO_Pin_7
#define EXTI_OK_LINE             EXTI_Line7
#define EXTI_OK_PORTSRC          GPIO_PortSourceGPIOA, GPIO_PinSource7
#define EXTI_OK_IRQ              EXTI9_5_IRQn

#define JOYSTICK_IRQHandler      EXTI9_5_IRQHandler


uint16_t joystick_data[2] = {0};

static void __configGPIO(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(ADC_X_GPIO_RCC|ADC_Y_GPIO_RCC|EXTI_OK_GPIO_RCC,ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    /* Initialize the OK Pin */
    GPIO_InitStructure.GPIO_Pin     = EXTI_OK_PIN;
    GPIO_InitStructure.GPIO_Mode     = GPIO_Mode_IN_FLOATING;

    GPIO_Init(EXTI_OK_GPIO, &GPIO_InitStructure);

    /* Initialize the X , Y Pin */
    GPIO_InitStructure.GPIO_Pin        = ADC_X_PIN;
    GPIO_InitStructure.GPIO_Mode     = GPIO_Mode_AIN;
    GPIO_Init(ADC_X_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin        = ADC_Y_PIN;
    GPIO_InitStructure.GPIO_Mode     = GPIO_Mode_AIN;
    GPIO_Init(ADC_Y_GPIO, &GPIO_InitStructure);


    GPIO_EXTILineConfig( EXTI_OK_PORTSRC );

}

static void __configEXTI(void){
    EXTI_InitTypeDef EXIT_InitStructure;

    EXIT_InitStructure.EXTI_Line     = EXTI_Line7 ;

    EXIT_InitStructure.EXTI_Mode     = EXTI_Mode_Interrupt;
    EXIT_InitStructure.EXTI_Trigger  = EXTI_Trigger_Falling;
    EXIT_InitStructure.EXTI_LineCmd  = ENABLE;
    EXTI_Init(&EXIT_InitStructure);
}

static void __configNVIC(void){
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI_OK_IRQ;

    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void __configDMA(void){
    DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHBPeriphClockCmd(DMA_RCC,ENABLE);

    DMA_DeInit(DMAx_CHx);
    
    DMA_InitStructure.DMA_PeripheralBaseAddr    = (uint32_t)(0x4001244C);
    DMA_InitStructure.DMA_DIR                   = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_MemoryBaseAddr        = (uint32_t)joystick_data;
    DMA_InitStructure.DMA_BufferSize            = 2;                                 // -> x * DMA_PeripheralDataSize 
    DMA_InitStructure.DMA_PeripheralInc         = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc             = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize    = DMA_PeripheralDataSize_HalfWord;   // -> sizeof( uint16_t )
    DMA_InitStructure.DMA_MemoryDataSize        = DMA_MemoryDataSize_HalfWord ;
    DMA_InitStructure.DMA_Mode                  = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority              = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                   = DMA_M2M_Disable;
    
    DMA_Init(DMAx_CHx,&DMA_InitStructure);
    DMA_Cmd(DMAx_CHx,ENABLE);
}

static void __configADC(void){
    ADC_InitTypeDef ADC_InitStructure;
    
    RCC_APB2PeriphClockCmd(ADC_X_RCC, ENABLE);

    ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent; 
    ADC_InitStructure.ADC_ScanConvMode       = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
    ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel       = 2; 
    
    ADC_Init(ADC_BASE,&ADC_InitStructure);
    ADC_RegularChannelConfig(ADC_BASE,ADC_X_CH,1,ADC_SampleTime_28Cycles5);
    ADC_RegularChannelConfig(ADC_BASE,ADC_Y_CH,2,ADC_SampleTime_28Cycles5);
    ADC_DMACmd(ADC_BASE,ENABLE);
    ADC_Cmd(ADC_BASE,ENABLE);
    
    ADC_ResetCalibration(ADC_BASE);
    while(ADC_GetResetCalibrationStatus(ADC_BASE));
    ADC_StartCalibration(ADC_BASE);
    while(ADC_GetCalibrationStatus(ADC_BASE));
    ADC_SoftwareStartConvCmd(ADC_BASE,ENABLE);
}

void JoyStick_Init(void){
    __configGPIO();
    __configEXTI();
    __configNVIC();
    __configDMA();
    __configADC();
}








