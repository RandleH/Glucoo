
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#ifndef _OLED_H
#define _OLED_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#define OLED_X_WIDTH 		128
#define OLED_Y_WIDTH 		64


void SSD1306_Init(void);
void SSD1306_Clean(void);

void SSD1306_ShowImg(uint8_t *image);
void SSD1306_Brightness(uint8_t br);
void SSD1306_ClearArea_page(uint8_t page,uint8_t x_start,uint8_t x_end);

void SSD1306_API_DrawArea( int x1, int y1, int x2, int y2, const uint8_t* pixData );

#endif


