


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
#define M_SCREEN_CNT    3




#if GUI_WINDOW_DISPLAY
struct __GUI_INT_Window_t{
    struct __GUI_Window_t config;
    void (*insert_func)(__GUI_Window_t*);
    void (*remove_func)(__GUI_Window_t*);
};
typedef struct __GUI_INT_Window_t __GUI_INT_Window_t;
#endif

typedef __Stack_t    __LINK_AreaRefreash;
typedef __LinkLoop_t __LINK_WindowCFG;

static struct{
    __PixelUnit_t GRAM[M_SCREEN_CNT][ GUI_Y_WIDTH][ GUI_X_WIDTH ];
    size_t           allocated_byte;

    bool             autoDisplay;

    __LINK_AreaRefreash*     areaNeedRefreashHead;
    size_t                   areaNeedRefreashCnt;
    size_t                   areaNeedRefreashPixelCnt;
    
#if GUI_WINDOW_DISPLAY
    __LINK_WindowCFG*        windowCFG;
#endif
}Screen;

static void __attribute__((constructor)) GUI_Init(void){
    memset( Screen.GRAM , 0, M_SCREEN_CNT*GUI_Y_WIDTH*GUI_X_WIDTH*sizeof(__Pixel_t) );
    
    Screen.autoDisplay = false;
    
    Screen.allocated_byte = 0;
    Screen.areaNeedRefreashHead = __Stack_createBase( NULL );
    Screen.areaNeedRefreashCnt      = 0;
    Screen.areaNeedRefreashPixelCnt = 0;
    
    Screen.windowCFG = NULL;
}

void GUI_RefreashScreenArea( int xs,int ys,int xe,int ye ){
//    printf("[%d,%d] -> [%d,%d]\n",xs,ys,xe,ye);
    int x_width = xe-xs+1;
    int y_width = ye-ys+1;
    if(GUI_API_DrawArea != NULL){
        __Pixel_t* p = (__Pixel_t*)__malloc((x_width)*(y_width)*sizeof(__Pixel_t));
        (*GUI_API_DrawArea)( xs , ys , xe , ye ,
                            __memgrab_Area(p, Screen.GRAM[M_SCREEN_MAIN][0] ,\
                                              sizeof(__Pixel_t)             ,\
                                              GUI_X_WIDTH                   ,\
                                              xs, ys, xe, ye                ) );
        __free(p);
    }
    else{
        for(int y=ys;y<=ye;y++)
            for(int x=xs;x<=xe;x++)
                (*GUI_API_DrawPixel)(x,y,Screen.GRAM[M_SCREEN_MAIN][y][x].data);
    }
}

void GUI_RefreashScreen(void){
    __exit( Screen.areaNeedRefreashHead == NULL );
    __Area_t *p = NULL;
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        GUI_RefreashScreenArea( 0, 0, GUI_X_WIDTH-1, GUI_Y_WIDTH-1 );
        while( !__Stack_empty( Screen.areaNeedRefreashHead ) ){
            p = __Stack_pop( Screen.areaNeedRefreashHead );
            __free(p);
        }
    }else{
        while( !__Stack_empty( Screen.areaNeedRefreashHead ) ){
            p = __Stack_pop( Screen.areaNeedRefreashHead );
            GUI_RefreashScreenArea( (int)(p->xs)             ,\
                                    (int)(p->ys)             ,\
                                    (int)(p->xs+p->width-1)  ,\
                                    (int)(p->ys+p->height-1) );
            __free(p);
        }
    }
    Screen.areaNeedRefreashPixelCnt = 0;
}

void GUI_AddScreenArea( int xs,int ys,int xe,int ye ){
    if( Screen.areaNeedRefreashPixelCnt >= GUI_X_WIDTH*GUI_Y_WIDTH ){
        __Area_t *p = NULL;
        while( !__Stack_empty( Screen.areaNeedRefreashHead ) ){
            p = __Stack_pop( Screen.areaNeedRefreashHead );
            __free(p);
        }
        return;
    }
    
    __Area_t* pArea = (__Area_t*)__malloc( sizeof(__Area_t) );
    pArea->xs      = xs;
    pArea->ys      = ys;
    pArea->width   = xe-xs+1;
    pArea->height  = ye-ys+1;
    Screen.areaNeedRefreashPixelCnt += pArea->width*pArea->height;
    __Stack_push( Screen.areaNeedRefreashHead, (void*)pArea );
}

void GUI_rect_raw( int xs,int ys,int xe,int ye ){
    __GraphInfo_t info = {
        .height = GUI_Y_WIDTH ,
        .width  = GUI_X_WIDTH ,
        .pBuffer = Screen.GRAM[M_SCREEN_MAIN][0]
    };
    
    __Graph_rect_raw(xs,ys,ys,ye,&info,kApplyPixel_fill);
    
    if( Screen.autoDisplay ){
        
    }else{
        GUI_AddScreenArea(xs, ys, xe, ye);
    }
}

