
#include "GLU_glucoo.h"
#include "GLU_area.h"

#include "BLK_graphic.h"

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH

extern BLK_TYPE(Canvas) info_MainScreen; //...//
extern void GLU_FUNC( GUI, refreashScreenArea    )   ( var xs,var ys,var xe,var ye );
extern void GLU_FUNC( GUI, addScreenArea         )   ( var xs,var ys,var xe,var ye );
extern void GLU_FUNC( GUI, EX_refreashScreenArea )   ( const __Area_t* area );
extern void GLU_FUNC( GUI, EX_addScreenArea      )   ( const __Area_t* area );


static void __gui_remove_object_text      ( const GLU_SRCT(Object)* config ){
    struct{
        __Area_t area;
        bool     showFrame;
    }*pHistory = (void*)config->history;
    
#ifdef RH_DEBUG
    RH_ASSERT( config->widget == kGUI_ObjStyle_text || \
               config->widget == kGUI_ObjStyle_num  || \
               config->widget == kGUI_ObjStyle_fnum  );
#endif
    
    BLK_FUNC( Graph, backupCache )();
    
    if( !pHistory ){
        BLK_FUNC( Graph, set_penColor )( config->bk_color );
        BLK_FUNC( Graph, rect_fill    )( (int)( config->area.xs+1                   ),\
                                         (int)( config->area.ys+1                   ),\
                                         (int)( config->area.xs+config->area.w -1-1 ),\
                                         (int)( config->area.ys+config->area.h -1-1 ),\
                                         &info_MainScreen, NULL);
        if( config->showFrame ){
            BLK_FUNC( Graph, set_penColor )( config->bk_color );
            BLK_FUNC( Graph, rect_raw     )( (int)( config->area.xs                   ),\
                                             (int)( config->area.ys                   ),\
                                             (int)( config->area.xs+config->area.w -1 ),\
                                             (int)( config->area.ys+config->area.h-1  ),\
                                             &info_MainScreen, NULL);
        }
    }else{
    #ifdef RH_DEBUG
        RH_ASSERT( pHistory->area.xs >= config->area.xs );
        RH_ASSERT( pHistory->area.ys >= config->area.ys );
        RH_ASSERT( pHistory->area.xs+pHistory->area.w <= config->area.xs+config->area.w  );
        RH_ASSERT( pHistory->area.ys+pHistory->area.h <= config->area.ys+config->area.h );
    #endif
        BLK_FUNC( Graph, set_penColor )( config->bk_color );
        BLK_FUNC( Graph, rect_fill    )( (int)( pHistory->area.xs                     ),\
                                         (int)( pHistory->area.ys                     ),\
                                         (int)( pHistory->area.xs+pHistory->area.w -1 ),\
                                         (int)( pHistory->area.ys+pHistory->area.h -1 ),\
                                         &info_MainScreen, NULL);
        if( pHistory->showFrame && !config->showFrame ){
            BLK_FUNC( Graph, set_penColor )( config->bk_color );
            BLK_FUNC( Graph, rect_raw     )( (int)( config->area.xs                   ),\
                                             (int)( config->area.ys                   ),\
                                             (int)( config->area.xs+config->area.w -1 ),\
                                             (int)( config->area.ys+config->area.h -1 ),\
                                             &info_MainScreen, NULL);
        }
    }
    
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_insert_object_text      ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->text.font < kGLU_NUM_FontStyle );
    RH_ASSERT( config->text.str );
    RH_ASSERT( config->widget == kGUI_ObjStyle_text );
#endif
    
    __gui_remove_object_text(config);

    struct{
        __Area_t area;
        bool     showFrame;
    }*pHistory = (void*)config->history;
    
    if( !pHistory ){
        pHistory = RH_MALLOC(sizeof(*pHistory));
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, pHistory);
    }
    
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font , backupCache )();
    GLU_FUNC( Font , set_font    )( config->text.font     );
    GLU_FUNC( Font , set_size    )( config->text.size);
    int cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.w, config->text.str );

    char* p = NULL;
    if(cnt>0){
        p = alloca( cnt+sizeof('\0') );
        strncpy(p, config->text.str, cnt);
        p[cnt] = '\0';
        
        // 输出字符串灰度字体图像
        GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
    #ifdef RH_DEBUG
        RH_ASSERT( pF );
        RH_ASSERT( pF->img_buf );
        RH_ASSERT( pF->img_w < config->area.w );
    #endif
        /* 计算画图区域的左上角坐标, 即开始坐标 , 并记录到history, 方便下次清除区域 */
        var x_fs = 0;
        var y_fs = pHistory->area.ys = (var)RH_LIMIT( config->area.ys +((config->area.h - config->text.size)>>1) , 0, GUI_Y_WIDTH-1 );
        
        switch ( config->text.align ) {
            case kGLU_Align_Left:
                x_fs = pHistory->area.xs = (var)RH_LIMIT( config->area.xs +(((int)(config->area.h - config->text.size))>>1) , 0, GUI_X_WIDTH-1 );
                break;
            case kGLU_Align_Middle:
                x_fs = pHistory->area.xs = (var)RH_LIMIT( config->area.xs +(((int)(config->area.w - pF->img_w))>>1)         , 0, GUI_X_WIDTH-1 );
                break;
            default:
                RH_ASSERT(0);
        }
        
        // 引用灰度字体图像(类型信息复制转换)
        BLK_SRCT(ImgGry) img_font = {
            .h   = pF->img_h,
            .w   = pF->img_w,
            .ptr = (BLK_UION(PixelGry)*)pF->img_buf
        };
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        
        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        
        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        
        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
        
    #else
         
    #endif
        
        /* 记录区域长宽到history, 方便下次清除区域 */
        pHistory->area.h = RH_MIN( pF->img_h, config->area.h );
        pHistory->area.w = pF->img_w;
    }
    
    

    if( config->showFrame ){
        BLK_FUNC( Graph, set_penColor )( config->obj_color );
        BLK_FUNC( Graph, rect_raw     )( (int)( config->area.xs                  ),\
                                         (int)( config->area.ys                  ),\
                                         (int)( config->area.xs+config->area.w-1 ),\
                                         (int)( config->area.ys+config->area.h-1 ),\
                                         &info_MainScreen, NULL);

    }
    pHistory->showFrame = config->showFrame;
    
    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( Font, restoreCache )();
    
}
static void __gui_adjust_object_text      ( const GLU_SRCT(Object)* config ){
    struct __GUI_ObjDataScr_text* p = config->dataScr;
//    config->text = p->text;
    __SET_STRUCT_MB(GLU_SRCT(Object), char*, config, text, p->text);
    __gui_insert_object_text( config );
}

static void __gui_remove_object_num       ( const GLU_SRCT(Object)* config ){
    __gui_remove_object_text(config);
}
static void __gui_insert_object_num       ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->text.font < kGLU_NUM_FontStyle );
    RH_ASSERT( config->widget == kGUI_ObjStyle_num );
#endif
    __gui_remove_object_num(config);
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
    
    struct{
        __Area_t area;
        bool     showFrame;
    }*pHistory = (void*)config->history;
    
    if( !pHistory ){
        pHistory = RH_MALLOC(sizeof(*pHistory));
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, pHistory);
    }
    
    // 绘制数字
    char __str[GUI_X_WIDTH>>2] = {0};
    GLU_FUNC( Font, set_size )(config->text.size);
    
    // 计算数值共占有多少十进制位
    int wordCnt = snprintf(__str, sizeof(__str), "%d",((struct __GUI_ObjDataScr_num*)config->dataScr)->value);
    
    // 计算在用户设定的宽度(width)以及字体大小内, 最多可容纳多少个字符
    int maxWordCnt = GLU_FUNC( Font, get_str_WordCnt )(config->area.w, __str);
    // 在临界位置截断字符串
    __str[ maxWordCnt ] = '\0';
    
    // 计算该数在这样宽度范围内是否可以被正确显示: [例] 假设最多显示3个字符  123 | 90 | 1 均可 而 1234 | 4253 不可能被显示正确
    bool isEnough = wordCnt <= maxWordCnt;
    
    // 不可能被显示正确的数字, 则显示全“#”, 以表示无法显示
    if( !isEnough){
        memset(__str, '#', maxWordCnt);
    }
 
    
    
    if(__str[0]!='\0'){

        GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(__str);
        
        /* 计算画图区域的左上角坐标, 即开始坐标 , 并记录到history, 方便下次清除区域 */
        var x_fs = 0;
        var y_fs = pHistory->area.ys = (var)RH_LIMIT( config->area.ys +((config->area.h - config->text.size)>>1) , 0, GUI_Y_WIDTH-1 );
        switch ( config->text.align ) {
            case kGLU_Align_Left:
                x_fs = pHistory->area.xs = (var)RH_LIMIT( config->area.xs +((config->area.h - config->text.size)>>1) , 0, GUI_X_WIDTH-1 );
                break;
            case kGLU_Align_Middle:
                x_fs = pHistory->area.xs = (var)RH_LIMIT( config->area.xs +((config->area.h - pF->img_w)>>1)         , 0, GUI_X_WIDTH-1 );
                break;
            default:
                RH_ASSERT(0);
        }
        
        // 引用灰度字体图像(类型信息复制转换)
        BLK_SRCT(ImgGry) img_font = {
            .h   = pF->img_h,
            .w   = pF->img_w,
            .ptr = (BLK_UION(PixelGry)*)pF->img_buf
        };
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        
        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        
        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        
        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
        
    #else
         
    #endif
    
        /* 记录区域长宽到history, 方便下次清除区域 */
        pHistory->area.h = RH_MIN( pF->img_h, config->area.h );
        pHistory->area.w  = pF->img_w;
    }

    if( config->showFrame ){
        BLK_FUNC( Graph, set_penColor )( M_COLOR_WHITE );
        BLK_FUNC( Graph, rect_raw     )( (int)( config->area.xs                  ),\
                                         (int)( config->area.ys                  ),\
                                         (int)( config->area.xs+config->area.w-1 ),\
                                         (int)( config->area.ys+config->area.h-1 ),\
                                         &info_MainScreen, NULL);

    }
    pHistory->showFrame = config->showFrame;

    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_adjust_object_num       ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_num( config );
}

