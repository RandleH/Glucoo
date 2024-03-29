
#include "../GLU_glucoo.h"
#include "./GLU_window.h"
#include "BLK_graphic.h"

#define GUI_Y_WIDTH                 RH_CFG_SCREEN_HEIGHT
#define GUI_X_WIDTH                 RH_CFG_SCREEN_WIDTH
extern BLK_TYPE(Canvas) info_MainScreen; //...//

extern void GLU_FUNC( GUI, refreashScreenArea    )   ( var xs,var ys,var xe,var ye );
extern void GLU_FUNC( GUI, addScreenArea         )   ( var xs,var ys,var xe,var ye );
extern void GLU_FUNC( GUI, EX_refreashScreenArea )   ( const __Area_t* area );
extern void GLU_FUNC( GUI, EX_addScreenArea      )   ( const __Area_t* area );

static void __gui_insert_window_MacOS  (__GUI_Window_t* config){
#ifdef RH_DEBUG
    RH_ASSERT( config );

#else
    __exit( !config );
#endif
    
    const int xs = (int)(config->area.xs);
    const int ys = (int)(config->area.ys);
    const int xe = (int)(xs+config->area.w-1);
    const int ye = (int)(ys+config->area.h-1);
    const int bar_size   = RH_LIMIT( (int)(config->size), 5, 256 );//38
    const int bar_size_2 = bar_size>>1;
    const int bar_size_4 = bar_size>>2;
    const int bar_rad    = RH_LIMIT( (int)(config->size), 5, 256 )/5;
    const int bar_edge   = config->win_edge;
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    
    const GLU_UION(Pixel) color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_BLACK ) ):( COLOR_1BIT(M_COLOR_WHITE) )};
    const GLU_UION(Pixel) color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_WHITE ) ):( COLOR_1BIT(M_COLOR_BLACK) )};
    const GLU_UION(Pixel) color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_BLACK ) ):( COLOR_1BIT(M_COLOR_WHITE) )};
    const GLU_UION(Pixel) color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_WHITE ) ):( COLOR_1BIT(M_COLOR_BLACK) )};
#else
    const GLU_UION(Pixel) color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_DARKGRAY) ):( COLOR_16BIT(M_COLOR_SILVER) )};
    const GLU_UION(Pixel) color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_WHITE   ) ):( COLOR_16BIT(M_COLOR_BLACK ) )};
    const GLU_UION(Pixel) color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_COAL    ) ):( COLOR_16BIT(M_COLOR_WHITE ) )};
    const GLU_UION(Pixel) color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_WHITE   ) ):( COLOR_16BIT(M_COLOR_BLACK ) )};
