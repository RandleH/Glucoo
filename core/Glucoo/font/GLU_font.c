
#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_truetype.h"
#include "GLU_font.h"

#if RH_CFG_OUTPUT_FONT_PNG
#define STB_OUTPUT_FONT_PNG
#endif

#ifdef STB_OUTPUT_FONT_PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

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
          (const stbtt_fontinfo *info, unsigned char *img_buf, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint);
    
     int  (*_GetCodepointKernAdvance)
          (const stbtt_fontinfo *info, int ch1, int ch2);

};
typedef struct __Method __Method;

int   rhtt_InitFont(stbtt_fontinfo *info, const unsigned char *data, int offset){
    
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
    *ascent  = 0;
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

void  rhtt_MakeCodepointBitmap  (const stbtt_fontinfo *info, unsigned char *img_buf, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint){
    // info       :  字体点阵数据
    // img_buf     :  输出图像地址(假设用户已做偏移),以该地址为首地址
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
    for( int y=0; y<pInfo->h; y+=8, img_buf+=out_stride ){
        for( int cnt=0; cnt<8; cnt++){
            for( int x=0; x<pInfo->w; x++ ){
                *(img_buf+x) = ((((*(pData+x))>>cnt)&0x01)==0)?(0x00):(0xff); // printf("%d\n",((((*pData)>>cnt)&0x01)==0)?(0x00):(0xff));
            }
            img_buf+=out_stride;
        }
        pData += pInfo->w;
    }
}

int  rhtt_GetCodepointKernAdvance(const stbtt_fontinfo *info, int ch1, int ch2){
    return 0;
}


#if ( RH_CFG_FONT_DATA_TYPE != RH_CFG_FONT_DATA_LOCAL_BITMAP )
static __Method stbtt = {  // Present by Sean T. Barrett  --> stb
    ._InitFont                = stbtt_InitFont,
    ._ScaleForPixelHeight     = stbtt_ScaleForPixelHeight,
    ._GetFontVMetrics         = stbtt_GetFontVMetrics,
    ._GetCodepointHMetrics    = stbtt_GetCodepointHMetrics,
    ._GetCodepointBitmapBox   = stbtt_GetCodepointBitmapBox,
    ._MakeCodepointBitmap     = stbtt_MakeCodepointBitmap,
    ._GetCodepointKernAdvance = stbtt_GetCodepointKernAdvance
};
#else
static __Method rhtt  = {   // Present by Randle Hemlslay  --> rh
    ._InitFont                = rhtt_InitFont,
    ._ScaleForPixelHeight     = rhtt_ScaleForPixelHeight,
    ._GetFontVMetrics         = rhtt_GetFontVMetrics,
    ._GetCodepointHMetrics    = rhtt_GetCodepointHMetrics,
    ._GetCodepointBitmapBox   = rhtt_GetCodepointBitmapBox,
    ._MakeCodepointBitmap     = rhtt_MakeCodepointBitmap,
    ._GetCodepointKernAdvance = rhtt_GetCodepointKernAdvance
};

#endif

static struct{
    GLU_SRCT(FontImg)    img;
    GLU_ENUM(Font)       style;
    uint8_t              size;
    float                scale;
    int                  ascent;
    int                  descent;
    int                  lineGap;
    
    stbtt_fontinfo       stb_info;
    const uint8_t*       font_data;
    __Method*            method;
    
}FCFG_copy,FCFG = {0};


#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF )
/*==================================================================================================================================
 * 配置外部TruethType文件方式获取字体数据
 *==================================================================================================================================
 * 以下为外部字体文件的路径名称字符串, 以供读取.
 * 字体路径顺序随枚举顺序.
 * 根据宏 RH_CFG_FONT_STYLE__xxxx 进行初始化, 如果未开启该字体宏, 则路径将为NULL
 * __read_ttf_file 为字体ttf文件读取函数, 将数据拷贝至FCFG.ttf中
 ==================================================================================================================================*/
    static E_Status_t __read_ttf_file( const char* path ){
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

        return MAKE_ENUM(kStatus_Success);
    }
    #if defined (__WIN32)
      #error "WIN32 NOT SUPPORTED YET."
        static const char* font_ttf_path[kGLU_NUM_FontStyle] = {
            0
        };
    #elif defined  (__APPLE__)
        static const char* font_ttf_path[kGLU_NUM_FontStyle] = {
             [kGLU_Font_Unscii] =
            "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/unscii-8.ttf"           ,
             [kGLU_Font_ArialRounded_Bold] =
            "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/Arial Rounded Bold.ttf" ,
            
             [kGLU_Font_CourierNew] =
                #if RH_CFG_FONT_STYLE__CourierNew
                    "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/Courier New.ttf"        ,
                #else
                    NULL,
                #endif
             [kGLU_Font_CourierNew_Italic] =
                #if RH_CFG_FONT_STYLE__CourierNew_Italic
                    "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/Courier New Italic.ttf" ,
                #else
                    NULL,
                #endif
             [kGLU_Font_CourierNew_Bold] =
                #if RH_CFG_FONT_STYLE__CourierNew_Bold
                    "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/Courier New Bold.ttf"   ,
                #else
                    NULL,
                #endif
             [kGLU_Font_NewYork] =
                #if RH_CFG_FONT_STYLE__NewYork
                    "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/NewYork.ttf"            ,
                #else
                    NULL,
                #endif
             [kGLU_Font_NewYork_Italic] =
                #if RH_CFG_FONT_STYLE__NewYork_Italic
                    "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/NewYorkItalic.ttf"      ,
                #else
                    NULL,
                #endif
             [kGLU_Font_Arial_Unicode] =
                #if RH_CFG_FONT_STYLE__Arial_Unicode
                    "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/Arial Unicode.ttf"      ,
                #else
                    NULL,
                #endif
        };
    #endif


#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY )
/*==================================================================================================================================
 * 配置内部TruethType数组方式获取字体数据
 *==================================================================================================================================
 * 以下为内部字体文件数据的数组名称, 以供读取.
 * 字体路径顺序随枚举顺序.
 * 根据宏 RH_CFG_FONT_STYLE__xxxx 进行初始化, 如果未开启该字体宏, 则路径将为NULL
 ==================================================================================================================================*/
    extern const uint8_t Font_TTF_ArialRoundedBold  [49296];
    extern const uint8_t Font_TTF_CourierNew        [684624];
    extern const uint8_t Font_TTF_CourierNew_Bold   [691796];
    extern const uint8_t Font_TTF_CourierNew_Italic [589900];
    extern const uint8_t Font_TTF_NewYork           [344120];
    extern const uint8_t Font_TTF_NewYork_Italic    [361176];
    extern const uint8_t Font_TTF_Unscii            [293712];
    extern const uint8_t Font_TTF_Optima            [263984];

    static const uint8_t* font_ttf_array[kGLU_NUM_FontStyle] = {
        
        [kGLU_Font_Unscii] =
               Font_TTF_Unscii            ,
        
        [kGLU_Font_ArialRounded_Bold] =
               Font_TTF_ArialRoundedBold  ,
       
        [kGLU_Font_CourierNew] =
           #if RH_CFG_FONT_STYLE__CourierNew
               Font_TTF_CourierNew        ,
           #else
               NULL,
           #endif
        [kGLU_Font_CourierNew_Italic] =
           #if RH_CFG_FONT_STYLE__CourierNew_Italic
               Font_TTF_CourierNew_Italic ,
           #else
               NULL,
           #endif
        [kGLU_Font_CourierNew_Bold] =
           #if RH_CFG_FONT_STYLE__CourierNew_Bold
               Font_TTF_CourierNew_Bold   ,
           #else
               NULL,
           #endif
        [kGLU_Font_NewYork] =
           #if RH_CFG_FONT_STYLE__NewYork
               Font_TTF_NewYork           ,
           #else
               NULL,
           #endif
        [kGLU_Font_NewYork_Italic] =
           #if RH_CFG_FONT_STYLE__NewYork_Italic
               Font_TTF_NewYork_Italic    ,
           #else
               NULL,
           #endif
        
        [kGLU_Font_Optima] =
           #if RH_CFG_FONT_STYLE__Optima
                   Font_TTF_Optima        ,
           #else
                   NULL,
           #endif
        
    };
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP  )
/*==================================================================================================================================
 * 配置字体点阵数组方式获取字体数据
 *==================================================================================================================================
 * 该方案适用于内存单元较小的主机使用
 * 只有一种字体(STD6x8) 一种大小(8)可用.
 *
 ==================================================================================================================================*/