static void __gui_remove_object_fnum      ( const GLU_SRCT(Object)* config ){
    __gui_remove_object_text(config);
}
static void __gui_insert_object_fnum      ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->text.font < kGLU_NUM_FontStyle );
    RH_ASSERT( config->widget == kGUI_ObjStyle_fnum );
#endif
    __gui_remove_object_fnum(config);
    
    // 记录历史改动区域
    struct{
        __Area_t area;
        bool     showFrame;
    }*pHistory = (void*)config->history;
    
    if( !pHistory ){
        pHistory = RH_MALLOC(sizeof(*pHistory));
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, pHistory);
    }
    
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
    
    char __str[GUI_X_WIDTH>>2] = {'\0'};
    GLU_FUNC( Font, set_size )(config->text.size);
    snprintf(__str, sizeof(__str), "%.3f",((struct __GUI_ObjDataScr_fnum*)config->dataScr)->value);
    
    // 计算在用户设定的宽度(width)以及字体大小内, 最多可容纳多少个字符
    int maxWordCnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.w, __str );
    // 在临界位置截断字符串
    __str[ maxWordCnt ] = '\0';
    
    // 计算该浮点数在这样宽度范围内是否可以被正确显示: [例] 假设最多显示3个字符  12.34 | 90.001 | 123.123 均可 而 1234.567 | 4253.000 不可能被显示正确
    
    bool isEnough = false;
    for ( int i=0; i<strlen(__str)&&i<maxWordCnt; i++) {
        if( __str[i] == '.' ){
            if( __str[i+1] == '\0' ) // 小数点后字符串结束
                __str[i] = '\0'; // 则小数点也无需显示
            isEnough = true;
            break;
        }
    }
    // 不可能被显示正确的数字, 则显示全“#”, 以表示无法显示
    if( !isEnough){
        memset(__str, '#', maxWordCnt);
    }
    
    GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(__str);
    /* 计算画图区域的左上角坐标, 即开始坐标 , 并记录到history, 方便下次清除区域 */
    var x_fs = 0;
    var y_fs = pHistory->area.ys = (var)RH_LIMIT( config->area.ys +((config->area.h-config->text.size) >>1) , 0, GUI_Y_WIDTH-1 );
    switch ( config->text.align ) {
        case kGLU_Align_Left:
            x_fs = pHistory->area.xs = (var)RH_LIMIT( config->area.xs + ((config->area.h-config->text.size) >>1) , 0, GUI_X_WIDTH-1 );
            break;
        case kGLU_Align_Middle:
            x_fs = pHistory->area.xs = (var)RH_LIMIT( config->area.xs + ((config->area.w-pF->img_w) >>1)         , 0, GUI_X_WIDTH-1 );
            break;
        default:
            RH_ASSERT(0);
    }
    
    // 引用灰度字体图像(类型信息复制转换)
    BLK_SRCT(ImgGry) img_font = {
        .h   = pF->img_h,
        .w   = pF->img_w,
        .ptr = (BLK_UION(PixelGry)*)pF->img_buf
    };
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    
    BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
    
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    
    BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
    
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    
    BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
    
#else
     
#endif
    
    /* 记录区域长宽到history, 方便下次清除区域 */
    pHistory->area.h = RH_MIN( pF->img_h, config->area.h );
    pHistory->area.w = pF->img_w;
    
    
    if( config->showFrame ){
        BLK_FUNC( Graph, set_penColor )( M_COLOR_WHITE );
        BLK_FUNC( Graph, rect_raw     )( (int)( config->area.xs                  ),\
                                         (int)( config->area.ys                  ),\
                                         (int)( config->area.xs+config->area.w-1 ),\
                                         (int)( config->area.ys+config->area.h-1 ),\
                                         &info_MainScreen, NULL);

    }
    pHistory->showFrame = config->showFrame;

    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_adjust_object_fnum      ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_fnum( config );
}

static void __gui_remove_object_switch    ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->widget == kGUI_ObjStyle_switch );
#endif
    
    // 加载历史改动区域
    struct{
        bool     cmd;
        bool     showFrame;
    }*pHistory = (void*)config->history;
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
    
    bool needRemove = !pHistory;
    if( pHistory ){
        needRemove |= (pHistory->cmd ^ ((__GUI_ObjDataScr_switch*)(config->dataScr))->cmd );
        needRemove |= (pHistory->showFrame)^(config->showFrame);
    }
    
    if( needRemove ){
        BLK_FUNC( Graph, set_penColor )(config->bk_color);
        BLK_FUNC( Graph, capsule_fill )( (int)( config->area.xs+2                    ),\
                                         (int)( config->area.ys+2                    ),\
                                         (int)( config->area.xs+2+config->area.w-4-1 ),\
                                         (int)( config->area.ys+2+config->area.h-4-1 ),\
                                         &info_MainScreen, NULL);
        BLK_FUNC( Graph, rect_raw     )( (int)( config->area.xs                      ),\
                                         (int)( config->area.ys                      ),\
                                         (int)( config->area.xs+config->area.w-1     ),\
                                         (int)( config->area.ys+config->area.h-1     ),\
                                         &info_MainScreen, NULL);
    }
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_insert_object_switch    ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->widget == kGUI_ObjStyle_switch );
#endif
    // 记录历史改动区域
    struct{
        bool     cmd;
        bool     showFrame;
    }*pHistory = (void*)config->history;
    
    if( !pHistory ){
        pHistory = RH_MALLOC(sizeof(*pHistory));
    }
#ifdef RH_DEBUG
    RH_ASSERT( pHistory );