#endif
    
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font, backupCache )();
    
    // Window Bar
    BLK_FUNC( Graph, set_penColor   )( color_bar.data);
    BLK_FUNC( Graph, set_penSize    )( bar_rad);
    BLK_FUNC( Graph, rect_round_fill)(xs   , ys         , xe  , ys+bar_size+bar_rad, info_MainScreen.ptr, NULL);
    
    BLK_FUNC( Graph, line_raw )     (xs   , ye         , xe  , ye                 , info_MainScreen.ptr, NULL);
    BLK_FUNC( Graph, line_raw )     (xs   , ye-1       , xe  , ye-1               , info_MainScreen.ptr, NULL);
    
    for(int i=0; i<bar_edge; i++){
        BLK_FUNC( Graph, line_raw )     (xs+i , ys+bar_size, xs+i, ye  , info_MainScreen.ptr, NULL);
        BLK_FUNC( Graph, line_raw )     (xe-i , ys+bar_size, xe-i, ye  , info_MainScreen.ptr, NULL);
    }
    
    // Title
    if( config->title != NULL ){
        GLU_FUNC( Font, set_size )( (int)(config->size>>1) );
        GLU_FUNC( Font, set_font )( config->title_font );
        GLU_SRCT(FontImg)* pFontInfo = GLU_FUNC( Font, out_str_Img )( config->title );
        const int font_xs = RH_MID(xs,xe)-(int)((pFontInfo->img_w)>>1);
        const int font_ys = ys + bar_size_4;
        
        
        for( int y=0; y<pFontInfo->img_h; y++ ){
            for( int x=0; x<pFontInfo->img_w; x++ ){
                uint8_t pixWeight = pFontInfo->img_buf[ y*pFontInfo->img_w +x ];
                
            #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                if( pixWeight ){
                    const size_t  index    = ((y+font_ys)>>3)*info_MainScreen.w + (x+font_xs);
                    const size_t  offset   = (y+font_ys)%8;
                    if( color_title.data == 0 )
                        info_MainScreen.ptr[ index ].data = __BIT_CLR(info_MainScreen.ptr[ index ].data, offset);
                    else
                        info_MainScreen.ptr[ index ].data = __BIT_SET(info_MainScreen.ptr[ index ].data, offset);
                }

            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                if( pixWeight != 0 ){
                    const size_t  index     = (y+font_ys)*info_MainScreen.w + (x+font_xs);
                    info_MainScreen.ptr[ index ].R = info_MainScreen.ptr[ index ].R + (( (color_title.R - info_MainScreen.ptr[ index ].R) * pixWeight )>>8);
                    info_MainScreen.ptr[ index ].G = info_MainScreen.ptr[ index ].G + (( (color_title.G - info_MainScreen.ptr[ index ].G) * pixWeight )>>8);
                    info_MainScreen.ptr[ index ].B = info_MainScreen.ptr[ index ].B + (( (color_title.B - info_MainScreen.ptr[ index ].B) * pixWeight )>>8);
                }
            #else
              #error "[RH_graphic]: Unknown color type."
            #endif
                
            }
        }
    }
    
    // Context
    BLK_FUNC( Graph, set_penColor )(color_blank.data);
    BLK_FUNC( Graph, rect_fill )    (xs+bar_edge , ys+bar_size, xe-bar_edge, ye-bar_edge, info_MainScreen.ptr, NULL);
    
    
    if( config->text != NULL ){
        uint8_t*             pIterFont = ((uint8_t*)config->text_bitMap) + (config->text_rs*config->text_bitW);
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        typeof(info_MainScreen.ptr) pIterScr  = &info_MainScreen.ptr[ ((ys+bar_size)>>3)*info_MainScreen.w + xs+bar_edge+config->text_margin ];
        size_t               numOfFontPix = config->text_bitH*config->text_bitW;
        size_t               cntOfFontPix = 0;
        for( int y=ys+bar_size; y<ye-2; y++ ){
            for( int x=0; x<config->text_bitW; x++, pIterFont++, pIterScr++ ){
                if( *pIterFont > 130 ){
                    if( color_text.data == 0 )
                        pIterScr->data = __BIT_CLR( pIterScr->data, y%8 );
                    else
                        pIterScr->data = __BIT_SET( pIterScr->data, y%8 );
                }
                cntOfFontPix++;
            }
            if(cntOfFontPix == numOfFontPix)
                break;
            pIterScr -= config->text_bitW;
            pIterScr += ((y+1)%8==0)*info_MainScreen.w;
        }
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        typeof(info_MainScreen.ptr) pIterScr  = &info_MainScreen.ptr[ (ys+bar_size)*info_MainScreen.w + xs+bar_edge+config->text_margin ];
        size_t               numOfFontPix = config->text_bitH*config->text_bitW;
        size_t               cntOfFontPix = 0;
        for( int y=ys+bar_size; y<ye-2; y++ ){
            for( int x=0; x<config->text_bitW; x++, pIterFont++, pIterScr++ ){
                if( *pIterFont != 0x00 ){
                    pIterScr->R = pIterScr->R + (( (color_text.R - pIterScr->R) * (*pIterFont) )>>8);
                    pIterScr->G = pIterScr->G + (( (color_text.G - pIterScr->G) * (*pIterFont) )>>8);
                    pIterScr->B = pIterScr->B + (( (color_text.B - pIterScr->B) * (*pIterFont) )>>8);
                }
                cntOfFontPix++;
            }
            if(cntOfFontPix == numOfFontPix)
                break;
            pIterScr -= config->text_bitW;
            pIterScr += info_MainScreen.w;
        }
    
    #else
      #error "[RH_graphic]: Unknown color type."
    #endif
    
    }
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    const GLU_UION(Pixel) color_button_cl = {.data = 0x00};
    const GLU_UION(Pixel) color_button_zm = {.data = 0x00};
    const GLU_UION(Pixel) color_button_mi = {.data = 0x00};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    const GLU_UION(Pixel) color_button_cl = {.data = COLOR_16BIT(M_COLOR_BLOODYMEAT) };
    const GLU_UION(Pixel) color_button_zm = {.data = COLOR_16BIT(M_COLOR_GOLDEN    ) };
    const GLU_UION(Pixel) color_button_mi = {.data = COLOR_16BIT(M_COLOR_LAWNGREEN ) };
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    const GLU_UION(Pixel) color_button_cl = {.data = M_COLOR_BLOODYMEAT };
    const GLU_UION(Pixel) color_button_zm = {.data = M_COLOR_GOLDEN     };
    const GLU_UION(Pixel) color_button_mi = {.data = M_COLOR_LAWNGREEN  };
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    // Button
    BLK_FUNC( Graph, set_penColor )(color_button_cl.data);
    BLK_FUNC( Graph, circle_fill )  (xs+bar_size_2, RH_MID(ys,ys+bar_size), bar_size_2 , info_MainScreen.ptr, NULL);

    BLK_FUNC( Graph, set_penColor )(color_button_zm.data);
    BLK_FUNC( Graph, circle_fill )  (xs+bar_size+bar_size_4, RH_MID(ys,ys+bar_size), bar_size_2 , info_MainScreen.ptr, NULL);

    BLK_FUNC( Graph, set_penColor )(color_button_mi.data);
    BLK_FUNC( Graph, circle_fill )  (xs+(bar_size<<1), RH_MID(ys,ys+bar_size), bar_size_2 , info_MainScreen.ptr, NULL);
    
    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( Font, restoreCache )();

}
static void __gui_insert_window_Win10  (__GUI_Window_t* config){
#ifdef RH_DEBUG
    RH_ASSERT(config);
#else
    __exit( !config );
#endif
    
    const int xs = config->area.xs;
    const int ys = config->area.ys;
    const int xe = (int)(xs+config->area.w-1);
    const int ye = (int)(ys+config->area.h-1);
    const int bar_size   = RH_LIMIT( (int)((config->size<<1)/3), 10, 256 );//38
    const int bar_size_2 = bar_size>>1;
    const int bar_edge   = config->win_edge;
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    const GLU_UION(Pixel) color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_DARKGRAY) ):( COLOR_1BIT(M_COLOR_SILVER) )};
//    const GLU_UION(Pixel) color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_WHITE   ) ):( COLOR_1BIT(M_COLOR_BLACK ) )};
    const GLU_UION(Pixel) color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_COAL    ) ):( COLOR_1BIT(M_COLOR_WHITE ) )};
    const GLU_UION(Pixel) color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_1BIT(M_COLOR_WHITE   ) ):( COLOR_1BIT(M_COLOR_BLACK ) )};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    const GLU_UION(Pixel) color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_DARKGRAY) ):( COLOR_16BIT(M_COLOR_SILVER) )};