extern const rhtt_fontinfo Font_BIT_ArialRoundedBold_size_8[];
static const rhtt_fontinfo* font_bit_array[kGLU_NUM_FontStyle] = {
    Font_BIT_ArialRoundedBold_size_8  ,
};
#else
  #error "Unknown font data source."
#endif


void RH_PREMAIN
GLU_FUNC( Font, init           ) ( void ){
    FCFG.style     = kGLU_Font_Unscii;
    FCFG.size      = 24;
    
    GLU_FUNC( Font, set_font )( kGLU_Font_Unscii );
    
    memcpy(&FCFG_copy, &FCFG, sizeof(FCFG_copy));
}

void
GLU_FUNC( Font, set_font      ) ( GLU_ENUM(Font) style   ){
#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF   )
    // 确认字体解析库 stbtt为使用STB库, rhtt为使用自研库
    FCFG.method = &stbtt;
    
    // 导入字体文件数据
    RH_ASSERT( font_ttf_path[style] ); // 失败: 检查对应字体宏 RH_CFG_FONT_STYLE__xxxx 是否开启
    RH_ASSERT( MAKE_ENUM(kStatus_Success) == __read_ttf_file( font_ttf_path[style] ) );
    (*FCFG.method->_InitFont)(&FCFG.stb_info, FCFG.font_data, 0);
    
    // 记录字体类型
    FCFG.style        = style;
    
    // 计算字体数据
    FCFG.scale        = (*FCFG.method->_ScaleForPixelHeight)( &FCFG.stb_info, FCFG.size );
    (*FCFG.method->_GetFontVMetrics)( &FCFG.stb_info, &FCFG.ascent, &FCFG.descent, &FCFG.lineGap );
    FCFG.ascent  = roundf(FCFG.ascent * FCFG.scale);
    FCFG.descent = roundf(FCFG.descent * FCFG.scale);
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY  )
    // 确认字体解析库 stbtt为使用STB库, rhtt为使用自研库
    FCFG.method = &stbtt;
    
    // 导入字体文件数据
    FCFG.font_data = font_ttf_array[style];
    (*FCFG.method->_InitFont)(&FCFG.stb_info, FCFG.font_data, 0);
    
    // 记录字体类型
    FCFG.style        = style;
    
    // 计算字体数据
    FCFG.scale        = (*FCFG.method->_ScaleForPixelHeight)( &FCFG.stb_info, FCFG.size );
    (*FCFG.method->_GetFontVMetrics)( &FCFG.stb_info, &FCFG.ascent, &FCFG.descent, &FCFG.lineGap );
    FCFG.ascent  = roundf(FCFG.ascent * FCFG.scale);
    FCFG.descent = roundf(FCFG.descent * FCFG.scale);
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )
    FCFG.method = &rhtt;
    FCFG.font_data = font_bit_array[style];
