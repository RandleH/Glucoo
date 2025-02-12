
#include "../GLU_glucoo.h"
#include "./GLU_menu.h"
#include "BLK_graphic.h"

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH
extern BLK_TYPE(Canvas) info_MainScreen; //...//


static void __gui_insert_menu_title    ( const tGluMenu* config ){
    struct{
        var idx;          // 上一次选中的菜单索引(一定小于config->nItem)
        var cur;          // 选中的菜单实际索引(一定小于 nIterPer)
        var bSize;        // 菜单栏行高 bar size
        var tSize;        // 标题行高 title size
        var tFontH;       // 菜单标题字体高度
        var bFontH;       // 菜单栏字体高度
        var nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    glu_font_set_size( pHistory->tFontH );
    
    int cnt = glu_font_get_str_word_cnt( config->area.w, config->title ); // 计算最多可容纳的字符个数
    char* p = NULL;
    if( cnt>0 ){
        p = alloca( cnt+sizeof('\0') );  // 分配空间
        strncpy(p, config->title, cnt);  // 截取字符串到该空间
        p[cnt] = '\0';                   // 末尾取0
        tGluFontImg* pF = glu_font_out_str_img(p);
        var x_fs = RH_LIMIT( config->area.xs +((config->area.w - pF->img_w)>>1)        , 0, GUI_X_WIDTH-1 );
        var y_fs = RH_LIMIT( config->area.ys +((pHistory->tSize - pHistory->tFontH)>>1), 0, GUI_Y_WIDTH-1 );
        
        // 引用灰度字体图像(类型信息复制转换)
        BLK_SRCT(ImgGry) img_font = {
            .h    = pF->img_h,
            .w    = pF->img_w,
            .ptr  = (BLK_UION(PixelGry)*)pF->img_buf
        };
        
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, config->color_title, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, config->color_title, 100);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, config->color_title, 100);
        
    #else
         
    #endif
        
    }
    
}