//    const GLU_UION(Pixel) color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_WHITE   ) ):( COLOR_16BIT(M_COLOR_BLACK ) )};
    const GLU_UION(Pixel) color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_COAL    ) ):( COLOR_16BIT(M_COLOR_WHITE ) )};
    const GLU_UION(Pixel) color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_16BIT(M_COLOR_WHITE   ) ):( COLOR_16BIT(M_COLOR_BLACK ) )};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    const GLU_UION(Pixel) color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_24BIT(M_COLOR_DARKGRAY) ):( COLOR_24BIT(M_COLOR_SILVER) )};
//    const GLU_UION(Pixel) color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_24BIT(M_COLOR_WHITE   ) ):( COLOR_24BIT(M_COLOR_BLACK ) )};
    const GLU_UION(Pixel) color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_24BIT(M_COLOR_COAL    ) ):( COLOR_24BIT(M_COLOR_WHITE ) )};
    const GLU_UION(Pixel) color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( COLOR_24BIT(M_COLOR_WHITE   ) ):( COLOR_24BIT(M_COLOR_BLACK ) )};
#endif
    
    BLK_FUNC( Graph, backupCache )();
    GLU_FUNC( Font, backupCache )();
    
    BLK_FUNC( Graph, set_penColor ) (color_bar.data);
    BLK_FUNC( Graph, rect_fill )    ( xs, ys, xe, ys+bar_size, info_MainScreen.ptr, NULL );
    
        
    for(int i=0; i<bar_edge; i++){
        BLK_FUNC( Graph, line_raw )     (xs+i , ys+bar_size, xs+i, ye  , info_MainScreen.ptr, NULL);
        BLK_FUNC( Graph, line_raw )     (xe-i , ys+bar_size, xe-i, ye  , info_MainScreen.ptr, NULL);
        BLK_FUNC( Graph, line_raw )     (xs   , ye-i       , xe  , ye-i, info_MainScreen.ptr, NULL);
    }
    
    // Context
    BLK_FUNC( Graph, set_penColor ) (color_blank.data);
    BLK_FUNC( Graph, rect_fill )    (xs+bar_edge , ys+bar_size, xe-bar_edge, ye-bar_edge, info_MainScreen.ptr, NULL);
    
    if( config->text != NULL ){
        uint8_t*             pIterFont = ((uint8_t*)config->text_bitMap) + (config->text_rs*config->text_bitW);
        
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        RH_ASSERT(false);
        typeof(info_MainScreen.ptr) pIterScr  = &info_MainScreen.ptr[ ((ys+bar_size)>>3)*info_MainScreen.w + xs+bar_edge+config->text_margin ];
        size_t               numOfFontPix = config->text_bitH*config->text_bitW;
        size_t               cntOfFontPix = 0;
        for( int y=ys+bar_size; y<ye-2; y++, pIterScr+=info_MainScreen.w ){
            for( int x=0; x<config->text_bitW; x++, pIterFont++, pIterScr++ ){
                if( (*pIterFont>128) ^ (color_text.data) ){
                    pIterScr->data = __BIT_SET( pIterScr->data, y%8 );
                }else{
                    pIterScr->data = __BIT_CLR( pIterScr->data, y%8 );
                }
                cntOfFontPix++;
            }
            if(cntOfFontPix == numOfFontPix)
                break;
            pIterScr -= config->text_bitW;
        }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        
        typeof(info_MainScreen.ptr) pIterScr  = &info_MainScreen.ptr[ (ys+bar_size)*info_MainScreen.w + xs+bar_edge+config->text_margin ];
        size_t               numOfFontPix = config->text_bitH*config->text_bitW;
        size_t               cntOfFontPix = 0;
        for( int y=ys+bar_size; y<ye-2; y++, pIterScr+=info_MainScreen.w ){
            for( int x=0; x<config->text_bitW; x++, pIterFont++, pIterScr++ ){
                if( *pIterFont != 0x00 ){
                    pIterScr->R = pIterScr->R + (( (color_text.R - pIterScr->R) * (*pIterFont) )>>8);
                    pIterScr->G = pIterScr->G + (( (color_text.G - pIterScr->G) * (*pIterFont) )>>8);
                    pIterScr->B = pIterScr->B + (( (color_text.B - pIterScr->B) * (*pIterFont) )>>8);
                }
                cntOfFontPix++;
            }
            if(cntOfFontPix == numOfFontPix)
                break;
            pIterScr -= config->text_bitW;
        }
#else
  #error "[RH_graphic]: Unknown color type."
#endif
            
    }
    
    // Button
    const int button_w = bar_size_2*3;
    const int button_h = bar_size;
    const int button_cl_xs = xe-button_w+1, button_zm_xs = button_cl_xs-button_w, button_mi_xs = button_zm_xs-button_w;
    const int button_cl_ys = ys           , button_zm_ys = ys                   , button_mi_ys = ys;
    const int button_cl_xe = xe           , button_zm_xe = button_cl_xe-button_w, button_mi_xe = button_zm_xe-button_w;
    const int button_cl_ye = ys+button_h-1, button_zm_ye = button_cl_ye         , button_mi_ye = button_cl_ye;
    
    BLK_FUNC( Graph, set_penColor )(color_bar.data);
    BLK_FUNC( Graph, rect_fill )   ( button_cl_xs, button_cl_ys, button_cl_xe, button_cl_ye, info_MainScreen.ptr, NULL );
    {
        int xs = RH_MID(button_cl_xs,button_cl_xe)-(button_h>>3);
        int ys = RH_MID(button_cl_ys,button_cl_ye)-(button_h>>3);
        int xe = RH_MID(button_cl_xs,button_cl_xe)+(button_h>>3);
        int ye = RH_MID(button_cl_ys,button_cl_ye)+(button_h>>3);
        BLK_FUNC( Graph, set_penColor )(M_COLOR_WHITE);
        BLK_FUNC( Graph, line_raw )( xs, ys, xe, ye, info_MainScreen.ptr, NULL);
        BLK_FUNC( Graph, line_raw )( xs, ye, xe, ys, info_MainScreen.ptr, NULL);
    }
    
    BLK_FUNC( Graph, set_penColor )(color_bar.data);
    BLK_FUNC( Graph, rect_fill )   ( button_zm_xs, button_zm_ys, button_zm_xe, button_zm_ye, info_MainScreen.ptr, NULL );
    {
        int xs = RH_MID(button_zm_xs,button_zm_xe)-(button_h>>3);
        int ys = RH_MID(button_zm_ys,button_zm_ye)-(button_h>>3);
        int xe = RH_MID(button_zm_xs,button_zm_xe)+(button_h>>3);
        int ye = RH_MID(button_zm_ys,button_zm_ye)+(button_h>>3);
        BLK_FUNC( Graph, set_penColor )(M_COLOR_WHITE);
        BLK_FUNC( Graph, rect_raw )( xs, ys, xe, ye, info_MainScreen.ptr, NULL);
    }
    
    BLK_FUNC( Graph, set_penColor )(color_bar.data);
    BLK_FUNC( Graph, rect_fill )   ( button_mi_xs, button_mi_ys, button_mi_xe, button_mi_ye, info_MainScreen.ptr, NULL );
    {
        int xs = RH_MID(button_mi_xs,button_mi_xe)-(button_h>>3);
        int ys = RH_MID(button_mi_ys,button_mi_ye);
        int xe = RH_MID(button_mi_xs,button_mi_xe)+(button_h>>3);
        int ye = ys;
        BLK_FUNC( Graph, set_penColor )(M_COLOR_WHITE);
        BLK_FUNC( Graph, line_raw )( xs, ys, xe, ye, info_MainScreen.ptr, NULL);
    }
    
    BLK_FUNC( Graph, restoreCache )();
    GLU_FUNC( Font, restoreCache )();
}

