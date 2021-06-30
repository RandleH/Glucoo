
#include "../GLU_glucoo.h"
#include "./GLU_menu.h"
#include "BLK_graphic.h"

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH
extern BLK_TYPE(Canvas) info_MainScreen; //...//

static void __gui_insert_menu_title    ( const __GUI_Menu_t* config ){
    struct{
        int8_t idx;          // 上一次选中的菜单索引(一定小于config->nItem)
        int8_t cur;          // 选中的菜单实际索引(一定小于 nIterPer)
        int8_t bSize;        // 菜单栏行高 bar size
        int8_t tSize;        // 标题行高 title size
        int8_t tFontH;       // 菜单标题字体高度
        int8_t bFontH;       // 菜单栏字体高度
        int8_t nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    GLU_FUNC( Font, set_size )( pHistory->tFontH );
    
    int cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->title ); // 计算最多可容纳的字符个数
    char* p = NULL;
    if( cnt>0 ){
        p = alloca( cnt+sizeof('\0') );  // 分配空间
        strncpy(p, config->title, cnt);  // 截取字符串到该空间
        p[cnt] = '\0';                   // 末尾取0
        GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
        int x_fs = __limit( config->area.xs +(((int)(config->area.width - pF->img_w))>>1)     , 0, GUI_X_WIDTH-1 );
        int y_fs = __limit( config->area.ys +(((int)(pHistory->tSize - pHistory->tFontH))>>1) , 0, GUI_Y_WIDTH-1 );
        
        // 引用灰度字体图像(类型信息复制转换)
        BLK_SRCT(ImgGry) img_font = {
            .height  = pF->img_h,
            .width   = pF->img_w,
            .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
        };
        
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        
        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, config->color_title);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        
        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, config->color_title);
        
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        
        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, config->color_title);
        
    #else
         
    #endif
        
    }
    
}

static void __gui_insert_menu_bar      ( const __GUI_Menu_t* config ){
    struct{
        int8_t idx;          // 上一次选中的菜单索引(一定小于config->nItem)
        int8_t cur;          // 选中的菜单实际索引(一定小于 nIterPer)
        int8_t bSize;        // 菜单栏行高 bar size
        int8_t tSize;        // 标题行高 title size
        int8_t tFontH;       // 菜单标题字体高度
        int8_t bFontH;       // 菜单栏字体高度
        int8_t nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    GLU_FUNC( Font, set_size )( pHistory->bFontH );
    
    // 菜单内容字体的起始绘制坐标
    int x_fs = __limit( config->area.xs +(((int)(pHistory->bSize - pHistory->bFontH))>>1)                    , 0, GUI_X_WIDTH-1 );
    int y_fs = __limit( config->area.ys + pHistory->tSize + (((int)(pHistory->bSize - pHistory->tFontH))>>1) , 0, GUI_Y_WIDTH-1 );
    
    // 菜单栏起始绘制坐标,即右上角
    int xs   = __limit( config->area.xs + 1               , 0, GUI_X_WIDTH-1 );
    int ys   = __limit( config->area.ys + pHistory->tSize , 0, GUI_Y_WIDTH-1 );
    
    // 确认画笔颜色
    GLU_UION(Pixel) text_color = {.data = config->text_color};
    
    for ( int8_t i=0; i<pHistory->nItemPer&&i<config->nItem; i++, y_fs+=pHistory->bSize, ys+=pHistory->bSize ) {
        int cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->menuList[pHistory->idx+i].text ); // 计算最多可容纳的字符个数
        char* p = NULL;
        
        if( i == pHistory->cur ){  // 该行被选中, 颜色选反色
            text_color.data = REVERSE_COLOR( config->text_color );
            BLK_FUNC( Graph, set_penColor )( config->sl_color );
        }else{                     // 该行未被选中
            text_color.data = config->text_color;
            BLK_FUNC( Graph, set_penColor )( config->bk_color );
        }
        
        // 绘制背景色
        BLK_FUNC( Graph, rect_fill )(xs, ys, config->area.xs+(int)config->area.width-2, ys+pHistory->bSize, &info_MainScreen, kApplyPixel_fill );
        
        if( cnt>0 ){
            p = alloca( cnt+sizeof('\0') );             // 分配空间
            strncpy(p, config->menuList[pHistory->idx+i].text, cnt);  // 截取字符串到该空间
            p[cnt] = '\0';                              // 末尾取0
            GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
            
            // 引用灰度字体图像(类型信息复制转换)
            BLK_SRCT(ImgGry) img_font = {
                .height  = pF->img_h,
                .width   = pF->img_w,
                .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
            };
            
        #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            
            BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            
            BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            
            BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #else
             
        #endif
            
        
        }
    }
}

