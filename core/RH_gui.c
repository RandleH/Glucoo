


#include "RH_gui.h"
#include "RH_data.h"
#include "RH_lib.h"
#include "RH_graphic.h"


void __attribute__((weak)) GUI_DrawArea       (int x1,int y1,int x2,int y2,const __Pixel_t* pixData){
// THIS MAY COST SOME TIME.
}
void (*GUI_API_DrawArea)                      (int x1,int y1,int x2,int y2,const __Pixel_t* pixData) = GUI_DrawArea;

void __attribute__((weak)) GUI_DummyDrawPixel (int x,int y,const __Pixel_t pixData){
// IF U DONT GIVE ME A PEN, HOW CAN I DRAW !?
}
void (*GUI_API_DrawPixel)                     (int x ,int y ,const __Pixel_t pixData)          = GUI_DummyDrawPixel;

void __attribute__((weak)) GUI_AsserParam     (bool expression,const char* WHAT_IS_WRONG){
// DONT KEEP MY MOTH SHUT, I GOT A PROBLEM TO REPORT.
}
void (*GUI_API_AssertParam)                   (bool expression,const char* WHAT_IS_WRONG)      = GUI_AsserParam;

void __attribute__((weak)) GUI_Delay          (unsigned long ms){
    ms*=1000;
    while(ms--){}
}
void (*GUI_API_DelayMs)                       (unsigned long ms)                               = GUI_Delay;

#define M_SCREEN_MAIN   0
#define M_SCREEN_CNT    1


typedef __Stack_t    __LINK_AreaRefreash;
typedef __LinkLoop_t __LINK_WindowCFG;

#pragma pack(1)
static struct{
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH>>3 ][ GUI_X_WIDTH ];
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH ][ GUI_X_WIDTH ];
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH ][ GUI_X_WIDTH ];
#endif
    size_t           allocated_byte;

    bool             autoDisplay;

    __LINK_AreaRefreash*     areaNeedRefreashHead;
    size_t                   areaNeedRefreashCnt;
    size_t                   areaNeedRefreashPixelCnt;
    
#if GUI_WINDOW_DISPLAY
    __LINK_WindowCFG*        windowCFG;
#endif
}Screen;

static __GraphInfo_t info_MainScreen = {
    .height = GUI_Y_WIDTH ,
    .width  = GUI_X_WIDTH ,
    .pBuffer = Screen.GRAM[M_SCREEN_MAIN][0]
};

void RH_PREMAIN GUI_Init(void){

    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        memset( Screen.GRAM , 0, M_SCREEN_CNT*(GUI_Y_WIDTH>>3)*GUI_X_WIDTH*sizeof(__Pixel_t) );
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        memset( Screen.GRAM , 0, M_SCREEN_CNT*(GUI_Y_WIDTH>>3)*GUI_X_WIDTH*sizeof(__Pixel_t) );
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        memset( Screen.GRAM , 0, M_SCREEN_CNT*GUI_Y_WIDTH*GUI_X_WIDTH*sizeof(__Pixel_t) );
    #endif

    Screen.autoDisplay = false;

    Screen.allocated_byte = 0;
    Screen.areaNeedRefreashHead = __Stack_createBase( NULL );
    Screen.areaNeedRefreashCnt      = 0;
    Screen.areaNeedRefreashPixelCnt = 0;

    Screen.windowCFG = NULL;

    __Graph_init();
    __Font_init();
}

void GUI_RefreashScreenArea( int xs,int ys,int xe,int ye ){
    
    if(GUI_API_DrawArea != NULL){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        const int x_width = xe-xs+1;
        const int ps      = ys>>3;
        const int pe      = ye>>3;
        const int p_width = (pe-ps+1);
        __Pixel_t* p = (__Pixel_t*)malloc((x_width)*(p_width)*sizeof(__Pixel_t));
        
       (*GUI_API_DrawArea)( xs , ys , xe , ye ,
                           __memgrab_Area(p, Screen.GRAM[M_SCREEN_MAIN][0] ,\
                                             sizeof(__Pixel_t)             ,\
                                             GUI_X_WIDTH                   ,\
                                             xs, ps, xe, pe                ) );
//#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
//        RH_ASSERT(false);
//#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
#else
        const int x_width = xe-xs+1;
        const int y_width = ye-ys+1;
        __Pixel_t* p = (__Pixel_t*)RH_MALLOC((x_width)*(y_width)*sizeof(__Pixel_t));
		(*GUI_API_DrawArea)( xs , ys , xe , ye ,
                            __memgrab_Area(p, Screen.GRAM[M_SCREEN_MAIN][0] ,\
                                              sizeof(__Pixel_t)             ,\
                                              GUI_X_WIDTH                   ,\
                                              xs, ys, xe, ye                ) );
#endif
        RH_FREE(p);
    }
    else{
        
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*GUI_API_DrawPixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y>>3][x].data);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        RH_ASSERT(false);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*GUI_API_DrawPixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y][x].data);
#endif
    }

}

