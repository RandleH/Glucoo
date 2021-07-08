//
//  main.c
//  Xcode_11
//
//  Created by Randle Helmslay on 2021/4/18.
//  Copyright © 2021 Randle Helmslay. All rights reserved.
//

#include <stdio.h>
#include "GLU_glucoo.h"


static void line( int x1, int y1, int x2, int y2, void (*func)(int x, int y) ){
    int dx = __abs( x2-x1 );
    int dy = __abs( y2-y1 );
    
    int type = (int)( ((y2-y1<0)<<2) | ( (x2-x1<0)<<1) | (dy > dx));
    
    /* About this <type> : 通过平移, 将(x1,y1)移到原点, 此时(x2,y2)的位置决定type.
    
                      Y
          *           |           *
            *  type=3 | type=1  *
              *       |       *
                *     |     *
        type=2    *   |   *    type=0
                    * | *
    ------------------+------------------ X
                    * | *
        type=6    *   |   *    type=4
                *     |     *
              *       |       *
            *  type=7 | type=5  *
          *           |           *
     
     测试用例:
         type 0:   30,  30 ,    150,  90
         type 1: -150,-150 ,   -134,  69
         type 2:  -50,  10 ,   -100,  20
         type 3:   30,  30 ,     10, 100
         type 4:   50, -20 ,    150, -50
         type 5:   20, -40 ,     60,-100
         type 6:  150,  90 ,     30,  30
         type 7:  -20, -40 ,    -40,-120
         
    */
    
    switch(type){
        case 0:
            break;
        case 2: x2 = -x2;
                x1 = -x1;
            break;
        case 1: __swap(x2, y2);
                __swap(x1, y1);
            break;
        case 6: y2 = -y2;
                y1 = -y1;
                x2 = -x2;
                x1 = -x1;
            break;
        case 3: x2 = -x2;
                x1 = -x1;
                __swap(x2, y2);
                __swap(x1, y1);
            break;
        case 7: __swap(x2,y2);
                __swap(x1,y1);
                x2 = -x2; x1 = -x1;
                y2 = -y2; y1 = -y1;
            break;
        case 5: y2 = -y2;
                y1 = -y1;
                __swap(x2,y2);
                __swap(x1,y1);
            break;
        case 4: y2 = -y2;
                y1 = -y1;
            break;
    }
    
# if 1
    printf("type=%d\n",type);
    { // 检查是否成功转换, 此段可注释
        int dx = __abs( x2-x1 );
        int dy = __abs( y2-y1 );
        int type1 = (int)( ((y2-y1<=0)<<2) | ( (x2-x1<=0)<<1) | (dy > dx));
        assert( type1 == 0 );
    }
#endif

    dx = x2-x1 ;
    dy = y2-y1 ;
    
    int d  = dy*2 -dx;
    int x = x1, y = y1;
    int res_x, res_y;
    while( x <= x2 ){
        
        res_x = x; res_y = y;
            switch(type){
                case 0: break;
                case 2: res_x = -res_x;
                    break;
                case 1: __swap(res_x, res_y);
                    break;
                case 6: res_y = -res_y;
                        res_x = -res_x;
                    break;
                case 3: __swap(res_x,res_y);
                        res_x = -res_x;
                    break;
                case 7: __swap(res_x,res_y);
                        res_x = -res_x;
                        res_y = -res_y;
                    break;
                case 5: res_y = -res_y;
                        __swap(res_x,res_y);
                    break;
                case 4: res_y = -res_y;
                    break;
            }
        
            (*func)( res_x, res_y );
        
        if( d < 0 || y>=y2 ){
            d += 2*dy;
        }else{
            d += (dy-dx)*2;
            y++;
        }
        x++;
    }
    
}

void a(int x, int y){
    printf("%d,%d\n",x,y);
}

int __Square_Triangle(int x1,int y1,int x2,int y2,int x3,int y3);
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    GLU_FUNC(GUI,init)();
    
    GLU_FUNC(Font,set_font)( kGLU_Font_NewYork_Italic );
    GLU_FUNC(Font,set_size )(23);


    printf("%d\n", __Point_toTriangle( 900,740,  1363,909,  1327,987, 995,805 ) );

#if 1
    GLU_SRCT(Text) text = {
        .align = kGLU_Align_Middle ,
        .size  = 200,
        .str   = "Glucoo" ,
        .color = M_COLOR_RED,
        .font  = kGLU_Font_SignPrinter
    };

    BLK_SRCT(Img888)* IMG = BLK_Img888_create(1800, 1480);
    
    BLK_TYPE(Pixel888) colors[5] = {
        MAKE_COLOR(255,105,180) ,\
        MAKE_COLOR(135,206,235) ,\
        MAKE_COLOR( 64,224,208) ,\
        MAKE_COLOR(173,255, 47) ,\
        MAKE_COLOR(250,250,210) ,\
    };
    
    BLK_FUNC( Img888, draw_img_ )( IMG, colors, 5 );
    
    BLK_FUNC(Img888, out_bmp)("/Users/randle_h/Desktop/screen.bmp", IMG);

#endif
    
//    line(  -20, -40 ,    -40,-120,a);
    
    
    return 0;
}