#else
  #error "Unknown font data source."
#endif
    
    
}

void
GLU_FUNC( Font, set_size       ) ( uint8_t        size    ){

#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF   )
    FCFG.method = &stbtt;
    FCFG.size   = size;
    FCFG.scale       = (*FCFG.method->_ScaleForPixelHeight)( &FCFG.stb_info, FCFG.size );
    (*FCFG.method->_GetFontVMetrics)( &FCFG.stb_info, &FCFG.ascent, &FCFG.descent, &FCFG.lineGap );
    FCFG.ascent  = roundf(FCFG.ascent * FCFG.scale);
    FCFG.descent = roundf(FCFG.descent * FCFG.scale);
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY  )
    FCFG.method = &stbtt;
    FCFG.size   = size;
    FCFG.scale       = (*FCFG.method->_ScaleForPixelHeight)( &FCFG.stb_info, FCFG.size );
    (*FCFG.method->_GetFontVMetrics)( &FCFG.stb_info, &FCFG.ascent, &FCFG.descent, &FCFG.lineGap );
    FCFG.ascent  = roundf(FCFG.ascent * FCFG.scale);
    FCFG.descent = roundf(FCFG.descent * FCFG.scale);
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )
    FCFG.method = &rhtt;
    FCFG.size   = 8;