static void __gui_scroll_menu_up       ( const __GUI_Menu_t* config ){
    struct{
        int8_t idx;          // 该屏第一条菜单栏的索引(一定小于等于config->nItem-nIterPer)
        int8_t cur;          // 选中的菜单行(一定小于 nIterPer)
        int8_t bSize;        // 菜单栏行高 bar size
        int8_t tSize;        // 标题行高 title size
        int8_t tFontH;       // 菜单标题字体高度
        int8_t bFontH;       // 菜单栏字体高度
        int8_t nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    GLU_FUNC( Font, set_size )( pHistory->bFontH );
    // 菜单内容字体的起始绘制坐标
    int x_fs = __limit( config->area.xs +(((int)(pHistory->bSize - pHistory->bFontH))>>1)                    , 0, GUI_X_WIDTH-1 );
    int y_fs = __limit( config->area.ys + pHistory->tSize + (((int)(pHistory->bSize - pHistory->tFontH))>>1) , 0, GUI_Y_WIDTH-1 );
    
    // 菜单栏起始绘制坐标,即右上角
    int xs   = __limit( config->area.xs + 1               , 0, GUI_X_WIDTH-1 );
    int ys   = __limit( config->area.ys + pHistory->tSize , 0, GUI_Y_WIDTH-1 );
    
    // 确认画笔颜色
    GLU_UION(Pixel) text_color = {.data = config->text_color};
    
    if( pHistory->cur == 0 ){       //  游标已经到顶, 只能滑动菜单
        if( pHistory->idx > 0 ){    //  菜单未到顶,向上滑动一栏
            pHistory->idx--;
            
            for ( int8_t i=0; i<pHistory->nItemPer&&pHistory->idx+i<config->nItem; i++, y_fs+=pHistory->bSize, ys+=pHistory->bSize ) {
                int cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->menuList[pHistory->idx+i].text ); // 计算最多可容纳的字符个数
                char* p = NULL;
                
                if( i == 0 ){        // 首行颜色选反色
                    text_color.data = REVERSE_COLOR( config->text_color );
                    BLK_FUNC( Graph, set_penColor )( config->sl_color );
                }else{                     // 该行未被选中
                    text_color.data = config->text_color;
                    BLK_FUNC( Graph, set_penColor )( config->bk_color );
                }
                
                // 绘制背景色
                BLK_FUNC( Graph, rect_fill )(xs, ys, config->area.xs+(int)config->area.width-2, ys+pHistory->bSize, &info_MainScreen, kApplyPixel_fill );
                
                if( cnt>0 ){
                    p = alloca( cnt+sizeof('\0') );             // 分配空间
                    strncpy(p, config->menuList[pHistory->idx+i].text, cnt);  // 截取字符串到该空间
                    p[cnt] = '\0';                              // 末尾取0
                    GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
                    
                    // 引用灰度字体图像(类型信息复制转换)
                    BLK_SRCT(ImgGry) img_font = {
                        .height  = pF->img_h,
                        .width   = pF->img_w,
                        .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
                    };
                    
                    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                        
                        BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                        
                    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                        
                        BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                        
                    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                        
                        BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                        
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
        int cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->menuList[pHistory->idx+pHistory->cur+1].text ); // 计算最多可容纳的字符个数
        char* p = NULL;
        // 配置画笔颜色
        text_color.data = config->text_color;
        BLK_FUNC( Graph, set_penColor )( config->bk_color );
        
        // 重新配置坐标起始位置
        ys   += (pHistory->cur+1)*pHistory->bSize;
        y_fs += (pHistory->cur+1)*pHistory->bSize;
        // 绘制背景色
        BLK_FUNC( Graph, rect_fill )(xs, ys, config->area.xs+(int)config->area.width-2, ys+pHistory->bSize, &info_MainScreen, kApplyPixel_fill );
        if( cnt>0 ){
            p = alloca( cnt+sizeof('\0') );             // 分配空间
            strncpy(p, config->menuList[pHistory->idx+pHistory->cur+1].text, cnt);  // 截取字符串到该空间
            p[cnt] = '\0';                              // 末尾取0
            GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
            
            // 引用灰度字体图像(类型信息复制转换)
            BLK_SRCT(ImgGry) img_font = {
                .height  = pF->img_h,
                .width   = pF->img_w,
                .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
            };
            
        #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            
            BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            
            BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            
            BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #else
             
        #endif
        
        }
        
        // 绘制之前未选中,现在选中的那条菜单栏
        cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->menuList[pHistory->idx+pHistory->cur].text ); // 计算最多可容纳的字符个数
        p = NULL;
        // 配置画笔颜色
        text_color.data = REVERSE_COLOR( config->text_color );
        BLK_FUNC( Graph, set_penColor )( config->sl_color );
        
        // 重新配置坐标起始位置
        ys   -= pHistory->bSize;
        y_fs -= pHistory->bSize;
        
        // 绘制背景色
        BLK_FUNC( Graph, rect_fill )(xs, ys, config->area.xs+(int)config->area.width-2, ys+pHistory->bSize, &info_MainScreen, kApplyPixel_fill );
        
        if( cnt>0 ){
            p = alloca( cnt+sizeof('\0') );             // 分配空间
            strncpy(p, config->menuList[pHistory->idx+pHistory->cur].text, cnt);  // 截取字符串到该空间
            p[cnt] = '\0';                              // 末尾取0
            GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
            // 引用灰度字体图像(类型信息复制转换)
            BLK_SRCT(ImgGry) img_font = {
                .height  = pF->img_h,
                .width   = pF->img_w,
                .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
            };
            
        #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
            
            BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
            
            BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
            
            BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
            
        #else
             
        #endif
        
        }
        //...//
    }
}

static void __gui_scroll_menu_down     ( const __GUI_Menu_t* config ){
    struct{
        int8_t idx;          // 该屏第一条菜单栏的索引(一定小于等于config->nItem-nIterPer)
        int8_t cur;          // 选中的菜单行(一定小于 nIterPer)
        int8_t bSize;        // 菜单栏行高 bar size
        int8_t tSize;        // 标题行高 title size
        int8_t tFontH;       // 菜单标题字体高度
        int8_t bFontH;       // 菜单栏字体高度
        int8_t nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    // 配置字体大小
    GLU_FUNC( Font, set_size )( pHistory->bFontH );
    // 菜单内容字体的起始绘制坐标
    int x_fs = __limit( config->area.xs +(((int)(pHistory->bSize - pHistory->bFontH))>>1)                    , 0, GUI_X_WIDTH-1 );
    int y_fs = __limit( config->area.ys + pHistory->tSize + (((int)(pHistory->bSize - pHistory->tFontH))>>1) , 0, GUI_Y_WIDTH-1 );
    
    // 菜单栏起始绘制坐标,即右上角
    int xs   = __limit( config->area.xs + 1               , 0, GUI_X_WIDTH-1 );
    int ys   = __limit( config->area.ys + pHistory->tSize , 0, GUI_Y_WIDTH-1 );
    
    // 确认画笔颜色
    GLU_UION(Pixel) text_color = {.data = config->text_color};
    
    if( pHistory->cur+1==pHistory->nItemPer ){ // 游标到达底端, 只能滑动菜单
        if( pHistory->idx < config->nItem-pHistory->nItemPer ){ // 菜单未到底, 向下滑动一栏
            pHistory->idx++;
            
            for ( int8_t i=0; i<pHistory->nItemPer&&pHistory->idx+i<config->nItem; i++, y_fs+=pHistory->bSize, ys+=pHistory->bSize ) {
                int cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->menuList[pHistory->idx+i].text ); // 计算最多可容纳的字符个数
                char* p = NULL;
                
                if( i == pHistory->nItemPer-1 ){        // 首行颜色选反色
                    text_color.data = REVERSE_COLOR( config->text_color );
                    BLK_FUNC( Graph, set_penColor )( config->sl_color );
                }else{                     // 该行未被选中
                    text_color.data = config->text_color;
                    BLK_FUNC( Graph, set_penColor )( config->bk_color );
                }
                
                // 绘制背景色
                BLK_FUNC( Graph, rect_fill )(xs, ys, config->area.xs+(int)config->area.width-2, ys+pHistory->bSize, &info_MainScreen, kApplyPixel_fill );
                
                if( cnt>0 ){
                    p = alloca( cnt+sizeof('\0') );             // 分配空间
                    strncpy(p, config->menuList[pHistory->idx+i].text, cnt);  // 截取字符串到该空间
                    p[cnt] = '\0';                              // 末尾取0
                    GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
                    // 引用灰度字体图像(类型信息复制转换)
                    BLK_SRCT(ImgGry) img_font = {
                        .height  = pF->img_h,
                        .width   = pF->img_w,
                        .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
                    };
                    
                #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                    
                    BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                    
                    BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                    
                    BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                    
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
            int cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->menuList[pHistory->idx+pHistory->cur-1].text ); // 计算最多可容纳的字符个数
            char* p = NULL;
            // 配置画笔颜色
            text_color.data = config->text_color;
            BLK_FUNC( Graph, set_penColor )( config->bk_color );
            
            // 重新配置坐标起始位置
            ys   += (pHistory->cur-1)*pHistory->bSize;
            y_fs += (pHistory->cur-1)*pHistory->bSize;
            // 绘制背景色
            BLK_FUNC( Graph, rect_fill )(xs, ys, config->area.xs+(int)config->area.width-2, ys+pHistory->bSize, &info_MainScreen, kApplyPixel_fill );
            if( cnt>0 ){
                p = alloca( cnt+sizeof('\0') );             // 分配空间
                strncpy(p, config->menuList[pHistory->idx+pHistory->cur-1].text, cnt);  // 截取字符串到该空间
                p[cnt] = '\0';                              // 末尾取0
                GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
                
                // 引用灰度字体图像(类型信息复制转换)
                BLK_SRCT(ImgGry) img_font = {
                    .height  = pF->img_h,
                    .width   = pF->img_w,
                    .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
                };
                
            #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                
                BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                
                BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                
            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                
                BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                
            #else
                 
            #endif
            
            }
            
            // 绘制之前未选中,现在选中的那条菜单栏
            cnt = GLU_FUNC( Font, get_str_WordCnt )( config->area.width, config->menuList[pHistory->idx+pHistory->cur].text ); // 计算最多可容纳的字符个数
            p = NULL;
            // 配置画笔颜色
            text_color.data = REVERSE_COLOR( config->text_color );
            BLK_FUNC( Graph, set_penColor )( config->sl_color );
            
            // 重新配置坐标起始位置
            ys   += pHistory->bSize;
            y_fs += pHistory->bSize;
            
            // 绘制背景色
            BLK_FUNC( Graph, rect_fill )(xs, ys, config->area.xs+(int)config->area.width-2, ys+pHistory->bSize, &info_MainScreen, kApplyPixel_fill );
            
            if( cnt>0 ){
                p = alloca( cnt+sizeof('\0') );             // 分配空间
                strncpy(p, config->menuList[pHistory->idx+pHistory->cur].text, cnt);  // 截取字符串到该空间
                p[cnt] = '\0';                              // 末尾取0
                GLU_SRCT(FontImg)* pF = GLU_FUNC( Font, out_str_Img )(p);
                
                // 引用灰度字体图像(类型信息复制转换)
                BLK_SRCT(ImgGry) img_font = {
                    .height  = pF->img_h,
                    .width   = pF->img_w,
                    .pBuffer = (BLK_UION(PixelGry)*)pF->img_buf
                };
                
                #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                    
                    BLK_FUNC(ImgGry,into_ImgBin)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
                    
                    BLK_FUNC(ImgGry,into_Img565)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                    
                #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                    
                    BLK_FUNC(ImgGry,into_Img888)(&img_font, &info_MainScreen, x_fs, y_fs, text_color.data);
                    
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

ID_t       GLU_FUNC( Menu, create )    ( const __GUI_Menu_t* config ){
    __GUI_Menu_t* m_config = (__GUI_Menu_t*)RH_MALLOC( sizeof(__GUI_Menu_t) );
#ifdef RH_DEBUG
    RH_ASSERT( m_config );
    RH_ASSERT( config );
#endif
    memmove(m_config, config, sizeof(__GUI_Menu_t));

    m_config->menuList = RH_MALLOC( config->nItem*sizeof(__GUI_MenuParam_t) );
    memmove(m_config->menuList, config->menuList, config->nItem*sizeof(__GUI_MenuParam_t));

    __SET_STRUCT_MB(__GUI_Menu_t, void*, m_config, history, NULL);
    
    return (ID_t)m_config;
}

E_Status_t GLU_FUNC( Menu, insert )    ( ID_t ID ){
    
    __GUI_Menu_t* config = (__GUI_Menu_t* )ID;
    
    struct{
        int8_t idx;          // 该屏第一条菜单栏的索引(一定小于等于config->nItem-nIterPer)
        int8_t cur;          // 选中的菜单行(一定小于 nIterPer)
        int8_t bSize;        // 菜单栏行高 bar size
        int8_t tSize;        // 标题行高 title size
        int8_t tFontH;       // 菜单标题字体高度
        int8_t bFontH;       // 菜单栏字体高度
        int8_t nItemPer;     // 一版最多可显示菜单行数
    }*pHistory = (void*)config->history;
    
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font, backupCache )();
    GLU_FUNC( Font, set_font )( config->font );
    
    if( pHistory == NULL ){
        pHistory = RH_MALLOC(sizeof(*pHistory));
    #ifdef RH_DEBUG
        RH_ASSERT( pHistory );
    #endif
        __SET_STRUCT_MB(__GUI_Menu_t, void*, config, history, pHistory);
        pHistory->bSize     = 12;//
        pHistory->tSize     = 12;//
        pHistory->idx       = 0;
        pHistory->nItemPer  = config->area.height/pHistory->bSize;
        pHistory->tFontH    = 8; //
        pHistory->bFontH    = 8; //
        pHistory->nItemPer  = (config->area.height-pHistory->tSize)/pHistory->bSize;
        pHistory->cur       = 0;
    
    }
    // 绘制菜单标题名
    __gui_insert_menu_title( config );
    
    // 绘制菜单栏
    __gui_insert_menu_bar( config );
    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( Font, restoreCache )();
    
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )( config->area.xs, \
                                                 config->area.ys, \
                                                 config->area.xs+(int)(config->area.width )-1, \
                                                 config->area.ys+(int)(config->area.height)-1) \
                       :
                         GLU_FUNC( GUI, addScreenArea )     ( config->area.xs, \
                                                 config->area.ys, \
                                                 config->area.xs+(int)(config->area.width )-1, \
                                                 config->area.ys+(int)(config->area.height)-1);
    
    return MAKE_ENUM( kStatus_Success );
}

E_Status_t GLU_FUNC( Menu, frame  )    ( ID_t ID, bool  cmd    ){
#ifdef RH_DEBUG
    RH_ASSERT( ID );
#endif
    __GUI_Menu_t* p = (__GUI_Menu_t*)(ID);
    
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font, backupCache )();
    
    if( cmd ){
        BLK_FUNC( Graph, rect_raw )(p->area.xs, p->area.ys, p->area.xs+(int)(p->area.width)-1, p->area.ys+(int)(p->area.height)-1, &info_MainScreen, kApplyPixel_fill);
    }

    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( Font, restoreCache )();
    return MAKE_ENUM( kStatus_Success );
}

int        GLU_FUNC( Menu, scroll )    ( ID_t ID, int cmd ){
    __GUI_Menu_t* config = (__GUI_Menu_t* )ID;
    
    if( config->history == NULL )
        return 0;
    
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font, backupCache )();
    
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
    GLU_FUNC( Font, restoreCache )();
    
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )( config->area.xs, \
                                                 config->area.ys, \
                                                 config->area.xs+(int)(config->area.width )-1, \
                                                 config->area.ys+(int)(config->area.height)-1) \
                       :
                         GLU_FUNC( GUI, addScreenArea )     ( config->area.xs, \
                                                 config->area.ys, \
                                                 config->area.xs+(int)(config->area.width )-1, \
                                                 config->area.ys+(int)(config->area.height)-1);
    
    return MAKE_ENUM( kStatus_Success );
}

E_Status_t GLU_FUNC( Menu, delete )    ( ID_t ID ){
    __GUI_Menu_t* config = (__GUI_Menu_t* )ID;
    
    RH_FREE( (void*)config->history );
    RH_FREE( config->menuList );
    __SET_STRUCT_MB(__GUI_Menu_t, void*, config, history, NULL);
    
    BLK_FUNC( Graph, backupCache  )();
    BLK_FUNC( Graph, set_penColor )(config->bk_color);
    
    BLK_FUNC( Graph, rect_fill )( config->area.xs, \
                       config->area.ys, \
                       config->area.xs+(int)(config->area.width )-1, \
                       config->area.ys+(int)(config->area.height)-1, &info_MainScreen, kApplyPixel_fill);
    
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, refreashScreenArea )( config->area.xs, \
                                                 config->area.ys, \
                                                 config->area.xs+(int)(config->area.width )-1, \
                                                 config->area.ys+(int)(config->area.height)-1) \
                       :
                         GLU_FUNC( GUI, addScreenArea )     ( config->area.xs, \
                                                 config->area.ys, \
                                                 config->area.xs+(int)(config->area.width )-1, \
                                                 config->area.ys+(int)(config->area.height)-1);
    
    RH_FREE( config );
    BLK_FUNC( Graph, restoreCache )();

    return MAKE_ENUM( kStatus_Success );
}