static void __gui_insert_menu_bar      ( const tGluMenu* config ){
    struct{
        var idx;          // 上一次选中的菜单索引(一定小于config->nItem)
        var cur;          // 选中的菜单实际索引(一定小于 nIterPer)
        var bSize;        // 菜单栏行高 bar size
        var tSize;        // 标题行高 title size
        var tFontH;       // 菜单标题字体高度
        var bFontH;       // 菜单栏字体高度
        var nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    glu_font_set_size( pHistory->bFontH );
    
    // 菜单内容字体的起始绘制坐标
    var x_fs = RH_LIMIT( config->area.xs +(((int)(pHistory->bSize - pHistory->bFontH))>>1)                    , 0, GUI_X_WIDTH-1 );
    var y_fs = RH_LIMIT( config->area.ys + pHistory->tSize + (((int)(pHistory->bSize - pHistory->tFontH))>>1) , 0, GUI_Y_WIDTH-1 );
    
    // 菜单栏起始绘制坐标,即右上角
    int xs   = RH_LIMIT( config->area.xs + 1               , 0, GUI_X_WIDTH-1 );
    int ys   = RH_LIMIT( config->area.ys + pHistory->tSize , 0, GUI_Y_WIDTH-1 );
    
    // 确认画笔颜色
    GLU_UION(Pixel) text_color = {.data = config->text_color};
    
    for ( int8_t i=0; i<pHistory->nItemPer&&i<config->nItem; i++, y_fs+=pHistory->bSize, ys+=pHistory->bSize ) {
        int cnt = glu_font_get_str_word_cnt( config->area.w, config->menuList[pHistory->idx+i].text ); // 计算最多可容纳的字符个数
        char* p = NULL;
        
        if( i == pHistory->cur ){  // 该行被选中, 颜色选反色
            text_color.data = REVERSE_COLOR( config->text_color );
            BLK_FUNC( Graph, set_penColor )( config->sl_color );
        }else{                     // 该行未被选中
            text_color.data = config->text_color;
            BLK_FUNC( Graph, set_penColor )( config->bk_color );
        }
        
        // 绘制背景色
        BLK_FUNC( Graph, rect_fill )( (int)( xs                               ),\
                                      (int)( ys                               ),\
                                      (int)( config->area.xs+config->area.w-2 ),\
                                      (int)( ys+pHistory->bSize               ),\
                                      &info_MainScreen, NULL );
        
        if( cnt>0 ){
            p = alloca( cnt+sizeof('\0') );             // 分配空间
            strncpy(p, config->menuList[pHistory->idx+i].text, cnt);  // 截取字符串到该空间
            p[cnt] = '\0';                              // 末尾取0
            tGluFontImg* pF = glu_font_out_str_img(p);
            
            // 引用灰度字体图像(类型信息复制转换)
            BLK_SRCT(ImgGry) img_font = {
                .h   = pF->img_h,
                .w   = pF->img_w,
                .ptr = (BLK_UION(PixelGry)*)pF->img_buf
            };
            
        #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #else
             
        #endif
            
        }
    }
}

static void __gui_scroll_menu_up       ( const tGluMenu* config ){
    struct{
        var idx;          // 上一次选中的菜单索引(一定小于config->nItem)
        var cur;          // 选中的菜单实际索引(一定小于 nIterPer)
        var bSize;        // 菜单栏行高 bar size
        var tSize;        // 标题行高 title size
        var tFontH;       // 菜单标题字体高度
        var bFontH;       // 菜单栏字体高度
        var nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    glu_font_set_size( pHistory->bFontH );
    // 菜单内容字体的起始绘制坐标
    int x_fs = RH_LIMIT( config->area.xs +(((int)(pHistory->bSize - pHistory->bFontH))>>1)                    , 0, GUI_X_WIDTH-1 );
    int y_fs = RH_LIMIT( config->area.ys + pHistory->tSize + (((int)(pHistory->bSize - pHistory->tFontH))>>1) , 0, GUI_Y_WIDTH-1 );
    
    // 菜单栏起始绘制坐标,即右上角
    int xs   = RH_LIMIT( config->area.xs + 1               , 0, GUI_X_WIDTH-1 );
    int ys   = RH_LIMIT( config->area.ys + pHistory->tSize , 0, GUI_Y_WIDTH-1 );
    
    // 确认画笔颜色
    GLU_UION(Pixel) text_color = {.data = config->text_color};
    
    if( pHistory->cur == 0 ){       //  游标已经到顶, 只能滑动菜单
        if( pHistory->idx > 0 ){    //  菜单未到顶,向上滑动一栏
            pHistory->idx--;
            
            for ( int8_t i=0; i<pHistory->nItemPer&&pHistory->idx+i<config->nItem; i++, y_fs+=pHistory->bSize, ys+=pHistory->bSize ) {
                int cnt = glu_font_get_str_word_cnt( config->area.w, config->menuList[pHistory->idx+i].text ); // 计算最多可容纳的字符个数
                char* p = NULL;
                
                if( i == 0 ){        // 首行颜色选反色
                    text_color.data = REVERSE_COLOR( config->text_color );
                    BLK_FUNC( Graph, set_penColor )( config->sl_color );
                }else{                     // 该行未被选中
                    text_color.data = config->text_color;
                    BLK_FUNC( Graph, set_penColor )( config->bk_color );
                }
                
                // 绘制背景色
                BLK_FUNC( Graph, rect_fill )( (int)( xs                               ),\
                                              (int)( ys                               ),\
                                              (int)( config->area.xs+config->area.w-2 ),\
                                              (int)( ys+pHistory->bSize               ),\
                                              &info_MainScreen, NULL );
                
                if( cnt>0 ){
                    p = alloca( cnt+sizeof('\0') );             // 分配空间
                    strncpy(p, config->menuList[pHistory->idx+i].text, cnt);  // 截取字符串到该空间
                    p[cnt] = '\0';                              // 末尾取0
                    tGluFontImg* pF = glu_font_out_str_img(p);
                    
                    // 引用灰度字体图像(类型信息复制转换)
                    BLK_SRCT(ImgGry) img_font = {
                        .h   = pF->img_h,
                        .w   = pF->img_w,
                        .ptr = (BLK_UION(PixelGry)*)pF->img_buf
                    };
                    
                    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                        
                        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                        
                    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                        
                        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                        
                    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                        
                        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                        
                    #else
                         
                    #endif
            
                }
            }
            
            //...//
        }else{                      //  菜单与选中的条目均到顶端, 无需操作.
                                    
        }
    }else{                          //  游标未到顶端, 先移动游标
        pHistory->cur--;
        // 绘制之前选中,现在未选中的那条菜单栏
        int cnt = glu_font_get_str_word_cnt( config->area.w, config->menuList[pHistory->idx+pHistory->cur+1].text ); // 计算最多可容纳的字符个数
        char* p = NULL;
        // 配置画笔颜色
        text_color.data = config->text_color;
        BLK_FUNC( Graph, set_penColor )( config->bk_color );
        
        // 重新配置坐标起始位置
        ys   += (pHistory->cur+1)*pHistory->bSize;
        y_fs += (pHistory->cur+1)*pHistory->bSize;
        
        // 绘制背景色
        BLK_FUNC( Graph, rect_fill )( (int)( xs                               ),\
                                      (int)( ys                               ),\
                                      (int)( config->area.xs+config->area.w-2 ),\
                                      (int)( ys+pHistory->bSize               ),\
                                      &info_MainScreen, NULL );
        
        if( cnt>0 ){
            p = alloca( cnt+sizeof('\0') );             // 分配空间
            strncpy(p, config->menuList[pHistory->idx+pHistory->cur+1].text, cnt);  // 截取字符串到该空间
            p[cnt] = '\0';                              // 末尾取0
            tGluFontImg* pF = glu_font_out_str_img(p);
            
            // 引用灰度字体图像(类型信息复制转换)
            BLK_SRCT(ImgGry) img_font = {
                .h   = pF->img_h,
                .w   = pF->img_w,
                .ptr = (BLK_UION(PixelGry)*)pF->img_buf
            };
            
        #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            
            BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            
            BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            
            BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #else
             
        #endif
        
        }
        
        // 绘制之前未选中,现在选中的那条菜单栏
        cnt = glu_font_get_str_word_cnt( config->area.w, config->menuList[pHistory->idx+pHistory->cur].text ); // 计算最多可容纳的字符个数
        p = NULL;
        // 配置画笔颜色
        text_color.data = REVERSE_COLOR( config->text_color );
        BLK_FUNC( Graph, set_penColor )( config->sl_color );
        
        // 重新配置坐标起始位置
        ys   -= pHistory->bSize;
        y_fs -= pHistory->bSize;
        
        // 绘制背景色
        BLK_FUNC( Graph, rect_fill )( (int)( xs                               ),\
                                      (int)( ys                               ),\
                                      (int)( config->area.xs+config->area.w-2 ),\
                                      (int)( ys+pHistory->bSize               ),\
                                      &info_MainScreen, NULL );
        
        if( cnt>0 ){
            p = alloca( cnt+sizeof('\0') );             // 分配空间
            strncpy(p, config->menuList[pHistory->idx+pHistory->cur].text, cnt);  // 截取字符串到该空间
            p[cnt] = '\0';                              // 末尾取0
            tGluFontImg* pF = glu_font_out_str_img(p);
            // 引用灰度字体图像(类型信息复制转换)
            BLK_SRCT(ImgGry) img_font = {
                .h   = pF->img_h,
                .w   = pF->img_w,
                .ptr = (BLK_UION(PixelGry)*)pF->img_buf
            };
            
        #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
            
        #else
             
        #endif
        
        }
        //...//
    }
}

static void __gui_scroll_menu_down     ( const tGluMenu* config ){
    struct{
        var idx;          // 该屏第一条菜单栏的索引(一定小于等于config->nItem-nIterPer)
        var cur;          // 选中的菜单行(一定小于 nIterPer)
        var bSize;        // 菜单栏行高 bar size
        var tSize;        // 标题行高 title size
        var tFontH;       // 菜单标题字体高度
        var bFontH;       // 菜单栏字体高度
        var nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    glu_font_set_size( pHistory->bFontH );
    // 菜单内容字体的起始绘制坐标
    int x_fs = RH_LIMIT( config->area.xs +(((int)(pHistory->bSize - pHistory->bFontH))>>1)                    , 0, GUI_X_WIDTH-1 );
    int y_fs = RH_LIMIT( config->area.ys + pHistory->tSize + (((int)(pHistory->bSize - pHistory->tFontH))>>1) , 0, GUI_Y_WIDTH-1 );
    
    // 菜单栏起始绘制坐标,即右上角
    int xs   = RH_LIMIT( config->area.xs + 1               , 0, GUI_X_WIDTH-1 );
    int ys   = RH_LIMIT( config->area.ys + pHistory->tSize , 0, GUI_Y_WIDTH-1 );
    
    // 确认画笔颜色
    GLU_UION(Pixel) text_color = {.data = config->text_color};
    
    if( pHistory->cur+1==pHistory->nItemPer ){ // 游标到达底端, 只能滑动菜单
        if( pHistory->idx < config->nItem-pHistory->nItemPer ){ // 菜单未到底, 向下滑动一栏
            pHistory->idx++;
            
            for ( int8_t i=0; i<pHistory->nItemPer&&pHistory->idx+i<config->nItem; i++, y_fs+=pHistory->bSize, ys+=pHistory->bSize ) {
                int cnt = glu_font_get_str_word_cnt( config->area.w, config->menuList[pHistory->idx+i].text ); // 计算最多可容纳的字符个数
                char* p = NULL;
                
                if( i == pHistory->nItemPer-1 ){        // 首行颜色选反色
                    text_color.data = REVERSE_COLOR( config->text_color );
                    BLK_FUNC( Graph, set_penColor )( config->sl_color );
                }else{                     // 该行未被选中
                    text_color.data = config->text_color;
                    BLK_FUNC( Graph, set_penColor )( config->bk_color );
                }
                
                // 绘制背景色
                BLK_FUNC( Graph, rect_fill )( (int)( xs                               ),\
                                              (int)( ys                               ),\
                                              (int)( config->area.xs+config->area.w-2 ),\
                                              (int)( ys+pHistory->bSize               ),\
                                              &info_MainScreen, NULL );
                
                if( cnt>0 ){
                    p = alloca( cnt+sizeof('\0') );             // 分配空间
                    strncpy(p, config->menuList[pHistory->idx+i].text, cnt);  // 截取字符串到该空间
                    p[cnt] = '\0';                              // 末尾取0
                    tGluFontImg* pF = glu_font_out_str_img(p);
                    // 引用灰度字体图像(类型信息复制转换)
                    BLK_SRCT(ImgGry) img_font = {
                        .h   = pF->img_h,
                        .w   = pF->img_w,
                        .ptr = (BLK_UION(PixelGry)*)pF->img_buf
                    };
                    
                #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                    BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                    BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                    BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                    
                #else
                     
                #endif
                    
                }
            }
            
        }else{                      //  菜单与选中的条目均到底端, 无需操作.
            
        }
    }else{                                     // 游标未到底端
        if( pHistory->cur+1 != config->nItem ){// 判断游标是否为菜单底端, 菜单栏数可能小于屏幕所容纳的最大栏目数
            pHistory->cur++;                   // 移动游标
            // 绘制之前选中,现在未选中的那条菜单栏
            int cnt = glu_font_get_str_word_cnt( config->area.w, config->menuList[pHistory->idx+pHistory->cur-1].text ); // 计算最多可容纳的字符个数
            char* p = NULL;
            // 配置画笔颜色
            text_color.data = config->text_color;
            BLK_FUNC( Graph, set_penColor )( config->bk_color );
            
            // 重新配置坐标起始位置
            ys   += (pHistory->cur-1)*pHistory->bSize;
            y_fs += (pHistory->cur-1)*pHistory->bSize;

            // 绘制背景色
            BLK_FUNC( Graph, rect_fill )( (int)( xs                               ),\
                                          (int)( ys                               ),\
                                          (int)( config->area.xs+config->area.w-2 ),\
                                          (int)( ys+pHistory->bSize               ),\
                                          &info_MainScreen, NULL );
            
            if( cnt>0 ){
                p = alloca( cnt+sizeof('\0') );             // 分配空间
                strncpy(p, config->menuList[pHistory->idx+pHistory->cur-1].text, cnt);  // 截取字符串到该空间
                p[cnt] = '\0';                              // 末尾取0
                tGluFontImg* pF = glu_font_out_str_img(p);
                
                // 引用灰度字体图像(类型信息复制转换)
                BLK_SRCT(ImgGry) img_font = {
                    .h   = pF->img_h,
                    .w   = pF->img_w,
                    .ptr = (BLK_UION(PixelGry)*)pF->img_buf
                };
                
            #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                
            #else
                 
            #endif
            
            }
            
            // 绘制之前未选中,现在选中的那条菜单栏
            cnt = glu_font_get_str_word_cnt( config->area.w, config->menuList[pHistory->idx+pHistory->cur].text ); // 计算最多可容纳的字符个数
            p = NULL;
            // 配置画笔颜色
            text_color.data = REVERSE_COLOR( config->text_color );
            BLK_FUNC( Graph, set_penColor )( config->sl_color );
            
            // 重新配置坐标起始位置
            ys   += pHistory->bSize;
            y_fs += pHistory->bSize;
            
            // 绘制背景色
            BLK_FUNC( Graph, rect_fill )( (int)( xs                               ),\
                                          (int)( ys                               ),\
                                          (int)( config->area.xs+config->area.w-2 ),\
                                          (int)( ys+pHistory->bSize               ),\
                                          &info_MainScreen, NULL );
            
            if( cnt>0 ){
                p = alloca( cnt+sizeof('\0') );             // 分配空间
                strncpy(p, config->menuList[pHistory->idx+pHistory->cur].text, cnt);  // 截取字符串到该空间
                p[cnt] = '\0';                              // 末尾取0
                tGluFontImg* pF = glu_font_out_str_img(p);
                
                // 引用灰度字体图像(类型信息复制转换)
                BLK_SRCT(ImgGry) img_font = {
                    .h   = pF->img_h,
                    .w   = pF->img_w,
                    .ptr = (BLK_UION(PixelGry)*)pF->img_buf
                };
                
                #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                    BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                    BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                    BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data, 100);
                    
                #else
                     
                #endif
                
            }
        //...//
        }else{         // 只能为菜单栏数小于屏幕所容纳的最大栏数
            RH_ASSERT( config->nItem < pHistory->nItemPer );
            RH_ASSERT( pHistory->idx == 0 );
            
        }
    }
}

gluHandle_t       glu_gui_menu_create( const tGluMenu* config ){
    tGluMenu* m_config = (tGluMenu*)RH_MALLOC( sizeof(tGluMenu) );
#ifdef RH_DEBUG
    RH_ASSERT( m_config );
    RH_ASSERT( config );
#endif
    memmove(m_config, config, sizeof(tGluMenu));

    m_config->menuList = RH_MALLOC( config->nItem*sizeof(__GUI_MenuParam_t) );
    memmove(m_config->menuList, config->menuList, config->nItem*sizeof(__GUI_MenuParam_t));

    __SET_STRUCT_MB(tGluMenu, void*, m_config, history, NULL);
    
    return (gluHandle_t)m_config;
}

gluStatus_t glu_gui_menu_insert( gluHandle_t ID ){
    
    tGluMenu* config = (tGluMenu* )ID;
    
    struct{
        var idx;          // 该屏第一条菜单栏的索引(一定小于等于config->nItem-nIterPer)
        var cur;          // 选中的菜单行(一定小于 nIterPer)
        var bSize;        // 菜单栏行高 bar size
        var tSize;        // 标题行高 title size
        var tFontH;       // 菜单标题字体高度
        var bFontH;       // 菜单栏字体高度
        var nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    BLK_FUNC( Graph, backupCache )();
    glu_font_backup_cache();
    glu_font_set_style( config->font );
    
    if( pHistory == NULL ){
        pHistory = RH_MALLOC(sizeof(*pHistory));
    #ifdef RH_DEBUG
        RH_ASSERT( pHistory );
    #endif
        __SET_STRUCT_MB(tGluMenu, void*, config, history, pHistory);
        pHistory->bSize     = 12;//
        pHistory->tSize     = 12;//
        pHistory->idx       = 0;
        pHistory->nItemPer  = config->area.h/pHistory->bSize;
        pHistory->tFontH    = 8; //
        pHistory->bFontH    = 8; //
        pHistory->nItemPer  = (config->area.h-pHistory->tSize)/pHistory->bSize;
        pHistory->cur       = 0;
    
    }
    // 绘制菜单标题名
    __gui_insert_menu_title( config );
    
    // 绘制菜单栏
    __gui_insert_menu_bar( config );
    BLK_FUNC( Graph, restoreCache )();
    glu_font_restore_cache();
    
    glu_dev_is_auto_refreash() ? glu_dev_refreash_partial_screen_ex(&config->area)
                                     : glu_dev_add_refreash_area_ex(&config->area);
    
    return MAKE_ENUM( kStatus_Success );
}

gluStatus_t glu_gui_menu_frame( gluHandle_t ID, bool  cmd    ){
#ifdef RH_DEBUG
    RH_ASSERT( ID );
#endif
    tGluMenu* p = (tGluMenu*)(ID);
    
    BLK_FUNC( Graph, backupCache )();
    glu_font_backup_cache();
    
    if( cmd ){
        BLK_FUNC( Graph, EX_rect_raw )( &p->area, &info_MainScreen, NULL);
    }

    BLK_FUNC( Graph, restoreCache )();
    glu_font_restore_cache();
    return MAKE_ENUM( kStatus_Success );
}

int        glu_gui_menu_scroll( gluHandle_t ID, int cmd ){
    tGluMenu* config = (tGluMenu* )ID;
    
    if( config->history == NULL )
        return 0;
    
    BLK_FUNC( Graph, backupCache )();
    glu_font_backup_cache();
    
    switch(cmd){
        default:
        case 0:   // No action
            return MAKE_ENUM( kStatus_Success );
            
        case -1:  // scroll up
            __gui_scroll_menu_up( config );
            break;
            
        case 1:  // scroll down
            __gui_scroll_menu_down( config );
            break;
    }
    BLK_FUNC( Graph, restoreCache )();
    glu_font_restore_cache();
    
    glu_dev_is_auto_refreash() ? glu_dev_refreash_partial_screen_ex(&config->area)
                               : glu_dev_add_refreash_area_ex(&config->area);
    
    return MAKE_ENUM( kStatus_Success );
}

gluStatus_t glu_gui_menu_delete( gluHandle_t ID ){
    tGluMenu* config = (tGluMenu* )ID;
    
    RH_FREE( (void*)config->history );
    RH_FREE( config->menuList );
    __SET_STRUCT_MB(tGluMenu, void*, config, history, NULL);
    
    BLK_FUNC( Graph, backupCache  )();
    BLK_FUNC( Graph, set_penColor )(config->bk_color);
    
    BLK_FUNC( Graph, EX_rect_fill )( &config->area, &info_MainScreen, NULL);
    
    glu_dev_is_auto_refreash() ? glu_dev_refreash_partial_screen_ex(&config->area)
                                     : glu_dev_add_refreash_area_ex(&config->area);
    
    RH_FREE( config );
    BLK_FUNC( Graph, restoreCache )();

    return MAKE_ENUM( kStatus_Success );
}