static void __gui_remove_window_MacOS  (__GUI_Window_t* config){
    
}
static void __gui_remove_window_Win10  (__GUI_Window_t* config){}

#ifdef RH_DEBUG
static inline void __gui_check_window  ( const __GUI_Window_t* config ){
    RH_ASSERT( config->size      > 5                   );  /* Too small */
    RH_ASSERT( config->text_size > 5                   );  /* Too small */
    RH_ASSERT( config->type      < NUM_kGUI_WindowType );  /* Wrong enumeration reference */
    
}
#endif

ID_t RH_RESULT  GLU_FUNC( Window, create   )    ( const __GUI_Window_t* config ){
    __GUI_Window_t* m_config = (__GUI_Window_t*)RH_MALLOC( sizeof(__GUI_Window_t) );

    GLU_FUNC( Font, backupCache )();
#ifdef RH_DEBUG
    RH_ASSERT( m_config );
    RH_ASSERT( config );
    __gui_check_window(config);
#endif
    memcpy(m_config, config, sizeof( __GUI_Window_t ));
    
    switch( m_config->type ){
        case kGUI_WindowType_macOS:
            m_config->insert_func = __gui_insert_window_MacOS;
            m_config->remove_func = __gui_remove_window_MacOS;
            __SET_STRUCT_MB(__GUI_Window_t, int, m_config, win_edge  , 2);
            break;
        case kGUI_WindowType_win10:
            m_config->insert_func = __gui_insert_window_Win10;
            m_config->remove_func = __gui_remove_window_Win10;
            __SET_STRUCT_MB(__GUI_Window_t, int, m_config, win_edge  , 2);
            break;
        default:
#ifdef RH_DEBUG
            RH_ASSERT( false );
#else
            while(1);
#endif
    }
    
    if( m_config->text != NULL ){
        GLU_FUNC( Font, set_font )(m_config->text_font);
        GLU_FUNC( Font, set_size )(m_config->text_size);
        __SET_STRUCT_MB(__GUI_Window_t, int  , m_config, text_margin, 5        );

        size_t fontW = m_config->area.w-((m_config->win_edge+m_config->text_margin)<<1);
        
        GLU_SRCT(FontImg)* p = GLU_FUNC( Font, out_txt_Img )( m_config->text, fontW, kGLU_Align_Justify );
        
        __SET_STRUCT_MB(__GUI_Window_t, void*, m_config, text_bitMap, RH_MALLOC(p->img_w*p->img_h*sizeof(*(p->img_buf))));
#ifdef RH_DEBUG
        RH_ASSERT( m_config->text_bitMap );
#endif
        memcpy((void*)m_config->text_bitMap, p->img_buf, p->img_w*p->img_h*sizeof(*(p->img_buf)) );

        __SET_STRUCT_MB(__GUI_Window_t, int, m_config, text_bitH  , p->img_h);
        __SET_STRUCT_MB(__GUI_Window_t, int, m_config, text_bitW  , p->img_w );
        //...//
    }
    
    GLU_FUNC( Font, restoreCache )();
    return (ID_t)m_config;
}