#endif
    
    __gui_remove_object_switch(config);
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel) color_switch_on  = {.data = (config->bk_color==0x00)?0xff:0x00};
//    GLU_UION(Pixel) color_switch_off = {.data = (config->bk_color==0x00)?0x00:0xff};
    GLU_UION(Pixel) color_switch     = {.data = 0x00};
    //...//
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel) color_switch_on  = {.data = config->obj_color };
    GLU_UION(Pixel) color_switch_off = {.data = COLOR_16BIT(M_COLOR_COAL      ) };
    GLU_UION(Pixel) color_switch     = {.data = COLOR_16BIT(M_COLOR_WHITESMOKE) };
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel) color_switch_on  = {.data = config->obj_color };
    GLU_UION(Pixel) color_switch_off = {.data = M_COLOR_COAL      };
    GLU_UION(Pixel) color_switch     = {.data = M_COLOR_WHITESMOKE};
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    BLK_FUNC( Graph, set_penColor )( color_switch_on.data );
    
    if( ((struct __GUI_ObjDataScr_switch*)config->dataScr)->cmd ){
        BLK_FUNC( Graph, set_penColor )( color_switch_on.data );
        BLK_FUNC( Graph, capsule_fill )( (int)( config->area.xs+2                    ),\
                                         (int)( config->area.ys+2                    ),\
                                         (int)( config->area.xs+2+config->area.w-4-1 ),\
                                         (int)( config->area.ys+2+config->area.h-4-1 ),\
                                         &info_MainScreen, NULL);
        
        // 绘制滑杆柄
        BLK_FUNC( Graph, set_penColor )( color_switch.data );
        BLK_FUNC( Graph, circle_fill  )( (int)( config->area.xs+2+(config->area.w-4)-((config->area.h-4)>>1)-1  ),\
                                         (int)( config->area.ys+2+((config->area.h-4)>>1)-(config->area.h%2==0) ),\
                                         (int)( config->area.h-4                                                ),\
                                         &info_MainScreen, NULL);
        
        BLK_FUNC( Graph, set_penColor )( color_switch_on.data );
        BLK_FUNC( Graph, circle_raw   )( (int)( config->area.xs+2+(config->area.w-4)-((config->area.h-4)>>1)-1  ),\
                                         (int)( config->area.ys+2+((config->area.h-4)>>1)-(config->area.h%2==0) ),\
                                         (int)( config->area.h                                                  ),\
                                         &info_MainScreen, NULL);

        pHistory->cmd = true;
    }else{
        // 二值颜色与彩色画法稍有不同
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        BLK_FUNC( Graph, set_penColor )( color_switch_on.data );
        BLK_FUNC( Graph, capsule_raw  )( (var)( config->area.xs+2                    ),\
                                         (var)( config->area.ys+2                    ),\
                                         (var)( config->area.xs+2+config->area.w-4-1 ),\
                                         (var)( config->area.ys+2+config->area.h-4-1 ),\
                                         &info_MainScreen, NULL);
        
        BLK_FUNC( Graph, circle_raw   )( (var)( config->area.xs+2+((config->area.h-4)>>1)                       ),\
                                         (var)( config->area.ys+2+((config->area.h-4)>>1)-(config->area.h%2==0) ),\
                                         (var)( config->area.h-4                                                ),\
                                         &info_MainScreen, NULL);
#else
        BLK_FUNC( Graph, set_penColor )( color_switch_off.data );
        BLK_FUNC( Graph, capsule_fill )( (var)( config->area.xs+2                    ),\
                                         (var)( config->area.ys+2                    ),\
                                         (var)( config->area.xs+2+config->area.w-4-1 ),\
                                         (var)( config->area.ys+2+config->area.h-4-1 ),\
                                         &info_MainScreen, NULL);
        
        BLK_FUNC( Graph, set_penColor )( color_switch.data );
        BLK_FUNC( Graph, circle_fill  )( (var)( config->area.xs+2+((config->area.h-4)>>1)                       ),\
                                         (var)( config->area.ys+2+((config->area.h-4)>>1)-(config->area.h%2==0) ),\
                                         (var)( config->area.h-4                                                ),\
                                         &info_MainScreen, NULL);
        
        BLK_FUNC( Graph, set_penColor )( color_switch_off.data );
        BLK_FUNC( Graph, circle_raw   )( (var)( config->area.xs+2+((config->area.h-4)>>1)                       ),\
                                         (var)( config->area.ys+2+((config->area.h-4)>>1)-(config->area.h%2==0) ),\
                                         (var)( config->area.h-4                                                ),\
                                         &info_MainScreen, NULL);
        
#endif
        pHistory->cmd = false;
    }
    
    __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, pHistory);
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_adjust_object_switch    ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_switch(config);
}

static void __gui_remove_object_bar_h     ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->widget == kGUI_ObjStyle_barH );
#endif
    
    // 记录历史改动区域
    struct{
        int     bar_pos; /* 上一次进度条所在的像素点位置(横坐标) */
    }*pHistory = (void*)config->history;
    
    int32_t val = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->value;
    int32_t min = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->min;
    int32_t max = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->max;
    val = RH_LIMIT(val, min, max);
    
    var bar_pos = config->area.xs + val*config->area.w/(max-min);
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel) color_bar_off = {.data = (config->bk_color==0x00)?0x00:0xff};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel) color_bar_off = {.data = config->bk_color};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel) color_bar_off = {.data = config->bk_color};
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    if( !pHistory ){
        BLK_FUNC( Graph, set_penColor )( color_bar_off.data );
        BLK_FUNC( Graph, rect_fill    )( (int)(config->area.xs+1                   ),\
                                         (int)(config->area.ys+1                   ),\
                                         (int)(config->area.xs+config->area.w -1-1 ),\
                                         (int)(config->area.ys+config->area.h -1-1 ),\
                                         &info_MainScreen, NULL);
    }else if(pHistory->bar_pos > bar_pos){
        BLK_FUNC( Graph, set_penColor )( color_bar_off.data );
        BLK_FUNC( Graph, rect_fill    )( (int)( bar_pos                            ),\
                                         (int)( config->area.ys+1                  ),\
                                         (int)( pHistory->bar_pos                  ),\
                                         (int)( config->area.ys+config->area.h-1-1 ),\
                                         &info_MainScreen, NULL);
    }
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_insert_object_bar_h     ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->widget == kGUI_ObjStyle_barH );
#endif
    // 记录历史改动区域
    struct{
        int     bar_pos; /* 上一次进度条所在的像素点位置(横坐标) */
        
    }*pHistory = (void*)config->history;

    __gui_remove_object_bar_h(config);
    
    if( !pHistory ){
        pHistory = RH_CALLOC(sizeof(*pHistory),1);
    #ifdef RH_DEBUG
        RH_ASSERT( pHistory );
    #endif
        pHistory->bar_pos = config->area.xs;
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, pHistory );
    }

    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel) color_bar_on  = {.data = (config->bk_color==0x00)?0xff:0x00};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel) color_bar_on  = {.data = config->obj_color};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel) color_bar_on  = {.data = config->obj_color};
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    int32_t val = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->value;
    int32_t min = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->min;
    int32_t max = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->max;
    val = RH_LIMIT(val, min, max);
    
    var bar_pos = config->area.xs + val*config->area.w/(max-min);
    
    BLK_FUNC( Graph, set_penColor )( color_bar_on.data );
    BLK_FUNC( Graph, EX_rect_raw  )( &config->area, &info_MainScreen, NULL );
    
    if( pHistory->bar_pos < bar_pos ){
        BLK_FUNC( Graph, set_penColor )( color_bar_on.data );
        BLK_FUNC( Graph, rect_fill    )( (int)( pHistory->bar_pos                  ),\
                                         (int)( config->area.ys+1                  ),\
                                         (int)( bar_pos                            ),\
                                         (int)( config->area.ys+config->area.h-1-1 ),\
                                         &info_MainScreen, NULL);
    }

    pHistory->bar_pos = bar_pos;
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_adjust_object_bar_h     ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_bar_h(config);
}

static void __gui_remove_object_bar_v     ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->widget == kGUI_ObjStyle_barV );
#endif
    // 记录历史改动区域
    struct{
        var     bar_pos; /* 上一次进度条所在的像素点位置(横坐标) */
    }*pHistory = (void*)config->history;
    
    int32_t min = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->min;
    int32_t max = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->max;
    int32_t val = RH_LIMIT(((struct __GUI_ObjDataScr_barH*)config->dataScr)->value, min, max);
    var bar_pos = config->area.ys + config->area.h-1 - val*config->area.h/(max-min);
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel) color_bar_off = {.data = (config->bk_color==0x00)?0x00:0xff};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel) color_bar_off = {.data = config->bk_color};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel) color_bar_off = {.data = config->bk_color};
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    if( !pHistory ){
        BLK_FUNC( Graph, set_penColor )( color_bar_off.data );
        BLK_FUNC( Graph, rect_fill    )( (int)( config->area.xs+1                  ),\
                                         (int)( config->area.ys+1                  ),\
                                         (int)( config->area.xs+config->area.w-1-1 ),\
                                         (int)( config->area.ys+config->area.h-1-1 ),\
                                         &info_MainScreen, NULL);
    }else if(pHistory->bar_pos < bar_pos){
        BLK_FUNC( Graph, set_penColor )( color_bar_off.data );
        BLK_FUNC( Graph, rect_fill    )( (int)( config->area.xs+1                  ),\
                                         (int)( pHistory->bar_pos                  ),\
                                         (int)( config->area.xs+config->area.w-1-1 ),\
                                         (int)( bar_pos                            ),\
                                         &info_MainScreen, NULL);
    }
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_insert_object_bar_v     ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->widget == kGUI_ObjStyle_barV );
#endif
    // 记录历史改动区域
    struct{
        var     bar_pos; /* 上一次进度条所在的像素点位置(横坐标) */
        
    }*pHistory = (void*)config->history;

    __gui_remove_object_bar_v(config);
    
    if( !pHistory ){
        pHistory = RH_CALLOC(sizeof(*pHistory),1);
    #ifdef RH_DEBUG
        RH_ASSERT( pHistory );
    #endif
        pHistory->bar_pos = config->area.ys+config->area.h-1;
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, pHistory );
    }
    
    int32_t val = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->value;
    int32_t min = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->min;
    int32_t max = ((struct __GUI_ObjDataScr_barH*)config->dataScr)->max;
    val = RH_LIMIT(val, min, max);
    
    var bar_pos = config->area.ys + config->area.h-1 - val*config->area.h/(max-min);
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel) color_bar_on  = {.data = (config->bk_color==0x00)?0xff:0x00};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel) color_bar_on  = {.data = config->obj_color};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel) color_bar_on  = {.data = config->obj_color};
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    BLK_FUNC( Graph, set_penColor )( color_bar_on.data );
    BLK_FUNC( Graph, EX_rect_raw  )( &config->area, &info_MainScreen, NULL );
    
    if( pHistory->bar_pos > bar_pos ){
        BLK_FUNC( Graph, set_penColor )( color_bar_on.data );
        BLK_FUNC( Graph, rect_fill )( (int)( config->area.xs+1                ),\
                                      (int)( bar_pos                          ),\
                                      (int)( config->area.xs+config->area.w-1 ),\
                                      (int)( pHistory->bar_pos                ),\
                                      &info_MainScreen, NULL);
    }

    pHistory->bar_pos = bar_pos;
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
    
}
static void __gui_adjust_object_bar_v     ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_bar_v(config);
}

