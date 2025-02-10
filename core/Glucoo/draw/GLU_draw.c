
#include "../GLU_glucoo.h"

#include "BLK_graphic.h"

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH
extern BLK_TYPE(Canvas) info_MainScreen; //...//
#define canvas info_MainScreen


#define STATIC static

STATIC void glu_draw_done( int xs, int ys, int xe, int ye){
    if(glu_dev_is_auto_refreash()){
        glu_dev_refreash_partial_screen(xs, ys, xe, ye);
    }else{
        glu_dev_add_refreash_area(xs, ys, xe, ye);
    }
}


void glu_draw_rectangle( int xs, int ys, int xe, int ye){
    BLK_FUNC( Graph, rect_raw )( xs, ys, xe, ye, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void glu_draw_rectangle_edged( int xs, int ys, int xe, int ye){
    BLK_FUNC( Graph, rect_edged )( xs, ys, xe, ye, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void glu_draw_rectangle_filled( int xs, int ys, int xe, int ye){
    BLK_FUNC( Graph, rect_fill )( xs, ys, xe, ye, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void glu_draw_rectangle_rounded( int xs, int ys, int xe, int ye){
    BLK_FUNC( Graph, rect_round_fill )( xs, ys, xe, ye, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}


void GLU_FUNC( GUI, circle_raw       )   ( int x , int y , int d ){
    int xs = RH_LIMIT( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_raw )( x, y, d, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_edged     )   ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_edged )( x, y, d, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_fill      )   ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_fill )( x, y, d, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt1_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt1_fill )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt2_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt2_fill )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt3_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt3_fill )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt4_fill )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt4_fill )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, circle_qrt1_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt1_raw )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}
void GLU_FUNC( GUI, circle_qrt2_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt2_raw )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}
void GLU_FUNC( GUI, circle_qrt3_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt3_raw )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}
void GLU_FUNC( GUI, circle_qrt4_raw  )   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = RH_LIMIT( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = RH_LIMIT( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = RH_LIMIT( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = RH_LIMIT( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt4_raw )( x, y, r, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, capsule_raw      )   ( int xs, int ys, int xe, int ye ){
    BLK_FUNC( Graph, capsule_raw )( xs, ys, xe, ye, &info_MainScreen, NULL );
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, line_raw         )   ( int x1, int y1, int x2, int y2 ){
    BLK_FUNC( Graph, line_raw )( x1,y1,x2,y2, &canvas, NULL );
    const int xs = RH_MIN(x1,x2);
    const int ys = RH_MIN(y1,y2);
    const int xe = RH_MAX(x1,x2);
    const int ye = RH_MAX(y1,y2);
    glu_draw_done(xs, ys, xe, ye);
}

void GLU_FUNC( GUI, quad_raw         )   ( int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4 ){
    
    int xs = RH_LIMIT( RH_MIN(x1, RH_MIN(x2, RH_MIN(x3, x4))), 0, GUI_X_WIDTH );
    int xe = RH_LIMIT( RH_MAX(x1, RH_MAX(x2, RH_MAX(x3, x4))), 0, GUI_X_WIDTH );
    int ys = RH_LIMIT( RH_MIN(y1, RH_MIN(y2, RH_MIN(y3, y4))), 0, GUI_Y_WIDTH );
    int ye = RH_LIMIT( RH_MAX(y1, RH_MAX(y2, RH_MAX(y3, y4))), 0, GUI_Y_WIDTH );
    
    BLK_FUNC( Graph, quad_raw )( x1, y1, x2, y2, x3, y3, x4, y4, &canvas, NULL );
    glu_draw_done(xs, ys, xe, ye);
}


void GLU_FUNC( GUI, screen_fill      )   ( gluColor_t M_COLOR_xxxx ){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )

    GLU_TYPE(Pixel) color = COLOR_1BIT(M_COLOR_xxxx);
    if( color == 0x00 ){
        memset( canvas.ptr, 0x00, (RH_CFG_SCREEN_HEIGHT>>3)*RH_CFG_SCREEN_WIDTH );
    }else{
        memset( canvas.ptr, 0xff, (RH_CFG_SCREEN_HEIGHT>>3)*RH_CFG_SCREEN_WIDTH );
    }

#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )

    GLU_TYPE(Pixel) color = COLOR_16BIT(M_COLOR_xxxx);
    if( sizeof(uint16_t)==sizeof(wchar_t) ){
        wmemset( (wchar_t*)canvas.ptr, color, RH_CFG_SCREEN_HEIGHT*RH_CFG_SCREEN_WIDTH );
    }else{
        uint16_t *iter = (uint16_t*)canvas.ptr;
        for( size_t i=0; i<RH_CFG_SCREEN_HEIGHT*RH_CFG_SCREEN_WIDTH; i++, iter++ ){
             *iter = color;
        }
    }

#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )

    GLU_TYPE(Pixel) color = COLOR_24BIT(M_COLOR_xxxx);
    if( sizeof(uint32_t)==sizeof(wchar_t) ){
        wmemset( (wchar_t*)canvas.ptr, color, RH_CFG_SCREEN_HEIGHT*RH_CFG_SCREEN_WIDTH );
    }else{
        uint32_t *iter = (uint32_t*)canvas.ptr;
        for( size_t i=0; i<RH_CFG_SCREEN_HEIGHT*RH_CFG_SCREEN_WIDTH; i++, iter++ ){
             *iter = color;
        }
    }

#endif

    glu_dev_is_auto_refreash() ? \
        glu_dev_refreash_full_screen() : \
        glu_dev_add_refreash_area(0,0,RH_CFG_SCREEN_WIDTH-1,RH_CFG_SCREEN_HEIGHT-1);

}