void GUI_RefreashScreen(void){
    __exit( Screen.areaNeedRefreashHead == NULL );
    __Area_t *p = NULL;
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        GUI_RefreashScreenArea( 0, 0, GUI_X_WIDTH-1, GUI_Y_WIDTH-1 );
        while( !__Stack_empty( Screen.areaNeedRefreashHead ) ){
            p = __Stack_pop( Screen.areaNeedRefreashHead );
            RH_FREE(p);
        }
    }else{
        while( !__Stack_empty( Screen.areaNeedRefreashHead ) ){
            p = __Stack_pop( Screen.areaNeedRefreashHead );
            GUI_RefreashScreenArea( (int)(p->xs)             ,\
                                    (int)(p->ys)             ,\
                                    (int)(p->xs+p->width-1)  ,\
                                    (int)(p->ys+p->height-1) );
            RH_FREE(p);
        }
    }
    Screen.areaNeedRefreashPixelCnt = 0;
}

void GUI_AddScreenArea( int xs,int ys,int xe,int ye ){
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        __Area_t *p = NULL;
        while( !__Stack_empty( Screen.areaNeedRefreashHead ) ){
            p = __Stack_pop( Screen.areaNeedRefreashHead );
            RH_FREE(p);
        }
        return;
    }
    
    __Area_t* pArea = (__Area_t*)RH_MALLOC( sizeof(__Area_t) );
    pArea->xs      = xs;
    pArea->ys      = ys;
    pArea->width   = xe-xs+1;
    pArea->height  = ye-ys+1;
    Screen.areaNeedRefreashPixelCnt += pArea->width*pArea->height;
    __Stack_push( Screen.areaNeedRefreashHead, (void*)pArea );
}

void GUI_set_penSize        ( size_t    penSize  ){
    __Graph_set_penSize(penSize);
}

void GUI_set_penColor       ( __Pixel_t penColor ){
    __Graph_set_penColor(penColor);
}


