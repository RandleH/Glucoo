
#include <stdio.h>
#include "RH_image.h"

#ifdef __cplusplus
extern "C" {
#endif


/*===========================================================================================================================
 > Image Processing Reference
============================================================================================================================*/
#if defined    (_WIN32)
#include <windows.h>
//#elif defined  (__APPLE__)
#else
typedef uint8_t   BYTE;
typedef uint16_t  WORD;
typedef uint32_t  DWORD;
typedef int32_t   LONG;
typedef float     FLOAT;
typedef FLOAT     *PFLOAT;
typedef BYTE      *PBYTE;
typedef BYTE      *LPBYTE;
typedef int       *PINT;
typedef int       *LPINT;
typedef WORD      *PWORD;
typedef WORD      *LPWORD;
typedef int32_t   *LPLONG;
typedef DWORD     *PDWORD;
typedef DWORD     *LPDWORD;
typedef void      *LPVOID;
#pragma pack(1)
typedef struct tagBITMAPFILEHEADER {
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
} BITMAPFILEHEADER;

#pragma pack(1)
typedef struct tagBITMAPINFOHEADER {
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} BITMAPINFOHEADER;

#endif

    
    
#define PNG_CHUNK(a,b,c,d)      (uint32_t)((( a )<<24)|(( b )<<16)|(( c )<<8)|( d ))

// Critical chunks
#define PNG_IHDR                PNG_CHUNK('I','H','D','R')
#define PNG_PLTE                PNG_CHUNK('P','L','T','E')
#define PNG_IDAT                PNG_CHUNK('I','D','A','T')
#define PNG_IEND                PNG_CHUNK('I','E','N','D')


// Ancillary chunks
/// Transparency information
#define PNG_tRNS                PNG_CHUNK('t','R','N','S')

/// Colour space information
#define PNG_cHRM                PNG_CHUNK('c','H','R','M')
#define PNG_gAMA                PNG_CHUNK('g','A','M','A')
#define PNG_iCCP                PNG_CHUNK('i','C','C','P')
#define PNG_sBIT                PNG_CHUNK('s','B','I','T')
#define PNG_sRGB                PNG_CHUNK('s','R','G','B')

/// Textual information
#define PNG_tEXt                PNG_CHUNK('t','E','X','t')
#define PNG_zEXt                PNG_CHUNK('z','E','X','t')
#define PNG_iEXt                PNG_CHUNK('i','E','X','t')
    
/// Miscellaneous information
#define PNG_bKGD                PNG_CHUNK('b','K','G','D')
#define PNG_hIST                PNG_CHUNK('h','I','S','T')
#define PNG_pHYs                PNG_CHUNK('p','H','Y','s')
#define PNG_sPLT                PNG_CHUNK('s','P','L','T')

/// Time stamp information
#define PNG_tIME                PNG_CHUNK('t','I','M','E')

__ImageBIN_t*    __ImgBIN_load_bmp         (const char* __restrict__ path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    __ImageBIN_t* pIMG = RH_MALLOC(sizeof(__ImageBIN_t));
    pIMG->height  = 0;
    pIMG->width   = 0;
    pIMG->pBuffer = NULL;

    bmp = fopen(path, "r");
    if (bmp == NULL) {
        // printf("open error\n");
        return pIMG;
    }
    fseek(bmp, 0L, SEEK_SET);
    fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, bmp);
    fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, bmp);

    if (fileHead.bfType != 0x4D42) {
        printf("This not a *.bmp file\n");
        return pIMG;
    }
    printf( "(w,h) = (%d, %d)\n", infoHead.biWidth , infoHead.biHeight);
    printf( "biBitCount = %d\n" , infoHead.biBitCount);
    
    size_t page   = (__RND8(infoHead.biHeight)>>3);
    size_t col    = infoHead.biWidth;
    pIMG->pBuffer = RH_CALLOC( page*col, sizeof(uint8_t) );
    pIMG->height  = infoHead.biHeight;
    pIMG->width   = infoHead.biWidth;
    
    size_t BPL  = __RND4( (infoHead.biWidth>>3)+((infoHead.biWidth&0x07)!=0) ); /* Bytes Per Line */
#ifdef RH_DEBUG
    RH_ASSERT( BPL==infoHead.biSizeImage/infoHead.biHeight );
#endif
    fseek(bmp, fileHead.bfOffBits, SEEK_SET);
    
    uint8_t* pTmp = RH_MALLOC( BPL );
    for( int row=0; row<infoHead.biHeight; row++ ){
        fread( pTmp, sizeof(uint8_t), BPL, bmp );
        for( int col=0; col<BPL; col++ ){
            for(size_t cnt=0; cnt<8; cnt++){
                if( col*8 + cnt < infoHead.biWidth ){
                    pIMG->pBuffer[ (row/8)*infoHead.biWidth + col*8 + cnt ].data |= ( ( (pTmp[col]>>(7-cnt))&0x01 ) << (7-row%8) );
                }
                else
                    break;
            }
            
        }
    }
    fclose(bmp);
    RH_FREE(pTmp);

    
    // Reverse page data.
    for( int p=0; p<(page>>1); p++ ){
        __memexch( &pIMG->pBuffer[ p*infoHead.biWidth ], &pIMG->pBuffer[ (page-p-1)*infoHead.biWidth ], infoHead.biWidth*sizeof(uint8_t) );
    }
    
    size_t dummyBit =  (page<<3) - infoHead.biHeight ;
    for( int p=0; p<page; p++ ){
        for( int c=0; c<col; c++ ){
            if( p+1 < page ){
                uint16_t tmp = (uint16_t)(((pIMG->pBuffer[ (p+1)*col+c ].data)<<8) | (pIMG->pBuffer[  p   *col+c ].data) );
                tmp >>= dummyBit;
                pIMG->pBuffer[  p*col+c ].data = (uint8_t)(tmp);
            }else{
                pIMG->pBuffer[  p*col+c ].data >>= dummyBit;
            }
        }
    }
//    for( int p=0; p<page; p++ ){
//        for( int c=0; c<col; c++ ){
//            printf("%02X ", pIMG->pBuffer[  p*col+c ].data);
//        }
//        printf("\n");
//    }
    
    return pIMG;
}
    
__ImageBIN_t*    __ImgBIN_create           (size_t width,size_t height){
    __ImageBIN_t* pIMG = RH_MALLOC(sizeof(__ImageBIN_t));
    __exitReturn( !pIMG, NULL );
    pIMG->height          = height;
    pIMG->width           = width;
    pIMG->pBuffer         = RH_CALLOC((__RND8(height)>>3)*(pIMG->width), sizeof(uint8_t));
    
    if(pIMG->pBuffer == NULL){
        RH_FREE(pIMG);
        return NULL;
    }
    return pIMG;
}
    
