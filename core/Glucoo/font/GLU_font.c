
#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_truetype.h"
#include "GLU_font.h"


#define MIN_TTF_FONT_SIZE   10
/*==================================================================================================================================
 *
 * Due to the display issue that when u set the font size smaller than 10 by using the <TrueTypeFont>, the result of font image is
 * bad-quality. It has to be switched into bitmap font method. In order to maintain the API for "stb" library, so i have to create a
 * structure for switching methods and build some fake functions with the same interface as the "stb" has.
 *
 *
 ==================================================================================================================================*/

struct __Method{
    int   (* _InitFont             )
          (stbtt_fontinfo *info, const unsigned char *data, int offset);
    
    float (* _ScaleForPixelHeight  )
          (const stbtt_fontinfo *info, float height);
    
    
    void  (*_GetFontVMetrics       )
          (const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap);
    
    void  (*_GetCodepointHMetrics  )
          (const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing);
    
    void  (*_GetCodepointBitmapBox )
          (const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1);
    
    void  (*_MakeCodepointBitmap   )
          (const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint);

};
typedef struct __Method __Method;

int   rhtt_InitFont
      (stbtt_fontinfo *info, const unsigned char *data, int offset){
    
    const rhtt_fontinfo *pInfo = (const rhtt_fontinfo*)data;
    RH_ASSERT(pInfo->c == ' ');
    
    info->data = (unsigned char*)data;
          
    return 0;
}

float rhtt_ScaleForPixelHeight(const stbtt_fontinfo *info, float height){
    const rhtt_fontinfo *pInfo = (const rhtt_fontinfo*)(info->data);
#ifdef RH_DEBUG
    RH_ASSERT( pInfo );
    RH_ASSERT( pInfo->c == ' ' );
#endif
    return 1.0;
}

void  rhtt_GetFontVMetrics(const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap){
          
    const rhtt_fontinfo *pInfo = (const rhtt_fontinfo*)(info->data);
#ifdef RH_DEBUG
    RH_ASSERT( pInfo );
    RH_ASSERT( pInfo->c == ' ' );
#endif
    *ascent = 0;
    *descent = 0;
    
    
}

void  rhtt_GetCodepointHMetrics(const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing){
    // info         :  字体点阵数据
    // codepoint    :  字符, 可以为ASCII, 也可以是UNICODE, 这里仅支持ASCII
    // advanceWidth :
    
    const rhtt_fontinfo *pInfo = (const rhtt_fontinfo*)(info->data);
    pInfo += codepoint - ' ';
#ifdef RH_DEBUG
    RH_ASSERT( pInfo );
    RH_ASSERT( pInfo->c == codepoint );
#endif
    
    *advanceWidth = pInfo->w;
    *leftSideBearing = 0;
}

void  rhtt_GetCodepointBitmapBox(const stbtt_fontinfo *info, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1){
    const rhtt_fontinfo *pInfo = (const rhtt_fontinfo*)(info->data);
    RH_ASSERT(pInfo->c == ' ');
    *ix0 = 0;
    *iy0 = 0;
    *ix1 = pInfo->w;
    *iy1 = pInfo->h;
}

void  rhtt_MakeCodepointBitmap  (const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint){
    // info       :  字体点阵数据
    // output     :  输出图像地址(假设用户已做偏移),以该地址为首地址
    // out_w      :  该字符宽度
    // out_h      :  该字符高度
    // out_stride :  输出图像地址宽度
    // scale_x    :
    // scale_y    :
    // codepoint  :  字符, 可以为ASCII, 也可以是UNICODE, 这里仅支持ASCII

    const rhtt_fontinfo *pInfo = (const rhtt_fontinfo*)(info->data);
    if( !isprint(codepoint) ){
    #ifdef RH_DEBUG
        RH_ASSERT(0);
    #else
        codepoint = '?';
    #endif
    }
    pInfo += codepoint - ' ';
#ifdef RH_DEBUG
    RH_ASSERT( pInfo );
    RH_ASSERT( pInfo->c == codepoint);
    RH_ASSERT( pInfo->h == out_h    );
    RH_ASSERT( pInfo->w == out_w    );
#endif
    
    uint8_t *pData = pInfo->data;
    for( int y=0; y<pInfo->h; y+=8, output+=out_stride ){
        for( int cnt=0; cnt<8; cnt++){
            for( int x=0; x<pInfo->w; x++ ){
                *(output+x) = ((((*(pData+x))>>cnt)&0x01)==0)?(0x00):(0xff); // printf("%d\n",((((*pData)>>cnt)&0x01)==0)?(0x00):(0xff));
            }
            output+=out_stride;
        }
        pData += pInfo->w;
    }
        
    
}

