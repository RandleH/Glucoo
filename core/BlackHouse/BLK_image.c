
#include <stdio.h>
#include "BLK_image.h"

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

    
    

    
BLK_SRCT(Img888)* BLK_FUNC( Img888, out_png )     (const char* __restrict__ path, const BLK_SRCT(Img888)* img){
    
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

    uint8_t* pBuffer = RH_MALLOC(img->height*img->width*3);
    uint8_t* pBufferIter = pBuffer;
   
    for(int y=0;y<img->height;y++){
        for(int x=0;x<img->width;x++){
            *pBufferIter = img->pBuffer[ y*img->width + x ].R;
            pBufferIter++;
            
            *pBufferIter = img->pBuffer[ y*img->width + x ].G;
            pBufferIter++;
            
            *pBufferIter = img->pBuffer[ y*img->width + x ].B;
            pBufferIter++;
            
        }
    }
    
    FILE *fp = fopen(path, "wb");
    
    #define SVPNG_PUT(u) fputc(u, fp)
    #define SVPNG_U8A(ua, l) for (i = 0; i < l; i++) SVPNG_PUT((ua)[i]);
    #define SVPNG_U32(u) do { SVPNG_PUT((u) >> 24); SVPNG_PUT(((u) >> 16) & 255); SVPNG_PUT(((u) >> 8) & 255); SVPNG_PUT((u) & 255); } while(0)
    #define SVPNG_U8C(u) do { SVPNG_PUT(u); c ^= (u); c = (c >> 4) ^ t[c & 15]; c = (c >> 4) ^ t[c & 15]; } while(0)
    #define SVPNG_U8AC(ua, l) for (i = 0; i < l; i++) SVPNG_U8C((ua)[i])
    #define SVPNG_U16LC(u) do { SVPNG_U8C((u) & 255); SVPNG_U8C(((u) >> 8) & 255); } while(0)
    #define SVPNG_U32C(u) do { SVPNG_U8C((u) >> 24); SVPNG_U8C(((u) >> 16) & 255); SVPNG_U8C(((u) >> 8) & 255); SVPNG_U8C((u) & 255); } while(0)
    #define SVPNG_U8ADLER(u) do { SVPNG_U8C(u); a = (a + (u)) % 65521; b = (b + a) % 65521; } while(0)
    #define SVPNG_BEGIN(s, l) do { SVPNG_U32(l); c = ~0U; SVPNG_U8AC(s, 4); } while(0)
    #define SVPNG_END() SVPNG_U32(~c)
    
    static const unsigned t[] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    /* CRC32 Table */    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
    unsigned a = 1, b = 0, c, p = (uint32_t)img->width * (3) + 1, x, y, i;   /* ADLER-a, ADLER-b, CRC, pitch */
    SVPNG_U8A("\x89PNG\r\n\32\n", 8);           /* Magic */
    SVPNG_BEGIN("IHDR", 13);                    /* IHDR chunk { */
    SVPNG_U32C((uint32_t)img->width); SVPNG_U32C((uint32_t)img->height);               /*   Width & Height (8 bytes) */
    SVPNG_U8C(8); SVPNG_U8C(2);                 /*   Depth=8, Color=True color with/without alpha (2 bytes) */
    SVPNG_U8AC("\0\0\0", 3);                    /*   Compression=Deflate, Filter=No, Interlace=No (3 bytes) */
    SVPNG_END();                                /* } */
    SVPNG_BEGIN("IDAT", 2 + (uint32_t)img->height * (5 + p) + 4);   /* IDAT chunk { */
    SVPNG_U8AC("\x78\1", 2);                    /*   Deflate block begin (2 bytes) */
    
    uint8_t* pIter = (uint8_t*)pBuffer;
    for (y = 0; y < img->height; y++) {                   /*   Each horizontal line makes a block for simplicity */
        SVPNG_U8C(y == img->height - 1);                  /*   1 for the last block, 0 for others (1 byte) */
        SVPNG_U16LC(p); SVPNG_U16LC(~p);        /*   Size of block in little endian and its 1's complement (4 bytes) */
        SVPNG_U8ADLER(0);                       /*   No filter prefix (1 byte) */
        for (x = 0; x < p - 1; x++, pIter++)
            SVPNG_U8ADLER(*pIter);                /*   Image pixel data */
    }
    SVPNG_U32C((b << 16) | a);                  /*   Deflate block end with adler (4 bytes) */
    SVPNG_END();                                /* } */
    SVPNG_BEGIN("IEND", 0); SVPNG_END();        /* IEND chunk {} */
    
    
    RH_FREE(pBuffer);
    
    return (BLK_SRCT(Img888)*)img;
}

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, load_bmp )    (const char* __restrict__ path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    BLK_SRCT(ImgBin)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(ImgBin)));
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
        BLK_FUNC( Memory, exchange )( &pIMG->pBuffer[ p*infoHead.biWidth ], &pIMG->pBuffer[ (page-p-1)*infoHead.biWidth ], infoHead.biWidth*sizeof(uint8_t) );
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
    
    return pIMG;
}
    
BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, create   )    (size_t width,size_t height){
    BLK_SRCT(ImgBin)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(ImgBin)));
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

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, copy     )    (const BLK_SRCT(ImgBin)* src,BLK_SRCT(ImgBin)* dst){
    __exitReturn( src==NULL         ||dst==NULL          , dst );
    __exitReturn( src->pBuffer==NULL||dst->pBuffer==NULL , dst );
    
    memcpy(dst->pBuffer, src->pBuffer, (__RND8(src->height)>>3)*(src->width)*sizeof(BLK_TYPE(PixelBin)));
    dst->height = src->height;
    dst->width  = src->width;
    return dst;
}
    
BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, out_bmp  )    (const char* __restrict__ path,BLK_SRCT(ImgBin)* p){
    __exitReturn(p == NULL && p->pBuffer == NULL , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn(bmp == NULL, NULL);
    
    size_t BPL  = __RND4( (p->width>>3)+((p->width&0x07)!=0) ); /* Bytes Per Line */
    
    BITMAPFILEHEADER fileHead = {
        .bfType      = 0x4d42  ,
        .bfSize      = 458     , //(uint32_t)((__RND8(p->height)>>3)*(p->width)*sizeof(BLK_TYPE(PixelBin)) + 54) ,
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
        BLK_FUNC( Memory, exchange )(&pTmp[row*BPL], &pTmp[(p->height-row-1)*BPL], BPL);
    }
    
    fwrite( pTmp, 1, infoHead.biSizeImage*sizeof(uint8_t), bmp );
    
    fclose(bmp);
    RH_FREE(pTmp);
    return p;
}

BLK_SRCT(Img565)* BLK_FUNC( Img565, load_bmp )    (const char* __restrict__ path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    BLK_SRCT(Img565)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img565)));
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

    pIMG->pBuffer = (BLK_UION(Pixel565)*)RH_MALLOC(infoHead.biWidth * infoHead.biHeight * sizeof(BLK_UION(Pixel565)));
    
    for (int row = 0; row < infoHead.biHeight; row++) {
        for (int col = 0; col < infoHead.biWidth; col++) {
            fread(&(pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data), sizeof(BLK_SRCT(Pixel565)), 1, bmp);
            // printf("%d ",pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data);
        }
        int eps = (4-(infoHead.biWidth*sizeof(BLK_SRCT(Pixel565)))%4)%4;
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

BLK_SRCT(Img565)* BLK_FUNC( Img565, create   )    (size_t width,size_t height){
    BLK_SRCT(Img565)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img565)));
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

BLK_SRCT(Img565)* BLK_FUNC( Img565, copy     )    (const BLK_SRCT(Img565)* src,BLK_SRCT(Img565)* dst){
    __exitReturn( src==NULL         ||dst==NULL          , dst );
    __exitReturn( src->pBuffer==NULL||dst->pBuffer==NULL , dst );

    memcpy(dst->pBuffer, src->pBuffer, (src->height)*(src->width)*sizeof(BLK_UION(Pixel565)));
    dst->height = src->height;
    dst->width  = src->width;
    return dst;
}