static void __gui_remove_object_joystick  ( const GLU_SRCT(Object)* config ){
    struct{
        int      cord; // (x,y)象限信息
        __Area_t area;
    }*pHistory = (void*)config->history;
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
    BLK_FUNC( Graph, set_penColor )( config->bk_color );
    if( !pHistory ){
        BLK_FUNC( Graph, EX_rect_fill )( &config->area  , &info_MainScreen, NULL );
    }else{
        BLK_FUNC( Graph, EX_rect_fill )( &pHistory->area, &info_MainScreen, NULL );
    }
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_insert_object_joystick  ( const GLU_SRCT(Object)* config ){
    struct{
        int      cord; // (x,y)象限信息
        __Area_t area;
    }*pHistory = (void*)config->history;
    
    
    __gui_remove_object_joystick(config);
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
    
    BLK_FUNC( Graph, set_penColor )( config->obj_color );
    
    
    var D = RH_MIN( config->area.h , config->area.w );
    bool eps = ((D&0x01)==0);
    var X = config->area.xs + (D>>1) - eps;
    var Y = config->area.ys + (D>>1) - eps;
    
    
//    BLK_FUNC( Graph, circle_raw )( X, Y, D, &info_MainScreen, NULL );
     if(  !pHistory  ){
         BLK_FUNC( Graph, circle_raw )( X, Y, D, &info_MainScreen, NULL );
     }else{
         
         switch( pHistory->cord ){
             
             case 1:
                 BLK_FUNC( Graph, circle_qrt1_raw )( X    , Y+eps, (D>>1)+1, &info_MainScreen, NULL );
                 break;
             case 2:
                 BLK_FUNC( Graph, circle_qrt2_raw )( X+eps, Y+eps, (D>>1)+1, &info_MainScreen, NULL );
                 break;
             case 3:
                 BLK_FUNC( Graph, circle_qrt3_raw )( X+eps, Y    , (D>>1)+1, &info_MainScreen, NULL );
                 break;
             case 4:
                 BLK_FUNC( Graph, circle_qrt4_raw )( X    , Y    , (D>>1)+1, &info_MainScreen, NULL );
                 break;
             case 0:
             case 5:
             case 6:
                 BLK_FUNC( Graph, circle_raw      )( X    , Y    , D       , &info_MainScreen, NULL );
                 break;
         }
     }
    
    struct __GUI_ObjDataScr_joystick* pDataSrc = ((struct __GUI_ObjDataScr_joystick*)config->dataScr);
    
    int32_t val_x = RH_LIMIT( (int32_t)pDataSrc->value[0], (int32_t)pDataSrc->min[0], (int32_t)pDataSrc->max[0] );
    int32_t val_y = RH_LIMIT( (int32_t)pDataSrc->value[1], (int32_t)pDataSrc->min[1], (int32_t)pDataSrc->max[1] );
    
    
    int dis_cir_max = ((3*D)>>3); // 两圆心距最大值

    
    var px = (val_x - (int32_t)pDataSrc->min[0])*(dis_cir_max<<1)/((int32_t)pDataSrc->max[0]-(int32_t)pDataSrc->min[0]) - dis_cir_max;
    var py = (val_y - (int32_t)pDataSrc->min[1])*(dis_cir_max<<1)/((int32_t)pDataSrc->max[1]-(int32_t)pDataSrc->min[1]) - dis_cir_max;
    var pd = RH_LIMIT( (D>>3), 1, D );

    BLK_ENUM(PtPos) cord   = BLK_FUNC( Math, pt_cord2D )( px, py );// 记录游标圆心坐标的象限

    if( px*px +py*py >= dis_cir_max*dis_cir_max ){
        
        var pTmp_x = (var)lroundf(dis_cir_max*cosf(atan2f(py, px)));
        var pTmp_y = (var)lroundf(dis_cir_max*sinf(atan2f(py, px)));
        px = __abs(pTmp_x);
        py = __abs(pTmp_y);
        switch( cord ){
            case kBLK_PtPos_at_axisXp: // Axis +X
            case kBLK_PtPos_at_axisYp: // Axis +Y
            case kBLK_PtPos_at_cord1:  // Cord 1
                px = px;
                py = py;
                break;
            case kBLK_PtPos_at_cord2:  // Cord 2
                px = -px;
                break;
            case kBLK_PtPos_at_axisXm: // Axis -X
            case kBLK_PtPos_at_axisYm: // Axis -Y
            case kBLK_PtPos_at_cord3:  // Cord 3
                px = -px;
                py = -py;
                break;
            case kBLK_PtPos_at_cord4:  // Cord 4
                py = -py;
                break;
            default: // Impossible
                RH_ASSERT(0);
        }
    }
    BLK_FUNC( Graph, circle_fill )( X+px, Y-py, pd, &info_MainScreen, NULL);
    
    if( !pHistory ){
        pHistory = RH_MALLOC(sizeof(*pHistory));
    #ifdef RH_DEBUG
        RH_ASSERT( pHistory );
    #endif
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, pHistory);
    }
    pHistory->cord     = cord;
    pHistory->area.xs  = (X+px-(pd>>1)+eps);
    pHistory->area.ys  = (Y-py-(pd>>1)+eps);
    pHistory->area.w   = pd;
    pHistory->area.h   = pd;
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
    
}
static void __gui_adjust_object_joystick  ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_joystick(config);
}

static void __gui_remove_object_trunk     ( const GLU_SRCT(Object)* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->widget == kGUI_ObjStyle_trunk );
#endif
    // 记录历史改动区域
    struct{
        var     bar_s;   /* 进度条的起始位置 */
        var     bar_e;   /* 进度条的终末位置 */
        var     bar_pos; /* 上一次进度条所在的像素点位置(横坐标) */
        var     margin;  /* 留白 */
    }*cache = (void*)config->history;
    
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel) color  = {.data = (config->bk_color==0x00)?0x00:0xff};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel) color  = {.data = config->bk_color};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel) color  = {.data = config->bk_color};
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    BLK_FUNC( Graph, set_penColor )( color.data );
    
    if( !cache ){
        BLK_FUNC( Graph, rect_fill )( (int)( config->area.xs+1                  ),\
                                      (int)( config->area.ys+1                  ),\
                                      (int)( config->area.xs+config->area.w-1-1 ),\
                                      (int)( config->area.ys+config->area.h-1-1 ),\
                                      &info_MainScreen, NULL);
    }else{
        int32_t min = ((__GUI_ObjDataScr_trunk*)config->dataScr)->min;
        int32_t max = ((__GUI_ObjDataScr_trunk*)config->dataScr)->max;
        int32_t val = RH_LIMIT(((__GUI_ObjDataScr_trunk*)config->dataScr)->value, min, max);
        
        var bar_pos = cache->bar_e - val*(int)(cache->bar_e-cache->bar_s+1)/(max-min);
        if( cache->bar_pos - config->text.size < bar_pos ){
            BLK_FUNC( Graph, rect_fill )( (int)( config->area.xs+1                   ),\
                                          (int)( cache->bar_pos-config->text.size    ),\
                                          (int)( config->area.xs+config->area.w -1-1 ),\
                                          (int)( bar_pos                             ),\
                                          &info_MainScreen, NULL);
        }
        //...//
    }
    
    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_insert_object_trunk     ( const GLU_SRCT(Object)* config ){
    // 记录历史改动区域
    struct{
        var     bar_s;   /* 进度条的起始位置 */
        var     bar_e;   /* 进度条的终末位置 */
        var     bar_pos; /* 上一次进度条所在的像素点位置(横坐标) */
        var     margin;  /* 留白 */
    }*cache = (void*)config->history;
    
    __gui_remove_object_trunk(config);
    
    if( !cache ){
        cache = RH_CALLOC(sizeof(*cache),1);
    #ifdef RH_DEBUG
        RH_ASSERT( cache );
    #endif
        cache->margin = 2;
        cache->bar_s = config->area.ys + config->text.size + cache->margin;
        cache->bar_e = config->area.ys + config->area.h-1-1;
        cache->bar_pos = cache->bar_e;
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, cache );
    }
    
    int32_t min = ((__GUI_ObjDataScr_trunk*)config->dataScr)->min;
    int32_t max = ((__GUI_ObjDataScr_trunk*)config->dataScr)->max;
    int32_t val = RH_LIMIT(((__GUI_ObjDataScr_trunk*)config->dataScr)->value, min, max);
    int bar_pos = cache->bar_e - val*(int)(cache->bar_e-cache->bar_s+1)/(max-min);
    
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, backupCache )();
    
    // 确认画笔颜色
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    GLU_UION(Pixel) color  = {.data = (config->obj_color==0x00)?0x00:0xff};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    GLU_UION(Pixel) color  = {.data = config->obj_color};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    GLU_UION(Pixel) color  = {.data = config->obj_color};
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    
    // 当且仅当进度条所占区域大于原先所占区域(坐标值相反)
    if( cache->bar_pos >= bar_pos ){
        BLK_FUNC( Graph, set_penColor )( color.data );
        BLK_FUNC( Graph, rect_fill    )( (int)( config->area.xs+cache->margin                  ),\
                                         (int)( bar_pos                                        ),\
                                         (int)( config->area.xs+config->area.w-1-cache->margin ),\
                                         (int)( cache->bar_pos                                 ),\
                                         &info_MainScreen, NULL);
    }
    cache->bar_pos = bar_pos;
    // 绘制数字
    GLU_SRCT(FontImg)* pF = NULL;
    {
        char __str[GUI_X_WIDTH>>2] = {0};
        GLU_FUNC( Font, set_size )(config->text.size);
        snprintf(__str, sizeof(__str), "%d",val);
        __str[ GLU_FUNC( Font, get_str_WordCnt )(config->area.w, __str) ] = '\0';
        
    #ifdef RH_DEBUG
        RH_ASSERT( __str[0] != '\0' );
    #endif
        
        // 计算数值共占有多少十进制位
        int wordCnt = snprintf(__str, sizeof(__str), "%d",val);
        
        // 计算在用户设定的宽度(width)以及字体大小内, 最多可容纳多少个字符
        int maxWordCnt = GLU_FUNC( Font, get_str_WordCnt )(config->area.w, __str);
        // 在临界位置截断字符串
        __str[ maxWordCnt ] = '\0';
        
        // 计算该数在这样宽度范围内是否可以被正确显示: [例] 假设最多显示3个字符  123 | 90 | 1 均可 而 1234 | 4253 不可能被显示正确
        bool isEnough = wordCnt <= maxWordCnt;
        
        // 不可能被显示正确的数字, 则显示全“#”, 以表示无法显示
        if( !isEnough){
            memset(__str, '#', maxWordCnt);
        }
        pF = GLU_FUNC( Font, out_str_Img )(__str);
    }
