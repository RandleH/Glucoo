
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


#include "BLK_dsp.h"

int main(int argc, char const *argv[]){
    
    cvar x[] = { 0,1,2,3,4,5,6,0.8,8,9,10,11,12,13,14,15};
    BLK_SRCT(Cseq) X    = __BLK_Dsp_dft(x, sizeof(x)/sizeof(*x));

    
    __BLK_Dsp_fft( NULL, 234);
    
    __BLK_Dsp_cseq_free(X);
    
    
    
#if 0
    
    GLU_GUI_init();
    BLK_Graph_init();
    
    GLU_TYPE(Color) colors_sky[2] = { MAKE_COLOR( 10, 10, 88 ), MAKE_COLOR( 10, 10, 16) };
    __Area_t area_sky = {
        .xs = 0 , .ys = 0,
        .w  = RH_CFG_SCREEN_WIDTH-1 , .h  = RH_CFG_SCREEN_HEIGHT-1,
    };
    
    GLU_TYPE(Color) colors_moon[2] = { MAKE_COLOR( 208, 208, 208 ), MAKE_COLOR( 15, 17, 16) };
    __Area_t area_moon = {
        .xs = 300 , .ys = 300,
        .w  = 400 , .h  = 400,
    };
    
    GLU_TYPE(Color) colors_land[2] = { MAKE_COLOR(  24,  44,  21 ), MAKE_COLOR( 20, 20, 20) };
    __Area_t area_land = {
        .xs = 0   , .ys = 1790,
        .w  = RH_CFG_SCREEN_WIDTH, .h = RH_CFG_SCREEN_HEIGHT-1790+1
    };
    
    GLU_TYPE(Color) colors_roof[2] = { MAKE_COLOR(  31,  31,  31 ), MAKE_COLOR( 11, 10, 20) };
    __Area_t area_roof = {
        .xs = 1018 , .ys = 1418,
        .w  = 660  , .h = 151
    };
    
    GLU_TYPE(Color) colors_wall[2] = { MAKE_COLOR(  21,  21,  21 ), MAKE_COLOR( 11, 10, 20) };
    __Area_t area_wall = {
        .xs = area_roof.xs + 100    , .ys = area_roof.ys+area_roof.h,
        .w  = area_roof.w  - 100*2  , .h  = area_land.ys-(area_roof.ys+area_roof.h)+1
    };
    
    GLU_TYPE(Color) colors_door[2] = { MAKE_COLOR(  21,  21,  21 ), MAKE_COLOR( 11, 10, 20) };
    __Area_t area_door = {
        .xs = area_wall.xs + 180    , .ys = area_wall.ys+70,
        .w  = area_wall.w  - 180*2  , .h  = area_wall.h -70
    };
    
    // Create a render
    GLU_Handle_Render_t sky  = GLU_Render_EX_create( &area_sky , colors_sky , 2, kGLU_Render_gradient_v_24bit );
    GLU_Handle_Render_t moon = GLU_Render_EX_create( &area_moon, colors_moon, 2, kGLU_Render_centered_24bit   );
    GLU_Handle_Render_t land = GLU_Render_EX_create( &area_land, colors_land, 2, kGLU_Render_gradient_v_24bit );
    GLU_Handle_Render_t roof = GLU_Render_EX_create( &area_roof, colors_roof, 2, kGLU_Render_gradient_h_24bit );
    GLU_Handle_Render_t wall = GLU_Render_EX_create( &area_wall, colors_wall, 2, kGLU_Render_gradient_v_24bit );
    
    // Given the GRAM
    BLK_SRCT(Img888) IMG = { .h = RH_CFG_SCREEN_HEIGHT, .w = RH_CFG_SCREEN_WIDTH, .ptr = GLU_GUI_yield_GRAM() };
    
    // Draw Sky
    BLK_Graph_EX_rect_fill(&area_sky, &IMG, GLU_Render_upload(sky) );
    
    // Draw Moon
    BLK_Graph_circle_fill((area_moon.xs+area_moon.w/2), (area_moon.ys+area_moon.h/2), area_moon.w, &IMG, GLU_Render_upload(moon));
    
    // Draw land
    BLK_Graph_EX_rect_fill(&area_land, &IMG, GLU_Render_upload(land) );
    
    // Draw roof
    BLK_Graph_quad_fill(area_roof.xs                  , area_roof.ys+area_roof.h-1,\
                        area_roof.xs+200              , area_roof.ys              ,\
                        area_roof.xs+area_roof.w-1    , area_roof.ys+area_roof.h-1, \
                        area_roof.xs+area_roof.w-200-1, area_roof.ys, &IMG, GLU_Render_upload(roof));
    
    // Draw wall
    BLK_Graph_EX_rect_fill(&area_wall, &IMG, GLU_Render_upload(wall) );
    
    // Draw door
    BLK_Graph_set_penColor(M_COLOR_BLACK);
    BLK_Graph_EX_rect_fill(&area_door, &IMG, NULL );
    
    GLU_GUI_refreashEntireScreen();
    GLU_Render_free(moon);
    GLU_Render_free(land);
    GLU_Render_free(roof);
    open_img();
    
    return 0;
    
#endif
    
    
}

#endif