void GUI_rect_raw( int xs,int ys,int xe,int ye ){
#ifdef RH_DEBUG
#endif
    __Graph_rect_raw( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_rect_edged( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    __Graph_rect_edged( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_rect_fill( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    __Graph_rect_fill( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_rect_round( int xs, int ys, int xe, int ye ){
#ifdef RH_DEBUG
#endif
    __Graph_rect_round( xs, ys, xe, ye, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_raw         ( int x ,int y ,int d ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    __Graph_circle_raw( x, y, d, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_edged       ( int x ,int y ,int d ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    __Graph_circle_edged( x, y, d, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_fill         ( int x, int y, int d ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-(d>>1)-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+(d>>1)+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-(d>>1)-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+(d>>1)+1), 0, GUI_Y_WIDTH-1 );
    __Graph_circle_fill( x, y, d, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt1 (int x ,int y ,int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    __Graph_circle_qrt1( x, y, r, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt2 (int x ,int y ,int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y-r-1), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    __Graph_circle_qrt2( x, y, r, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt3 (int x ,int y ,int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x-r-1), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+r+1), 0, GUI_Y_WIDTH-1 );
    __Graph_circle_qrt3( x, y, r, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

void GUI_circle_qrt4 (int x ,int y ,int r ){
#ifdef RH_DEBUG
#endif
    int xs = __limit( (x    ), 0, GUI_X_WIDTH-1 );
    int xe = __limit( (x+r+1), 0, GUI_X_WIDTH-1 );
    int ys = __limit( (y    ), 0, GUI_Y_WIDTH-1 );
    int ye = __limit( (y+r+1), 0, GUI_Y_WIDTH-1 );
    __Graph_circle_qrt4( x, y, r, &info_MainScreen, kApplyPixel_fill );
    Screen.autoDisplay ? GUI_RefreashScreenArea(xs, ys, xe, ye) : GUI_AddScreenArea(xs, ys, xe, ye);
}

static void __gui_insert_object_text( const __GUI_Object_t* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config->font < kGUI_NUM_FontStyle );
    RH_ASSERT( config->text );
#endif
    
    __GraphInfo_t info = {
        .pBuffer = Screen.GRAM[M_SCREEN_MAIN][0]  ,
        .height  = GUI_Y_WIDTH                    ,
        .width   = GUI_X_WIDTH                    ,
    };
    
    size_t cnt=0, w=0,w_tmp=0;
    do{
        __Font_getCharSize(&w_tmp,NULL,config->text[cnt++]);
        w+=w_tmp;
    }while(  cnt<strlen(config->text) && w<config->area.width);
    cnt--;
    
    char* p = NULL;
    if(cnt>0){
        p = alloca( cnt+sizeof('\0') );
        strncpy(p, config->text, cnt);
        __GUI_Font_t* pF = __Font_exportStr(p);
    #ifdef RH_DEBUG
        RH_ASSERT( pF );
        RH_ASSERT( pF->width < config->area.width );
    #endif
        
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        RH_ASSERT(0);
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        for( int y=0; y<pF->height&&y<config->area.height; y++ ){
            for( int x=0; x<pF->width; x++ ){
                if( pF->output[y*pF->width+x] > 128 ){
                    info.pBuffer[ (config->area.ys+y)*(info.width)+(config->area.xs+x) ].data = config->color;
                }
            }
        }
         
    #endif
        
    }
    
}

static void __gui_remove_object_text( const __GUI_Object_t* config ){
    
}

#ifdef RH_DEBUG
static inline void __gui_check_object(const __GUI_Object_t* config){
    RH_ASSERT( config );
    RH_ASSERT( config->min   <= config->max       );
    RH_ASSERT( config->style <  NUM_kGUI_ObjStyle );
    RH_ASSERT( config->area.xs + config->area.width  -1  < GUI_X_WIDTH   ); // Can be compromised, no need to abort the program.
    RH_ASSERT( config->area.ys + config->area.height -1  < GUI_Y_WIDTH   ); // Can be compromised, no need to abort the program.
}
#endif

ID_t RH_RESULT    GUI_object_create    ( const __GUI_Object_t* config ){
    __GUI_Object_t* m_config = (__GUI_Object_t*)RH_MALLOC( sizeof(__GUI_Object_t) );
#ifdef RH_DEBUG
    RH_ASSERT( m_config );
    RH_ASSERT( config );
    __gui_check_object(config);
#endif
    *m_config = *config;
    
    switch( m_config->style ){
        case kGUI_ObjStyle_text:
            m_config->insert_func = __gui_insert_object_text;
            m_config->remove_func = __gui_remove_object_text;
            __gui_insert_object_text(config);
            break;
        case kGUI_ObjStyle_num:
            
            break;
        default:
            RH_ASSERT(0);
    }
    
    return (ID_t)m_config;
}

__GUI_Object_t*   GUI_object_quickSet  (       __GUI_Object_t* config ){
    return NULL;
}

E_Status_t        GUI_object_show      ( ID_t ID ){
    __GUI_Object_t* config = (__GUI_Object_t*)ID;
    Screen.autoDisplay ? GUI_RefreashScreenArea(config->area.xs, config->area.ys, config->area.xs+config->area.width-1, config->area.ys+config->area.height-1) :\
                         GUI_AddScreenArea(config->area.xs, config->area.ys, config->area.xs+config->area.width-1, config->area.ys+config->area.height-1);
    return kStatus_Success;
}


#if GUI_WINDOW_DISPLAY

static void __gui_insert_window_MacOS(__GUI_Window_t* config){
#ifdef RH_DEBUG
    RH_ASSERT( config );

#else
    __exit( !config );
#endif
    
    const int xs = config->area.xs;
    const int ys = config->area.ys;
    const int xe = (int)(xs + config->area.width -1);
    const int ye = (int)(ys + config->area.height-1);
    const int bar_size   = __limit( (int)(config->size), 5, 256 );//38
    const int bar_size_2 = bar_size>>1;
    const int bar_size_4 = bar_size>>2;
    const int bar_rad    = __limit( (int)(config->size), 5, 256 )/5;
    const int bar_edge   = config->win_edge;
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    
    const __PixelUnit_t color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_BLACK    ):( M_COLOR_WHITE  )};
    const __PixelUnit_t color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
    const __PixelUnit_t color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_BLACK    ):( M_COLOR_WHITE  )};
    const __PixelUnit_t color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
#else
    const __PixelUnit_t color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_DARKGRAY ):( M_COLOR_SILVER )};
    const __PixelUnit_t color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
    const __PixelUnit_t color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_COAL     ):( M_COLOR_WHITE  )};    
    const __PixelUnit_t color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
#endif    
    
    __Graph_backup_config();
    __Font_backup_config();
    
    __GraphInfo_t info = {
        .pBuffer = Screen.GRAM[M_SCREEN_MAIN][0]  ,
        .height  = GUI_Y_WIDTH                    ,
        .width   = GUI_X_WIDTH                    ,
    };
    
    // Window Bar
    __Graph_set_penColor(color_bar.data);
    __Graph_set_penSize(bar_rad);
    __Graph_rect_round   (xs   , ys         , xe  , ys+bar_size+bar_rad, &info, kApplyPixel_fill);
    
    __Graph_line_raw     (xs   , ye         , xe  , ye                 , &info, kApplyPixel_fill);
    __Graph_line_raw     (xs   , ye-1       , xe  , ye-1               , &info, kApplyPixel_fill);
    
    for(int i=0; i<bar_edge; i++){
        __Graph_line_raw     (xs+i , ys+bar_size, xs+i, ye  , &info, kApplyPixel_fill);
        __Graph_line_raw     (xe-i , ys+bar_size, xe-i, ye  , &info, kApplyPixel_fill);
    }
    
    // Title
    if( config->title != NULL ){
        __Font_setSize( (int)(config->size>>1) );
        __Font_setStyle( config->title_font );
        __GUI_Font_t* pFontInfo = __Font_exportStr( config->title );
        const int font_xs = __mid(xs,xe)-(int)((pFontInfo->width)>>1);
        const int font_ys = ys + bar_size_4;
        
        
        for( int y=0; y<pFontInfo->height; y++ ){
            for( int x=0; x<pFontInfo->width; x++ ){
                uint8_t pixWeight = pFontInfo->output[ y*pFontInfo->width +x ];
                
            #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                if( pixWeight ){
                    const size_t  index    = ((y+font_ys)>>3)*info.width + (x+font_xs);
                    const size_t  offset   = (y+font_ys)%8;
                    if( color_title.data == 0 )
                        info.pBuffer[ index ].data = __BIT_CLR(info.pBuffer[ index ].data, offset);
                    else
                        info.pBuffer[ index ].data = __BIT_SET(info.pBuffer[ index ].data, offset);
                }

            #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                if( pixWeight != 0 ){
                    const size_t  index     = (y+font_ys)*info.width + (x+font_xs);
                    info.pBuffer[ index ].R = info.pBuffer[ index ].R + (( (color_title.R - info.pBuffer[ index ].R) * pixWeight )>>8);
                    info.pBuffer[ index ].G = info.pBuffer[ index ].G + (( (color_title.G - info.pBuffer[ index ].G) * pixWeight )>>8);
                    info.pBuffer[ index ].B = info.pBuffer[ index ].B + (( (color_title.B - info.pBuffer[ index ].B) * pixWeight )>>8);
                }
            #else
              #error "[RH_graphic]: Unknown color type."
            #endif
                
            }
        }
    }
    
    // Context
    __Graph_set_penColor(color_blank.data);
    __Graph_rect_fill    (xs+bar_edge , ys+bar_size, xe-bar_edge, ye-bar_edge, &info, kApplyPixel_fill);
    
    
    if( config->text != NULL ){
        uint8_t*             pIterFont = ((uint8_t*)config->text_bitMap) + (config->text_rs*config->text_bitW);
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        typeof(info.pBuffer) pIterScr  = &info.pBuffer[ ((ys+bar_size)>>3)*info.width + xs+bar_edge+config->text_margin ];
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
            pIterScr += ((y+1)%8==0)*info.width;
        }
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        typeof(info.pBuffer) pIterScr  = &info.pBuffer[ (ys+bar_size)*info.width + xs+bar_edge+config->text_margin ];
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
            pIterScr += info.width;
        }
    
    #else
      #error "[RH_graphic]: Unknown color type."
    #endif
    
    }
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    const __PixelUnit_t color_button_cl = {.data = 0x00};
    const __PixelUnit_t color_button_zm = {.data = 0x00};
    const __PixelUnit_t color_button_mi = {.data = 0x00};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    const __PixelUnit_t color_button_cl = {.data = M_COLOR_BLOODYMEAT };
    const __PixelUnit_t color_button_zm = {.data = M_COLOR_GOLDEN     };
    const __PixelUnit_t color_button_mi = {.data = M_COLOR_LAWNGREEN  };
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    const __PixelUnit_t color_button_cl = {.data = M_COLOR_BLOODYMEAT };
    const __PixelUnit_t color_button_zm = {.data = M_COLOR_GOLDEN     };
    const __PixelUnit_t color_button_mi = {.data = M_COLOR_LAWNGREEN  };
#else
  #error "[RH_graphic]: Unknown color type."
#endif
    // Button
    __Graph_set_penColor(color_button_cl.data);
    __Graph_circle_fill  (xs+bar_size_2, __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);

    __Graph_set_penColor(color_button_zm.data);
    __Graph_circle_fill  (xs+bar_size+bar_size_4, __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);

    __Graph_set_penColor(color_button_mi.data);
    __Graph_circle_fill  (xs+(bar_size<<1), __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);
    
    __Graph_restore_config();
    __Font_restore_config();

}

static void __gui_insert_window_Win10(__GUI_Window_t* config){
#ifdef RH_DEBUG
    RH_ASSERT(config);
#else
    __exit( !config );
#endif
    
    const int xs = config->area.xs;
    const int ys = config->area.ys;
    const int xe = (int)(xs + config->area.width -1);
    const int ye = (int)(ys + config->area.height-1);
    const int bar_size   = __limit( (int)((config->size<<1)/3), 10, 256 );//38
    const int bar_size_2 = bar_size>>1;
    const int bar_edge   = config->win_edge;
    
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    const __PixelUnit_t color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_DARKGRAY ):( M_COLOR_SILVER )};
    const __PixelUnit_t color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
    const __PixelUnit_t color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_COAL     ):( M_COLOR_WHITE  )};
    const __PixelUnit_t color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    const __PixelUnit_t color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_DARKGRAY ):( M_COLOR_SILVER )};
