

#include "delay.h"
#include "ssd1351.h"
#include "stm32f4xx_conf.h"

#define SPI_GPIO_RCC_CMD(a,b)   RCC_AHB1PeriphClockCmd(a,b) 
#define SPI_GPIO_RCC            RCC_AHB1Periph_GPIOB
#define SPI_GPIO                GPIOB
#define SPI_GPIO_AF             GPIO_AF_SPI1
#define SPI_PIN_SDA             GPIO_Pin_3
#define SPI_PIN_SCL             GPIO_Pin_5
#define SPI_PINSRC_SDA          GPIO_PinSource3
#define SPI_PINSRC_SCL          GPIO_PinSource5
#define SPI_PINs                ((uint16_t)( SPI_PIN_SDA | SPI_PIN_SCL ))
         
#define CS_RCC_CMD(a,b)         RCC_AHB1PeriphClockCmd(a,b)
#define CS_GPIO_RCC             RCC_AHB1Periph_GPIOA
#define CS_GPIO                 GPIOA
#define CS_PIN                  GPIO_Pin_4
    
#define DC_RCC_CMD(a,b)         RCC_AHB1PeriphClockCmd(a,b)
#define DC_GPIO_RCC             RCC_AHB1Periph_GPIOB
#define DC_GPIO                 GPIOB
#define DC_PIN                  GPIO_Pin_1
    
#define RES_RCC_CMD(a,b)        RCC_AHB1PeriphClockCmd(a,b)
#define RES_GPIO_RCC            RCC_AHB1Periph_GPIOB
#define RES_GPIO                GPIOB
#define RES_PIN                 GPIO_Pin_0

    
#define SPI_RCC_CMD(a,b)        RCC_APB2PeriphClockCmd(a,b)     
#define SPI_BASE                SPI1
#define SPI_RCC                 RCC_APB2Periph_SPI1