__GUI_Window_t* GLU_FUNC( Window, template )    (       __GUI_Window_t* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
#else
    __exitReturn( !config, NULL);
#endif
    
    config->area.xs      = 0;
    config->area.ys      = 0;
    config->area.h       = 0;
    config->area.w       = 0;
    config->type         = kGUI_WindowType_macOS;
    config->appearance   = kGUI_Appearance_Light;
    config->size         = 40;
    config->title        = NULL;
    config->title_font   = kGLU_Font_ArialRounded_Bold;
    config->text         = NULL;
    config->text_font    = kGLU_Font_ArialRounded_Bold;
    config->text_align   = kGLU_Align_Justify;
    config->text_size    = 40;
    
    __SET_STRUCT_MB(__GUI_Window_t, int   , config, text_rs    , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, void* , config, text_bitMap, NULL );
    __SET_STRUCT_MB(__GUI_Window_t, size_t, config, text_bitH  , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, size_t, config, text_bitW  , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, int   , config, text_margin, 0    );
    return config;
}

E_Status_t      GLU_FUNC( Window, insert   )    ( ID_t ID ){
#ifdef RH_DEBUG
    RH_ASSERT( ID );
#endif
    (*((__GUI_Window_t*)ID)->insert_func)( (__GUI_Window_t*)ID );
    
    GLU_FUNC( GUI, isAutoDisplay )() ? GLU_FUNC( GUI, EX_refreashScreenArea )( &((__GUI_Window_t*)ID)->area )
                                     : GLU_FUNC( GUI, EX_addScreenArea      )( &((__GUI_Window_t*)ID)->area );
    
    return MAKE_ENUM( kStatus_Success );
}

E_Status_t      GLU_FUNC( Window, delete   )    ( ID_t ID ){
    RH_FREE((void*)ID);
    //...//
    return MAKE_ENUM( kStatus_Success );
}
