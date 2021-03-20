
#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "RH_font.h"

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
    "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Courier New.ttf"        ,
    "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Courier New Italic.ttf" ,
    "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Courier New Bold.ttf"
};
#endif



static void  RH_PREMAIN __gui_font_init(void){
    __Font_setStyle( kGUI_FontStyle_CourierNew );
    __Font_setSize ( 24 );
}

static E_Status_t __gui_font_read( const char* path ){
//    char buf[300] = {0};
//    getcwd( buf,300 );
//    printf("%s\n",buf);
    FILE* fontFile = fopen( path , "rb" );
#ifdef RH_DEBUG
    ASSERT( fontFile );
#endif
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

void __Font_setStyle(E_GUI_FontStyle_t style){
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

void __Font_setSize(int size){
    Font.size        = size;
    Font.scale       = stbtt_ScaleForPixelHeight( &Font.stb_info, Font.size );
    stbtt_GetFontVMetrics( &Font.stb_info, &Font.info.ascent, &Font.info.descent, &Font.info.lineGap );
    Font.info.ascent  = roundf(Font.info.ascent * Font.scale);
    Font.info.descent = roundf(Font.info.descent * Font.scale);
}

int __Font_getSize(void){
    return Font.size;
}

E_GUI_FontStyle_t __Font_getStyle(void){
    return Font.style;
}

#define STB_OUTPUT_FONT_PNG

#ifdef STB_OUTPUT_FONT_PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif
__GUI_Font_t*  __Font_exportChar(uint16_t unicode){
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

__GUI_Font_t*  __Font_exportStr( const char* str ){
    
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

void __Font_getCharSize( size_t *width, size_t *height, char c ){
    int c_x1 , c_y1 , c_x2 , c_y2;
    stbtt_GetCodepointBitmapBox(&Font.stb_info, c, Font.scale, Font.scale, &c_x1, &c_y1, &c_x2, &c_y2);
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
        stbtt_GetCodepointHMetrics( &Font.stb_info, str[i], &advanceWidth, &leftSideBearing );
    
        if( width )
            *width += roundf( advanceWidth*Font.scale );;
    }
    if( height )
        *height = Font.size;
}

#include "RH_data.h"
__GUI_Font_t*  __Font_exportText_Justify( const char* str, size_t width ){
    
    // 释放之前的缓存数据
    if( Font.info.output ){
        free(Font.info.output);
        Font.info.output = NULL;
    }
    Font.info.width = width;
    
    // 获取空格的最小像素宽度,为改字体下的空格所占宽度的一半.
    size_t spW = 0;
    size_t spH = 0;
    __Font_getCharSize(&spW, &spH, 'I' );
    spW >>= 1;
    
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

    __GUI_Font_t *pd = __Font_exportStr(WordInfo.str); printf("%ld\n",WordInfo.pixsW);
    
    
    
    
    char* p = NULL;
    while( (p = strtok(NULL," ")) != NULL ){
        WordInfo_t* pWordInfo = alloca(sizeof(WordInfo_t));
        pWordInfo->str   = p;
        pWordInfo->pixsW = 0;
//        for(int i=0; i<strlen(WordInfo.str); i++){
//            size_t w = 0;
//            __Font_getCharSize(&w, NULL, pWordInfo->str[i]);
//            pWordInfo->pixsW += w;
//        }
        __Font_getStrSize( &pWordInfo->pixsW, NULL, pWordInfo->str );
        
        __LINK_DB_addTail( pTextHead, pWordInfo );
    }
    

    const __LinkDB_t* pIter1 = pTextHead;
    const __LinkDB_t* pIter2 = pTextHead;
    const __LinkDB_t* pIter  = pTextHead;
/* 此处可以测试,句子信息是否提取准确 */
    pIter  = pTextHead;
    do{
        printf("%s\t\tlen=%ld\n", ((WordInfo_t*)pIter->object)->str,((WordInfo_t*)pIter->object)->pixsW);
        pIter = pIter->pNext;
    }while( pIter );
    
    size_t pixCnt   = 0;          // 用于记录一行已使用的像素栏
    size_t wordCnt  = 0;          // 用于记录一行单词有多少个
    size_t spCnt    = 0;          // 用于记录一行单词间隙有多少个, 永远等于单词数减1
    size_t spExtra  = 0;          // 一行单词出去基本空格单元像素(spW)点后,额外的所有空格占用的像素点
    size_t spAvg    = 0;          // 平均每个单词间隙空格占用的像素点
    size_t spRemain = 0;          // spAvg的余数
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
            
            printf("[word]%ld\n", wordCnt);
            while( spCnt-- ){
                printf("spaceExtra: %ld [str]: %s\t\n",spExtra,((WordInfo_t*)(pIter2->object))->str );
                // 插入空格字符
                WordInfo_t* wi = alloca(sizeof(WordInfo_t));
                wi->str   = NULL;    // 这是一个间隔空白字符,
                wi->pixsW = spW + spAvg + ((spRemain==0)?(0):((spRemain--)!=0));
                
                pIter2 = __LINK_DB_insert( pTextHead, pIter2->object , wi )->pNext;
            }printf("spaceExtra: %ld [str]: %s\t\n",spExtra,((WordInfo_t*)(pIter2->object))->str );


#ifdef RH_DEBUG
            if( pIter1 )
                ASSERT( pIter1->pPrev==pIter2 );
            else
                ASSERT( pIter2->pNext==pIter1 );
#endif
            // 插入回车字符
            WordInfo_t* wi = alloca(sizeof(WordInfo_t));
            wi->str   = "\n";    // 这是一个回车字符,当读取到此需要换行
            wi->pixsW = 0;
            pIter2 = __LINK_DB_insert( pTextHead, pIter2->object , wi )->pNext;
#ifdef RH_DEBUG
            ASSERT( pIter1==pIter2 );
#endif
            pixCnt  = 0;
            wordCnt = 0;
            
        }

        
    }while( pIter1!=NULL || pIter2!=NULL );
    
/* 此处可以测试,句子信息是否提取准确 */
    pIter  = pTextHead;
    do{
        if( ((WordInfo_t*)pIter->object)->str==NULL ){
            printf(" #%ld ",((WordInfo_t*)pIter->object)->pixsW);
            pIter = pIter->pNext;
            continue;
        }
        printf("%s", ((WordInfo_t*)pIter->object)->str);
        pIter = pIter->pNext;
    }while( pIter );
     
    __LINK_DB_removeAll(pTextHead);
    return &Font.info;
}