#if ( RH_CFG_FONT_DATA_TYPE != RH_CFG_FONT_DATA_LOCAL_BITMAP )
static __Method stbtt = {  // Present by Sean T. Barrett  --> stb
    ._InitFont               = stbtt_InitFont,
    ._ScaleForPixelHeight    = stbtt_ScaleForPixelHeight,
    ._GetFontVMetrics        = stbtt_GetFontVMetrics,
    ._GetCodepointHMetrics   = stbtt_GetCodepointHMetrics,
    ._GetCodepointBitmapBox  = stbtt_GetCodepointBitmapBox,
    ._MakeCodepointBitmap    = stbtt_MakeCodepointBitmap
};
#endif

static __Method rhtt  = {   // Present by Randle Hemlslay  --> rh
    ._InitFont               = rhtt_InitFont,
    ._ScaleForPixelHeight    = rhtt_ScaleForPixelHeight,
    ._GetFontVMetrics        = rhtt_GetFontVMetrics,
    ._GetCodepointHMetrics   = rhtt_GetCodepointHMetrics,
    ._GetCodepointBitmapBox  = rhtt_GetCodepointBitmapBox,
    ._MakeCodepointBitmap    = rhtt_MakeCodepointBitmap
};

static struct{
    __GUI_Font_t       info;
    E_GUI_FontStyle_t  style;
    size_t             size;
    float              scale;
    
    stbtt_fontinfo     stb_info;
    const uint8_t*     font_data;
    
    __Method*          method;
    
}FCFG_copy,FCFG = {0};




#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF )
    #if defined (__WIN32)
        static const char* font_ttf_path[kGUI_NUM_FontStyle] = {
            "../Glucoo/Font/Arial Rounded Bold.ttf" ,
        #if RH_CFG_FONT_STYLE__CourierNew
            "../Glucoo/Font/Courier New.ttf"        ,
        #endif
        #if RH_CFG_FONT_STYLE__CourierNew_Italic        
            "../Glucoo/Font/Courier New Italic.ttf" ,
        #endif  
        #if RH_CFG_FONT_STYLE__CourierNew_Bold      
            "../Glucoo/Font/Courier New Bold.ttf"   ,
        #endif
        #if RH_CFG_FONT_STYLE__NewYork        
            "../Glucoo/Font/NewYork.ttf"            ,
        #endif
        #if RH_CFG_FONT_STYLE__NewYork_Italic        
            "../Glucoo/Font/NewYorkItalic.ttf"      ,
        #endif
        #if RH_CFG_FONT_STYLE__Arial_Unicode   
            "../Glucoo/Font/Arial Unicode.ttf"      
        #endif      
        };
    #elif defined  (__APPLE__)
        static const char* font_ttf_path[kGUI_NUM_FontStyle] = {
            "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Arial Rounded Bold.ttf" ,
        #if RH_CFG_FONT_STYLE__CourierNew
            "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Courier New.ttf"        ,
        #endif
        #if RH_CFG_FONT_STYLE__CourierNew_Italic        
            "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Courier New Italic.ttf" ,
        #endif  
        #if RH_CFG_FONT_STYLE__CourierNew_Bold      
            "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Courier New Bold.ttf"   ,
        #endif
        #if RH_CFG_FONT_STYLE__NewYork        
            "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/NewYork.ttf"            ,
        #endif
        #if RH_CFG_FONT_STYLE__NewYork_Italic        
            "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/NewYorkItalic.ttf"      ,
        #endif
        #if RH_CFG_FONT_STYLE__Arial_Unicode        
            "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Arial Unicode.ttf"       
        #endif
        };
    #endif

    static E_Status_t __gui_font_read( const char* path ){
        FILE* fontFile = fopen( path , "rb" );
    #ifdef RH_DEBUG
        RH_ASSERT( fontFile );
    #endif
        __exitReturn( !fontFile, MAKE_ENUM( kStatus_BadAccess ) );

        fseek(fontFile, 0, SEEK_END);
        size_t size = ftell(fontFile);
        fseek(fontFile, 0, SEEK_SET);

        if( !FCFG.font_data ){
            RH_FREE((void*)FCFG.font_data);
        }

        FCFG.font_data = RH_CALLOC(size, sizeof(uint8_t));

        fread((void*)FCFG.font_data, size, sizeof(uint8_t), fontFile);
        fclose(fontFile);

        return kStatus_Success;
    }

