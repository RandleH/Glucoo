
#include <unistd.h>

#include "RH_common.h"
#include "RH_color.h"

#include "GLU_api.h"
#include "GLU_glucoo.h"
#include "GLU_area.h"


#include "GLU_image.h"
#include "GLU_object.h"

#include "GLU_render.h"


#include "BLK_graphic.h"

static void open_img(void){
    char path[255] = {0};
    const char* name = "snapshot";
    sprintf( path, "%s/%s.bmp", RH_DIR, name );
    
    char cmd[255+9] = {0};
    sprintf( cmd, "open %s", path);
    system(cmd);
}

int main(int argc, char const *argv[]){
    printf("%x\n", REVERSE_COLOR( M_COLOR_WHITE ));
    
    GLU_GUI_init();
    
    __Area_t area_render = { .xs = 0, .ys = 0, .h = RH_CFG_SCREEN_HEIGHT, .w = RH_CFG_SCREEN_WIDTH };
    
    GLU_TYPE(Color) colors[2] = { M_COLOR_DARKVOILET, M_COLOR_BLACK };
    
    GLU_Render_set_color ( colors, 2);
    GLU_Render_set_area  ( &area_render, sizeof(area_render) );
    
    BLK_SRCT(Img888) IMG = {.w = RH_CFG_SCREEN_WIDTH, .h = RH_CFG_SCREEN_HEIGHT, .ptr = GLU_GUI_yield_GRAM() };

    BLK_Graph_init();
    
#define  NUM_RECT_H  5
    
    __Area_t area_all = { .xs = 0, .ys = 100, .h = 300                 , .w = RH_CFG_SCREEN_WIDTH    };
    __Area_t area_sub[ NUM_RECT_H ] = {
        {.h=300, .w=500},
        {.h=300, .w=500},
        {.h=300, .w=500},
        {.h=300, .w=500},
        {.h=300, .w=500},
    };
    GLU_Utility_area_hdiv(&area_all, &area_sub[0], NUM_RECT_H);
    
    BLK_Graph_set_penSize(100);
    for( int i=0; i<NUM_RECT_H; i++ ){
        BLK_Graph_EX_rect_round_fill( &area_sub[i], &IMG, GLU_Render_24bit_blur );
        area_sub[i].ys = RH_CFG_SCREEN_HEIGHT-area_sub[i].h-100;
        BLK_Graph_EX_rect_round_fill( &area_sub[i], &IMG, GLU_Render_24bit_blur );
    }
    GLU_Font_set_font( kGLU_Font_Optima );
    GLU_Font_set_size( 150 );
    
    GLU_SRCT(FontImg)* pFontImg = GLU_Font_out_str_Img("He is sending you instagram!");
    __Area_t area_tmp;
    GLU_Utility_align_screen(pFontImg->img_w, pFontImg->img_h, &area_tmp, M_UTILITY_ALIGN_HM|M_UTILITY_ALIGN_VM);
    BLK_SRCT(ImgGry) FontImg = { .w = pFontImg->img_w, .h = pFontImg->img_h, .ptr = (BLK_UION(PixelGry)*)pFontImg->img_buf,   };
    BLK_ImgGry_into_Img888( &FontImg, &IMG, area_tmp.xs, area_tmp.ys, M_COLOR_DARKVOILET, 90);
    
    GLU_GUI_refreashEntireScreen();
    
    open_img();
    return 0;
}