#if GUI_WINDOW_DISPLAY

static void __gui_insert_window_MacOS(__GUI_Window_t* config){
#ifdef RH_DEBUG
    ASSERT( config );

#else
    __exit( !config );
#endif
    
    const int xs = config->area.xs;
    const int ys = config->area.ys;
    const int xe = (int)(xs + config->area.width -1);
    const int ye = (int)(ys + config->area.height-1);
    const int bar_size   = __limit( (int)(config->size), 10, 256 );//38
    const int bar_size_2 = bar_size>>1;
    const int bar_size_4 = bar_size>>2;
    const int bar_rad    = __limit( (int)(config->size), 5, 256 )/5;
    const int bar_edge   = config->win_edge;
    
    const __PixelUnit_t color_bar   = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_DARKGRAY ):( M_COLOR_SILVER )};
    const __PixelUnit_t color_title = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
    const __PixelUnit_t color_blank = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_COAL     ):( M_COLOR_WHITE  )};
    
    const __PixelUnit_t color_text  = {.data = (config->appearance==kGUI_Appearance_Dark)?( M_COLOR_WHITE    ):( M_COLOR_BLACK  )};
    
    
    __Graph_backup_config();
//    __Pixel_t penColor = __Graph_get_penColor();
//    size_t    penSize  = __Graph_get_penSize();
    int                fontSize = __Font_getSize();
    E_GUI_FontStyle_t fontStyle = __Font_getStyle();
    
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
        __Font_setSize(bar_size_2);
        __Font_setStyle( kGUI_FontStyle_CourierNew_Bold );
        __GUI_Font_t* pFontInfo = __Font_exportStr( config->title );
        const int font_xs = __mid(xs,xe)-(int)((pFontInfo->width)>>1);
        const int font_ys = ys + bar_size_4;
        
        
        for( int y=0; y<pFontInfo->height; y++ ){
            for( int x=0; x<pFontInfo->width; x++ ){
                uint8_t pixWeight = pFontInfo->output[ y*pFontInfo->width +x ];
                size_t  index     = (y+font_ys)*info.width + (x+font_xs);
                if( pixWeight != 0 ){
#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
                    while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )
                    while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
                    info.pBuffer[ index ].R = info.pBuffer[ index ].R + (( (color_title.R - info.pBuffer[ index ].R) * pixWeight )>>8);
                    info.pBuffer[ index ].G = info.pBuffer[ index ].G + (( (color_title.G - info.pBuffer[ index ].G) * pixWeight )>>8);
                    info.pBuffer[ index ].B = info.pBuffer[ index ].B + (( (color_title.B - info.pBuffer[ index ].B) * pixWeight )>>8);
#else
  #error "[RH_graphic]: Unknown color type."
#endif
                    
                }
            }
        }
    }
    
    // Context
    __Graph_set_penColor(color_blank.data);
    __Graph_rect_fill    (xs+bar_edge , ys+bar_size, xe-bar_edge, ye-bar_edge, &info, kApplyPixel_fill);
    
    
    if( config->text != NULL ){
        uint8_t*             pIterFont = ((uint8_t*)config->text_bitMap) + (config->text_rs*config->text_bitW);
        typeof(info.pBuffer) pIterScr  = &info.pBuffer[ (ys+bar_size)*info.width + xs+bar_edge+config->text_margin ];
        
        size_t               numOfFontPix = config->text_bitH*config->text_bitW;
        size_t               cntOfFontPix = 0;
        for( int y=ys+bar_size; y<ye-2; y++, pIterScr+=info.width ){
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
    }
    
    // Button
    __Graph_set_penColor(M_COLOR_BLOODYMEAT);
    __Graph_circle_fill  (xs+bar_size_2, __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);
    
    __Graph_set_penColor(M_COLOR_GOLDEN);
    __Graph_circle_fill  (xs+bar_size+bar_size_4, __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);
    
    __Graph_set_penColor(M_COLOR_LAWNGREEN);
    __Graph_circle_fill  (xs+(bar_size<<1), __mid(ys,ys+bar_size), bar_size_2 , &info, kApplyPixel_fill);
    
    __Graph_restore_config();
//    __Graph_set_penColor(penColor);
//    __Graph_set_penSize(penSize);
    
    __Font_setSize(fontSize);
    __Font_setStyle(fontStyle);
}

static void __gui_remove_window_MacOS(__GUI_Window_t* config){
    
}

#ifdef RH_DEBUG
static inline void __gui_check_window(__GUI_Window_t* config){
    ASSERT( config->size      > 10                  );  /* Too small */
    ASSERT( config->text_size > 5                   );  /* Too small */
    ASSERT( config->type      < NUM_kGUI_WindowType );  /* Wrong enumeration reference */
    
}
#endif