#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY )
    static const uint8_t* font_ttf_array[kGUI_NUM_FontStyle] = {
        (const uint8_t*)Font_TTF_ArialRoundedBold  ,
        
    #if RH_CFG_FONT_STYLE__CourierNew
        (const uint8_t*)Font_TTF_CourierNew        ,
    #endif
    #if RH_CFG_FONT_STYLE__CourierNew_Bold
        (const uint8_t*)Font_TTF_CourierNew_Bold   ,
    #endif
        
    };
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP  )

#else
  #error "Unknown font data source."
#endif

extern const rhtt_fontinfo Font_BIT_ArialRoundedBold_size_8[];

static const rhtt_fontinfo* font_bit_array[kGUI_NUM_FontStyle] = {
    Font_BIT_ArialRoundedBold_size_8  ,
    
#if RH_CFG_FONT_STYLE__CourierNew
//    (const uint8_t*)Font_TTF_CourierNew        ,
#endif
#if RH_CFG_FONT_STYLE__CourierNew_Bold
//    (const uint8_t*)Font_TTF_CourierNew_Bold   ,
#endif
};





void  RH_PREMAIN __Font_init(void){
    
    FCFG.style     = kGUI_FontStyle_ArialRounded_Bold;
    FCFG.size      = 24;
    
#if    ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )
    FCFG.method = &rhtt;
    FCFG.font_data = (const uint8_t*)font_bit_array[ FCFG.style ];
#else
    if( FCFG.size <= MIN_TTF_FONT_SIZE ){
        FCFG.method = &rhtt;
        FCFG.font_data = (const uint8_t*)font_bit_array[ FCFG.style ];
    }else{
        FCFG.method    = &stbtt;
        FCFG.font_data = (const uint8_t*)font_ttf_array[ FCFG.style ];
    }
#endif
    
    (*FCFG.method->_InitFont)(&FCFG.stb_info, FCFG.font_data, 0);
    
    FCFG.scale        = (*FCFG.method->_ScaleForPixelHeight)( &FCFG.stb_info, FCFG.size );
    (*FCFG.method->_GetFontVMetrics)( &FCFG.stb_info, &FCFG.info.ascent, &FCFG.info.descent, &FCFG.info.lineGap );

    FCFG.info.ascent  = roundf( FCFG.info.ascent  * FCFG.scale );
    FCFG.info.descent = roundf( FCFG.info.descent * FCFG.scale );
    
    memcpy(&FCFG_copy, &FCFG, sizeof(FCFG_copy));
}



void __Font_setStyle(E_GUI_FontStyle_t style){
    
#if    ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )
    FCFG.method = &rhtt;
#else
    ( FCFG.size < MIN_TTF_FONT_SIZE )? (FCFG.method = &rhtt) : (FCFG.method = &stbtt);
#endif
    
    switch(style){
        case kGUI_FontStyle_ArialRounded_Bold:
    #if RH_CFG_FONT_STYLE__CourierNew
        case kGUI_FontStyle_CourierNew:
    #endif
    #if RH_CFG_FONT_STYLE__CourierNew_Italic
        case kGUI_FontStyle_CourierNew_Italic:
    #endif
    #if RH_CFG_FONT_STYLE__CourierNew_Bold
        case kGUI_FontStyle_CourierNew_Bold:
    #endif
    #if RH_CFG_FONT_STYLE__NewYork
        case kGUI_FontStyle_NewYork:
    #endif
    #if RH_CFG_FONT_STYLE__NewYork_Italic
        case kGUI_FontStyle_NewYork_Italic:
    #endif
    #if RH_CFG_FONT_STYLE__Arial_Unicode
        case kGUI_FontStyle_Arial_Unicode:
    #endif
            
#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF   )
            if( FCFG.method==&stbtt )
                __gui_font_read( font_ttf_path[style] );
            if( FCFG.method==&rhtt )
                FCFG.font_data = (const uint8_t*)font_bit_array[ style ];
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY  )
            if( FCFG.method==&stbtt )
                FCFG.font_data = (const uint8_t*)font_ttf_array[ style ];
            if( FCFG.method==&rhtt )
                FCFG.font_data = (const uint8_t*)font_bit_array[ style ];
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )
            FCFG.font_data = (const uint8_t*)font_bit_array[ style ];