BLK_SRCT(Img565)* BLK_FUNC( Img565, out_bmp  )    (const char* __restrict__ path,BLK_SRCT(Img565)* p){
    __exitReturn(p == NULL && p->pBuffer == NULL , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn(bmp == NULL, NULL);

    int eps = (4-(p->width*sizeof(BLK_SRCT(Pixel565)))%4)%4;
    BITMAPFILEHEADER fileHead = {
        .bfOffBits      = 40 + 14   ,
        .bfReserved1    = 0         ,
        .bfReserved2    = 0         ,
        .bfSize         = (uint32_t)(p->height * p->width * sizeof(BLK_SRCT(Pixel565)) + 54),
        .bfType         = 0x4D42    ,
    };
    BITMAPINFOHEADER infoHead = {
        .biSize          = 40        ,
        .biWidth         = (int)(p->width)  ,
        .biHeight        = (int)(p->height) ,
        .biPlanes        = 1         ,
        .biBitCount      = 5+6+5     ,
        .biCompression   = 0         ,
        .biSizeImage     = (uint32_t)(p->height*p->width*sizeof(BLK_SRCT(Pixel565)) + eps*(p->height)) ,
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
            fwrite( &p->pBuffer[(infoHead.biHeight - row - 1) * infoHead.biWidth + col] ,sizeof(BLK_SRCT(Pixel565)) ,1 ,bmp );
        }
        int eps = (4-(infoHead.biWidth*sizeof(BLK_SRCT(Pixel565)))%4)%4;
        uint8_t dummyByte = 0x00;
        while(eps--){
            fwrite(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    
    fclose(bmp);
    return p;
}
    
BLK_SRCT(Img565)* BLK_FUNC( Img565, conv2D   )    (const BLK_SRCT(Img565)* src,BLK_SRCT(Img565)* dst,const __Kernel_t* k,uint16_t br_100){
        if( src == NULL || src->pBuffer == NULL || k == NULL){
            return dst;
        }
            
        if(dst == NULL){
            dst = (BLK_SRCT(Img565)*)RH_MALLOC(sizeof(BLK_SRCT(Img565)));
            if(dst == NULL) // Not enough space :-(
                return dst;
            dst->pBuffer = (BLK_UION(Pixel565)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel565)));
            if(dst->pBuffer == NULL) // Not enough space :-(
                return dst;
        }
        
        if(dst->pBuffer == NULL){
            dst->pBuffer = (BLK_UION(Pixel565)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel565)));
            if(dst->pBuffer == NULL) // Not enough space :-(
                return dst;
        }
        
        if(dst == NULL){
            dst = (BLK_SRCT(Img565)*)RH_MALLOC(sizeof(BLK_SRCT(Img565)));
            if(dst == NULL) // Not enough space :-(
                return dst;
            dst->pBuffer = (BLK_UION(Pixel565)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel565)));
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
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, load_bmp )    (const char* __restrict__ path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    BLK_SRCT(Img888)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img888)));
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

    pIMG->pBuffer = (BLK_UION(Pixel888)*)RH_MALLOC(infoHead.biWidth * infoHead.biHeight * sizeof(BLK_UION(Pixel888)));
    
    for (int row = 0; row < infoHead.biHeight; row++) {
        for (int col = 0; col < infoHead.biWidth; col++) {
            fread(&(pIMG->pBuffer[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data), sizeof(BLK_SRCT(Pixel888)), 1, bmp);
        }
        int eps = (4-(infoHead.biWidth*sizeof(BLK_SRCT(Pixel888)))%4)%4;
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


BLK_SRCT(Img888)* BLK_FUNC( Img888, copy     )    (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst){
    __exitReturn( src==NULL         ||dst==NULL          , dst );
    __exitReturn( src->pBuffer==NULL||dst->pBuffer==NULL , dst );

    memcpy(dst->pBuffer, src->pBuffer, (src->height)*(src->width)*sizeof(BLK_UION(Pixel888)));
    dst->height = src->height;
    dst->width  = src->width;
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, create   )    (size_t width,size_t height){
    BLK_SRCT(Img888)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img888)));
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

BLK_SRCT(Img888)* BLK_FUNC( Img888, out_bmp     )  (const char* __restrict__ path,BLK_SRCT(Img888)* p){
    __exitReturn(p == NULL && p->pBuffer == NULL , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn(bmp == NULL, NULL);

    int eps = (4-(p->width*sizeof(BLK_SRCT(Pixel888)))%4)%4;
    BITMAPFILEHEADER fileHead = {
        .bfOffBits      = 40 + 14   ,
        .bfReserved1    = 0         ,
        .bfReserved2    = 0         ,
        .bfSize         = (uint32_t)(p->height * p->width * sizeof(BLK_SRCT(Pixel888)) + 54),
        .bfType         = 0x4D42    ,
    };
    BITMAPINFOHEADER infoHead = {
        .biSize          = 40        ,
        .biWidth         = (int)(p->width)  ,
        .biHeight        = (int)(p->height) ,
        .biPlanes        = 1         ,
        .biBitCount      = 8+8+8     ,
        .biCompression   = 0         ,
        .biSizeImage     = (uint32_t)(p->height*p->width*sizeof(BLK_SRCT(Pixel888)) + eps*(p->height)) ,
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
            fwrite( &p->pBuffer[(infoHead.biHeight - row - 1) * infoHead.biWidth + col] ,sizeof(BLK_SRCT(Pixel888)) ,1 ,bmp );
        }
        int eps = (4-(infoHead.biWidth*sizeof(BLK_SRCT(Pixel888)))%4)%4;
        uint8_t dummyByte = 0x00;
        while(eps--){
            fwrite(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    
    fclose(bmp);
    return p;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, free_buffer )  (BLK_SRCT(Img888)*      ptr){
    RH_FREE(ptr->pBuffer);
    ptr->height  = 0;
    ptr->width   = 0;
    ptr->pBuffer = NULL;
    return ptr;
}

void              BLK_FUNC( Img888, free        )  (BLK_SRCT(Img888)*      ptr){
    RH_FREE(BLK_FUNC( Img888, free_buffer )(ptr));
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_gray )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
    
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

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_cold )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_warm )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
    
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_OTUS )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
    uint32_t threshold = 0;
    __exitReturn( src==NULL         , NULL);
    __exitReturn( src->pBuffer==NULL, NULL);
    __exitReturn( dst==NULL         , NULL);
    __exitReturn( dst->pBuffer==NULL, NULL);
    
    BLK_FUNC( Img888, data_OTUS )(src, &threshold);
    
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
     
