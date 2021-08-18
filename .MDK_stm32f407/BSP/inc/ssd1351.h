#ifndef _SSD1351_H
#define _SSD1351_H 

#include <stdint.h>
#include <stddef.h>
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


#define SSD1351_WIDTH    128
#define SSD1351_HEIGHT   128


// #define	SSD1351_BLACK   0x0000
// #define	SSD1351_BLUE    0x001F
// #define	SSD1351_RED     0xF800
// #define	SSD1351_GREEN   0x07E0
// #define SSD1351_CYAN    0x07FF
// #define SSD1351_MAGENTA 0xF81F
// #define SSD1351_YELLOW  0xFFE0
// #define SSD1351_WHITE   0xFFFF



void SSD1351_Init(void);
void SSD1351_Clean(void);


void SSD1351_API_DrawArea   ( int xs, int ys, int xe, int ye,const uint16_t* pixData );
void SSD1351_API_DrawPixel  ( int x , int y ,const uint16_t pixData);


#endif