//    const __PixelUnit_t color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
    const __PixelUnit_t color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_COAL     ):( M_COLOR_WHITE  )};
    const __PixelUnit_t color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
#endif
    __GraphInfo_t info = {
        .pBuffer = Screen.GRAM[M_SCREEN_MAIN][0]  ,
        .height  = GUI_Y_WIDTH                    ,
        .width   = GUI_X_WIDTH                    ,
    };
    
    __Graph_backup_config();
    __Font_backup_config();
    
    __Graph_set_penColor (color_bar.data);
    __Graph_rect_fill    ( xs, ys, xe, ys+bar_size, &info, kApplyPixel_fill );
    
        
    for(int i=0; i<bar_edge; i++){
        __Graph_line_raw     (xs+i , ys+bar_size, xs+i, ye  , &info, kApplyPixel_fill);
        __Graph_line_raw     (xe-i , ys+bar_size, xe-i, ye  , &info, kApplyPixel_fill);
        __Graph_line_raw     (xs   , ye-i       , xe  , ye-i, &info, kApplyPixel_fill);
    }
    
    // Context
    __Graph_set_penColor (color_blank.data);
    __Graph_rect_fill    (xs+bar_edge , ys+bar_size, xe-bar_edge, ye-bar_edge, &info, kApplyPixel_fill);
    
    if( config->text != NULL ){
        uint8_t*             pIterFont = ((uint8_t*)config->text_bitMap) + (config->text_rs*config->text_bitW);
        typeof(info.pBuffer) pIterScr  = &info.pBuffer[ (ys+bar_size)*info.width + xs+bar_edge+config->text_margin ];
        
        size_t               numOfFontPix = config->text_bitH*config->text_bitW;
        size_t               cntOfFontPix = 0;
        for( int y=ys+bar_size; y<ye-2; y++, pIterScr+=info.width ){
            for( int x=0; x<config->text_bitW; x++, pIterFont++, pIterScr++ ){
                if( *pIterFont != 0x00 ){
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
                    RH_ASSERT(false);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 ) || ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
                    
                    pIterScr->R = pIterScr->R + (( (color_text.R - pIterScr->R) * (*pIterFont) )>>8);
                    pIterScr->G = pIterScr->G + (( (color_text.G - pIterScr->G) * (*pIterFont) )>>8);
                    pIterScr->B = pIterScr->B + (( (color_text.B - pIterScr->B) * (*pIterFont) )>>8);
#else
  #error "[RH_graphic]: Unknown color type."
#endif
                }
                cntOfFontPix++;
            }
            if(cntOfFontPix == numOfFontPix)
                break;
            pIterScr -= config->text_bitW;
        }
    }
    
    // Button
    const int button_w = bar_size_2*3;
    const int button_h = bar_size;
    const int button_cl_xs = xe-button_w+1, button_zm_xs = button_cl_xs-button_w, button_mi_xs = button_zm_xs-button_w;
    const int button_cl_ys = ys           , button_zm_ys = ys                   , button_mi_ys = ys;
    const int button_cl_xe = xe           , button_zm_xe = button_cl_xe-button_w, button_mi_xe = button_zm_xe-button_w;
    const int button_cl_ye = ys+button_h-1, button_zm_ye = button_cl_ye         , button_mi_ye = button_cl_ye;
    
    __Graph_set_penColor(color_bar.data);
    __Graph_rect_fill   ( button_cl_xs, button_cl_ys, button_cl_xe, button_cl_ye, &info, kApplyPixel_fill );
    {
        int xs = __mid(button_cl_xs,button_cl_xe)-(button_h>>3);
        int ys = __mid(button_cl_ys,button_cl_ye)-(button_h>>3);
        int xe = __mid(button_cl_xs,button_cl_xe)+(button_h>>3);
        int ye = __mid(button_cl_ys,button_cl_ye)+(button_h>>3);
        __Graph_set_penColor(M_COLOR_WHITE);
        __Graph_line_raw( xs, ys, xe, ye, &info, kApplyPixel_fill);
        __Graph_line_raw( xs, ye, xe, ys, &info, kApplyPixel_fill);
    }
    
    __Graph_set_penColor(color_bar.data);
    __Graph_rect_fill   ( button_zm_xs, button_zm_ys, button_zm_xe, button_zm_ye, &info, kApplyPixel_fill );
    {
        int xs = __mid(button_zm_xs,button_zm_xe)-(button_h>>3);
        int ys = __mid(button_zm_ys,button_zm_ye)-(button_h>>3);
        int xe = __mid(button_zm_xs,button_zm_xe)+(button_h>>3);
        int ye = __mid(button_zm_ys,button_zm_ye)+(button_h>>3);
        __Graph_set_penColor(M_COLOR_WHITE);
        __Graph_rect_raw( xs, ys, xe, ye, &info, kApplyPixel_fill);
    }
    
    __Graph_set_penColor(color_bar.data);
    __Graph_rect_fill   ( button_mi_xs, button_mi_ys, button_mi_xe, button_mi_ye, &info, kApplyPixel_fill );
    {
        int xs = __mid(button_mi_xs,button_mi_xe)-(button_h>>3);
        int ys = __mid(button_mi_ys,button_mi_ye);
        int xe = __mid(button_mi_xs,button_mi_xe)+(button_h>>3);
        int ye = ys;
        __Graph_set_penColor(M_COLOR_WHITE);
        __Graph_line_raw( xs, ys, xe, ye, &info, kApplyPixel_fill);
    }
    
    __Graph_restore_config();
    __Font_restore_config();
}