BLK_SRCT(Img888)* BLK_FUNC( Img888, trans_mirror)  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint8_t HV){
    if( src == NULL || src->pBuffer == NULL ){
        return NULL;
    }
    if(dst == NULL){
        dst = (BLK_SRCT(Img888)*)RH_MALLOC(sizeof(BLK_SRCT(Img888)));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (BLK_UION(Pixel888)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel888)));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    if(dst->pBuffer == NULL){
        dst->pBuffer = (BLK_UION(Pixel888)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel888)));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    switch(HV){
        case 0:
            for(size_t y=0;y<src->height;y++){
                for(size_t x=0;x<((src->width+1)>>1);x++){
                    BLK_UION(Pixel888) tmp_fore = src->pBuffer[y*src->width + x];
                    BLK_UION(Pixel888) tmp_back = src->pBuffer[y*src->width + src->width - 1 - x];
                    dst->pBuffer[y*src->width+x]                    = tmp_back;
                    dst->pBuffer[y*src->width + src->width - 1 - x] = tmp_fore;
                }
            }

            break;
        case 1:
            for(size_t y=0;y<src->height;y++){
                memmove(&dst->pBuffer[(src->height-1-y)*dst->width], &src->pBuffer[y*src->width], src->width*sizeof(BLK_UION(Pixel888)));
            }
            break;
        default:
            //...//
            break;
    }
    
    return NULL;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_gussian)  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
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

    BLK_SRCT(Img888)* pImg = BLK_FUNC( Img888, conv2D )(src, dst,&gus_kernel,br_100);
    
    radSize_old      = radSize;

    return pImg;

}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_average)  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    __exitReturn(src == NULL || dst == NULL , NULL);
    
    BLK_UION(Pixel888)* pSrcData = src->pBuffer;
    BLK_UION(Pixel888)* pDstData = dst->pBuffer;
    if(pSrcData == dst->pBuffer){
        RH_ASSERT(0);
        pDstData = RH_MALLOC(src->height*src->width*sizeof(BLK_UION(Pixel888)));
    }
    
    size_t order = RH_LIMIT(((radSize*60)>>16), 3, 101);
    if((order & 0x01) == 0) // order should be an odd number.
        order--;
    
    if( area==NULL ){
        area = alloca( sizeof(__Area_t) );
        area->height = src->height;
        area->width  = src->width;
        area->xs = area->ys = 0;
    }
    
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
        memcpy(dst->pBuffer,pDstData,src->height*src->width*sizeof(BLK_UION(Pixel888)));
        RH_FREE(pDstData);
    }
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_fast   )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    __exitReturn( !src || !dst || !src->pBuffer || !dst->pBuffer, NULL );
    
    const int xs = area->xs;
    const int ys = area->ys;
    const int xe = (int)(area->xs + area->width  -1);