#ifdef RH_DEBUG
    RH_ASSERT( pF );
#endif
    var x_fs = 0;
    var y_fs = bar_pos - config->text.size;
    switch ( config->text.align ) {
        case kGLU_Align_Left:
            x_fs = config->area.xs;
            break;
        case kGLU_Align_Middle:
            x_fs = RH_LIMIT( config->area.xs +((config->area.w - pF->img_w)>>1) , 0, GUI_X_WIDTH-1   );
            break;
        default:
            RH_ASSERT(0);
    }
    
    // 引用灰度字体图像(类型信息复制转换)
    BLK_SRCT(ImgGry) img_font = {
        .h   = pF->img_h,
        .w   = pF->img_w,
        .ptr = (BLK_UION(PixelGry)*)pF->img_buf
    };
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
    
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
    
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
    
#else
     
#endif

    GLU_FUNC( Font, restoreCache )();
    BLK_FUNC( Graph, restoreCache )();
    
}
static void __gui_adjust_object_trunk     ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_trunk(config);
}

static void __gui_remove_object_spinbox   ( const GLU_SRCT(Object)* config ){
    struct{
        int32_t    value;
        var        margin;
        bool       triUP;
        bool       triDN;
        var        lineUP;
        var        lineDN;
        var        textXS;
        var        textYS;
        __Area_t   num;
        bool       active;
    }*cache = (void*)config->history;
    
    __GUI_ObjDataScr_spinbox* dataScr = (__GUI_ObjDataScr_spinbox*)(config->dataScr);
    BLK_FUNC( Graph, backupCache )();
    
    // 清除数字
    if( dataScr->value != cache->value ){
        BLK_FUNC( Graph, set_penColor )( config->bk_color );
        BLK_FUNC( Graph, rect_fill    )( (int)( cache->num.xs                ),\
                                         (int)( cache->num.ys                ),\
                                         (int)( cache->num.xs+cache->num.w-1 ),\
                                         (int)( cache->num.ys+cache->num.h-1 ),\
                                         &info_MainScreen, NULL );
    }
    
    // 清除三角形
    {
        // 判断是否需要清除箭头
        if( dataScr->value >= dataScr->max || (cache->active&& !dataScr->active) ){
            // 去除下箭头
            var len = config->text.size;                              // 三角形(上) 底长度(pix)
            var xs  = (config->area.xs + cache->textXS - len)>>1;     // 三角形(上) 最左端坐标
            var ys  = cache->lineDN + cache->margin ;                 // 三角形(上下) 底起始位置
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            for( var y=ys; len>0&&y<config->area.ys+config->area.h; len-=2, y++, xs++ ){
                GLU_UION(Pixel)* pIter = &info_MainScreen.ptr[(y>>3)*info_MainScreen.w + xs];
                for( var x=0; x<len; x++,pIter++ ){
                    if( config->bk_color!=0 ){
                        pIter->data = __BIT_SET( pIter->data, y%8 );
                    }else{
                        pIter->data = __BIT_CLR( pIter->data, y%8 );
                    }
                }
            }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            for( var y=ys; len>0&&y<config->area.ys+config->area.h; len-=2, y++, xs++ ){
                GLU_UION( Pixel )* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( var x=0; x<len; x++,pIter++ ){
                    pIter->data = config->bk_color;
                }
            }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            for( var y=ys; len>0&&y<config->area.ys+config->area.h; len-=2, y++, xs++ ){
                GLU_UION( Pixel )* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( var x=0; x<len; x++,pIter++ ){
                    pIter->data = config->bk_color;
                }
            }
#endif
        }
        
        if( dataScr->value <= dataScr->min || (cache->active&& !dataScr->active) ){
            // 去除上箭头
            var len = config->text.size;                                    // 三角形(上) 底长度(pix)
            var xs  = (config->area.xs + cache->textXS - len)>>1;           // 三角形(上) 最左端坐标
            var ys  = cache->lineUP - cache->margin;                        // 三角形(上下) 底起始位置
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            for( var y=ys; len>0&&y>=config->area.ys; len-=2, y--, xs++ ){
                GLU_UION(Pixel)* pIter = &info_MainScreen.ptr[(y>>3)*info_MainScreen.w + xs];
                for( int x=0; x<len; x++, pIter++ ){
                    if( config->bk_color!=0 ){
                        pIter->data = __BIT_SET( pIter->data, y%8 );
                    }else{
                        pIter->data = __BIT_CLR( pIter->data, y%8 );
                    }
                }
                
            }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            for( var y=ys; len>0&&y>=config->area.ys; len-=2, y--, xs++ ){
                GLU_UION(Pixel)* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( var x=0; x<len; x++,pIter++ ){
                    pIter->data = config->bk_color;
                }
            }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            for( var y=ys; len>0&&y>=config->area.ys; len-=2, y--, xs++ ){
                GLU_UION(Pixel)* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( var x=0; x<len; x++,pIter++ ){
                    pIter->data = config->bk_color;
                }
            }
#endif
        }
        
    }
    
    BLK_FUNC( Graph, restoreCache )();
}
static void __gui_insert_object_spinbox   ( const GLU_SRCT(Object)* config ){
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font, backupCache )();
    struct{
        int32_t    value;
        var        margin;
        bool       triUP;
        bool       triDN;
        var        lineUP;
        var        lineDN;
        var        textXS;
        var        textYS;
        __Area_t   num;
        bool       active;
    }*cache = (void*)config->history;
    
    __GUI_ObjDataScr_spinbox* dataScr = (__GUI_ObjDataScr_spinbox*)(config->dataScr);
    
    if( !cache ){
        cache = RH_MALLOC( sizeof(*cache) );
        cache->margin = 4;
        cache->value  = dataScr->min;
        cache->triUP  = false;
        cache->lineUP = config->area.ys + ((config->area.h-(config->text.size+cache->margin))>>1);
        cache->lineDN = config->area.ys + ((config->area.h+(config->text.size+cache->margin))>>1);
        cache->textXS = config->area.xs+dataScr->text_offset-1;
        cache->textYS = cache->lineUP + (cache->margin>>1) + 1;
        cache->active = false;
        { // 绘制上下两横线
            int line_y1 = cache->lineUP = config->area.ys + ((config->area.h-(config->text.size+cache->margin))>>1);
            int line_y2 = cache->lineDN = config->area.ys + ((config->area.h+(config->text.size+cache->margin))>>1);
            BLK_FUNC( Graph, set_penColor )( M_COLOR_WHITE );
            BLK_FUNC( Graph, line_raw     )( (int)( config->area.xs                  ),\
                                             (int)( line_y1                          ),\
                                             (int)( config->area.xs+config->area.w-1 ),\
                                             (int)( line_y1                          ),\
                                             &info_MainScreen, NULL );
            BLK_FUNC( Graph, line_raw     )( (int)( config->area.xs                  ),\
                                             (int)( line_y2                          ),\
                                             (int)( config->area.xs+config->area.w-1 ),\
                                             (int)( line_y2                          ),\
                                             &info_MainScreen, NULL );
        }
        
        { // 绘制文字
            if( config->text.str!=NULL ){
                char* ptrUnit = alloca( strlen(config->text.str) );
                strcpy( ptrUnit, config->text.str );
                GLU_FUNC( Font, set_size )( config->text.size );
                ptrUnit[ GLU_FUNC(Font,get_str_WordCnt)( config->area.w - dataScr->text_offset , config->text.str) ] = '\0';
                GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )( ptrUnit );
                
                // 引用灰度字体图像(类型信息复制转换)
                BLK_SRCT(ImgGry) img_font = {
                    .h   = pF->img_h,
                    .w   = pF->img_w,
                    .ptr = (BLK_UION(PixelGry)*)pF->img_buf
                };
                
                var width;
                GLU_FUNC( Font, get_str_ImgInfo )( &width, NULL, ptrUnit );
                int x_fs = cache->textXS;
                int y_fs = cache->textYS = cache->lineUP + (cache->margin>>1);
                
            #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
                
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
                
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, config->obj_color, 100);
                
            #else
                 
            #endif
                
            }
        }
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, cache);
    }else{
        __gui_remove_object_spinbox( config );
    }
    
    if( dataScr->value < dataScr->max )
        cache->triDN = true;
    else
        cache->triDN = false;
    
    if( dataScr->value > dataScr->min )
        cache->triUP = true;
    else
        cache->triUP = false;
    
    { // 绘制数字
        cache->value = RH_LIMIT( dataScr->value, dataScr->min, dataScr->max );
        GLU_FUNC( Font, set_size )( config->text.size );
        size_t size   = 1 + BLK_FUNC( Bit, DECs )( cache->value );
        char* ptrNum  = alloca( size );
        snprintf( ptrNum, size, "%d", cache->value );
        ptrNum[size-1] = '\0';
        
        GLU_FUNC( Font, get_str_ImgInfo )( &cache->num.w, &cache->num.h, ptrNum);
        cache->num.xs     = cache->textXS - cache->num.w - dataScr->margin;
        cache->num.ys     = cache->textYS;
        
        GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )( ptrNum );
        
        // 引用灰度字体图像(类型信息复制转换)
        BLK_SRCT(ImgGry) img_font = {
            .h   = pF->img_h,
            .w   = pF->img_w,
            .ptr = (BLK_UION(PixelGry)*)pF->img_buf
        };
        
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, cache->num.xs, cache->num.ys, config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, cache->num.xs, cache->num.ys, config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, cache->num.xs, cache->num.ys, config->obj_color, 100);
        
    #else
         
    #endif
        
    }
    
    if( dataScr->active ){ // 绘制三角箭头提示
        var len   = config->text.size;                                 // 三角形(上) 底长度(pix)
        var xs    = (config->area.xs + cache->textXS - len)>>1;        // 三角形(上) 最左端坐标
        var ys[2] = { cache->lineUP - cache->margin , cache->lineDN + cache->margin }; // 三角形(上下) 底起始位置
        
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        if( cache->triUP ){
            for( var y=ys[0]; len>0&&y>=config->area.ys; len-=2, y--, xs++ ){
                GLU_UION(Pixel)* pIter = &info_MainScreen.ptr[(y>>3)*info_MainScreen.w + xs];
                for( var x=0; x<len; x++, pIter++ ){
                    if( config->obj_color!=0 ){
                        pIter->data = __BIT_SET( pIter->data, y%8 );
                    }else{
                        pIter->data = __BIT_CLR( pIter->data, y%8 );
                    }
                }
                
            }
        }
        
        len = config->text_size;
        xs  = (config->area.xs + cache->textXS - len)>>1;
        if( cache->triDN ){
            for( var y=ys[1]; len>0&&y<config->area.ys+config->area.h; len-=2, y++, xs++ ){
                GLU_UION(Pixel)* pIter = &info_MainScreen.ptr[(y>>3)*info_MainScreen.w + xs];
                for( var x=0; x<len; x++,pIter++ ){
                    if( config->obj_color!=0 ){
                        pIter->data = __BIT_SET( pIter->data, y%8 );
                    }else{
                        pIter->data = __BIT_CLR( pIter->data, y%8 );
                    }
                }
            }
        }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        
        if( cache->triUP ){
            for( int y=ys[0]; len>0&&y>=config->area.ys; len-=2, y--, xs++ ){
                GLU_UION( Pixel )* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( int x=0; x<len; x++,pIter++ ){
                    pIter->data = config->obj_color;
                }
            }
        }
        
        len = config->text_size;
        xs  = cache->num.xs + (int)((cache->num.width - len)>>1);
        if( cache->triDN ){
            for( int y=ys[1]; len>0&&y<config->area.ys+config->area.height; len-=2, y++, xs++ ){
                GLU_UION( Pixel )* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( int x=0; x<len; x++,pIter++ ){
                    pIter->data = config->obj_color;
                }
            }
        }
        
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        if( cache->triUP ){
            for( int y=ys[0]; len>0&&y>=config->area.ys; len-=2, y--, xs++ ){
                GLU_UION( Pixel )* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( int x=0; x<len; x++,pIter++ ){
                    pIter->data = config->obj_color;
                }
            }
        }
        
        len = config->text.size;
        xs  = cache->num.xs + ((cache->num.w - len)>>1);
        if( cache->triDN ){
            for( var y=ys[1]; len>0&&y<config->area.ys+config->area.h; len-=2, y++, xs++ ){
                GLU_UION( Pixel )* pIter = &info_MainScreen.ptr[ y*info_MainScreen.w+xs ];
                for( var x=0; x<len; x++,pIter++ ){
                    pIter->data = config->obj_color;
                }
            }
        }
#else
     
#endif
        
    }
    
    cache->active = dataScr->active;
    
    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( Font, restoreCache )();
    
}
static void __gui_adjust_object_spinbox   ( const GLU_SRCT(Object)* config ){
    __gui_insert_object_spinbox( config );
}