static void __gui_remove_window_MacOS(__GUI_Window_t* config){
    
}

static void __gui_remove_window_Win10(__GUI_Window_t* config){}

#ifdef RH_DEBUG
static inline void __gui_check_window(const __GUI_Window_t* config){
    RH_ASSERT( config->size      > 5                   );  /* Too small */
    RH_ASSERT( config->text_size > 5                   );  /* Too small */
    RH_ASSERT( config->type      < NUM_kGUI_WindowType );  /* Wrong enumeration reference */
    
}
#endif

ID_t GUI_window_create( const __GUI_Window_t* config ){
    __GUI_Window_t* m_config = (__GUI_Window_t*)RH_MALLOC( sizeof(__GUI_Window_t) );

    __Font_backup_config();
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
        __Font_setStyle(m_config->text_font);
        __Font_setSize(m_config->text_size);
        __SET_STRUCT_MB(__GUI_Window_t, int  , m_config, text_margin, 5        );

        size_t fontW = m_config->area.width-((m_config->win_edge+m_config->text_margin)<<1);
        __GUI_Font_t* p =  __Font_exportText_Justify( m_config->text, fontW );
        __SET_STRUCT_MB(__GUI_Window_t, void*, m_config, text_bitMap, RH_MALLOC(p->width*p->height*sizeof(*(p->output))));
#ifdef RH_DEBUG
        RH_ASSERT( m_config->text_bitMap );
#endif
        memcpy((void*)m_config->text_bitMap, p->output, p->width*p->height*sizeof(*(p->output)) );

        __SET_STRUCT_MB(__GUI_Window_t, void*, m_config, text_bitH  , p->height);
        __SET_STRUCT_MB(__GUI_Window_t, void*, m_config, text_bitW  , p->width );
        //...//
    }
    
    if( Screen.windowCFG==NULL )
        Screen.windowCFG = __LINK_Loop_createHead( m_config );
    else
        __LINK_Loop_add( Screen.windowCFG, m_config );
    
    __Font_restore_config();
    return (ID_t)m_config;
}

