
#include "../GLU_glucoo.h"

#include "BLK_graphic.h"

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH
extern __GraphInfo_t info_MainScreen; //...//

#define canvas info_MainScreen

void GUI_rect_raw           ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_raw )( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_rect_edged         ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_edged )( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_rect_fill          ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_fill )( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_rect_round         ( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    BLK_FUNC( Graph, rect_round )( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_raw         ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_raw )( x, y, d, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_edged       ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_edged )( x, y, d, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_fill        ( int x , int y , int d ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_fill )( x, y, d, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt1_fill   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt1_fill )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt2_fill   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt2_fill )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt3_fill   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt3_fill )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt4_fill   ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt4_fill )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt1_raw    ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt1_raw )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}
void GUI_circle_qrt2_raw    ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt2_raw )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}
void GUI_circle_qrt3_raw    ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt3_raw )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}
void GUI_circle_qrt4_raw    ( int x , int y , int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+r+1), 0, GUI_Y_WIDTH-1 );
    BLK_FUNC( Graph, circle_qrt4_raw )( x, y, r, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_sausage_raw        ( int xs, int ys, int xe, int ye ){
    BLK_FUNC( Graph, sausage_raw )( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_line_raw           ( int x1, int y1, int x2, int y2 ){
    BLK_FUNC( Graph, line_raw )( x1,y1,x2,y2, &canvas, kApplyPixel_fill );
    GUI_is_AutoDisplay() ? GUI_RefreashScreenArea(__min(x1, x2), __min(y1, y2), __max(x1, x2), __max(y1, y2)) : \
                           GUI_AddScreenArea     (__min(x1, x2), __min(y1, y2), __max(x1, x2), __max(y1, y2));
}









