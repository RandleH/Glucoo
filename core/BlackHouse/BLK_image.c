
#include <stdio.h>
#include "BLK_image.h"
#include "BLK_graphic.h"

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

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, load_bmp )    (const char* RH_RESTRICT path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    BLK_SRCT(ImgBin)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(ImgBin)));
    pIMG->h   = 0;
    pIMG->w   = 0;
    pIMG->ptr = NULL;

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
    pIMG->ptr     = RH_CALLOC( page*col, sizeof(uint8_t) );
    pIMG->h       = infoHead.biHeight;
    pIMG->w       = infoHead.biWidth;
    
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
                    pIMG->ptr[ (row/8)*infoHead.biWidth + col*8 + cnt ].data |= ( ( (pTmp[col]>>(7-cnt))&0x01 ) << (7-row%8) );
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
        BLK_FUNC( Memory, exchange )( &pIMG->ptr[ p*infoHead.biWidth ], &pIMG->ptr[ (page-p-1)*infoHead.biWidth ], infoHead.biWidth*sizeof(uint8_t) );
    }
    
    size_t dummyBit =  (page<<3) - infoHead.biHeight ;
    for( int p=0; p<page; p++ ){
        for( int c=0; c<col; c++ ){
            if( p+1 < page ){
                uint16_t tmp = (uint16_t)(((pIMG->ptr[ (p+1)*col+c ].data)<<8) | (pIMG->ptr[  p   *col+c ].data) );
                tmp >>= dummyBit;
                pIMG->ptr[  p*col+c ].data = (uint8_t)(tmp);
            }else{
                pIMG->ptr[  p*col+c ].data >>= dummyBit;
            }
        }
    }
    
    return pIMG;
}
    
BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, create   )    (size_t width,size_t height){
    BLK_SRCT(ImgBin)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(ImgBin)));
    __exitReturn( !pIMG, NULL );
    pIMG->h   = height;
    pIMG->w   = width;
    pIMG->ptr = RH_CALLOC((__RND8(height)>>3)*(pIMG->w), sizeof(uint8_t));
    
    if(pIMG->ptr == NULL){
        RH_FREE(pIMG);
        return NULL;
    }
    return pIMG;
}

BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, copy     )    (const BLK_SRCT(ImgBin)* src,BLK_SRCT(ImgBin)* dst){
    __exitReturn( src==NULL         ||dst==NULL          , dst );
    __exitReturn( src->ptr==NULL||dst->ptr==NULL , dst );
    
    memcpy(dst->ptr, src->ptr, (__RND8(src->h)>>3)*(src->w)*sizeof(BLK_TYPE(PixelBin)));
    dst->h  = src->h;
    dst->w  = src->w;
    return dst;
}
    
BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, out_bmp  )    (const char* RH_RESTRICT path, const BLK_SRCT(ImgBin)* img){
    __exitReturn(img == NULL && img->ptr == NULL , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn(bmp == NULL, NULL);
    
    size_t BPL  = __RND4( (img->w>>3)+((img->w&0x07)!=0) ); /* Bytes Per Line */
    
    BITMAPFILEHEADER fileHead = {
        .bfType      = 0x4d42  ,
        .bfSize      = 458     , //(uint32_t)((__RND8(img->height)>>3)*(img->width)*sizeof(BLK_TYPE(PixelBin)) + 54) ,
        .bfReserved1 = 0       ,
        .bfReserved2 = 0       ,
        .bfOffBits   = 62      ,
    };
    
    BITMAPINFOHEADER infoHead = {
        .biBitCount  = 1              ,
        .biSize      = 40             ,
        .biWidth     = (int)img->w  ,
        .biHeight    = (int)img->h ,
        .biPlanes    = 1              ,
        .biSizeImage = (DWORD)( BPL*img->h )
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
    
    for( int row=0; row<img->h; row++ ){
        for( int col=0; col<BPL; col++ ){
            for(size_t cnt=0; cnt<8; cnt++){
                if( (col<<3)+cnt < img->w ){
                    pTmp[ row*BPL + col ] |= (((img->ptr[ (row/8)*img->w + (col<<3)+cnt ].data)>>(row%8))&0x01)<<(7-cnt);
                }else{
                    break;
                }
            }
        }
    }
    
    for( int row=0; row<(img->h>>1); row++ ){
        BLK_FUNC( Memory, exchange )(&pTmp[row*BPL], &pTmp[(img->h-row-1)*BPL], BPL);
    }
    
    fwrite( pTmp, 1, infoHead.biSizeImage*sizeof(uint8_t), bmp );
    
    fclose(bmp);
    RH_FREE(pTmp);
    return (BLK_SRCT(ImgBin)*)img;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, out_png  )    (const char* RH_RESTRICT path, const BLK_SRCT(Img888)* img){
    
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

    uint8_t* pBuffer = RH_MALLOC(img->h*img->w*3);
    uint8_t* pBufferIter = pBuffer;
   
    for(var y=0;y<img->h;y++){
        for(var x=0;x<img->w;x++){
            *pBufferIter = img->ptr[ y*img->w + x ].R;
            pBufferIter++;
            
            *pBufferIter = img->ptr[ y*img->w + x ].G;
            pBufferIter++;
            
            *pBufferIter = img->ptr[ y*img->w + x ].B;
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
    unsigned a = 1, b = 0, c, p = (uint32_t)img->w * (3) + 1, x, y, i;   /* ADLER-a, ADLER-b, CRC, pitch */
    SVPNG_U8A("\x89PNG\r\n\32\n", 8);           /* Magic */
    SVPNG_BEGIN("IHDR", 13);                    /* IHDR chunk { */
    SVPNG_U32C((uint32_t)img->w); SVPNG_U32C((uint32_t)img->h);               /*   Width & Height (8 bytes) */
    SVPNG_U8C(8); SVPNG_U8C(2);                 /*   Depth=8, Color=True color with/without alpha (2 bytes) */
    SVPNG_U8AC("\0\0\0", 3);                    /*   Compression=Deflate, Filter=No, Interlace=No (3 bytes) */
    SVPNG_END();                                /* } */
    SVPNG_BEGIN("IDAT", 2 + (uint32_t)img->h * (5 + p) + 4);   /* IDAT chunk { */
    SVPNG_U8AC("\x78\1", 2);                    /*   Deflate block begin (2 bytes) */
    
    uint8_t* pIter = (uint8_t*)pBuffer;
    for (y = 0; y < img->h; y++) {                   /*   Each horizontal line makes a block for simplicity */
        SVPNG_U8C(y == img->h - 1);                  /*   1 for the last block, 0 for others (1 byte) */
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

BLK_SRCT(Img565)* BLK_FUNC( Img565, load_bmp )    (const char* RH_RESTRICT path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    BLK_SRCT(Img565)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img565)));
    pIMG->h   = 0;
    pIMG->w   = 0;
    pIMG->ptr = NULL;

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

    pIMG->ptr = (BLK_UION(Pixel565)*)RH_MALLOC(infoHead.biWidth * infoHead.biHeight * sizeof(BLK_UION(Pixel565)));
    
    for (var row = 0; row < infoHead.biHeight; row++) {
        for (var col = 0; col < infoHead.biWidth; col++) {
            fread(&(pIMG->ptr[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data), sizeof(BLK_SRCT(Pixel565)), 1, bmp);
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

    pIMG->w  = (var)infoHead.biWidth;
    pIMG->h  = (var)infoHead.biHeight;

    return pIMG;
}

BLK_SRCT(Img565)* BLK_FUNC( Img565, create   )    (var width,var height){
    BLK_SRCT(Img565)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img565)));
    __exitReturn( !pIMG, NULL );
    pIMG->h   = height;
    pIMG->w   = width;
    pIMG->ptr = RH_CALLOC((pIMG->h)*(pIMG->w), sizeof(pIMG->ptr[0]));
    if(pIMG->ptr == NULL){
        RH_FREE(pIMG);
        return NULL;
    }
    return pIMG;
}

BLK_SRCT(Img565)* BLK_FUNC( Img565, copy     )    (const BLK_SRCT(Img565)* src,BLK_SRCT(Img565)* dst){
    __exitReturn( !src || !dst , NULL );
    __exitReturn( !src->ptr || !dst->ptr , NULL );

    memcpy(dst->ptr, src->ptr, (src->h)*(src->w)*sizeof(BLK_UION(Pixel565)));
    dst->h = src->h;
    dst->w = src->w;
    return dst;
}

BLK_SRCT(Img565)* BLK_FUNC( Img565, out_bmp  )    (const char* RH_RESTRICT path, const BLK_SRCT(Img565)* img){
    __exitReturn( !img && !img->ptr , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn( !bmp, NULL);

    int eps = (4-(img->w*sizeof(BLK_SRCT(Pixel565)))%4)%4;
    BITMAPFILEHEADER fileHead = {
        .bfOffBits      = 40 + 14   ,
        .bfReserved1    = 0         ,
        .bfReserved2    = 0         ,
        .bfSize         = (uint32_t)(img->h * img->w * sizeof(BLK_SRCT(Pixel565)) + 54),
        .bfType         = 0x4D42    ,
    };
    BITMAPINFOHEADER infoHead = {
        .biSize          = 40        ,
        .biWidth         = (int)(img->w)  ,
        .biHeight        = (int)(img->h) ,
        .biPlanes        = 1         ,
        .biBitCount      = 5+6+5     ,
        .biCompression   = 0         ,
        .biSizeImage     = (uint32_t)(img->h*img->w*sizeof(BLK_SRCT(Pixel565)) + eps*(img->h)) ,
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
    for (var row = 0; row < img->h; row++) {
        for (var col = 0; col < img->w; col++) {
            fwrite( &img->ptr[(infoHead.biHeight - row - 1) * infoHead.biWidth + col] ,sizeof(BLK_SRCT(Pixel565)) ,1 ,bmp );
        }
        int eps = (4-(infoHead.biWidth*sizeof(BLK_SRCT(Pixel565)))%4)%4;
        uint8_t dummyByte = 0x00;
        while(eps--){
            fwrite(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    
    fclose(bmp);
    return (BLK_SRCT(Img565)*)img;
}
  
BLK_SRCT(Img565)* BLK_FUNC( Img565, conv2D   )    (const BLK_SRCT(Img565)* src,BLK_SRCT(Img565)* dst,const BLK_SRCT(Kernel)* k,uint16_t br_100){
    if( !src || !src->ptr || !k ){
        return dst;
    }
        
    if( !dst ){
        dst = (BLK_SRCT(Img565)*)RH_MALLOC(sizeof(BLK_SRCT(Img565)));
        if( !dst ) // Not enough space :-(
            return dst;
        dst->ptr = (BLK_UION(Pixel565)*)RH_MALLOC(src->w * src->h * sizeof(BLK_UION(Pixel565)));
        if( !dst->ptr ) // Not enough space :-(
            return dst;
    }
    
    if( !dst->ptr ){
        dst->ptr = (BLK_UION(Pixel565)*)RH_MALLOC(src->w * src->h * sizeof(BLK_UION(Pixel565)));
        if( !dst->ptr ) // Not enough space :-(
            return NULL;
    }
    
    if( !dst ){
        dst = (BLK_SRCT(Img565)*)RH_MALLOC(sizeof(BLK_SRCT(Img565)));
        if( !dst ) // Not enough space :-(
            return NULL;
        dst->ptr = (BLK_UION(Pixel565)*)RH_MALLOC(src->w * src->h * sizeof(BLK_UION(Pixel565)));
    }
#warning "Able to optimize."
    

    uint16_t *pIterKer = k->pBuffer;
    
    for(var j=0;j<src->h;j++){
        for(var i=0;i<src->w;i++){
            int div = k->sum;
            
            // Here comes the convolution part.
            
            unsigned long tmp_R = 0,tmp_G = 0,tmp_B = 0; // Preparation for RGB data.
            for(var n=0;n<k->order;n++){
                for(var m=0;m<k->order;m++,  pIterKer++){
                    var offset_y  = j-(k->order>>1)+n;
                    var offset_x  = i-(k->order>>1)+m;
                    // int selectKernel = *( k->pBuffer + n       * k->order + m       );
                    
                    uint16_t selectKernel = *pIterKer;
                    
                    if( offset_x>=src->w || offset_y>=src->h ){
                        div -= selectKernel;
                    }else{
                        uint8_t select_R  = (src->ptr + offset_y*src->w + offset_x)->R;
                        uint8_t select_G  = (src->ptr + offset_y*src->w + offset_x)->G;
                        uint8_t select_B  = (src->ptr + offset_y*src->w + offset_x)->B;
                        
                        tmp_R += ( (select_R) * (selectKernel) );
                        tmp_G += ( (select_G) * (selectKernel) );
                        tmp_B += ( (select_B) * (selectKernel) );
                    }
                }
            }
            size_t offset = (j*src->w)+i;
            if( offset < dst->w*dst->h ){
                (dst->ptr+offset)->R = (div==0)?((1<<5)-1):(tmp_R*br_100/(div*100));
                (dst->ptr+offset)->G = (div==0)?((1<<6)-1):(tmp_G*br_100/(div*100));
                (dst->ptr+offset)->B = (div==0)?((1<<5)-1):(tmp_B*br_100/(div*100));
            }
        }
    }
    
    return dst;
}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, load_bmp )    (const char* RH_RESTRICT path){
    FILE* bmp;
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;

    BLK_SRCT(Img888)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img888)));
    pIMG->h   = 0;
    pIMG->w   = 0;
    pIMG->ptr = NULL;
    
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

    pIMG->ptr = (BLK_UION(Pixel888)*)RH_MALLOC(infoHead.biWidth * infoHead.biHeight * sizeof(BLK_UION(Pixel888)));
    
    for (int row = 0; row < infoHead.biHeight; row++) {
        for (int col = 0; col < infoHead.biWidth; col++) {
            fread(&(pIMG->ptr[(infoHead.biHeight - row - 1)*infoHead.biWidth + col].data), sizeof(BLK_SRCT(Pixel888)), 1, bmp);
        }
        int eps = (4-(infoHead.biWidth*sizeof(BLK_SRCT(Pixel888)))%4)%4;
        uint8_t dummyByte;
        while(eps--){
            fread(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    fclose(bmp);

    pIMG->w = (var)infoHead.biWidth;
    pIMG->h = (var)infoHead.biHeight;

    return pIMG;
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
BLK_SRCT(Img888)* BLK_FUNC( Img888, load_jpg )    (const char* RH_RESTRICT path){
    int x,y,n;
    uint8_t *p, *ptr = stbi_load(path, &x, &y, &n, 3);
    p = ptr;
    BLK_SRCT(Img888) *IMG = BLK_FUNC(Img888,create) (x, y);
    for (var y=0; y<IMG->h; y++){
        for (var x=0; x<IMG->w; x++) {
            IMG->ptr[ y*IMG->w + x ].R = *ptr++;
            IMG->ptr[ y*IMG->w + x ].G = *ptr++;
            IMG->ptr[ y*IMG->w + x ].B = *ptr++;
        }
    }
    stbi_image_free(p);
    return IMG;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, load_png )    (const char* RH_RESTRICT path){
    return  BLK_FUNC( Img888, load_jpg )(path);
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, copy     )    (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst){
    __exitReturn( !src || !dst , NULL );
    __exitReturn( !src->ptr || !dst->ptr , NULL );

    memcpy(dst->ptr, src->ptr, (src->h)*(src->w)*sizeof(BLK_UION(Pixel888)));
    dst->h = src->h;
    dst->w = src->w;
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, create   )    (var  width,var height){
    BLK_SRCT(Img888)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img888)));
    if( !pIMG )
        return NULL;
    pIMG->h   = height;
    pIMG->w   = width;
    pIMG->ptr = RH_MALLOC((pIMG->h)*(pIMG->w)*sizeof(pIMG->ptr[0]));
    if( !pIMG->ptr ){
        RH_FREE(pIMG);
        return NULL;
    }
    memset(pIMG->ptr, 0, (pIMG->h)*(pIMG->w)*sizeof(pIMG->ptr[0]));
    return pIMG;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, out_bmp  )    (const char* RH_RESTRICT path, const BLK_SRCT(Img888)* img){
    __exitReturn( !img && !img->ptr , NULL);
    
    FILE* bmp = fopen(path,"wb");
    __exitReturn( !bmp , NULL);

    int eps = (4-(img->w*sizeof(BLK_SRCT(Pixel888)))%4)%4;
    BITMAPFILEHEADER fileHead = {
        .bfOffBits      = 40 + 14   ,
        .bfReserved1    = 0         ,
        .bfReserved2    = 0         ,
        .bfSize         = (uint32_t)(img->h * img->w * sizeof(BLK_SRCT(Pixel888)) + 54),
        .bfType         = 0x4D42    ,
    };
    BITMAPINFOHEADER infoHead = {
        .biSize          = 40        ,
        .biWidth         = (int)(img->w)  ,
        .biHeight        = (int)(img->h) ,
        .biPlanes        = 1         ,
        .biBitCount      = 8+8+8     ,
        .biCompression   = 0         ,
        .biSizeImage     = (uint32_t)(img->h*img->w*sizeof(BLK_SRCT(Pixel888)) + eps*(img->h)) ,
        .biClrUsed       = 0         ,
        .biClrImportant  = 0         ,
        .biXPelsPerMeter = 0         ,
        .biYPelsPerMeter = 0         ,
    };
    // printf("%d\n" ,infoHead.biSizeImage    );
   

    // RGB Sequence should be reversed.
    fseek(bmp,0L,SEEK_SET);
    fwrite(&fileHead ,1 ,sizeof(BITMAPFILEHEADER) , bmp);
    fwrite(&infoHead ,1 ,sizeof(BITMAPINFOHEADER) , bmp);
    fseek(bmp,54L,SEEK_SET);
    for (var row = 0; row < img->h; row++) {
        for (var col = 0; col < img->w; col++) {
            fwrite( &img->ptr[(infoHead.biHeight - row - 1) * infoHead.biWidth + col] ,sizeof(BLK_SRCT(Pixel888)) ,1 ,bmp );
        }
        int eps = (4-(infoHead.biWidth*sizeof(BLK_SRCT(Pixel888)))%4)%4;
        uint8_t dummyByte = 0x00;
        while(eps--){
            fwrite(&dummyByte,sizeof(char) ,1 , bmp);
        }
    }
    
    fclose(bmp);
    return (BLK_SRCT(Img888)*)img;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, free_buffer )  (BLK_SRCT(Img888)*      pIMG){
    RH_FREE(pIMG->ptr);
    pIMG->h   = 0;
    pIMG->w   = 0;
    pIMG->ptr = NULL;
    return pIMG;
}

void              BLK_FUNC( Img888, free        )  (BLK_SRCT(Img888)*      ptr){
    RH_FREE( BLK_FUNC( Img888, free_buffer )(ptr) );
}
    

    
BLK_SRCT(Img565)* BLK_FUNC( Img565, free_buffer  ) (      BLK_SRCT(Img565)* ptr){
    return (BLK_SRCT(Img565)*)BLK_FUNC( Img888, free_buffer )  ( (BLK_SRCT(Img888)*) ptr);
}
    

    
void              BLK_FUNC( Img565, free         ) (      BLK_SRCT(Img565)* ptr){
    RH_FREE( BLK_FUNC( Img565, free_buffer )(ptr) );
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_gray )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
    if(src != NULL && dst != NULL){
        if(src->ptr != NULL && dst->ptr != NULL){
            for (var row = 0; row < src->h; row++) {
                for (var col = 0; col < src->w; col++) {
                    long temp = lroundl(0.299 * src->ptr[row * src->w + col].R + 0.587 * src->ptr[row * src->w + col].G + 0.114 * src->ptr[row * src->w + col].B);
                    dst->ptr[row * src->w + col].data = (uint32_t)(((temp&0xff)<<16)|((temp&0xff)<<8)|((temp&0xff)));
                }
            }
        }
    }
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_cold )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
    __exitReturn( !src      , NULL);
    __exitReturn( !src->ptr , NULL);
    __exitReturn( !dst      , NULL);
    __exitReturn( !dst->ptr , NULL);
    
    BLK_UION(Pixel888)* pIterDst = dst->ptr;
    BLK_UION(Pixel888)* pIterSrc = src->ptr;
    for(var y=0;y<src->h;y++){
        for(var x=0;x<src->w;x++, pIterSrc++, pIterDst++){
            pIterDst->B += (uint8_t)(((0xff-pIterSrc->B)*br_100)>>8);
        }
    }
    
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_warm )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
#warning "Wrong algorithm."
    __exitReturn( !src      , NULL);
    __exitReturn( !src->ptr , NULL);
    __exitReturn( !dst      , NULL);
    __exitReturn( !dst->ptr , NULL);
    
    BLK_UION(Pixel888)* pIterDst = dst->ptr;
    BLK_UION(Pixel888)* pIterSrc = src->ptr;
    for(var y=0;y<src->h;y++){
        for(var x=0;x<src->w;x++, pIterSrc++, pIterDst++){
            pIterDst->R += (uint8_t)(( RH_LIMIT( (180-pIterSrc->R),0,180) *br_100)/180);
            pIterDst->G += (uint8_t)(( RH_LIMIT( (180-pIterSrc->G),0,180) *br_100)/180);
//            pIterDst->B -= (uint8_t)(pIterSrc->B*br_100>>8);
        }
    }
    
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, filter_OTUS )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint32_t br_100){
    uint8_t threshold = 0;
    __exitReturn( !src      , NULL);
    __exitReturn( !src->ptr , NULL);
    __exitReturn( !dst      , NULL);
    __exitReturn( !dst->ptr , NULL);
    
    BLK_FUNC( Img888, data_OTUS )(src, &threshold);
    
    __exitReturn(threshold == (uint8_t)(-1), NULL);
    
    BLK_UION(Pixel888)* pIterDst = dst->ptr;
    BLK_UION(Pixel888)* pIterSrc = src->ptr;
    for(var y=0;y<src->h;y++){
        for(var x=0;x<src->w;x++,pIterSrc++, pIterDst++){
            uint8_t temp = ( pIterSrc->R*19595 + \
                             pIterSrc->G*38469 + \
                             pIterSrc->B*7472 )>>16;
            if( temp > threshold )
                pIterDst->data = 0x00ffffff;
            else
                pIterDst->data = 0x00000000;
        }
    }
    return dst;
}
     
BLK_SRCT(Img888)* BLK_FUNC( Img888, trans_mirror)  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,uint8_t HV){

    if( !src || !src->ptr ){
        return NULL;
    }
    if(dst == NULL){
        dst = (BLK_SRCT(Img888)*)RH_MALLOC(sizeof(BLK_SRCT(Img888)));
        if(dst == NULL) // Not enough space :-(
            return dst;
        dst->ptr = (BLK_UION(Pixel888)*)RH_MALLOC(src->w * src->h * sizeof(BLK_UION(Pixel888)));
        if(dst->ptr == NULL) // Not enough space :-(
            return dst;
    }
    if(dst->ptr == NULL){
        dst->ptr = (BLK_UION(Pixel888)*)RH_MALLOC(src->w * src->h * sizeof(BLK_UION(Pixel888)));
        if(dst->ptr == NULL) // Not enough space :-(
            return dst;
    }
    
    dst->w = src->w;
    dst->h = src->h;
    
    switch(HV){
        case 0:{
            BLK_UION(Pixel888) *pIterDst_f = dst->ptr;
            BLK_UION(Pixel888) *pIterDst_b = dst->ptr+dst->w-1;
            BLK_UION(Pixel888) *pIterSrc_f = src->ptr;
            BLK_UION(Pixel888) *pIterSrc_b = src->ptr+src->w-1;
            for(var y=0;y<src->h;y++,pIterSrc_f += src->w - ((src->w>>1)+(src->w&0x01)) ,\
                                     pIterSrc_b += src->w + ((src->w>>1)+(src->w&0x01)) ,\
                                     pIterDst_f += dst->w - ((dst->w>>1)+(dst->w&0x01)) ,\
                                     pIterDst_b += dst->w + ((dst->w>>1)+(dst->w&0x01))  \
                ){
                
                for(var x=0;x<((src->w+1)>>1);x++, pIterDst_f++, pIterSrc_f++, pIterDst_b--, pIterSrc_b--){
                    BLK_UION(Pixel888) tmp_fore = *pIterSrc_f;
                    BLK_UION(Pixel888) tmp_back = *pIterSrc_b;
                    *pIterDst_f = tmp_back;
                    *pIterSrc_b = tmp_fore;
                
                }
                
            }
            
            break;
        }

            
        case 1:
            for(size_t y=0;y<src->h;y++){
                memmove(&dst->ptr[(src->h-1-y)*dst->w], &src->ptr[y*src->w], src->w*sizeof(BLK_UION(Pixel888)));
            }
            break;
        default:
            //...//
            break;
    }
    
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_gussian)  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    static BLK_SRCT(Kernel) gus_kernel = {
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
        BLK_FUNC( Gussian, kernel )(sigma,order,&gus_kernel);
    }

    BLK_SRCT(Img888)* pImg = BLK_FUNC( Img888, conv2D )(src, dst,&gus_kernel,br_100);
    
    radSize_old      = radSize;

    return pImg;

}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_average)  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    __exitReturn(src == NULL || dst == NULL , NULL);
        
        BLK_UION(Pixel888)* pSrcData = src->ptr;
        BLK_UION(Pixel888)* pDstData = dst->ptr;
        if(pSrcData == dst->ptr){
//            RH_ASSERT(0);
            pDstData = RH_MALLOC(src->h*src->w*sizeof(BLK_UION(Pixel888)));
        }
        
        size_t order = RH_LIMIT(((radSize*60)>>16), 3, 101);
        if((order & 0x01) == 0) // order should be an odd number.
            order--;
        
        if( area==NULL ){
            area = alloca( sizeof(__Area_t) );
            area->h = (var)src->h;
            area->w = (var)src->w;
            area->xs = area->ys = 0;
        }
        
        unsigned long sum_R = 0, sum_G = 0, sum_B = 0;
        unsigned long div = 0;
        
        var xs = area->xs;
        var ys = area->ys;
        var xe = area->xs + area->w-1;
        var ye = area->ys + area->h-1;
        
        // Pre-Calculation
        int half_order  = (int)((order+1)>>1); // Kernel
        div = half_order * half_order;
        
        if( (ys&0x01)==0 ){
            int iter = (int)(src->w*ys + xs);
            for(var n=ys; n < ys+half_order; n++, iter+=src->w){
                for(var m=xs; m < xs+half_order;m++, iter++){
                    sum_R += pSrcData[iter].R;
                    sum_G += pSrcData[iter].G;
                    sum_B += pSrcData[iter].B;
                }
                iter-=half_order;
            }
        }
        else{
            int iter = (int)(src->w*(ye+1-half_order) + xe+1-half_order);
            for(var n=ye+1-half_order; n <= ye; n++, iter+=src->w){
                for(var m=xe+1-half_order; m <= xe;m++, iter++){
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
        for(var j=ys; j <= ye; j++ ){
            
            if((j&0x01) == 0){ // Scan Direction:  [old] -->--> [new]
                for(var i=xs; i <= xe; i++, target++ ){
                    if(i!=xs){
                        // No need to do when it reachs the left-edge because it has been done when moving to the next row.
                        // Remove leftmost column because it is old.
                        if(i-half_order >= xs){                    // [!] no cross the broad [0,src->w-1] [xs,xe]
                            
                            for(int row  = j-half_order+1,                                     \
                                    iter = (int)(src->w*(j-half_order+1) + i-half_order);  \
                                  
                                row<=j+half_order-1;                                           \
                                
                                row++,                                                         \
                                iter+=src->w){
                                if( row<=ye && row>=ys ){          // [!] no cross the broad [0,src->h-1] [ys,ye]
                                    sum_R -= pSrcData[ iter ].R;
                                    sum_G -= pSrcData[ iter ].G;
                                    sum_B -= pSrcData[ iter ].B;
                                    div--;
                                }
                            }
                        }
                        
                        // Add rightmost column because it is new.
                        if( i+half_order-1 <= xe ){                // [!] no cross the broad [0,src->w-1] [xs,xe]
                            for(var row  = j-half_order+1,                                     \
                                    iter = (int)(src->w*(j-half_order+1) + i+half_order-1);\
                                
                                row<=j+half_order-1;                                           \
                                
                                row++,                                                         \
                                iter+=src->w){
                                if( row<=ye && row>=ys ){          // [!] no cross the broad [0,src->h-1] [ys,ye]
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
                target+=area->w-1;
                for(var i=xs; i <= xe; i++, target-- ){
                    int k = (int)(xe + xs - i); // reverse i   i in (xs->xe); k in (xe -> xs)

                    if( k != xe ){
                        // No need to do when it reachs the right-edge because it has been done when moving to the next row.
                        // Remove rightmost column because it is old.
                        if(k+half_order <= xe ){                                // [!] no cross the broad [0,src->w-1] [xs,xe]
                            for(int row  = j-half_order+1,\
                                    iter = (int)(src->w*(j-half_order+1)+k+half_order);
                                
                                row <= j+half_order-1;\
                                
                                row++,\
                                iter+=src->w){
                                if( row<=ye && row>=ys ){                       // [!] no cross the broad [0,src->h-1] [ys,ye]
                                    sum_R -= pSrcData[ iter ].R;
                                    sum_G -= pSrcData[ iter ].G;
                                    sum_B -= pSrcData[ iter ].B;
                                    div--;
                                }
                            }
                        }
                        
                        // Add leftmost column because it is new.
                        if(k-half_order+1 >= xs ){                              // [!] no cross the broad [0,src->w-1] [xs,xe]
                            for(var row  = j-half_order+1,\
                                    iter = (int)(src->w*(j-half_order+1)+k-half_order+1);
                                
                                row <= j+half_order-1;\
                                
                                row++,\
                                iter+=src->w){
                                if( row<=ye && row>=ys ){                       // [!] no cross the broad [0,src->h-1] [ys,ye]
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
                target += area->w+1;
                
            }
            // End of scanning of this row.
            
            // Remove topmost row because it is old.
            if( j-half_order+1 >= ys ){         // [!] no cross the broad [0,src->h-1] [ys,ye]
                
                if((j&0x01) == 0){ // Scan Direction:  [old] -->--> [new]. Now it is reaching the rightmost.
                    for(var col  = xe+1-half_order,\
                            iter = src->w*(j-half_order+1) + xe+1-half_order;\
                        
                        col <= xe;\
                        
                        col++ ,\
                        iter++ ){
                        sum_R -= pSrcData[ iter ].R;
                        sum_G -= pSrcData[ iter ].G;
                        sum_B -= pSrcData[ iter ].B;
                        div--;
                    }
                }else{        // Scan Direction:  [new] <--<-- [old]. Now it is reaching the leftmost.
                    for(var col  = xs,\
                            iter = src->w*(j-half_order+1) + xs;\
                        
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
            if(j+half_order <= ye ){         // [!] no cross the broad [0,src->h-1] [ys,ye]
                
                if((j&0x01) == 0){ // Scan Direction:  [old] -->--> [new]. Now it is reaching the rightmost.
                    for(var col  = xe+1-half_order,\
                            iter = src->w*(j+half_order) + col;
                        
                        col <= xe;\
                        
                        col++,
                        iter++){
                        sum_R += pSrcData[ iter ].R;
                        sum_G += pSrcData[ iter ].G;
                        sum_B += pSrcData[ iter ].B;
                        div++;
                    }
                }else{        // Scan Direction:  [new] <--<-- [old]. Now it is reaching the leftmost.
                    for(var col  = xs,\
                            iter = src->w*(j+half_order) + col;\
                        
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


        if(src->ptr == dst->ptr){
//            RH_ASSERT(0);
            memcpy(dst->ptr,pDstData,src->h*src->w*sizeof(BLK_UION(Pixel888)));
            RH_FREE(pDstData);
        }
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, blur_fast   )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,__Area_t* area,uint32_t radSize, uint16_t br_100){
    __exitReturn( !src || !dst || !src->ptr || !dst->ptr, NULL );
        
        const int xs = area->xs;
        const int ys = area->ys;
        const int xe = (int)(area->xs + area->w  -1);
     // const int ye = (int)(area->ys + area->h -1);
        
        const BLK_UION(Pixel888)* pSrcData = src->ptr;
        BLK_UION(Pixel888)*       pDstData = dst->ptr;

        BLK_UION(Pixel888)*       pTmpData = dst->ptr;//RH_MALLOC( area->w*area->h*sizeof(BLK_UION(Pixel888)) );
        
        

        long accumulate_R=0, accumulate_G=0, accumulate_B=0;
        // Horizontal Processing
        for( int y=0; y<area->h; y++ ){
            BLK_UION(Pixel888) pix_s = pSrcData[ (y+ys)*src->w + xs ];
            BLK_UION(Pixel888) pix_e = pSrcData[ (y+ys)*src->w + xe ];
            
            accumulate_B = (radSize+1)*pix_s.B;
            accumulate_G = (radSize+1)*pix_s.G;
            accumulate_R = (radSize+1)*pix_s.R;


            int lx = 0;
            int rx = radSize;
            // printf( "rx=%d lx=%d\n",rx,lx );
            for( int x=0; x<radSize; x++){
                accumulate_B += pSrcData[ (y+ys)*src->w + xs+x ].B;
                accumulate_G += pSrcData[ (y+ys)*src->w + xs+x ].G;
                accumulate_R += pSrcData[ (y+ys)*src->w + xs+x ].R;
            }
            
            // Now: rx=radSize; lx=0;
            // printf( "rx=%d lx=%d\n",rx,lx );
            for( int x=0; x<=radSize; x++, rx++ ){
                accumulate_B += pSrcData[ (y+ys)*src->w + xs+rx ].B - pix_s.B;
                accumulate_G += pSrcData[ (y+ys)*src->w + xs+rx ].G - pix_s.G;
                accumulate_R += pSrcData[ (y+ys)*src->w + xs+rx ].R - pix_s.R;

                pTmpData[ y*area->w + x ].B = accumulate_B / ((radSize<<1)+1);
                pTmpData[ y*area->w + x ].G = accumulate_G / ((radSize<<1)+1);
                pTmpData[ y*area->w + x ].R = accumulate_R / ((radSize<<1)+1);
            }
            
            // Now: rx=2*radSize+1; lx=0;
            // printf( "rx=%d lx=%d\n",rx,lx );
            for( int x=radSize+1; x<area->w-radSize; x++,rx++,lx++ ){
                accumulate_B += pSrcData[ (y+ys)*src->w + xs+rx ].B - pSrcData[ (y+ys)*src->w + xs+lx ].B;
                accumulate_G += pSrcData[ (y+ys)*src->w + xs+rx ].G - pSrcData[ (y+ys)*src->w + xs+lx ].G;
                accumulate_R += pSrcData[ (y+ys)*src->w + xs+rx ].R - pSrcData[ (y+ys)*src->w + xs+lx ].R;
            
                pTmpData[ y*area->w + x ].B = accumulate_B / ((radSize<<1)+1);
                pTmpData[ y*area->w + x ].G = accumulate_G / ((radSize<<1)+1);
                pTmpData[ y*area->w + x ].R = accumulate_R / ((radSize<<1)+1);
            }

            // Now: rx=area->w; lx=area->w-2*radSize-1;
            // printf( "rx=%d lx=%d\n",rx,lx );
            for( int x=(int)(area->w-radSize); x<area->w; x++,lx++ ){
                accumulate_B += pix_e.B - pSrcData[ (y+ys)*src->w + xs+lx ].B;
                accumulate_G += pix_e.R - pSrcData[ (y+ys)*src->w + xs+lx ].G;
                accumulate_R += pix_e.R - pSrcData[ (y+ys)*src->w + xs+lx ].R;
            
                pTmpData[ y*area->w + x ].B = accumulate_B / ((radSize<<1)+1);
                pTmpData[ y*area->w + x ].G = accumulate_G / ((radSize<<1)+1);
                pTmpData[ y*area->w + x ].R = accumulate_R / ((radSize<<1)+1);
            }
            // printf( "rx=%d lx=%d\n\n",rx,lx);

        }
        
        // Trunk Processing
        for( int x=0; x<area->w; x++ ){
            BLK_UION(Pixel888) pix_s = pSrcData[                       x ];
            BLK_UION(Pixel888) pix_e = pSrcData[ (area->h-1)*area->w + x ];

            accumulate_B = (radSize+1)*pix_s.B;
            accumulate_G = (radSize+1)*pix_s.G;
            accumulate_R = (radSize+1)*pix_s.R;

            int ty = 0;
            int by = radSize;

            for( int y=0; y<radSize; y++ ){
                accumulate_B += pTmpData[ y*area->w + x ].B;
                accumulate_G += pTmpData[ y*area->w + x ].G;
                accumulate_R += pTmpData[ y*area->w + x ].R;
            }

            for( int y=0; y<=radSize; y++,by++ ){
                accumulate_B += pTmpData[ by*area->w + x ].B - pix_s.B;
                accumulate_G += pTmpData[ by*area->w + x ].G - pix_s.G;
                accumulate_R += pTmpData[ by*area->w + x ].R - pix_s.R;

                pDstData[ y*area->w + x ].B = accumulate_B / ((radSize<<1)+1);
                pDstData[ y*area->w + x ].G = accumulate_G / ((radSize<<1)+1);
                pDstData[ y*area->w + x ].R = accumulate_R / ((radSize<<1)+1);
            }

            for( int y=radSize+1; y<area->h-radSize; y++, ty++, by++ ){
                accumulate_B += pTmpData[ by*area->w + x ].B - pTmpData[ ty*area->w + x ].B;
                accumulate_G += pTmpData[ by*area->w + x ].G - pTmpData[ ty*area->w + x ].G;
                accumulate_R += pTmpData[ by*area->w + x ].R - pTmpData[ ty*area->w + x ].R;

                pDstData[ y*area->w + x ].B = accumulate_B / ((radSize<<1)+1);
                pDstData[ y*area->w + x ].G = accumulate_G / ((radSize<<1)+1);
                pDstData[ y*area->w + x ].R = accumulate_R / ((radSize<<1)+1);
            }

            for( int y=(int)(area->h-radSize); y<area->h; y++, ty++ ){
                accumulate_B += pix_e.B - pTmpData[ ty*area->w + x ].B;
                accumulate_G += pix_e.G - pTmpData[ ty*area->w + x ].G;
                accumulate_R += pix_e.R - pTmpData[ ty*area->w + x ].R;

                pDstData[ y*area->w + x ].B = accumulate_B / ((radSize<<1)+1);
                pDstData[ y*area->w + x ].G = accumulate_G / ((radSize<<1)+1);
                pDstData[ y*area->w + x ].R = accumulate_R / ((radSize<<1)+1);
            }

        }
        
        RH_FREE( pTmpData );
    return dst;
}



BLK_SRCT(Img888)* BLK_FUNC( Img888, insert_NstNeighbor )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,size_t height,size_t width){
    if(src == NULL || src->ptr == NULL || dst == NULL) // Bad address
        return NULL;
    if(height < src->h || width < src->w) // Image of "dst" should be larger than image of "src" in both dimension.
        return NULL;
    if(dst->ptr == NULL){
        dst->ptr = (BLK_UION(Pixel888)*)RH_MALLOC(width*height*sizeof(BLK_UION(Pixel888)));
        if(dst->ptr == NULL){
            return NULL;  // There is no space to malloc.
        }
    }
    dst->h = height;
    dst->w = width;
    memset(dst->ptr, 0, width*height*sizeof(BLK_UION(Pixel888)));
    
    var eps_x = 0; // Record errors no bigger than w.
    var eps_y = 0; // Record errors no bigger than h.
    var fx    = 0; // Pixel cordination of original image in x direction.
    var fy    = 0; // Pixel cordination of original image in y direction.
    for(var gy=0;gy<height;gy++){
        eps_y += src->h;
        if(eps_y >= height){
            fx = 0;
            for(var gx=0;gx<width;gx++){
                eps_x += src->w;
                if( eps_x >= width ){
                    // This is the position to copy pixels from original image.
                    (dst->ptr + (width*gy) + gx)->data = (src->ptr + (src->w*fy) + fx)->data;
                    eps_x-=width;
                    fx++;
                }else{
                    // This is the position needs to interpolate.
                    //...//
                }
            }
            eps_y -= height;
            fy++;
        }else
            continue;
    }
    
    return dst;
}


BLK_SRCT(Img888)* BLK_FUNC( Img888, conv2D      )  (const BLK_SRCT(Img888)* src,BLK_SRCT(Img888)* dst,const BLK_SRCT(Kernel)* k,uint16_t br_100){
    if( !src || !src->ptr || !k || !dst || !dst->ptr ){
        return NULL;
    }

    for(var j=0;j<src->h;j++){
        for(var i=0;i<src->w;i++){
            long div = k->sum;
            
            // Here comes the convolution part.
            unsigned long tmp_R = 0,tmp_G = 0,tmp_B = 0; // Preparation for RGB data.
            for(var n=0;n<k->order;n++){
                for(var m=0;m<k->order;m++){
                    var offset_y  = j-(k->order>>1)+n;
                    var offset_x  = i-(k->order>>1)+m;
                    int selectKernel = *( k->pBuffer + n       * k->order + m       );
                    if( offset_x>=src->w || offset_y>=src->h ){
                        div -= selectKernel;
                    }else{
                        uint8_t select_R  = (src->ptr + offset_y*src->w + offset_x)->R;
                        uint8_t select_G  = (src->ptr + offset_y*src->w + offset_x)->G;
                        uint8_t select_B  = (src->ptr + offset_y*src->w + offset_x)->B;
                        
                        tmp_R += ( (select_R) * (selectKernel) );
                        tmp_G += ( (select_G) * (selectKernel) );
                        tmp_B += ( (select_B) * (selectKernel) );
                    }
                }
            }
            size_t offset = (j*src->w)+i;
            if(offset < dst->w*dst->h){
                unsigned long temp = 0;
                
                temp = (tmp_R*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->ptr+offset)->R = (uint8_t)((1<<8)-1);
                else                                (dst->ptr+offset)->R = (uint8_t)(temp);
                
                temp = (tmp_G*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->ptr+offset)->G = (uint8_t)((1<<8)-1);
                else                                (dst->ptr+offset)->G = (uint8_t)(temp);
                
                temp = (tmp_B*br_100)/(div*100);
                if( div == 0 || temp >= (1<<8) )    (dst->ptr+offset)->B = (uint8_t)((1<<8)-1);
                else                                (dst->ptr+offset)->B = (uint8_t)(temp);
                
            }
        }
    }
    
    return dst;
}
   
void              BLK_FUNC( Img888, data_OTUS   )  (const BLK_SRCT(Img888)* src,uint8_t* threshold){
    __exit( !threshold );
    *threshold = (uint8_t)(-1);
    __exit( !src      );
    __exit( !src->ptr );
    
    uint8_t  threshold_temp;
    long   NumOf_bckPixel = 0;    //Number of pixels defined as background
    long   SumOf_bckPixel = 0;    //Sum of pixels defined as background
    float  AvgOf_bckPixel = 0.0;  //Average value of pixels defined as background

    long   NumOf_objPixel = 0;    //Number of pixels defined as background
    long   SumOf_objPixel = 0;    //Sum of pixels defined as background
    float  AvgOf_objPixel = 0.0;  //Average value of pixels defined as background
    
    float  g = 0.0, g_max = 0.0;  //Variance between obj and bck
    
    const long NumOf_allPixel = (src->w) * (src->h);
    
    // Make Statistic...

    long gray_cnt[255] = {0};
    BLK_UION(Pixel888) *pIterSrc = src->ptr;
    for (var row = 0; row < src->h; row++){
        for (var col = 0; col < src->w; col++,pIterSrc++){
            uint8_t temp = ( pIterSrc->R*38 + \
                             pIterSrc->G*75 + \
                             pIterSrc->B*15 )>>7;
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
(const BLK_SRCT(ImgGry)* src,BLK_SRCT(ImgBin)* dst,int xs, int ys,BLK_TYPE(Color) obj_color, uint8_t br_100){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    RH_ASSERT(xs < dst->w);
    RH_ASSERT(ys < dst->h);
    
    const BLK_UION(PixelGry)*   pIterSrc = src->ptr;
    BLK_UION(PixelBin)*         pIterDst = &dst->ptr[((ys)>>3)*(dst->w)+(xs)];
    BLK_UION(PixelBin) color = {.data = MAKE_COLOR_1BIT( (obj_color>>16)&0xff, (obj_color>>8)&0xff, (obj_color)&0xff) };
    for( var y=0; y<src->h && y<dst->h; y++ ){
        pIterDst = dst->ptr + ((ys+y)>>3)*(dst->w) + xs;
        for( var x=0; x<src->w; x++, pIterSrc++,pIterDst++ ){
            if( (pIterSrc->data<128) ^ (color.data!=0) ){
                pIterDst->data = __BIT_SET( pIterDst->data, (ys+y)%8 );
            }else{
                pIterDst->data = __BIT_CLR( pIterDst->data, (ys+y)%8 );
            }
        }
    }
    
    return dst;
}
    
BLK_SRCT(Img565)* BLK_FUNC( ImgGry, into_Img565 )
(const BLK_SRCT(ImgGry)* src,BLK_SRCT(Img565)* dst,int xs, int ys,BLK_TYPE(Color) obj_color, uint8_t br_100){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    RH_ASSERT(xs<dst->w);
    RH_ASSERT(ys<dst->h);
    
    const BLK_UION(PixelGry)*      pIterSrc = src->ptr;
    BLK_UION(Pixel565)*            pIterDst = dst->ptr+ys*dst->w+xs;
    
    BLK_UION(Pixel565) color = {.data = MAKE_COLOR_16BIT( (obj_color>>16)&0xff, (obj_color>>8)&0xff, (obj_color)&0xff) };
    for( var y=0; y<src->h&&y<dst->h; y++ ){
        for( var x=0; x<src->w; x++,pIterSrc++, pIterDst++ ){
            pIterDst->R = pIterDst->R + (( (color.R - pIterDst->R) * (pIterSrc->data) )>>8);
            pIterDst->G = pIterDst->G + (( (color.G - pIterDst->G) * (pIterSrc->data) )>>8);
            pIterDst->B = pIterDst->B + (( (color.B - pIterDst->B) * (pIterSrc->data) )>>8);
        }
        pIterDst -= src->w;
        pIterDst += dst->w;
    }
    
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( ImgGry, into_Img888 )
(const BLK_SRCT(ImgGry)* src,BLK_SRCT(Img888)* dst,int xs, int ys,BLK_TYPE(Color) obj_color, uint8_t br_100){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    RH_ASSERT(xs < dst->w);
    RH_ASSERT(ys < dst->h);
    
    br_100 = RH_LIMIT((signed)br_100, 0, 100);
    
    const BLK_UION(PixelGry)*      pIterSrc = src->ptr;
    BLK_UION(Pixel888)*            pIterDst = dst->ptr+ys*dst->w+xs;
    
    BLK_UION(Pixel888) color = {.data = obj_color&0x00ffffff};
    if( br_100 == 100 ){
        for( var y=0; y<src->h&&y<dst->h; y++ ){
            for( var x=0; x<src->w; x++,pIterSrc++, pIterDst++ ){
                pIterDst->R += (( (color.R - pIterDst->R) * (pIterSrc->data) )>>8);
                pIterDst->G += (( (color.G - pIterDst->G) * (pIterSrc->data) )>>8);
                pIterDst->B += (( (color.B - pIterDst->B) * (pIterSrc->data) )>>8);
            }
            pIterDst -= src->w;
            pIterDst += dst->w;
        }
    }else if( br_100 == 50 ){
        for( var y=0; y<src->h&&y<dst->h; y++ ){
            for( var x=0; x<src->w; x++,pIterSrc++, pIterDst++ ){
                pIterDst->R += (( (color.R - pIterDst->R) * (pIterSrc->data) )>>9);
                pIterDst->G += (( (color.G - pIterDst->G) * (pIterSrc->data) )>>9);
                pIterDst->B += (( (color.B - pIterDst->B) * (pIterSrc->data) )>>9);
            }
            pIterDst -= src->w;
            pIterDst += dst->w;
        }
    }else{
        int div = 25500/br_100;
        for( int y=0; y<src->h&&y<dst->h; y++ ){
            for( var x=0; x<src->w; x++,pIterSrc++, pIterDst++ ){
                pIterDst->R += (( (color.R - pIterDst->R) * (pIterSrc->data) )/div);
                pIterDst->G += (( (color.G - pIterDst->G) * (pIterSrc->data) )/div);
                pIterDst->B += (( (color.B - pIterDst->B) * (pIterSrc->data) )/div);
            }
            pIterDst -= src->w;
            pIterDst += dst->w;
        }
    }
    
    return dst;
}
    
BLK_SRCT(ImgBin)* BLK_FUNC( ImgBin, draw_img_aurora )
( BLK_SRCT(ImgBin)* dst, const BLK_TYPE(PixelBin)* colors, size_t size ){
    RH_ASSERT( dst          );

    
    RH_ASSERT(0);
    return dst;
}
    
BLK_SRCT(Img565)* BLK_FUNC( Img565, draw_img_aurora )
( BLK_SRCT(Img565)* dst, const BLK_TYPE(Pixel565)* colors, size_t size ){
    RH_ASSERT( dst      );
    RH_ASSERT( dst->ptr );
    RH_ASSERT( dst->h   );
    RH_ASSERT( dst->w   );

    
    const var sect = (dst->w)/(var)(size+1);
    var* xc = alloca((size+1)*sizeof(var));
    for( var i=1; i<=(size+1); i++){
        xc[i-1] = dst->w*i/(var)(size+1);
    }
    
    for( var x=0; x<=dst->w-1; x++ ){
        var stage = 0;
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
        
        
        var ys = (var)BLK_FUNC(Math,rand)()%(dst->h/3), ye = (int)(dst->h<<1)/3 + (unsigned)BLK_FUNC(Math,rand)()%(dst->h/3);
        
        float _2_sigma_2 = (ye-ys)*(ye-ys)/18.0;
        BLK_UION(Pixel565)* pIterUP = dst->ptr + ys*(dst->w) +x;
        BLK_UION(Pixel565)* pIterDN = dst->ptr + ye*(dst->w) +x;
#if 1
        // 以下代码被性能优化
        for( var y=ys, tmp = ((ye - ys)*(ye - ys)>>2); pIterUP<=pIterDN; y++, pIterUP+=dst->w, pIterDN-=dst->w, tmp += ((y+1)<<1)-(ye+ys) ){
            pIterUP->R = pIterDN->R = (uint8_t)lroundl( color.R* exp2( -tmp/_2_sigma_2));
            pIterUP->G = pIterDN->G = (uint8_t)lroundl( color.G* exp2( -tmp/_2_sigma_2));
            pIterUP->B = pIterDN->B = (uint8_t)lroundl( color.B* exp2( -tmp/_2_sigma_2));
            
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
    RH_ASSERT( dst      );
    RH_ASSERT( dst->ptr );
    RH_ASSERT( dst->h   );
    RH_ASSERT( dst->w   );
    
    const var sect = (var)((dst->w)/(var)(size+1));
    var* xc = alloca((size+1)*sizeof(var));
    for( size_t i=1; i<=(size+1); i++){
        xc[i-1] = (var)(dst->w*i)/(var)(size+1);
    }
    
    for( var x=0; x<=dst->w-1; x++ ){
        size_t stage = 0;
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
        
        
        var ys = ((unsigned)BLK_FUNC(Math,rand)())%(dst->h/3), ye = (var)(dst->h<<1)/3 + ((unsigned)BLK_FUNC(Math,rand)())%(dst->h/3);
        
        BLK_UION(Pixel888)* pIterUP = dst->ptr + ys*(dst->w) +x;
        BLK_UION(Pixel888)* pIterDN = dst->ptr + ye*(dst->w) +x;
        
#if 0
        // 原代码_2 为:
        for( int y=ys; pIterUP<=pIterDN; y++, pIterUP+=dst->w, pIterDN-=dst->w ){
            int tmp = (y-((ye+ys)>>1))*(y-((ye+ys)>>1));
            pIterUP->R = pIterDN->R = roundl( color.R* exp2( -tmp/_2_sigma_2));
            pIterUP->G = pIterDN->G = roundl( color.G* exp2( -tmp/_2_sigma_2));
            pIterUP->B = pIterDN->B = roundl( color.B* exp2( -tmp/_2_sigma_2));
        }
        // 原代码_1 为:
        for( int y=ys; y<=ye; y++, pIterUP+=dst->w, pIterDN-=dst->w ){
            int tmp = (y-((ye-ys)>>1)-ys)*(y-((ye-ys)>>1)-ys);
            pIterUP->R = roundl( color.R* exp( -tmp/(2*sigma_2)));
            pIterUP->G = roundl( color.G* exp( -tmp/(2*sigma_2)));
            pIterUP->B = roundl( color.B* exp( -tmp/(2*sigma_2)));
            printf("%d\n",tmp);
        }
        
#elif 0 // 初级优化
        float _2_sigma_2 = (ye-ys)*(ye-ys)/18.0;
        long tmp = ((ye - ys)*(ye - ys)>>2);
        for( var y=ys; pIterUP<=pIterDN; y++, pIterUP+=dst->w, pIterDN-=dst->w, tmp += ((y+1)<<1)-(ye+ys) ){
            
            pIterUP->R = pIterDN->R = roundl( color.R* exp2( -tmp/_2_sigma_2));
            pIterUP->G = pIterDN->G = roundl( color.G* exp2( -tmp/_2_sigma_2));
            pIterUP->B = pIterDN->B = roundl( color.B* exp2( -tmp/_2_sigma_2));
            
        }
        
#elif 1 // 高级优化
        
        const uint8_t gus_exp[257] = {   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,\
                                         2,   2,   2,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,\
                                         3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,\
                                         5,   6,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,   8,   8,\
                                         9,   9,   9,  10,  10,  10,  11,  11,  11,  12,  12,  13,  13,  13,\
                                        14,  14,  15,  15,  16,  16,  17,  17,  18,  18,  19,  19,  20,  20,\
                                        21,  22,  22,  23,  24,  24,  25,  26,  26,  27,  28,  29,  30,  30,\
                                        31,  32,  33,  34,  35,  36,  37,  37,  38,  39,  40,  41,  43,  44,\
                                        45,  46,  47,  48,  49,  50,  52,  53,  54,  55,  56,  58,  59,  60,\
                                        62,  63,  65,  66,  67,  69,  70,  72,  73,  75,  76,  78,  79,  81,\
                                        83,  84,  86,  88,  89,  91,  93,  94,  96,  98, 100, 101, 103, 105,\
                                       107, 109, 111, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132,\
                                       134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160,\
                                       162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188,\
                                       190, 191, 193, 195, 197, 199, 201, 203, 204, 206, 208, 210, 211, 213,\
                                       215, 216, 218, 219, 221, 222, 224, 225, 227, 228, 230, 231, 232, 234,\
                                       235, 236, 237, 239, 240, 241, 242, 243, 244, 245, 246, 246, 247, 248,\
                                       249, 249, 250, 251, 251, 252, 252, 253, 253, 254, 254, 254, 254, 255,\
                                       255, 255, 255, 255, 255 };
        
        size_t idx = 0;
        for( var y=ys; pIterUP<=pIterDN; y++, pIterUP+=dst->w, pIterDN-=dst->w ){
            idx = ((y-ys)<<9)/(ye-ys);
            RH_ASSERT( idx<=256 );
            
            pIterUP->R = pIterDN->R = color.R*gus_exp[idx]>>8 ;
            pIterUP->G = pIterDN->G = color.G*gus_exp[idx]>>8 ;
            pIterUP->B = pIterDN->B = color.B*gus_exp[idx]>>8 ;
            
        }
        

#endif
        
    }
    
    return dst;
}

    
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_ )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    RH_ASSERT( dst      );
    RH_ASSERT( dst->ptr );
    RH_ASSERT( dst->h   );
    RH_ASSERT( dst->w   );
    
    const var x0 = dst->w>>1;
    const var y0 = dst->h>>1;
    const var r0 = RH_MIN(dst->w, dst->h)/3;
    
    dst->ptr[y0*dst->w+x0].data = M_COLOR_WHITE;
    
    struct{
        var x;
        var y;
    }cord[19];
    
    // 获取 以(x0,y0)为中心, 0度 10度...180度的坐标
    for( int8_t a=0,cnt=0; a<=90; a+=10,cnt++ ){
        cord[cnt     ].x = (int)lround(x0+r0*cos(a*M_PI/180));
        cord[19-cnt-1].x = 2*x0-cord[cnt].x;
        cord[cnt     ].y =  cord[19-cnt-1].y = (int)lround(y0+r0*sin(a*M_PI/180));
    }
    
    for( int i=0; i<19; i++ ){
        dst->ptr[( cord[i].y )*dst->w+cord[i].x].data = M_COLOR_WHITE;
    }
    
    // 填充颜色
#if 1
    for( var cnt=0; cnt<18; cnt++ ){
        uint32_t c = rand()%0x00ffffff;
        // xs 的轨迹为圆心至动点直线, xe 的轨迹为圆弧
        int xs = RH_MIN(x0, RH_MIN(cord[cnt].x, cord[cnt+1].x));
        int xe = RH_MAX(x0, RH_MAX(cord[cnt].x, cord[cnt+1].x));
        int ys = RH_MIN(y0, RH_MIN(cord[cnt].y, cord[cnt+1].y));
        int ye = RH_MAX(y0, RH_MAX(cord[cnt].y, cord[cnt+1].y));
        
         // 填充三个点组成的三角形: (x0,y0) (cord[cnt].x, cord[cnt].y) (cord[cnt+1].x, cord[cnt+1].y)
        for(int y=ys; y<=ye; y++){
            int x = xs;

            while( kBLK_PtPos_outside==BLK_FUNC( Math, pt_triangle )( x0, y0, cord[cnt].x, cord[cnt].y, cord[cnt+1].x, cord[cnt+1].y, x, y) && x<=xe ){
                x++;
            }
            while( kBLK_PtPos_inside==BLK_FUNC( Math, pt_triangle )( x0, y0, cord[cnt].x, cord[cnt].y, cord[cnt+1].x, cord[cnt+1].y, x, y) && x<=xe ){
                dst->ptr[ (y)*dst->w+x].data = c;
                x++;
            }

        }
    }
#endif
    
    return dst;
}

    
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_radar   )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    RH_ASSERT( dst      );
    RH_ASSERT( dst->ptr );
    RH_ASSERT( dst->h   );
    RH_ASSERT( dst->w   );
    
    var cx = dst->w>>1;
    var cy = dst->h>>1;
    
    /* About this <type> : 通过平移, 将(x1,y1)移到原点, 此时(x2,y2)的位置决定type.
    
                      Y
          *           |           *
         (x0,y0)      |      (x1,y1)
              *       |       *
                *     |     *
                  *   |   *
                    * | *
    ------------------+------------------ X
                    * | *
                  *   |   *
                *     |     *
              *       |       *
         (x3,y3)      |       (x2,y2)
          *           |           *
     
     */
    
    var x[4] = {0};
    var y[4] = {0};
    
    x[0] = x[3] = RH_LIMIT( cx-cy,  0, cx      );
    x[1] = x[2] = RH_LIMIT( cx+cy, cx, dst->w-1);
    
    y[0] = y[1] = RH_LIMIT( cy-cx,  0, cy      );
    y[2] = y[3] = RH_LIMIT( cy+cx, cy, dst->h-1);
    
    var step = RH_LIMIT( RH_MIN(dst->w, dst->h) / 10, 5, dst->w);
    
    int r = step*2;
    
    if( !colors )
        size = 0;
    
    if( size < 4 ){
        BLK_TYPE(Pixel888)* temp = (BLK_TYPE(Pixel888)*)alloca( 4*sizeof(BLK_TYPE(Pixel888)) );
        memset(temp, 0xff, 4*sizeof(BLK_TYPE(Pixel888)));
        memcpy(temp, colors, size*sizeof(BLK_TYPE(Pixel888)));
        colors = temp;
    }
    
    BLK_FUNC(Graph,backupCache)();
    BLK_FUNC(Graph,set_penSize       )( RH_LIMIT( step/9, 1, step ));
    BLK_FUNC(Graph,set_penColor      )( M_COLOR_YELLOW );
    BLK_FUNC(Graph,set_color_depth   )( kBLK_ColorDepth_24Bit  );
    BLK_FUNC(Graph,set_render_method )( kBLK_RenderMethod_fill );
    
    // 绘制45度斜线
    BLK_FUNC(Graph,set_penColor      )( colors[2] );
    BLK_FUNC(Graph,line_edged        )( (int)x[0], (int)y[0], (int)x[2], (int)y[2], dst, NULL);
    BLK_FUNC(Graph,line_edged        )( (int)x[1], (int)y[1], (int)x[3], (int)y[3], dst, NULL);
    
    // 绘制靶心
    BLK_FUNC(Graph,set_penColor      )( colors[0] );
    BLK_FUNC(Graph,circle_fill       )( (int)cx, (int)cy,  (int)(step<<1), dst, NULL);
    
    // 绘制十字准心
    BLK_FUNC(Graph,set_penColor      )( colors[1] );
    BLK_FUNC(Graph,line_edged        )( (int)cx, (int) 0, (int)cx       , (int)dst->h-1, dst, NULL);
    BLK_FUNC(Graph,line_edged        )( (int) 0, (int)cy, (int)dst->w -1, (int)cy      , dst, NULL);
    
    BLK_FUNC(Graph,set_penColor      )( colors[3] );
    while( r < RH_MAX( dst->w, dst->h ) ){
        BLK_FUNC(Graph,circle_edged  )( (int)cx, (int)cy, (int)(r<<1), dst, NULL );
        r+=step;
    }
    BLK_FUNC(Graph,restoreCache)();
    return dst;
}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_faded   )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    RH_ASSERT( dst          );
    RH_ASSERT( dst->ptr );
    RH_ASSERT( dst->h  );
    RH_ASSERT( dst->w   );
    
    BLK_UION(Pixel888)* p = dst->ptr;
    // 染蓝色
    for(int y=0; y<dst->h; y++){
        for(int x=0; x<dst->w; x++,p++){
            p->B =0x7e;
        }
    }
    
    // 染红色
    p = dst->ptr;
    int delta_x    = (int)( dst->w );
    int delta_y    = (int)( 0xff );
    int j = 0;
    int e = 0;
    for(int x=0; x<dst->w; x++,p++){
        BLK_UION(Pixel888)* q = p;
        for(int y=0; y<dst->h; y++,q+=dst->w){
            q->R = j;
        }
        e += delta_y;
        while( ( (e+delta_y)<<1 ) > delta_x){
            j++;
            e -= delta_x;
        }
    }
    
    // 染绿色
    p = dst->ptr;
    delta_x    = (int)( dst->h );
    delta_y    = (int)( 0xff );
    j = 0;
    e = 0;
    for(int y=0; y<dst->h; y++){
        
        for(int x=0; x<dst->w; x++,p++){
            p->G = j;
        }
        e += delta_y;
        while( ( (e+delta_y)<<1 ) > delta_x){
            j++;
            e -= delta_x;
        }
    }
    
    return dst;
}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_blur    )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    
    var sig_x = dst->w>>1;
    var sig_y = dst->h>>1;
    
    const BLK_UION(Pixel888) colorB = {.data=colors[0]};
    const BLK_UION(Pixel888) colorA = {.data=colors[1]};
    
    
#if 0  // 初级优化
    var miu_x = dst->w>>1;
    var miu_y = dst->h>>1;
    
    BLK_UION(Pixel888)* pIter = dst->ptr;
    for( var y=0; y<dst->h; y++){
        for( var x=0; x < dst->w; x++, pIter++){
            float del = expf(-0.5*( ((x-miu_x)*(x-miu_x))/(float)(sig_x*sig_x) + ((y-miu_y)*(y-miu_y))/(float)(sig_y*sig_y) ));
            BLK_GRAPH_ASSERT(del <= 1.0);
            pIter->R = roundf( colorA.R+del*(colorB.R-colorA.R) );
            pIter->G = roundf( colorA.G+del*(colorB.G-colorA.G) );
            pIter->B = roundf( colorA.B+del*(colorB.B-colorA.B) );
            
        }
    }
    
#elif 0  // 二次优化
    var miu_x = dst->w>>1;
    var miu_y = dst->h>>1;
    
    BLK_UION(Pixel888)* pIter2 = dst->ptr;
    BLK_UION(Pixel888)* pIter1 = dst->ptr+dst->w-1;
    BLK_UION(Pixel888)* pIter3 = dst->ptr+(dst->h-1)*dst->w;
    BLK_UION(Pixel888)* pIter4 = dst->ptr+dst->h*dst->w-1;
    
    pIter2->data = M_COLOR_ORANGE;
    pIter1->data = M_COLOR_RED;
    pIter3->data = M_COLOR_YELLOW;
    pIter4->data = M_COLOR_GREEN;
    
    for( int ys=0,ye=(int)dst->h-1; ys<=ye; ys++,ye--,  pIter2+=dst->w,pIter1+=dst->w,pIter3-=dst->w,pIter4-=dst->w){
        for( int xs=0,xe=(int)dst->w-1; xs<=xe; xs++,xe--,  pIter1--,pIter4--,pIter2++,pIter3++ ){
            
            float del = expf(-0.5*( ((xs-miu_x)*(xs-miu_x))/(float)(sig_x*sig_x) + ((ys-miu_y)*(ys-miu_y))/(float)(sig_y*sig_y) ));
            BLK_GRAPH_ASSERT(del <= 1.0);
            pIter2->R = pIter1->R = pIter3->R = pIter4->R = roundf( colorA.R+del*(colorB.R-colorA.R) );
            pIter2->G = pIter1->G = pIter3->G = pIter4->G = roundf( colorA.G+del*(colorB.G-colorA.G) );
            pIter2->B = pIter1->B = pIter3->B = pIter4->B = roundf( colorA.B+del*(colorB.B-colorA.B) );
        }
        pIter1+=(dst->w>>1)+(dst->w&0x01);
        pIter2-=(dst->w>>1)+(dst->w&0x01);
        pIter3-=(dst->w>>1)+(dst->w&0x01);
        pIter4+=(dst->w>>1)+(dst->w&0x01);
    }
    
#else
    BLK_UION(Pixel888)* pIter2 = dst->ptr;
    BLK_UION(Pixel888)* pIter1 = dst->ptr+dst->w-1;
    BLK_UION(Pixel888)* pIter3 = dst->ptr+(dst->h-1)*dst->w;
    BLK_UION(Pixel888)* pIter4 = dst->ptr+dst->h*dst->w-1;
    
    const uint8_t exps[257] = {  255 , 255 , 255 , 254 , 253 , 252 , 251 , 250 , 249 , 248 , 247 , 246 , 245 , 244 , \
                                 243 , 242 , 241 , 240 , 240 , 239 , 238 , 237 , 236 , 235 , 234 , 233 , 232 , 231 , \
                                 230 , 229 , 229 , 228 , 227 , 226 , 225 , 224 , 223 , 222 , 222 , 221 , 220 , 219 , \
                                 218 , 217 , 216 , 216 , 215 , 214 , 213 , 212 , 211 , 211 , 210 , 209 , 208 , 207 , \
                                 207 , 206 , 205 , 204 , 203 , 203 , 202 , 201 , 200 , 199 , 199 , 198 , 197 , 196 , \
                                 196 , 195 , 194 , 193 , 192 , 192 , 191 , 190 , 190 , 189 , 188 , 187 , 187 , 186 , \
                                 185 , 184 , 184 , 183 , 182 , 182 , 181 , 180 , 179 , 179 , 178 , 177 , 177 , 176 , \
                                 175 , 175 , 174 , 173 , 173 , 172 , 171 , 171 , 170 , 169 , 169 , 168 , 167 , 167 , \
                                 166 , 165 , 165 , 164 , 163 , 163 , 162 , 161 , 161 , 160 , 160 , 159 , 158 , 158 , \
                                 157 , 156 , 156 , 155 , 155 , 154 , 153 , 153 , 152 , 152 , 151 , 150 , 150 , 149 , \
                                 149 , 148 , 148 , 147 , 146 , 146 , 145 , 145 , 144 , 144 , 143 , 142 , 142 , 141 , \
                                 141 , 140 , 140 , 139 , 139 , 138 , 138 , 137 , 136 , 136 , 135 , 135 , 134 , 134 , \
                                 133 , 133 , 132 , 132 , 131 , 131 , 130 , 130 , 129 , 129 , 128 , 128 , 127 , 127 , \
                                 126 , 126 , 125 , 125 , 124 , 124 , 123 , 123 , 122 , 122 , 121 , 121 , 120 , 120 , \
                                 120 , 119 , 119 , 118 , 118 , 117 , 117 , 116 , 116 , 115 , 115 , 114 , 114 , 114 , \
                                 113 , 113 , 112 , 112 , 111 , 111 , 111 , 110 , 110 , 109 , 109 , 108 , 108 , 108 , \
                                 107 , 107 , 106 , 106 , 105 , 105 , 105 , 104 , 104 , 103 , 103 , 103 , 102 , 102 , \
                                 101 , 101 , 101 , 100 , 100 , 99  , 99  , 99  , 98  , 98  , 98  , 97  , 97  , 96  , \
                                 96  , 96  , 95  , 95  , 95  };
    
    
    register uint32_t ys_2=0, xs_2=0, ys_sig_y=0, xs_sig_x=0;
    for( var ys=0,ye=dst->h-1; ys<=ye; ys++,ye--,  pIter2+=dst->w,pIter1+=dst->w,pIter3-=dst->w,pIter4-=dst->w){
        for( var xs=0,xe=dst->w-1; xs<=xe; xs++,xe--,  pIter1--,pIter4--,pIter2++,pIter3++ ){
           
            /*=======================================================================================================
             * 假设 miu == sig == dst/2 的情况下
             * expf函数参数可以化简为
             *
             *      x*(x-2*sig_x)         y*(y-2*sig_y)
             * ( ------------------- + ------------------- + 2 ) * (-0.5)
             *       sig_x*sig_x           sig_y*sig_y
             *
             *         x*(0.5*x-sig_x)         y*(0.5*y-sig_y)
             *  - ( -------------------- + ---------------------- + 1 )
             *           sig_x*sig_x           sig_y*sig_y
             *
             *
             * 由于 x 和 y 的范围限定在 [0~2*sig_x] 和 [0~2*sig_y]之间, 因此上述式子值介于 [-1,0]之间
             * 那么将上式乘以256
             *
             *         x*(128*x-256*sig_x)          y*(128*y-256*sig_y)
             *  - ( ------------------------- + -------------------------- + 256 ) 值介于[-256,0]
             *             sig_x*sig_x                  sig_y*sig_y
             *
             *
             =======================================================================================================*/
            int16_t del1 = ( ( (signed)(xs_2<<7) - (signed)(xs_sig_x<<8) )/(sig_x*sig_x) + ( (signed)(ys_2<<7) - (signed)(ys_sig_y<<8) )/(sig_y*sig_y) + 256 );
            //  RH_ASSERT(del1<=256);
            pIter2->R = pIter1->R = pIter3->R = pIter4->R = colorA.R+  (exps[del1]*(colorB.R-colorA.R)>>8);
            pIter2->G = pIter1->G = pIter3->G = pIter4->G = colorA.G+  (exps[del1]*(colorB.G-colorA.G)>>8);
            pIter2->B = pIter1->B = pIter3->B = pIter4->B = colorA.B+  (exps[del1]*(colorB.B-colorA.B)>>8);
            
            xs_2     += (xs<<1)+1;
            xs_sig_x += sig_x;
        }
        pIter1+=(dst->w>>1)+(dst->w&0x01);
        pIter2-=(dst->w>>1)+(dst->w&0x01);
        pIter3-=(dst->w>>1)+(dst->w&0x01);
        pIter4+=(dst->w>>1)+(dst->w&0x01);
        
        ys_2     += (ys<<1)+1;
        ys_sig_y += sig_y;
        
        xs_2      = 0;
        xs_sig_x  = 0;
    }
    
#endif

    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_gradient_v )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    RH_ASSERT( dst      );
    RH_ASSERT( dst->ptr );
    RH_ASSERT( dst->h   );
    RH_ASSERT( dst->w   );
    
    const BLK_TYPE(Pixel888) *colors_copy = NULL;
    {
        if(size<2){
            BLK_TYPE(Pixel888) *pTmp = alloca( 2*sizeof(BLK_TYPE(Pixel888)) );
            RH_ASSERT(pTmp);
            
            colors_copy = pTmp;

            for( size_t i=0; i<2; i++, pTmp++ ){
                if(i<size){
                    *pTmp = *(colors+i);
                }else{
                    *pTmp = M_COLOR_WHITE;
                }
            }
        }else{
            colors_copy = colors;
        }
    }
    
    BLK_UION(Pixel888) OP   = {.data = colors_copy[0]};
    BLK_UION(Pixel888) OA   = {.data = colors_copy[0]};
    BLK_UION(Pixel888) OB   = {.data = colors_copy[1]};
    
    uint32_t map_R = OA.R*dst->h;
    uint32_t map_G = OA.G*dst->h;
    uint32_t map_B = OA.B*dst->h;
    
    BLK_UION(Pixel888) *pIter = dst->ptr;
    for( var y=0; y<dst->h; y++, pIter+=dst->w){
        
#if 0
        OP.R  =  OA.R + y * (OB.R-OA.R) / dst->h;
        OP.G  =  OA.G + y * (OB.G-OA.G) / dst->h;
        OP.B  =  OA.B + y * (OB.B-OA.B) / dst->h;
#elif 1
        map_R += OB.R-OA.R;
        map_G += OB.G-OA.G;
        map_B += OB.B-OA.B;
        
        OP.R  =  map_R/dst->h;
        OP.G  =  map_G/dst->h;
        OP.B  =  map_B/dst->h;
        
#endif

        BLK_FUNC( Memory, setDWord )( pIter, OP.data, dst->w );
    }
    
    return dst;
}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_gradient_h )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    RH_ASSERT( dst      );
    RH_ASSERT( dst->ptr );
    RH_ASSERT( dst->h   );
    RH_ASSERT( dst->w   );
    
    const BLK_TYPE(Pixel888) *colors_copy = NULL;
    {
        if(size<2){
            BLK_TYPE(Pixel888) *pTmp = alloca( 2*sizeof(BLK_TYPE(Pixel888)) );
            RH_ASSERT(pTmp);
            
            colors_copy = pTmp;

            for( size_t i=0; i<2; i++, pTmp++ ){
                if(i<size){
                    *pTmp = *(colors+i);
                }else{
                    *pTmp = M_COLOR_WHITE;
                }
            }
        }else{
            colors_copy = colors;
        }
    }
    
    BLK_UION(Pixel888) OP   = {.data = colors_copy[0]};
    BLK_UION(Pixel888) OA   = {.data = colors_copy[0]};
    BLK_UION(Pixel888) OB   = {.data = colors_copy[1]};
    
    uint32_t map_R = OA.R*dst->w;
    uint32_t map_G = OA.G*dst->w;
    uint32_t map_B = OA.B*dst->w;
    
    BLK_UION(Pixel888) *pIter = dst->ptr;
    for( var x=0; x<dst->w; x++, pIter++){
        
#if 0
        OP.R  =  OA.R + x * (OB.R-OA.R) / dst->w;
        OP.G  =  OA.G + x * (OB.G-OA.G) / dst->w;
        OP.B  =  OA.B + x * (OB.B-OA.B) / dst->w;
#elif 1
        map_R += OB.R-OA.R;
        map_G += OB.G-OA.G;
        map_B += OB.B-OA.B;
        
        OP.R  =  map_R/dst->w;
        OP.G  =  map_G/dst->w;
        OP.B  =  map_B/dst->w;
        
        pIter->data = OP.data;
#endif
    }
    
    for( var y=1; y<dst->h; y++, pIter+=dst->w){
        memcpy( pIter, dst->ptr, dst->w*sizeof( BLK_TYPE(Pixel888) ));
    }
    
    return dst;
}

BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_center1 )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    var miu_x = dst->w>>1;
    var miu_y = dst->h>>1;
    
    var sig_x = dst->w/6;
    var sig_y = dst->w/6;
    
    BLK_UION(Pixel888)* pIter = dst->ptr;
    for( var y=0; y<dst->h; y++){
        for( var x=0; x < dst->w; x++, pIter++){
            float del = expf(-0.5*( ((x-miu_x)*(x-miu_x))/(sig_x*sig_x) + ((y-miu_y)*(y-miu_y))/(sig_y*sig_y) ));
            
            BLK_GRAPH_ASSERT(del <= 1.0);
            pIter->R = (uint8_t)lroundf(0xff*del);
            pIter->G = (uint8_t)lroundf(0xff*del);
            pIter->B = (uint8_t)lroundf(0xff*del);
            
        }
    }

    return dst;
}
    
BLK_SRCT(Img888)* BLK_FUNC( Img888, spy_img_blur     )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size, const __Area_t* pArea ){
    
    RH_ASSERT(dst);
//    RH_ASSERT(dst->ptr);
    
    if( pArea->xs >= dst->w || pArea->ys >= dst->h )
        return dst;
    
    var sig_x = dst->w>>1;
    var sig_y = dst->h>>1;
    
    const BLK_UION(Pixel888) colorB = {.data=colors[0]};
    const BLK_UION(Pixel888) colorA = {.data=colors[1]};
    
    __Area_t area = *pArea;
    if( pArea->xs+pArea->w > dst->w )
        area.w = dst->w-pArea->xs;
    if( pArea->ys+pArea->h > dst->h )
        area.h = dst->h-pArea->ys;
    
    var xs,xe,ys,ye;
    if( area.xs > ((dst->w-area.w)>>1) ){
        xe = area.xs+area.w-1;
        xs = dst->w-area.xs-area.w+1;
    }else{
        xs = area.xs;
        xe = dst->w-area.xs-1;
    }
    if( area.ys > ((dst->h-area.h)>>1) ){
        ye = area.ys+area.h-1;
        ys = dst->h-area.ys-area.h+1;
    }else{
        ys = area.ys;
        ye = dst->h-area.ys-1;
    }
//    printf("%d\n",xs);
    
    const uint8_t exps[257] = {  255 , 255 , 255 , 254 , 253 , 252 , 251 , 250 , 249 , 248 , 247 , 246 , 245 , 244 , \
                                 243 , 242 , 241 , 240 , 240 , 239 , 238 , 237 , 236 , 235 , 234 , 233 , 232 , 231 , \
                                 230 , 229 , 229 , 228 , 227 , 226 , 225 , 224 , 223 , 222 , 222 , 221 , 220 , 219 , \
                                 218 , 217 , 216 , 216 , 215 , 214 , 213 , 212 , 211 , 211 , 210 , 209 , 208 , 207 , \
                                 207 , 206 , 205 , 204 , 203 , 203 , 202 , 201 , 200 , 199 , 199 , 198 , 197 , 196 , \
                                 196 , 195 , 194 , 193 , 192 , 192 , 191 , 190 , 190 , 189 , 188 , 187 , 187 , 186 , \
                                 185 , 184 , 184 , 183 , 182 , 182 , 181 , 180 , 179 , 179 , 178 , 177 , 177 , 176 , \
                                 175 , 175 , 174 , 173 , 173 , 172 , 171 , 171 , 170 , 169 , 169 , 168 , 167 , 167 , \
                                 166 , 165 , 165 , 164 , 163 , 163 , 162 , 161 , 161 , 160 , 160 , 159 , 158 , 158 , \
                                 157 , 156 , 156 , 155 , 155 , 154 , 153 , 153 , 152 , 152 , 151 , 150 , 150 , 149 , \
                                 149 , 148 , 148 , 147 , 146 , 146 , 145 , 145 , 144 , 144 , 143 , 142 , 142 , 141 , \
                                 141 , 140 , 140 , 139 , 139 , 138 , 138 , 137 , 136 , 136 , 135 , 135 , 134 , 134 , \
                                 133 , 133 , 132 , 132 , 131 , 131 , 130 , 130 , 129 , 129 , 128 , 128 , 127 , 127 , \
                                 126 , 126 , 125 , 125 , 124 , 124 , 123 , 123 , 122 , 122 , 121 , 121 , 120 , 120 , \
                                 120 , 119 , 119 , 118 , 118 , 117 , 117 , 116 , 116 , 115 , 115 , 114 , 114 , 114 , \
                                 113 , 113 , 112 , 112 , 111 , 111 , 111 , 110 , 110 , 109 , 109 , 108 , 108 , 108 , \
                                 107 , 107 , 106 , 106 , 105 , 105 , 105 , 104 , 104 , 103 , 103 , 103 , 102 , 102 , \
                                 101 , 101 , 101 , 100 , 100 , 99  , 99  , 99  , 98  , 98  , 98  , 97  , 97  , 96  , \
                                 96  , 96  , 95  , 95  , 95  };
    BLK_UION(Pixel888)* pIter2 = dst->ptr+ys*dst->w+xs;
    for( var y=ys; y<=ye; y++ ){
        for( var x=xs; x<=xe; x++,pIter2++ ){
            if( x>=area.xs && x<=area.xs+area.w-1 && y>=area.ys && y<=area.ys+area.h-1 ){
                // pIter2
                int16_t del1 = ( x*((x<<7) - (sig_x<<8))/(sig_x*sig_x) + y*((y<<7) - (sig_y<<8))/(sig_y*sig_y) + 256 );
                RH_ASSERT(del1<=256);
                pIter2->R = colorA.R+  (exps[del1]*(colorB.R-colorA.R)>>8);
                pIter2->G = colorA.G+  (exps[del1]*(colorB.G-colorA.G)>>8);
                pIter2->B = colorA.B+  (exps[del1]*(colorB.B-colorA.B)>>8);
            }
        }
        pIter2 -= xe-xs+1;
        pIter2 += dst->w;
    }
    return dst;
}
    
#ifdef __cplusplus
}
#endif