#else
  #error "Unknown font data source."
#endif
            (*FCFG.method->_InitFont)(&FCFG.stb_info, FCFG.font_data, 0);
            break;
        default:
            return;
    }
    FCFG.style        = style;
    FCFG.scale        = (*FCFG.method->_ScaleForPixelHeight)( &FCFG.stb_info, FCFG.size );
    (*FCFG.method->_GetFontVMetrics)( &FCFG.stb_info, &FCFG.info.ascent, &FCFG.info.descent, &FCFG.info.lineGap );
    FCFG.info.ascent  = roundf(FCFG.info.ascent * FCFG.scale);
    FCFG.info.descent = roundf(FCFG.info.descent * FCFG.scale);
}

void __Font_setSize(size_t size){
#if ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )
    FCFG.size = 8;
    FCFG.method = &rhtt;
    __Font_setStyle(FCFG.style);
#else
    if      ( size <= MIN_TTF_FONT_SIZE && FCFG.size >  MIN_TTF_FONT_SIZE ){
        FCFG.size = 8;
        FCFG.method = &rhtt;
        __Font_setStyle(FCFG.style);
    }else if( size >  MIN_TTF_FONT_SIZE && FCFG.size <= MIN_TTF_FONT_SIZE ){
        FCFG.size = size;
        FCFG.method = &stbtt;
        __Font_setStyle(FCFG.style);
    }else{
        FCFG.size = size;
    }
#endif
    

    FCFG.scale       = (*FCFG.method->_ScaleForPixelHeight)( &FCFG.stb_info, FCFG.size );
    (*FCFG.method->_GetFontVMetrics)( &FCFG.stb_info, &FCFG.info.ascent, &FCFG.info.descent, &FCFG.info.lineGap );
    FCFG.info.ascent  = roundf(FCFG.info.ascent * FCFG.scale);
    FCFG.info.descent = roundf(FCFG.info.descent * FCFG.scale);
}

size_t __Font_getSize(void){
    return FCFG.size;
}

E_GUI_FontStyle_t __Font_getStyle(void){
    return FCFG.style;
}

#if RH_CFG_OUTPUT_FONT_PNG
#define STB_OUTPUT_FONT_PNG
#endif