__GUI_Window_t* GUI_window_quickSet( __GUI_Window_t* config ){
#ifdef RH_DEBUG
    RH_ASSERT( config );
#else
    __exitReturn( !config, NULL);
#endif
    
    config->area.xs      = 0;
    config->area.ys      = 0;
    config->area.height  = 0;
    config->area.width   = 0;
    config->type         = kGUI_WindowType_macOS;
    config->appearance   = kGUI_Appearance_Light;
    config->size         = 40;
    config->title        = NULL;
    config->title_font   = kGUI_FontStyle_ArialRounded_Bold;
    config->text         = NULL;
    config->text_font    = kGUI_FontStyle_ArialRounded_Bold;
    config->text_align   = kGUI_FontAlign_Justify;
    config->text_size    = 40;
    
    __SET_STRUCT_MB(__GUI_Window_t, int   , config, text_rs    , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, void* , config, text_bitMap, NULL );
    __SET_STRUCT_MB(__GUI_Window_t, size_t, config, text_bitH  , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, size_t, config, text_bitW  , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, int   , config, text_margin, 0    );
    return config;
}

E_Status_t GUI_window_insert( ID_t ID ){
    __LINK_WindowCFG* pCFG = __LINK_Loop_find( Screen.windowCFG, (void*)ID );

    __exitReturn( !pCFG, kStatus_NotFound );
    
    (*((__GUI_Window_t*)ID)->insert_func)( (__GUI_Window_t*)ID );
    if( Screen.autoDisplay ){
        
    }else{
        GUI_AddScreenArea(      ((__GUI_Window_t*)ID)->area.xs ,\
                                ((__GUI_Window_t*)ID)->area.ys ,\
                          (int)(((__GUI_Window_t*)ID)->area.xs +  ((__GUI_Window_t*)ID)->area.width -1),\
                          (int)(((__GUI_Window_t*)ID)->area.ys +  ((__GUI_Window_t*)ID)->area.height-1));
    }
    return kStatus_Success;
}

E_Status_t GUI_window_delete( ID_t ID ){
    __LINK_WindowCFG* pCFG = __LINK_Loop_find( Screen.windowCFG, (void*)ID );
    __exitReturn( !pCFG, kStatus_NotFound );
    
    __LINK_Loop_remove( Screen.windowCFG, (void*)ID );
    RH_FREE((void*)ID);
    return kStatus_Success;
}

#endif