ID_t GUI_create_window( __GUI_Window_t* config ){
    __GUI_INT_Window_t* tmp = (__GUI_INT_Window_t*)__malloc( sizeof(__GUI_INT_Window_t) );
    int               font_size  = __Font_getSize();
    E_GUI_FontStyle_t font_style = __Font_getStyle();
#ifdef RH_DEBUG
    ASSERT( tmp );
    ASSERT( config );
//    __gui_check_window(config);
#endif
    memcpy(&tmp->config, config, sizeof( __GUI_Window_t ));
    
    switch( tmp->config.type ){
        case kGUI_WindowType_macOS:
            tmp->insert_func = __gui_insert_window_MacOS;
            tmp->remove_func = __gui_remove_window_MacOS;
            __SET_STRUCT_MB(__GUI_Window_t, int, &(tmp->config), win_edge  , 2);
            break;
        default:
#ifdef RH_DEBUG
            ASSERT( false );
#else
            while(1);
#endif
    }
    
    if( tmp->config.text != NULL ){
        // 配置用户配置的文本字体和大小
        __Font_setStyle(tmp->config.text_font);
        __Font_setSize(tmp->config.text_size);
        // 设置文本白边, 暂定恒为5
        __SET_STRUCT_MB(__GUI_Window_t, int  , &(tmp->config), text_margin, 5        );
        // 生成文本镜像
        size_t fontW = tmp->config.area.width-((tmp->config.win_edge+tmp->config.text_margin)<<1);
        __GUI_Font_t* p =  __Font_exportText_Justify( tmp->config.text, fontW );
        // 拷贝信息到结构体<__GUI_Window_t> config 中
        // 创建缓存, 并将p->output的文本镜像拷贝至 config->text_bitMap
        __SET_STRUCT_MB(__GUI_Window_t, void*, &(tmp->config), text_bitMap, __malloc(p->width*p->height*sizeof(*(p->output))));
#ifdef RH_DEBUG
        ASSERT(tmp->config.text_bitMap);
#endif
        memcpy((void*)tmp->config.text_bitMap, p->output, p->width*p->height*sizeof(*(p->output)) );
        // 拷贝文本镜像的长和宽
        __SET_STRUCT_MB(__GUI_Window_t, void*, &(tmp->config), text_bitH  , p->height);
        __SET_STRUCT_MB(__GUI_Window_t, void*, &(tmp->config), text_bitW  , p->width );
        //...//
    }
    
    if( Screen.windowCFG==NULL )
        Screen.windowCFG = __LINK_Loop_createHead( tmp );
    else
        __LINK_Loop_add( Screen.windowCFG, tmp );
    
    
    __Font_setStyle(font_style);
    __Font_setSize(font_size);
    return (ID_t)tmp;
}

__GUI_Window_t* GUI_easySet_window( __GUI_Window_t* config ){
#ifdef RH_DEBUG
    ASSERT( config );
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
    config->title_font   = kGUI_FontStyle_CourierNew;
    config->text         = NULL;
    config->text_font    = kGUI_FontStyle_CourierNew_Bold;
    config->text_align   = kGUI_FontAlign_Justify;
    config->text_size    = 40;
    
    __SET_STRUCT_MB(__GUI_Window_t, int   , config, text_rs    , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, void* , config, text_bitMap, NULL );
    __SET_STRUCT_MB(__GUI_Window_t, size_t, config, text_bitH  , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, size_t, config, text_bitW  , 0    );
    __SET_STRUCT_MB(__GUI_Window_t, int   , config, text_margin, 0    );
    return config;
}

E_Status_t GUI_insert_window( ID_t ID ){
    __LINK_WindowCFG* pCFG = __LINK_Loop_find( Screen.windowCFG, (void*)ID );

    __exitReturn( !pCFG, kStatus_NotFound );
    
    (*((__GUI_INT_Window_t*)ID)->insert_func)( &((__GUI_INT_Window_t*)ID)->config );
    if( Screen.autoDisplay ){
        
    }else{
        GUI_AddScreenArea(      ((__GUI_INT_Window_t*)ID)->config.area.xs ,\
                                ((__GUI_INT_Window_t*)ID)->config.area.ys ,\
                          (int)(((__GUI_INT_Window_t*)ID)->config.area.xs +      ((__GUI_INT_Window_t*)ID)->config.area.width -1),\
                          (int)(((__GUI_INT_Window_t*)ID)->config.area.ys +  ((__GUI_INT_Window_t*)ID)->config.area.height-1));
    }
    return kStatus_Success;
}

E_Status_t GUI_delete_window( ID_t ID ){
    __LINK_WindowCFG* pCFG = __LINK_Loop_find( Screen.windowCFG, (void*)ID );
    __exitReturn( !pCFG, kStatus_NotFound );
    
    __LINK_Loop_remove( Screen.windowCFG, (void*)ID );
    __free((void*)ID);
    return kStatus_Success;
}



#endif