static void __gui_remove_object_button    ( const GLU_SRCT(Object)* config ){
    struct{
        bool   cmd;
        bool   active;
        var    margin;
        var    radius;
    }*cache = (void*)config->history;
    const __GUI_ObjDataScr_button* dataScr = config->dataScr;
    
    if( dataScr->cmd!=cache->cmd || dataScr->radius!=cache->radius ){
        BLK_FUNC( Graph, backupCache )();
        BLK_FUNC( Graph, set_penColor )( config->bk_color );
        BLK_FUNC( Graph, EX_rect_fill )( &config->area, &info_MainScreen, NULL );
        BLK_FUNC( Graph, restoreCache )();
    }
    
}
static void __gui_insert_object_button    ( const GLU_SRCT(Object)* config ){
    struct{
        bool   cmd;
        bool   active;
        var    margin;
        var    radius;
    }*cache = (void*)config->history;
    
    const __GUI_ObjDataScr_button* dataScr = config->dataScr;
    
    if( !cache ){
        cache = RH_CALLOC( 1, sizeof(*cache));
        __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, cache);
        cache->margin = 1;
        cache->cmd    = !dataScr->cmd;
    }else{
        __gui_remove_object_button( config );
    }
    
    
    BLK_FUNC( Graph, backupCache  )();

    // 绘制按钮
    BLK_FUNC( Graph, set_penColor )( config->obj_color );
    var roundRadius = RH_LIMIT( dataScr->radius, 0, RH_MIN(config->area.h>>1, config->area.w>>1) );
    
    // 绘制实心圆角矩形
    BLK_FUNC( Graph, set_penSize  )( roundRadius );
    
    if(dataScr->cmd == true)
        BLK_FUNC( Graph, rect_round_fill)( (int)( config->area.xs+cache->margin                  ),\
                                           (int)( config->area.ys+cache->margin                  ),\
                                           (int)( config->area.xs+config->area.w-cache->margin-1 ),\
                                           (int)( config->area.ys+config->area.h-cache->margin-1 ),\
                                           &info_MainScreen, NULL );
    else
        BLK_FUNC( Graph, rect_round_raw )( (int)( config->area.xs+cache->margin                  ),\
                                           (int)( config->area.ys+cache->margin                  ),\
                                           (int)( config->area.xs+config->area.w-cache->margin-1 ),\
                                           (int)( config->area.ys+config->area.h-cache->margin-1 ),\
                                           &info_MainScreen, NULL );
    
    
    // 绘制按钮上的文字
    if( config->text.str ){
        GLU_FUNC( Font, backupCache )();
        GLU_FUNC( Font, set_font )( config->text.font );
        GLU_FUNC( Font, set_size )( config->text.size );
        char* str = alloca( strlen(config->text.str)+1 );
    #ifdef RH_DEBUG
        RH_ASSERT( str );
    #endif
        strcpy(str, config->text.str);
        str[ GLU_FUNC(Font,get_str_WordCnt)( config->area.w-2*cache->margin, config->text.str ) ] = '\0';
        GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )( str );
        
        var x_fs = config->area.xs + ((config->area.w-pF->img_w)>>1);
        var y_fs = config->area.ys + ((config->area.h-pF->img_h)>>1);

        // 引用灰度字体图像(类型信息复制转换)
        BLK_SRCT(ImgGry) img_font = {
            .h   = pF->img_h,
            .w   = pF->img_w,
            .ptr = (BLK_UION(PixelGry)*)pF->img_buf
        };
        
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, (dataScr->cmd == true)?config->bk_color:config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, (dataScr->cmd == true)?config->bk_color:config->obj_color, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, (dataScr->cmd == true)?config->bk_color:config->obj_color, 100);
        
    #else
         
    #endif
        
        GLU_FUNC( Font, restoreCache )();
    }
    
    // 绘制激活态, 即边框
    if( dataScr->active ){
        BLK_FUNC( Graph, set_penColor)( config->obj_color );
        BLK_FUNC( Graph, rect_raw    )( (int)( config->area.xs+cache->margin    ),\
                                        (int)( config->area.ys+cache->margin    ),\
                                        (int)( config->area.xs+config->area.w-1 ),\
                                        (int)( config->area.ys+config->area.h-1 ),\
                                        &info_MainScreen, NULL );
    }
    
    cache->radius = dataScr->radius;
    cache->cmd    = dataScr->cmd;
    cache->active = dataScr->active;
    
    BLK_FUNC( Graph, restoreCache )();
    
}
static void __gui_adjust_object_button    ( const GLU_SRCT(Object)* config ){
    struct{
        bool   cmd;
        bool   active;
        var    margin;
        var    radius;
    }*cache = (void*)config->history;
    const __GUI_ObjDataScr_button* dataScr = config->dataScr;
    
    if( dataScr->cmd!=cache->cmd || dataScr->active!=cache->active || dataScr->radius!=cache->radius ){
        __gui_insert_object_button( config );
    }
}