__ImageBIN_t*    __ImgBIN_copy             (const __ImageBIN_t* src,__ImageBIN_t* dst){
    __exitReturn( src==NULL         ||dst==NULL          , dst );
    __exitReturn( src->pBuffer==NULL||dst->pBuffer==NULL , dst );
    
    memcpy(dst->pBuffer, src->pBuffer, (__RND8(src->height)>>3)*(src->width)*sizeof(__UNION_PixelBIN_t));
    dst->height = src->height;
    dst->width  = src->width;
    return dst;
}
    
__ImageBIN_t*    __ImgBIN_out_bmp          (const char* __restrict__ path,__ImageBIN_t* p){
    __exitReturn(p == NULL && p->pBuffer == NULL , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn(bmp == NULL, NULL);
    
    size_t BPL  = __RND4( (p->width>>3)+((p->width&0x07)!=0) ); /* Bytes Per Line */
    
    BITMAPFILEHEADER fileHead = {
        .bfType      = 0x4d42  ,
        .bfSize      = 458     , //(uint32_t)((__RND8(p->height)>>3)*(p->width)*sizeof(__UNION_PixelBIN_t) + 54) ,
        .bfReserved1 = 0       ,
        .bfReserved2 = 0       ,
        .bfOffBits   = 62      ,
    };
    
    BITMAPINFOHEADER infoHead = {
        .biBitCount  = 1              ,
        .biSize      = 40             ,
        .biWidth     = (int)p->width  ,
        .biHeight    = (int)p->height ,
        .biPlanes    = 1              ,
        .biSizeImage = (DWORD)( BPL*p->height )
    };
    
    const uint8_t color_plane[8] = {0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00};
    
    fseek(bmp,0L,SEEK_SET);
    fwrite(&fileHead ,1 ,sizeof(BITMAPFILEHEADER) , bmp);
    fwrite(&infoHead ,1 ,sizeof(BITMAPINFOHEADER) , bmp);
    fseek(bmp,54L,SEEK_SET);
    fwrite(color_plane ,1 ,8 , bmp);
    fseek(bmp,fileHead.bfOffBits,SEEK_SET);
    
#ifdef RH_DEBUG
    RH_ASSERT( BPL==infoHead.biSizeImage/infoHead.biHeight );
#endif
    
    uint8_t* pTmp = RH_CALLOC( infoHead.biSizeImage, sizeof(uint8_t) );
    
    for( int row=0; row<p->height; row++ ){
        for( int col=0; col<BPL; col++ ){
            for(size_t cnt=0; cnt<8; cnt++){
                if( (col<<3)+cnt < p->width ){
                    pTmp[ row*BPL + col ] |= (((p->pBuffer[ (row/8)*p->width + (col<<3)+cnt ].data)>>(row%8))&0x01)<<(7-cnt);
                }else{
                    break;
                }
            }
        }
    }
    
    for( int row=0; row<(p->height>>1); row++ ){
        __memexch(&pTmp[row*BPL], &pTmp[(p->height-row-1)*BPL], BPL);
    }

//    for( int row=0; row<p->height; row++ ){
//        for( int c=0; c<BPL; c++ ){
//            printf("%02X ", pTmp[  row*BPL + c ]);
//        }
//        printf("\n");
//    }
    
    fwrite( pTmp, 1, infoHead.biSizeImage*sizeof(uint8_t), bmp );
    
    fclose(bmp);
    RH_FREE(pTmp);
    return p;
}

__ImageRGB565_t* __ImgRGB565_load_bmp      (const char* __restrict__ path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    __ImageRGB565_t* pIMG = RH_MALLOC(sizeof(__ImageRGB565_t));
    pIMG->height  = 0;
    pIMG->width   = 0;
    pIMG->pBuffer = NULL;

    bmp = fopen(path, "r");
    if (bmp == NULL) {
        // printf("open error\n");
        return pIMG;
    }
    fseek(bmp, 0L, SEEK_SET);
    fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, bmp);
    fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, bmp);

    if (fileHead.bfType != 0x4D42) {
        printf("This not a *.bmp file\n");
        return pIMG;
    }
    printf( "(w,h) = (%d, %d)\n", infoHead.biWidth , infoHead.biHeight);
    printf( "biBitCount = %d\n" , infoHead.biBitCount);

    fseek(bmp, fileHead.bfOffBits, SEEK_SET);

    pIMG->pBuffer = (__UNION_PixelRGB565_t*)RH_MALLOC(infoHead.biWidth * infoHead.biHeight * sizeof(__UNION_PixelRGB565_t));
    
    for (int row = 0; row < infoHead.biHeight; row++) {
        for (int col = 0; col < infoHead.biWidth; col++) {
            fread(&(pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data), sizeof(__PixelRGB565_t), 1, bmp);
            // printf("%d ",pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data);
        }
        int eps = (4-(infoHead.biWidth*sizeof(__PixelRGB565_t))%4)%4;
        uint8_t dummyByte;
        while(eps--){
            fread(&dummyByte,sizeof(char) ,1 , bmp);
        }
        // printf("\n");
    }
    fclose(bmp);

    pIMG->width   = infoHead.biWidth;
    pIMG->height  = infoHead.biHeight;

    return pIMG;
}

__ImageRGB565_t* __ImgRGB565_create        (size_t width,size_t height){
    __ImageRGB565_t* pIMG = RH_MALLOC(sizeof(__ImageRGB565_t));
    __exitReturn( !pIMG, NULL );
    pIMG->height          = height;
    pIMG->width           = width;
    pIMG->pBuffer         = RH_CALLOC((pIMG->height)*(pIMG->width), sizeof(pIMG->pBuffer[0]));
    if(pIMG->pBuffer == NULL){
        RH_FREE(pIMG);
        return NULL;
    }
    return pIMG;
}

__ImageRGB565_t* __ImgRGB565_copy          (const __ImageRGB565_t* src,__ImageRGB565_t* dst){
    __exitReturn( src==NULL         ||dst==NULL          , dst );
    __exitReturn( src->pBuffer==NULL||dst->pBuffer==NULL , dst );

    memcpy(dst->pBuffer, src->pBuffer, (src->height)*(src->width)*sizeof(__UNION_PixelRGB565_t));
    dst->height = src->height;
    dst->width  = src->width;
    return dst;
}

