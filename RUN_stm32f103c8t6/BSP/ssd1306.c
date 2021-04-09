


#include "delay.h"
#include "ssd1306.h"

#include "stm32f10x_conf.h"


#define I2C_PIN_SDA         GPIO_Pin_10
#define I2C_PIN_SCL         GPIO_Pin_11
#define I2C_PIN             ((uint16_t)( I2C_PIN_SDA | I2C_PIN_SCL ))
     
#define I2C_GPIO            GPIOB
#define I2C_GPIO_RCC        RCC_APB2Periph_GPIOB
#define I2C_BASE            I2C2
#define I2C_RCC             RCC_APB1Periph_I2C2
#define I2C_ADDR            0x78


#define OLED_PAGEs   		8
#define OLED_TOTAL_PIXELs 	8192

#ifndef __min
  #define __min(a,b)                           (((a)<(b))?(a):(b))
#endif

#ifndef __max
  #define __max(a,b)                           (((a)>(b))?(a):(b))
#endif

static void __configI2C(void){
	I2C_InitTypeDef  I2C_InitStructure = {
		.I2C_Mode                = I2C_Mode_I2C       ,
		.I2C_DutyCycle           = I2C_DutyCycle_2    ,
		.I2C_OwnAddress1         = 0x30               ,
		.I2C_Ack                 = I2C_Ack_Enable     ,
		.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit , 
		.I2C_ClockSpeed          = 400000
	};
	GPIO_InitTypeDef  GPIO_InitStructure = {
        .GPIO_Speed              = GPIO_Speed_50MHz   ,
        .GPIO_Mode               = GPIO_Mode_AF_OD    ,
        .GPIO_Pin                = I2C_PIN            ,
	};
	RCC_APB2PeriphClockCmd(I2C_GPIO_RCC,ENABLE);
	GPIO_Init(I2C_GPIO, &GPIO_InitStructure);


	RCC_APB1PeriphClockCmd(I2C_RCC,ENABLE);
	I2C_DeInit(I2C_BASE);
	I2C_Cmd(I2C_BASE, ENABLE);
	I2C_Init(I2C_BASE, &I2C_InitStructure);
}

static void __writeByte(uint8_t addr,uint8_t data){
	while(I2C_GetFlagStatus(I2C_BASE, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2C_BASE, ENABLE);//开启I2C
	while(!I2C_CheckEvent(I2C_BASE, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2C_BASE, I2C_ADDR, I2C_Direction_Transmitter);//器件地址 -- 默认0x78
	while(!I2C_CheckEvent(I2C_BASE, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C_BASE, addr);//寄存器地址
	while (!I2C_CheckEvent(I2C_BASE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C_BASE, data);//发送数据
	while (!I2C_CheckEvent(I2C_BASE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C_BASE, ENABLE);//关闭I2C1总线
}

static void __writeDat(uint8_t data){
	__writeByte(0x40,data);
}

static void __writeCmd(uint8_t cmd){
	__writeByte(0x00,cmd);
}



void SSD1306_Init(void){
	__configI2C();
	delay_ms(100); 
	__writeCmd(0xAE); //display off
	__writeCmd(0x20); //Set Memory Addressing Mode	
	__writeCmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	__writeCmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
	__writeCmd(0xc8); //Set COM Output Scan Direction
	__writeCmd(0x00); //---set low column address
	__writeCmd(0x10); //---set high column address
	__writeCmd(0x40); //--set start line address
	__writeCmd(0x81); //--set contrast control register
	__writeCmd(0xff); //亮度调节 0x00~0xff
	__writeCmd(0xa1); //--set segment re-map 0 to 127
	__writeCmd(0xa6); //--set normal display
	__writeCmd(0xa8); //--set multiplex ratio(1 to 64)
	__writeCmd(0x3F); //
	__writeCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	__writeCmd(0xd3); //-set display offset
	__writeCmd(0x00); //-not offset
	__writeCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	__writeCmd(0xf0); //--set divide ratio
	__writeCmd(0xd9); //--set pre-charge period
	__writeCmd(0x22); //
	__writeCmd(0xda); //--set com pins hardware configuration
	__writeCmd(0x12);
	__writeCmd(0xdb); //--set vcomh
	__writeCmd(0x20); //0x20,0.77xVcc
	__writeCmd(0x8d); //--set DC-DC enable
	__writeCmd(0x14); //
	__writeCmd(0xaf); //--turn on oled panel

}

void SSD1306_Clean(void){
	for(size_t page = 0;page<OLED_PAGEs;page++){
		__writeCmd (0xb0+page);    
		__writeCmd (0x00);      
		__writeCmd (0x10);      
		for(size_t column=0;column<OLED_X_WIDTH;column++)
			__writeDat(0x00);
	}
}


void SSD1306_ShowImg(uint8_t *image){
	uint8_t page_addr;
	uint8_t cnt;
	for(page_addr=0xb0;page_addr<0xb8;page_addr++)
	{
		__writeCmd(page_addr);
		__writeCmd(0x10);
		__writeCmd(0x00);
		for(cnt=0;cnt<128;cnt++)
			__writeDat(*image++);
	}
}

void SSD1306_Brightness(uint8_t br){
	__writeCmd(0x81);
	if(br>255)
		br=255;
	__writeCmd(br);
}


void SSD1306_ClearArea_page(uint8_t page,uint8_t x_start,uint8_t x_end){
	uint8_t cnt;
	__writeCmd(0xb0+page);
	__writeCmd((x_start>>4)|0x10);
	__writeCmd(x_start&0x0f);
	for(cnt=x_start;cnt<x_end;cnt++)
		__writeDat(0x00);
}

// void OLED_API_DrawPageColumn(unsigned int page,unsigned int column_start,unsigned int column_num,const unsigned char* pixData){
// 	assert_param(column_start >= 0);
// 	assert_param(page < 8);

// 	__writeCmd (0xb0+page);    
// 	__writeCmd (column_start&0x0f);      
// 	__writeCmd ((column_start>>4)|0x10);      
// 	for(unsigned char column=0;column<column_num;column++)
// 		__writeDat(*(pixData++));
// }

void SSD1306_API_DrawArea( int x1, int y1, int x2, int y2, const uint8_t* pixData){
    assert_param( x1>=0 && x1<OLED_X_WIDTH );
	assert_param( x2>=0 && x2<OLED_X_WIDTH );
    assert_param( y1>=0 && y1<OLED_Y_WIDTH );
	assert_param( y2>=0 && y2<OLED_Y_WIDTH );
    
    int xs = __min( x1, x2 );
    int xe = __max( x1, x2 );
    int ps = __min( y1, y2 ) >> 3;
    int pe = __max( y1, y2 ) >> 3;

    for (int p = ps; p<=pe; p++){
	    __writeCmd (0xb0+p);    
		__writeCmd ( xs&0x0f );      
		__writeCmd ((xs>>4)|0x10);      
		for( int x=xs; x<=xe; x++)
			__writeDat(*(pixData++));
	}
}





