//    const int ye = (int)(area->ys + area->height -1);
    
    const BLK_UION(Pixel888)* pSrcData = src->pBuffer;
    BLK_UION(Pixel888)*       pDstData = dst->pBuffer;

    BLK_UION(Pixel888)*       pTmpData = dst->pBuffer;//RH_MALLOC( area->width*area->height*sizeof(BLK_UION(Pixel888)) );
    
    

    long accumulate_R=0, accumulate_G=0, accumulate_B=0;
    // Horizontal Processing
    for( int y=0; y<area->height; y++ ){
        BLK_UION(Pixel888) pix_s = pSrcData[ (y+ys)*src->width + xs ];
        BLK_UION(Pixel888) pix_e = pSrcData[ (y+ys)*src->width + xe ];
        
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
        BLK_UION(Pixel888) pix_s = pSrcData[                                x ];
        BLK_UION(Pixel888) pix_e = pSrcData[ (area->height-1)*area->width + x ];

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



BLK_SRCT(Img888)* BLK_FUNC( Img888, insert_NstNeighbor )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,size_t height,size_t width){
    if(src == NULL || src->pBuffer == NULL || dst == NULL) // Bad address
        return NULL;
    if(height < src->height || width < src->width) // Image of "dst" should be larger than image of "src" in both dimension.
        return NULL;
    if(dst->pBuffer == NULL){
        dst->pBuffer = (BLK_UION(Pixel888)*)RH_MALLOC(width*height*sizeof(BLK_UION(Pixel888)));
        if(dst->pBuffer == NULL){
            return NULL;  // There is no space to malloc.
        }
    }
    dst->height = height;
    dst->width  = width;
    memset(dst->pBuffer, 0, width*height*sizeof(BLK_UION(Pixel888)));
    
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


BLK_SRCT(Img888)* BLK_FUNC( Img888, conv2D      )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,const __Kernel_t* k,uint16_t br_100){
    if( src == NULL || src->pBuffer == NULL || k == NULL ){
        return dst;
    }
    
    if(dst == NULL){
        dst = (BLK_SRCT(Img888)*)RH_MALLOC(sizeof(BLK_SRCT(Img888)));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (BLK_UION(Pixel888)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel888)));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst->pBuffer == NULL){
        dst->pBuffer = (BLK_UION(Pixel888)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel888)));
        if(dst->pBuffer == NULL) // Not enough space :-(
            return dst;
    }
    
    if(dst == NULL){
        dst = (BLK_SRCT(Img888)*)RH_MALLOC(sizeof(BLK_SRCT(Img888)));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->pBuffer = (BLK_UION(Pixel888)*)RH_MALLOC(src->width * src->height * sizeof(BLK_UION(Pixel888)));
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
   
void              BLK_FUNC( Img888, data_OTUS   )  (const BLK_SRCT(Img888)* src,uint32_t* threshold){
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
    
BLK_SRCT(ImgBin)* BLK_FUNC( ImgGry, into_ImgBin )
(const BLK_SRCT(ImgGry)* src,BLK_SRCT(ImgBin)* dst,int xs, int ys,BLK_TYPE(PixelBin) obj_color, uint8_t br_100){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    RH_ASSERT(xs < dst->width);
    RH_ASSERT(ys < dst->height);
    
    const BLK_UION(PixelGry)*   pIterSrc = src->pBuffer;
    BLK_UION(PixelBin)*         pIterDst = &dst->pBuffer[((ys)>>3)*(dst->width)+(xs)];
    
    for( int y=0; y<src->height && y<dst->height; y++ ){
        pIterDst = dst->pBuffer + ((ys+y)>>3)*(dst->width) + xs;
        for( int x=0; x<src->width; x++, pIterSrc++,pIterDst++ ){
            if( (pIterSrc->data<128) ^ (obj_color!=0) ){
                pIterDst->data = __BIT_SET( pIterDst->data, (ys+y)%8 );
            }else{
                pIterDst->data = __BIT_CLR( pIterDst->data, (ys+y)%8 );
            }
        }
    }
    
    return dst;
}
    
BLK_SRCT(Img565)* BLK_FUNC( ImgGry, into_Img565 )
(const BLK_SRCT(ImgGry)* src,BLK_SRCT(Img565)* dst,int xs, int ys,BLK_TYPE(Pixel565) obj_color, uint8_t br_100){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    RH_ASSERT(xs < dst->width);
    RH_ASSERT(ys < dst->height);
    
    const BLK_UION(PixelGry)*      pIterSrc = src->pBuffer;
    BLK_UION(Pixel565)*            pIterDst = &dst->pBuffer[(ys)*(dst->width)+(xs)];
    
    BLK_UION(Pixel565) color = {.data = obj_color};
    for( int y=0; y<src->height&&y<dst->height; y++ ){
        for( int x=0; x<src->width; x++,pIterSrc++, pIterDst++ ){
            pIterDst->R = pIterDst->R + (( (color.R - pIterDst->R) * (pIterSrc->data) )>>8);
            pIterDst->G = pIterDst->G + (( (color.G - pIterDst->G) * (pIterSrc->data) )>>8);
            pIterDst->B = pIterDst->B + (( (color.B - pIterDst->B) * (pIterSrc->data) )>>8);
        }
        pIterDst -= src->width;
        pIterDst += dst->width;
    }
    
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( ImgGry, into_Img888 )
(const BLK_SRCT(ImgGry)* src,BLK_SRCT(Img888)* dst,int xs, int ys,BLK_TYPE(Pixel888) obj_color, uint8_t br_100){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    RH_ASSERT(xs < dst->width);
    RH_ASSERT(ys < dst->height);
    
    br_100 = RH_LIMIT((signed)br_100, 0, 100);
    
    const BLK_UION(PixelGry)*      pIterSrc = src->pBuffer;
    BLK_UION(Pixel888)*            pIterDst = &dst->pBuffer[(ys)*(dst->width)+(xs)];
    
    BLK_UION(Pixel888) color = {.data = obj_color};
    if( br_100 == 100 ){
        for( int y=0; y<src->height&&y<dst->height; y++ ){
            for( int x=0; x<src->width; x++,pIterSrc++, pIterDst++ ){
                pIterDst->R += (( (color.R - pIterDst->R) * (pIterSrc->data) )>>8);
                pIterDst->G += (( (color.G - pIterDst->G) * (pIterSrc->data) )>>8);
                pIterDst->B += (( (color.B - pIterDst->B) * (pIterSrc->data) )>>8);
            }
            pIterDst -= src->width;
            pIterDst += dst->width;
        }
    }else if( br_100 == 50 ){
        for( int y=0; y<src->height&&y<dst->height; y++ ){
            for( int x=0; x<src->width; x++,pIterSrc++, pIterDst++ ){
                pIterDst->R += (( (color.R - pIterDst->R) * (pIterSrc->data) )>>9);
                pIterDst->G += (( (color.G - pIterDst->G) * (pIterSrc->data) )>>9);
                pIterDst->B += (( (color.B - pIterDst->B) * (pIterSrc->data) )>>9);
            }
            pIterDst -= src->width;
            pIterDst += dst->width;
        }
    }else{
        int div = 25500/br_100;
        for( int y=0; y<src->height&&y<dst->height; y++ ){
            for( int x=0; x<src->width; x++,pIterSrc++, pIterDst++ ){
                pIterDst->R += (( (color.R - pIterDst->R) * (pIterSrc->data) )/div);
                pIterDst->G += (( (color.G - pIterDst->G) * (pIterSrc->data) )/div);
                pIterDst->B += (( (color.B - pIterDst->B) * (pIterSrc->data) )/div);
            }
            pIterDst -= src->width;
            pIterDst += dst->width;
        }
    }
    
    return dst;
}
    
BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, draw_img_aurora )
( BLK_SRCT(ImgBin)* dst, const BLK_TYPE(PixelBin)* colors, size_t size ){
    RH_ASSERT( dst          );
    RH_ASSERT( dst->pBuffer );
    RH_ASSERT( dst->height  );
    RH_ASSERT( dst->width   );
    
    for( int x=0; x<=dst->width-1; x++ ){
        
//        int ys = (unsigned)BLK_FUNC(Math,rand)()%(dst->height/3), ye = (int)(dst->height<<1)/3 + (unsigned)BLK_FUNC(Math,rand)()%(dst->height/3);
        
        
        
    }
    
    while(1);
    return dst;
}
    
BLK_SRCT(Img565)* BLK_FUNC( Img565, draw_img_aurora )
( BLK_SRCT(Img565)* dst, const BLK_TYPE(Pixel565)* colors, size_t size ){
    RH_ASSERT( dst          );
    RH_ASSERT( dst->pBuffer );
    RH_ASSERT( dst->height  );
    RH_ASSERT( dst->width   );

    
    const int sect = (int)((int)dst->width)/(int)(size+1);
    int* xc = alloca((size+1)*sizeof(int));
    for( int i=1; i<=(size+1); i++){
        xc[i-1] = (int)((int)dst->width*i)/(int)(size+1);
    }
    
    for( int x=0; x<=dst->width-1; x++ ){
        int stage = 0;
        for( ; stage<(size+1); stage++){
            if( x < xc[ stage ] )
                break;
        }
        
        BLK_UION(Pixel565) color_prev, color_next, color;
        
        if( stage == 0 ){
            color_prev.data = M_COLOR_BLACK;
            color_next.data = colors[ stage ];
        }else if( stage == size ){
            color_prev.data = colors[stage-1];
            color_next.data = M_COLOR_BLACK;
        }else{
            color_prev.data = colors[stage-1];
            color_next.data = colors[stage  ];
        }
        if(stage==0){
            color.R = color_prev.R + (color_next.R-color_prev.R)*(x)/sect;
            color.G = color_prev.G + (color_next.G-color_prev.G)*(x)/sect;
            color.B = color_prev.B + (color_next.B-color_prev.B)*(x)/sect;
        }else{
            color.R = color_prev.R + (color_next.R-color_prev.R)*(x-xc[stage-1])/sect;
            color.G = color_prev.G + (color_next.G-color_prev.G)*(x-xc[stage-1])/sect;
            color.B = color_prev.B + (color_next.B-color_prev.B)*(x-xc[stage-1])/sect;
        }
        
        
        int ys = (unsigned)BLK_FUNC(Math,rand)()%(dst->height/3), ye = (int)(dst->height<<1)/3 + (unsigned)BLK_FUNC(Math,rand)()%(dst->height/3);
        
        float _2_sigma_2 = (ye-ys)*(ye-ys)/18.0;
        BLK_UION(Pixel565)* pIterUP = dst->pBuffer + ys*(dst->width) +x;
        BLK_UION(Pixel565)* pIterDN = dst->pBuffer + ye*(dst->width) +x;
        
# if 1
        // 以下代码被性能优化
        for( int y=ys, tmp = ((ye - ys)*(ye - ys)>>2); pIterUP<=pIterDN; y++, pIterUP+=dst->width, pIterDN-=dst->width, tmp += ((y+1)<<1)-(ye+ys) ){
            
            pIterUP->R = pIterDN->R = roundl( color.R* exp2( -tmp/_2_sigma_2));
            pIterUP->G = pIterDN->G = roundl( color.G* exp2( -tmp/_2_sigma_2));
            pIterUP->B = pIterDN->B = roundl( color.B* exp2( -tmp/_2_sigma_2));
            
            
        }
#else
        // 原代码_2 为:
        for( int y=ys; pIterUP<=pIterDN; y++, pIterUP+=dst->width, pIterDN-=dst->width ){
            int tmp = (y-((ye+ys)>>1))*(y-((ye+ys)>>1));
            pIterUP->R = pIterDN->R = roundl( color.R* exp2( -tmp/_2_sigma_2));
            pIterUP->G = pIterDN->G = roundl( color.G* exp2( -tmp/_2_sigma_2));
            pIterUP->B = pIterDN->B = roundl( color.B* exp2( -tmp/_2_sigma_2));
        }
        // 原代码_1 为:
        for( int y=ys; y<=ye; y++, pIterUP+=dst->width, pIterDN-=dst->width ){
            int tmp = (y-((ye-ys)>>1)-ys)*(y-((ye-ys)>>1)-ys);
            pIterUP->R = roundl( color.R* exp( -tmp/(2*sigma_2)));
            pIterUP->G = roundl( color.G* exp( -tmp/(2*sigma_2)));
            pIterUP->B = roundl( color.B* exp( -tmp/(2*sigma_2)));
            printf("%d\n",tmp);
        }
        
#endif
        
    }
    
    return dst;
}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_aurora )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    RH_ASSERT( dst          );
    RH_ASSERT( dst->pBuffer );
    RH_ASSERT( dst->height  );
    RH_ASSERT( dst->width   );

    
    const int sect = (int)((int)dst->width)/(int)(size+1);
    int* xc = alloca((size+1)*sizeof(int));
    for( int i=1; i<=(size+1); i++){
        xc[i-1] = (int)((int)dst->width*i)/(int)(size+1);
    }
    
    for( int x=0; x<=dst->width-1; x++ ){
        int stage = 0;
        for( ; stage<(size+1); stage++){
            if( x < xc[ stage ] )
                break;
        }
        
        BLK_UION(Pixel888) color_prev, color_next, color;
        
        if( stage == 0 ){
            color_prev.data = M_COLOR_BLACK;
            color_next.data = colors[ stage ];
        }else if( stage == size ){
            color_prev.data = colors[stage-1];
            color_next.data = M_COLOR_BLACK;
        }else{
            color_prev.data = colors[stage-1];
            color_next.data = colors[stage  ];
        }
        if(stage==0){
            color.R = color_prev.R + (color_next.R-color_prev.R)*(x)/sect;
            color.G = color_prev.G + (color_next.G-color_prev.G)*(x)/sect;
            color.B = color_prev.B + (color_next.B-color_prev.B)*(x)/sect;
        }else{
            color.R = color_prev.R + (color_next.R-color_prev.R)*(x-xc[stage-1])/sect;
            color.G = color_prev.G + (color_next.G-color_prev.G)*(x-xc[stage-1])/sect;
            color.B = color_prev.B + (color_next.B-color_prev.B)*(x-xc[stage-1])/sect;
        }
        
        
        int ys = (unsigned)BLK_FUNC(Math,rand)()%(dst->height/3), ye = (int)(dst->height<<1)/3 + (unsigned)BLK_FUNC(Math,rand)()%(dst->height/3);
        
        float _2_sigma_2 = (ye-ys)*(ye-ys)/18.0;
        BLK_UION(Pixel888)* pIterUP = dst->pBuffer + ys*(dst->width) +x;
        BLK_UION(Pixel888)* pIterDN = dst->pBuffer + ye*(dst->width) +x;
        
# if 1
        // 以下代码被性能优化
        for( int y=ys, tmp = ((ye - ys)*(ye - ys)>>2); pIterUP<=pIterDN; y++, pIterUP+=dst->width, pIterDN-=dst->width, tmp += ((y+1)<<1)-(ye+ys) ){
            
            pIterUP->R = pIterDN->R = roundl( color.R* exp2( -tmp/_2_sigma_2));
            pIterUP->G = pIterDN->G = roundl( color.G* exp2( -tmp/_2_sigma_2));
            pIterUP->B = pIterDN->B = roundl( color.B* exp2( -tmp/_2_sigma_2));
            
            
        }
#else
        // 原代码_2 为:
        for( int y=ys; pIterUP<=pIterDN; y++, pIterUP+=dst->width, pIterDN-=dst->width ){
            int tmp = (y-((ye+ys)>>1))*(y-((ye+ys)>>1));
            pIterUP->R = pIterDN->R = roundl( color.R* exp2( -tmp/_2_sigma_2));
            pIterUP->G = pIterDN->G = roundl( color.G* exp2( -tmp/_2_sigma_2));
            pIterUP->B = pIterDN->B = roundl( color.B* exp2( -tmp/_2_sigma_2));
        }
        // 原代码_1 为:
        for( int y=ys; y<=ye; y++, pIterUP+=dst->width, pIterDN-=dst->width ){
            int tmp = (y-((ye-ys)>>1)-ys)*(y-((ye-ys)>>1)-ys);
            pIterUP->R = roundl( color.R* exp( -tmp/(2*sigma_2)));
            pIterUP->G = roundl( color.G* exp( -tmp/(2*sigma_2)));
            pIterUP->B = roundl( color.B* exp( -tmp/(2*sigma_2)));
            printf("%d\n",tmp);
        }
        
#endif
        
    }
    
    return dst;
}

    
    
    
    
    

    
    
    
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_ )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    
    const int x0 = (int)dst->width>>1;
    const int y0 = (int)dst->height>>1;
    const int r0 = RH_MIN((int)dst->width, (int)dst->height)/3;
    
    dst->pBuffer[y0*dst->width+x0].data = M_COLOR_WHITE;
    
    struct{
        int x;
        int y;
    }cord[19];
    
    // 获取 以(x0,y0)为中心, 0度 10度...180度的坐标
    for( int a=0,cnt=0; a<=90; a+=10,cnt++ ){
        cord[cnt     ].x = (int)lround(x0+r0*cos(a*M_PI/180));
        cord[19-cnt-1].x = 2*x0-cord[cnt].x;
        cord[cnt     ].y =  cord[19-cnt-1].y = (int)lround(y0+r0*sin(a*M_PI/180));
    }
    
    for( int i=0; i<19; i++ ){
        dst->pBuffer[( cord[i].y )*dst->width+cord[i].x].data = M_COLOR_WHITE;
    }
    
    // 填充颜色
