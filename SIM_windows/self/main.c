#include "RH_common.h"
#include "RH_config.h"
#include "BLK_image.h"
#include "GLU_Glucoo.h"
#include "GLU_image.h"
#include "BLK_graphic.h"

extern BLK_TYPE(Canvas) info_MainScreen; //...//


int main(void){
	
	printf("%s\n", RH_DIR_PRJ );
	GLU_API_init();
	GLU_GUI_init();
	
	GLU_SRCT(Text) text = {
		.align = kGLU_Align_Middle,
		.size  = 520              ,
		.str   = "KIRBY"         ,
		.color = M_COLOR_BLACK    ,
		.font  = kGLU_Font_Optima ,  
	};
	
	BLK_TYPE(Pixel888) colors[2] = {
		M_COLOR_PINK ,
		M_COLOR_BLACK
	}; 
	
	GLU_Image_profile( kGLU_ImageStyle_blur, colors, 2, &text, 70);
	
    GLU_Font_set_font(kGLU_Font_Unscii);
    GLU_Font_set_size(140);
    GLU_SRCT(FontImg)* pF = GLU_Font_out_str_Img("BiBiBaBi Bong~");
    BLK_SRCT(ImgGry) img_font = {
        .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf ,
        .height  = pF->img_h   ,
        .width   = pF->img_w
    };
    BLK_ImgGry_into_Img888(&img_font, &info_MainScreen, 667, 1516, M_COLOR_BLACK, 100);

		
	GLU_GUI_refreashEntireScreen();
	
	return 0;
}
