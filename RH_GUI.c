
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include "RH_GUI.h"


#pragma anon_unions

//==================================================== API Handle =====================================================//
//==================================================== API Handle =====================================================//
//==================================================== API Handle =====================================================//

void (*GUI_API_DrawArea)      (unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,const Pixel_t* pixData) = NULL; 

void (*GUI_API_DrawPixel)     (unsigned int x,unsigned int y,const Pixel_t pixData) = NULL;

void (*GUI_API_DelayMs)       (unsigned long ms) = NULL;

#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
void (*GUI_API_DrawPageColumn)(unsigned int page,unsigned int column_start,unsigned int column_num,const Pixel_t* data) = NULL;
#endif

#if GUI_ASSERT
void (*GUI_API_AssertParam)   (bool expression,const char* WHAT_IS_WRONG )  = NULL;
#endif

//================================================ End of API Handle ==================================================//
//================================================ End of API Handle ==================================================//
//================================================ End of API Handle ==================================================//

//==================================================  Pixel Config ====================================================//
//==================================================  Pixel Config ====================================================//
//==================================================  Pixel Config ====================================================//

#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
union PixelUnit_t{
	struct __BYTE_BIT{
		Pixel_t bit0 : 1;
		Pixel_t bit1 : 1;
		Pixel_t bit2 : 1;
		Pixel_t bit3 : 1;
		Pixel_t bit4 : 1;
		Pixel_t bit5 : 1;
		Pixel_t bit6 : 1;
		Pixel_t bit7 : 1;
	};
	Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;
#elif ( GUI_DISPLAY_MODE == GUI_SINGLE_PIXEL )

#if ( GUI_COLOR_TYPE == GUI_1Bit)
union PixelUnit_t{
	struct{
		Pixel_t bit : 1;
	};
  	Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;
#elif ( GUI_COLOR_TYPE == GUI_RGB565 ) 
union PixelUnit_t{
	struct{
		Pixel_t R : 5;
		Pixel_t G : 6;
		Pixel_t B : 5;
	};
  	Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;
#elif ( GUI_COLOR_TYPE == GUI_RGB888 )
union PixelUnit_t{
	struct{
		Pixel_t R : 8;
		Pixel_t G : 8;
		Pixel_t B : 8;
	};
  	Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;
#endif

#endif

//=============================================== End of Pixel Config ===============================================//
//=============================================== End of Pixel Config ===============================================//
//=============================================== End of Pixel Config ===============================================//

//==================================================  Font Config ===================================================//
//==================================================  Font Config ===================================================//
//==================================================  Font Config ===================================================//
struct __FontChar_t{
	unsigned char        c;
	unsigned int         height;
	unsigned int         width;
	const unsigned char* byte;
	struct __FontChar_t* next;
};

typedef struct __FontChar_t  __FontChar_t;


static unsigned char __FONT_STD6X8__ASCII_32_0 [] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_1 [] = {0x00, 0x00, 0x00, 0x2f, 0x00, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_2 [] = {0x00, 0x00, 0x07, 0x00, 0x07, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_3 [] = {0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14};
static unsigned char __FONT_STD6X8__ASCII_32_4 [] = {0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12};
static unsigned char __FONT_STD6X8__ASCII_32_5 [] = {0x23, 0x13, 0x08, 0x64, 0x62, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_6 [] = {0x00, 0x36, 0x49, 0x55, 0x22, 0x50};
static unsigned char __FONT_STD6X8__ASCII_32_7 [] = {0x00, 0x00, 0x05, 0x03, 0x00, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_8 [] = {0x00, 0x00, 0x1c, 0x22, 0x41, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_9 [] = {0x00, 0x00, 0x41, 0x22, 0x1c, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_10[] = {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14};
static unsigned char __FONT_STD6X8__ASCII_32_11[] = {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08};
static unsigned char __FONT_STD6X8__ASCII_32_12[] = {0x00, 0x00, 0x00, 0xA0, 0x60, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_13[] = {0x00, 0x08, 0x08, 0x08, 0x08, 0x08};
static unsigned char __FONT_STD6X8__ASCII_32_14[] = {0x00, 0x00, 0x60, 0x60, 0x00, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_15[] = {0x00, 0x20, 0x10, 0x08, 0x04, 0x02};
static unsigned char __FONT_STD6X8__ASCII_32_16[] = {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E};
static unsigned char __FONT_STD6X8__ASCII_32_17[] = {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_18[] = {0x00, 0x42, 0x61, 0x51, 0x49, 0x46};
static unsigned char __FONT_STD6X8__ASCII_32_19[] = {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31};
static unsigned char __FONT_STD6X8__ASCII_32_20[] = {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10};
static unsigned char __FONT_STD6X8__ASCII_32_21[] = {0x00, 0x27, 0x45, 0x45, 0x45, 0x39};
static unsigned char __FONT_STD6X8__ASCII_32_22[] = {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30};
static unsigned char __FONT_STD6X8__ASCII_32_23[] = {0x00, 0x01, 0x71, 0x09, 0x05, 0x03};
static unsigned char __FONT_STD6X8__ASCII_32_24[] = {0x00, 0x36, 0x49, 0x49, 0x49, 0x36};
static unsigned char __FONT_STD6X8__ASCII_32_25[] = {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E};
static unsigned char __FONT_STD6X8__ASCII_32_26[] = {0x00, 0x00, 0x36, 0x36, 0x00, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_27[] = {0x00, 0x00, 0x56, 0x36, 0x00, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_28[] = {0x00, 0x08, 0x14, 0x22, 0x41, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_29[] = {0x00, 0x14, 0x14, 0x14, 0x14, 0x14};
static unsigned char __FONT_STD6X8__ASCII_32_30[] = {0x00, 0x00, 0x41, 0x22, 0x14, 0x08};
static unsigned char __FONT_STD6X8__ASCII_32_31[] = {0x00, 0x02, 0x01, 0x51, 0x09, 0x06};
static unsigned char __FONT_STD6X8__ASCII_32_32[] = {0x00, 0x32, 0x49, 0x59, 0x51, 0x3E};
static unsigned char __FONT_STD6X8__ASCII_32_33[] = {0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C};
static unsigned char __FONT_STD6X8__ASCII_32_34[] = {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36};
static unsigned char __FONT_STD6X8__ASCII_32_35[] = {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22};
static unsigned char __FONT_STD6X8__ASCII_32_36[] = {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C};
static unsigned char __FONT_STD6X8__ASCII_32_37[] = {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41};
static unsigned char __FONT_STD6X8__ASCII_32_38[] = {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01};
static unsigned char __FONT_STD6X8__ASCII_32_39[] = {0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A};
static unsigned char __FONT_STD6X8__ASCII_32_40[] = {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F};
static unsigned char __FONT_STD6X8__ASCII_32_41[] = {0x00, 0x00, 0x41, 0x7F, 0x41, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_42[] = {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01};
static unsigned char __FONT_STD6X8__ASCII_32_43[] = {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41};
static unsigned char __FONT_STD6X8__ASCII_32_44[] = {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40};
static unsigned char __FONT_STD6X8__ASCII_32_45[] = {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F};
static unsigned char __FONT_STD6X8__ASCII_32_46[] = {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F};
static unsigned char __FONT_STD6X8__ASCII_32_47[] = {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E};
static unsigned char __FONT_STD6X8__ASCII_32_48[] = {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06};
static unsigned char __FONT_STD6X8__ASCII_32_49[] = {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E};
static unsigned char __FONT_STD6X8__ASCII_32_50[] = {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46};
static unsigned char __FONT_STD6X8__ASCII_32_51[] = {0x00, 0x46, 0x49, 0x49, 0x49, 0x31};
static unsigned char __FONT_STD6X8__ASCII_32_52[] = {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01};
static unsigned char __FONT_STD6X8__ASCII_32_53[] = {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F};
static unsigned char __FONT_STD6X8__ASCII_32_54[] = {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F};
static unsigned char __FONT_STD6X8__ASCII_32_55[] = {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F};
static unsigned char __FONT_STD6X8__ASCII_32_56[] = {0x00, 0x63, 0x14, 0x08, 0x14, 0x63};
static unsigned char __FONT_STD6X8__ASCII_32_57[] = {0x00, 0x07, 0x08, 0x70, 0x08, 0x07};
static unsigned char __FONT_STD6X8__ASCII_32_58[] = {0x00, 0x61, 0x51, 0x49, 0x45, 0x43};
static unsigned char __FONT_STD6X8__ASCII_32_59[] = {0x00, 0x00, 0x7F, 0x41, 0x41, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_60[] = {0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55};
static unsigned char __FONT_STD6X8__ASCII_32_61[] = {0x00, 0x00, 0x41, 0x41, 0x7F, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_62[] = {0x00, 0x04, 0x02, 0x01, 0x02, 0x04};
static unsigned char __FONT_STD6X8__ASCII_32_63[] = {0x00, 0x40, 0x40, 0x40, 0x40, 0x40};
static unsigned char __FONT_STD6X8__ASCII_32_64[] = {0x00, 0x00, 0x01, 0x02, 0x04, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_65[] = {0x00, 0x20, 0x54, 0x54, 0x54, 0x78};
static unsigned char __FONT_STD6X8__ASCII_32_66[] = {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38};
static unsigned char __FONT_STD6X8__ASCII_32_67[] = {0x00, 0x38, 0x44, 0x44, 0x44, 0x20};
static unsigned char __FONT_STD6X8__ASCII_32_68[] = {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F};
static unsigned char __FONT_STD6X8__ASCII_32_69[] = {0x00, 0x38, 0x54, 0x54, 0x54, 0x18};
static unsigned char __FONT_STD6X8__ASCII_32_70[] = {0x00, 0x08, 0x7E, 0x09, 0x01, 0x02};
static unsigned char __FONT_STD6X8__ASCII_32_71[] = {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C};
static unsigned char __FONT_STD6X8__ASCII_32_72[] = {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78};
static unsigned char __FONT_STD6X8__ASCII_32_73[] = {0x00, 0x00, 0x44, 0x7D, 0x40, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_74[] = {0x00, 0x40, 0x80, 0x84, 0x7D, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_75[] = {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_76[] = {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00};
static unsigned char __FONT_STD6X8__ASCII_32_77[] = {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78};
static unsigned char __FONT_STD6X8__ASCII_32_78[] = {0x00, 0x7C, 0x08, 0x04, 0x04, 0x78};
static unsigned char __FONT_STD6X8__ASCII_32_79[] = {0x00, 0x38, 0x44, 0x44, 0x44, 0x38};
static unsigned char __FONT_STD6X8__ASCII_32_80[] = {0x00, 0xFC, 0x24, 0x24, 0x24, 0x18};
static unsigned char __FONT_STD6X8__ASCII_32_81[] = {0x00, 0x18, 0x24, 0x24, 0x18, 0xFC};
static unsigned char __FONT_STD6X8__ASCII_32_82[] = {0x00, 0x7C, 0x08, 0x04, 0x04, 0x08};
static unsigned char __FONT_STD6X8__ASCII_32_83[] = {0x00, 0x48, 0x54, 0x54, 0x54, 0x20};
static unsigned char __FONT_STD6X8__ASCII_32_84[] = {0x00, 0x04, 0x3F, 0x44, 0x40, 0x20};
static unsigned char __FONT_STD6X8__ASCII_32_85[] = {0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C};
static unsigned char __FONT_STD6X8__ASCII_32_86[] = {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C};
static unsigned char __FONT_STD6X8__ASCII_32_87[] = {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C};
static unsigned char __FONT_STD6X8__ASCII_32_88[] = {0x00, 0x44, 0x28, 0x10, 0x28, 0x44};
static unsigned char __FONT_STD6X8__ASCII_32_89[] = {0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C};
static unsigned char __FONT_STD6X8__ASCII_32_90[] = {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44};
static unsigned char __FONT_STD6X8__ASCII_32_91[] = {0x14, 0x14, 0x14, 0x14, 0x14, 0x14};
static unsigned char __FONT_STD6X8__ASCII_32_92[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};
static unsigned char __FONT_STD6X8__ASCII_32_93[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};
static unsigned char __FONT_STD6X8__ASCII_32_94[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};
static unsigned char __FONT_STD6X8__ASCII_32_95[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};

static __FontChar_t __FONT_STD6X8[] = {
	{ .c = ' ' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_0  },
	{ .c = '!' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_1  },
	{ .c = '"' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_2  },
	{ .c = '#' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_3  },
	{ .c = '$' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_4  },
	{ .c = '%' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_5  },
	{ .c = '&' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_6  },
	{ .c = '\'', .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_7  },
	{ .c = '(' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_8  },
	{ .c = ')' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_9  },
	{ .c = '*' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_10 },
	{ .c = '+' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_11 },
	{ .c = ',' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_12 },
	{ .c = '-' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_13 },
	{ .c = '.' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_14 },
	{ .c = '/' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_15 },
	{ .c = '0' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_16 },
	{ .c = '1' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_17 },
	{ .c = '2' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_18 },
	{ .c = '3' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_19 },
	{ .c = '4' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_20 },
	{ .c = '5' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_21 },
	{ .c = '6' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_22 },
	{ .c = '7' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_23 },
	{ .c = '8' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_24 },
	{ .c = '9' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_25 },
	{ .c = ':' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_26 },
	{ .c = ';' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_27 },
	{ .c = '<' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_28 },
	{ .c = '=' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_29 },
	{ .c = '>' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_30 },
	{ .c = '?' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_31 },
	{ .c = '@' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_32 },
	{ .c = 'A' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_33 },
	{ .c = 'B' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_34 },
	{ .c = 'C' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_35 },
	{ .c = 'D' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_36 },
	{ .c = 'E' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_37 },
	{ .c = 'F' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_38 },
	{ .c = 'G' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_39 },
	{ .c = 'H' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_40 },
	{ .c = 'I' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_41 },
	{ .c = 'J' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_42 },
	{ .c = 'K' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_43 },
	{ .c = 'L' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_44 },
	{ .c = 'M' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_45 },
	{ .c = 'N' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_46 },
	{ .c = 'O' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_47 },
	{ .c = 'P' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_48 },
	{ .c = 'Q' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_49 },
	{ .c = 'R' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_50 },
	{ .c = 'S' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_51 },
	{ .c = 'T' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_52 },
	{ .c = 'U' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_53 },
	{ .c = 'V' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_54 },
	{ .c = 'W' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_55 },
	{ .c = 'X' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_56 },
	{ .c = 'Y' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_57 },
	{ .c = 'Z' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_58 },
	{ .c = '[' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_59 },
	{ .c = '\\', .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_60 },
	{ .c = ']' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_61 },
	{ .c = '^' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_62 },
	{ .c = '_' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_63 },
	{ .c = '`' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_64 },
	{ .c = 'a' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_65 },
	{ .c = 'b' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_66 },
	{ .c = 'c' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_67 },
	{ .c = 'd' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_68 },
	{ .c = 'e' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_69 },
	{ .c = 'f' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_70 },
	{ .c = 'g' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_71 },
	{ .c = 'h' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_72 },
	{ .c = 'i' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_73 },
	{ .c = 'j' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_74 },
	{ .c = 'k' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_75 },
	{ .c = 'l' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_76 },
	{ .c = 'm' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_77 },
	{ .c = 'n' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_78 },
	{ .c = 'o' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_79 },
	{ .c = 'p' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_80 },
	{ .c = 'q' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_81 },
	{ .c = 'r' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_82 },
	{ .c = 's' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_83 },
	{ .c = 't' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_84 },
	{ .c = 'u' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_85 },
	{ .c = 'v' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_86 },
	{ .c = 'w' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_87 },
	{ .c = 'x' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_88 },
	{ .c = 'y' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_89 },
	{ .c = 'z' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_90 },
	{ .c = '{' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_91 },
	{ .c = '|' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_92 },
	{ .c = '}' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_93 },
	{ .c = '~' , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_94 },
	{ .c = 127 , .height = 8 , .width = 6 , .byte = __FONT_STD6X8__ASCII_32_95 },
};

static unsigned char __FONT_STD8X16__ASCII_32_0 [] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_1 [] = {0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_2 [] = {0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_3 [] = {0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_4 [] = {0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_5 [] = {0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_6 [] = {0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10};
static unsigned char __FONT_STD8X16__ASCII_32_7 [] = {0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_8 [] = {0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_9 [] = {0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_10[] = {0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_11[] = {0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_12[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_13[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
static unsigned char __FONT_STD8X16__ASCII_32_14[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_15[] = {0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_16[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_17[] = {0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_18[] = {0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_19[] = {0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_20[] = {0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_21[] = {0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_22[] = {0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_23[] = {0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_24[] = {0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_25[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_26[] = {0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_27[] = {0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_28[] = {0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_29[] = {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_30[] = {0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_31[] = {0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_32[] = {0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_33[] = {0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_34[] = {0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_35[] = {0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_36[] = {0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_37[] = {0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_38[] = {0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_39[] = {0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_40[] = {0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_41[] = {0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_42[] = {0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_43[] = {0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_44[] = {0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_45[] = {0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_46[] = {0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_47[] = {0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_48[] = {0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_49[] = {0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_50[] = {0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_51[] = {0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_52[] = {0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_53[] = {0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_54[] = {0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_55[] = {0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_56[] = {0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_57[] = {0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_58[] = {0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_59[] = {0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_60[] = {0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_61[] = {0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_62[] = {0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_63[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80};
static unsigned char __FONT_STD8X16__ASCII_32_64[] = {0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_65[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_66[] = {0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_67[] = {0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_68[] = {0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_69[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_70[] = {0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_71[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_72[] = {0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_73[] = {0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_74[] = {0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_75[] = {0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_76[] = {0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_77[] = {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F};
static unsigned char __FONT_STD8X16__ASCII_32_78[] = {0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_79[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_80[] = {0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_81[] = {0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80};
static unsigned char __FONT_STD8X16__ASCII_32_82[] = {0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_83[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_84[] = {0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_85[] = {0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20};
static unsigned char __FONT_STD8X16__ASCII_32_86[] = {0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_87[] = {0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_88[] = {0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_89[] = {0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_90[] = {0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_91[] = {0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40};
static unsigned char __FONT_STD8X16__ASCII_32_92[] = {0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_93[] = {0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_94[] = {0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static unsigned char __FONT_STD8X16__ASCII_32_95[] = {0xff,0x01,0x01,0x01,0x01,0x01,0x01,0xff,0xff,0x80,0x80,0x80,0x80,0x80,0x80,0xff};

static __FontChar_t __FONT_STD8X16[] = {
	{ .c = ' ' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_0  },
	{ .c = '!' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_1  },
	{ .c = '"' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_2  },
	{ .c = '#' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_3  },
	{ .c = '$' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_4  },
	{ .c = '%' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_5  },
	{ .c = '&' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_6  },
	{ .c = '\'', .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_7  },
	{ .c = '(' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_8  },
	{ .c = ')' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_9  },
	{ .c = '*' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_10 },
	{ .c = '+' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_11 },
	{ .c = ',' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_12 },
	{ .c = '-' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_13 },
	{ .c = '.' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_14 },
	{ .c = '/' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_15 },
	{ .c = '0' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_16 },
	{ .c = '1' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_17 },
	{ .c = '2' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_18 },
	{ .c = '3' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_19 },
	{ .c = '4' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_20 },
	{ .c = '5' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_21 },
	{ .c = '6' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_22 },
	{ .c = '7' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_23 },
	{ .c = '8' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_24 },
	{ .c = '9' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_25 },
	{ .c = ':' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_26 },
	{ .c = ';' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_27 },
	{ .c = '<' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_28 },
	{ .c = '=' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_29 },
	{ .c = '>' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_30 },
	{ .c = '?' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_31 },
	{ .c = '@' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_32 },
	{ .c = 'A' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_33 },
	{ .c = 'B' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_34 },
	{ .c = 'C' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_35 },
	{ .c = 'D' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_36 },
	{ .c = 'E' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_37 },
	{ .c = 'F' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_38 },
	{ .c = 'G' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_39 },
	{ .c = 'H' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_40 },
	{ .c = 'I' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_41 },
	{ .c = 'J' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_42 },
	{ .c = 'K' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_43 },
	{ .c = 'L' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_44 },
	{ .c = 'M' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_45 },
	{ .c = 'N' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_46 },
	{ .c = 'O' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_47 },
	{ .c = 'P' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_48 },
	{ .c = 'Q' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_49 },
	{ .c = 'R' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_50 },
	{ .c = 'S' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_51 },
	{ .c = 'T' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_52 },
	{ .c = 'U' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_53 },
	{ .c = 'V' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_54 },
	{ .c = 'W' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_55 },
	{ .c = 'X' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_56 },
	{ .c = 'Y' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_57 },
	{ .c = 'Z' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_58 },
	{ .c = '[' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_59 },
	{ .c = '\\', .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_60 },
	{ .c = ']' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_61 },
	{ .c = '^' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_62 },
	{ .c = '_' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_63 },
	{ .c = '`' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_64 },
	{ .c = 'a' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_65 },
	{ .c = 'b' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_66 },
	{ .c = 'c' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_67 },
	{ .c = 'd' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_68 },
	{ .c = 'e' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_69 },
	{ .c = 'f' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_70 },
	{ .c = 'g' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_71 },
	{ .c = 'h' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_72 },
	{ .c = 'i' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_73 },
	{ .c = 'j' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_74 },
	{ .c = 'k' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_75 },
	{ .c = 'l' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_76 },
	{ .c = 'm' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_77 },
	{ .c = 'n' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_78 },
	{ .c = 'o' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_79 },
	{ .c = 'p' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_80 },
	{ .c = 'q' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_81 },
	{ .c = 'r' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_82 },
	{ .c = 's' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_83 },
	{ .c = 't' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_84 },
	{ .c = 'u' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_85 },
	{ .c = 'v' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_86 },
	{ .c = 'w' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_87 },
	{ .c = 'x' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_88 },
	{ .c = 'y' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_89 },
	{ .c = 'z' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_90 },
	{ .c = '{' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_91 },
	{ .c = '|' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_92 },
	{ .c = '}' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_93 },
	{ .c = '~' , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_94 },
	{ .c = 127 , .height = 16 , .width = 8 , .byte = __FONT_STD8X16__ASCII_32_95 },
};

//================================================ End of Font Config ================================================//
//================================================ End of Font Config ================================================//
//================================================ End of Font Config ================================================//

//================================================= Internal Config ==================================================//
//================================================= Internal Config ==================================================//
//================================================= Internal Config ==================================================//

struct __GUI_XY_t{
	unsigned int x;
	unsigned int y;
};
typedef struct __GUI_XY_t __GUI_XY_t;

static struct __Screen_t{
#if   ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	PixelUnit_t buffer[ GUI_PAGEs  ][ GUI_X_WIDTH ];
#elif ( GUI_DISPLAY_MODE == GUI_SINGLE_PIXEL )
	PixelUnit_t buffer[ GUI_Y_WIDTH][ GUI_X_WIDTH ];
#endif
	Pixel_t          bkColor;
	Pixel_t          penColor;
	unsigned int     penSize;
	
	__GUI_XY_t       txtPos;
	__FontChar_t*    pFont;



}Screen;

static void __insertPixel(unsigned int x,unsigned int y){

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	int temp = y&0x07;
	switch(temp){
		case 0:Screen.buffer[ y>>3 ][x].bit0 = (Screen.penColor&0x01);break;
		case 1:Screen.buffer[ y>>3 ][x].bit1 = (Screen.penColor&0x01);break;
		case 2:Screen.buffer[ y>>3 ][x].bit2 = (Screen.penColor&0x01);break;
		case 3:Screen.buffer[ y>>3 ][x].bit3 = (Screen.penColor&0x01);break;
		case 4:Screen.buffer[ y>>3 ][x].bit4 = (Screen.penColor&0x01);break;
		case 5:Screen.buffer[ y>>3 ][x].bit5 = (Screen.penColor&0x01);break;
		case 6:Screen.buffer[ y>>3 ][x].bit6 = (Screen.penColor&0x01);break;
		case 7:Screen.buffer[ y>>3 ][x].bit7 = (Screen.penColor&0x01);break;
		default:break;
	}
#else
	Screen.buffer[y][x].data = Screen.penColor;
#endif
}

static void __erasePixel(unsigned int x,unsigned int y){
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	int temp = y&0x07;
	switch(temp){
		case 0:Screen.buffer[ y>>3 ][x].bit0 = (Screen.bkColor&0x01);break;
		case 1:Screen.buffer[ y>>3 ][x].bit1 = (Screen.bkColor&0x01);break;
		case 2:Screen.buffer[ y>>3 ][x].bit2 = (Screen.bkColor&0x01);break;
		case 3:Screen.buffer[ y>>3 ][x].bit3 = (Screen.bkColor&0x01);break;
		case 4:Screen.buffer[ y>>3 ][x].bit4 = (Screen.bkColor&0x01);break;
		case 5:Screen.buffer[ y>>3 ][x].bit5 = (Screen.bkColor&0x01);break;
		case 6:Screen.buffer[ y>>3 ][x].bit6 = (Screen.bkColor&0x01);break;
		case 7:Screen.buffer[ y>>3 ][x].bit7 = (Screen.bkColor&0x01);break;
		default:break;
	}
#else
	Screen.buffer[y][x].data = Screen.bkColor;
#endif
}

static void __clearFrameBuffer(void){
	if(sizeof(Pixel_t) == 1)
#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
		memset(Screen.buffer[0], Screen.bkColor ,(GUI_PAGEs   * GUI_X_WIDTH));
#else
		memset(Screen.buffer[0], Screen.bkColor ,(GUI_X_WIDTH * GUI_Y_WIDTH));
#endif
	else	
		for(size_t i=0;i<GUI_Y_WIDTH*GUI_X_WIDTH;i++){
	        *(&(Screen.buffer[0][0].data)+i) = Screen.bkColor;
	    }
}
#include <stdlib.h>
static void* __mallocFrameBuffer(unsigned long size){
	return malloc(size);
}

#define __free(p) free(p)

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
static void __clearPageArea(unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end){
	Pixel_t* p;
	unsigned int length = column_end - column_start+1;
	for(unsigned int page=page_start;page<=page_end;page++){
		p  = (Pixel_t*)&Screen.buffer[page];
		p += column_start;
		memset(p, Screen.bkColor ,(length)*sizeof(Screen.buffer[0][0].data));
	}
}
#endif

//============================================= End of Internal Config ===============================================//
//============================================= End of Internal Config ===============================================//
//============================================= End of Internal Config ===============================================//

//================================================== Display Config ==================================================//
//================================================== Display Config ==================================================//
//================================================== Display Config ==================================================//

void GUI_RefreashScreen(void){
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	for(unsigned int page=0;page<GUI_PAGEs;page++)  {
		(*GUI_API_DrawPageColumn)(page,0,GUI_X_WIDTH,(Pixel_t*)&Screen.buffer[ page ]);
	}
#else
	if(GUI_API_DrawArea != NULL)
		(*GUI_API_DrawArea)(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1,&(Screen.buffer[0][0].data));
	else{
		for(int x=0;x<GUI_X_WIDTH;x++)
			for(int y=0;y<GUI_Y_WIDTH;y++)
				(*GUI_API_DrawPixel)(x,y,Screen.buffer[y][x].data);
	}
#endif
}

void GUI_RefreashArea(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2){
	unsigned int x_end   = GUI_MAX(x1,x2);
    unsigned int x_start = GUI_MIN(x1,x2);
    unsigned int y_end   = GUI_MAX(y1,y2);
    unsigned int y_start = GUI_MIN(y1,y2);
    unsigned int x_width = x_end-x_start+1;
    unsigned int y_width = y_end-y_start+1;

    if(GUI_API_DrawArea != NULL){
    	Pixel_t* p = (Pixel_t*)__mallocFrameBuffer((x_width)*(y_width)*sizeof(Pixel_t));
    	for(int y=0;y<y_width;y++){
	        memcpy(&p[x_width*y], &Screen.buffer[y_start+y][x_start].data, x_width*sizeof(Pixel_t));
	    }
		(*GUI_API_DrawArea)(x_start,y_start,x_end,y_end,p);
    }
	else{
		for(int y=y_start;y<=y_end;y++)
			for(int x=x_start;x<=x_end;x++)
				(*GUI_API_DrawPixel)(x,y,Screen.buffer[y][x].data);
	}
}

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
void GUI_RefreashPageArea(unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end){	
	Pixel_t* p;
	unsigned int column_num = column_end-column_start+1;
	for(unsigned int page=page_start;page<=page_end;page++){
		p  = (Pixel_t*)&Screen.buffer[ page ];
		p += column_start;
		(*GUI_API_DrawPageColumn)(page,column_start,column_num,p);
	}
}
#endif

void GUI_FillAll(Pixel_t data){
	if(sizeof(Pixel_t) == 1)
#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
		memset(Screen.buffer[0], data ,(GUI_PAGEs   * GUI_X_WIDTH));
#else
		memset(Screen.buffer[0], data ,(GUI_X_WIDTH * GUI_Y_WIDTH));
#endif
	else	
		for(size_t i=0;i<GUI_Y_WIDTH*GUI_X_WIDTH;i++){
	        *(&(Screen.buffer[0][0].data)+i) = data;
	    }
	GUI_RefreashScreen();
}

void GUI_ClearAll(void){
	GUI_FillAll(Screen.bkColor);
}

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
void GUI_ClearPageArea(unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end,...){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(page_start <= page_end,"<page_start> should be smaller than <page_end>.");
    (*GUI_API_AssertParam)(page_start < GUI_PAGEs && page_end < GUI_PAGEs,"Page index is out of range.");
#endif
    va_list ap;
	va_start(ap,column_end);
	va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	__clearPageArea(page_start,page_end,column_start,column_end);
	if(onlyChangeBuffer!=true){
		GUI_RefreashScreen();
	}
}
#endif

void GUI_SetPenColor(Pixel_t color){
	Screen.penColor = color;
}

Pixel_t GUI_GetPenColor(void){
	return Screen.penColor;
}

void GUI_SetBackColor(Pixel_t color){
	Screen.bkColor = color;
}

Pixel_t GUI_GetBackColor(void){
	return Screen.bkColor;
}

void GUI_SetPenSize(unsigned int penSize){
#if GUI_ASSERT
	(*GUI_API_AssertParam)(penSize < GUI_MIN(GUI_X_WIDTH,GUI_Y_WIDTH),"Pen size is too big.");
#endif
	Screen.penSize = penSize;
}

unsigned int GUI_GetPenSize(void){
	return Screen.penSize;
}

void GUI_SetFont(int GUI_FONT_xxx){
	switch(GUI_FONT_xxx){
		case GUI_FONT_Standard_Small  : Screen.pFont = __FONT_STD6X8  ;break;
		case GUI_FONT_Standard_Middle : Screen.pFont = __FONT_STD8X16 ;break;
		
#if GUI_ASSERT
	    default: (*GUI_API_AssertParam)(false,"Wrong Text Font Type.");break;
#else
	    default: Screen.pFont = __FONT_STD6X8  ;break;
#endif
	}	
}

void GUI_SetTextPos(unsigned int x,unsigned int y){
	Screen.txtPos.x = x;
	Screen.txtPos.x = y;
}

//=============================================== End of Display Config ==============================================//
//=============================================== End of Display Config ==============================================//
//=============================================== End of Display Config ==============================================//


//================================================= Graphic Function =================================================//
//================================================= Graphic Function =================================================//
//================================================= Graphic Function =================================================//

void GUI_DrawPixel(unsigned int x,unsigned int y,...){
#if GUI_ASSERT
	(*GUI_API_AssertParam)(x < GUI_X_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif

	va_list ap;
	va_start(ap,y);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();

	__insertPixel(x,y);

	if(onlyChangeBuffer != true){
		if(clearScreen==true){
			GUI_RefreashScreen();
		}else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)	
			unsigned char page = y>>3;
			Pixel_t* p = (Pixel_t*)(&Screen.buffer[page]);
			p+=x;
			(*GUI_API_DrawPageColumn)(page,x,1,p);
#else
			(*GUI_API_DrawPixel)(x,y,Screen.buffer[y][x].data);
#endif
		}
	}

}

void GUI_FillRect(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,...){
#if GUI_ASSERT
	(*GUI_API_AssertParam)(x1 < GUI_X_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(x2 < GUI_X_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y1 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y2 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif
	va_list ap;
	va_start(ap,y2);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)

	unsigned char page_start   = (GUI_MIN(y1,y2))>>3;
	unsigned char page_end     = (GUI_MAX(y1,y2))>>3;
	unsigned char column_start = (GUI_MIN(x1,x2));
	unsigned char column_end   = (GUI_MAX(x1,x2));
	for(size_t page=page_start;page<=page_end;page++){
		unsigned char y_max = GUI_MAX(y1,y2);
		unsigned char y_min = GUI_MIN(y1,y2);
		if(page==page_start){
			while( y_min < ((page+1)<<3) && y_min <= y_max)
				__insertPixel(column_start,y_min++);
			
			memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
			continue;
		}
		if(page==page_end){
			while( y_max >= (page<<3) && y_max >= y_min)
				__insertPixel(column_start,y_max--);

			memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
			continue;
		}
		memset(Screen.buffer[page]+column_start,Screen.penColor,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
	}

#else

	unsigned int x_end   = GUI_MAX(x1,x2);
    unsigned int x_start = GUI_MIN(x1,x2);
    unsigned int y_end   = GUI_MAX(y1,y2);
    unsigned int y_start = GUI_MIN(y1,y2);

	for(unsigned int y=y_start;y<=y_end;y++){
		for(unsigned int x=x_start;x<=x_end;x++)
			Screen.buffer[y][x].data = Screen.penColor;
	}

#endif

	if(onlyChangeBuffer != true){
		if(clearScreen==true){
			GUI_RefreashScreen();
		}else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			Pixel_t* p;
			for(unsigned int page=page_start;page<=page_end;page++){
				p = (Pixel_t*)(&Screen.buffer[page]);
				p += column_start;
				(*GUI_API_DrawPageColumn)(page,column_start,column_end-column_start,p );
			}
#else
			GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
		}
	}

}

void GUI_DrawRect(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,...){
#if GUI_ASSERT
	(*GUI_API_AssertParam)(x1 < GUI_X_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(x2 < GUI_X_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y1 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y2 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif
	va_list ap;
	va_start(ap,y2);
	const int clearScreen = va_arg(ap,int);
	va_end(ap);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	if(clearScreen==true)
		__clearFrameBuffer();

	BYTE penSize      = Screen.penSize;

	unsigned char page_start   = (GUI_MIN(y1,y2))>>3;
	unsigned char page_end     = (GUI_MAX(y1,y2))>>3;
	unsigned char column_start = (GUI_MIN(x1,x2));
	unsigned char column_end   = (GUI_MAX(x1,x2));

	for(size_t page=page_start;page<=page_end;page++){
		unsigned char y_max = GUI_MAX(y1,y2);
		unsigned char y_min = GUI_MIN(y1,y2);
		if(page==page_start){
			while( y_min < ((page+1)<<3) && y_min <= y_max)
				__insertPixel(column_start,y_min++);
			
			memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
			continue;
		}
		if(page==page_end){
			while( y_max >= (page<<3) && y_max >= y_min)
				__insertPixel(column_start,y_max--);

			memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
			continue;
		}
		memset(Screen.buffer[page]+column_start,Screen.penColor,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
	}

	unsigned char x3 = GUI_MIN(x1,x2)+penSize;
	unsigned char x4 = GUI_MAX(x1,x2)-penSize;

	unsigned char y3 = GUI_MIN(y1,y2)+penSize;
	unsigned char y4 = GUI_MAX(y1,y2)-penSize;

	if(y3 < y4 && x3 < x4){
		page_start   = (GUI_MIN(y3,y4))/8;
		page_end     = (GUI_MAX(y3,y4))/8;
		column_start = (GUI_MIN(x3,x4));
		column_end   = (GUI_MAX(x3,x4));

		for(size_t page=page_start;page<=page_end;page++){
			unsigned char y_max = GUI_MAX(y3,y4);
			unsigned char y_min = GUI_MIN(y3,y4);
			if(page==page_start){
				while( y_min < ((page+1)<<3) && y_min <= y_max)
					__erasePixel(column_start,y_min++);
				
				memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
				continue;
			}
			if(page==page_end){
				while( y_max >= (page<<3) && y_max >= y_min)
					__erasePixel(column_start,y_max--);

				memset(Screen.buffer[page]+column_start,Screen.buffer[page][column_start].data,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
				continue;
			}
			memset(Screen.buffer[page]+column_start,Screen.bkColor,(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
		}
	}

	page_start   = (GUI_MIN(y1,y2))/8;
	page_end     = (GUI_MAX(y1,y2))/8;
	column_start = (GUI_MIN(x1,x2));
	column_end   = (GUI_MAX(x1,x2));

	if(clearScreen == true){
		GUI_RefreashScreen();
	}else{
		Pixel_t* p;
		for(unsigned int page=page_start;page<=page_end;page++){
			p = (Pixel_t*)(&Screen.buffer[page]);
			p += column_start;
			(*GUI_API_DrawPageColumn)(page,column_start,column_end-column_start,p );
		}	
	}

#endif
}

void GUI_FillCircle(unsigned int x, unsigned int y, int r,...){
#if GUI_ASSERT
	(*GUI_API_AssertParam)(x<GUI_X_WIDTH ,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y<GUI_Y_WIDTH ,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(r >= 0        ,"Radius should be bigger than zero.");
#endif
	va_list ap;
	va_start(ap,r);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	unsigned int page_start   = (GUI_LIMIT(y-r,0,GUI_Y_WIDTH))>>3;
	unsigned int page_end     = (GUI_LIMIT(y+r,0,GUI_Y_WIDTH))>>3;
	unsigned int column_start = (GUI_LIMIT(x-r,0,GUI_X_WIDTH));
	unsigned int column_end   = (GUI_LIMIT(x+r,0,GUI_X_WIDTH));

	if(clearScreen==true)
		__clearFrameBuffer();
	unsigned int r_2 = r*r;
	for(int i = -r;i <= r;i++){
		for(int j = -r;j <= r;j++){
			if(  (x-i)<GUI_X_WIDTH && y-j<GUI_Y_WIDTH && i*i+j*j <= r_2 )
				__insertPixel(x-i,y-j);
		}
	}
	if(onlyChangeBuffer != true){
		if(clearScreen == true){
			GUI_RefreashScreen();
		}else{
			Pixel_t* p;
			for(unsigned int page=page_start;page<=page_end;page++){
				p = (Pixel_t*)(&Screen.buffer[page]);
				p += column_start;
				(*GUI_API_DrawPageColumn)(page,column_start,column_end-column_start,p );
			}
		}
	}
#endif
}

void GUI_DrawCircle(unsigned int x, unsigned int y, int r,...){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x<GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y<GUI_Y_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(r >= 0       ,"Radius should be bigger than zero.");
#endif
    
	va_list ap;
	va_start(ap,r);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	unsigned int page_start   = (GUI_LIMIT(y-r,0,GUI_Y_WIDTH))>>3;
	unsigned int page_end     = (GUI_LIMIT(y+r,0,GUI_Y_WIDTH))>>3;
	unsigned int column_start = (GUI_LIMIT(x-r,0,GUI_X_WIDTH));
	unsigned int column_end   = (GUI_LIMIT(x+r,0,GUI_X_WIDTH));

	if(clearScreen==true)
		__clearFrameBuffer();

	Pixel_t penColor = Screen.penColor;
	Pixel_t bkColor  = Screen.bkColor;
	GUI_FillCircle(x,y,r,false,true);
	GUI_SetPenColor(bkColor);
	GUI_FillCircle(x,y,r-Screen.penSize,false,true);
	GUI_SetPenColor(penColor);
	if(onlyChangeBuffer != true){
		if(clearScreen == true){
			GUI_RefreashScreen();
		}else{
			Pixel_t* p;
			for(unsigned int page=page_start;page<=page_end;page++){
				p = (Pixel_t*)(&Screen.buffer[page]);
				p += column_start;
				(*GUI_API_DrawPageColumn)(page,column_start,column_end-column_start,p );
			}
		}
	}
#endif
}

void GUI_FillEllipse(unsigned int x, unsigned int y,int rx, int ry,...){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x<GUI_X_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y<GUI_Y_WIDTH,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(rx >= 0      ,"Radius X should be bigger than zero."); 
    (*GUI_API_AssertParam)(ry >= 0      ,"Radius Y should be bigger than zero.");
#endif

	va_list ap;
	va_start(ap,ry);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)

	unsigned int page_start   = (GUI_LIMIT(y-ry,0,GUI_Y_WIDTH))>>3;
	unsigned int page_end     = (GUI_LIMIT(y+ry,0,GUI_Y_WIDTH))>>3;
	unsigned int column_start = (GUI_LIMIT(x-rx,0,GUI_X_WIDTH));
	unsigned int column_end   = (GUI_LIMIT(x+rx,0,GUI_X_WIDTH));

	if(clearScreen==true)
		__clearFrameBuffer();

	unsigned int rx_2   = rx*rx;
	unsigned int ry_2   = ry*ry;
	unsigned int rxry_2 = rx_2*ry_2;

	for(int i = -rx;i <= rx;i++){
		for(int j = -ry;j <= ry;j++){
			if(  (x-i)<GUI_X_WIDTH && y-j<GUI_Y_WIDTH && ry_2*i*i+rx_2*j*j < rxry_2 )
				__insertPixel(x-i,y-j);
		}
	}

	if(onlyChangeBuffer != true){
		if(clearScreen == true){
			GUI_RefreashScreen();
		}else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif
		}
	}
#endif
}

void GUI_DrawEllipse(unsigned int x, unsigned int y,int rx, int ry,...){
#if GUI_ASSERT
    (*GUI_API_AssertParam)(x<GUI_X_WIDTH      ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(y<GUI_Y_WIDTH      ,"X-Y cordination is out of range.");
    (*GUI_API_AssertParam)(rx >= 0            ,"Radius X should be bigger than zero.");
    (*GUI_API_AssertParam)(ry >= 0            ,"Radius Y should be bigger than zero.");
	(*GUI_API_AssertParam)(Screen.penSize < rx,"Graphic size should be bigger than Pen size or maybe pen size is too big");
	(*GUI_API_AssertParam)(Screen.penSize < ry,"Graphic size should be bigger than Pen size or maybe pen size is too big");
#endif

	va_list ap;
	va_start(ap,ry);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)

	unsigned int page_start   = (GUI_LIMIT(y-ry,0,GUI_Y_WIDTH))>>3;
	unsigned int page_end     = (GUI_LIMIT(y+ry,0,GUI_Y_WIDTH))>>3;
	unsigned int column_start = (GUI_LIMIT(x-rx,0,GUI_X_WIDTH));
	unsigned int column_end   = (GUI_LIMIT(x+rx,0,GUI_X_WIDTH));

	if(clearScreen==true)
		__clearFrameBuffer();

	Pixel_t penColor = Screen.penColor;
	Pixel_t bkColor  = Screen.bkColor;

	GUI_FillEllipse(x,y,rx               ,ry               ,false,true);
	GUI_SetPenColor(bkColor);
	GUI_FillEllipse(x,y,rx-Screen.penSize,ry-Screen.penSize,false,true);
	GUI_SetPenColor(penColor);

	if(onlyChangeBuffer != true){
		if(clearScreen == true){
			GUI_RefreashScreen();
		}else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)			
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif			
		}
	}
#endif
}

void GUI_DrawLine(int x1,int y1,int x2,int y2,...){
#if GUI_ASSERT
	(*GUI_API_AssertParam)(0 <= x1         ,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(0 <= x2         ,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(0 <= y1         ,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(0 <= y2         ,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(x1 < GUI_X_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(x2 < GUI_X_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y1 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
	(*GUI_API_AssertParam)(y2 < GUI_Y_WIDTH,"X-Y cordination is out of range.");
#endif
	va_list ap;
	va_start(ap,y2);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int); 
	va_end(ap);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	if(clearScreen==true)
		__clearFrameBuffer();


	unsigned int page_start   = GUI_LIMIT( (signed)((GUI_MIN(y1,y2)-Screen.penSize)>>3) ,0 ,GUI_PAGEs);
	unsigned int page_end     = GUI_LIMIT( (signed)((GUI_MAX(y1,y2)+Screen.penSize)>>3) ,0 ,GUI_PAGEs);
	unsigned int column_start = GUI_LIMIT( (signed)(GUI_MIN(x1,x2)-Screen.penSize)      ,0 ,GUI_X_WIDTH-1);
	unsigned int column_end   = GUI_LIMIT( (signed)(GUI_MAX(x1,x2)+Screen.penSize)      ,0 ,GUI_X_WIDTH-1);

	if(x1 != x2){
		double K = ((double)(y1-y2)) / ((double)(x1-x2));
		double B = y1-K*x1;
		int x1_tmp = 0;
		int x2_tmp = 0;
		int y1_tmp = 0;
		int y2_tmp = 0;
		if( -1.0 < K && K < 1.0 ){
			if(x1 < x2){	
				x1_tmp = x1; y1_tmp = y1;
				x2_tmp = x2; y2_tmp = y2;
			}else{
				x1_tmp = x2; y1_tmp = y2;
				x2_tmp = x1; y2_tmp = y1;
			}
			for(unsigned int x = x1_tmp;x <= x2_tmp;x++){
				int cnt    = (int)(Screen.penSize>>1);
				int offset = -cnt;
				if(Screen.penSize%2==0) 
					offset++;
				for(;offset<=cnt;offset++ ){
					__insertPixel(x, (unsigned char)(K*x+B+offset) );
				}
			}
		}else{
			if(y1 < y2){
				x1_tmp = x1; y1_tmp = y1;
				x2_tmp = x2; y2_tmp = y2;
			}else{
				x1_tmp = x2; y1_tmp = y2;
				x2_tmp = x1; y2_tmp = y1;
			}
			for(unsigned int y = y1_tmp;y <= y2_tmp;y++){
				int cnt    = (int)(Screen.penSize>>1);
				int offset = -cnt;
				if(Screen.penSize%2==0) 
					offset++;
				for(;offset<=cnt;offset++ ){
					__insertPixel((unsigned char)((y-B)/K+offset),y );
				}
			}
		}
	}else{
		unsigned int page_start   = (GUI_MIN(y1,y2))>>3;
		unsigned int page_end     = (GUI_MAX(y1,y2))>>3;
		unsigned int column_start = (GUI_MIN(x1,x2)); 

		int offset = (int)(Screen.penSize>>1);

		for(int page=page_start;page<=page_end;page++){
			unsigned char y_max = GUI_MAX(y1,y2);
			unsigned char y_min = GUI_MIN(y1,y2);
			if(page==page_start){
				while( y_min < ((page+1)<<3) && y_min <= y_max)
					__insertPixel(column_start,y_min++);
				
				memset(Screen.buffer[page]+column_start-offset,Screen.buffer[page][column_start].data,(Screen.penSize)*sizeof(Screen.buffer[0][0].data));
				continue;
			}
			if(page==page_end){
				while( y_max >= (page<<3) && y_max >= y_min)
					__insertPixel(column_start,y_max--);

				memset(Screen.buffer[page]+column_start-offset,Screen.buffer[page][column_start].data,(Screen.penSize)*sizeof(Screen.buffer[0][0].data));
				continue;
			}
			memset(Screen.buffer[page]+column_start-offset,Screen.bkColor,(Screen.penSize)*sizeof(Screen.buffer[0][0].data));
		}
	}

	if(Screen.penSize>=3){
		GUI_FillCircle(x1,y1,Screen.penSize>>1,false,true);
		GUI_FillCircle(x2,y2,Screen.penSize>>1,false,true);
	}
	if(onlyChangeBuffer != true){
		if(clearScreen == true){
			GUI_RefreashScreen();
		}else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)			
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif			
		}
	}
#endif
}

void GUI_DrawWave(int A,float w,float phi,int x_start,int x_end,int y_level,...){
	A = abs(A);
	unsigned int page_start   = GUI_LIMIT( (y_level-A)>>3 ,0 ,GUI_PAGEs);
	unsigned int page_end     = GUI_LIMIT( (y_level+A)>>3 ,0 ,GUI_PAGEs);
	unsigned int column_start = GUI_LIMIT( (x_start  )    ,0 ,GUI_X_WIDTH-1);
	unsigned int column_end   = GUI_LIMIT( (x_end    )    ,0 ,GUI_X_WIDTH-1);

	va_list ap;
	va_start(ap,y_level);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();


	unsigned int x = x_start,x_old = x_start ,y_old = y_level,y = y_level;
	for(;x<=x_end;x++){
		y = (unsigned int)(y_level + A*sin(w*x+phi));
		// if(Screen.penSize == 1)
		// 	__insertPixel( x,(unsigned int)(y_level + A*sin(w*x+phi)) );
		// else
		// 	GUI_FillCircle(x,(unsigned int)(y_level + A*sin(w*x+phi)),Screen.penSize,false,true);

		GUI_DrawLine(x_old,y_old,x,y,false,true);	
		x_old = x;
		y_old = y;
	}

	if(onlyChangeBuffer!=true){
		if(clearScreen == true){
			GUI_RefreashScreen();
		}else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif			
		}
	}

}

void GUI_FillTriangle(int x1,int y1,int x2,int y2,int x3,int y3,...){
	
// 	unsigned int x_start;
//     unsigned int x_end;
//     unsigned int y_start;
//     unsigned int y_end;

// 	unsigned int page_start;
// 	unsigned int page_end;
// 	unsigned int column_start;
// 	unsigned int column_end;

// 	va_list ap;
// 	va_start(ap,y3);
// 	const int clearScreen      = va_arg(ap,int);
// 	const int onlyChangeBuffer = va_arg(ap,int);
// 	va_end(ap);

// 	if(clearScreen==true)
// 		__clearFrameBuffer();

// 	int XY[3][2] = {{x1,y1},{x2,y2},{x3,y3}};

// 	int XY_x[3][2],XY_y[3][2];
// 	if(x1 > x2){
// 		if(x1 > x3){
// 			XY_x[0][0] = x1; 
// 			XY_x[0][1] = y1;
// 			if(x2 > x3)  {XY_x[1][0] = x2;XY_x[1][1] = y2;XY_x[2][0] = x3;XY_x[2][1] = y3;}
// 			else         {XY_x[1][0] = x3;XY_x[1][1] = y3;XY_x[2][0] = x2;XY_x[2][1] = y2;}
// 		}else{    
// 			XY_x[0][0] = x3; 
// 			XY_x[0][1] = y3;
// 			if(x2 > x1)  {XY_x[1][0] = x2;XY_x[1][1] = y2;XY_x[2][0] = x1;XY_x[2][1] = y1;}
// 			else         {XY_x[1][0] = x1;XY_x[1][1] = y1;XY_x[2][0] = x2;XY_x[2][1] = y2;}
// 		}
// 	}else{
// 		if(x2 > x3){
// 			XY_x[0][0] = x2; 
// 			XY_x[0][1] = y2;
// 			if(x1 > x3)  {XY_x[1][0] = x1;XY_x[1][1] = y1;XY_x[2][0] = x3;XY_x[2][1] = y3;}
// 			else         {XY_x[1][0] = x3;XY_x[1][1] = y3;XY_x[2][0] = x1;XY_x[2][1] = y1;}
// 		}else{    
// 			XY_x[0][0] = x3; 
// 			XY_x[0][1] = y3;
// 			XY_x[1][0] = x2;
// 			XY_x[1][1] = y2;
// 			XY_x[2][0] = x1;
// 			XY_x[2][1] = y1;
// 		}
// 	}

// 	if(y1 > y2){
// 		if(y1 > y3){
// 			XY_y[0][0] = x1; 
// 			XY_y[0][1] = y1;
// 			if(y2 > y3)  {XY_y[1][0] = x2;XY_y[1][1] = y2;XY_y[2][0] = x3;XY_y[2][1] = y3;}
// 			else         {XY_y[1][0] = x3;XY_y[1][1] = y3;XY_y[2][0] = x2;XY_y[2][1] = y2;}
// 		}else{    
// 			XY_y[0][0] = x3; 
// 			XY_y[0][1] = y3;
// 			if(y2 > y1)  {XY_y[1][0] = x2;XY_y[1][1] = y2;XY_y[2][0] = x1;XY_y[2][1] = y1;}
// 			else         {XY_y[1][0] = x1;XY_y[1][1] = y1;XY_y[2][0] = x2;XY_y[2][1] = y2;}
// 		}
// 	}else{
// 		if(y2 > y3){
// 			XY_y[0][0] = x2; 
// 			XY_y[0][1] = y2;
// 			if(y1 > y3)  {XY_y[1][0] = x1;XY_y[1][1] = y1;XY_y[2][0] = x3;XY_y[2][1] = y3;}
// 			else         {XY_y[1][0] = x3;XY_y[1][1] = y3;XY_y[2][0] = x1;XY_y[2][1] = y1;}
// 		}else{    
// 			XY_y[0][0] = x3; 
// 			XY_y[0][1] = y3;
// 			XY_y[1][0] = x2;
// 			XY_y[1][1] = y2;
// 			XY_y[2][0] = x1;
// 			XY_y[2][1] = y1;
// 		}
// 	}

// 	column_start = x_start = XY_x[2][0];
// 	column_end   = x_end   = XY_x[0][0];
// 	y_start                = XY_y[2][1];
// 	y_end                  = XY_y[0][1];
// 	page_start   = ((y_start)>>3);
// 	page_end     = ((y_end)>>3);

// 	for(int y=y_start;y<=y_end;y++){
// 		for(int x=x_start;x<=x_end;x++){
// 			int j=0,i=2;
// 			for(;j<3;i=j++){
// 				int px = XY[i][1] - XY[j][1];
// 				int py = XY[j][0] - XY[i][0];
// 				int qx = x        - XY[i][0];
// 				int qy = y        - XY[i][1];
// 				if(px*qx+py*qy <= 0){
// 					__insertPixel(x,y);
// 					break;
// 				}
// 			}
// 		}
// 	}

// 	if(onlyChangeBuffer!=true){
// 		if(clearScreen==true)
// 			GUI_RefreashScreen();
// 		else
// #if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
// 			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
// #endif
// 	}
}

void GUI_DrawTriangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,...){
	

    unsigned int y_start      = GUI_LIMIT( ( GUI_MIN( ( GUI_MIN(y1,y2) ) ,y3)  )    ,0 ,GUI_X_WIDTH-1);
    unsigned int y_end        = GUI_LIMIT( ( GUI_MAX( ( GUI_MAX(y1,y2) ) ,y3)  )    ,0 ,GUI_X_WIDTH-1);

	unsigned int page_start   = GUI_LIMIT( (y_start)>>3 ,0 ,GUI_PAGEs);
	unsigned int page_end     = GUI_LIMIT( (y_end  )>>3 ,0 ,GUI_PAGEs);
	unsigned int column_start = GUI_LIMIT( ( GUI_MIN( ( GUI_MIN(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);
	unsigned int column_end   = GUI_LIMIT( ( GUI_MAX( ( GUI_MAX(x1,x2) ) ,x3)  )    ,0 ,GUI_X_WIDTH-1);

	va_list ap;
	va_start(ap,y3);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();

	GUI_DrawLine(x1,y1,x2,y2,false,true);
	GUI_DrawLine(x2,y2,x3,y3,false,true);
	GUI_DrawLine(x3,y3,x1,y1,false,true);

	if(onlyChangeBuffer!=true){
		if(clearScreen==true)
			GUI_RefreashScreen();
		else
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif
	}
}

void GUI_CONTI_DrawLine(unsigned int (*p)[2],const size_t num,...){

	for(size_t i=0;i<num-1;i++){
		GUI_DrawLine((*p)[0],(*p)[1],(*(p+1))[0],(*(p+1))[1],false,false);
		p++;
	}
}

//============================================== End of Graphic Function ==============================================//
//============================================== End of Graphic Function ==============================================//
//============================================== End of Graphic Function ==============================================//

//=================================================== Text Function ===================================================//
//=================================================== Text Function ===================================================//
//=================================================== Text Function ===================================================//


void GUI_DispChar(unsigned char c,...){

	c = GUI_LIMIT( (c) , ' ' , '~' );
	struct __Screen_t*   s     = &Screen;
	struct __FontChar_t* pChar = (s->pFont + c - 32);

	if(s->txtPos.x + pChar->width > GUI_X_WIDTH){
		s->txtPos.x = 0;
		s->txtPos.y += pChar->height;
	}
	if(s->txtPos.y >= GUI_Y_WIDTH){
		s->txtPos.y = 0;
	}

	unsigned int page_start    = ((s->txtPos.y)>>3);
	unsigned int page_end      = ((s->txtPos.y + pChar->height-1)>>3);
	unsigned int column_start  = s->txtPos.x;
	unsigned int column_end    = s->txtPos.x + pChar->width -1;

	va_list ap;
	va_start(ap,c);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();

	for(uint y=0;y < pChar->height;y++){
		for(uint x=0;x < pChar->width ;x++){
			if( (s->txtPos.x + x) >= GUI_X_WIDTH )
				while(1);
			if( (s->txtPos.y + y) >= GUI_Y_WIDTH )
				while(1);

			if(  ( ((*(pChar->byte + (y&0xfff8) + x))>>(y&0x07))&0x01  ) == 1 )
		//  if( ((*(pChar->byte + (y/8)*8    + x)) >> (y%8   ))&0x01  )
				__insertPixel(s->txtPos.x + x,s->txtPos.y + y);
			else
				__erasePixel (s->txtPos.x + x,s->txtPos.y + y);
		}
	}

	if(onlyChangeBuffer!=true){
		if(clearScreen==true)
			GUI_RefreashScreen();
		else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif
		}
	}

	s->txtPos.x += pChar->width;
	if( s->txtPos.x >= GUI_X_WIDTH ){
		s->txtPos.x = 0;
		s->txtPos.y += pChar->height;
	}
	if( s->txtPos.y >= GUI_Y_WIDTH ){
		s->txtPos.y = 0;
	}
	 
}

//================================================ End of Text Function ================================================//
//================================================ End of Text Function ================================================//
//================================================ End of Text Function ================================================//

//=================================================== Demo Function ===================================================//
//=================================================== Demo Function ===================================================//
//=================================================== Demo Function ===================================================//

#if GUI_DEMO
//Put the func into " While(1){ ... } "

inline void GUI_DEMO_MovingRect_1(void){
	const int radius   = 28;
	const int center_y = 32;
	const int center_x = 64;

	register float theater = 360.0;
	register unsigned int x,y;
	register unsigned int mov_x,mov_y;
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	while(theater > 0){
		x     = center_x+radius*cos(theater);
		y     = center_y+radius*sin(theater);
		mov_x = center_x+0.4*radius*sin(theater);
		mov_y = center_y+0.4*radius*cos(theater);
		GUI_DrawRect(mov_x,mov_y,x,y,true);

		theater-=(float)0.1;
	}
}

inline void GUI_DEMO_MovingRect_2(void){
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	for(unsigned int x = 0;x < 128;x++)
		GUI_DrawRect(x,127-(x>>1),64,32,true,false);
	for(unsigned int x = 0;x < 128;x++)
		GUI_DrawRect(x,x>>1,64,32,true,false);
}
#include <stdlib.h>
inline void GUI_DEMO_MovingRect_3(void){
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	GUI_DrawRect(rand()%128,rand()%64,rand()%128,rand()%64,true);
	unsigned long i = 0xffff;
	while(i--);
}

inline void GUI_DEMO_MovingEllipse_1(void){
	const int c = 20;
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	for(int a=1;a<=64-c;a++){
		GUI_FillEllipse(64,32,64-a,c,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)		
		GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif		
	}

	for(int b=32-c;b>=0;b--){
		GUI_FillEllipse(64,32,c,32-b,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea (0,7,64-c,64+c);
#endif	
	}

	for(int b=0;b<=32-c;b++){
		GUI_FillEllipse(64,32,c,32-b,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea (0,7,64-c,64+c);
#endif	
	}

	for(int a=64-c;a>0;a--){
		GUI_FillEllipse(64,32,64-a,c,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif	
	}
}

inline void GUI_DEMO_MovingEllipse_2(void){
	const int c = 20;
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	for(int a=1;a<=64-c;a++){
		GUI_DrawEllipse(64,32,64-a,c,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif
	}

	for(int b=32-c;b>=0;b--){
		GUI_DrawEllipse(64,32,c,32-b,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea (0,7,64-c,64+c);
#endif
	}

	for(int b=0;b<=32-c;b++){
		GUI_DrawEllipse(64,32,c,32-b,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea (0,7,64-c,64+c);
#endif
	}

	for(int a=64-c;a>0;a--){
		GUI_DrawEllipse(64,32,64-a,c,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea (1,6,a-1,64*2-a+1);
#endif
	}
}

inline void GUI_DEMO_MovingWave_1(void){
	const int x_start = 0;
	const int x_end   = GUI_X_WIDTH-1;
	const int y_level = GUI_Y_WIDTH>>1;
	const int A       = (int)(y_level/1.5);
	GUI_SetPenSize(2); 
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetBackColor(GUI_BLACK);
	for(float w=0.0;w<1.5;w+=0.01){
		GUI_DrawWave(A,w,0.0,x_start,x_end,y_level,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
#endif		
	}
	for(float w=1.5;w>0.0;w-=0.01){
		GUI_DrawWave(A,w,0.0,x_start,x_end,32,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)		
		GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
#endif		
	}
}

inline void GUI_DEMO_MovingWave_2(void){
	const int x_start = 0;
	const int x_end   = GUI_X_WIDTH-1;
	const int y_level = GUI_Y_WIDTH>>1;
	const int A       = (int)(y_level/1.5);
	const float w     = 0.2;
	GUI_SetPenSize(1); 
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetBackColor(GUI_BLACK);
	
	for(int phi=0;phi<=31;phi++){
		GUI_DrawWave(A,w,phi,x_start,x_end,y_level,true,true);
		GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
	}
}

inline void GUI_DEMO_Rotation_1(void){
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	for(double Ø=0;Ø<360;Ø+=0.1){
		const float π = 3.1415926;
		GUI_SetPenSize(3);
		GUI_DrawCircle(64,32,31,true,true);
		GUI_SetPenSize(1);
		GUI_DrawLine (64,32,64-23*cos(Ø)       ,32-23*sin(Ø)       ,false,true);
		GUI_DrawLine (64,32,64-23*cos(Ø+2*π/3) ,32-23*sin(Ø+2*π/3) ,false,true);
		GUI_DrawLine (64,32,64-23*cos(Ø-2*π/3) ,32-23*sin(Ø-2*π/3) ,false,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN) && (GUI_COLOR_TYPE == GUI_1Bit)
		GUI_RefreashPageArea(0,7,64-30,64+30);
#endif
	}
}

inline void GUI_DEMO_Blink_1(void){
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	for(int r=32;r>0;r--){
		GUI_FillCircle(64, 32, r,false,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN) && (GUI_COLOR_TYPE == GUI_1Bit)
		GUI_RefreashPageArea(0,7,64-r-1,64+r+1);
		GUI_ClearPageArea(0,7,64-r-1,64+r+1,false,true);
#endif
	}
}

inline void GUI_DEMO_Pattern_1(void){
	unsigned int penSize = GUI_GetPenSize(); 
	const int r = 20,ps = 3;
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(ps);
	GUI_DrawRect(64-r-ps,32-r-ps,64+r+ps,32+r+ps);
	GUI_FillCircle(64,32,r);

	GUI_SetPenSize(penSize);
}

#endif

//================================================ End of Demo Function ================================================//
//================================================ End of Demo Function ================================================//
//================================================ End of Demo Function ================================================//


#if 0

#endif