__ImageRGB565_t* __ImgRGB565_out_bmp       (const char* __restrict__ path,__ImageRGB565_t* p){
    __exitReturn(p == NULL && p->pBuffer == NULL , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn(bmp == NULL, NULL);

    int eps = (4-(p->width*sizeof(__PixelRGB565_t))%4)%4;
    BITMAPFILEHEADER fileHead = {
        .bfOffBits      = 40 + 14   ,
        .bfReserved1    = 0         ,
        .bfReserved2    = 0         ,
        .bfSize         = (uint32_t)(p->height * p->width * sizeof(__PixelRGB565_t) + 54),
        .bfType         = 0x4D42    ,
    };
    BITMAPINFOHEADER infoHead = {
        .biSize          = 40        ,
        .biWidth         = (int)(p->width)  ,
        .biHeight        = (int)(p->height) ,
        .biPlanes        = 1         ,
        .biBitCount      = 5+6+5     ,
        .biCompression   = 0         ,
        .biSizeImage     = (uint32_t)(p->height*p->width*sizeof(__PixelRGB565_t) + eps*(p->height)) ,
        .biClrUsed       = 0         ,
        .biClrImportant  = 0         ,
        .biXPelsPerMeter = 0         ,
        .biYPelsPerMeter = 0         ,
    };

    // RGB Sequence should be reversed.
    fseek(bmp,0L,SEEK_SET);
    fwrite(&fileHead ,1 ,sizeof(BITMAPFILEHEADER) , bmp);
    fwrite(&infoHead ,1 ,sizeof(BITMAPINFOHEADER) , bmp);
    fseek(bmp,54L,SEEK_SET);
    for (int row = 0; row < p->height; row++) {
        for (int col = 0; col < p->width; col++) {
            fwrite( &p->pBuffer[(infoHead.biHeight - row - 1) * infoHead.biWidth + col] ,sizeof(__PixelRGB565_t) ,1 ,bmp );
        }
        int eps = (4-(infoHead.biWidth*sizeof(__PixelRGB565_t))%4)%4;
        uint8_t dummyByte = 0x00;
        while(eps--){
            fwrite(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    
    fclose(bmp);
    return p;
}
    
__ImageRGB888_t* __ImgRGB888_load_bmp      (const char* __restrict__ path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    __ImageRGB888_t* pIMG = RH_MALLOC(sizeof(__ImageRGB888_t));
    pIMG->height  = 0;
    pIMG->width   = 0;
    pIMG->pBuffer = NULL;
    
    bmp = fopen(path, "r");
    if (bmp == NULL) {
        // printf("open error\n");
        return pIMG;
    }
    fseek(bmp, 0L, SEEK_SET);
    fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, bmp);
    fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, bmp);

    if (fileHead.bfType != 0x4D42) {
        // printf("This not a *.bmp file\n");
        return pIMG;
    }

    fseek(bmp, fileHead.bfOffBits, SEEK_SET);

    pIMG->pBuffer = (__UNION_PixelRGB888_t*)RH_MALLOC(infoHead.biWidth * infoHead.biHeight * sizeof(__UNION_PixelRGB888_t));
    
    for (int row = 0; row < infoHead.biHeight; row++) {
        for (int col = 0; col < infoHead.biWidth; col++) {
            fread(&(pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data), sizeof(__PixelRGB888_t), 1, bmp);
        }
        int eps = (4-(infoHead.biWidth*sizeof(__PixelRGB888_t))%4)%4;
        uint8_t dummyByte;
        while(eps--){
            fread(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    fclose(bmp);

    pIMG->width   = infoHead.biWidth;
    pIMG->height  = infoHead.biHeight;

    return pIMG;
}

#if 0
__ImageRGB888_t* __ImgRGB888_load_png      (const char* __restrict__ path){
#pragma pack(1)
struct {
//    uint32_t chunk_data_lenth;
//    uint32_t chunk_type_code;
    uint32_t width;                 /* __SWAP_DWORD */
    uint32_t height;                /* __SWAP_DWORD */

    uint8_t  bit_depth;
    uint8_t  color_type;
    uint8_t  compress_method;
    uint8_t  filter_method;
    uint8_t  interlace_method;
    //...//
    
//    uint32_t CRC;
}IHDR;
    
    
    FILE*   png;
    
    __ImageRGB888_t* pIMG = RH_MALLOC(sizeof(__ImageRGB888_t));
#ifdef RH_DEBUG
    RH_ASSERT( pIMG );
#endif
    pIMG->height  = 0;
    pIMG->width   = 0;
    pIMG->pBuffer = NULL;
    
    // 打开文件
    png = fopen(path, "r");
#ifdef RH_DEBUG
    RH_ASSERT( png );
#endif
    fseek(png,0L,SEEK_END);
    size_t  f_size = ftell(png);
    fseek(png,0L,SEEK_SET);
    
    // 检查PNG固定签名
#ifdef RH_DEBUG
    const uint8_t pngHead[8]     = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
    uint8_t       pngHeadRead[8] = {0};
    for( int8_t i=0; i<8; i++ ){
        fread(&pngHeadRead[i], 1, 1, png);
        RH_ASSERT( pngHeadRead[i] == pngHead[i] );
    }
#endif
    
    uint32_t chunk_data_lenth = 0x00000000;
    uint32_t chunk_type_code  = 0x00000000;
    while( ftello(png) < f_size ){
        uint8_t temp = 0x00;
        chunk_data_lenth <<= 8;
        chunk_data_lenth  |= (uint8_t)(chunk_type_code>>24);
        fread( &temp, sizeof(temp), 1, png );
        chunk_type_code  <<= 8;
        chunk_type_code   |= temp;
        
        switch( chunk_type_code ){
            case PNG_IHDR:  // 解析 <IHDR> Image Header
                fread( &IHDR, sizeof(IHDR), 1, png );
#ifdef RH_DEBUG
                RH_ASSERT( chunk_data_lenth == sizeof(IHDR) );
                RH_ASSERT( IHDR.bit_depth  == 0x08 ); //
                RH_ASSERT( IHDR.color_type == 0x06 || IHDR.color_type==0x02 ); // 8/16bit 真彩色
#endif
                pIMG->width   = __SWAP_DWORD(IHDR.width);
                pIMG->height  = __SWAP_DWORD(IHDR.height);
                break;
            case PNG_PLTE:  // 解析 <PLTE> Palette
                //...//
                break;
            case PNG_IDAT:  // 解析 <IDAT> Image data
                //...//
                break;
            case PNG_IEND:  // 解析 <IEND> Image trailer
                //...//
                break;
                
            case PNG_tRNS:
                 RH_ASSERT(false);
                break;
                
            case PNG_cHRM:
                 RH_ASSERT(false);
                break;    
            case PNG_gAMA:
                 RH_ASSERT(false);
                break;    
            case PNG_iCCP:
                //...//
                break;    
            case PNG_sBIT:
                 RH_ASSERT(false);
                break;    
            case PNG_sRGB:
                 RH_ASSERT(false);
                break;    


            case PNG_tEXt:
                 RH_ASSERT(false);
                break;    
            case PNG_zEXt:
                 RH_ASSERT(false);
                break;    
            case PNG_iEXt:
                 RH_ASSERT(false);
                break;    

            case PNG_bKGD:
                 RH_ASSERT(false);
                break;    
            case PNG_hIST:
                 RH_ASSERT(false);
                break;
            case PNG_pHYs:
                 RH_ASSERT(false);
                break;    
            case PNG_sPLT:
                 RH_ASSERT(false);
                break;    

            case PNG_tIME:
                 RH_ASSERT(false);
                break;

            default:
                break;
        }
    }
    
    fclose(png);
    
    return pIMG;
}
#endif

__ImageRGB888_t* __ImgRGB888_copy          (const __ImageRGB888_t* src,__ImageRGB888_t* dst){
    __exitReturn( src==NULL         ||dst==NULL          , dst );
    __exitReturn( src->pBuffer==NULL||dst->pBuffer==NULL , dst );

    memcpy(dst->pBuffer, src->pBuffer, (src->height)*(src->width)*sizeof(__UNION_PixelRGB888_t));
    dst->height = src->height;
    dst->width  = src->width;
    return dst;
}

__ImageRGB888_t* __ImgRGB888_create        (size_t width,size_t height){
    __ImageRGB888_t* pIMG = RH_MALLOC(sizeof(__ImageRGB888_t));
    if(pIMG == NULL)
        return NULL;
    pIMG->height          = height;
    pIMG->width           = width;
    pIMG->pBuffer         = RH_MALLOC((pIMG->height)*(pIMG->width)*sizeof(pIMG->pBuffer[0]));
    if(pIMG->pBuffer == NULL){
        RH_FREE(pIMG);
        return NULL;
    }
    memset(pIMG->pBuffer, 0, (pIMG->height)*(pIMG->width)*sizeof(pIMG->pBuffer[0]));
    return pIMG;
}

__ImageRGB888_t* __ImgRGB888_out_bmp       (const char* __restrict__ path,__ImageRGB888_t* p){
    __exitReturn(p == NULL && p->pBuffer == NULL , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn(bmp == NULL, NULL);

    int eps = (4-(p->width*sizeof(__PixelRGB888_t))%4)%4;
    BITMAPFILEHEADER fileHead = {
        .bfOffBits      = 40 + 14   ,
        .bfReserved1    = 0         ,
        .bfReserved2    = 0         ,
        .bfSize         = (uint32_t)(p->height * p->width * sizeof(__PixelRGB888_t) + 54),
        .bfType         = 0x4D42    ,
    };
    BITMAPINFOHEADER infoHead = {
        .biSize          = 40        ,
        .biWidth         = (int)(p->width)  ,
        .biHeight        = (int)(p->height) ,
        .biPlanes        = 1         ,
        .biBitCount      = 8+8+8     ,
        .biCompression   = 0         ,
        .biSizeImage     = (uint32_t)(p->height*p->width*sizeof(__PixelRGB888_t) + eps*(p->height)) ,
        .biClrUsed       = 0         ,
        .biClrImportant  = 0         ,
        .biXPelsPerMeter = 0         ,
        .biYPelsPerMeter = 0         ,
    };
     printf("%d\n" ,infoHead.biSizeImage    );
   

    // RGB Sequence should be reversed.
    fseek(bmp,0L,SEEK_SET);
    fwrite(&fileHead ,1 ,sizeof(BITMAPFILEHEADER) , bmp);
    fwrite(&infoHead ,1 ,sizeof(BITMAPINFOHEADER) , bmp);
    fseek(bmp,54L,SEEK_SET);
    for (int row = 0; row < p->height; row++) {
        for (int col = 0; col < p->width; col++) {
            fwrite( &p->pBuffer[(infoHead.biHeight - row - 1) * infoHead.biWidth + col] ,sizeof(__PixelRGB888_t) ,1 ,bmp );
        }
        int eps = (4-(infoHead.biWidth*sizeof(__PixelRGB888_t))%4)%4;
        uint8_t dummyByte = 0x00;
        while(eps--){
            fwrite(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    
    fclose(bmp);
    return p;
}

__ImageRGB888_t* __ImgRGB888_free_buffer   (__ImageRGB888_t*      ptr){
    RH_FREE(ptr->pBuffer);
    ptr->height  = 0;
    ptr->width   = 0;
    ptr->pBuffer = NULL;
    return ptr;
}

void             __ImgRGB888_free          (__ImageRGB888_t*      ptr){
    RH_FREE(__ImgRGB888_free_buffer(ptr));
}

__ImageRGB888_t* __ImgRGB888_filter_gray   (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    
    if(src != NULL && dst != NULL){
        if(src->pBuffer != NULL && dst->pBuffer != NULL){
            for (int row = 0; row < src->height; row++) {
                for (int col = 0; col < src->width; col++) {
                    long temp = lroundl(0.299 * src->pBuffer[row * src->width + col].R + 0.587 * src->pBuffer[row * src->width + col].G + 0.114 * src->pBuffer[row * src->width + col].B);
                    dst->pBuffer[row * src->width + col].data = (uint32_t)(((temp&0xff)<<16)|((temp&0xff)<<8)|((temp&0xff)));
                }
            }
        }
    }
    return dst;
}

__ImageRGB888_t* __ImgRGB888_filter_cold   (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    return dst;
}

__ImageRGB888_t* __ImgRGB888_filter_warm   (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    
    return dst;
}

__ImageRGB888_t* __ImgRGB888_filter_OTUS   (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint32_t br_100){
    uint32_t threshold = 0;
    __exitReturn( src==NULL         , NULL);
    __exitReturn( src->pBuffer==NULL, NULL);
    __exitReturn( dst==NULL         , NULL);
    __exitReturn( dst->pBuffer==NULL, NULL);
    __ImgRGB888_data_OTUS(src, &threshold);
    __exitReturn(threshold == (uint32_t)(-1), NULL);
    
    for(int y=0;y<src->height;y++){
        for(int x=0;x<src->width;x++){
            uint8_t temp = ( __array1D(src->pBuffer, src->width, y, x)->R*19595 + \
                             __array1D(src->pBuffer, src->width, y, x)->G*38469 + \
                             __array1D(src->pBuffer, src->width, y, x)->B*7472 )>>16;
            if( temp > threshold )
                __array1D(dst->pBuffer, dst->width, y, x)->data = 0x00ffffff;
            else
                __array1D(dst->pBuffer, dst->width, y, x)->data = 0x00000000;
        }
    }
    
//    printf("otus threshold = %d\n", threshold);
    
    
    return NULL;
}
     
__ImageRGB888_t* __ImgRGB888_trans_mirror  (const __ImageRGB888_t* src,__ImageRGB888_t* dst,uint8_t HV){
    if( src == NULL || src->pBuffer == NULL ){
        return NULL;
    }
    if(dst == NULL){
        dst = (__ImageRGB888_t*)RH_MALLOC(sizeof(__ImageRGB888_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB888_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    if(dst->pBuffer == NULL){
        dst->pBuffer = (__UNION_PixelRGB888_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    switch(HV){
        case 0:
            for(size_t y=0;y<src->height;y++){
                for(size_t x=0;x<((src->width+1)>>1);x++){
                    __UNION_PixelRGB888_t tmp_fore = src->pBuffer[y*src->width + x];
                    __UNION_PixelRGB888_t tmp_back = src->pBuffer[y*src->width + src->width - 1 - x];
                    dst->pBuffer[y*src->width+x]                    = tmp_back;
                    dst->pBuffer[y*src->width + src->width - 1 - x] = tmp_fore;
                }
            }

            break;
        case 1:
            for(size_t y=0;y<src->height;y++){
                memmove(&dst->pBuffer[(src->height-1-y)*dst->width], &src->pBuffer[y*src->width], src->width*sizeof(__UNION_PixelRGB888_t));
            }
            break;
        default:
            //...//
            break;
    }
    
    return NULL;
}

__ImageRGB888_t* __ImgRGB888_blur_gussian  (const __ImageRGB888_t* src,__ImageRGB888_t* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    static __Kernel_t gus_kernel = {
        .pBuffer = NULL,
        .order   = 0,
        .sum     = 0,
    };
    static uint16_t radSize_old      = 0;
    
    if( radSize_old != radSize ){
        if( gus_kernel.pBuffer != NULL ){
            RH_FREE( gus_kernel.pBuffer );
        }
        double sigma  = __map(radSize, 0, 65535, 0.0, 10.0); // convert a normal value to sigma
        size_t order  = lround(sigma*6); // 6 times sigma includes 99% area.
        gus_kernel.pBuffer = (uint16_t*)RH_MALLOC( order*order*sizeof(uint16_t) );
        
        if((order & 0x01) == 0) // order should be an odd number.
            order--;
        if(order>=31) // too big!!!
            order = 31;
        __gussianKernel(sigma,order,&gus_kernel);
    }

    __ImageRGB888_t* pImg = __ImgRGB888_conv2D(src, dst,&gus_kernel,br_100);
    
    radSize_old      = radSize;

    return pImg;

}
    
__ImageRGB888_t* __ImgRGB888_blur_average  (const __ImageRGB888_t* src,__ImageRGB888_t* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    __exitReturn(src == NULL || dst == NULL , NULL);
    
    __UNION_PixelRGB888_t* pSrcData = src->pBuffer;
    __UNION_PixelRGB888_t* pDstData = dst->pBuffer;
    if(pSrcData == dst->pBuffer){
        RH_ASSERT(0);
        pDstData = RH_MALLOC(src->height*src->width*sizeof(__UNION_PixelRGB888_t));
    }
    
    size_t order = __limit(((radSize*60)>>16), 3, 101);
    if((order & 0x01) == 0) // order should be an odd number.
        order--;
    
    
{
    unsigned long sum_R = 0, sum_G = 0, sum_B = 0;
    unsigned long div = 0;
    
    int xs = area->xs;
    int ys = area->ys;
    int xe = (int)(area->xs + area->width -1);
    int ye = (int)(area->ys + area->height-1);
    
    // Pre-Calculation
    int half_order  = (int)((order+1)>>1); // Kernel
    div = half_order * half_order;
    
    if( (ys&0x01)==0 ){
        int iter = (int)(src->width*ys + xs);
        for(int n=ys; n < ys+half_order; n++, iter+=src->width){
            for(int m=xs; m < xs+half_order;m++, iter++){
                sum_R += pSrcData[iter].R;
                sum_G += pSrcData[iter].G;
                sum_B += pSrcData[iter].B;
            }
            iter-=half_order;
        }
    }
    else{
        int iter = (int)(src->width*(ye+1-half_order) + xe+1-half_order);
        for(int n=ye+1-half_order; n <= ye; n++, iter+=src->width){
            for(int m=xe+1-half_order; m <= xe;m++, iter++){
                sum_R += pSrcData[iter].R;
                sum_G += pSrcData[iter].G;
                sum_B += pSrcData[iter].B;
            }
            iter-=half_order;
        }
    }
    div = half_order * half_order;
    
    
    
// Average Filter Begin
    size_t target = 0;
    for(int j=ys; j <= ye; j++ ){
        
        if((j&0x01) == 0){ // Scan Direction:  [old] -->--> [new]
            for(int i=xs; i <= xe; i++, target++ ){
                if(i!=xs){
// No need to do when it reachs the left-edge because it has been done when moving to the next row.
// Remove leftmost column because it is old.
                    if(i-half_order >= xs){                    // [!] no cross the broad [0,src->width-1] [xs,xe]
                        
                        for(int row  = j-half_order+1,                                     \
                                iter = (int)(src->width*(j-half_order+1) + i-half_order);  \
                              
                            row<=j+half_order-1;                                           \
                            
                            row++,                                                         \
                            iter+=src->width){
                            if( row<=ye && row>=ys ){          // [!] no cross the broad [0,src->height-1] [ys,ye]
                                sum_R -= pSrcData[ iter ].R;
                                sum_G -= pSrcData[ iter ].G;
                                sum_B -= pSrcData[ iter ].B;
                                div--;
                            }
                        }
                    }
                    
// Add rightmost column because it is new.
                    if( i+half_order-1 <= xe ){                // [!] no cross the broad [0,src->width-1] [xs,xe]
                        for(int row  = j-half_order+1,                                     \
                                iter = (int)(src->width*(j-half_order+1) + i+half_order-1);\
                            
                            row<=j+half_order-1;                                           \
                            
                            row++,                                                         \
                            iter+=src->width){
                            if( row<=ye && row>=ys ){          // [!] no cross the broad [0,src->height-1] [ys,ye]
                                sum_R += pSrcData[ iter ].R;
                                sum_G += pSrcData[ iter ].G;
                                sum_B += pSrcData[ iter ].B;
                                div++;
                            }
                        }
                    }
                }
                pDstData[ target ].R = sum_R*br_100/(div*100);
                pDstData[ target ].G = sum_G*br_100/(div*100);
                pDstData[ target ].B = sum_B*br_100/(div*100);
            }
        }else{ // Scan Direction:  [new] <--<-- [old]
            target+=area->width-1;
            for(int i=xs; i <= xe; i++, target-- ){
                int k = (int)(xe + xs - i); // reverse i   i in (xs->xe); k in (xe -> xs)

                if( k != xe ){
// No need to do when it reachs the right-edge because it has been done when moving to the next row.
// Remove rightmost column because it is old.
                    if(k+half_order <= xe ){                                // [!] no cross the broad [0,src->width-1] [xs,xe]
                        for(int row  = j-half_order+1,\
                                iter = (int)(src->width*(j-half_order+1)+k+half_order);
                            
                            row <= j+half_order-1;\
                            
                            row++,\
                            iter+=src->width){
                            if( row<=ye && row>=ys ){                       // [!] no cross the broad [0,src->height-1] [ys,ye]
                                sum_R -= pSrcData[ iter ].R;
                                sum_G -= pSrcData[ iter ].G;
                                sum_B -= pSrcData[ iter ].B;
                                div--;
                            }
                        }
                    }
                    
// Add leftmost column because it is new.
                    if(k-half_order+1 >= xs ){                              // [!] no cross the broad [0,src->width-1] [xs,xe]
                        for(int row  = j-half_order+1,\
                                iter = (int)(src->width*(j-half_order+1)+k-half_order+1);
                            
                            row <= j+half_order-1;\
                            
                            row++,\
                            iter+=src->width){
                            if( row<=ye && row>=ys ){                       // [!] no cross the broad [0,src->height-1] [ys,ye]
                                sum_R += pSrcData[ iter ].R;
                                sum_G += pSrcData[ iter ].G;
                                sum_B += pSrcData[ iter ].B;
                                div++;
                            }
                        }
                    }
                }

                pDstData[ target ].R = sum_R*br_100/(div*100);
                pDstData[ target ].G = sum_G*br_100/(div*100);
                pDstData[ target ].B = sum_B*br_100/(div*100);
            }
            target += area->width+1;
            
        }
        // End of scanning of this row.
        
        // Remove topmost row because it is old.
        if( j-half_order+1 >= ys ){         // [!] no cross the broad [0,src->height-1] [ys,ye]
            
            if((j&0x01) == 0){ // Scan Direction:  [old] -->--> [new]. Now it is reaching the rightmost.
                for(int col  = (int)(xe+1-half_order),\
                        iter = (int)(src->width*(j-half_order+1) + xe+1-half_order);\
                    
                    col <= xe;\
                    
                    col++ ,\
                    iter++ ){
                    sum_R -= pSrcData[ iter ].R;
                    sum_G -= pSrcData[ iter ].G;
                    sum_B -= pSrcData[ iter ].B;
                    div--;
                }
            }else{        // Scan Direction:  [new] <--<-- [old]. Now it is reaching the leftmost.
                for(int col  = xs,\
                        iter = (int)(src->width*(j-half_order+1) + xs);\
                    
                    col < xs+half_order;\
                    
                    col++,\
                    iter++){
                    sum_R -= pSrcData[ iter ].R;
                    sum_G -= pSrcData[ iter ].G;
                    sum_B -= pSrcData[ iter ].B;
                    div--;
                }
            }

        }
        // Add downmost row because it is new.
        if(j+half_order <= ye ){         // [!] no cross the broad [0,src->height-1] [ys,ye]
            
            if((j&0x01) == 0){ // Scan Direction:  [old] -->--> [new]. Now it is reaching the rightmost.
                for(int col  = (int)(xe+1-half_order),\
                        iter = (int)(src->width*(j+half_order) + col);
                    
                    col <= xe;\
                    
                    col++,
                    iter++){
                    sum_R += pSrcData[ iter ].R;
                    sum_G += pSrcData[ iter ].G;
                    sum_B += pSrcData[ iter ].B;
                    div++;
                }
            }else{        // Scan Direction:  [new] <--<-- [old]. Now it is reaching the leftmost.
                for(int col  = xs,\
                        iter = (int)(src->width*(j+half_order) + col);\
                    
                    col < xs+half_order;\
                    
                    col++,
                    iter++){
                    sum_R += pSrcData[ iter ].R;
                    sum_G += pSrcData[ iter ].G;
                    sum_B += pSrcData[ iter ].B;
                    div++;
                }
            }
        }
        
    }

}
    if(src->pBuffer == dst->pBuffer){
        RH_ASSERT(0);
        memcpy(dst->pBuffer,pDstData,src->height*src->width*sizeof(__UNION_PixelRGB888_t));
        RH_FREE(pDstData);
    }
    return dst;
}

__ImageRGB888_t* __ImgRGB888_blur_fast     (const __ImageRGB888_t* src,__ImageRGB888_t* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    __exitReturn( !src || !dst || !src->pBuffer || !dst->pBuffer, NULL );
    
    const int xs = area->xs;
    const int ys = area->ys;
    const int xe = (int)(area->xs + area->width  -1);
//    const int ye = (int)(area->ys + area->height -1);
    
    const __UNION_PixelRGB888_t* pSrcData = src->pBuffer;
    __UNION_PixelRGB888_t*       pDstData = dst->pBuffer;

    __UNION_PixelRGB888_t*       pTmpData = dst->pBuffer;//RH_MALLOC( area->width*area->height*sizeof(__UNION_PixelRGB888_t) );
    
    

    long accumulate_R=0, accumulate_G=0, accumulate_B=0;
    // Horizontal Processing
    for( int y=0; y<area->height; y++ ){
        __UNION_PixelRGB888_t pix_s = pSrcData[ (y+ys)*src->width + xs ];
        __UNION_PixelRGB888_t pix_e = pSrcData[ (y+ys)*src->width + xe ];
        
        accumulate_B = (radSize+1)*pix_s.B;
        accumulate_G = (radSize+1)*pix_s.G;
        accumulate_R = (radSize+1)*pix_s.R;


        int lx = 0;
        int rx = radSize;
        // printf( "rx=%d lx=%d\n",rx,lx );
        for( int x=0; x<radSize; x++){
            accumulate_B += pSrcData[ (y+ys)*src->width + xs+x ].B;
            accumulate_G += pSrcData[ (y+ys)*src->width + xs+x ].G;
            accumulate_R += pSrcData[ (y+ys)*src->width + xs+x ].R;
        }
        
        // Now: rx=radSize; lx=0;
        // printf( "rx=%d lx=%d\n",rx,lx );
        for( int x=0; x<=radSize; x++, rx++ ){
            accumulate_B += pSrcData[ (y+ys)*src->width + xs+rx ].B - pix_s.B;
            accumulate_G += pSrcData[ (y+ys)*src->width + xs+rx ].G - pix_s.G;
            accumulate_R += pSrcData[ (y+ys)*src->width + xs+rx ].R - pix_s.R;

            pTmpData[ y*area->width + x ].B = accumulate_B / ((radSize<<1)+1);
            pTmpData[ y*area->width + x ].G = accumulate_G / ((radSize<<1)+1);
            pTmpData[ y*area->width + x ].R = accumulate_R / ((radSize<<1)+1);
        }
        
        // Now: rx=2*radSize+1; lx=0;
        // printf( "rx=%d lx=%d\n",rx,lx );
        for( int x=radSize+1; x<area->width-radSize; x++,rx++,lx++ ){
            accumulate_B += pSrcData[ (y+ys)*src->width + xs+rx ].B - pSrcData[ (y+ys)*src->width + xs+lx ].B;
            accumulate_G += pSrcData[ (y+ys)*src->width + xs+rx ].G - pSrcData[ (y+ys)*src->width + xs+lx ].G;
            accumulate_R += pSrcData[ (y+ys)*src->width + xs+rx ].R - pSrcData[ (y+ys)*src->width + xs+lx ].R;
        
            pTmpData[ y*area->width + x ].B = accumulate_B / ((radSize<<1)+1);
            pTmpData[ y*area->width + x ].G = accumulate_G / ((radSize<<1)+1);
            pTmpData[ y*area->width + x ].R = accumulate_R / ((radSize<<1)+1);
        }

        // Now: rx=area->width; lx=area->width-2*radSize-1;
        // printf( "rx=%d lx=%d\n",rx,lx );
        for( int x=(int)(area->width-radSize); x<area->width; x++,lx++ ){
            accumulate_B += pix_e.B - pSrcData[ (y+ys)*src->width + xs+lx ].B;
            accumulate_G += pix_e.R - pSrcData[ (y+ys)*src->width + xs+lx ].G;
            accumulate_R += pix_e.R - pSrcData[ (y+ys)*src->width + xs+lx ].R;
        
            pTmpData[ y*area->width + x ].B = accumulate_B / ((radSize<<1)+1);
            pTmpData[ y*area->width + x ].G = accumulate_G / ((radSize<<1)+1);
            pTmpData[ y*area->width + x ].R = accumulate_R / ((radSize<<1)+1);
        }
        // printf( "rx=%d lx=%d\n\n",rx,lx);

    }
    
    // Trunk Processing
    for( int x=0; x<area->width; x++ ){
        __UNION_PixelRGB888_t pix_s = pSrcData[                                x ];
        __UNION_PixelRGB888_t pix_e = pSrcData[ (area->height-1)*area->width + x ];

        accumulate_B = (radSize+1)*pix_s.B;
        accumulate_G = (radSize+1)*pix_s.G;
        accumulate_R = (radSize+1)*pix_s.R;

        int ty = 0;
        int by = radSize;

        for( int y=0; y<radSize; y++ ){
            accumulate_B += pTmpData[ y*area->width + x ].B;
            accumulate_G += pTmpData[ y*area->width + x ].G;
            accumulate_R += pTmpData[ y*area->width + x ].R;
        }

        for( int y=0; y<=radSize; y++,by++ ){
            accumulate_B += pTmpData[ by*area->width + x ].B - pix_s.B;
            accumulate_G += pTmpData[ by*area->width + x ].G - pix_s.G;
            accumulate_R += pTmpData[ by*area->width + x ].R - pix_s.R;

            pDstData[ y*area->width + x ].B = accumulate_B / ((radSize<<1)+1);
            pDstData[ y*area->width + x ].G = accumulate_G / ((radSize<<1)+1);
            pDstData[ y*area->width + x ].R = accumulate_R / ((radSize<<1)+1);
        }

        for( int y=radSize+1; y<area->height-radSize; y++, ty++, by++ ){
            accumulate_B += pTmpData[ by*area->width + x ].B - pTmpData[ ty*area->width + x ].B;
            accumulate_G += pTmpData[ by*area->width + x ].G - pTmpData[ ty*area->width + x ].G;
            accumulate_R += pTmpData[ by*area->width + x ].R - pTmpData[ ty*area->width + x ].R;

            pDstData[ y*area->width + x ].B = accumulate_B / ((radSize<<1)+1);
            pDstData[ y*area->width + x ].G = accumulate_G / ((radSize<<1)+1);
            pDstData[ y*area->width + x ].R = accumulate_R / ((radSize<<1)+1);
        }

        for( int y=(int)(area->height-radSize); y<area->height; y++, ty++ ){
            accumulate_B += pix_e.B - pTmpData[ ty*area->width + x ].B;
            accumulate_G += pix_e.G - pTmpData[ ty*area->width + x ].G;
            accumulate_R += pix_e.R - pTmpData[ ty*area->width + x ].R;

            pDstData[ y*area->width + x ].B = accumulate_B / ((radSize<<1)+1);
            pDstData[ y*area->width + x ].G = accumulate_G / ((radSize<<1)+1);
            pDstData[ y*area->width + x ].R = accumulate_R / ((radSize<<1)+1);
        }

    }
    
    RH_FREE( pTmpData );
    return dst;
}



__ImageRGB888_t* __ImgRGB888_insert_NstNeighbor  (const __ImageRGB888_t* src,__ImageRGB888_t* dst,size_t height,size_t width){
    if(src == NULL || src->pBuffer == NULL || dst == NULL) // Bad address
        return NULL;
    if(height < src->height || width < src->width) // Image of "dst" should be larger than image of "src" in both dimension.
        return NULL;
    if(dst->pBuffer == NULL){
        dst->pBuffer = (__UNION_PixelRGB888_t*)RH_MALLOC(width*height*sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL){
            return NULL;  // There is no space to malloc.
        }
    }
    dst->height = height;
    dst->width  = width;
    memset(dst->pBuffer, 0, width*height*sizeof(__UNION_PixelRGB888_t));
    
    size_t eps_x = 0; // Record errors no bigger than width.
    size_t eps_y = 0; // Record errors no bigger than height.
    size_t fx    = 0; // Pixel cordination of original image in x direction.
    size_t fy    = 0; // Pixel cordination of original image in y direction.
    for(size_t gy=0;gy<height;gy++){
        eps_y += src->height;
        if(eps_y >= height){
            fx = 0;
            for(size_t gx=0;gx<width;gx++){
                eps_x += src->width;
                if( eps_x >= width ){
                    // This is the position to copy pixels from original image.
                    (dst->pBuffer + (width*gy) + gx)->data = (src->pBuffer + (src->width*fy) + fx)->data;
//                    printf("%ld,%ld ",fx,fy);
                    eps_x-=width;
                    fx++;
                }else{
                    // This is the position needs to interpolate.
                    //...//
                }
            }
//            printf("\n");
            eps_y -= height;
            fy++;
        }else
            continue;
    }
    
    return dst;
}


__ImageRGB888_t* __ImgRGB888_conv2D        (const __ImageRGB888_t* src,__ImageRGB888_t* dst,const __Kernel_t* k,uint16_t br_100){
    if( src == NULL || src->pBuffer == NULL || k == NULL ){
        return dst;
    }
    
    if(dst == NULL){
        dst = (__ImageRGB888_t*)RH_MALLOC(sizeof(__ImageRGB888_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB888_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst->pBuffer == NULL){
        dst->pBuffer = (__UNION_PixelRGB888_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst == NULL){
        dst = (__ImageRGB888_t*)RH_MALLOC(sizeof(__ImageRGB888_t));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (__UNION_PixelRGB888_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB888_t));
    }

    for(int j=0;j<src->height;j++){
        for(int i=0;i<src->width;i++){
            int div = k->sum;
            
            // Here comes the convolution part.
            unsigned long tmp_R = 0,tmp_G = 0,tmp_B = 0; // Preparation for RGB data.
            for(int n=0;n<k->order;n++){
                for(int m=0;m<k->order;m++){
                    size_t offset_y  = j-(k->order>>1)+n;
                    size_t offset_x  = i-(k->order>>1)+m;
                    int selectKernel = *( k->pBuffer + n       * k->order + m       );
                    if( offset_x>=src->width || offset_y>=src->height ){
                        div -= selectKernel;
                    }else{
                        uint8_t select_R  = (src->pBuffer + offset_y*src->width + offset_x)->R;
                        uint8_t select_G  = (src->pBuffer + offset_y*src->width + offset_x)->G;
                        uint8_t select_B  = (src->pBuffer + offset_y*src->width + offset_x)->B;
                        
                        tmp_R += ( (select_R) * (selectKernel) );
                        tmp_G += ( (select_G) * (selectKernel) );
                        tmp_B += ( (select_B) * (selectKernel) );
                    }
                }
            }
            size_t offset = (j*src->width)+i;
            if(offset < dst->width*dst->height){
                unsigned long temp = 0;
                
                temp = (tmp_R*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->pBuffer+offset)->R = (uint8_t)((1<<8)-1);
                else                                (dst->pBuffer+offset)->R = (uint8_t)(temp);
                
                temp = (tmp_G*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->pBuffer+offset)->G = (uint8_t)((1<<8)-1);
                else                                (dst->pBuffer+offset)->G = (uint8_t)(temp);
                
                temp = (tmp_B*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->pBuffer+offset)->B = (uint8_t)((1<<8)-1);
                else                                (dst->pBuffer+offset)->B = (uint8_t)(temp);
                
            }
        }
    }
    
    return dst;
}
   
void             __ImgRGB888_data_OTUS     (const __ImageRGB888_t* src,uint32_t* threshold){
    *threshold = (uint32_t)(-1);
    __exit( src          == NULL );
    __exit( src->pBuffer == NULL );
    
    int    threshold_temp;
    long   NumOf_bckPixel = 0;    //Number of pixels defined as background
    long   SumOf_bckPixel = 0;    //Sum of pixels defined as background
    float  AvgOf_bckPixel = 0.0;  //Average value of pixels defined as background

    long   NumOf_objPixel = 0;    //Number of pixels defined as background
    long   SumOf_objPixel = 0;    //Sum of pixels defined as background
    float  AvgOf_objPixel = 0.0;  //Average value of pixels defined as background
    
    float  g = 0.0, g_max = 0.0;  //Variance between obj and bck
    
    const long NumOf_allPixel = (src->width) * (src->height);
    
    // Make Statistic...

    long gray_cnt[255] = {0};
    for (int row = 0; row < src->height; row++){
        for (int col = 0; col < src->width; col++){
            uint8_t temp = ( __array1D(src->pBuffer, src->width, row, col)->R*19595 + \
                             __array1D(src->pBuffer, src->width, row, col)->G*38469 + \
                             __array1D(src->pBuffer, src->width, row, col)->B*7472 )>>16;
            gray_cnt[temp]++;
        }
    }
    
    for (threshold_temp = 0; threshold_temp < 255; threshold_temp++){
        NumOf_bckPixel = 0; SumOf_bckPixel = 0;
        NumOf_objPixel = 0; SumOf_objPixel = 0;
        
        // Calculation for Background.
        for (uint8_t i = 0; i < threshold_temp; i++){
            NumOf_bckPixel += gray_cnt[i];
            SumOf_bckPixel += (i * gray_cnt[i]);
        }
        if (NumOf_bckPixel == 0)
            continue;
        AvgOf_bckPixel = SumOf_bckPixel / NumOf_bckPixel;
        
        // Calculation for object.
        NumOf_objPixel = NumOf_allPixel - NumOf_bckPixel;
        for (uint8_t i = threshold_temp; i < 255; i++){
            SumOf_objPixel += (i * gray_cnt[i]);
        }
        if (NumOf_objPixel == 0)
            continue;
        AvgOf_objPixel = SumOf_objPixel / NumOf_objPixel;
        
        //In case of overloading,calculate step by step.
        float w_bck   = (float)NumOf_bckPixel / NumOf_allPixel;
        float w_obj   = (float)NumOf_objPixel / NumOf_allPixel;
        float mu_diff = AvgOf_objPixel - AvgOf_bckPixel;

        g = w_bck * mu_diff * w_obj * mu_diff;
        if (g > g_max){
            g_max = g;
            *threshold = threshold_temp;
        }
    }
}

__ImageRGB565_t* __ImgRGB565_conv2D        (const __ImageRGB565_t* src,__ImageRGB565_t* dst,const __Kernel_t* k,uint16_t br_100){
        if( src == NULL || src->pBuffer == NULL || k == NULL){
            return dst;
        }
            
        if(dst == NULL){
            dst = (__ImageRGB565_t*)RH_MALLOC(sizeof(__ImageRGB565_t));
            if(dst == NULL) // Not enough space :-(
                return dst;
            dst->pBuffer = (__UNION_PixelRGB565_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB565_t));
            if(dst->pBuffer == NULL) // Not enough space :-(
                return dst;
        }
        
        if(dst->pBuffer == NULL){
            dst->pBuffer = (__UNION_PixelRGB565_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB565_t));
            if(dst->pBuffer == NULL) // Not enough space :-(
                return dst;
        }
        
        if(dst == NULL){
            dst = (__ImageRGB565_t*)RH_MALLOC(sizeof(__ImageRGB565_t));
            if(dst == NULL) // Not enough space :-(
                return dst;
            dst->pBuffer = (__UNION_PixelRGB565_t*)RH_MALLOC(src->width * src->height * sizeof(__UNION_PixelRGB565_t));
        }

        for(int j=0;j<src->height;j++){
            for(int i=0;i<src->width;i++){
                int div = k->sum;
                
                // Here comes the convolution part.
                unsigned long tmp_R = 0,tmp_G = 0,tmp_B = 0; // Preparation for RGB data.
                for(int n=0;n<k->order;n++){
                    for(int m=0;m<k->order;m++){
                        size_t offset_y  = j-(k->order>>1)+n;
                        size_t offset_x  = i-(k->order>>1)+m;
                        int selectKernel = *( k->pBuffer + n       * k->order + m       );
                        if( offset_x>=src->width || offset_y>=src->height ){
                            div -= selectKernel;
                        }else{
                            uint8_t select_R  = (src->pBuffer + offset_y*src->width + offset_x)->R;
                            uint8_t select_G  = (src->pBuffer + offset_y*src->width + offset_x)->G;
                            uint8_t select_B  = (src->pBuffer + offset_y*src->width + offset_x)->B;
                            
                            tmp_R += ( (select_R) * (selectKernel) );
                            tmp_G += ( (select_G) * (selectKernel) );
                            tmp_B += ( (select_B) * (selectKernel) );
                        }
                    }
                }
                size_t offset = (j*src->width)+i;
                if(offset < dst->width*dst->height){
                    (dst->pBuffer+offset)->R = (div==0)?((1<<5)-1):(tmp_R*br_100/(div*100));
                    (dst->pBuffer+offset)->G = (div==0)?((1<<6)-1):(tmp_G*br_100/(div*100));
                    (dst->pBuffer+offset)->B = (div==0)?((1<<5)-1):(tmp_B*br_100/(div*100));
                }
            }
        }
        
        return dst;
    }

#ifdef __cplusplus
}
#endif