#else
  #error "Unknown font data source."
#endif
    
    
}

uint8_t
GLU_FUNC( Font, get_size       ) ( void ){
    return FCFG.size;
}

GLU_ENUM(Font)
GLU_FUNC( Font, get_font      ) ( void ){
    return FCFG.style;
}

GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE 
GLU_FUNC( Font, out_chr_Img    ) ( uint16_t    chr ){
    int c_x1 , c_y1 , c_x2 , c_y2;
    (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, chr, FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
    FCFG.img.img_h = c_y2-c_y1;
    FCFG.img.img_w  = c_x2-c_x1;
    
    if( FCFG.img.img_buf ){
        RH_FREE(FCFG.img.img_buf);
        FCFG.img.img_buf = NULL;
    }
    FCFG.img.img_buf = RH_CALLOC( FCFG.img.img_h*FCFG.img.img_w , sizeof(uint8_t) );
    
    (*FCFG.method->_MakeCodepointBitmap)( &FCFG.stb_info, FCFG.img.img_buf, (int)FCFG.img.img_w, (int)FCFG.img.img_h, (int)FCFG.img.img_w, FCFG.scale, FCFG.scale, chr );
    
#ifdef STB_OUTPUT_FONT_PNG
    stbi_write_png("/Users/randle_h/Desktop/img_buf.png", (int)FCFG.img.img_w, (int)FCFG.img.img_h, 1, FCFG.img.img_buf, (int)FCFG.img.img_w);
    stbi_write_png("C:/Users/asus/Desktop/img_buf.png", (int)FCFG.img.img_w, (int)FCFG.img.img_h, 1, FCFG.img.img_buf, (int)FCFG.img.img_w);
    
	printf("ascent = %d\n"   , FCFG.ascent);
    printf("descent = %d\n"  , FCFG.descent);
    printf("lineGap = %d\n"   , FCFG.lineGap);
    
    printf("w = %d\n", FCFG.img.img_w  );
    printf("h = %d\n", FCFG.img.img_h );
#endif
    return &FCFG.img;
}

GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE
GLU_FUNC( Font, out_str_Img    ) ( const char* str ){
    if( FCFG.img.img_buf ){
        RH_FREE(FCFG.img.img_buf);
        FCFG.img.img_buf = NULL;
    }
    
    // 采集字符串像素坐标信息
    size_t size = (strlen(str)+1)*sizeof(int);
    int* cx  = alloca(size); memset( cx, 0, size); // 记录每个字母起始绘制的横坐标
    int* cy  = alloca(size); memset( cy, 0, size); // 记录每个字母起始绘制的纵坐标
    int* cw  = alloca(size); memset( cw, 0, size); // 记录每个字母外框宽度(不可用于计算起始坐标, 每个字母会有高度和间隙补偿)
    int* ch  = alloca(size); memset( ch, 0, size); // 记录每个字母外框高度(不可用于计算起始坐标, 每个字母会有高度和间隙补偿)
    int  cnt = 0;
    while( str[cnt]!='\0' ){
        {// 字符外框大小
            int c_x1 , c_y1 , c_x2 , c_y2;
            (*FCFG.method->_GetCodepointBitmapBox)( &FCFG.stb_info, str[cnt], FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
            cw[cnt] = c_x2-c_x1;
            ch[cnt] = c_y2-c_y1;
            cy[cnt] = FCFG.ascent + c_y1;
        }
        
        {// 字符横向间隙和宽度
            int advanceWidth,leftSideBearing;
            (*FCFG.method->_GetCodepointHMetrics)(&FCFG.stb_info, str[cnt], &advanceWidth, &leftSideBearing );
            
            leftSideBearing = roundf( leftSideBearing*FCFG.scale );
            advanceWidth    = roundf( advanceWidth*FCFG.scale );
            
            cx[cnt]   += leftSideBearing;
            
            cx[cnt+1]  = cx[cnt] - leftSideBearing + advanceWidth + roundf( (*FCFG.method->_GetCodepointKernAdvance)( &FCFG.stb_info, str[cnt], str[cnt+1] ) * FCFG.scale) ;
        }
        cnt++;
    }
    
    // 确定绘制出这样的字符串至少需要的图像大小
    (*FCFG.method->_GetCodepointHMetrics)(&FCFG.stb_info, '\0', NULL, &FCFG.img.img_w ); // 求出空字符的左偏移str[strlen(str)-1]
    FCFG.img.img_w   = roundf( FCFG.img.img_w*FCFG.scale );
    FCFG.img.img_w  += cx[cnt];
    FCFG.img.img_h   = FCFG.ascent-FCFG.descent+FCFG.lineGap;
    FCFG.img.img_buf = RH_CALLOC( FCFG.img.img_w*FCFG.img.img_h, sizeof(uint8_t) );
    
    // 迭代字符渲染
    cnt = 0;
    while( str[cnt]!='\0' ){
        uint8_t *pIter = FCFG.img.img_buf + ( FCFG.img.img_w*cy[cnt] ) + cx[cnt];
        (*FCFG.method->_MakeCodepointBitmap)( &FCFG.stb_info, pIter, cw[cnt], ch[cnt], (int)FCFG.img.img_w, FCFG.scale, FCFG.scale, str[cnt] );
        cnt++;
    }
#if RH_CFG_OUTPUT_FONT_PNG
    stbi_write_png("/Users/randle_h/Desktop/output.png", FCFG.img.img_w, FCFG.img.img_h, 1, FCFG.img.img_buf, FCFG.img.img_w);
#endif
    return &FCFG.img;
}

#include "BLK_data.h"
static GLU_SRCT(FontImg)*  __out_txt_Justify  ( const char* str, size_t width ){

    // 获取空格的最小像素宽度,为改字体下的空格所占宽度的一半.
    size_t spW = 0;
    size_t spH = 0;
    GLU_FUNC( Font, get_chr_ImgInfo )(&spW, &spH, 'r' );
    
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
    GLU_FUNC( Font, get_str_ImgInfo )( &WordInfo.pixsW, NULL, WordInfo.str );
    
    BLK_SRCT(LinkDB)* pTextHead = BLK_FUNC( LinkDB, createHead )( &WordInfo );

    char* p = NULL;
    while( (p = strtok(NULL," ")) != NULL ){
        WordInfo_t* pWordInfo = alloca(sizeof(WordInfo_t));
        pWordInfo->str   = p;
        pWordInfo->pixsW = 0;
        GLU_FUNC( Font, get_str_ImgInfo )( &pWordInfo->pixsW, NULL, pWordInfo->str );
        
        BLK_FUNC( LinkDB, addTail )( pTextHead, pWordInfo );
    }
    

    const BLK_SRCT(LinkDB)* pIter1 = pTextHead;
    const BLK_SRCT(LinkDB)* pIter2 = pTextHead;

/* 此处可以测试,句子信息是否提取准确 */
    #if 0
    const BLK_SRCT(LinkDB)* pIter  = pTextHead;
    pIter  = pTextHead;
    do{
        printf("%s\t\tlen=%ld\n", ((WordInfo_t*)pIter->object)->str,((WordInfo_t*)pIter->object)->pixsW);
        pIter = pIter->pNext;
    }while( pIter );
    #endif

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
                
                pIter2 = BLK_FUNC( LinkDB, insert )( pTextHead, pIter2->object , wi )->pNext;
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
            pIter2 = BLK_FUNC( LinkDB, insert )( pTextHead, pIter2->object , wi )->pNext;
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
    if( FCFG.img.img_buf ){
        RH_FREE(FCFG.img.img_buf);
        FCFG.img.img_buf = NULL;
    }
    // 重建缓存, 宽度为输入的width,高度为上述计算后的行数*字体高度即Font.size
    FCFG.img.img_w  = (int)width;
    FCFG.img.img_h  = (int)(rowCnt*FCFG.size);
    FCFG.img.img_buf = RH_CALLOC( FCFG.img.img_h*FCFG.img.img_w, sizeof(uint8_t) );
#ifdef RH_DEBUG
    RH_ASSERT( FCFG.img.img_buf );
#endif
    // 逐单词输出
    const BLK_SRCT(LinkDB)* pIter3 = pTextHead;
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
            RH_ASSERT( x<FCFG.img.img_w );
        #endif


            for(int i=0; i<strlen(str); i++){
                int c_x1 , c_y1 , c_x2 , c_y2;
                int advanceWidth    = 0;
                int leftSideBearing = 0;
                (*FCFG.method->_GetCodepointHMetrics)( &FCFG.stb_info, str[i], &advanceWidth, &leftSideBearing );
                (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, str[i], FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
                size_t byteOffset = FCFG.img.img_w*(y+FCFG.ascent + c_y1) + x;
                (*FCFG.method->_MakeCodepointBitmap)(&FCFG.stb_info, FCFG.img.img_buf+byteOffset, c_x2-c_x1, c_y2-c_y1, (int)(FCFG.img.img_w), FCFG.scale, FCFG.scale, str[i]);
                x += roundf( advanceWidth*FCFG.scale );
            }
        }
        pIter3 = pIter3->pNext;
    }while( pIter3 );
    
#ifdef STB_OUTPUT_FONT_PNG
    stbi_write_png("C:/Users/asus/Desktop/img_buf.png", (int)FCFG.img.img_w, (int)FCFG.img.img_h, 1, FCFG.img.img_buf, (int)FCFG.img.img_w);
    stbi_write_png("/Users/randle_h/Desktop/o.png", (int)FCFG.img.img_w, (int)FCFG.img.img_h, 1, FCFG.img.img_buf, (int)FCFG.img.img_w);
#endif
    BLK_FUNC( LinkDB, removeAll )(pTextHead);
    return &FCFG.img;
}
static GLU_SRCT(FontImg)*  __out_txt_Left     ( const char* str, size_t width ){
    return NULL;
}//
static GLU_SRCT(FontImg)*  __out_txt_Right    ( const char* str, size_t width ){
    return NULL;
}//
static GLU_SRCT(FontImg)*  __out_txt_Middle   ( const char* str, size_t width ){
    return NULL;
}//

GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE
GLU_FUNC( Font, out_txt_Img    ) ( const char* str, size_t width, GLU_ENUM(Align) align ){
    switch(align){
        case kGLU_Align_Justify:
            return __out_txt_Justify( str, width );
        case kGLU_Align_Left:
            return __out_txt_Left   ( str, width );
        case kGLU_Align_Right:
            return __out_txt_Right  ( str, width );
        case kGLU_Align_Middle:
            return __out_txt_Middle ( str, width );
        default:
            return NULL;
    }
}

void
GLU_FUNC( Font, get_chr_ImgInfo) ( size_t RH_NULLABLE *width, size_t RH_NULLABLE *height, char        c   ){
    int c_x1 , c_y1 , c_x2 , c_y2;
    (*FCFG.method->_GetCodepointBitmapBox)(&FCFG.stb_info, c, FCFG.scale, FCFG.scale, &c_x1, &c_y1, &c_x2, &c_y2);
    if( width )
        *width = c_x2-c_x1;

    if( height )
        *height = c_y2-c_y1;
}

void
GLU_FUNC( Font, get_str_ImgInfo) ( size_t RH_NULLABLE *width, size_t RH_NULLABLE *height, const char* str ){
    
    if( height ){
        *height = FCFG.ascent-FCFG.descent+FCFG.lineGap;
    }
    
    if( width ){
        int cnt = 0;
        int advanceWidth=0,leftSideBearing=0;
        *width = 0;
        while( str[cnt]!='\0' ){
            (*FCFG.method->_GetCodepointHMetrics)(&FCFG.stb_info, str[cnt], &advanceWidth, &leftSideBearing ); // 获取字符所占横向宽度
            leftSideBearing = roundf( leftSideBearing * FCFG.scale );
            advanceWidth    = roundf( advanceWidth    * FCFG.scale );
            
            *width +=  advanceWidth + roundf( (*FCFG.method->_GetCodepointKernAdvance)( &FCFG.stb_info, str[cnt], str[cnt+1] ) * FCFG.scale) ;
            
            cnt++;
        }
    }
}

int
GLU_FUNC( Font, get_str_WordCnt) ( size_t width, const char* str ){
    int cnt=0, w=0;
    
    int advanceWidth,leftSideBearing;
    do{
        stbtt_GetCodepointHMetrics(&FCFG.stb_info, str[cnt], &advanceWidth, &leftSideBearing );
        leftSideBearing = roundf( leftSideBearing * FCFG.scale );
        advanceWidth    = roundf( advanceWidth    * FCFG.scale );
        
        w += advanceWidth + roundf( stbtt_GetCodepointKernAdvance( &FCFG.stb_info, str[cnt], str[cnt+1] ) * FCFG.scale);
        cnt++;
    }while( str[cnt]!='\0' && w+leftSideBearing<width );
    
    if( w> width )
        cnt--;
    
    return cnt;
}


static bool backFCFG = false;
void
GLU_FUNC( Font, backupCache    ) ( void ){
    memcpy(&FCFG_copy, &FCFG, sizeof(FCFG_copy));
    backFCFG = true;
}

void
GLU_FUNC( Font, restoreCache   ) ( void ){
    if( backFCFG ){
        if( FCFG.img.img_buf ){
            RH_FREE(FCFG.img.img_buf);
            FCFG.img.img_buf=NULL;
        }
        memcpy(&FCFG, &FCFG_copy, sizeof(FCFG));
        GLU_FUNC( Font, set_font )( FCFG.style );
        GLU_FUNC( Font, set_size  )( FCFG.size  );
        backFCFG = false;
    }
}


// 仅供开发者使用
#if 1

size_t
GLU_FUNC( Font, out_ttf_array )( const char* ttf_path, const char* dst ){
    FILE* fontFile = fopen( ttf_path , "rb" );
    
#ifdef RH_DEBUG
    assert( fontFile );
#endif
    
    fseek(fontFile, 0, SEEK_END);
    size_t size = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);
    
    uint8_t* array = calloc(size, sizeof(uint8_t));

    fread(array, size, sizeof(uint8_t), fontFile);
    fclose(fontFile);
    
    FILE* fontTxt = fopen(dst, "a");
    
    char buf[10] = {0};

    for(int i=0; i<size; i++){
        if(i%20 == 0 ){
            fprintf( fontTxt, "\n");
        }
        sprintf(buf, "0x%02X, ",array[i]);
        fprintf( fontTxt, "%s",buf);
    }
    fclose(fontTxt);
    
    return size;
}

#endif