#if 1
    for( int cnt=0; cnt<2; cnt++ ){
        uint32_t c = rand()%0x00ffffff;
        // xs 的轨迹为圆心至动点直线, xe 的轨迹为圆弧
        int xs = RH_MIN(x0, RH_MIN(cord[cnt].x, cord[cnt+1].x));
        int xe = RH_MAX(x0, RH_MAX(cord[cnt].x, cord[cnt+1].x));
        int ys = RH_MIN(y0, RH_MIN(cord[cnt].y, cord[cnt+1].y));
        int ye = RH_MAX(y0, RH_MAX(cord[cnt].y, cord[cnt+1].y));
        
         // 填充三个点组成的三角形: (x0,y0) (cord[cnt].x, cord[cnt].y) (cord[cnt+1].x, cord[cnt+1].y)
        
        for(int y=ys; y<=ye; y++){
            int x = xs;
            
            while( 0==__Point_toTriangle( x0, y0, cord[cnt].x, cord[cnt].y, cord[cnt+1].x, cord[cnt+1].y, x, y) && x<=xe ){
                x++;
            }
            if(y==960){
                assert(1);
            }
            while( 0<=__Point_toTriangle( x0, y0, cord[cnt].x, cord[cnt].y, cord[cnt+1].x, cord[cnt+1].y, x, y) && x<=xe ){
                dst->pBuffer[ (y)*dst->width+x].data = c;
                x++;
            }
            
        }
        
        
        
       
        
        
        
        
        printf("===========\n");
    }
#endif
    
    
    
    
    return dst;
}
    

#ifdef __cplusplus
}
#endif