#ifdef RH_DEBUG
static inline void __gui_check_object     ( const GLU_SRCT(Object)* config ){
    RH_ASSERT( config );
    RH_ASSERT( config->widget <  NUM_kGUI_ObjWidgets );
    RH_ASSERT( config->area.xs + config->area.w-1 < GUI_X_WIDTH   ); // Can be compromised, no need to abort the program.
    RH_ASSERT( config->area.ys + config->area.h-1 < GUI_Y_WIDTH   ); // Can be compromised, no need to abort the program.
}
#endif

ID_t RH_RESULT    GLU_FUNC( Object, create   )  ( const GLU_SRCT(Object)* config, const void* RH_NULLABLE dataScr ){
    GLU_SRCT(Object)* m_config = (GLU_SRCT(Object)*)RH_MALLOC( sizeof(GLU_SRCT(Object)) );
#ifdef RH_DEBUG
    RH_ASSERT( m_config );
    RH_ASSERT( config );
    __gui_check_object(config);
#endif
    memmove(m_config, config, sizeof(GLU_SRCT(Object)));
    __SET_STRUCT_MB(GLU_SRCT(Object), void*, m_config, history, NULL);
    
    switch( m_config->widget ){
        case kGUI_ObjStyle_text:
            m_config->insert_func = __gui_insert_object_text;
            m_config->remove_func = __gui_remove_object_text;
            m_config->adjust_func = __gui_adjust_object_text;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_text) );
            break;
        case kGUI_ObjStyle_num:
            m_config->insert_func = __gui_insert_object_num;
            m_config->remove_func = __gui_remove_object_num;
            m_config->adjust_func = __gui_adjust_object_num;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_num) );
            break;
        case kGUI_ObjStyle_fnum:
            m_config->insert_func = __gui_insert_object_fnum;
            m_config->remove_func = __gui_remove_object_fnum;
            m_config->adjust_func = __gui_adjust_object_fnum;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_fnum) );
//            if( !dataScr ){}
//            else{}
            break;
        case kGUI_ObjStyle_switch:
            m_config->insert_func = __gui_insert_object_switch;
            m_config->remove_func = __gui_remove_object_switch;
            m_config->adjust_func = __gui_adjust_object_switch;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_switch) );
            if( !dataScr ){
                ((__GUI_ObjDataScr_switch*)m_config->dataScr)->cmd   = false;
            }else{
                memcpy(m_config->dataScr, dataScr, sizeof( __GUI_ObjDataScr_switch ));
            }
            break;
        case kGUI_ObjStyle_barH:
            m_config->insert_func = __gui_insert_object_bar_h;
            m_config->remove_func = __gui_remove_object_bar_h;
            m_config->adjust_func = __gui_adjust_object_bar_h;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_barH) );
            break;
        case kGUI_ObjStyle_barV:
            m_config->insert_func = __gui_insert_object_bar_v;
            m_config->remove_func = __gui_remove_object_bar_v;
            m_config->adjust_func = __gui_adjust_object_bar_v;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(       __GUI_ObjDataScr_barV) );
            if( !dataScr ){
                ((__GUI_ObjDataScr_barV*)m_config->dataScr)->max   = 100;
                ((__GUI_ObjDataScr_barV*)m_config->dataScr)->min   = 0;
                ((__GUI_ObjDataScr_barV*)m_config->dataScr)->value = 0;
            }else{
                memcpy(m_config->dataScr, dataScr, sizeof( __GUI_ObjDataScr_barV ));
            }
            break;
        case kGUI_ObjStyle_trunk:
            m_config->insert_func = __gui_insert_object_trunk;
            m_config->remove_func = __gui_remove_object_trunk;
            m_config->adjust_func = __gui_adjust_object_trunk;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof( __GUI_ObjDataScr_trunk) );
            if( !dataScr ){
                ((__GUI_ObjDataScr_barV*)m_config->dataScr)->max   = 100;
                ((__GUI_ObjDataScr_barV*)m_config->dataScr)->min   = 0;
                ((__GUI_ObjDataScr_barV*)m_config->dataScr)->value = 0;
            }else{
                memcpy(m_config->dataScr, dataScr, sizeof( __GUI_ObjDataScr_trunk));
            }
            break;
        case kGUI_ObjStyle_joystick:
            m_config->insert_func = __gui_insert_object_joystick;
            m_config->remove_func = __gui_remove_object_joystick;
            m_config->adjust_func = __gui_adjust_object_joystick;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_joystick) );
            if( !dataScr ){
                ((struct __GUI_ObjDataScr_joystick*)m_config->dataScr)->max[0]   = 100;
                ((struct __GUI_ObjDataScr_joystick*)m_config->dataScr)->max[1]   = 100;
                ((struct __GUI_ObjDataScr_joystick*)m_config->dataScr)->min[0]   = 0;
                ((struct __GUI_ObjDataScr_joystick*)m_config->dataScr)->min[1]   = 0;
                ((struct __GUI_ObjDataScr_joystick*)m_config->dataScr)->value[0] = 50;
                ((struct __GUI_ObjDataScr_joystick*)m_config->dataScr)->value[1] = 50;
            }else{
                memcpy(m_config->dataScr, dataScr, sizeof(struct __GUI_ObjDataScr_joystick));
            }
            break;
        case kGUI_ObjStyle_spinbox:
            m_config->insert_func = __gui_insert_object_spinbox;
            m_config->remove_func = __gui_remove_object_spinbox;
            m_config->adjust_func = __gui_adjust_object_spinbox;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_spinbox) );
            if( !dataScr ){
                ((struct __GUI_ObjDataScr_spinbox*)m_config->dataScr)->min  = 0;
                ((struct __GUI_ObjDataScr_spinbox*)m_config->dataScr)->max  = 100;
            }else{
                memcpy(m_config->dataScr, dataScr, sizeof(struct __GUI_ObjDataScr_spinbox));
            }
            //...//
            break;
        case kGUI_ObjStyle_button:
            m_config->insert_func = __gui_insert_object_button;
            m_config->remove_func = __gui_remove_object_button;
            m_config->adjust_func = __gui_adjust_object_button;
            m_config->dataScr     = RH_CALLOC( 1U, sizeof(struct __GUI_ObjDataScr_button) );
            if( !dataScr ){
                ((struct __GUI_ObjDataScr_button*)m_config->dataScr)->active = true;
                ((struct __GUI_ObjDataScr_button*)m_config->dataScr)->cmd    = true;
                ((struct __GUI_ObjDataScr_button*)m_config->dataScr)->radius = 126;
            }else{
                memcpy(m_config->dataScr, dataScr, sizeof(struct __GUI_ObjDataScr_spinbox));
            }
            break;
        default:
            RH_ASSERT(0);
    }
    
    return (ID_t)m_config;
}