#ifdef STB_OUTPUT_FONT_PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif
__GUI_Font_t*  __Font_exportChar(uint16_t unicode){
    int c_x1 , c_y1 , c_x2 , c_y2;
    (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, unicode, FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
    FCFG.info.height = c_y2-c_y1;
    FCFG.info.width  = c_x2-c_x1;
    
    if( FCFG.info.output ){
        RH_FREE(FCFG.info.output);
        FCFG.info.output = NULL;
    }
    FCFG.info.output = RH_CALLOC( FCFG.info.height*FCFG.info.width , sizeof(uint8_t) );
    
    (*FCFG.method->_MakeCodepointBitmap)( &FCFG.stb_info, FCFG.info.output, (int)FCFG.info.width, (int)FCFG.info.height, (int)FCFG.info.width, FCFG.scale, FCFG.scale, unicode );
#ifdef STB_OUTPUT_FONT_PNG
    stbi_write_png("/Users/randle_h/Desktop/output.png", (int)FCFG.info.width, (int)FCFG.info.height, 1, FCFG.info.output, (int)FCFG.info.width);
    stbi_write_png("C:/Users/asus/Desktop/output.png", (int)FCFG.info.width, (int)FCFG.info.height, 1, FCFG.info.output, (int)FCFG.info.width);
    
	printf("ascent = %d\n"   , FCFG.info.ascent);
    printf("descent = %d\n"  , FCFG.info.descent);
    printf("lineGap = %d\n"   , FCFG.info.lineGap);
    
    printf("w = %ld\n", FCFG.info.width  );
    printf("h = %ld\n", FCFG.info.height );
#endif
    return &FCFG.info;
}

__GUI_Font_t*  __Font_exportStr( const char* str ){
    
    if( FCFG.info.output ){
        RH_FREE(FCFG.info.output);
        FCFG.info.output = NULL;
    }
    
    size_t len = strlen(str);
    
    FCFG.info.height = FCFG.size;
    FCFG.info.width  = 0;
    int* xs  = (int*)RH_CALLOC(len,sizeof(int));
    int* ys  = (int*)RH_CALLOC(len,sizeof(int));
    int* c_x = (int*)RH_CALLOC(len,sizeof(int));
    int* c_y = (int*)RH_CALLOC(len,sizeof(int));
    int* adv = (int*)RH_MALLOC(len*sizeof(int));
    int* lfB = (int*)RH_MALLOC(len*sizeof(int));
    for(int i=0; i<len; i++){
        
        int advanceWidth    = 0;
        int leftSideBearing = 0;
        (*FCFG.method->_GetCodepointHMetrics)( &FCFG.stb_info, str[i], &advanceWidth, &leftSideBearing );
        
        
        int c_x1 = 0, c_y1 = 0, c_x2 = 0, c_y2 = 0;
        (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, str[i], FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
        c_x[i] = c_x2-c_x1;
        c_y[i] = c_y2-c_y1;
        
        if( c_x[i]==0 ){
            (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, 'h', FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
            c_x[i] = c_x2-c_x1;
        }
        
        adv[i] = roundf( advanceWidth*FCFG.scale );
        lfB[i] = roundf( leftSideBearing*FCFG.scale );
        FCFG.info.width += c_x[i];
        if(i!=0)
            xs[i]  = xs[i-1] + c_x[i-1];
        ys[i]  = FCFG.info.ascent + c_y1;

    }
    
    FCFG.info.output = RH_CALLOC(FCFG.info.width*FCFG.info.height, sizeof(uint8_t));
    for(int i=0; i<len; i++){
        size_t byteOffset = 0;
        if( i!=0 ){
            byteOffset = ( lfB[i] + ys[i]*FCFG.info.width + xs[i] );
        }else{
            byteOffset = ( lfB[i] + ys[i]*FCFG.info.width + xs[i] );
        }
        (*FCFG.method->_MakeCodepointBitmap)(&FCFG.stb_info, FCFG.info.output+byteOffset, c_x[i], c_y[i], (int)(FCFG.info.width), FCFG.scale, FCFG.scale, str[i]);
    }
    RH_FREE(xs);
    RH_FREE(ys);
    RH_FREE(c_x);
    RH_FREE(c_y);
    RH_FREE(adv);
    RH_FREE(lfB);
#ifdef STB_OUTPUT_FONT_PNG
    printf("ascent = %d\n"   , FCFG.info.ascent);
    printf("descent = %d\n"  , FCFG.info.descent);
    printf("lineGap = %d\n"   , FCFG.info.lineGap);
    
    printf("w = %ld\n", FCFG.info.width  );
    printf("h = %ld\n", FCFG.info.height );
    stbi_write_png("C:/Users/asus/Desktop/output.png", (int)FCFG.info.width, (int)FCFG.info.height, 1, FCFG.info.output, (int)FCFG.info.width);
    stbi_write_png("/Users/randle_h/Desktop/output.png", (int)FCFG.info.width, (int)FCFG.info.height, 1, FCFG.info.output, (int)FCFG.info.width);
#endif
    return &FCFG.info;
}

void __Font_getCharSize( size_t *width, size_t *height, char c ){
    int c_x1 , c_y1 , c_x2 , c_y2;
    (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, c, FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
    if( width )
        *width = c_x2-c_x1;

    if( height )
        *height = c_y2-c_y1;
}

void __Font_getStrSize( size_t *width, size_t *height, const char* str ){
    __exit( !str );
    
    for(int i=0; i<strlen(str); i++){
        int advanceWidth    = 0;
        int leftSideBearing = 0;
        (*FCFG.method->_GetCodepointHMetrics)( &FCFG.stb_info, str[i], &advanceWidth, &leftSideBearing );
    
        if( width )
            *width += roundf( advanceWidth*FCFG.scale );;
    }
    if( height )
        *height = FCFG.size;
}

int  __Font_getWordNum( const size_t width, const char* str ){
    int cnt=0, w=0;
    int c_x1 , c_y1 , c_x2 , c_y2;
    
    do{
        (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, str[cnt++], FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
        w+=c_x2-c_x1;
    }while(  cnt<strlen(str) && w<width);
    if( w>= width )
        cnt--;
    
    return cnt;
}

#include "BLK_data.h"
__GUI_Font_t*  __Font_exportText_Justify( const char* str, size_t width ){

    // 获取空格的最小像素宽度,为改字体下的空格所占宽度的一半.
    size_t spW = 0;
    size_t spH = 0;
    __Font_getCharSize(&spW, &spH, 'r' );
    
    // 定义词汇数据结构,字符串及所需绘制的像素点宽度.
    struct WordInfo_t{
        char*   str;
        size_t  pixsW;
    };
    typedef struct WordInfo_t WordInfo_t;
    
    // 对于strtok需要动态存储变量,不可以为只读字符串,故做拷贝处理.
    char* pSentence = (char*)alloca(strlen(str));
    strcpy(pSentence, str);
    
    // 获取句子中的单词信息,每个单词单独存储在链表节点中,节点中包含单词字符串以及其所需绘制的像素点个数.
    WordInfo_t WordInfo = {.str = strtok(pSentence," "), .pixsW = 0};
    __Font_getStrSize( &WordInfo.pixsW, NULL, WordInfo.str );
    
    __LinkDB_t* pTextHead = __LINK_DB_createHead( &WordInfo );

    char* p = NULL;
    while( (p = strtok(NULL," ")) != NULL ){
        WordInfo_t* pWordInfo = alloca(sizeof(WordInfo_t));
        pWordInfo->str   = p;
        pWordInfo->pixsW = 0;
        __Font_getStrSize( &pWordInfo->pixsW, NULL, pWordInfo->str );
        __LINK_DB_addTail( pTextHead, pWordInfo );
    }
    

    const __LinkDB_t* pIter1 = pTextHead;
    const __LinkDB_t* pIter2 = pTextHead;

/* 此处可以测试,句子信息是否提取准确 */
//    const __LinkDB_t* pIter  = pTextHead;
//    pIter  = pTextHead;
//    do{
//        printf("%s\t\tlen=%ld\n", ((WordInfo_t*)pIter->object)->str,((WordInfo_t*)pIter->object)->pixsW);
//        pIter = pIter->pNext;
//    }while( pIter );

    size_t pixCnt   = 0;          // 用于记录一行已使用的像素栏
    size_t wordCnt  = 0;          // 用于记录一行单词有多少个
    size_t spCnt    = 0;          // 用于记录一行单词间隙有多少个, 永远等于单词数减1
    size_t spExtra  = 0;          // 一行单词出去基本空格单元像素(spW)点后,额外的所有空格占用的像素点
    size_t spAvg    = 0;          // 平均每个单词间隙空格占用的像素点
    size_t spRemain = 0;          // spAvg的余数
    size_t rowCnt   = 0;          // 用于记录左右文本对其后所需的行数, height = rowCnt* FCFG.height
    bool   spAdded = false;       // 用于记录单词结尾是否添加过空格
    do{
        if( pIter1 != NULL && pixCnt + ((WordInfo_t*)(pIter1->object))->pixsW < width ){
            pixCnt += ((WordInfo_t*)(pIter1->object))->pixsW;
            wordCnt++;
            spAdded = false;       // 单词结尾未添加空格
            if(pixCnt + spW < width){
                pixCnt += spW;
                spAdded = true;    // 单词结尾已添加空格
            }
            pIter1 = pIter1->pNext;
        }else{
            if( spAdded )
                pixCnt -= spW;     // 末尾单词无需添空格,因此去除.
            spExtra  = width - pixCnt;
            spCnt    = wordCnt-1;
            spAvg    = (spCnt==0)?(1):(spExtra/spCnt);
            spRemain = (spCnt==0)?(1):(spExtra%spCnt);
            
            while( spCnt-- ){
                // 插入空格字符
                WordInfo_t* wi = alloca(sizeof(WordInfo_t));
                wi->str   = NULL;    // 这是一个间隔空白字符,
                wi->pixsW = spW + spAvg + ((spRemain==0)?(0):((spRemain--)!=0));
                
                pIter2 = __LINK_DB_insert( pTextHead, pIter2->object , wi )->pNext;
            }


#ifdef RH_DEBUG
            if( pIter1 )
                RH_ASSERT( pIter1->pPrev==pIter2 );
            else
                RH_ASSERT( pIter2->pNext==pIter1 );
#endif
            // 插入回车字符
            WordInfo_t* wi = alloca(sizeof(WordInfo_t));
            wi->str   = "\n";    // 这是一个回车字符,当读取到此需要换行
            wi->pixsW = 0;
            pIter2 = __LINK_DB_insert( pTextHead, pIter2->object , wi )->pNext;
            rowCnt++;
#ifdef RH_DEBUG
            RH_ASSERT( pIter1==pIter2 );
#endif
            pixCnt  = 0;
            wordCnt = 0;
            
        }

        
    }while( pIter1!=NULL || pIter2!=NULL );
    
/* 此处可以测试,句子信息是否提取准确 */
//    pIter  = pTextHead;
//    do{
//        if( ((WordInfo_t*)pIter->object)->str==NULL ){
//            printf(" #%ld ",((WordInfo_t*)pIter->object)->pixsW);
//            pIter = pIter->pNext;
//            continue;
//        }
//        printf("%s", ((WordInfo_t*)pIter->object)->str);
//        pIter = pIter->pNext;
//    }while( pIter );
    
    // 释放之前的缓存数据
    if( FCFG.info.output ){
        RH_FREE(FCFG.info.output);
        FCFG.info.output = NULL;
    }
    // 重建缓存, 宽度为输入的width,高度为上述计算后的行数*字体高度即Font.size
    FCFG.info.width  = width;
    FCFG.info.height = rowCnt*FCFG.size;
    FCFG.info.output = RH_CALLOC( FCFG.info.height*FCFG.info.width, sizeof(uint8_t) );
#ifdef RH_DEBUG
    RH_ASSERT( FCFG.info.output );
#endif
    // 逐单词输出
    const __LinkDB_t* pIter3 = pTextHead;
    size_t x=0, y=0;
    do{
        char* str = ((WordInfo_t*)(pIter3->object))->str;
        if( str==NULL ){
            x += ((WordInfo_t*)(pIter3->object))->pixsW;
        }else if( *str == '\n' ){
            y += FCFG.size;
            x = 0;
        }else{
#ifdef DEBUG
            RH_ASSERT( x<FCFG.info.width );
#endif
            for(int i=0; i<strlen(str); i++){
                int c_x1 , c_y1 , c_x2 , c_y2;
                int advanceWidth    = 0;
                int leftSideBearing = 0;
                (*FCFG.method->_GetCodepointHMetrics)( &FCFG.stb_info, str[i], &advanceWidth, &leftSideBearing );
                (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, str[i], FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
                size_t byteOffset = FCFG.info.width*(y+FCFG.info.ascent + c_y1) + x;
                (*FCFG.method->_MakeCodepointBitmap)(&FCFG.stb_info, FCFG.info.output+byteOffset, c_x2-c_x1, c_y2-c_y1, (int)(FCFG.info.width), FCFG.scale, FCFG.scale, str[i]);
                x += roundf( advanceWidth*FCFG.scale );
            }
        }
        pIter3 = pIter3->pNext;
    }while( pIter3 );
    
#ifdef STB_OUTPUT_FONT_PNG
//    printf("ascent = %d\n"   , FCFG.info.ascent);
//    printf("descent = %d\n"  , FCFG.info.descent);
//    printf("lineGap = %d\n"   , FCFG.info.lineGap);
    stbi_write_png("C:/Users/asus/Desktop/output.png", (int)FCFG.info.width, (int)FCFG.info.height, 1, FCFG.info.output, (int)FCFG.info.width);
    stbi_write_png("/Users/randle_h/Desktop/o.png", (int)FCFG.info.width, (int)FCFG.info.height, 1, FCFG.info.output, (int)FCFG.info.width);
#endif
    __LINK_DB_removeAll(pTextHead);
    return &FCFG.info;
}

static bool backFCFG = false;
void __Font_backup_config(void){
    memcpy(&FCFG_copy, &FCFG, sizeof(FCFG_copy));
    backFCFG = true;
}

void __Font_restore_config(void){
    if( backFCFG ){
        if( FCFG.info.output ){
            RH_FREE(FCFG.info.output);
            FCFG.info.output=NULL;
        }
        memcpy(&FCFG, &FCFG_copy, sizeof(FCFG));
        __Font_setStyle( FCFG.style );
        __Font_setSize( FCFG.size );
        backFCFG = false;
    }
}




