
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

//
//int main(int argc, char const *argv[]){
//    GLU_GUI_init();
//
//    BLK_SRCT(Img888) *pSRC = BLK_Img888_load_jpg("/Users/randle_h/Downloads/IMG_0772.jpg");
//
//
//    BLK_SRCT(Img888) *pDST = BLK_Img888_create(pSRC->w, pSRC->h);
//
//    __Area_t area = {
//        .w = pSRC->w ,
//        .h = pSRC->h ,
//        .xs = 0,
//        .ys = 0
//    };
//
//    BLK_Img888_blur_gussian(pSRC, pDST, &area, 44100, 100);
//
//    BLK_Img888_out_bmp("/Users/randle_h/Desktop/summer.bmp", pDST);
//}


# if 1

int main(int argc, char const *argv[]){
    printf("%x\n", REVERSE_COLOR( M_COLOR_WHITE ));
    
    GLU_GUI_init();
    
    GLU_TYPE(Color) colors[2] = { MAKE_COLOR(255,30,90), MAKE_COLOR(255, 205, 50) };
    
    BLK_SRCT(Img888) IMG = {.w = RH_CFG_SCREEN_WIDTH, .h = RH_CFG_SCREEN_HEIGHT, .ptr = GLU_GUI_yield_GRAM() };

    BLK_Graph_init();
    
    GLU_Render_set_area(90, 100, 500, 700);
    GLU_Render_set_color(colors, 2);
    
    BLK_Graph_rect_edged(90, 100, 500, 700, &IMG, GLU_Render_24bit_gradient_v );
    
    int d = 400;
    BLK_Graph_set_penSize(20);
    
    GLU_Render_set_area(1000-(d>>1), 1000-(d>>1), 1000+(d>>1), 1000+(d>>1));
    BLK_Graph_circle_edged( 1000, 1000, d, &IMG, GLU_Render_24bit_gradient_v);
    
    d = 300;
    GLU_Render_set_area(1000-(d>>1), 1000-(d>>1), 1000+(d>>1), 1000+(d>>1));
    colors[0] = MAKE_COLOR( 203,  34, 203);
    colors[1] = MAKE_COLOR( 233, 234, 240);
    GLU_Render_set_color( colors, 2);
    BLK_Graph_circle_edged( 1000, 1000, d, &IMG, GLU_Render_24bit_gradient_h);
    
    d = 200;
    GLU_Render_set_area(1000-(d>>1), 1000-(d>>1), 1000+(d>>1), 1000+(d>>1));
    colors[0] = MAKE_COLOR(  40, 175, 203);
    colors[1] = MAKE_COLOR( 240, 240, 240);
    GLU_Render_set_color( colors, 2);
    BLK_Graph_circle_edged( 1000, 1000, d, &IMG, GLU_Render_24bit_gradient_v);
    
    d = 100;
    GLU_Render_set_area(1000-(d>>1), 1000-(d>>1), 1000+(d>>1), 1000+(d>>1));
    colors[0] = MAKE_COLOR( 240,  40, 140);
    colors[1] = MAKE_COLOR(  40, 125, 203);
    GLU_Render_set_color( colors, 2);
    BLK_Graph_circle_fill( 1000, 1000, d, &IMG, GLU_Render_24bit_gradient_h);
    
    GLU_GUI_refreashEntireScreen();
    
    open_img();
    return 0;
}



#endif