E_Status_t        GLU_FUNC( Object, template )  ( GLU_SRCT(Object)* config, E_GUI_ObjWidget_t widget ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( widget < NUM_kGUI_ObjWidgets );
#endif
    // Common Settings
    config->text.str  = "DEMO";
    config->widget    = widget;
    config->showFrame = true;
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    config->bk_color    = COLOR_1BIT(M_COLOR_BLACK);
    config->obj_color   = COLOR_1BIT(M_COLOR_WHITE);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    config->bk_color    = COLOR_16BIT(M_COLOR_BLACK);
    config->obj_color   = COLOR_16BIT(M_COLOR_WHITE);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    config->bk_color    = COLOR_24BIT(M_COLOR_BLACK);
    config->obj_color   = COLOR_24BIT(M_COLOR_WHITE);
#endif
    
    // Speacial Settings
    switch ( widget ) {
        case kGUI_ObjStyle_text:
        case kGUI_ObjStyle_num:
        case kGUI_ObjStyle_fnum:
            config->text.font   = kGLU_Font_ArialRounded_Bold;
            config->text.align  = kGLU_Align_Middle;
            config->text.size   = RH_LIMIT((GUI_Y_WIDTH*GUI_X_WIDTH)>>10, 8, 64);
            config->area.w      = (var)RH_LIMIT( config->text.size*strlen(config->text.str), 0, GUI_X_WIDTH);
            config->area.h      = (var)RH_LIMIT( config->text.size+(RH_LIMIT( config->text.size>>3, 1, config->text.size )<<2) , 0, GUI_Y_WIDTH);
            config->area.xs     = (var)(( GUI_X_WIDTH - config->area.w )>>1);
            config->area.ys     = (var)(( GUI_Y_WIDTH - config->area.h )>>1);
            break;
            
        case kGUI_ObjStyle_switch:
            config->area.w      = (var)((hypotf(GUI_X_WIDTH, GUI_Y_WIDTH)+646)/26.3);
            config->area.h      = (var)(RH_LIMIT( config->area.w>>1, 4, GUI_Y_WIDTH));
            config->area.xs     = (var)(( GUI_X_WIDTH - config->area.w )>>1);
            config->area.ys     = (var)(( GUI_Y_WIDTH - config->area.h )>>1);
            break;
            
        case kGUI_ObjStyle_barH:
            config->area.w      = (var)(GUI_X_WIDTH>>2);
            config->area.h      = (var)(config->area.w>>3);
            config->area.xs     = (var)(( GUI_X_WIDTH - config->area.w )>>1);
            config->area.ys     = (var)(( GUI_Y_WIDTH - config->area.h )>>1);
            break;
        case kGUI_ObjStyle_barV:
            config->area.h      = (var)((GUI_Y_WIDTH*3)>>3);
            config->area.w      = (var)(RH_LIMIT( config->area.h>>3, 4, GUI_X_WIDTH ));
            config->area.xs     = (var)(( GUI_X_WIDTH - config->area.w )>>1);
            config->area.ys     = (var)(( GUI_Y_WIDTH - config->area.h )>>1);
            break;
        case kGUI_ObjStyle_joystick:
            config->area.w      = (var)(RH_MIN(GUI_X_WIDTH, GUI_Y_WIDTH)>>1);
            config->area.h      = (var)(RH_MIN(GUI_X_WIDTH, GUI_Y_WIDTH)>>1);
            config->area.xs     = (var)(( GUI_X_WIDTH - config->area.w )>>1);
            config->area.ys     = (var)(( GUI_Y_WIDTH - config->area.h )>>1);
            break;
            
        case kGUI_ObjStyle_trunk:
            config->area.h      = (var)((GUI_Y_WIDTH*3)>>2);
            config->area.w      = (var)RH_LIMIT( config->area.h>>1, 4, GUI_X_WIDTH );
            config->area.xs     = (var)(( GUI_X_WIDTH - config->area.w )>>1);
            config->area.ys     = (var)(( GUI_Y_WIDTH - config->area.h )>>1);
            config->text.size   = 8;
            config->text.align  = kGLU_Align_Middle;
            break;
        case kGUI_ObjStyle_spinbox:
            config->area.h      = (var)((GUI_Y_WIDTH*3)>>2);
            config->area.w      = (var)((GUI_X_WIDTH*3)>>2);
            config->area.xs     = (var)(( GUI_X_WIDTH - config->area.w )>>1);
            config->area.ys     = (var)(( GUI_Y_WIDTH - config->area.h )>>1);
            config->text.size   = 8;
            config->text.align  = kGLU_Align_Left;
            break;
        case kGUI_ObjStyle_button:
            GLU_FUNC( Object, preferred_area )( &config->area, widget );
            GLU_Utility_optimal_text( &config->area, config->text.str, kGLU_Font_ArialRounded_Bold, &config->text );
            config->text.align  = kGLU_Align_Middle;
            break;
        default:
            return MAKE_ENUM( kStatus_NotFound );
    }
    
    
    return MAKE_ENUM( kStatus_Success );
}

E_Status_t        GLU_FUNC( Object, frame    )  ( ID_t ID  , bool  cmd   ){
#ifdef RH_DEBUG
    RH_ASSERT( ID );
#endif
    GLU_SRCT(Object)* p = (GLU_SRCT(Object)*)(ID);
    
    BLK_FUNC( Graph, backupCache )();
    if( cmd ){
        BLK_FUNC( Graph, set_penColor )( p->obj_color );
        BLK_FUNC( Graph, EX_rect_raw  )( &p->area, &info_MainScreen, NULL);
    }else{
        BLK_FUNC( Graph, set_penColor )( p->bk_color );
        BLK_FUNC( Graph, EX_rect_raw  )( &p->area, &info_MainScreen, NULL);
    }
    p->showFrame = cmd;
    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, EX_refreashScreenArea )( &p->area )\
                                     : GLU_FUNC( GUI, EX_addScreenArea      )( &p->area );
    return MAKE_ENUM( kStatus_Success );
}

E_Status_t        GLU_FUNC( Object, insert   )  ( ID_t ID ){
    GLU_SRCT(Object)* config = (GLU_SRCT(Object)*)ID;
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->insert_func );
#endif
    
    (*config->insert_func)( config );
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, EX_refreashScreenArea )( &config->area )\
                                     : GLU_FUNC( GUI, EX_addScreenArea      )( &config->area );
    return MAKE_ENUM( kStatus_Success );
}

E_Status_t        GLU_FUNC( Object, adjust   )  ( ID_t ID  , void*  dataScr, size_t dataSize ){
    GLU_SRCT(Object)* config = (GLU_SRCT(Object)*)ID;
#ifdef RH_DEBUG
    RH_ASSERT( config );
    RH_ASSERT( config->insert_func );
    //...//
#endif
    memcpy(config->dataScr, dataScr, dataSize);
    (*config->adjust_func)(config);
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, EX_refreashScreenArea )( &config->area )\
                                     : GLU_FUNC( GUI, EX_addScreenArea      )( &config->area );
    return MAKE_ENUM( kStatus_Success );
}

E_Status_t        GLU_FUNC( Object, delete   )  ( ID_t ID ){
    GLU_SRCT(Object)* config = (GLU_SRCT(Object)*)( ID );
    RH_FREE( (void*)config->history );
    RH_FREE( (void*)config->dataScr );
    __SET_STRUCT_MB(GLU_SRCT(Object), void*, config, history, NULL);
    
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font, backupCache )();
    BLK_FUNC( Graph, set_penColor )(config->bk_color);
    
    BLK_FUNC( Graph, EX_rect_fill )( &config->area, &info_MainScreen, NULL);
    
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, EX_refreashScreenArea )( &config->area )
                                     : GLU_FUNC( GUI, EX_addScreenArea      )( &config->area );
    
    RH_FREE( config );
    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( Font, restoreCache )();
    
    return MAKE_ENUM( kStatus_Success );
}


E_Status_t        GLU_FUNC( Object, preferred_area ) ( __Area_t* preferred_area, E_GUI_ObjWidget_t widget ){
    
    RH_ASSERT( preferred_area );
    
    switch( widget ){
        case kGUI_ObjStyle_button:
            preferred_area->w = (var)( RH_CFG_SCREEN_WIDTH  /6 );
            preferred_area->h = (var)( RH_CFG_SCREEN_HEIGHT>>3 );
            break;
        default: 
            return MAKE_ENUM( kStatus_NotFound );
    }

    GLU_FUNC( Utility, align_screen )( preferred_area->w, preferred_area->h, preferred_area, M_UTILITY_ALIGN_VM|M_UTILITY_ALIGN_HM );

    return MAKE_ENUM( kStatus_Success );
}
