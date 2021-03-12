
#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "RH_gui_font.h"

static struct{
    __GUI_Font_t       info;
    E_GUI_FontStyle_t  style;
    int                size;
    float              scale;
    
    stbtt_fontinfo     stb_info;
    uint8_t*           font_data;
}Font = {0};

#if defined (__WIN32)
#include <direct.h>
static const char* font_path[kGUI_NUM_FontStyle] = {
    "../Glucoo/Font/Courier New.ttf"        ,
    "../Glucoo/Font/Courier New Italic.ttf" ,
    "../Glucoo/Font/Courier New Bold.ttf"
};
#elif defined  (__APPLE__)
#include <unistd.h>
static const char* font_path[kGUI_NUM_FontStyle] = {
    "/Users/randle_h/Desktop/Glucoo-Simulation-MacOS/Glucoo/Font/Courier New.ttf"        ,
    "/Users/randle_h/Desktop/Glucoo-Simulation-MacOS/Glucoo/Font/Courier New Italic.ttf" ,
    "/Users/randle_h/Desktop/Glucoo-Simulation-MacOS/Glucoo/Font/Courier New Bold.ttf"
};
#endif



static void  __attribute__((constructor)) __gui_font_init(void){
    GUI_SetFontStyle( kGUI_FontStyle_CourierNew );
    GUI_SetFontSize ( 24 );
    
}

static E_Status_t __gui_font_read( const char* path ){
//    char buf[300] = {0};
//    getcwd( buf,300 );
//    printf("%s\n",buf);
    FILE* fontFile = fopen( path , "rb" );
    __exitReturn( !fontFile, kStatus_BadAccess );
    
    fseek(fontFile, 0, SEEK_END);
    size_t size = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);
    
    if( !Font.font_data ){
        free(Font.font_data);
    }
    
    Font.font_data = calloc(size, sizeof(uint8_t));
    
    fread(Font.font_data, size, sizeof(uint8_t), fontFile);
    fclose(fontFile);
    
    return kStatus_Success;
}

void GUI_SetFontStyle(E_GUI_FontStyle_t style){
    switch(style){
        case kGUI_FontStyle_CourierNew:
        case kGUI_FontStyle_CourierNew_Italic:
        case kGUI_FontStyle_CourierNew_Bold:
            __gui_font_read( font_path[style] );
            stbtt_InitFont(&Font.stb_info, Font.font_data, 0);
            break;
        default:
            return;
    }
    Font.style = style;
    Font.scale       = stbtt_ScaleForPixelHeight( &Font.stb_info, Font.size );
    stbtt_GetFontVMetrics( &Font.stb_info, &Font.info.ascent, &Font.info.descent, &Font.info.lineGap );
    Font.info.ascent  = roundf(Font.info.ascent * Font.scale);
    Font.info.descent = roundf(Font.info.descent * Font.scale);
}

void GUI_SetFontSize(int size){
    Font.size        = size;
    Font.scale       = stbtt_ScaleForPixelHeight( &Font.stb_info, Font.size );
    stbtt_GetFontVMetrics( &Font.stb_info, &Font.info.ascent, &Font.info.descent, &Font.info.lineGap );
    Font.info.ascent  = roundf(Font.info.ascent * Font.scale);
    Font.info.descent = roundf(Font.info.descent * Font.scale);
}

int GUI_GetFontSize(void){
    return Font.size;
}

E_GUI_FontStyle_t GUI_GetFontStyle(void){
    return Font.style;
}

#define STB_OUTPUT_FONT_PNG

#ifdef STB_OUTPUT_FONT_PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif
__GUI_Font_t* __attribute__((warn_unused_result)) GUI_ExportFontChar(uint16_t unicode){
    int c_x1 , c_y1 , c_x2 , c_y2;
    stbtt_GetCodepointBitmapBox(&Font.stb_info, unicode, Font.scale, Font.scale, &c_x1, &c_y1, &c_x2, &c_y2);
    Font.info.height = c_y2-c_y1;
    Font.info.width  = c_x2-c_x1;
    
    if( Font.info.output ){
        free(Font.info.output);
    }
    Font.info.output = calloc( Font.info.height*Font.info.width , sizeof(uint8_t) );
    
    stbtt_MakeCodepointBitmap( &Font.stb_info, Font.info.output, (int)Font.info.width, (int)Font.info.height, (int)Font.info.width, Font.scale, Font.scale, unicode );
#ifdef STB_OUTPUT_FONT_PNG
    stbi_write_png("/Users/randle_h/Desktop/output.png", (int)Font.info.width, (int)Font.info.height, 1, Font.info.output, (int)Font.info.width);
    printf("ascent = %d\n"   , Font.info.ascent);
    printf("descent = %d\n"  , Font.info.descent);
    printf("lineGap = %d\n"   , Font.info.lineGap);
#endif
    return &Font.info;
}

__GUI_Font_t* __attribute__((warn_unused_result)) GUI_ExportFontStr( const char* str ){
    
    if( Font.info.output ){
        free(Font.info.output);
    }
    
    size_t len = strlen(str);
    
    Font.info.height = Font.size;
    Font.info.width  = 0;
    int* xs  = (int*)calloc(len,sizeof(int));
    int* ys  = (int*)calloc(len,sizeof(int));
    int* c_x = (int*)malloc(len*sizeof(int));
    int* c_y = (int*)malloc(len*sizeof(int));
    int* adv = (int*)malloc(len*sizeof(int));
    int* lfB = (int*)malloc(len*sizeof(int));
    for(int i=0; i<len; i++){
        int advanceWidth    = 0;
        int leftSideBearing = 0;
        stbtt_GetCodepointHMetrics( &Font.stb_info, str[i], &advanceWidth, &leftSideBearing );
        
        
        int c_x1 = 0, c_y1 = 0, c_x2 = 0, c_y2 = 0;
        stbtt_GetCodepointBitmapBox(&Font.stb_info, str[i], Font.scale, Font.scale, &c_x1, &c_y1, &c_x2, &c_y2);
        c_x[i] = c_x2-c_x1;
        c_y[i] = c_y2-c_y1;
        
        adv[i] = roundf( advanceWidth*Font.scale );
        lfB[i] = roundf( leftSideBearing*Font.scale );
        Font.info.width += adv[i];
        if(i!=0)
            xs[i]  = xs[i-1] + adv[i];
        ys[i]  = Font.info.ascent + c_y1;

    }
    
    Font.info.output = calloc(Font.info.width*Font.info.height, sizeof(uint8_t));
    
    for(int i=0; i<len; i++){
        size_t byteOffset = ( lfB[i] + ys[i]*Font.info.width + xs[i] );
        stbtt_MakeCodepointBitmap(&Font.stb_info, Font.info.output+byteOffset, c_x[i], c_y[i], (int)(Font.info.width), Font.scale, Font.scale, str[i]);
    }
    free(xs);
    free(ys);
    free(c_x);
    free(c_y);
    free(adv);
    free(lfB);
#ifdef STB_OUTPUT_FONT_PNG
    stbi_write_png("/Users/randle_h/Desktop/output.png", (int)Font.info.width, (int)Font.info.height, 1, Font.info.output, (int)Font.info.width);
#endif
    return &Font.info;
}