static void __configSPI(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
  	SPI_InitTypeDef   SPI_InitStructure;

  	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);
  	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    DC_RCC_CMD(DC_GPIO_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin    = DC_PIN;
    GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;
    GPIO_Init(DC_GPIO, &GPIO_InitStructure);

    RES_RCC_CMD(RES_GPIO_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin    = RES_PIN;
    GPIO_Init(RES_GPIO, &GPIO_InitStructure);

    CS_RCC_CMD(CS_GPIO_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin    = CS_PIN;
    GPIO_Init(CS_GPIO, &GPIO_InitStructure);


    SPI_GPIO_RCC_CMD(SPI_GPIO_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin    = SPI_PINs;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,SPI_PINSRC_SDA,SPI_GPIO_AF); 
	GPIO_PinAFConfig(GPIOB,SPI_PINSRC_SCL,SPI_GPIO_AF); 
    
    SPI_RCC_CMD( SPI_RCC, ENABLE );
    // RCC_APB2PeriphResetCmd(SPI_RCC,ENABLE);
	// RCC_APB2PeriphResetCmd(SPI_RCC,DISABLE);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;	
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit  = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPI_BASE, &SPI_InitStructure);  
	SPI_Cmd(SPI_BASE, ENABLE);
}

static uint16_t __transferByte(uint8_t byte){
	while (SPI_I2S_GetFlagStatus(SPI_BASE, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI_BASE, byte); 
	while (SPI_I2S_GetFlagStatus(SPI_BASE, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI_BASE);
}

static void __writeCmd(uint8_t cmd){
	GPIO_ResetBits(DC_GPIO, DC_PIN);
	__transferByte(cmd);
}

static void __writeDat(uint8_t data){
	GPIO_SetBits(DC_GPIO, DC_PIN);
	__transferByte(data);
}

static void SSD1351_Reset() {
    GPIO_SetBits(RES_GPIO, RES_PIN);
    delay_ms(500);
    GPIO_ResetBits(RES_GPIO, RES_PIN);
  	delay_ms(500);
    GPIO_SetBits(RES_GPIO, RES_PIN);
    delay_ms(500);
}

void SSD1351_Init(void){
	__configSPI();
    GPIO_ResetBits(CS_GPIO, CS_PIN);
	SSD1351_Reset();
    __writeCmd(0xFD); // COMMANDLOCK
    __writeDat(0x12);

    __writeCmd(0xFD); // COMMANDLOCK
    __writeDat(0xB1);

    __writeCmd(0xAE); // DISPLAYOFF
    __writeCmd(0xB3); // CLOCKDIV
    __writeCmd(0xF1); // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
    
    __writeCmd(0xCA); // MUXRATIO
    __writeDat(0x7F);

    __writeCmd(0xA0); // SETREMAP
    __writeDat(0x74);

    __writeCmd(0x15); // SETCOLUMN
    __writeDat(0x00);
    __writeDat(0x7F);

    __writeCmd(0x75); // SETROW
    __writeDat(0x00);
    __writeDat(0x7F);

    __writeCmd(0xA1); // STARTLINE
    __writeDat(0x00);// 96 if display height == 96
    
    __writeCmd(0xA2); // DISPLAYOFFSET
    __writeDat(0x00);
    
    __writeCmd(0xB5); // SETGPIO
    __writeDat(0x00);
    
    __writeCmd(0xAB); // FUNCTIONSELECT
    __writeDat(0x01);
    
    __writeCmd(0xB1); // PRECHARGE
    __writeDat(0x32);
    
    __writeCmd(0xBE); // VCOMH
    __writeDat(0x05);
    
    __writeCmd(0xA6); // NORMALDISPLAY (don't invert)
    __writeCmd(0xC1); // CONTRASTABC
    __writeDat(0xC8);
    __writeDat(0x80);
    __writeDat(0xC8);
    
    __writeCmd(0xC7); // CONTRASTMASTER
    __writeDat(0x0F);
    
    __writeCmd(0xB4); // SETVSL
    __writeDat(0xA0);
    __writeDat(0xB5);
    __writeDat(0x55);
    
    __writeCmd(0xB6); // PRECHARGE2
    __writeDat(0x01);
    
    __writeCmd(0xAF); // DISPLAYON

    GPIO_SetBits(CS_GPIO, CS_PIN);
}

void SSD1351_Clean(void){
    // SSD1351_FillRectangle(0, 0, SSD1351_WIDTH, SSD1351_HEIGHT, color);
    GPIO_ResetBits(CS_GPIO, CS_PIN);
    // column address set
    __writeCmd(0x15); // SETCOLUMN
    __writeDat(0x00);
    __writeDat(0xff);
    // row address set
    __writeCmd(0x75); // SETROW
    __writeDat(0x00);
    __writeDat(0xff);
    // write to RAM
    __writeCmd(0x5C); // WRITERAM

    for(int y=0;y<SSD1351_HEIGHT;y++){
        for(int x=0;x<SSD1351_WIDTH;x++){
            __writeDat((0x00)>>8);
            __writeDat((0x00)&0xff);
        }
    }

    GPIO_SetBits(CS_GPIO, CS_PIN);
}

void SSD1351_API_DrawArea( int xs, int ys, int xe, int ye,const uint16_t* pixData){
    GPIO_ResetBits(CS_GPIO, CS_PIN);
    // column address set
    __writeCmd(0x15); // SETCOLUMN
    __writeDat(xs);
    __writeDat(xe);
    // row address set
    __writeCmd(0x75); // SETROW
    __writeDat(ys);
    __writeDat(ye);
    // write to RAM
    __writeCmd(0x5C); // WRITERAM

    for(uint16_t y=ys;y<=ye;y++){
        for(uint16_t x=xs;x<=xe;x++){
            __writeDat((*pixData)>>8);
            __writeDat((*pixData)&0xff);
            // __writeDat((SSD1351_GREEN)>>8);
            // __writeDat((SSD1351_GREEN)&0xff);
            pixData++;
        }
    }
    
    GPIO_SetBits(CS_GPIO, CS_PIN);
}

void SSD1351_API_DrawPixel( int x, int y,const uint16_t pixData){
    GPIO_ResetBits(CS_GPIO, CS_PIN);
    // column address set
    __writeCmd(0x15); // SETCOLUMN
    __writeDat(x);
    __writeDat(x);
    // row address set
    __writeCmd(0x75); // SETROW
    __writeDat(y);
    __writeDat(y);
    // write to RAM
    __writeCmd(0x5C); // WRITERAM

    __writeDat((pixData)>>8);
    __writeDat((pixData)&0xff);
    // __writeDat((SSD1351_RED)>>8);
    // __writeDat((SSD1351_RED)&0xff);
    
    GPIO_SetBits(CS_GPIO, CS_PIN);
}







