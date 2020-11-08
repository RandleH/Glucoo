
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include "RH_GUI.h"


#pragma anon_unions

void (*GUI_API_DrawArea)      (unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,const Pixel_t* pixData) = NULL; 

void (*GUI_API_DrawPixel)     (unsigned int x,unsigned int y,const Pixel_t pixData) = NULL;

void (*GUI_API_DelayMs)       (unsigned long ms) = NULL;

#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )
void (*GUI_API_DrawPageColumn)(unsigned int page,unsigned int column_start,unsigned int column_num,const Pixel_t* data) = NULL;
#endif

#if GUI_ASSERT
void (*GUI_API_AssertParam)   (bool expression,const char* WHAT_IS_WRONG )  = NULL;
#endif


#if ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN )

union PixelUnit_t{
	struct{
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
// *
// *
// *
// *
// *
// *

#elif ( GUI_DISPLAY_MODE == GUI_SINGLE_PIXEL )

#if ( GUI_COLOR_TYPE == GUI_1Bit)

union PixelUnit_t{
	struct{
		Pixel_t bit : 1;
	};
  	Pixel_t data;
};
typedef union PixelUnit_t PixelUnit_t;
// *
// *
// *
// *
// *
// *
// *
// *

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
// *
// *
// *
// *
// *
// *
// *
// *

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
// *
// *
// *
// *
// *
// *

#endif

#endif

static struct Screen_t{

#if   ( GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	PixelUnit_t buffer[ GUI_PAGEs  ][ GUI_X_WIDTH ];
#elif ( GUI_DISPLAY_MODE == GUI_SINGLE_PIXEL )
	PixelUnit_t buffer[ GUI_Y_WIDTH][ GUI_X_WIDTH ];
#endif
	
	Pixel_t          penColor;
	unsigned int     penSize;
	Pixel_t          bkColor;
	
}Screen;


static inline void __insertPixel(unsigned int x,unsigned int y){

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
	int temp = y&0x07;
	switch(temp){
		case 0:Screen.buffer[ y>>3 ][x].bit0 = (bool)Screen.penColor;break;
		case 1:Screen.buffer[ y>>3 ][x].bit1 = (bool)Screen.penColor;break;
		case 2:Screen.buffer[ y>>3 ][x].bit2 = (bool)Screen.penColor;break;
		case 3:Screen.buffer[ y>>3 ][x].bit3 = (bool)Screen.penColor;break;
		case 4:Screen.buffer[ y>>3 ][x].bit4 = (bool)Screen.penColor;break;
		case 5:Screen.buffer[ y>>3 ][x].bit5 = (bool)Screen.penColor;break;
		case 6:Screen.buffer[ y>>3 ][x].bit6 = (bool)Screen.penColor;break;
		case 7:Screen.buffer[ y>>3 ][x].bit7 = (bool)Screen.penColor;break;
	}
#else
	Screen.buffer[y][x].data = Screen.penColor;
#endif
}

static inline void __clearFrameBuffer(void){
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
static inline void* __mallocFrameBuffer(unsigned long size){
	return malloc(size);
}

#define __free(p) free(p)

#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
static inline void __clearPageArea(unsigned int page_start,unsigned int page_end,unsigned int column_start,unsigned int column_end){
	Pixel_t* p;
	unsigned int length = column_end - column_start+1;
	for(unsigned int page=page_start;page<=page_end;page++){
		p  = (Pixel_t*)&Screen.buffer[page];
		p += column_start;
		memset(p, (Screen.penColor == GUI_WHITE)?(0x00):(0xff) ,(length)*sizeof(Screen.buffer[0][0].data));
	}
}
#endif

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
	unsigned int column_num = column_end-column_start;
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
		memset(Screen.buffer[page]+column_start,(Screen.penColor == GUI_WHITE)?(0xff):(0x00),(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
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
		memset(Screen.buffer[page]+column_start,(Screen.penColor == GUI_WHITE)?(0xff):(0x00),(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
	}

	Screen.penColor = ~Screen.penColor;

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
			memset(Screen.buffer[page]+column_start,(Screen.penColor == GUI_WHITE)?(0xff):(0x00),(column_end-column_start+1)*sizeof(Screen.buffer[0][0].data));
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

	Screen.penColor = ~Screen.penColor;
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

	GUI_FillCircle(x,y,r,false,true);
	Screen.penColor = ~Screen.penColor;
	GUI_FillCircle(x,y,r-Screen.penSize,false,true);
	Screen.penColor = ~Screen.penColor;
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

	GUI_FillEllipse(x,y,rx               ,ry               ,false,true);
	Screen.penColor = ~Screen.penColor;
	GUI_FillEllipse(x,y,rx-Screen.penSize,ry-Screen.penSize,false,true);
	Screen.penColor = ~Screen.penColor;

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
			memset(Screen.buffer[page]+column_start-offset,(Screen.penColor == GUI_WHITE)?(0xff):(0x00),(Screen.penSize)*sizeof(Screen.buffer[0][0].data));
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

void GUI_FillTriangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,...){
	

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

	double K = ((double)(y1-y2)) / ((double)(x1-x2));
	double B = y1-K*x1;

	...// Haven't finished yet. Let's create an error.  //  :-(

	if(onlyChangeBuffer!=true){
		if(clearScreen==true)
			GUI_RefreashScreen();
		else
#if (GUI_DISPLAY_MODE == GUI_OLED_PAGE_COLUMN)
			GUI_RefreashPageArea(page_start,page_end,column_start,column_end);
#endif
	}
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



#if 0

#include <stdio.h>
void assert_param(bool express){
	if(!express)
		while(1);
}

int main(void){
    printf("APP Start\n");
	GUI_API_AssertParam = assert_param;
    return 0;
}

#endif




