
#include "RH_GUI.h"

#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>



#pragma anon_unions

//==================================================== API Handle =====================================================//
//==================================================== API Handle =====================================================//
//==================================================== API Handle =====================================================//

void __attribute__((weak)) GUI_DrawArea(uint x1,uint y1,uint x2,uint y2,const Pixel_t* pixData){
// THIS MAY COST SOME TIME.
}

void __attribute__((weak)) GUI_DummyDrawPixel(uint x,uint y,const Pixel_t pixData){
// IF U DONT GIVE ME A PEN, HOW CAN I DRAW !?
}

void __attribute__((weak)) GUI_AsserParam(bool expression,const char* WHAT_IS_WRONG){
// DONT KEEP MY MOTH SHUT, I GOT A PROBLEM TO REPORT.
}

void (*GUI_API_DrawArea)      (unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,const Pixel_t* pixData) = GUI_DrawArea; 

void (*GUI_API_DrawPixel)     (unsigned int x,unsigned int y,const Pixel_t pixData) = GUI_DummyDrawPixel;

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

static const unsigned char __FONT_STD6X8__ASCII_32_0 [] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_1 [] = {0x00, 0x00, 0x00, 0x2f, 0x00, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_2 [] = {0x00, 0x00, 0x07, 0x00, 0x07, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_3 [] = {0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14};
static const unsigned char __FONT_STD6X8__ASCII_32_4 [] = {0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12};
static const unsigned char __FONT_STD6X8__ASCII_32_5 [] = {0x23, 0x13, 0x08, 0x64, 0x62, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_6 [] = {0x00, 0x36, 0x49, 0x55, 0x22, 0x50};
static const unsigned char __FONT_STD6X8__ASCII_32_7 [] = {0x00, 0x00, 0x05, 0x03, 0x00, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_8 [] = {0x00, 0x00, 0x1c, 0x22, 0x41, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_9 [] = {0x00, 0x00, 0x41, 0x22, 0x1c, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_10[] = {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14};
static const unsigned char __FONT_STD6X8__ASCII_32_11[] = {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08};
static const unsigned char __FONT_STD6X8__ASCII_32_12[] = {0x00, 0x00, 0x00, 0xA0, 0x60, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_13[] = {0x00, 0x08, 0x08, 0x08, 0x08, 0x08};
static const unsigned char __FONT_STD6X8__ASCII_32_14[] = {0x00, 0x00, 0x60, 0x60, 0x00, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_15[] = {0x00, 0x20, 0x10, 0x08, 0x04, 0x02};
static const unsigned char __FONT_STD6X8__ASCII_32_16[] = {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E};
static const unsigned char __FONT_STD6X8__ASCII_32_17[] = {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_18[] = {0x00, 0x42, 0x61, 0x51, 0x49, 0x46};
static const unsigned char __FONT_STD6X8__ASCII_32_19[] = {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31};
static const unsigned char __FONT_STD6X8__ASCII_32_20[] = {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10};
static const unsigned char __FONT_STD6X8__ASCII_32_21[] = {0x00, 0x27, 0x45, 0x45, 0x45, 0x39};
static const unsigned char __FONT_STD6X8__ASCII_32_22[] = {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30};
static const unsigned char __FONT_STD6X8__ASCII_32_23[] = {0x00, 0x01, 0x71, 0x09, 0x05, 0x03};
static const unsigned char __FONT_STD6X8__ASCII_32_24[] = {0x00, 0x36, 0x49, 0x49, 0x49, 0x36};
static const unsigned char __FONT_STD6X8__ASCII_32_25[] = {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E};
static const unsigned char __FONT_STD6X8__ASCII_32_26[] = {0x00, 0x00, 0x36, 0x36, 0x00, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_27[] = {0x00, 0x00, 0x56, 0x36, 0x00, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_28[] = {0x00, 0x08, 0x14, 0x22, 0x41, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_29[] = {0x00, 0x14, 0x14, 0x14, 0x14, 0x14};
static const unsigned char __FONT_STD6X8__ASCII_32_30[] = {0x00, 0x00, 0x41, 0x22, 0x14, 0x08};
static const unsigned char __FONT_STD6X8__ASCII_32_31[] = {0x00, 0x02, 0x01, 0x51, 0x09, 0x06};
static const unsigned char __FONT_STD6X8__ASCII_32_32[] = {0x00, 0x32, 0x49, 0x59, 0x51, 0x3E};
static const unsigned char __FONT_STD6X8__ASCII_32_33[] = {0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C};
static const unsigned char __FONT_STD6X8__ASCII_32_34[] = {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36};
static const unsigned char __FONT_STD6X8__ASCII_32_35[] = {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22};
static const unsigned char __FONT_STD6X8__ASCII_32_36[] = {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C};
static const unsigned char __FONT_STD6X8__ASCII_32_37[] = {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41};
static const unsigned char __FONT_STD6X8__ASCII_32_38[] = {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01};
static const unsigned char __FONT_STD6X8__ASCII_32_39[] = {0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A};
static const unsigned char __FONT_STD6X8__ASCII_32_40[] = {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F};
static const unsigned char __FONT_STD6X8__ASCII_32_41[] = {0x00, 0x00, 0x41, 0x7F, 0x41, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_42[] = {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01};
static const unsigned char __FONT_STD6X8__ASCII_32_43[] = {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41};
static const unsigned char __FONT_STD6X8__ASCII_32_44[] = {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40};
static const unsigned char __FONT_STD6X8__ASCII_32_45[] = {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F};
static const unsigned char __FONT_STD6X8__ASCII_32_46[] = {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F};
static const unsigned char __FONT_STD6X8__ASCII_32_47[] = {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E};
static const unsigned char __FONT_STD6X8__ASCII_32_48[] = {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06};
static const unsigned char __FONT_STD6X8__ASCII_32_49[] = {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E};
static const unsigned char __FONT_STD6X8__ASCII_32_50[] = {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46};
static const unsigned char __FONT_STD6X8__ASCII_32_51[] = {0x00, 0x46, 0x49, 0x49, 0x49, 0x31};
static const unsigned char __FONT_STD6X8__ASCII_32_52[] = {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01};
static const unsigned char __FONT_STD6X8__ASCII_32_53[] = {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F};
static const unsigned char __FONT_STD6X8__ASCII_32_54[] = {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F};
static const unsigned char __FONT_STD6X8__ASCII_32_55[] = {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F};
static const unsigned char __FONT_STD6X8__ASCII_32_56[] = {0x00, 0x63, 0x14, 0x08, 0x14, 0x63};
static const unsigned char __FONT_STD6X8__ASCII_32_57[] = {0x00, 0x07, 0x08, 0x70, 0x08, 0x07};
static const unsigned char __FONT_STD6X8__ASCII_32_58[] = {0x00, 0x61, 0x51, 0x49, 0x45, 0x43};
static const unsigned char __FONT_STD6X8__ASCII_32_59[] = {0x00, 0x00, 0x7F, 0x41, 0x41, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_60[] = {0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55};
static const unsigned char __FONT_STD6X8__ASCII_32_61[] = {0x00, 0x00, 0x41, 0x41, 0x7F, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_62[] = {0x00, 0x04, 0x02, 0x01, 0x02, 0x04};
static const unsigned char __FONT_STD6X8__ASCII_32_63[] = {0x00, 0x40, 0x40, 0x40, 0x40, 0x40};
static const unsigned char __FONT_STD6X8__ASCII_32_64[] = {0x00, 0x00, 0x01, 0x02, 0x04, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_65[] = {0x00, 0x20, 0x54, 0x54, 0x54, 0x78};
static const unsigned char __FONT_STD6X8__ASCII_32_66[] = {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38};
static const unsigned char __FONT_STD6X8__ASCII_32_67[] = {0x00, 0x38, 0x44, 0x44, 0x44, 0x20};
static const unsigned char __FONT_STD6X8__ASCII_32_68[] = {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F};
static const unsigned char __FONT_STD6X8__ASCII_32_69[] = {0x00, 0x38, 0x54, 0x54, 0x54, 0x18};
static const unsigned char __FONT_STD6X8__ASCII_32_70[] = {0x00, 0x08, 0x7E, 0x09, 0x01, 0x02};
static const unsigned char __FONT_STD6X8__ASCII_32_71[] = {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C};
static const unsigned char __FONT_STD6X8__ASCII_32_72[] = {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78};
static const unsigned char __FONT_STD6X8__ASCII_32_73[] = {0x00, 0x00, 0x44, 0x7D, 0x40, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_74[] = {0x00, 0x40, 0x80, 0x84, 0x7D, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_75[] = {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_76[] = {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00};
static const unsigned char __FONT_STD6X8__ASCII_32_77[] = {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78};
static const unsigned char __FONT_STD6X8__ASCII_32_78[] = {0x00, 0x7C, 0x08, 0x04, 0x04, 0x78};
static const unsigned char __FONT_STD6X8__ASCII_32_79[] = {0x00, 0x38, 0x44, 0x44, 0x44, 0x38};
static const unsigned char __FONT_STD6X8__ASCII_32_80[] = {0x00, 0xFC, 0x24, 0x24, 0x24, 0x18};
static const unsigned char __FONT_STD6X8__ASCII_32_81[] = {0x00, 0x18, 0x24, 0x24, 0x18, 0xFC};
static const unsigned char __FONT_STD6X8__ASCII_32_82[] = {0x00, 0x7C, 0x08, 0x04, 0x04, 0x08};
static const unsigned char __FONT_STD6X8__ASCII_32_83[] = {0x00, 0x48, 0x54, 0x54, 0x54, 0x20};
static const unsigned char __FONT_STD6X8__ASCII_32_84[] = {0x00, 0x04, 0x3F, 0x44, 0x40, 0x20};
static const unsigned char __FONT_STD6X8__ASCII_32_85[] = {0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C};
static const unsigned char __FONT_STD6X8__ASCII_32_86[] = {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C};
static const unsigned char __FONT_STD6X8__ASCII_32_87[] = {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C};
static const unsigned char __FONT_STD6X8__ASCII_32_88[] = {0x00, 0x44, 0x28, 0x10, 0x28, 0x44};
static const unsigned char __FONT_STD6X8__ASCII_32_89[] = {0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C};
static const unsigned char __FONT_STD6X8__ASCII_32_90[] = {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44};
static const unsigned char __FONT_STD6X8__ASCII_32_91[] = {0x14, 0x14, 0x14, 0x14, 0x14, 0x14};
static const unsigned char __FONT_STD6X8__ASCII_32_92[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};
static const unsigned char __FONT_STD6X8__ASCII_32_93[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};
static const unsigned char __FONT_STD6X8__ASCII_32_94[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};
static const unsigned char __FONT_STD6X8__ASCII_32_95[] = {0xff, 0x81, 0x81, 0x81, 0x81, 0xff};

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


static const unsigned char __FONT_STD8X16__ASCII_32_0 [] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_1 [] = {0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_2 [] = {0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_3 [] = {0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_4 [] = {0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_5 [] = {0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_6 [] = {0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10};
static const unsigned char __FONT_STD8X16__ASCII_32_7 [] = {0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_8 [] = {0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_9 [] = {0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_10[] = {0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_11[] = {0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_12[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_13[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
static const unsigned char __FONT_STD8X16__ASCII_32_14[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_15[] = {0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_16[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_17[] = {0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_18[] = {0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_19[] = {0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_20[] = {0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_21[] = {0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_22[] = {0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_23[] = {0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_24[] = {0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_25[] = {0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_26[] = {0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_27[] = {0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_28[] = {0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_29[] = {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_30[] = {0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_31[] = {0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_32[] = {0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_33[] = {0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_34[] = {0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_35[] = {0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_36[] = {0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_37[] = {0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_38[] = {0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_39[] = {0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_40[] = {0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_41[] = {0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_42[] = {0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_43[] = {0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_44[] = {0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_45[] = {0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_46[] = {0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_47[] = {0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_48[] = {0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_49[] = {0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_50[] = {0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_51[] = {0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_52[] = {0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_53[] = {0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_54[] = {0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_55[] = {0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_56[] = {0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_57[] = {0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_58[] = {0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_59[] = {0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_60[] = {0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_61[] = {0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_62[] = {0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_63[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80};
static const unsigned char __FONT_STD8X16__ASCII_32_64[] = {0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_65[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_66[] = {0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_67[] = {0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_68[] = {0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_69[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_70[] = {0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_71[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_72[] = {0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_73[] = {0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_74[] = {0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_75[] = {0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_76[] = {0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_77[] = {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F};
static const unsigned char __FONT_STD8X16__ASCII_32_78[] = {0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_79[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_80[] = {0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_81[] = {0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80};
static const unsigned char __FONT_STD8X16__ASCII_32_82[] = {0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_83[] = {0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_84[] = {0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_85[] = {0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20};
static const unsigned char __FONT_STD8X16__ASCII_32_86[] = {0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_87[] = {0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_88[] = {0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_89[] = {0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_90[] = {0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_91[] = {0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40};
static const unsigned char __FONT_STD8X16__ASCII_32_92[] = {0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_93[] = {0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_94[] = {0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char __FONT_STD8X16__ASCII_32_95[] = {0xff,0x01,0x01,0x01,0x01,0x01,0x01,0xff,0xff,0x80,0x80,0x80,0x80,0x80,0x80,0xff};

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

#if GUI_FONT_EXTENTION

const unsigned char __FONT_BRADLEY__ASCII_32_0 [] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_1 [] = { 0x00,0x00,0xFC,0xFC,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x13,0x13,0x10,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_2 [] = { 0x00,0x78,0x78,0x78,0x78,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_3 [] = { 0x00,0x40,0x40,0x40,0xE0,0xF8,0x5C,0xC4, 0xF0,0x7C,0x4C,0x40,0x40,0x00,0x00,0x00, 0x04,0xC4,0xFC,0x3F,0x07,0xE4,0xFC,0x1F, 0x07,0x04,0x04,0x04,0x04,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_4 [] = { 0x00,0x00,0x40,0xE0,0xA0,0xB0,0xFF,0xFF, 0xFF,0x10,0x10,0x10,0x00,0x00,0x00,0x00, 0x08,0x08,0x08,0x08,0x08,0x49,0xFF,0xFF, 0xFF,0x05,0x05,0x07,0x02,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_5 [] = { 0x00,0x3C,0x7E,0x42,0x66,0x3E,0xDA,0xF2, 0x3E,0x0E,0x03,0x01,0x00,0x00,0x00,0x00, 0x00,0x00,0x80,0xF0,0x7E,0x0F,0x01,0x1C, 0x3F,0x23,0x31,0x1F,0x0E,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_6 [] = { 0x00,0x00,0x00,0xB0,0xF8,0xCC,0xC4,0x44, 0x44,0x44,0x0C,0x08,0x00,0x00,0x00,0x00, 0xC0,0xC6,0x8F,0x09,0x08,0x08,0x08,0x08, 0x0C,0x84,0xFE,0x7A,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_7 [] = { 0x00,0x78,0x78,0x08,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_8 [] = { 0x00,0x00,0x00,0x00,0xF8,0xFE,0x07,0x01, 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x1F,0x7F,0xE0,0xC0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_9 [] = { 0x00,0x00,0x01,0x0F,0xFE,0xF0,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x80,0xE0,0x78,0x1F,0x07,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_10[] = { 0x00,0x48,0x6A,0x3E,0xFF,0xFF,0x14,0x3E, 0x2A,0x68,0x40,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_11[] = { 0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80, 0xFE,0xFE,0x80,0x80,0x80,0x80,0x80,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_12[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x40,0x60,0x38,0x18,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_13[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_14[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_15[] = { 0x00,0x00,0x00,0x80,0xC0,0x70,0x38,0x0E, 0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x30,0x3C,0x0E,0x03,0x01,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_16[] = { 0x00,0x80,0xE0,0x70,0x10,0x18,0x08,0x18, 0x30,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00, 0x00,0x1F,0x1F,0x10,0x10,0x10,0x18,0x0C, 0x06,0x03,0x01,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_17[] = { 0x40,0x40,0x60,0x20,0xF0,0xF8,0x18,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x10,0x10,0x10,0x10,0x1F,0x1F,0x10,0x10, 0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_18[] = { 0x00,0x30,0x30,0x18,0x08,0x08,0x08,0x08, 0x18,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00, 0x10,0x18,0x18,0x18,0x08,0x08,0x1C,0x16, 0x33,0x21,0x20,0x20,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_19[] = { 0x00,0x20,0x30,0x10,0x90,0x90,0x90,0xD0, 0x50,0x70,0x20,0x00,0x00,0x00,0x00,0x00, 0x10,0x18,0x18,0x11,0x11,0x11,0x11,0x13, 0x1A,0x0E,0x0E,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_20[] = { 0x00,0x00,0x00,0x80,0xC0,0x60,0x38,0xF8, 0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x00, 0x02,0x03,0x01,0x01,0x01,0x01,0x3F,0x3F, 0x03,0x02,0x03,0x01,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_21[] = { 0x00,0x00,0xC0,0xF8,0xB8,0x88,0x88,0x88, 0x88,0x88,0x08,0x08,0x08,0x08,0x00,0x00, 0x0C,0x1C,0x10,0x10,0x10,0x10,0x10,0x10, 0x18,0x0F,0x07,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_22[] = { 0x00,0x00,0xC0,0xE0,0x30,0x18,0x08,0x08, 0x88,0x80,0x80,0x00,0x00,0x00,0x00,0x00, 0x00,0x0F,0x1F,0x1C,0x16,0x13,0x11,0x19, 0x09,0x0C,0x07,0x07,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_23[] = { 0x08,0x08,0x18,0x90,0x90,0x90,0x90,0x90, 0xD8,0xF8,0xBC,0x8C,0x80,0x80,0x00,0x00, 0x00,0x80,0xC0,0x60,0x70,0x18,0x0E,0x07, 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_24[] = { 0x00,0x20,0xF0,0xD8,0x08,0x0C,0x8C,0xCC, 0x44,0x7C,0x38,0x00,0x00,0x00,0x00,0x00, 0x00,0x18,0x1C,0x37,0x23,0x23,0x27,0x3C, 0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_25[] = { 0x00,0xE0,0xF0,0x18,0x0C,0x84,0xCC,0x7C, 0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x01,0x01,0x81,0xC1,0x60,0x3C, 0x1F,0x03,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_26[] = { 0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_27[] = { 0x00,0x00,0x40,0x40,0x40,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x40,0x60,0x38,0x18,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_28[] = { 0x00,0x00,0x00,0xC0,0xC0,0xE0,0x20,0x20, 0x30,0x10,0x18,0x08,0x08,0x0C,0x04,0x00, 0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01, 0x03,0x02,0x06,0x04,0x04,0x0C,0x08,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_29[] = { 0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20, 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00, 0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01, 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_30[] = { 0x00,0x00,0x00,0x04,0x0C,0x08,0x18,0x10, 0x10,0x30,0x20,0xE0,0xC0,0xC0,0xC0,0x00, 0x00,0x00,0x00,0x08,0x0C,0x04,0x04,0x06, 0x02,0x03,0x01,0x01,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_31[] = { 0x00,0x08,0x0C,0x84,0xC4,0x7C,0x38,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x13,0x17,0x14,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_32[] = { 0x00,0xC0,0xE0,0x30,0x18,0xCC,0xE4,0x34, 0xB4,0xE4,0x64,0x0C,0xF8,0xF0,0x00,0x00, 0x00,0x1F,0x3F,0x20,0x66,0x47,0x47,0x43, 0x47,0x47,0x64,0x26,0x23,0x01,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_33[] = { 0x00,0x00,0x00,0x00,0x80,0xE0,0x70,0x1C, 0x1C,0xFC,0xE0,0x00,0x00,0x00,0x00,      0x10,0x18,0x0C,0x07,0x03,0x01,0x01,0x01, 0x01,0x01,0x07,0x1F,0x39,0x21,0x00      };
const unsigned char __FONT_BRADLEY__ASCII_32_34[] = { 0x04,0x04,0x1C,0xFC,0xE8,0xC8,0x48,0x48, 0x68,0x38,0x10,0x00,0x00,0x00,           0x00,0x00,0x01,0x1F,0x1F,0x11,0x11,0x11, 0x11,0x19,0x0B,0x0E,0x06,0x04           };
const unsigned char __FONT_BRADLEY__ASCII_32_35[] = { 0x00,0x80,0xE0,0x78,0x18,0x0C,0x04,0x0C, 0x78,0x78,0x00,0x00,0x00,                0x00,0x07,0x0F,0x18,0x10,0x10,0x10,0x10, 0x10,0x18,0x0C,0x06,0x02                };
const unsigned char __FONT_BRADLEY__ASCII_32_36[] = { 0x00,0x08,0x0C,0x5C,0xFC,0xA8,0X08,0x18, 0x10,0x30,0x20,0x60,0xC0,0x80,0x00,      0x00,0x00,0x10,0x3F,0x3F,0x18,0x08,0x08, 0x08,0x08,0x0C,0x04,0x07,0x03,0x00      };
const unsigned char __FONT_BRADLEY__ASCII_32_37[] = { 0x00,0x00,0xF8,0xF8,0x88,0x8C,0x84,0x84, 0x84,0x84,0xC4,0x44,0x00,                0x00,0x00,0x07,0x1F,0x18,0x10,0x10,0x10, 0x18,0x0C,0x06,0x02,0x00                };
const unsigned char __FONT_BRADLEY__ASCII_32_38[] = { 0x00,0x88,0x88,0xF8,0xF8,0x88,0x8C,0x84, 0x84,0x84,0x84,0x84,0x00,                0x00,0x00,0x38,0x3F,0x07,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00                };
const unsigned char __FONT_BRADLEY__ASCII_32_39[] = { 0x00,0x00,0x80,0xC0,0x60,0x20,0x30,0x10, 0x18,0x08,0x08,0x08,0x08,0x00,0x00,      0x00,0x07,0x0F,0x08,0x18,0x10,0x18,0x08, 0x08,0x08,0x0C,0x04,0xFE,0xFE,0x00      };
const unsigned char __FONT_BRADLEY__ASCII_32_40[] = { 0x00,0x00,0xFC,0xFC,0x80,0x80,0x80,0x80, 0x80,0xC0,0x40,0xFC,0xFC,0x40,0x40,0x40, 0x00,0x00,0x1F,0x1F,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x3F,0x3F,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_41[] = { 0x00,0x00,0xF8,0xF8,0x00,                                                         0x00,0x00,0x1F,0x1F,0x00                                                         };
const unsigned char __FONT_BRADLEY__ASCII_32_42[] = { 0x00,0x00,0xFC,0xFC,0x00,                                                         0x00,0xC0,0xFF,0x3F,0x00                                                         };
const unsigned char __FONT_BRADLEY__ASCII_32_43[] = { 0x00,0x00,0xF8,0xF8,0x00,0x80,0x80,0x80, 0xC0,0x60,0x30,0x1C,0x0C,0x00,0x00,0x00, 0x00,0x00,0x3F,0x3F,0x01,0x03,0x06,0x04, 0x0C,0x18,0x10,0x10,0x10,0x18,0x0C,0x04 };
const unsigned char __FONT_BRADLEY__ASCII_32_44[] = { 0x00,0x00,0xF8,0xFC,0x0C,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,      0x00,0x00,0x0F,0x1F,0x10,0x10,0x10,0x10, 0x10,0x10,0x18,0x08,0x08,0x08,0x00      };
const unsigned char __FONT_BRADLEY__ASCII_32_45[] = { 0x00,0x00,0xC0,0xF8,0x38,0x60,0xC0,0x80, 0x00,0x00,0x80,0xC0,0x60,0x38,0xF8,0xF8, 0x00,0x1C,0x1F,0x03,0x00,0x00,0x01,0x07, 0x06,0x07,0x03,0x00,0x00,0x00,0x0F,0x1F };
const unsigned char __FONT_BRADLEY__ASCII_32_46[] = { 0x00,0x00,0xF8,0xF8,0x78,0x60,0xC0,0x80, 0x00,0x00,0x00,0x00,0xE8,0xF8,0x10,0x00, 0x00,0x00,0x1F,0x1F,0x00,0x00,0x00,0x01, 0x03,0x02,0x06,0x04,0x3F,0x3F,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_47[] = { 0x00,0x00,0xC0,0xF0,0x38,0x18,0x08,0x08, 0x08,0x08,0x08,0x38,0xF0,0xC0,0x00,      0x00,0x0F,0x1F,0x10,0x10,0x10,0x10,0x10, 0x18,0x08,0x0C,0x06,0x03,0x03,0x00,     };
const unsigned char __FONT_BRADLEY__ASCII_32_48[] = { 0x08,0x0C,0x84,0xF4,0x7C,0x08,0x08,0x08, 0x98,0x90,0xF0,0x60,0x00,                0x00,0x02,0x1F,0x1F,0x12,0x03,0x01,0x01, 0x01,0x00,0x00,0x00,0x00                };
const unsigned char __FONT_BRADLEY__ASCII_32_49[] = { 0x00,0x00,0xC0,0xE0,0x30,0x18,0x08,0x08, 0x08,0x08,0x08,0x08,0xF8,0xF0,0x00,0x00, 0x00,0x0F,0x1F,0x10,0x10,0x10,0x11,0x1F, 0x1E,0x3C,0x26,0x23,0x21,0x20,0x30,0x10 };
const unsigned char __FONT_BRADLEY__ASCII_32_50[] = { 0x10,0x18,0xF8,0xF8,0x88,0x88,0x08,0x88, 0x88,0x98,0x90,0xF0,0x70,0x20,0x00,0x00, 0x00,0x00,0x1F,0x1F,0x00,0x01,0x03,0x07, 0x0C,0x18,0x10,0x10,0x10,0x10,0x10,0x10 };
const unsigned char __FONT_BRADLEY__ASCII_32_51[] = { 0x00,0x00,0x00,0x70,0xF0,0x98,0x88,0x88, 0x88,0x08,0x08,0x08,0x08,0x00,0x00,      0x0C,0x1C,0x10,0x10,0x10,0x10,0x10,0x10, 0x11,0x11,0x11,0x1B,0x0E,0x0E,0x00      };
const unsigned char __FONT_BRADLEY__ASCII_32_52[] = { 0x08,0x08,0x08,0x08,0x08,0xF8,0xF8,0x08, 0x08,0x08,0x08,0x08,0x08,0x08,0x00,      0x00,0x00,0x00,0x00,0x00,0x3F,0x3F,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00      };
const unsigned char __FONT_BRADLEY__ASCII_32_53[] = { 0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00, 0x00,0x80,0xE8,0xF8,0x10,0x00,0x00,0x00, 0x00,0x00,0x1F,0x1F,0x18,0x08,0x0C,0x06, 0x03,0x01,0x07,0x1F,0x38,0x20,0x20,0x20 };
const unsigned char __FONT_BRADLEY__ASCII_32_54[] = { 0x00,0x18,0x38,0xE0,0xC0,0x00,0x00,0x00, 0x00,0x80,0xE0,0x78,0x18,0x00,           0x00,0x00,0x00,0x00,0x07,0x1F,0x18,0x1C, 0x07,0x03,0x00,0x00,0x00,0x00           };
const unsigned char __FONT_BRADLEY__ASCII_32_55[] = { 0x00,0x38,0xF8,0xC0,0x00,0x00,0x00,0x80, 0xC0,0x60,0x70,0xF0,0x80,0x00,0x00,0x00, 0x00,0x00,0x03,0x0F,0x1C,0x1C,0x07,0x03, 0x00,0x00,0x00,0x03,0x0F,0x3C,0x3C,0x0E };
const unsigned char __FONT_BRADLEY__ASCII_32_56[] = { 0x00,0x00,0x08,0x18,0x30,0xE0,0xC0,0xC0, 0x70,0x38,0x1C,0x04,0x00,0x00,           0x20,0x30,0x18,0x0C,0x06,0x03,0x01,0x07, 0x0E,0x08,0x18,0x10,0x10,0x00           };
const unsigned char __FONT_BRADLEY__ASCII_32_57[] = { 0x00,0x0C,0x1C,0x38,0x60,0xC0,0x80,0x80, 0xC0,0x60,0x30,0x18,0x0C,0x04,0x00,      0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF, 0x00,0x00,0x00,0x00,0x00,0x00,0x00      };
const unsigned char __FONT_BRADLEY__ASCII_32_58[] = { 0x00,0x00,0x04,0x04,0x04,0x04,0x84,0xC4, 0x64,0x34,0x1C,0x0C,0x04,0x00,0x00,0x00, 0x10,0x18,0x08,0x0C,0x0E,0x1B,0x11,0x10, 0x10,0x10,0x10,0x30,0x30,0x20,0x20,0x3C };
const unsigned char __FONT_BRADLEY__ASCII_32_59[] = { 0x00,0x00,0x01,0xC7,0xFF,0x39,0x01,0x01, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x40,0x7F,0x7F,0x40,0x40,0x40, 0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_60[] = { 0x06,0x0E,0x38,0x70,0xC0,0x80,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x01,0x03,0x0E,0x3C, 0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_61[] = { 0x02,0x02,0x03,0x01,0xFF,0xFF,0x01,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x40,0x40,0x4E,0x7F,0x71,0x40,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_62[] = { 0x00,0x00,0x00,0x00,0x08,0x08,0x0C,0x06, 0x03,0x01,0x00,0x01,0x03,0x06,0x0C,0x08, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_63[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80, 0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_64[] = { 0x00,0x00,0x01,0x03,0x07,0x04,0x04,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_65[] = { 0x00,0x00,0xE0,0xF0,0x10,0x10,0x90,0xF0, 0xF0,0x00,0x00,                          0x00,0x1F,0x1F,0x18,0x0C,0x06,0x03,0x1F, 0x1F,0x00,0x00                          };
const unsigned char __FONT_BRADLEY__ASCII_32_66[] = { 0x00,0xC3,0xFF,0xFC,0xE0,0x30,0x18,0xF8, 0xE0,0x00,0x00,                          0x00,0x07,0x0F,0x1F,0x11,0x10,0x10,0x1F, 0x0F,0x00,0x00                          };
const unsigned char __FONT_BRADLEY__ASCII_32_67[] = { 0x00,0x80,0xC0,0x70,0x30,0xE0,0xE0,0x00, 0x00,0x00,                               0x00,0x0F,0x1F,0x10,0x10,0x10,0x18,0x0E, 0x06,0x00                               };
const unsigned char __FONT_BRADLEY__ASCII_32_68[] = { 0x00,0x00,0xE0,0xF0,0x10,0x10,0x30,0xE0, 0xFF,0x7F,0x00,                          0x00,0x1F,0x1F,0x10,0x18,0x0C,0x07,0x03, 0x1F,0x1F,0x10                          };
const unsigned char __FONT_BRADLEY__ASCII_32_69[] = { 0x00,0x80,0xE0,0x70,0x90,0xF0,0x70,0x00,                                          0x00,0x1F,0x3F,0x21,0x21,0x30,0x18,0x08,                                         };
const unsigned char __FONT_BRADLEY__ASCII_32_70[] = { 0x80,0x80,0x80,0xC0,0xFC,0x7F,0x43,0x40, 0x41,0x01,0x00,                          0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00, 0x00,0x00,0x00                          };
const unsigned char __FONT_BRADLEY__ASCII_32_71[] = { 0x00,0x00,0xC0,0xE0,0x30,0x10,0x10,0x30, 0xF0,0xF0,0x00,                          0x00,0x1F,0x1F,0x10,0x18,0x0C,0x04,0x07, 0x03,0xFF,0xFF                          };
const unsigned char __FONT_BRADLEY__ASCII_32_72[] = { 0x00,0x02,0xFE,0xFC,0x80,0xC0,0x60,0xE0, 0xE0,0x00,0x00,                          0x00,0x07,0x1F,0x1E,0x07,0x01,0x00,0x0F, 0x3F,0x30,0x00                          };
const unsigned char __FONT_BRADLEY__ASCII_32_73[] = { 0x00,0xC4,0xE6,0x23,0x01,0x00,0x00,0x00,                                          0x00,0x1F,0x1F,0x10,0x18,0x0C,0x04,0x00                                          };
const unsigned char __FONT_BRADLEY__ASCII_32_74[] = { 0x00,0x01,0xF1,0xF0,0x00,                                                         0x00,0x00,0xFF,0xFF,0x00                                                         };
const unsigned char __FONT_BRADLEY__ASCII_32_75[] = { 0x00,0xFE,0xFE,0xC0,0xE0,0x20,0x30,0x10, 0x10,0xB0,0xE0,0x40,0x00,                0x00,0x19,0x1F,0x07,0x03,0x07,0x0E,0x1A, 0x33,0x21,0x20,0x30,0x10                };
const unsigned char __FONT_BRADLEY__ASCII_32_76[] = { 0x00,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,                                          0x00,0x0F,0x1F,0x10,0x18,0x0C,0x04,0x00,                                         };
const unsigned char __FONT_BRADLEY__ASCII_32_77[] = { 0x00,0x70,0xF0,0x80,0x80,0xC0,0x60,0xE0, 0xE0,0x00,0x00,0x80,0xC0,0xE0,0x20,0x00, 0x00,0x17,0x1F,0x1E,0x07,0x01,0x00,0x0F, 0x1F,0x18,0x0E,0x07,0x01,0x0F,0x1E,0x10 };
const unsigned char __FONT_BRADLEY__ASCII_32_78[] = { 0x00,0x20,0xE0,0xC0,0x00,0x80,0xC0,0xE0, 0xE0,0x00,0x00,0x00,0x00,0x00,           0x00,0x0E,0x1F,0x1D,0x0E,0x03,0x01,0x00, 0x0F,0x1F,0x18,0x0C,0x0E,0x02           };
const unsigned char __FONT_BRADLEY__ASCII_32_79[] = {      0x00,0xC0,0xE0,0x20,0x20,0xE0,0xC0,                                          0x00,0x1F,0x3F,0x20,0x30,0x18,0x0F,0x07,                                         };
const unsigned char __FONT_BRADLEY__ASCII_32_80[] = { 0x60,0x20,0xF0,0xF0,0x20,0x60,0xC0,0x80, 0x00,                                    0x00,0x00,0xFF,0xFF,0x08,0x08,0x08,0x0F, 0x0F                                    };
const unsigned char __FONT_BRADLEY__ASCII_32_81[] = { 0x00,0x00,0x80,0xC0,0x60,0x20,0x20,0x20, 0xE0,0xE0,0x20,                          0x00,0x0F,0x1F,0x10,0x18,0x08,0x0C,0x06, 0xFF,0xFF,0x00                          };
const unsigned char __FONT_BRADLEY__ASCII_32_82[] = { 0x00,0xE0,0xE0,0x00,0x80,0xC0,0x60,0x20, 0x20,                                    0x00,0x01,0x3F,0x3F,0x01,0x00,0x00,0x00, 0x00                                    };
const unsigned char __FONT_BRADLEY__ASCII_32_83[] = { 0x00,0xC0,0xE0,0x20,0x30,0x10,0x30,0x20, 0x00,                                    0x10,0x10,0x11,0x13,0x12,0x16,0x14,0x1C, 0x08                                    };
const unsigned char __FONT_BRADLEY__ASCII_32_84[] = { 0x20,0xFC,0xFC,0x60,0x20,0x20,0x20,0x20,                                          0x00,0x07,0x1F,0x18,0x10,0x10,0x10,0x00                                          };
const unsigned char __FONT_BRADLEY__ASCII_32_85[] = { 0x00,0xE0,0xE0,0x00,0x00,0x00,0x00,0x80, 0xE0,0x60,0x00,0x00,                     0x00,0x0F,0x1F,0x10,0x18,0x0C,0x06,0x0F, 0x1F,0x10,0x10,0x10                     };
const unsigned char __FONT_BRADLEY__ASCII_32_86[] = { 0x20,0xE0,0xC0,0x00,0x00,0x00,0x00,0xC0, 0xF0,0x38,0x08,                          0x00,0x00,0x07,0x1F,0x18,0x1C,0x0E,0x03, 0x01,0x00,0x00                          };
const unsigned char __FONT_BRADLEY__ASCII_32_87[] = { 0x30,0xF0,0xC0,0x00,0x00,0x80,0xC0,0xC0, 0x00,0x00,0x00,0xC0,0xF0,0x30,           0x00,0x03,0x1F,0x1C,0x0E,0x03,0x01,0x03, 0x1F,0x1C,0x0E,0x03,0x01,0x00           };
const unsigned char __FONT_BRADLEY__ASCII_32_88[] = { 0x00,0x00,0x20,0xE0,0xC0,0xC0,0x60,0x30, 0x10,0x00,                               0x70,0x38,0x0E,0x07,0x03,0x06,0x1C,0x18, 0x10,0x10                               };
const unsigned char __FONT_BRADLEY__ASCII_32_89[] = { 0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,0x00, 0x00,0xD0,0xF0,0x60,0x00,                0x00,0x00,0x9F,0xBF,0xB0,0x18,0x0C,0x06, 0x03,0x01,0xFF,0xFF,0x00                };
const unsigned char __FONT_BRADLEY__ASCII_32_90[] = { 0x10,0x30,0x20,0x20,0x20,0x20,0xE0,0xE0, 0x30,0x10,0x00,                          0x20,0x30,0x18,0x1C,0x16,0x13,0x11,0x10, 0x10,0x18,0x08                          };
const unsigned char __FONT_BRADLEY__ASCII_32_91[] = { 0x00,0x00,0x80,0x80,0xFE,0x7F,0x01,0x01, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x1F,0x3F,0x60,0x40,0x40, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_92[] = { 0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_93[] = { 0x00,0x01,0x01,0x07,0xFE,0xF8,0x80,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x40,0x40,0x7F,0x3F,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_94[] = { 0x00,0x00,0x80,0xC0,0x40,0x40,0x40,0x40, 0xC0,0x80,0x80,0x80,0x80,0x80,0xC0,0x40, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
const unsigned char __FONT_BRADLEY__ASCII_32_95[] = { 0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x0F,0x0F,0x08,0x08,0x0F,0x0F,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	
static __FontChar_t __FONT_BRADLEY_LARGE[] = {
	{ .c = ' ' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_0 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_0  },
	{ .c = '!' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_1 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_1  },
	{ .c = '"' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_2 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_2  },
	{ .c = '#' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_3 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_3  },
	{ .c = '$' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_4 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_4  },
	{ .c = '%' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_5 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_5  },
	{ .c = '&' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_6 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_6  },
	{ .c = '\'', .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_7 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_7  },
	{ .c = '(' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_8 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_8  },
	{ .c = ')' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_9 )/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_9  },
	{ .c = '*' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_10)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_10 },
	{ .c = '+' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_11)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_11 },
	{ .c = ',' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_12)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_12 },
	{ .c = '-' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_13)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_13 },
	{ .c = '.' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_14)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_14 },
	{ .c = '/' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_15)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_15 },
	{ .c = '0' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_16)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_16 },
	{ .c = '1' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_17)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_17 },
	{ .c = '2' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_18)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_18 },
	{ .c = '3' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_19)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_19 },
	{ .c = '4' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_20)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_20 },
	{ .c = '5' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_21)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_21 },
	{ .c = '6' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_22)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_22 },
	{ .c = '7' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_23)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_23 },
	{ .c = '8' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_24)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_24 },
	{ .c = '9' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_25)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_25 },
	{ .c = ':' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_26)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_26 },
	{ .c = ';' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_27)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_27 },
	{ .c = '<' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_28)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_28 },
	{ .c = '=' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_29)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_29 },
	{ .c = '>' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_30)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_30 },
	{ .c = '?' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_31)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_31 },
	{ .c = '@' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_32)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_32 },
	{ .c = 'A' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_33)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_33 },
	{ .c = 'B' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_34)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_34 },
	{ .c = 'C' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_35)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_35 },
	{ .c = 'D' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_36)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_36 },
	{ .c = 'E' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_37)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_37 },
	{ .c = 'F' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_38)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_38 },
	{ .c = 'G' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_39)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_39 },
	{ .c = 'H' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_40)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_40 },
	{ .c = 'I' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_41)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_41 },
	{ .c = 'J' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_42)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_42 },
	{ .c = 'K' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_43)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_43 },
	{ .c = 'L' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_44)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_44 },
	{ .c = 'M' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_45)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_45 },
	{ .c = 'N' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_46)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_46 },
	{ .c = 'O' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_47)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_47 },
	{ .c = 'P' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_48)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_48 },
	{ .c = 'Q' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_49)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_49 },
	{ .c = 'R' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_50)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_50 },
	{ .c = 'S' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_51)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_51 },
	{ .c = 'T' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_52)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_52 },
	{ .c = 'U' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_53)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_53 },
	{ .c = 'V' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_54)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_54 },
	{ .c = 'W' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_55)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_55 },
	{ .c = 'X' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_56)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_56 },
	{ .c = 'Y' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_57)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_57 },
	{ .c = 'Z' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_58)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_58 },
	{ .c = '[' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_59)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_59 },
	{ .c = '\\', .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_60)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_60 },
	{ .c = ']' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_61)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_61 },
	{ .c = '^' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_62)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_62 },
	{ .c = '_' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_63)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_63 },
	{ .c = '`' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_64)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_64 },
	{ .c = 'a' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_65)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_65 },
	{ .c = 'b' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_66)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_66 },
	{ .c = 'c' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_67)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_67 },
	{ .c = 'd' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_68)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_68 },
	{ .c = 'e' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_69)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_69 },
	{ .c = 'f' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_70)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_70 },
	{ .c = 'g' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_71)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_71 },
	{ .c = 'h' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_72)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_72 },
	{ .c = 'i' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_73)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_73 },
	{ .c = 'j' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_74)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_74 },
	{ .c = 'k' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_75)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_75 },
	{ .c = 'l' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_76)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_76 },
	{ .c = 'm' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_77)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_77 },
	{ .c = 'n' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_78)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_78 },
	{ .c = 'o' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_79)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_79 },
	{ .c = 'p' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_80)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_80 },
	{ .c = 'q' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_81)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_81 },
	{ .c = 'r' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_82)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_82 },
	{ .c = 's' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_83)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_83 },
	{ .c = 't' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_84)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_84 },
	{ .c = 'u' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_85)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_85 },
	{ .c = 'v' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_86)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_86 },
	{ .c = 'w' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_87)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_87 },
	{ .c = 'x' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_88)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_88 },
	{ .c = 'y' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_89)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_89 },
	{ .c = 'z' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_90)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_90 },
	{ .c = '{' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_91)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_91 },
	{ .c = '|' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_92)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_92 },
	{ .c = '}' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_93)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_93 },
	{ .c = '~' , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_94)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_94 },
	{ .c = 127 , .height = 16 , .width = sizeof(__FONT_BRADLEY__ASCII_32_95)/(16/8) , .byte = __FONT_BRADLEY__ASCII_32_95 },
};

	/* 0x20 [ ] */
#endif


#if GUI_FONT_EXTENTION

static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_0 [] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x21 [!] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_1 [] = { 0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x30,0x33,0x30,0x00,0x00,0x00,0x00,0x00 };
	/* 0x22 ["] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_2 [] = { 0x00,0x00,0x0E,0x7E,0x0E,0x00,0x00,0x0E,0x7E,0x0E,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x23 [#] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_3 [] = { 0x00,0x00,0x20,0x20,0xF8,0x27,0x20,0xF8,0x27,0x20,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x02,0x72,0x0F,0x02,0x72,0x0F,0x02,0x02,0x00,0x00,0x00 };
	/* 0x24 [$] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_4 [] = { 0x00,0x00,0x00,0x38,0x44,0x44,0x87,0x84,0x84,0x0C,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x1C,0x10,0x10,0xF0,0x10,0x18,0x0F,0x00,0x00,0x00 };
	/* 0x25 [%] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_5 [] = { 0x00,0x00,0x1C,0x22,0xA2,0xA2,0x9C,0x80,0x40,0x40,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x01,0x01,0x00,0x1C,0x22,0x22,0x22,0x1C,0x00,0x00,0x00 };
	/* 0x26 [&] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_6 [] = { 0x00,0x00,0x00,0x00,0x70,0x88,0x08,0x08,0x08,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x1E,0x21,0x21,0x23,0x1C,0x18,0x26,0x22,0x00,0x00 };
	/* 0x27 ['] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_7 [] = { 0x00,0x00,0x00,0x00,0x00,0x0E,0x7E,0x0E,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x28 [(] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_8 [] = { 0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x18,0x06,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x60,0x80,0x00,0x00,0x00,0x00 };
	/* 0x29 [)] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_9 [] = { 0x00,0x00,0x00,0x00,0x06,0x18,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x80,0x60,0x1F,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x2A [*] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_10[] = { 0x00,0x00,0x10,0x10,0x90,0x7E,0x50,0x90,0x10,0x10,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00 };
	/* 0x2B [+] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_11[] = { 0x00,0x80,0x80,0x80,0x80,0xFC,0x80,0x80,0x80,0x80,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x2C [,] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_12[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0xC0,0xF8,0x38,0x08,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x2D [-] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_13[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00 };
	/* 0x2E [.] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_14[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x2F [/] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_15[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x30,0x0C,0x03,0x00,0x00,0x00,\
                                                                     0x00,0x00,0xC0,0x30,0x0C,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x30 [0] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_16[] = { 0x00,0x00,0xF0,0x0C,0x04,0x02,0x02,0x02,0x02,0x0C,0xF0,0x00,0x00,\
                                                                     0x00,0x00,0x07,0x18,0x20,0x20,0x20,0x20,0x20,0x18,0x07,0x00,0x00 };
	/* 0x31 [1] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_17[] = { 0x00,0x00,0x04,0x04,0x04,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00 };
	/* 0x32 [2] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_18[] = { 0x00,0x00,0x18,0x04,0x02,0x02,0x02,0x82,0x44,0x38,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x20,0x20,0x30,0x00,0x00,0x00 };
	/* 0x33 [3] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_19[] = { 0x00,0x00,0x04,0x04,0x02,0x42,0x42,0x42,0x42,0xA4,0x18,0x00,0x00,\
                                                                     0x00,0x00,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x0F,0x00,0x00 };
	/* 0x34 [4] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_20[] = { 0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x02,0xFE,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x03,0x02,0x02,0x02,0x22,0x22,0x3F,0x22,0x00,0x00,0x00 };
	/* 0x35 [5] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_21[] = { 0x00,0x00,0x00,0x7E,0x42,0x22,0x22,0x22,0x42,0x80,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x08,0x10,0x20,0x20,0x20,0x20,0x10,0x0F,0x00,0x00,0x00 };
	/* 0x36 [6] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_22[] = { 0x00,0x00,0x00,0xF0,0x08,0x84,0x44,0x42,0x42,0x82,0x02,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x07,0x19,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,0x00 };
	/* 0x37 [7] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_23[] = { 0x00,0x00,0x06,0x02,0x02,0x02,0x02,0x82,0x72,0x0E,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x03,0x00,0x00,0x00,0x00,0x00 };
	/* 0x38 [8] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_24[] = { 0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x20,0x11,0x0F,0x00,0x00,0x00 };
	/* 0x39 [9] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_25[] = { 0x00,0x00,0x00,0x78,0x84,0x02,0x02,0x02,0x04,0x8C,0xF0,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x20,0x20,0x21,0x21,0x21,0x11,0x0C,0x03,0x00,0x00 };
	/* 0x3A [:] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_26[] = { 0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x3B [;] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_27[] = { 0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0xE0,0x78,0x18,0x08,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x3C [<] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_28[] = { 0x00,0x00,0x00,0x80,0x40,0x40,0x20,0x20,0x10,0x08,0x08,0x00,0x00,\
                                                                     0x00,0x01,0x01,0x02,0x04,0x04,0x08,0x08,0x10,0x20,0x20,0x00,0x00 };
	/* 0x3D [=] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_29[] = { 0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,\
                                                                     0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00 };
	/* 0x3E [>] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_30[] = { 0x00,0x08,0x08,0x10,0x20,0x20,0x40,0x40,0x80,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x20,0x20,0x10,0x08,0x08,0x04,0x04,0x02,0x01,0x01,0x00,0x00 };
	/* 0x3F [?] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_31[] = { 0x00,0x00,0x00,0x18,0x04,0x04,0x04,0x04,0x84,0x88,0x70,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x30,0x33,0x31,0x00,0x00,0x00,0x00,0x00 };
	/* 0x40 [@] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_32[] = { 0x00,0x00,0xF8,0x04,0x06,0xC2,0x42,0x22,0x24,0xF8,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x1F,0x20,0x40,0x43,0x44,0x44,0x24,0x07,0x00,0x00,0x00 };
	/* 0x41 [A] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_33[] = { 0x00,0x00,0x04,0x84,0x74,0x0C,0x04,0x0C,0x70,0x80,0x00,0x00,0x00,\
                                                                     0x20,0x30,0x2E,0x23,0x02,0x02,0x02,0x02,0x02,0x23,0x2E,0x30,0x20 };
	/* 0x42 [B] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_34[] = { 0x00,0x04,0x04,0xFC,0x84,0x84,0x84,0x84,0xC8,0x30,0x00,0x00,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x11,0x0E,0x00,0x00 };
	/* 0x43 [C] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_35[] = { 0x00,0xE0,0x10,0x08,0x04,0x04,0x04,0x04,0x08,0x08,0x3C,0x00,0x00,\
                                                                     0x00,0x07,0x08,0x10,0x20,0x20,0x20,0x20,0x20,0x10,0x08,0x00,0x00 };
	/* 0x44 [D] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_36[] = { 0x00,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x04,0x08,0x10,0xE0,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x10,0x08,0x07,0x00 };
	/* 0x45 [E] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_37[] = { 0x00,0x04,0x04,0xFC,0x84,0x84,0x84,0xE4,0x04,0x04,0x1C,0x00,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x23,0x20,0x20,0x3C,0x00,0x00 };
	/* 0x46 [F] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_38[] = { 0x00,0x04,0x04,0xFC,0x84,0x84,0x84,0xE4,0x04,0x04,0x1C,0x00,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x23,0x00,0x00,0x00,0x00,0x00 };
	/* 0x47 [G] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_39[] = { 0x00,0xE0,0x10,0x08,0x04,0x04,0x04,0x04,0x04,0x08,0x1C,0x00,0x00,\
                                                                     0x00,0x07,0x08,0x10,0x20,0x20,0x21,0x21,0x21,0x21,0x1F,0x01,0x01 };
	/* 0x48 [H] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_40[] = { 0x04,0x04,0xFC,0x84,0x84,0x80,0x80,0x80,0x84,0x84,0xFC,0x04,0x04,\
                                                                     0x20,0x20,0x3F,0x20,0x20,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20 };
	/* 0x49 [I] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_41[] = { 0x00,0x00,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x00,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00 };
	/* 0x4A [J] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_42[] = { 0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x00,\
                                                                     0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x20,0x10,0x0F,0x00,0x00,0x00 };
	/* 0x4B [K] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_43[] = { 0x00,0x04,0x04,0xFC,0x04,0x84,0x40,0x20,0x14,0x0C,0x04,0x04,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x21,0x20,0x01,0x01,0x02,0x0C,0x30,0x20,0x20 };
	/* 0x4C [L] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_44[] = { 0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x3E,0x00 };
	/* 0x4D [M] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_45[] = { 0x04,0x04,0xFC,0x0C,0x30,0xC0,0x00,0xC0,0x30,0x0C,0xFC,0x04,0x04,\
                                                                     0x20,0x20,0x3F,0x20,0x20,0x00,0x03,0x00,0x20,0x20,0x3F,0x20,0x20 };
	/* 0x4E [N] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_46[] = { 0x04,0x04,0xFC,0x0C,0x30,0x40,0x80,0x00,0x04,0x04,0xFC,0x04,0x04,\
                                                                     0x20,0x20,0x3F,0x20,0x20,0x00,0x01,0x06,0x08,0x30,0x3F,0x00,0x00 };
	/* 0x4F [O] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_47[] = { 0x00,0xE0,0x10,0x08,0x04,0x04,0x04,0x04,0x04,0x08,0x10,0xE0,0x00,\
                                                                     0x00,0x07,0x08,0x10,0x20,0x20,0x20,0x20,0x20,0x10,0x08,0x07,0x00 };
	/* 0x50 [P] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_48[] = { 0x00,0x00,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x04,0x88,0x70,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x3F,0x21,0x21,0x21,0x21,0x01,0x00,0x00,0x00 };
	/* 0x51 [Q] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_49[] = { 0x00,0xE0,0x10,0x08,0x04,0x04,0x04,0x04,0x04,0x08,0x10,0xE0,0x00,\
                                                                     0x00,0x07,0x08,0x10,0xA0,0xE0,0xA0,0xA0,0x20,0x10,0x08,0x87,0x00 };
	/* 0x52 [R] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_50[] = { 0x00,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x88,0x70,0x00,0x00,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x21,0x21,0x01,0x01,0x02,0x0C,0x30,0x20,0x20 };
	/* 0x53 [S] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_51[] = { 0x00,0x00,0x30,0x48,0x84,0x84,0x84,0x84,0x84,0x08,0x3C,0x00,0x00,\
                                                                     0x00,0x00,0x3C,0x10,0x20,0x20,0x20,0x20,0x20,0x11,0x0E,0x00,0x00 };
	/* 0x54 [T] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_52[] = { 0x00,0x00,0x7C,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x7C,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,0x00,0x00 };
	/* 0x55 [U] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_53[] = { 0x04,0x04,0xFC,0x04,0x04,0x00,0x00,0x00,0x04,0x04,0xFC,0x04,0x04,\
                                                                     0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x20,0x20,0x10,0x0F,0x00,0x00 };
	/* 0x56 [V] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_54[] = { 0x04,0x0C,0x74,0x84,0x00,0x00,0x00,0x00,0x84,0x74,0x0C,0x04,0x00,\
                                                                     0x00,0x00,0x00,0x01,0x0E,0x30,0x30,0x0E,0x01,0x00,0x00,0x00,0x00 };
	/* 0x57 [W] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_55[] = { 0x04,0x7C,0x84,0x04,0x00,0x80,0x60,0x80,0x00,0x04,0xC4,0x3C,0x04,\
                                                                     0x00,0x00,0x1F,0x20,0x1C,0x03,0x00,0x03,0x1C,0x20,0x1F,0x00,0x00 };
	/* 0x58 [X] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_56[] = { 0x00,0x04,0x04,0x0C,0x34,0x40,0x80,0x40,0x34,0x0C,0x04,0x04,0x00,\
                                                                     0x00,0x20,0x30,0x28,0x26,0x01,0x00,0x01,0x22,0x2C,0x30,0x20,0x00 };
	/* 0x59 [Y] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_57[] = { 0x00,0x04,0x0C,0x14,0x24,0xC0,0x00,0xC0,0x24,0x14,0x0C,0x04,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,0x00,0x00 };
	/* 0x5A [Z] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_58[] = { 0x00,0x00,0x3C,0x04,0x04,0x04,0x84,0x44,0x24,0x14,0x0C,0x00,0x00,\
                                                                     0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x20,0x20,0x20,0x3E,0x00,0x00 };
	/* 0x5B [[] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_59[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x5C [\] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_60[] = { 0x00,0x00,0x03,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x18,0x60,0x80,0x00,0x00,0x00 };
	/* 0x5D []] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_61[] = { 0x00,0x00,0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x5E [^] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_62[] = { 0x00,0x00,0x20,0x10,0x0C,0x02,0x02,0x0C,0x10,0x20,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x5F [_] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_63[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x60 [`] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_64[] = { 0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x02,0x04,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x61 [a] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_65[] = { 0x00,0x00,0x40,0x40,0x20,0x20,0x20,0x20,0x20,0xC0,0x00,0x00,0x00,\
                                                                     0x00,0x1C,0x22,0x21,0x21,0x21,0x21,0x11,0x11,0x3F,0x20,0x20,0x00 };
	/* 0x62 [b] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_66[] = { 0x02,0x02,0xFE,0x80,0x40,0x20,0x20,0x20,0x20,0x40,0xC0,0x00,0x00,\
                                                                     0x20,0x20,0x3F,0x08,0x10,0x20,0x20,0x20,0x20,0x10,0x08,0x07,0x00 };
	/* 0x63 [c] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_67[] = { 0x00,0x00,0x80,0x40,0x20,0x20,0x20,0x20,0x20,0x40,0xE0,0x00,0x00,\
                                                                     0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x20,0x20,0x10,0x08,0x00,0x00 };
	/* 0x64 [d] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_68[] = { 0x00,0x80,0x40,0x40,0x20,0x20,0x20,0x20,0x42,0x82,0xFE,0x00,0x00,\
                                                                     0x00,0x07,0x18,0x10,0x20,0x20,0x20,0x20,0x10,0x18,0x3F,0x20,0x20 };
	/* 0x65 [e] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_69[] = { 0x00,0x00,0x80,0x40,0x20,0x20,0x20,0x20,0x20,0x40,0x80,0x00,0x00,\
                                                                     0x00,0x00,0x0F,0x12,0x22,0x22,0x22,0x22,0x22,0x22,0x13,0x00,0x00 };
	/* 0x66 [f] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_70[] = { 0x00,0x00,0x20,0x20,0x20,0xFC,0x22,0x22,0x22,0x22,0x22,0x02,0x00,\
                                                                     0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00,0x00 };
	/* 0x67 [g] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_71[] = { 0x00,0x00,0x80,0x40,0x20,0x20,0x20,0x20,0x40,0xC0,0xE0,0x20,0x20,\
                                                                     0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x20,0x10,0x18,0xFF,0x00,0x00 };
	/* 0x68 [h] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_72[] = { 0x00,0x02,0x02,0xFE,0x40,0x20,0x20,0x20,0x20,0x40,0x80,0x00,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,0x20,0x20,0x3F,0x20,0x20 };
	/* 0x69 [i] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_73[] = { 0x00,0x00,0x00,0x20,0x20,0x20,0xE6,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00 };
	/* 0x6A [j] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_74[] = { 0x00,0x00,0x20,0x20,0x20,0x20,0x26,0x20,0xE0,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00 };
	/* 0x6B [k] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_75[] = { 0x00,0x00,0x02,0x02,0xFE,0x00,0x00,0xA0,0x60,0x20,0x20,0x00,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x3F,0x02,0x03,0x04,0x28,0x30,0x20,0x20,0x00 };
	/* 0x6C [l] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_76[] = { 0x00,0x00,0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00 };
	/* 0x6D [m] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_77[] = { 0x20,0x20,0xE0,0x40,0x20,0x20,0xC0,0x40,0x20,0x20,0xC0,0x00,0x00,\
                                                                     0x20,0x20,0x3F,0x20,0x20,0x00,0x3F,0x20,0x20,0x00,0x3F,0x20,0x20 };
	/* 0x6E [n] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_78[] = { 0x00,0x20,0x20,0xE0,0x40,0x40,0x20,0x20,0x20,0x40,0x80,0x00,0x00,\
                                                                     0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,0x20,0x20,0x3F,0x20,0x20 };
	/* 0x6F [o] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_79[] = { 0x00,0x00,0x80,0x40,0x20,0x20,0x20,0x20,0x20,0x40,0x80,0x00,0x00,\
                                                                     0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x20,0x20,0x10,0x0F,0x00,0x00 };
	/* 0x70 [p] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_80[] = { 0x20,0x20,0xE0,0x80,0x40,0x20,0x20,0x20,0x20,0x40,0x80,0x00,0x00,\
                                                                     0x00,0x00,0xFF,0x08,0x10,0x20,0x20,0x20,0x20,0x10,0x08,0x07,0x00 };
	/* 0x71 [q] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_81[] = { 0x00,0x00,0x80,0x40,0x20,0x20,0x20,0x20,0x40,0x80,0xE0,0x20,0x20,\
                                                                     0x00,0x00,0x0F,0x10,0x20,0x20,0x20,0x20,0x10,0x10,0xFF,0x00,0x00 };
	/* 0x72 [r] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_82[] = { 0x00,0x00,0x20,0x20,0xE0,0x80,0x40,0x20,0x20,0x20,0x40,0x00,0x00,\
                                                                     0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00 };
	/* 0x73 [s] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_83[] = { 0x00,0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x20,0x40,0xE0,0x00,0x00,\
                                                                     0x00,0x00,0x38,0x11,0x21,0x21,0x21,0x21,0x21,0x12,0x0C,0x00,0x00 };
	/* 0x74 [t] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_84[] = { 0x00,0x00,0x20,0x20,0xFC,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x10,0x10,0x00,0x00 };
	/* 0x75 [u] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_85[] = { 0x00,0x20,0x20,0xE0,0x00,0x00,0x00,0x00,0x20,0x20,0xE0,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x20,0x10,0x3F,0x20,0x20 };
	/* 0x76 [v] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_86[] = { 0x20,0x20,0x60,0xA0,0x20,0x00,0x00,0x00,0xA0,0x60,0x20,0x20,0x00,\
                                                                     0x00,0x00,0x00,0x03,0x0C,0x30,0x30,0x0E,0x01,0x00,0x00,0x00,0x00 };
	/* 0x77 [w] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_87[] = { 0x20,0x20,0xE0,0x20,0x20,0x00,0x80,0x00,0x20,0x20,0xE0,0x20,0x20,\
                                                                     0x00,0x00,0x01,0x1E,0x20,0x1E,0x01,0x1E,0x20,0x1E,0x01,0x00,0x00 };
	/* 0x78 [x] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_88[] = { 0x00,0x20,0x20,0x60,0xA0,0x00,0x00,0x00,0xA0,0x60,0x20,0x20,0x00,\
                                                                     0x00,0x20,0x20,0x30,0x28,0x05,0x02,0x05,0x28,0x30,0x20,0x20,0x00 };
	/* 0x79 [y] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_89[] = { 0x20,0x20,0x60,0xA0,0x00,0x00,0x00,0x00,0x00,0xA0,0x60,0x20,0x20,\
                                                                     0x00,0x00,0x00,0x01,0x06,0x98,0x60,0x18,0x06,0x01,0x00,0x00,0x00 };
	/* 0x7A [z] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_90[] = { 0x00,0x00,0xE0,0x20,0x20,0x20,0x20,0xA0,0x60,0x20,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x20,0x20,0x38,0x00,0x00,0x00 };
	/* 0x7B [{] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_91[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x02,0x02,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x01,0x01,0x7E,0x80,0x80,0x00,0x00,0x00,0x00 };
	/* 0x7C [|] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_92[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00 };
	/* 0x7D [};] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_93[] = { 0x00,0x00,0x00,0x00,0x02,0x02,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x00,0x00,0x00,0x00,0x80,0x80,0x7E,0x01,0x01,0x00,0x00,0x00,0x00 };
	/* 0x7E [~] */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_94[] = { 0x00,0x00,0x00,0xC0,0x40,0xC0,0x80,0x00,0x00,0x00,0x80,0x00,0x00,\
                                                                     0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,0x02,0x03,0x00,0x00,0x00 };
	/* 0x7F */
static const unsigned char __FONT_COURIERNEW13X16__ASCII_32_95[] = { 0xFE,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                                                     0x7F,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

static __FontChar_t __FONT_COURIERNEW13X16[] = {
	{ .c = ' ' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_0  },
	{ .c = '!' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_1  },
	{ .c = '"' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_2  },
	{ .c = '#' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_3  },
	{ .c = '$' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_4  },
	{ .c = '%' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_5  },
	{ .c = '&' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_6  },
	{ .c = '\'', .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_7  },
	{ .c = '(' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_8  },
	{ .c = ')' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_9  },
	{ .c = '*' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_10 },
	{ .c = '+' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_11 },
	{ .c = ',' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_12 },
	{ .c = '-' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_13 },
	{ .c = '.' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_14 },
	{ .c = '/' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_15 },
	{ .c = '0' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_16 },
	{ .c = '1' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_17 },
	{ .c = '2' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_18 },
	{ .c = '3' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_19 },
	{ .c = '4' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_20 },
	{ .c = '5' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_21 },
	{ .c = '6' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_22 },
	{ .c = '7' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_23 },
	{ .c = '8' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_24 },
	{ .c = '9' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_25 },
	{ .c = ':' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_26 },
	{ .c = ';' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_27 },
	{ .c = '<' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_28 },
	{ .c = '=' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_29 },
	{ .c = '>' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_30 },
	{ .c = '?' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_31 },
	{ .c = '@' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_32 },
	{ .c = 'A' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_33 },
	{ .c = 'B' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_34 },
	{ .c = 'C' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_35 },
	{ .c = 'D' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_36 },
	{ .c = 'E' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_37 },
	{ .c = 'F' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_38 },
	{ .c = 'G' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_39 },
	{ .c = 'H' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_40 },
	{ .c = 'I' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_41 },
	{ .c = 'J' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_42 },
	{ .c = 'K' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_43 },
	{ .c = 'L' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_44 },
	{ .c = 'M' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_45 },
	{ .c = 'N' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_46 },
	{ .c = 'O' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_47 },
	{ .c = 'P' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_48 },
	{ .c = 'Q' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_49 },
	{ .c = 'R' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_50 },
	{ .c = 'S' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_51 },
	{ .c = 'T' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_52 },
	{ .c = 'U' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_53 },
	{ .c = 'V' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_54 },
	{ .c = 'W' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_55 },
	{ .c = 'X' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_56 },
	{ .c = 'Y' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_57 },
	{ .c = 'Z' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_58 },
	{ .c = '[' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_59 },
	{ .c = '\\', .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_60 },
	{ .c = ']' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_61 },
	{ .c = '^' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_62 },
	{ .c = '_' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_63 },
	{ .c = '`' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_64 },
	{ .c = 'a' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_65 },
	{ .c = 'b' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_66 },
	{ .c = 'c' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_67 },
	{ .c = 'd' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_68 },
	{ .c = 'e' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_69 },
	{ .c = 'f' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_70 },
	{ .c = 'g' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_71 },
	{ .c = 'h' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_72 },
	{ .c = 'i' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_73 },
	{ .c = 'j' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_74 },
	{ .c = 'k' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_75 },
	{ .c = 'l' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_76 },
	{ .c = 'm' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_77 },
	{ .c = 'n' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_78 },
	{ .c = 'o' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_79 },
	{ .c = 'p' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_80 },
	{ .c = 'q' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_81 },
	{ .c = 'r' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_82 },
	{ .c = 's' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_83 },
	{ .c = 't' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_84 },
	{ .c = 'u' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_85 },
	{ .c = 'v' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_86 },
	{ .c = 'w' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_87 },
	{ .c = 'x' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_88 },
	{ .c = 'y' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_89 },
	{ .c = 'z' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_90 },
	{ .c = '{' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_91 },
	{ .c = '|' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_92 },
	{ .c = '}' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_93 },
	{ .c = '~' , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_94 },
	{ .c = 127 , .height = 16 , .width = 13, .byte = __FONT_COURIERNEW13X16__ASCII_32_95 },
};
#endif

#if GUI_FONT_EXTENTION
/* 0x20 [ ] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_0 [] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x21 [!] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_1 [] = { 0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x03,0x03,0x03,0x00,0x00,0x00,0x00 };
/* 0x22 ["] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_2 [] = { 0x00,0x00,0x00,0x1E,0x06,0x00,0x1E,0x06,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x23 [#] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_3 [] = { 0x00,0x88,0x88,0xFC,0x8B,0x88,0xFC,0x8B,0x88,0x00,\
	                                                                 0x00,0x00,0x06,0x01,0x00,0x06,0x01,0x00,0x00,0x00 };
/* 0x24 [$] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_4 [] = { 0x00,0x00,0x9C,0x22,0x23,0x22,0xE6,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x01,0x07,0x01,0x00,0x00,0x00,0x00 };
/* 0x25 [%] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_5 [] = { 0x00,0x00,0x2C,0xB2,0x72,0x6C,0xA0,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x01,0x02,0x02,0x01,0x00,0x00,0x00 };
/* 0x26 [&] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_6 [] = { 0x00,0x00,0xC0,0x38,0x44,0x84,0x44,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x01,0x02,0x02,0x00,0x00 };
/* 0x27 ['] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_7 [] = { 0x00,0x00,0x00,0x06,0x1E,0x06,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x28 [(] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_8 [] = { 0x00,0x00,0x00,0x00,0xF0,0x0C,0x02,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x01,0x06,0x08,0x00,0x00,0x00 };
/* 0x29 [)] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_9 [] = { 0x00,0x00,0x02,0x0C,0xF0,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x00 };
/* 0x2A [*] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_10[] = { 0x00,0x00,0x08,0x28,0x1E,0x28,0x08,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x2B [+] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_11[] = { 0x00,0x20,0x20,0x20,0xFC,0x20,0x20,0x20,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00 };
/* 0x2C [,] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_12[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x0C,0x07,0x01,0x00,0x00,0x00,0x00,0x00 };
/* 0x2D [-] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_13[] = { 0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x2E [.] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_14[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00 };
/* 0x2F [/] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_15[] = { 0x00,0x00,0x00,0xC0,0x30,0x0C,0x03,0x00,0x00,0x00,\
	                                                                 0x00,0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x30 [0] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_16[] = { 0x00,0xFC,0x02,0x02,0x02,0x02,0xFC,0x00,0x00,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00 };
/* 0x31 [1] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_17[] = { 0x00,0x00,0x04,0x04,0xFE,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x00,0x00 };
/* 0x32 [2] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_18[] = { 0x00,0x0C,0x82,0x42,0x22,0x12,0x0C,0x00,0x00,0x00,\
	                                                                 0x00,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0x00 };
/* 0x33 [3] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_19[] = { 0x00,0x04,0x02,0x02,0x22,0x22,0xDC,0x00,0x00,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00 };
/* 0x34 [4] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_20[] = { 0x00,0x40,0x70,0x4C,0x42,0xFE,0x40,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x02,0x02,0x03,0x02,0x00,0x00,0x00 };
/* 0x35 [5] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_21[] = { 0x00,0x00,0x1E,0x12,0x12,0x12,0xE2,0x00,0x00,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00 };
/* 0x36 [6] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_22[] = { 0x00,0x00,0xF0,0x48,0x24,0x22,0x22,0xC2,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x37 [7] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_23[] = { 0x00,0x06,0x02,0x02,0x82,0x72,0x0E,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00 };
/* 0x38 [8] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_24[] = { 0x00,0xDC,0x22,0x22,0x22,0x22,0xDC,0x00,0x00,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00 };
/* 0x39 [9] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_25[] = { 0x00,0x00,0x1C,0x22,0x22,0x22,0xA2,0x7C,0x00,0x00,\
	                                                                 0x00,0x00,0x02,0x02,0x02,0x01,0x00,0x00,0x00,0x00 };
/* 0x3A [:] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_26[] = { 0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00 };
/* 0x3B [;] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_27[] = { 0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x0C,0x07,0x01,0x00,0x00,0x00,0x00,0x00 };
/* 0x3C [<] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_28[] = { 0x00,0x20,0x20,0x50,0x50,0x88,0x88,0x04,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00 };
/* 0x3D [=] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_29[] = { 0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x3E [>] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_30[] = { 0x00,0x04,0x88,0x88,0x50,0x50,0x20,0x20,0x00,0x00,\
	                                                                 0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x3F [?] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_31[] = { 0x00,0x00,0x0C,0x02,0x42,0x22,0x1C,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00 };
/* 0x40 [@] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_32[] = { 0x00,0x00,0xF8,0x04,0x62,0x92,0x92,0xFC,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x04,0x04,0x02,0x00,0x00,0x00 };
/* 0x41 [A] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_33[] = { 0x00,0x00,0xC0,0xB4,0x8C,0xB0,0xC0,0x00,0x00,0x00,\
	                                                                 0x02,0x03,0x02,0x00,0x00,0x00,0x02,0x03,0x02,0x00 };
/* 0x42 [B] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_34[] = { 0x00,0x04,0xFC,0x24,0x24,0x24,0x24,0xD8,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x43 [C] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_35[] = { 0x00,0xF0,0x08,0x04,0x04,0x04,0x08,0x1C,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x44 [D] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_36[] = { 0x00,0x04,0xFC,0x04,0x04,0x04,0x08,0xF0,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x02,0x02,0x01,0x00,0x00,0x00 };
/* 0x45 [E] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_37[] = { 0x00,0x04,0xFC,0x24,0x24,0x74,0x04,0x9C,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00 };
/* 0x46 [F] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_38[] = { 0x00,0x04,0xFC,0x24,0x24,0x74,0x04,0x1C,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x02,0x00,0x00,0x00,0x00,0x00 };
/* 0x47 [G] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_39[] = { 0x00,0xF0,0x08,0x04,0x44,0x44,0x48,0xCC,0x40,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x48 [H] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_40[] = { 0x00,0x04,0xFC,0x24,0x20,0x20,0x24,0xFC,0x04,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x00,0x00,0x02,0x03,0x02,0x00 };
/* 0x49 [I] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_41[] = { 0x00,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x00,0x00,\
	                                                                 0x00,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x00,0x00 };
/* 0x4A [J] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_42[] = { 0x00,0xC0,0x00,0x04,0x04,0x04,0xFC,0x04,0x04,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00 };
/* 0x4B [K] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_43[] = { 0x00,0x04,0xFC,0x24,0x20,0x54,0x8C,0x04,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x00,0x00,0x00,0x03,0x02,0x00 };
/* 0x4C [L] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_44[] = { 0x00,0x04,0x04,0xFC,0x04,0x04,0x00,0xC0,0x00,0x00,\
	                                                                 0x00,0x02,0x02,0x03,0x02,0x02,0x02,0x03,0x00,0x00 };
/* 0x4D [M] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_45[] = { 0x04,0xFC,0x0C,0x70,0x80,0x70,0x0C,0xFC,0x04,0x00,\
	                                                                 0x02,0x03,0x02,0x00,0x00,0x00,0x02,0x03,0x02,0x00 };
/* 0x4E [N] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_46[] = { 0x00,0x04,0xFC,0x0C,0x30,0xC0,0x04,0xFC,0x04,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x00,0x00,0x03,0x03,0x00,0x00 };
/* 0x4F [O] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_47[] = { 0x00,0xF0,0x08,0x04,0x04,0x04,0x04,0x08,0xF0,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x50 [P] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_48[] = { 0x00,0x04,0xFC,0x44,0x44,0x44,0x44,0x38,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x02,0x02,0x00,0x00,0x00,0x00 };
/* 0x51 [Q] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_49[] = { 0x00,0xF0,0x08,0x04,0x04,0x04,0x04,0x08,0xF0,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x06,0x06,0x06,0x05,0x04,0x00 };
/* 0x52 [R] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_50[] = { 0x00,0x04,0xFC,0x44,0x44,0x44,0xB8,0x00,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x00,0x00,0x00,0x03,0x02,0x00 };
/* 0x53 [S] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_51[] = { 0x00,0x00,0x98,0x24,0x24,0x24,0x28,0xDC,0x00,0x00,\
	                                                                 0x00,0x00,0x03,0x01,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x54 [T] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_52[] = { 0x00,0x3C,0x04,0x04,0xFC,0x04,0x04,0x3C,0x00,0x00,\
	                                                                 0x00,0x00,0x02,0x02,0x03,0x02,0x02,0x00,0x00,0x00 };
/* 0x55 [U] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_53[] = { 0x00,0x04,0xFC,0x04,0x00,0x00,0x04,0xFC,0x04,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x56 [V] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_54[] = { 0x00,0x04,0x3C,0xC4,0x00,0x00,0xC4,0x3C,0x04,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00 };
/* 0x57 [W] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_55[] = { 0x04,0xFC,0x04,0xE0,0x18,0xE0,0x04,0xFC,0x04,0x00,\
	                                                                 0x00,0x01,0x02,0x01,0x00,0x01,0x02,0x01,0x00,0x00 };
/* 0x58 [X] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_56[] = { 0x00,0x04,0x0C,0x94,0x60,0x94,0x0C,0x04,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x00,0x02,0x03,0x02,0x00,0x00 };
/* 0x59 [Y] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_57[] = { 0x04,0x0C,0x14,0x20,0xC0,0x20,0x14,0x0C,0x04,0x00,\
	                                                                 0x00,0x00,0x02,0x02,0x03,0x02,0x02,0x00,0x00,0x00 };
/* 0x5A [Z] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_58[] = { 0x00,0x00,0x0C,0x84,0x44,0x24,0x14,0x8C,0x00,0x00,\
	                                                                 0x00,0x00,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00 };
/* 0x5B [[] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_59[] = { 0x00,0x00,0x00,0x00,0xFE,0x02,0x02,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x0F,0x08,0x08,0x00,0x00,0x00 };
/* 0x5C [\] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_60[] = { 0x00,0x01,0x06,0x18,0x60,0x80,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00 };
/* 0x5D []] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_61[] = { 0x00,0x00,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x08,0x08,0x0F,0x00,0x00,0x00,0x00,0x00 };
/* 0x5E [^] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_62[] = { 0x00,0x10,0x08,0x04,0x03,0x04,0x08,0x10,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x5F [_] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_63[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00 };
/* 0x60 [`] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_64[] = { 0x00,0x00,0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x61 [a] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_65[] = { 0x00,0x00,0xA0,0x50,0x50,0x50,0xE0,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x03,0x02,0x00,0x00 };
/* 0x62 [b] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_66[] = { 0x00,0x02,0xFE,0x20,0x10,0x10,0x10,0xE0,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x01,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x63 [c] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_67[] = { 0x00,0xC0,0x20,0x10,0x10,0x10,0x20,0x30,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x64 [d] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_68[] = { 0x00,0xE0,0x10,0x10,0x10,0x22,0xFE,0x00,0x00,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x01,0x03,0x02,0x00,0x00 };
/* 0x65 [e] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_69[] = { 0x00,0x00,0xE0,0x50,0x50,0x50,0x50,0x60,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x66 [f] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_70[] = { 0x00,0x00,0x10,0x10,0xFC,0x12,0x12,0x12,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x02,0x03,0x02,0x02,0x02,0x00,0x00 };
/* 0x67 [g] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_71[] = { 0x00,0xE0,0x10,0x10,0x10,0x20,0xF0,0x10,0x00,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x01,0x0F,0x00,0x00,0x00 };
/* 0x68 [h] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_72[] = { 0x00,0x02,0xFE,0x20,0x10,0x10,0x10,0xE0,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x00,0x00,0x02,0x03,0x02,0x00 };
/* 0x69 [i] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_73[] = { 0x00,0x00,0x10,0x10,0xF3,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x00,0x00 };
/* 0x6A [j] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_74[] = { 0x00,0x10,0x10,0x10,0x13,0xF0,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00 };
/* 0x6B [k] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_75[] = { 0x00,0x02,0xFE,0x40,0xD0,0x30,0x10,0x00,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x00,0x00,0x03,0x02,0x02,0x00,0x00 };
/* 0x6C [l] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_76[] = { 0x00,0x00,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x00,0x00 };
/* 0x6D [m] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_77[] = { 0x10,0xF0,0x20,0x10,0xE0,0x20,0x10,0xE0,0x00,0x00,\
	                                                                 0x02,0x03,0x02,0x00,0x03,0x02,0x00,0x03,0x02,0x00 };
/* 0x6E [n] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_78[] = { 0x00,0x10,0xF0,0x20,0x10,0x10,0x10,0xE0,0x00,0x00,\
	                                                                 0x00,0x02,0x03,0x02,0x00,0x00,0x02,0x03,0x02,0x00 };
/* 0x6F [o] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_79[] = { 0x00,0x00,0xE0,0x10,0x10,0x10,0x10,0xE0,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x70 [p] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_80[] = { 0x00,0x10,0xF0,0x20,0x10,0x10,0x10,0xE0,0x00,0x00,\
	                                                                 0x00,0x00,0x0F,0x01,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x71 [q] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_81[] = { 0x00,0xE0,0x10,0x10,0x10,0x20,0xF0,0x10,0x00,0x00,\
	                                                                 0x00,0x01,0x02,0x02,0x02,0x01,0x0F,0x00,0x00,0x00 };
/* 0x72 [r] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_82[] = { 0x00,0x00,0x10,0xF0,0x20,0x10,0x10,0x10,0x00,0x00,\
	                                                                 0x00,0x00,0x02,0x03,0x02,0x02,0x02,0x00,0x00,0x00 };
/* 0x73 [s] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_83[] = { 0x00,0x00,0x20,0x50,0x50,0x50,0x50,0xB0,0x00,0x00,\
	                                                                 0x00,0x00,0x03,0x02,0x02,0x02,0x02,0x01,0x00,0x00 };
/* 0x74 [t] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_84[] = { 0x00,0x10,0x10,0xFC,0x10,0x10,0x10,0x10,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x01,0x02,0x02,0x02,0x02,0x01,0x00 };
/* 0x75 [u] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_85[] = { 0x00,0x10,0xF0,0x00,0x00,0x00,0x10,0xF0,0x00,0x00,\
	                                                                 0x00,0x00,0x01,0x02,0x02,0x02,0x01,0x03,0x02,0x00 };
/* 0x76 [v] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_86[] = { 0x00,0x10,0x30,0xD0,0x00,0x00,0xD0,0x30,0x10,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00 };
/* 0x77 [w] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_87[] = { 0x10,0xF0,0x10,0xC0,0x20,0xC0,0x10,0xF0,0x10,0x00,\
	                                                                 0x00,0x01,0x02,0x01,0x00,0x01,0x02,0x01,0x00,0x00 };
/* 0x78 [x] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_88[] = { 0x00,0x10,0x10,0x30,0xC0,0xC0,0x30,0x10,0x10,0x00,\
	                                                                 0x00,0x02,0x02,0x03,0x00,0x00,0x03,0x02,0x02,0x00 };
/* 0x79 [y] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_89[] = { 0x00,0x10,0x30,0xD0,0x00,0x00,0xD0,0x30,0x10,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x0F,0x03,0x00,0x00,0x00,0x00 };
/* 0x7A [z] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_90[] = { 0x00,0x00,0x30,0x10,0x90,0x50,0x30,0x10,0x00,0x00,\
	                                                                 0x00,0x00,0x02,0x03,0x02,0x02,0x02,0x03,0x00,0x00 };
/* 0x7B [{] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_91[] = { 0x00,0x00,0x00,0x40,0xBC,0x02,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x07,0x08,0x00,0x00,0x00,0x00 };
/* 0x7C [|] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_92[] = { 0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00 };
/* 0x7D [}] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_93[] = { 0x00,0x00,0x00,0x02,0xBC,0x40,0x00,0x00,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x08,0x07,0x00,0x00,0x00,0x00,0x00 };
/* 0x7E [~] */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_94[] = { 0x00,0x40,0x20,0x20,0x40,0x80,0x80,0x40,0x00,0x00,\
	                                                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
/* 0x7F */
static const unsigned char __FONT_COURIERNEW10X12__ASCII_32_95[] = { 0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,\
	                                                                 0xFF,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xFF };

static __FontChar_t __FONT_COURIERNEW10X12[] = {
	{ .c = ' ' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_0  },
	{ .c = '!' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_1  },
	{ .c = '"' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_2  },
	{ .c = '#' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_3  },
	{ .c = '$' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_4  },
	{ .c = '%' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_5  },
	{ .c = '&' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_6  },
	{ .c = '\'', .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_7  },
	{ .c = '(' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_8  },
	{ .c = ')' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_9  },
	{ .c = '*' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_10 },
	{ .c = '+' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_11 },
	{ .c = ',' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_12 },
	{ .c = '-' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_13 },
	{ .c = '.' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_14 },
	{ .c = '/' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_15 },
	{ .c = '0' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_16 },
	{ .c = '1' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_17 },
	{ .c = '2' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_18 },
	{ .c = '3' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_19 },
	{ .c = '4' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_20 },
	{ .c = '5' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_21 },
	{ .c = '6' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_22 },
	{ .c = '7' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_23 },
	{ .c = '8' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_24 },
	{ .c = '9' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_25 },
	{ .c = ':' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_26 },
	{ .c = ';' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_27 },
	{ .c = '<' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_28 },
	{ .c = '=' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_29 },
	{ .c = '>' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_30 },
	{ .c = '?' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_31 },
	{ .c = '@' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_32 },
	{ .c = 'A' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_33 },
	{ .c = 'B' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_34 },
	{ .c = 'C' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_35 },
	{ .c = 'D' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_36 },
	{ .c = 'E' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_37 },
	{ .c = 'F' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_38 },
	{ .c = 'G' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_39 },
	{ .c = 'H' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_40 },
	{ .c = 'I' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_41 },
	{ .c = 'J' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_42 },
	{ .c = 'K' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_43 },
	{ .c = 'L' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_44 },
	{ .c = 'M' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_45 },
	{ .c = 'N' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_46 },
	{ .c = 'O' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_47 },
	{ .c = 'P' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_48 },
	{ .c = 'Q' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_49 },
	{ .c = 'R' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_50 },
	{ .c = 'S' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_51 },
	{ .c = 'T' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_52 },
	{ .c = 'U' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_53 },
	{ .c = 'V' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_54 },
	{ .c = 'W' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_55 },
	{ .c = 'X' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_56 },
	{ .c = 'Y' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_57 },
	{ .c = 'Z' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_58 },
	{ .c = '[' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_59 },
	{ .c = '\\', .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_60 },
	{ .c = ']' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_61 },
	{ .c = '^' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_62 },
	{ .c = '_' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_63 },
	{ .c = '`' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_64 },
	{ .c = 'a' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_65 },
	{ .c = 'b' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_66 },
	{ .c = 'c' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_67 },
	{ .c = 'd' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_68 },
	{ .c = 'e' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_69 },
	{ .c = 'f' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_70 },
	{ .c = 'g' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_71 },
	{ .c = 'h' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_72 },
	{ .c = 'i' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_73 },
	{ .c = 'j' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_74 },
	{ .c = 'k' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_75 },
	{ .c = 'l' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_76 },
	{ .c = 'm' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_77 },
	{ .c = 'n' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_78 },
	{ .c = 'o' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_79 },
	{ .c = 'p' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_80 },
	{ .c = 'q' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_81 },
	{ .c = 'r' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_82 },
	{ .c = 's' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_83 },
	{ .c = 't' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_84 },
	{ .c = 'u' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_85 },
	{ .c = 'v' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_86 },
	{ .c = 'w' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_87 },
	{ .c = 'x' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_88 },
	{ .c = 'y' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_89 },
	{ .c = 'z' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_90 },
	{ .c = '{' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_91 },
	{ .c = '|' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_92 },
	{ .c = '}' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_93 },
	{ .c = '~' , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_94 },
	{ .c = 127 , .height = 12 , .width = 10, .byte = __FONT_COURIERNEW10X12__ASCII_32_95 },
};
#endif
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

#if GUI_ANIMATION_DISPLAY
struct __AnimationConfigChain{
	struct GUI_Anim_t config;
	struct __AnimationConfigChain* nextConfig;
	uint  cnt;
};

typedef struct __AnimationConfigChain __AnimationConfigChain;
#endif

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

	size_t           allocated_byte;
//仅适用于动画功能	
#if GUI_ANIMATION_DISPLAY
	__AnimationConfigChain*  cfgAnimationHeadNode;
	size_t                   cfgAnimationNodeCnt;
#endif
}Screen;

static void __insertPixel(int x,int y){
	if( x>=GUI_X_WIDTH || y>=GUI_Y_WIDTH || x<0 || y<0 )
		return;
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

#define __malloc(size)  malloc(size)
#define __free(p)       free(p)
#define __exit(express) if(express) return

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

static void __insertBresenhamCircle(int x, int y, int r,...){
	
	int r_ex  = r+(Screen.penSize>>1);
	int r_in  = r-(Screen.penSize>>1)+((Screen.penSize&0x01)==0);	
	
	int x_ex_tmp = 0;
	int y_ex_tmp = r_ex;
	int x_in_tmp = 0;
	int y_in_tmp = r_in;
	int p_ex  = 3-2*r_ex;
	int p_in  = 3-2*r_in;
	for(;x_ex_tmp<=y_ex_tmp;x_ex_tmp++,x_in_tmp++){
		for(int Y = y_in_tmp;Y<=y_ex_tmp;Y++){
			__insertPixel(x+x_ex_tmp,y+Y);
			__insertPixel(x-x_ex_tmp,y+Y);
			__insertPixel(x+x_ex_tmp,y-Y);
			__insertPixel(x-x_ex_tmp,y-Y);
			__insertPixel(x+Y,y+x_ex_tmp);
			__insertPixel(x-Y,y+x_ex_tmp);
			__insertPixel(x+Y,y-x_ex_tmp);
			__insertPixel(x-Y,y-x_ex_tmp);
		}

		if(p_ex <= 0){
			p_ex += (x_ex_tmp<<2) + 6;
		}else{
			p_ex += ((x_ex_tmp-y_ex_tmp)<<2) + 10;
			y_ex_tmp--;
		}
		if(p_in <= 0){
			p_in += (x_in_tmp<<2) + 6;
		}else{
			p_in += ((x_in_tmp-y_in_tmp)<<2) + 10;
			y_in_tmp--;
		}
	}
}

static void __insertBresenhamLine(int x1,int y1,int x2,int y2){
	int x_min = (int)(GUI_MIN(x1,x2));
	int x_max = (int)(GUI_MAX(x1,x2));
	int y_min = (int)(GUI_MIN(y1,y2));
	int y_max = (int)(GUI_MAX(y1,y2));
	int ∆x    = (int)( x_max - x_min );
	int ∆y    = (int)( y_max - y_min );

	int type = (int)(( ((y2-y1)*(x2-x1)<0) << 1 ) | (∆y > ∆x));

	if(∆y > ∆x){
		int temp = ∆x;
		∆x = ∆y;
		∆y = temp;
	}
	
	int j = 0;
	int e = 0;
	for(int i = 0;i < ∆x;i++){	
		switch(type){
			case 0:__insertPixel(x_min+i,y_min+j);break;
			case 1:__insertPixel(x_min+j,y_min+i);break;
			case 2:__insertPixel(x_min+i,y_max-j);break;
			case 3:__insertPixel(x_min+j,y_max-i);break;
		}
		e += ∆y;
		if( 2*( e + ∆y ) > ∆x){
			j++;
			e -= ∆x;
		}
	}
}

//============================================= End of Internal Config ===============================================//
//============================================= End of Internal Config ===============================================//
//============================================= End of Internal Config ===============================================//

//================================================== Display Config ==================================================//
//================================================== Display Config ==================================================//
//================================================== Display Config ==================================================//

void GUI_Init(void){

	Screen.allocated_byte = 0;

	Screen.txtPos.x = 0;
	Screen.txtPos.y = 0;
	Screen.pFont    = __FONT_STD6X8;
	Screen.penColor = GUI_WHITE;
	Screen.bkColor  = GUI_BLACK;
	Screen.penSize  = 3;

	__clearFrameBuffer();

#if GUI_ANIMATION_DISPLAY
	Screen.cfgAnimationHeadNode = NULL;
	Screen.cfgAnimationNodeCnt  = 0;
#endif

	GUI_RefreashScreen();
}

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
    	// Pixel_t* p = (Pixel_t*)__mallocFrameBuffer((x_width)*(y_width)*sizeof(Pixel_t));
    	Pixel_t* p = (Pixel_t*)malloc((x_width)*(y_width)*sizeof(Pixel_t));
    	for(int y=0;y<y_width;y++){
	        memcpy(&p[x_width*y], &Screen.buffer[y_start+y][x_start].data, x_width*sizeof(Pixel_t));
	    }
		(*GUI_API_DrawArea)(x_start,y_start,x_end,y_end,p);
		// __free(p);
		free(p);
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
		case GUI_FONT_Standard_Small   : Screen.pFont = __FONT_STD6X8;          break;
		case GUI_FONT_Standard_Middle  : Screen.pFont = __FONT_STD8X16;         break;
#if GUI_FONT_EXTENTION
		case GUI_FONT_Bradley_Large    : Screen.pFont = __FONT_BRADLEY_LARGE;   break;
		case GUI_FONT_CourierNew_Middle: Screen.pFont = __FONT_COURIERNEW10X12; break;
		case GUI_FONT_CourierNew_Large : Screen.pFont = __FONT_COURIERNEW13X16; break;
#endif
#if GUI_ASSERT
	    default: (*GUI_API_AssertParam)(false,"Wrong Text Font Type.");         break;
#else
	    default: Screen.pFont = __FONT_STD6X8  ;break;
#endif
	}	
}

void GUI_SetTextPos(unsigned int x,unsigned int y){
	Screen.txtPos.x = x;
	Screen.txtPos.y = y;
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
		if(y == y_start){
			for(unsigned int x=x_start;x<=x_end;x++)
				Screen.buffer[y][x].data = Screen.penColor;
		}else{
			memcpy(&(Screen.buffer[y      ][x_start].data),\
                   &(Screen.buffer[y_start][x_start].data),\
                   ((x_end-x_start+1)*sizeof(Pixel_t)) );
		}
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

	if(clearScreen==true)
		__clearFrameBuffer();

	
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)

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
#else
	BYTE loop = 0;
	unsigned int y_end   = GUI_MAX(y1,y2);
	unsigned int y_start = GUI_MIN(y1,y2);
	unsigned int x_end   = GUI_MAX(x1,x2);
	unsigned int x_start = GUI_MIN(x1,x2);
	while(loop < Screen.penSize){
		uint x = x_start+loop, y = y_start+loop;

		while(x<=(x_end-loop) && y<=(y_end-loop)){
			if( x < (x_end-loop) ){
				__insertPixel(x,y_start + loop);
				__insertPixel(x,y_end   - loop);
				x++;
			}
			else{
				__insertPixel(x_start + loop,y);
				__insertPixel(x_end   - loop,y);
				y++;
			}
		}
		loop++;
	}
#endif

	if(clearScreen == true){
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
	if(clearScreen==true)
		__clearFrameBuffer();
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	unsigned int page_start   = (GUI_LIMIT(y-r,0,GUI_Y_WIDTH))>>3;
	unsigned int page_end     = (GUI_LIMIT(y+r,0,GUI_Y_WIDTH))>>3;
	unsigned int column_start = (GUI_LIMIT(x-r,0,GUI_X_WIDTH));
	unsigned int column_end   = (GUI_LIMIT(x+r,0,GUI_X_WIDTH));

	unsigned int r_2 = r*r;
	for(int i = -r;i <= r;i++){
		for(int j = -r;j <= r;j++){
			if(  (x-i)<GUI_X_WIDTH && (y-j)<GUI_Y_WIDTH && i*i+j*j <= r_2 )
				__insertPixel(x-i,y-j);
		}
	}
#else
	
	unsigned int x_start = GUI_LIMIT(((signed)(x-r)),0,GUI_X_WIDTH);
	unsigned int x_end   = GUI_LIMIT(((signed)(x+r)),0,GUI_X_WIDTH);
	unsigned int y_start = GUI_LIMIT(((signed)(y-r)),0,GUI_Y_WIDTH);	
	unsigned int y_end   = GUI_LIMIT(((signed)(y+r)),0,GUI_Y_WIDTH);
	unsigned int r_2 = r*r;
	for(int i = 0;i <= r;i++){
		for(int j = 0;j <= r;j++){
			if(  i*i+j*j <= r_2 ){
				if(x-i<=GUI_X_WIDTH && y-j<=GUI_Y_WIDTH)
					__insertPixel(x-i,y-j);
				if(x-i<=GUI_X_WIDTH && y+j<=GUI_Y_WIDTH)
					__insertPixel(x-i,y+j);
				if(x+i<=GUI_X_WIDTH && y-j<=GUI_Y_WIDTH)
					__insertPixel(x+i,y-j);
				if(x+i<=GUI_X_WIDTH && y+j<=GUI_Y_WIDTH)
					__insertPixel(x+i,y+j);
			}
		}
	}	
#endif

	if(onlyChangeBuffer != true){
		if(clearScreen == true){
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

void GUI_DrawCircle(int x,int y, int r,...){
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

	if(clearScreen==true)
		__clearFrameBuffer();


#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	int page_start   = (GUI_LIMIT(y-r,0,GUI_Y_WIDTH))>>3;
	int page_end     = (GUI_LIMIT(y+r,0,GUI_Y_WIDTH))>>3;
	int column_start = (GUI_LIMIT(x-r,0,GUI_X_WIDTH-1));
	int column_end   = (GUI_LIMIT(x+r,0,GUI_X_WIDTH-1));

	Pixel_t penColor = Screen.penColor;
	Pixel_t bkColor  = Screen.bkColor;
	GUI_FillCircle(x,y,r,false,true);
	GUI_SetPenColor(bkColor);
	GUI_FillCircle(x,y,r-Screen.penSize,false,true);
	GUI_SetPenColor(penColor);
#else
	int x_end   = GUI_LIMIT(x+r,0,GUI_X_WIDTH-1);
    int x_start = GUI_LIMIT(x-r,0,GUI_X_WIDTH-1);
    int y_end   = GUI_LIMIT(y+r,0,GUI_Y_WIDTH-1);
    int y_start = GUI_LIMIT(y-r,0,GUI_Y_WIDTH-1);

    __insertBresenhamCircle(x,y,r);
#endif

	if(onlyChangeBuffer != true){
		if(clearScreen == true){
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
	if(clearScreen==true)
		__clearFrameBuffer();
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	uint page_start   = GUI_LIMIT( (signed)((GUI_MIN(y1,y2)-Screen.penSize)>>3) ,0 ,GUI_PAGEs);
	uint page_end     = GUI_LIMIT( (signed)((GUI_MAX(y1,y2)+Screen.penSize)>>3) ,0 ,GUI_PAGEs);
	uint column_start = GUI_LIMIT( (signed)(GUI_MIN(x1,x2)-Screen.penSize)      ,0 ,GUI_X_WIDTH-1);
	uint column_end   = GUI_LIMIT( (signed)(GUI_MAX(x1,x2)+Screen.penSize)      ,0 ,GUI_X_WIDTH-1);
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
#else
	__insertBresenhamLine(x1,y1,x2,y2);
#endif

	// if(Screen.penSize>=3){
	// 	GUI_FillCircle(x1,y1,Screen.penSize>>1,false,true);
	// 	GUI_FillCircle(x2,y2,Screen.penSize>>1,false,true);
	// }
	if(onlyChangeBuffer != true){
		if(clearScreen == true){
			GUI_RefreashScreen();
		}else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)			
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
			GUI_RefreashArea(x1,y1,x2,y2);		
#endif			
		}
	}

}

void GUI_DrawWave(int A,float w,float phi,int x_start,int x_end,int y_level,...){
	A = abs(A);

	va_list ap;
	va_start(ap,y_level);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();

	unsigned int page_start   = GUI_LIMIT( (y_level-A)>>3 ,0 ,GUI_PAGEs);
	unsigned int page_end     = GUI_LIMIT( (y_level+A)>>3 ,0 ,GUI_PAGEs);
	unsigned int column_start = GUI_LIMIT( (x_start  )    ,0 ,GUI_X_WIDTH-1);
	unsigned int column_end   = GUI_LIMIT( (x_end    )    ,0 ,GUI_X_WIDTH-1);

	unsigned int x = x_start,x_old = x_start ,y_old = y_level,y = y_level;
	for(;x<=x_end;x++){
		y = (unsigned int)(y_level + A*sin(w*x+phi));
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
	//...//
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
		else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif
		}
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
//====================================================== RGB Test =====================================================//
//====================================================== RGB Test =====================================================//
//====================================================== RGB Test =====================================================//
#if GUI_TEST_EXTENTION
void GUI_TestRGB(unsigned int GUI_TEST_RGB_xxxx ,...){
	static double phi = 0.0;
	WORD penColor   = Screen.penColor;
	WORD penSize    = Screen.penSize;
	Screen.penSize  = 2;
	const double pi = 3.1415926;

	const uint R_MAX = (uint)(1.414*GUI_MAX(GUI_Y_WIDTH,GUI_X_WIDTH));

	if(phi >= 6.28318530717 )
		phi = 0.0;

	switch(GUI_TEST_RGB_xxxx){
		case GUI_TEST_RGB_VER_RAINBOW:
			for( uint x=0; x<GUI_X_WIDTH;x++ ){
				BYTE R = (BYTE)(128+128*sin(2*pi*x/GUI_X_WIDTH + phi          ));
				BYTE G = (BYTE)(128+128*sin(2*pi*x/GUI_X_WIDTH + phi + 2.0*pi/3));
				BYTE B = (BYTE)(128+128*sin(2*pi*x/GUI_X_WIDTH + phi + 4.0*pi/3));
				
				for( uint y=0; y<GUI_Y_WIDTH;y++){
					Screen.penColor = GUI_MAKE_COLOR( R,G,B );
					__insertPixel(x,y);
				}
			}
			break;
		case GUI_TEST_RGB_HOR_RAINBOW:
			for( uint y=0; y<GUI_Y_WIDTH;y++ ){
				BYTE R = (BYTE)(128+128*sin(2*pi*y/GUI_Y_WIDTH + phi          ));
				BYTE G = (BYTE)(128+128*sin(2*pi*y/GUI_Y_WIDTH + phi + 2.0*pi/3));
				BYTE B = (BYTE)(128+128*sin(2*pi*y/GUI_Y_WIDTH + phi + 4.0*pi/3));
				
				for( uint x=0; x<GUI_X_WIDTH;x++){
					Screen.penColor = GUI_MAKE_COLOR( R,G,B );
					__insertPixel(x,y);
				}
			}
			break;
		case GUI_TEST_RGB_ROL_RAINBOW:
			
			for( uint r=0; r<R_MAX;r++ ){
				BYTE R = (BYTE)(128+128*sin(2*pi*r/GUI_Y_WIDTH + phi          ));
				BYTE G = (BYTE)(128+128*sin(2*pi*r/GUI_Y_WIDTH + phi + 2.0*pi/3));
				BYTE B = (BYTE)(128+128*sin(2*pi*r/GUI_Y_WIDTH + phi + 4.0*pi/3));
				Screen.penColor = GUI_MAKE_COLOR( R,G,B );
				__insertBresenhamCircle(GUI_X_WIDTH>>1,GUI_Y_WIDTH>>1,r);	
				
			}
			break;

		default: 
			break;
	}
	GUI_RefreashScreen();
	Screen.penColor = penColor;
	Screen.penSize  = penSize;
	phi+=0.1;
}
#endif
//================================================== End of RGB Test ==================================================//
//================================================== End of RGB Test ==================================================//
//================================================== End of RGB Test ==================================================//
//=================================================== Text Function ===================================================//
//=================================================== Text Function ===================================================//
//=================================================== Text Function ===================================================//
struct __WordChain{
    char* sentence;
    char* word;
    struct __WordChain* nextWord;
};

static struct __WordChain* __creatTextSocket(const char* const_pSentence){
	char* pSentence = (char*)malloc(strlen(const_pSentence));
    strcpy(pSentence, const_pSentence);
    
    char* p = strtok(pSentence," ");

    struct __WordChain* pHeadWord        = (struct __WordChain*)malloc(sizeof(struct __WordChain));
    struct __WordChain* pWord            = pHeadWord;

    pWord->sentence = pSentence;
    pWord->word = p;
    pWord->nextWord = NULL;
    while( (p = strtok(NULL," ")) != NULL ){
        pWord->nextWord = (struct __WordChain*)malloc(sizeof(struct __WordChain));
        pWord           = pWord->nextWord;
        pWord->sentence = pSentence;
        pWord->word     = p;
        pWord->nextWord = NULL;
    }

    return pHeadWord;
}

static void __deleteTextSocket(struct __WordChain* p){
    while(p != NULL){
        struct __WordChain* tmp = p;
        
        if(tmp->nextWord == NULL){
            free(tmp->sentence);
        }
        p = tmp->nextWord;
        free(tmp);
    }
}

static void __insertChar(struct __FontChar_t* pChar){
	for(uint y=0;y < pChar->height;y++){
		for(uint x=0;x < pChar->width ;x++){
			if( (Screen.txtPos.x + x) >= GUI_X_WIDTH )
				while(1);
			if( (Screen.txtPos.y + y) >= GUI_Y_WIDTH )
				while(1);

			if(  ( ((*(pChar->byte + (y>>3)*(pChar->width) + x))>>(y&0x07))&0x01  ) == 1 )
		//  if(  (  (*(pChar->byte + (y/8 )*(pChar->width) + x))>>(y%8   ))&0x01  ) Same effect.
				__insertPixel(Screen.txtPos.x + x,Screen.txtPos.y + y);
			else
				__erasePixel (Screen.txtPos.x + x,Screen.txtPos.y + y);
		}
	}
}

static void __insertWord(const char* word){
	size_t pos = strcspn(word, " ");
	int    num = 0;
    while(pos--){
        struct __FontChar_t* pChar = (Screen.pFont + (*(word+num)) - 32);
        __insertChar(pChar);
        Screen.txtPos.x += pChar->width;
        num++;
    }
}

static void __insertJustifiedText(const char* text,uint xs,uint ys,uint xe,uint ye){
	struct __WordChain* pSentence =  __creatTextSocket(text);

	__deleteTextSocket(pSentence);
}

void GUI_DispChar(unsigned char c,...){

	c = GUI_LIMIT( (c) , ' ' , 127 );
	struct __Screen_t*   s     = &Screen;
	struct __FontChar_t* pChar = (s->pFont + c - 32);

	if(s->txtPos.x > GUI_X_WIDTH - pChar->width){
        s->txtPos.x = 0;
        s->txtPos.y += pChar->height;
        if(s->txtPos.y > GUI_Y_WIDTH - pChar->height)
            s->txtPos.y = 0;
    }

	va_list ap;
	va_start(ap,c);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	uint page_start    = ((s->txtPos.y)>>3);
	uint page_end      = ((s->txtPos.y + pChar->height-1)>>3);
	uint column_start  = s->txtPos.x;
	uint column_end    = s->txtPos.x + pChar->width -1;
#else
	uint x_start       = s->txtPos.x;
	uint y_start       = s->txtPos.y;
	uint x_end         = s->txtPos.x + pChar->width -1;
	uint y_end         = s->txtPos.y + pChar->height-1;
#endif
	__insertChar(pChar);

	if(onlyChangeBuffer!=true){
		if(clearScreen==true)
			GUI_RefreashScreen();
		else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
			GUI_RefreashArea(x_start,y_start,x_end,y_end);			
#endif
		}
	}

	s->txtPos.x += pChar->width;
}

void GUI_DispCharAt(unsigned char c,int x,int y,...){
	Screen.txtPos.x = x;
	Screen.txtPos.y = y;
	GUI_DispChar(c);
}

void GUI_DispChars(unsigned char c,int num,...){
	while(num--){
		GUI_DispChar(c,false,true);
	}
}

void GUI_DispWord(const char* word,...){
	struct __Screen_t*   s = &Screen;

	const char* p = word;
	struct __FontChar_t* pChar;
	size_t      pixLength = 0;
	while(*p!='\0'){
		pChar      = Screen.pFont + (*p - 32);
		pixLength += pChar->width;
		p++;
	}

	if(s->txtPos.x > GUI_X_WIDTH - pixLength){
        s->txtPos.x = 0;
        s->txtPos.y += pChar->height;
        if(s->txtPos.y > GUI_Y_WIDTH - pChar->height)
            s->txtPos.y = 0;
    }

	va_list ap;
	va_start(ap,word);
	const int clearScreen      = va_arg(ap,int);
	const int onlyChangeBuffer = va_arg(ap,int);
	va_end(ap);

	if(clearScreen==true)
		__clearFrameBuffer();

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	uint page_start    = ((s->txtPos.y)>>3);
	uint page_end      = ((s->txtPos.y + pChar->height-1)>>3);
	uint column_start  = s->txtPos.x;
	uint column_end    = s->txtPos.x + pChar->width -1;
#else
	uint x_start       = s->txtPos.x;
	uint y_start       = s->txtPos.y;
	uint x_end         = s->txtPos.x + pixLength -1;
	uint y_end         = s->txtPos.y + pChar->height-1;
#endif
	__insertWord(word);

	if(onlyChangeBuffer!=true){
		if(clearScreen==true)
			GUI_RefreashScreen();
		else{
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#else
			GUI_RefreashArea(x_start,y_start,x_end,y_end);			
#endif
		}
	}

}


//================================================ End of Text Function ================================================//
//================================================ End of Text Function ================================================//
//================================================ End of Text Function ================================================//
//================================================= Dialog Box Function ================================================//
//================================================= Dialog Box Function ================================================//
//================================================= Dialog Box Function ================================================//

#if GUI_DIALOG_DISPLAY
#define __BAR_HEIGHT__    (uint)((10*GUI_Y_WIDTH)>>7) // 10
#define __BUT_SIZE__      (uint)(__BAR_HEIGHT__*0.6)  // 3
#define __BUT_INTERVAL__  (uint)((__BUT_SIZE__)+(__BUT_SIZE__>>1))// 9
#define __BUT_INDENT__    (uint)(__BAR_HEIGHT__*0.7)//7

static void __insertButton(const char* name,Pixel_t color){

}

void GUI_DialogBox(struct GUI_DialogBox_t* p,const char* text,...){
//Save the previous configuration
	uint penColor = Screen.penColor;
	uint penSize  = Screen.penSize;
//Draw Edge
	Screen.penColor = GUI_MAKE_COLOR(232,232,232);
	Screen.penSize  = 1;
	GUI_DrawRect( p->x_start , p->y_start , p->x_end , p->y_end      ,true ,true);
//Draw Bar	
	GUI_FillRect( p->x_start , p->y_start , p->x_end , p->y_start+__BAR_HEIGHT__  ,false,true);
//Draw Box Button
	Screen.penColor = GUI_MAKE_COLOR(224,99 ,88 );
	GUI_FillCircle( p->x_start+__BUT_INDENT__                    , p->y_start+(__BAR_HEIGHT__>>1),(__BUT_SIZE__>>1),false,true );
	Screen.penColor = GUI_MAKE_COLOR(224,193,75 );
	GUI_FillCircle( p->x_start+__BUT_INDENT__+__BUT_INTERVAL__   , p->y_start+(__BAR_HEIGHT__>>1),(__BUT_SIZE__>>1),false,true );
	Screen.penColor = GUI_MAKE_COLOR(104,102,98 );
	GUI_FillCircle( p->x_start+__BUT_INDENT__+__BUT_INTERVAL__*2 , p->y_start+(__BAR_HEIGHT__>>1),(__BUT_SIZE__>>1),false,true );
//Draw User Button
	struct GUI_DialogBox_Button_t* pButton = p->firstButton;
	while(pButton != NULL){
		Screen.penColor = GUI_MAKE_COLOR(232,232,232);
		__insertButton(pButton->name,GUI_BLUE);
		pButton = pButton->nextButton;
	}
//Restore the previous configuration
	Screen.penColor = penColor;
	Screen.penSize  = penSize;	
//Display
	GUI_RefreashArea(p->x_start , p->y_start , p->x_end , p->y_end);	
}
	
#endif

#if GUI_ANIMATION_DISPLAY

static void __removeProgressBar(__AnimationConfigChain* p){
	uint x_start = p->config.x_pos;
	uint y_start = p->config.y_pos;

	int cnt = p->config.height;
	while(cnt--)
		memset(&(Screen.buffer[y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
}

static void __insertProgressBar(__AnimationConfigChain* p,uint fp_0_255_){
	uint x_start = p->config.x_pos;
	uint y_start = p->config.y_pos;
	uint x_end   = x_start + p->config.width  - 1;
	uint y_end   = y_start + p->config.height - 1;
// Clear Area
	{
		int cnt = p->config.height;
		while(cnt--)
			memset(&(Screen.buffer[y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
	}
// Draw Edge
	{
		uint x = x_start, y = y_start;
		while( x<=x_end && y<=y_end ){
			if( x < x_end ){
				Screen.buffer[y_start][x].data = GUI_WHITE;
				Screen.buffer[y_end][x].data   = GUI_WHITE;
				x++;
			}
			else{
				Screen.buffer[y][x_start].data = GUI_WHITE;
				Screen.buffer[y][x_end].data   = GUI_WHITE;
				y++;
			}
		}
	}

// Fill Rect
	{
		uint progress = (fp_0_255_ * (p->config.width-2))>>8;	
		for(uint y=y_start+1;y<y_end;y++){
			if(y == y_start+1){
				for(uint x=1;x<=progress;x++)
					Screen.buffer[y][x_start+x].data = p->config.themeColor;
			}else{
				memcpy(&(Screen.buffer[y        ][x_start+1].data),\
					   &(Screen.buffer[y_start+1][x_start+1].data),\
					   progress*sizeof(Pixel_t) );
			}
		}
	}
}

static void __insertProgressLoop(__AnimationConfigChain* p,uint fp_0_255_){
	uint x_center = p->config.x_pos + ((p->config.width)>>1);
	uint y_center = p->config.x_pos + ((p->config.height)>>1);
	uint radius   = (p->config.width>>1)-2;
	uint phi      = ((fp_0_255_*360)>>8);
	uint x_start = p->config.x_pos;
	uint y_start = p->config.y_pos;

// Clear Area
	int cnt = p->config.height;
	while(cnt--)
		memset(&(Screen.buffer[y_start+cnt][x_start].data),0,(p->config.width)*sizeof(Pixel_t) );
// Draw a Circle
	__insertBresenhamCircle(x_center,y_center,radius);
// Erase part of it
	if(phi > 180){
		

	}else if(phi < 180){

	}else{
		int cnt = p->config.height;
		while(cnt--)
			memset(&(Screen.buffer[y_start+cnt][x_start].data),0,radius*sizeof(Pixel_t) );
	}

}


static __AnimationConfigChain* __searchAnimationConfigChain(BYTE ID){
	__AnimationConfigChain* p = Screen.cfgAnimationHeadNode;

	while(p != NULL){
		if(p->config.ID == ID)
			break;

		p = p->nextConfig;
	}

	return p;
}

// 创建一个动画插件
void GUI_CreateAnimationSocket(struct GUI_Anim_t* config){
	__AnimationConfigChain* pConfig = Screen.cfgAnimationHeadNode;
	__AnimationConfigChain* pTmpConfig = (__AnimationConfigChain*)__malloc(sizeof(struct __AnimationConfigChain));
	pTmpConfig->config     = *config;	
	pTmpConfig->nextConfig = NULL;

// ID should be unique.
	if( NULL != __searchAnimationConfigChain(config->ID) ){
#if GUI_ASSERT
		//...//
#endif		
		return;
	}

	if(pConfig == NULL)
		Screen.cfgAnimationHeadNode = pTmpConfig;
	else{
		do{
			if(pConfig->nextConfig == NULL){
				pConfig->nextConfig = pTmpConfig;
				break;
			}
			pConfig = pConfig->nextConfig;
		}while(1);
	}
}

// 显示动画插件
void GUI_ShowAnimation(BYTE ID,uint fp_0_255_,...){
	__AnimationConfigChain* pNow = __searchAnimationConfigChain(ID);

	if(pNow == NULL){
#if GUI_ASSERT
		//...//
#endif		
		return;
	}

	switch(pNow->config.GUI_ANIM_xxxx){
		case GUI_ANIM_ProgressBar:
			__insertProgressBar(pNow,fp_0_255_);
			break;
		case GUI_ANIM_ProgressLoop:
			__insertProgressLoop(pNow,fp_0_255_);
		default: 
			break;
	}

	uint x_start = pNow->config.x_pos;
	uint y_start = pNow->config.y_pos;
	uint x_end   = pNow->config.x_pos + pNow->config.width  - 1;
	uint y_end   = pNow->config.y_pos + pNow->config.height - 1;

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	//...//
#else
	GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
}

// 隐藏动画插件
void GUI_HideAnimation(BYTE ID){
	__AnimationConfigChain* pNow = __searchAnimationConfigChain(ID);

	if(pNow == NULL){
#if GUI_ASSERT
		//...//
#endif		
		return;
	}

	switch(pNow->config.GUI_ANIM_xxxx){
		case GUI_ANIM_ProgressBar:
			__removeProgressBar(pNow);
			break;
		default: 
			break;
	}
	
	uint x_start = pNow->config.x_pos;
	uint y_start = pNow->config.y_pos;
	uint x_end   = pNow->config.x_pos + pNow->config.width  - 1;
	uint y_end   = pNow->config.y_pos + pNow->config.height - 1;

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	//...//
#else
	GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif
}

// 删除动画插件
void GUI_DeleteAnimationSocket(BYTE ID){
	uint x_start = 0;
	uint y_start = 0;
	uint x_end   = 0;
	uint y_end   = 0;
	__AnimationConfigChain* pNow  = Screen.cfgAnimationHeadNode;
	__AnimationConfigChain* pLast = Screen.cfgAnimationHeadNode;
	while(pNow != NULL){
		if(pNow->config.ID == ID){
			pLast->nextConfig = pNow->nextConfig;
			__removeProgressBar(pNow);
			x_start = pNow->config.x_pos;
			y_start = pNow->config.y_pos;
			x_end   = pNow->config.x_pos + pNow->config.width  - 1;
			y_end   = pNow->config.y_pos + pNow->config.height - 1;
			__free(pNow);
			break;
		}
		pLast = pNow;
		pNow  = pNow->nextConfig;
	}
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	//...//
#else
	GUI_RefreashArea(x_start,y_start,x_end,y_end);
#endif

}

#endif

//============================================== End of Dialog Box Function ============================================//
//============================================== End of Dialog Box Function ============================================//
//============================================== End of Dialog Box Function ============================================//
//=================================================== Icon Function ====================================================//
//=================================================== Icon Function ====================================================//
//=================================================== Icon Function ====================================================//
#if GUI_ICON_DISPLAY

void GUI_Icon(struct GUI_Icon_t* p,...){

}
#endif
//=============================================== End of Icon Function =================================================//
//=============================================== End of Icon Function =================================================//
//=============================================== End of Icon Function =================================================//
//=================================================== Demo Function ====================================================//
//=================================================== Demo Function ====================================================//
//=================================================== Demo Function ====================================================//

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
	GUI_SetPenSize(3);
	for(unsigned int x = 0;x < GUI_X_WIDTH;x++)
		GUI_DrawRect(x,(GUI_Y_WIDTH-1)-(unsigned int)(x*(GUI_Y_WIDTH*1.0/GUI_X_WIDTH)),GUI_X_WIDTH>>1,GUI_Y_WIDTH>>1,true,false);
	for(unsigned int x = 0;x < GUI_X_WIDTH;x++)
		GUI_DrawRect(x,(unsigned int)(x*(GUI_Y_WIDTH*1.0/GUI_X_WIDTH))                ,GUI_X_WIDTH>>1,GUI_Y_WIDTH>>1,true,false);
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
	for(double w=0.0;w<1.5;w+=0.01){
		GUI_DrawWave(A,w,0.0,x_start,x_end,y_level,true,true);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
		GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
#endif		
	}
	for(double w=1.5;w>0.0;w-=0.01){
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
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)			
		GUI_RefreashPageArea(( (y_level-A)>>3),((y_level+A)>>3),x_start,x_end );
#endif		
	}
}

inline void GUI_DEMO_Rotation_1(void){
	
	const unsigned int radius = (int)(((GUI_MIN(GUI_X_WIDTH,GUI_Y_WIDTH))>>2)-2);
	const unsigned int x      = GUI_X_WIDTH>>1;
	const unsigned int y      = GUI_Y_WIDTH>>1;
	GUI_SetPenColor(GUI_WHITE);
	GUI_SetPenSize(3);
	for(double Ø=0;Ø<360;Ø+=0.1){
		const float π = 3.1415926;
		GUI_SetPenSize (3);
		GUI_DrawCircle (x,y,radius,true,true);
		GUI_SetPenSize (1);
		GUI_DrawLine   (x,y,x-(radius-2)*cos(Ø)       ,y-(radius-2)*sin(Ø)       ,false,true);
		GUI_DrawLine   (x,y,x-(radius-2)*cos(Ø+2*π/3) ,y-(radius-2)*sin(Ø+2*π/3) ,false,true);
		GUI_DrawLine   (x,y,x-(radius-2)*cos(Ø-2*π/3) ,y-(radius-2)*sin(Ø-2*π/3) ,false,true);
		GUI_SetPenSize (3);
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN) && (GUI_COLOR_TYPE == GUI_1Bit)
		GUI_RefreashPageArea(0,7,64-30,64+30);
#else
		GUI_RefreashArea(x-radius-GUI_GetPenSize(),\
			             y-radius-GUI_GetPenSize(),\
			             x+radius+GUI_GetPenSize(),\
			             y+radius+GUI_GetPenSize());		
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

inline void GUI_DEMO_Microsoft_1(void){
	GUI_SetBackColor(GUI_BLACK);
    GUI_SetPenSize(3);

	GUI_SetPenColor(GUI_RED);
    GUI_DrawRect(24,24,64,64,false,false);
    GUI_SetPenColor(GUI_GREEN);
    GUI_DrawRect(94,24,64,64,false,false);
    GUI_SetPenColor(GUI_BLUE);
    GUI_DrawRect(24,94,64,64,false,false);
    GUI_SetPenColor(GUI_YELLOW);
    GUI_DrawRect(94,94,64,64,false,false);
}

#endif

#if GUI_ANIMATION_DISPLAY
inline void GUI_DEMO_ANIM_ProgressBar(void){
	static bool initFlag = false;
	if(initFlag == false){
		struct GUI_Anim_t config = {
	        .GUI_ANIM_xxxx = GUI_ANIM_ProgressBar,
	        .themeColor    = GUI_LIGHTGREEN,
	        .ID            = 0x01,
	        .x_pos         = 20,
	        .y_pos         = 40,
	        .height        = 15,
	        .width         = 90,
	        .text          = "Progress Bar",
	    };
	    GUI_CreateAnimationSocket(&config);

	    config.themeColor = GUI_LIGHTGRAY;
	    config.ID         = 0x02;
	    config.height     = 4;
	    config.width      = 90;
	    config.x_pos      = 20;
	    config.y_pos      = 10;
	    GUI_CreateAnimationSocket(&config);

	    config.themeColor = GUI_LBBLUE;
	    config.ID         = 0x03;
	    config.height     = 5;
	    config.width      = 70;
	    config.x_pos      = 20;
	    config.y_pos      = 24;
	    GUI_CreateAnimationSocket(&config);

	    config.themeColor = GUI_RED;
	    config.ID         = 0x04;
	    config.height     = 11;
	    config.width      = 90;
	    config.x_pos      = 20;
	    config.y_pos      = 60;
	    GUI_CreateAnimationSocket(&config);
	}

	initFlag = true;

    int i = 0;
    while(i++ < 255){
        GUI_ShowAnimation(0x01,i);
        GUI_ShowAnimation(0x02,i);
        GUI_ShowAnimation(0x03,i);
        GUI_ShowAnimation(0x04,i);
    }
}
#endif

//================================================ End of Demo Function ================================================//
//================================================ End of Demo Function ================================================//
//================================================ End of Demo Function ================================================//


#if 0

#endif

//===================================================== End of File ====================================================//
//===================================================== End of File ====================================================//
//===================================================== End of File ====================================================//


