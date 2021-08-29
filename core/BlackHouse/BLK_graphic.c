#include "BLK_graphic.h"

#ifdef __cplusplus
extern "C" {
#endif
    

struct __GraphConfig_t{
    BLK_UION(Pixel888) penColorRaw;
    uint32_t           penColor;
    uint8_t            penOpaque;
    size_t             penSize;
    
    unsigned int       blur_br_100;
    unsigned int       blur_size;
    BLK_TYPE(Canvas)   blur_tmp;
    __Area_t           blur_area;

    F_Render           callbacks[NUM_kBLK_RenderMethod];
    BLK_ENUM(RenderMethod) method;
    BLK_ENUM(ColorDepth)   depth;
    
};
    
static struct __GraphConfig_t GCFG = {
    .penColor    = M_COLOR_WHITE ,
    .penSize     = 3             ,
    .blur_size   = 44100         ,
    .blur_br_100 = 70            ,
};
    
    
/*===========================================
 > 颜色渲染函数 --- 即着色器
============================================*/
    static void __render_1bit_mark     (int x, int y, void* pIMG){
        BLK_SRCT(ImgBin)* pInfo = pIMG;
    #ifdef RH_DEBUG
        BLK_GRAPH_ASSERT(pInfo);
        BLK_GRAPH_ASSERT(pInfo->ptr);
    #endif
        __exit( x>=pInfo->w || y>=pInfo->h || x<0 || y<0);
        (pInfo->ptr+((y>>3)*pInfo->w)+x)->data = __BIT_CLR( (pInfo->ptr+((y>>3)*pInfo->w)+x)->data , y%8 );
    }
    static void __render_1bit_unmark   (int x, int y, void* pIMG){
        BLK_SRCT(ImgBin)* pInfo = pIMG;
    #ifdef RH_DEBUG
       BLK_GRAPH_ASSERT(pInfo);
       BLK_GRAPH_ASSERT(pInfo->ptr);
    #endif
       __exit( x>=pInfo->w || y>=pInfo->h || x<0 || y<0);
       (pInfo->ptr+((y>>3)*pInfo->w)+x)->data = __BIT_SET( (pInfo->ptr+((y>>3)*pInfo->w)+x)->data , y%8 );
    }
    static void __render_1bit_fill     (int x, int y, void* pIMG){
        BLK_SRCT(ImgBin)* pInfo = pIMG;
    #ifdef RH_DEBUG
        BLK_GRAPH_ASSERT(pInfo);
        BLK_GRAPH_ASSERT(pInfo->ptr);
    #endif
        __exit( x>=pInfo->w || y>=pInfo->h || x<0 || y<0 );
        size_t index = (y>>3)*pInfo->w+x;
        BLK_TYPE(PixelBin) data = pInfo->ptr[ index ].data;
        pInfo->ptr[ index ].data = (GCFG.penColor==0)?(__BIT_CLR( data , y%8 )):(__BIT_SET( data , y%8 ));
    }
    static void __render_1bit_light    (int x, int y, void* pIMG){
        
    }
    static void __render_1bit_depix    (int x, int y, void* pIMG){
        
    }//
    static void __render_1bit_reverse  (int x, int y, void* pIMG){
        
    }//
    static void __render_1bit_blur     (int x, int y, void* pIMG){
        
    }//
    static void __render_1bit_eor      (int x, int y, void* pIMG){
        
    }//
    
    static void __render_8bit_mark     (int x, int y, void* pIMG){
        
    }//
    static void __render_8bit_unmark   (int x, int y, void* pIMG){
        
    }//
    static void __render_8bit_fill     (int x, int y, void* pIMG){
        
    }//
    static void __render_8bit_light    (int x, int y, void* pIMG){
        
    }//
    static void __render_8bit_depix    (int x, int y, void* pIMG){
        
    }//
    static void __render_8bit_reverse  (int x, int y, void* pIMG){
        
    }//
    static void __render_8bit_blur     (int x, int y, void* pIMG){
        
    }//
    static void __render_8bit_eor      (int x, int y, void* pIMG){
        
    }//
    
    static void __render_16bit_mark    (int x, int y, void* pIMG){
        
    }//
    static void __render_16bit_unmark  (int x, int y, void* pIMG){
        
    }//
    static void __render_16bit_fill    (int x, int y, void* pIMG){
        BLK_SRCT(Img565)* pInfo = pIMG;
    #ifdef RH_DEBUG
        BLK_GRAPH_ASSERT(pInfo);
        BLK_GRAPH_ASSERT(pInfo->ptr);
    #endif
        __exit( x>=pInfo->w || y>=pInfo->h || x<0 || y<0 );
        pInfo->ptr[y*pInfo->w+x].data = (BLK_TYPE(Pixel565))GCFG.penColor;
    }
    static void __render_16bit_light   (int x, int y, void* pIMG){
        BLK_SRCT(Img565)* pInfo = pIMG;
    #ifdef RH_DEBUG
        BLK_GRAPH_ASSERT(pInfo);
        BLK_GRAPH_ASSERT(pInfo->ptr);
    #endif
        BLK_TYPE(Pixel565)* p = (BLK_TYPE(Pixel565)*)(pInfo->ptr);
        BLK_UION(Pixel565) temp = {
            .data = *(p+y*pInfo->w+x)
        };
        temp.R = RH_LIMIT((signed)(temp.R*110/100) , 0 , ((1<<5)-1));
        temp.G = RH_LIMIT((signed)(temp.G*110/100) , 0 , ((1<<6)-1));
        temp.B = RH_LIMIT((signed)(temp.B*110/100) , 0 , ((1<<5)-1));
        *(p+y*pInfo->w+x) = temp.data;
    }
    static void __render_16bit_depix   (int x, int y, void* pIMG){
        
    }//
    static void __render_16bit_reverse (int x, int y, void* pIMG){
        
    }//
    static void __render_16bit_blur    (int x, int y, void* pIMG){
        
    }//
    static void __render_16bit_eor     (int x, int y, void* pIMG){
        
    }//
    
    static void __render_24bit_mark    (int x, int y, void* pIMG){
        
    }//
    static void __render_24bit_unmark  (int x, int y, void* pIMG){
        
    }//
    static void __render_24bit_fill    (int x, int y, void* pIMG){
        BLK_SRCT(Img888)* pInfo = pIMG;
    #ifdef RH_DEBUG
        BLK_GRAPH_ASSERT(pInfo);
        BLK_GRAPH_ASSERT(pInfo->ptr);
    #endif
        __exit( x>=pInfo->w || y>=pInfo->h || x<0 || y<0 );
        if( GCFG.penOpaque==0xff )
            pInfo->ptr[y*pInfo->w+x].data = (BLK_TYPE(Pixel888))GCFG.penColor;
        else{
            BLK_UION(Pixel888) color = {.data = GCFG.penColor};
            pInfo->ptr[y*pInfo->w+x].R = pInfo->ptr[y*pInfo->w+x].R + ( (signed)( ( color.R-pInfo->ptr[y*pInfo->w+x].R )*GCFG.penOpaque )>>8 );
            pInfo->ptr[y*pInfo->w+x].G = pInfo->ptr[y*pInfo->w+x].G + ( (signed)( ( color.G-pInfo->ptr[y*pInfo->w+x].G )*GCFG.penOpaque )>>8 );
            pInfo->ptr[y*pInfo->w+x].B = pInfo->ptr[y*pInfo->w+x].B + ( (signed)( ( color.B-pInfo->ptr[y*pInfo->w+x].B )*GCFG.penOpaque )>>8 );
        }

    }
    static void __render_24bit_light   (int x, int y, void* pIMG){
        BLK_SRCT(Img888)* pInfo = pIMG;
    #ifdef RH_DEBUG
        BLK_GRAPH_ASSERT(pInfo);
        BLK_GRAPH_ASSERT(pInfo->ptr);
    #endif
        BLK_TYPE(Pixel888)* p = (BLK_TYPE(Pixel888)*)(pInfo->ptr);
        BLK_UION(Pixel888) temp = {
            .data = *(p+y*pInfo->w+x)
        };
        temp.R = RH_LIMIT((signed)(temp.R*110/100) , 0 , ((1<<8)-1));
        temp.G = RH_LIMIT((signed)(temp.G*110/100) , 0 , ((1<<8)-1));
        temp.B = RH_LIMIT((signed)(temp.B*110/100) , 0 , ((1<<8)-1));
        *(p+y*pInfo->w+x) = temp.data;
    }
    static void __render_24bit_depix   (int x, int y, void* pIMG){
        
    }//
    static void __render_24bit_reverse (int x, int y, void* pIMG){
        
    }//
    static void __render_24bit_blur    (int x, int y, void* pIMG){
        
    }//
    static void __render_24bit_eor     (int x, int y, void* pIMG){
        
    }//
    
static struct __GraphConfig_t GCFG_copy = {0};
    


     
E_Status_t      BLK_FUNC( Graph, init          )  (void){
    GCFG.blur_br_100  = 100;
    GCFG.blur_size    = 44100;
    GCFG.penSize      = 3;
    GCFG.penOpaque    = 255;
    
    GCFG.blur_tmp.ptr = NULL;
    GCFG.blur_tmp.h   = 0;
    GCFG.blur_tmp.w   = 0;
    
    BLK_FUNC(Graph,set_color_depth)   ( kBLK_ColorDepth_24Bit  );
    BLK_FUNC(Graph,set_penColor)      ( M_COLOR_WHITE          );
    BLK_FUNC(Graph,set_render_method) ( kBLK_RenderMethod_fill );
    
    return MAKE_ENUM( kStatus_Success );
}

void            BLK_FUNC( Graph, set_penOpaque )  (uint8_t        opaque){
    GCFG.penOpaque = opaque;
}
 
void            BLK_FUNC( Graph, set_penSize   )  (size_t         penSize      ){
    if(penSize >0xff){
        penSize = 0xff;
    }
    GCFG.penSize = penSize;
}
void            BLK_FUNC( Graph, set_penColor  )  (uint32_t penColor    ){

    GCFG.penColorRaw.data = penColor;

    switch( GCFG.depth ){
        case kBLK_ColorDepth_1Bit :
            GCFG.penColor = MAKE_COLOR_1BIT( ((penColor>>16)&0xff), ((penColor>>8)&0xff), (penColor&0xff) );
            break;
        case kBLK_ColorDepth_8Bit :
            BLK_GRAPH_ASSERT(0);
            break;
        case kBLK_ColorDepth_16Bit:
            GCFG.penColor = MAKE_COLOR_16BIT( ((penColor>>16)&0xff), ((penColor>>8)&0xff), (penColor&0xff) );
            break;
        case kBLK_ColorDepth_24Bit:
            GCFG.penColor = penColor&0x00ffffff;
            break;
        case kBLK_ColorDepth_32Bit:
            BLK_GRAPH_ASSERT(0);
            break;
        default: // Impossible
            BLK_GRAPH_ASSERT(0);
    }
    
}
void            BLK_FUNC( Graph, set_blurColor )  (size_t         size_0_65535 ){
    GCFG.blur_size = RH_LIMIT((unsigned int)(size_0_65535), 0U, 65535U);
}
void            BLK_FUNC( Graph, set_blurBr    )  (size_t         br_100       ){
    GCFG.blur_br_100 = RH_LIMIT((unsigned int)(br_100), 0, 200);
}

void            BLK_FUNC( Graph, set_color_depth   ) (BLK_ENUM(ColorDepth)   depth  ){
    
    GCFG.depth = depth;
    switch( depth ){
        case kBLK_ColorDepth_1Bit:
            GCFG.callbacks[kBLK_RenderMethod_mark   ] = __render_1bit_mark    ;
            GCFG.callbacks[kBLK_RenderMethod_unmark ] = __render_1bit_unmark  ;
            GCFG.callbacks[kBLK_RenderMethod_fill   ] = __render_1bit_fill    ;
            GCFG.callbacks[kBLK_RenderMethod_light  ] = __render_1bit_light   ;
            GCFG.callbacks[kBLK_RenderMethod_depix  ] = __render_1bit_depix   ;
            GCFG.callbacks[kBLK_RenderMethod_reverse] = __render_1bit_reverse ;
            GCFG.callbacks[kBLK_RenderMethod_blur   ] = __render_1bit_blur    ;
            GCFG.callbacks[kBLK_RenderMethod_eor    ] = __render_1bit_eor     ;
            GCFG.penColor = MAKE_COLOR_1BIT(GCFG.penColorRaw.R, GCFG.penColorRaw.G, GCFG.penColorRaw.B);
            break;
        case kBLK_ColorDepth_8Bit:
            GCFG.callbacks[kBLK_RenderMethod_mark   ] = __render_8bit_mark    ;
            GCFG.callbacks[kBLK_RenderMethod_unmark ] = __render_8bit_unmark  ;
            GCFG.callbacks[kBLK_RenderMethod_fill   ] = __render_8bit_fill    ;
            GCFG.callbacks[kBLK_RenderMethod_light  ] = __render_8bit_light   ;
            GCFG.callbacks[kBLK_RenderMethod_depix  ] = __render_8bit_depix   ;
            GCFG.callbacks[kBLK_RenderMethod_reverse] = __render_8bit_reverse ;
            GCFG.callbacks[kBLK_RenderMethod_blur   ] = __render_8bit_blur    ;
            GCFG.callbacks[kBLK_RenderMethod_eor    ] = __render_8bit_eor     ;
            BLK_GRAPH_ASSERT(0);
            break;
        case kBLK_ColorDepth_16Bit:
            GCFG.callbacks[kBLK_RenderMethod_mark   ] = __render_16bit_mark    ;
            GCFG.callbacks[kBLK_RenderMethod_unmark ] = __render_16bit_unmark  ;
            GCFG.callbacks[kBLK_RenderMethod_fill   ] = __render_16bit_fill    ;
            GCFG.callbacks[kBLK_RenderMethod_light  ] = __render_16bit_light   ;
            GCFG.callbacks[kBLK_RenderMethod_depix  ] = __render_16bit_depix   ;
            GCFG.callbacks[kBLK_RenderMethod_reverse] = __render_16bit_reverse ;
            GCFG.callbacks[kBLK_RenderMethod_blur   ] = __render_16bit_blur    ;
            GCFG.callbacks[kBLK_RenderMethod_eor    ] = __render_16bit_eor     ;
            GCFG.penColor = MAKE_COLOR_16BIT(GCFG.penColorRaw.R, GCFG.penColorRaw.G, GCFG.penColorRaw.B);
            break;
        case kBLK_ColorDepth_24Bit:
            GCFG.callbacks[kBLK_RenderMethod_mark   ] = __render_24bit_mark    ;
            GCFG.callbacks[kBLK_RenderMethod_unmark ] = __render_24bit_unmark  ;
            GCFG.callbacks[kBLK_RenderMethod_fill   ] = __render_24bit_fill    ;
            GCFG.callbacks[kBLK_RenderMethod_light  ] = __render_24bit_light   ;
            GCFG.callbacks[kBLK_RenderMethod_depix  ] = __render_24bit_depix   ;
            GCFG.callbacks[kBLK_RenderMethod_reverse] = __render_24bit_reverse ;
            GCFG.callbacks[kBLK_RenderMethod_blur   ] = __render_24bit_blur    ;
            GCFG.callbacks[kBLK_RenderMethod_eor    ] = __render_24bit_eor     ;
            GCFG.penColor = MAKE_COLOR_24BIT(GCFG.penColorRaw.R, GCFG.penColorRaw.G, GCFG.penColorRaw.B);
            break;
        case kBLK_ColorDepth_32Bit:
            break;
        default: // Impossible
            RH_ASSERT(0);
    }
}
void            BLK_FUNC( Graph, set_render_method ) (BLK_ENUM(RenderMethod) method ){
    RH_ASSERT( method < NUM_kBLK_RenderMethod );
    GCFG.method = method;
}

BLK_TYPE(Pixel) BLK_FUNC( Graph, get_penColor ) (void){
    return GCFG.penColor;
}
size_t          BLK_FUNC( Graph, get_penSize  ) (void){
    return GCFG.penSize;
}
size_t          BLK_FUNC( Graph, get_blurSize ) (void){
    return GCFG.blur_size;
}
size_t          BLK_FUNC( Graph, get_blurBr   ) (void){
    return GCFG.blur_br_100;
}

static bool backupGCFG = false;
void            BLK_FUNC( Graph, backupCache  ) (void){
    memcpy(&GCFG_copy, &GCFG, sizeof(struct __GraphConfig_t));
    memcpy(GCFG_copy.callbacks, GCFG.callbacks, NUM_kBLK_RenderMethod);
    backupGCFG = true;
}
void            BLK_FUNC( Graph, restoreCache ) (void){
    if( backupGCFG ){
        memcpy(&GCFG, &GCFG_copy, sizeof(struct __GraphConfig_t));
        memcpy(GCFG.callbacks, GCFG_copy.callbacks, NUM_kBLK_RenderMethod);
        backupGCFG = false;
    }
}


    
/*===========================================
 > 插入一个空心圆,线宽为1
============================================*/
E_Status_t      BLK_FUNC( Graph , circle_raw        ) (int x ,int y ,int d ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int r    = d>>1;
    int p    = 3-2*r;
    bool eps = (d%2==0);
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }

    for(int x_tmp=0,y_tmp = r;x_tmp<=y_tmp;x_tmp++){
        callback(x     + x_tmp ,y     + y_tmp ,pIMG );
        callback(x+eps - x_tmp ,y     + y_tmp ,pIMG );
        callback(x     + x_tmp ,y+eps - y_tmp ,pIMG );
        callback(x+eps - x_tmp ,y+eps - y_tmp ,pIMG );
        callback(x     + y_tmp ,y     + x_tmp ,pIMG );
        callback(x+eps - y_tmp ,y     + x_tmp ,pIMG );
        callback(x     + y_tmp ,y+eps - x_tmp ,pIMG );
        callback(x+eps - y_tmp ,y+eps - x_tmp ,pIMG );

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入一个空心圆,线宽随设定
=====================================*/
E_Status_t      BLK_FUNC( Graph , circle_edged      ) (int x ,int y ,int d ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int r = d>>1;
    int r_ex  = r;
    int r_in  = (int)(r-GCFG.penSize);
    
    int x_ex_tmp = 0;
    int y_ex_tmp = r_ex;
    int x_in_tmp = 0;
    int y_in_tmp = r_in;
    int p_ex  = 3-2*r_ex;
    int p_in  = 3-2*r_in;
    
    bool eps  = (d%2==0);
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_ex_tmp<y_ex_tmp;x_ex_tmp++,x_in_tmp++){
        for(int Y = y_in_tmp;Y<y_ex_tmp;Y++){
            callback(x     + x_ex_tmp ,y     + Y        ,pIMG );
            callback(x+eps - x_ex_tmp ,y     + Y        ,pIMG );
            callback(x     + x_ex_tmp ,y+eps - Y        ,pIMG );
            callback(x+eps - x_ex_tmp ,y+eps - Y        ,pIMG );
            callback(x     + Y        ,y     + x_ex_tmp ,pIMG );
            callback(x+eps - Y        ,y     + x_ex_tmp ,pIMG );
            callback(x     + Y        ,y+eps - x_ex_tmp ,pIMG );
            callback(x+eps - Y        ,y+eps - x_ex_tmp ,pIMG );
        }

        if(p_ex <= 0){
            p_ex += (x_ex_tmp<<2) + 6;
        }else{
            p_ex += ((x_ex_tmp-y_ex_tmp)<<2) + 10;
            y_ex_tmp--;
        }
        if(p_in <= 0){
            p_in += (x_in_tmp<<2) + 6;
        }else{
            p_in += ((x_in_tmp-y_in_tmp)<<2) + 10;
            y_in_tmp--;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入一个填充圆
=====================================*/
E_Status_t      BLK_FUNC( Graph , circle_fill       ) (int x ,int y ,int d ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int r = d>>1;
    int p = 3-(r<<1);
    int x_tmp = 0,y_tmp = r;
    bool eps  = (d%2==0);
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            callback(x     + x_tmp ,y     + cnt,pIMG );
            callback(x+eps - x_tmp ,y     + cnt,pIMG );
            callback(x     + x_tmp ,y+eps - cnt,pIMG );
            callback(x+eps - x_tmp ,y+eps - cnt,pIMG );
        }

        cnt = x_tmp+1;
        while(cnt--){
            callback(x     + y_tmp ,y     + cnt,pIMG );
            callback(x+eps - y_tmp ,y     + cnt,pIMG );
            callback(x     + y_tmp ,y+eps - cnt,pIMG );
            callback(x+eps - y_tmp ,y+eps - cnt,pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入一个1/4圆
=====================================*/
E_Status_t      BLK_FUNC( Graph , circle_qrt1_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        callback(x+x_tmp,y-y_tmp,pIMG );
        callback(x+y_tmp,y-x_tmp,pIMG );

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}
E_Status_t      BLK_FUNC( Graph , circle_qrt2_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        callback(x-x_tmp,y-y_tmp, pIMG );
        callback(x-y_tmp,y-x_tmp, pIMG );

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }

    return MAKE_ENUM( kStatus_Success );
}
E_Status_t      BLK_FUNC( Graph , circle_qrt3_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        callback(x-x_tmp,y+y_tmp,pIMG );
        callback(x-y_tmp,y+x_tmp,pIMG );

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}
E_Status_t      BLK_FUNC( Graph , circle_qrt4_raw   ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        callback(x+x_tmp,y+y_tmp, pIMG );
        callback(x+y_tmp,y+x_tmp, pIMG );

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}
    
/*====================================
 > 插入一个填充1/4圆
=====================================*/
E_Status_t      BLK_FUNC( Graph , circle_qrt1_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            callback(x+x_tmp,y-cnt,pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }

    const int xy_45 = x_tmp;
    p = 3-((r-1)<<1);
    x_tmp = 0,y_tmp = (r-1);
    for(;x_tmp<=y_tmp;x_tmp++){
        for( int i=x+xy_45; i<=x+y_tmp; i++ ){
            callback(i,y-x_tmp,pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }


    return MAKE_ENUM( kStatus_Success );
}
E_Status_t      BLK_FUNC( Graph , circle_qrt2_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            callback(x-x_tmp,y-cnt,pIMG );
        }
        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }

    /*
    * 
    * Draw this part:
    *
    *              ----|
    *           ---    |
    *         ||       |
    *       ||||       |
    *     ||||||       |
    *    |||||||       |
    *    |||||||       | 
    *   ||||||||       |
    *   ||||||||_______|
    *
    *
    */

    
    const int x_45 = x_tmp;  // <- very important
    x_tmp = 0,y_tmp = (r-1);
    p = 3-((r-1)<<1);

    for(;x_tmp<=y_tmp;x_tmp++){
        for( int i=x-y_tmp; i<=x-x_45; i++ ){
            callback(i,y-x_tmp,pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }

    return MAKE_ENUM( kStatus_Success );
}
E_Status_t      BLK_FUNC( Graph , circle_qrt3_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            callback(x-x_tmp,y+cnt,pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    
    const int xy_45 = x_tmp;
    x_tmp = 0,y_tmp = (r-1);
    p = 3-((r-1)<<1);
    for(;x_tmp<=y_tmp;x_tmp++){
        for( int i=x-y_tmp; i<=x-xy_45; i++ ){
            callback(i,y+x_tmp,pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }

    return MAKE_ENUM( kStatus_Success );
}
E_Status_t      BLK_FUNC( Graph , circle_qrt4_fill  ) (int x ,int y ,int r ,        void* pIMG, F_Render RH_NULLABLE callback ){
    int p = 3-((r-1)<<1);
    int x_tmp = 0,y_tmp = (r-1);

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    for(;x_tmp<=y_tmp;x_tmp++){
        int cnt = y_tmp+1;
        while(cnt--){
            callback(x+x_tmp,y+cnt, pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }

    const int xy_45 = x_tmp;
    p = 3-((r-1)<<1);
    x_tmp = 0,y_tmp = (r-1);
    for(;x_tmp<=y_tmp;x_tmp++){
        for( int i=x+xy_45; i<=x+y_tmp; i++ ){
            callback(i,y+x_tmp, pIMG );
        }

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    return MAKE_ENUM( kStatus_Success );
}
    
/*====================================
 > 插入一个空心长方形,线宽为1
=====================================*/
E_Status_t      BLK_FUNC( Graph , rect_raw          ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback ){
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }

    for(int x=xs;x<=xe;x++){
        callback( x, ys, pIMG );
        callback( x, ye, pIMG );
    }
    for(int y=ys+1;y<ye;y++){
        callback( xs ,y, pIMG );
        callback( xe ,y, pIMG );
    }
    
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入一个实心长方形
=====================================*/
E_Status_t      BLK_FUNC( Graph , rect_fill         ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback ){
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    // 以下某些条件可以被优化
    if       ( callback == __render_1bit_fill  ){
        BLK_SRCT(ImgBin)* pInfo = pIMG;
        int ps = ys>>3;
        int pe = ye>>3;
        for( int p=ps; p<=pe; p++ ){
            switch( ((p==ps)<<1)|(p==pe) ){
                case 0: // p!=ps && p!=pe
                    memset(pInfo->ptr + p*pInfo->w+xs, GCFG.penColor, xe-xs+1);
                    break;
                case 1: // p!=ps && p==pe
                    for( int x=xs; x<= xe; x++ ){
                        if( GCFG.penColor == 0x00 )
                            pInfo->ptr[ p*pInfo->w+x ].data &= ~( (uint8_t)((1<<((ye&7)+1))-1) );
                        else
                            pInfo->ptr[ p*pInfo->w+x ].data |=    (uint8_t)((1<<((ye&7)+1))-1)  ;
                    }
                    break;
                case 2: // p==ps && p!=pe
                    for( int x=xs; x<= xe; x++ ){
                        if( GCFG.penColor == 0x00 )
                            pInfo->ptr[ p*pInfo->w+x ].data &= ~( (uint8_t)(0xff<<(ys&7)) );
                        else
                            pInfo->ptr[ p*pInfo->w+x ].data |=    (uint8_t)(0xff<<(ys&7))  ;
                    }
                    break;
                case 3: // ps == pe
                    for( int x=xs; x<= xe; x++ ){
                        if( GCFG.penColor == 0x00 ){
                            pInfo->ptr[ p*pInfo->w+x ].data &= ~( (uint8_t)( ((1<<((ye&7)+1))-1)&(0xff<<(ys&7))) );
                        }else{
                            pInfo->ptr[ p*pInfo->w+x ].data |=    (uint8_t)( ((1<<((ye&7)+1))-1)&(0xff<<(ys&7)))  ;
                        }
                    }
                    break;
            }
         
        }
    }else if ( callback == __render_8bit_fill  ){
        BLK_SRCT(ImgGry)* pInfo = pIMG;
        for(int x = xs;x <= xe;x++)
            callback(x,ys,pInfo);
        for(int y = ys+1;y <= ye;y++)
            memmove((pInfo->ptr + y  * pInfo->w + xs),\
                    (pInfo->ptr + ys * pInfo->w + xs),\
                    ((xe-xs+1)*sizeof(pInfo->ptr[0]))   );
    }else if ( callback == __render_16bit_fill ){
        BLK_SRCT(Img565)* pInfo = pIMG;
        for(int x = xs;x <= xe;x++)
            callback(x,ys,pInfo);
        for(int y = ys+1;y <= ye;y++)
            memmove((pInfo->ptr + y  * pInfo->w + xs),\
                    (pInfo->ptr + ys * pInfo->w + xs),\
                    ((xe-xs+1)*sizeof(pInfo->ptr[0]))   );
    }else if ( callback == __render_24bit_fill ){
        BLK_SRCT(Img888)* pInfo = pIMG;
        for(int x = xs;x <= xe;x++)
            callback(x,ys,pInfo);
        for(int y = ys+1;y <= ye;y++)
            memmove((pInfo->ptr + y  * pInfo->w + xs),\
                    (pInfo->ptr + ys * pInfo->w + xs),\
                    ((xe-xs+1)*sizeof(pInfo->ptr[0]))   );
    }else{
        for( int y=ys; y<=ye; y++ ){
            for( int x=xs; x<= xe; x++ )
                callback(x,y,pIMG);
        }
    }

    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入一个空心长发形,线宽随设定
=====================================*/
E_Status_t      BLK_FUNC( Graph , rect_edged        ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback ){
    int loop = 0;
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    while(loop < GCFG.penSize){
        int x = xs+loop, y = ys+loop;

        while(x<=(xe-loop) && y<=(ye-loop)){
            if( x < (xe-loop) ){
                callback(x,ys + loop, pIMG );
                callback(x,ye - loop, pIMG );
                x++;
            }
            else{
                callback(xs + loop,y, pIMG );
                callback(xe - loop,y, pIMG );
                y++;
            }
        }
        loop++;
    }
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入圆角长方形
=====================================*/
E_Status_t      BLK_FUNC( Graph , rect_round_fill   ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback ){
    int r = RH_LIMIT((signed)GCFG.penSize, 0, (RH_MIN((xe-xs), (ye-ys)))/2 );
    
    BLK_FUNC( Graph, rect_fill )(xs+r+1, ys    , xe-r-1, ye    , pIMG, callback );
    BLK_FUNC( Graph, rect_fill )(xs    , ys+r+1, xs+r  , ye-r-1, pIMG, callback );
    BLK_FUNC( Graph, rect_fill )(xe-r  , ys+r+1, xe    , ye-r-1, pIMG, callback );

    BLK_FUNC( Graph, circle_qrt1_fill )(xe-r, ys+r, r, pIMG, callback );
    BLK_FUNC( Graph, circle_qrt2_fill )(xs+r, ys+r, r, pIMG, callback );
    BLK_FUNC( Graph, circle_qrt3_fill )(xs+r, ye-r, r, pIMG, callback );
    BLK_FUNC( Graph, circle_qrt4_fill )(xe-r, ye-r, r, pIMG, callback );
    
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入空心圆角长方形
=====================================*/
E_Status_t      BLK_FUNC( Graph , rect_round_raw    ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback ){
    int r = RH_LIMIT((signed)GCFG.penSize, 0, (RH_MIN((xe-xs), (ye-ys)))/2 );
    
    BLK_FUNC( Graph, line_raw )(xs+r+1, ys    , xe-r-1, ys    , pIMG, callback );
    BLK_FUNC( Graph, line_raw )(xs+r+1, ye    , xe-r-1, ye    , pIMG, callback );
    BLK_FUNC( Graph, line_raw )(xs    , ys+r+1, xs    , ye-r-1, pIMG, callback );
    BLK_FUNC( Graph, line_raw )(xe    , ys+r+1, xe    , ye-r-1, pIMG, callback );

    BLK_FUNC( Graph, circle_qrt1_raw )(xe-r, ys+r, r, pIMG, callback );
    BLK_FUNC( Graph, circle_qrt2_raw )(xs+r, ys+r, r, pIMG, callback );
    BLK_FUNC( Graph, circle_qrt3_raw )(xs+r, ye-r, r, pIMG, callback );
    BLK_FUNC( Graph, circle_qrt4_raw )(xe-r, ye-r, r, pIMG, callback );
    
    return MAKE_ENUM( kStatus_Success );
}
    
/*====================================
 > 插入空心长方形(使用__Area_t参数)
=====================================*/
E_Status_t      BLK_FUNC( Graph , EX_rect_raw       ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback ){
    return BLK_FUNC(Graph,rect_raw )( RH_LIMIT( (signed)( area->xs          ), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                      RH_LIMIT( (signed)( area->ys          ), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                      RH_LIMIT( (signed)( area->xs+area->w-1), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                      RH_LIMIT( (signed)( area->ys+area->h-1), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                      pIMG, callback );
}
    
/*====================================
 > 插入实心长方形(使用__Area_t参数)
=====================================*/
E_Status_t      BLK_FUNC( Graph , EX_rect_fill      ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback ){
    return BLK_FUNC(Graph,rect_fill)( RH_LIMIT( (signed)( area->xs          ), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                      RH_LIMIT( (signed)( area->ys          ), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                      RH_LIMIT( (signed)( area->xs+area->w-1), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                      RH_LIMIT( (signed)( area->ys+area->h-1), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                      pIMG, callback );
}
    
/*====================================
 > 插入一个空心长发形,线宽随设定(使用__Area_t参数)
=====================================*/
E_Status_t      BLK_FUNC( Graph , EX_rect_edged     ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback ){
    return BLK_FUNC(Graph,rect_edged)( RH_LIMIT( (signed)( area->xs          ), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                       RH_LIMIT( (signed)( area->ys          ), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                       RH_LIMIT( (signed)( area->xs+area->w-1), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                       RH_LIMIT( (signed)( area->ys+area->h-1), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                       pIMG, callback );
}
    
/*====================================
 > 插入填充圆角长方形(使用__Area_t参数)
=====================================*/
E_Status_t      BLK_FUNC( Graph , EX_rect_round_fill) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback ){
    return BLK_FUNC(Graph,rect_round_fill)( RH_LIMIT( (signed)( area->xs          ), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                            RH_LIMIT( (signed)( area->ys          ), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                            RH_LIMIT( (signed)( area->xs+area->w-1), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                            RH_LIMIT( (signed)( area->ys+area->h-1), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                            pIMG, callback );
}

/*====================================
 > 插入空心圆角长方形(使用__Area_t参数)
=====================================*/
E_Status_t      BLK_FUNC( Graph , EX_rect_round_raw ) (const __Area_t* area,        void* pIMG, F_Render RH_NULLABLE callback ){
    return BLK_FUNC(Graph,rect_round_raw )( RH_LIMIT( (signed)( area->xs          ), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                            RH_LIMIT( (signed)( area->ys          ), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                            RH_LIMIT( (signed)( area->xs+area->w-1), 0, RH_CFG_SCREEN_WIDTH -1 ),\
                                            RH_LIMIT( (signed)( area->ys+area->h-1), 0, RH_CFG_SCREEN_HEIGHT-1 ),\
                                            pIMG, callback );
}
    
/*====================================
 > 插入直线，线宽为1
=====================================*/
E_Status_t      BLK_FUNC( Graph , line_raw          ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback ){
    int x_min = (int)(RH_MIN(x1,x2));
    int x_max = (int)(RH_MAX(x1,x2));
    int y_min = (int)(RH_MIN(y1,y2));
    int y_max = (int)(RH_MAX(y1,y2));
    int delta_x    = (int)( x_max - x_min );
    int delta_y    = (int)( y_max - y_min );
    
    int type = (int)(( ((y2-y1)*(x2-x1)<0) << 1 ) | (delta_y > delta_x));

    if(delta_y > delta_x){
        int temp = delta_x;
        delta_x = delta_y;
        delta_y = temp;
    }
    
    int j = 0;
    int e = 0;
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    callback( x1, y1, pIMG);
    callback( x2, y2, pIMG);
    for(int i = 0;i < delta_x;i++){
        switch(type){
            case 0:callback( x_min+i, y_min+j, pIMG );break;
            case 1:callback( x_min+j, y_min+i, pIMG );break;
            case 2:callback( x_min+i, y_max-j, pIMG );break;
            case 3:callback( x_min+j, y_max-i, pIMG );break;
        }
        e += delta_y;
        if( 2*( e + delta_y ) > delta_x){
            j++;
            e -= delta_x;
        }
    }

    return MAKE_ENUM( kStatus_Success );
}
   
/*====================================
 > 插入直线，线宽随设定
=====================================*/
E_Status_t      BLK_FUNC( Graph , line_edged        ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback ){
    BLK_FUNC( Graph, line_raw )(x1,y1,x2,y2,pIMG,callback);
    
    if( GCFG.penSize > 1 ){
        BLK_ENUM(Monotonicity) dir_line = BLK_FUNC( Math, dir_line )(x1, y1, x2, y2);
        switch(dir_line){
            case kBLK_Monotonicity_hor:
            {
                int xs = RH_MIN(x1, x2);
                int xe = RH_MAX(x1, x2);
                int ys = RH_MIN(y1, y2) - (int)(GCFG.penSize>>1) + (GCFG.penSize%2==0);
                int ye = RH_MAX(y1, y2) + (int)(GCFG.penSize>>1);
                BLK_FUNC( Graph, circle_fill )( x1, y1, (int)GCFG.penSize, pIMG, callback );
                BLK_FUNC( Graph, circle_fill )( x2, y2, (int)GCFG.penSize, pIMG, callback );
                BLK_FUNC( Graph, rect_fill   )( xs, ys, xe, ye, pIMG, callback);
            }
                break;
            case kBLK_Monotonicity_inc:
            case kBLK_Monotonicity_dec:
            {
                int d = (int)(GCFG.penSize);
                int r = d>>1;
                int p = 3-(r<<1);
                int x_tmp = 0,y_tmp = r;
                bool eps  = (d%2==0);

                int    dis_min = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(2*x_tmp-eps) );
                int    dis_tmp = dis_min;
                int    py1 =  y_tmp , px1 = eps-x_tmp , py2 = eps-y_tmp , px2 =  x_tmp;

                for(;x_tmp<=y_tmp;x_tmp++){
 
                    // (x+∂x,y+∂y) & (x-∂x,y-∂y)
                    dis_tmp = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(eps-2*x_tmp) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  y_tmp ; px1 =  x_tmp;
                        py2 = eps-y_tmp ; px2 = eps-x_tmp;
                    }
                    // (x-∂x,y+∂y) & (x+∂x,y-∂y)
                    dis_tmp = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(2*x_tmp-eps) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  y_tmp ; px1 = eps-x_tmp;
                        py2 = eps-y_tmp ; px2 =  x_tmp;
                    }
                    // (x+∂y,y+∂x) & (x-∂y,y-∂x)
                    dis_tmp = __abs( (y2-y1)*(eps-2*x_tmp) + (x2-x1)*(eps-2*y_tmp) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  x_tmp ; px1 =  y_tmp;
                        py2 = eps-x_tmp ; px2 = -y_tmp;
                    }
                    // (x-∂y,y+∂x) & (x+∂y,y-∂x)
                    dis_tmp = __abs( (y2-y1)*(eps-2*x_tmp) + (x2-x1)*(2*y_tmp-eps) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  x_tmp ; px1 = eps-y_tmp;
                        py2 = eps-x_tmp ; px2 =  y_tmp;
                    }

                    if(p <= 0){
                        p += (x_tmp<<2) + 6;
                    }else{
                        p += ((x_tmp-y_tmp)<<2) + 10;
                        y_tmp--;
                    }
                }
                  
                BLK_FUNC( Graph, quad_fill )(x1+px1, y1+py1, x1+px2, y1+py2, x2+px1, y2+py1, x2+px2, y2+py2, pIMG, callback);
                
            }
                break;
            case kBLK_Monotonicity_ver:
            {
                int xs = RH_MIN(x1, x2) - (int)(GCFG.penSize>>1) + (GCFG.penSize%2==0);
                int xe = RH_MAX(x1, x2) + (int)(GCFG.penSize>>1);
                int ys = RH_MIN(y1, y2);
                int ye = RH_MAX(y1, y2);
                BLK_FUNC( Graph, circle_fill )( x1, y1, (int)GCFG.penSize, pIMG, callback );
                BLK_FUNC( Graph, circle_fill )( x2, y2, (int)GCFG.penSize, pIMG, callback );
                BLK_FUNC( Graph, rect_fill   )( xs, ys, xe, ye, pIMG, callback );
            }
                break;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 插入香肠线，线宽随设定
=====================================*/
E_Status_t      BLK_FUNC( Graph , line_sausage      ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback ){
    BLK_FUNC( Graph, line_raw )(x1,y1,x2,y2,pIMG,callback);
    int dir_line = BLK_FUNC( Math, dir_line )(x1, y1, x2, y2);
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    if( GCFG.penSize > 1 ){
        switch(dir_line){
            case kBLK_Monotonicity_hor:
                {
                    int xs = RH_MIN(x1, x2);
                    int xe = RH_MAX(x1, x2);
                    int ys = RH_MIN(y1, y2) - (int)(GCFG.penSize>>1) + (GCFG.penSize%2==0);
                    int ye = RH_MAX(y1, y2) + (int)(GCFG.penSize>>1);
                    BLK_FUNC( Graph, circle_fill )( x1, y1, (int)GCFG.penSize, pIMG, callback );
                    BLK_FUNC( Graph, circle_fill )( x2, y2, (int)GCFG.penSize, pIMG, callback );
                    BLK_FUNC( Graph, rect_fill   )( xs, ys, xe, ye, pIMG, callback);
                }
                break;
            case kBLK_Monotonicity_inc:
            case kBLK_Monotonicity_dec:
            {
                int d = (int)(GCFG.penSize);
                int r = d>>1;
                int p = 3-(r<<1);
                int x_tmp = 0,y_tmp = r;
                bool eps  = (d%2==0);

                int    dis_min = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(2*x_tmp-eps) );
                int    dis_tmp = dis_min;
                int    py1 =  y_tmp , px1 = eps-x_tmp , py2 = eps-y_tmp , px2 =  x_tmp;

                for(;x_tmp<=y_tmp;x_tmp++){
                    int cnt = y_tmp+1;
                    while(cnt--){
                        callback( x1     + x_tmp, y1     + cnt, pIMG );
                        callback( x1+eps - x_tmp, y1     + cnt, pIMG );
                        callback( x1     + x_tmp, y1+eps - cnt, pIMG );
                        callback( x1+eps - x_tmp, y1+eps - cnt, pIMG );

                        callback( x2     + x_tmp, y2     + cnt, pIMG );
                        callback( x2+eps - x_tmp, y2     + cnt, pIMG );
                        callback( x2     + x_tmp, y2+eps - cnt, pIMG );
                        callback( x2+eps - x_tmp, y2+eps - cnt, pIMG );
                    }
                    cnt = x_tmp+1;
                    while(cnt--){
                        callback( x1     + y_tmp, y1     + cnt, pIMG );
                        callback( x1+eps - y_tmp, y1     + cnt, pIMG );
                        callback( x1     + y_tmp, y1+eps - cnt, pIMG );
                        callback( x1+eps - y_tmp, y1+eps - cnt, pIMG );

                        callback( x2     + y_tmp, y2     + cnt, pIMG );
                        callback( x2+eps - y_tmp, y2     + cnt, pIMG );
                        callback( x2     + y_tmp, y2+eps - cnt, pIMG );
                        callback( x2+eps - y_tmp, y2+eps - cnt, pIMG );
                    }
                    // (x+∂x,y+∂y) & (x-∂x,y-∂y)
                    dis_tmp = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(eps-2*x_tmp) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  y_tmp ; px1 =  x_tmp;
                        py2 = eps-y_tmp ; px2 = eps-x_tmp;
                    }
                    // (x-∂x,y+∂y) & (x+∂x,y-∂y)
                    dis_tmp = __abs( (y2-y1)*(eps-2*y_tmp) + (x2-x1)*(2*x_tmp-eps) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  y_tmp ; px1 = eps-x_tmp;
                        py2 = eps-y_tmp ; px2 =  x_tmp;
                    }
                    // (x+∂y,y+∂x) & (x-∂y,y-∂x)
                    dis_tmp = __abs( (y2-y1)*(eps-2*x_tmp) + (x2-x1)*(eps-2*y_tmp) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  x_tmp ; px1 =  y_tmp;
                        py2 = eps-x_tmp ; px2 = -y_tmp;
                    }
                    // (x-∂y,y+∂x) & (x+∂y,y-∂x)
                    dis_tmp = __abs( (y2-y1)*(eps-2*x_tmp) + (x2-x1)*(2*y_tmp-eps) );
                    if( dis_tmp < dis_min ){
                        dis_min = dis_tmp;
                        py1 =  x_tmp ; px1 = eps-y_tmp;
                        py2 = eps-x_tmp ; px2 =  y_tmp;
                    }

                    if(p <= 0){
                        p += (x_tmp<<2) + 6;
                    }else{
                        p += ((x_tmp-y_tmp)<<2) + 10;
                        y_tmp--;
                    }
                }

                BLK_FUNC( Graph, quad_fill )(x1+px1, y1+py1, x1+px2, y1+py2, x2+px1, y2+py1, x2+px2, y2+py2, pIMG, callback);
                
            }
            break;
            case kBLK_Monotonicity_ver:
            {
                int xs = RH_MIN(x1, x2) - (int)(GCFG.penSize>>1) + (GCFG.penSize%2==0);
                int xe = RH_MAX(x1, x2) + (int)(GCFG.penSize>>1);
                int ys = RH_MIN(y1, y2);
                int ye = RH_MAX(y1, y2);
                BLK_FUNC( Graph, circle_fill )( x1, y1, (int)GCFG.penSize, pIMG, callback );
                BLK_FUNC( Graph, circle_fill )( x2, y2, (int)GCFG.penSize, pIMG, callback );
                BLK_FUNC( Graph, rect_fill   )( xs, ys, xe, ye, pIMG, callback );
            }
            break;
        }
    }
    return MAKE_ENUM( kStatus_Success );
}
        
    
/*====================================
 > 插入直线，线宽随设定
=====================================*/
E_Status_t      BLK_FUNC( Graph , line_fill         ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback ){
    return BLK_FUNC( Graph, line_edged  ) (x1,y1,x2,y2,pIMG,callback);
}
    
/*====================================
 > 画任意四边形,线宽为1
=====================================*/
E_Status_t      BLK_FUNC( Graph , quad_raw          ) (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,void* pIMG, F_Render RH_NULLABLE callback ){
    int tmp_y[] = {y1,y2,y3,y4};
    int tmp_x[] = {x1,x2,x3,x4};
    
    int ys;
    BLK_FUNC(Array, min)(tmp_y,4,&ys,NULL);
    
    int xs;
    BLK_FUNC(Array, min)(tmp_x,4,&xs,NULL);
    
    // 分析四边形的边框,任意两点组合去除对角线
    int x11 = x1;
    int y11 = y1;
    int x22,y22,x33,y33,x44,y44;
    
    int tmp_P1P2 = BLK_FUNC( Math, pt_line     )(x1,y1,x2,y2, x3,y3) + BLK_FUNC( Math, pt_line     )(x1,y1,x2,y2, x4,y4);
    int tmp_P1P3 = BLK_FUNC( Math, pt_line     )(x1,y1,x3,y3, x2,y2) + BLK_FUNC( Math, pt_line     )(x1,y1,x3,y3, x4,y4);

    if(tmp_P1P2 == kBLK_PtPos_above + kBLK_PtPos_beneath){
        x22 = x3; y22 = y3;
        x33 = x2; y33 = y2;
        x44 = x4; y44 = y4;
    }else if(tmp_P1P3 == kBLK_PtPos_above + kBLK_PtPos_beneath){
        x22 = x2; y22 = y2;
        x33 = x3; y33 = y3;
        x44 = x4; y44 = y4;
    }else{
        x22 = x2; y22 = y2;
        x33 = x4; y33 = y4;
        x44 = x3; y44 = y3;
    }
    BLK_FUNC( Graph, line_raw )( x11 , y11 , x22 , y22 ,pIMG,callback);        
    BLK_FUNC( Graph, line_raw )( x22 , y22 , x33 , y33 ,pIMG,callback);
    BLK_FUNC( Graph, line_raw )( x33 , y33 , x44 , y44 ,pIMG,callback);        
    BLK_FUNC( Graph, line_raw )( x44 , y44 , x11 , y11 ,pIMG,callback);    
    return MAKE_ENUM( kStatus_Success );
}
    
/*====================================
 > 填充任意四边形
=====================================*/
E_Status_t      BLK_FUNC( Graph , quad_fill         ) (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,void* pIMG, F_Render RH_NULLABLE callback ){
    int tmp_y[] = {y1,y2,y3,y4};
    int tmp_x[] = {x1,x2,x3,x4};
    
    int ys;
    BLK_FUNC(Array, min)(tmp_y,4,&ys,NULL);
    int ye;
    BLK_FUNC(Array, max)(tmp_y,4,&ye,NULL);
    
    
    int xs;
    BLK_FUNC(Array, min)(tmp_x,4,&xs,NULL);
    int xe;
    BLK_FUNC(Array, max)(tmp_x,4,&xe,NULL);
    

    int area_width  = xe  - xs + 1;
    int area_height = ye - ys  + 1;
 // 分析四边形的边框,任意两点组合去除对角线
    int x11 = x1;
    int y11 = y1;
    int x22,y22,x33,y33,x44,y44;
    
    int tmp_P1P2 = BLK_FUNC( Math, pt_line     )(x1,y1,x2,y2, x3,y3) + BLK_FUNC( Math, pt_line     )(x1,y1,x2,y2, x4,y4);
    int tmp_P1P3 = BLK_FUNC( Math, pt_line     )(x1,y1,x3,y3, x2,y2) + BLK_FUNC( Math, pt_line     )(x1,y1,x3,y3, x4,y4);

    if(tmp_P1P2 == kBLK_PtPos_beneath + kBLK_PtPos_above){
        x22 = x3; y22 = y3;
        x33 = x2; y33 = y2;
        x44 = x4; y44 = y4;
    }else if(tmp_P1P3 == kBLK_PtPos_beneath+kBLK_PtPos_above){
        x22 = x2; y22 = y2;
        x33 = x3; y33 = y3;
        x44 = x4; y44 = y4;
    }else{
        x22 = x2; y22 = y2;
        x33 = x4; y33 = y4;
        x44 = x3; y44 = y3;
    }



    // 创建临时空画布，大小取决于上述分析结果
    BLK_UION(PixelBin)* pBuffer = RH_CALLOC((area_height*area_width),sizeof(BLK_UION(PixelBin)));

    // 绘制四边形边框，通过画线程序实现
    BLK_SRCT(ImgBin) pTmpImg = {  .ptr = pBuffer      ,\
                                  .h   = area_height  ,\
                                  .w   = area_width   };

    BLK_FUNC( Graph, line_raw )( x11-xs , y11-ys , x22-xs , y22-ys ,&pTmpImg, __render_1bit_fill );        
    BLK_FUNC( Graph, line_raw )( x22-xs , y22-ys , x33-xs , y33-ys ,&pTmpImg, __render_1bit_fill );
    BLK_FUNC( Graph, line_raw )( x33-xs , y33-ys , x44-xs , y44-ys ,&pTmpImg, __render_1bit_fill );        
    BLK_FUNC( Graph, line_raw )( x44-xs , y44-ys , x11-xs , y11-ys ,&pTmpImg, __render_1bit_fill );

    // 从顶点开始，向下左右画点并搜寻,直到找到边线为止,随后填充
    for(int j = 0;j < area_height;j++){
        int LF = 0,RH = area_width - 1;
        for(;LF < RH;LF++){
            if( 1 == __BIT_GET( pBuffer[ (j>>3)*area_width+LF ].data, j%8) )  break;
        }
        for( ;RH > LF;RH--){
            if( 1 == __BIT_GET( pBuffer[ (j>>3)*area_width+RH ].data, j%8) )  break;
        }
        #ifdef RH_DEBUG
        BLK_GRAPH_ASSERT( LF<=RH );
        #endif
        for( int x=LF; x<=RH; x++ ){
            pBuffer[ (j>>3)*area_width+x ].data = __BIT_SET( pBuffer[ (j>>3)*area_width+x ].data, j%8);
        }
    }
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    // 将画布上的点，存入图像显存，注意偏移量
    for( int j=0; j<area_height; j++){
        for( int i=0; i<area_width; i++){
            if( 0 != __BIT_GET( pBuffer[ area_width*(j>>3)+i ].data, j%8) ){
                callback( i+xs , j+ys , pIMG );
            }
        }
    }

    RH_FREE(pBuffer);

    return MAKE_ENUM( kStatus_Success );
}
    
/*====================================
 > 画空心香肠,线宽为1
=====================================*/
E_Status_t      BLK_FUNC( Graph , capsule_raw       ) (int xs,int ys,int xe,int ye, void* pIMG, F_Render RH_NULLABLE callback ){
    int d = ye-ys+1;
    int r = d>>1;

    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }

    for(int x=xs+r;x<xe-r;x++){
        callback( x, ys, pIMG );
        callback( x, ye, pIMG );
    }
    
    
    int p    = 3-2*r;
    bool eps = (d%2==0);
    int lx   = xs + r, rx = xe - r;
    int y    = ys + r-eps;
    for(int x_tmp=0,y_tmp = r;x_tmp<=y_tmp && lx+eps-x_tmp>=xs && rx+x_tmp<=xe && lx+eps-y_tmp>=xs && rx+y_tmp<=xe;x_tmp++){
        callback( rx     + x_tmp, y     + y_tmp, pIMG );
        callback( lx+eps - x_tmp, y     + y_tmp, pIMG );
        callback( rx     + x_tmp, y+eps - y_tmp, pIMG );
        callback( lx+eps - x_tmp, y+eps - y_tmp, pIMG );
        
        callback( rx     + y_tmp, y     + x_tmp, pIMG );
        callback( lx+eps - y_tmp, y     + x_tmp, pIMG );
        callback( rx     + y_tmp, y+eps - x_tmp, pIMG );
        callback( lx+eps - y_tmp, y+eps - x_tmp, pIMG );

        if(p <= 0){
            p += (x_tmp<<2) + 6;
        }else{
            p += ((x_tmp-y_tmp)<<2) + 10;
            y_tmp--;
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}

/*====================================
 > 画空心香肠,线宽为1
=====================================*/
E_Status_t      BLK_FUNC( Graph , capsule_fill      ) (int x1,int y1,int x2,int y2, void* pIMG, F_Render RH_NULLABLE callback ){
    
    
    int xs = RH_MIN(x1, x2);
    int xe = RH_MAX(x1, x2);
    int ys = RH_MIN(y1, y2);
    int ye = RH_MAX(y1, y2);
    
    int d = ye-ys+1;
    int r = d>>1;
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    
    // 绘制上下梁
    for(int x=xs+r;x<xe-r;x++){
        callback( x, ys, pIMG );
        callback( x, ye, pIMG );
    }
    
    if( xe-xs >= d){
//    if( 1){
        int p    = 3-2*r;
        bool eps = (d%2==0);
        int lx   = xs + r, rx = xe - r;
        int y    = ys + r-eps;
        for(int x_tmp=0,y_tmp = r;x_tmp<=y_tmp && lx+eps-x_tmp>=xs && rx+x_tmp<=xe && lx+eps-y_tmp>=xs && rx+y_tmp<=xe;x_tmp++){
            callback( rx     + x_tmp, y     + y_tmp, pIMG );
            callback( lx+eps - x_tmp, y     + y_tmp, pIMG );
            callback( rx     + x_tmp, y+eps - y_tmp, pIMG );
            callback( lx+eps - x_tmp, y+eps - y_tmp, pIMG );
            for( int x=lx+eps-x_tmp; x<=rx+x_tmp; x++ ){
                callback( x, y+y_tmp    , pIMG );
                callback( x, y+eps-y_tmp, pIMG );
            }
            
            callback( rx     + y_tmp, y     + x_tmp, pIMG );
            callback( lx+eps - y_tmp, y     + x_tmp, pIMG );
            callback( rx     + y_tmp, y+eps - x_tmp, pIMG );
            callback( lx+eps - y_tmp, y+eps - x_tmp, pIMG );
            for( int x=lx+eps-y_tmp; x<=rx+y_tmp; x++ ){
                callback( x, y+x_tmp    , pIMG );
                callback( x, y+eps-x_tmp, pIMG );
            }
            

            if(p <= 0){
                p += (x_tmp<<2) + 6;
            }else{
                p += ((x_tmp-y_tmp)<<2) + 10;
                y_tmp--;
            }
        }
    }else if( xe-xs >= r ){
        int p    = 3-2*r;
        bool eps = (d%2==0);
        int lx   = xs + r, rx = xe - r;
        int y    = ys + r-eps;
        for(int x_tmp=0,y_tmp = r;x_tmp<=y_tmp && lx+eps-x_tmp>=xs && rx+x_tmp<=xe && lx+eps-y_tmp>=xs && rx+y_tmp<=xe;x_tmp++){
            for( int x=lx+eps-x_tmp; x<=rx+x_tmp; x++ ){
                callback( x, y+y_tmp    , pIMG );
                callback( x, y+eps-y_tmp, pIMG );
            }
            for( int x=lx+eps-y_tmp; x<=rx+y_tmp; x++ ){
                callback( x, y+x_tmp    , pIMG );
                callback( x, y+eps-x_tmp, pIMG );
            }
            if(p <= 0){
                p += (x_tmp<<2) + 6;
            }else{
                p += ((x_tmp-y_tmp)<<2) + 10;
                y_tmp--;
            }
        }
    }else{
        int p    = 3-2*r;
        bool eps = (d%2==0);
        int x    = xs + r;
        int y    = ys + r-eps;
        
        for(int x_tmp=0,y_tmp=r;x_tmp<=y_tmp;x_tmp++){
            int cnt = y_tmp+1;
            
            while(cnt--){
                if(x+eps-x_tmp<=xe){
                    callback(x+eps - x_tmp ,y     + cnt,pIMG );
                    callback(x+eps - x_tmp ,y+eps - cnt,pIMG );
                }
            }

            cnt = x_tmp+1;
            while(cnt--){
                if(x+eps-y_tmp<=xe){
                    callback(x+eps - y_tmp ,y     + cnt,pIMG );
                    callback(x+eps - y_tmp ,y+eps - cnt,pIMG );
                }
            }
            
            if(p <= 0){
                p += (x_tmp<<2) + 6;
            }else{
                p += ((x_tmp-y_tmp)<<2) + 10;
                y_tmp--;
            }
        }
    }
    
    return MAKE_ENUM( kStatus_Success );
}
    
    
E_Status_t      BLK_FUNC( Graph , triangle_raw      ) (int x1,int y1,int x2,int y2,int x3,int y3, void*pIMG, F_Render RH_NULLABLE callback ){
    BLK_FUNC(Graph,line_raw)( x1, y1, x2, y2, pIMG, callback );
    BLK_FUNC(Graph,line_raw)( x2, y2, x3, y3, pIMG, callback );
    return BLK_FUNC(Graph,line_raw)( x3, y3, x1, y1, pIMG, callback );
}
    
E_Status_t      BLK_FUNC( Graph , triangle_fill     ) (int x1,int y1,int x2,int y2,int x3,int y3, void*pIMG, F_Render RH_NULLABLE callback ){
    
    int xs = RH_MIN(x1, RH_MIN(x2, x3));
    int xe = RH_MAX(x1, RH_MAX(x2, x3));
    int ys = RH_MIN(y1, RH_MIN(y2, y3));
    int ye = RH_MAX(y1, RH_MAX(y2, y3));
    
    long t_area = BLK_FUNC(Math,area_triangle)( x1,y1, x2,y2, x3,y3  );
    
    if( !callback ){
        callback = GCFG.callbacks[ GCFG.method ];
    }
    BLK_FUNC( Graph , triangle_raw      )(x1,y1,x2,y2,x3,y3,pIMG,callback);
    for( int y=ys; y<=ye; y++){
        for( int x=xs; x<=xe; x++ ){
            long p_area = BLK_FUNC(Math,area_triangle)( x,y, x1,y1, x2,y2  ) + \
                          BLK_FUNC(Math,area_triangle)( x,y, x2,y2, x3,y3  ) + \
                          BLK_FUNC(Math,area_triangle)( x,y, x1,y1, x3,y3  ) -6;
            if( p_area <= t_area ){
                callback(x,y,pIMG);
            }
        }
    }
    return MAKE_ENUM( kStatus_Success );
}
    
void BLK_FUNC( Graph, demo )(void){
    S_BLK_Img888_t* IMG = BLK_Img888_create(800, 480);
    BLK_Graph_set_color_depth   ( kBLK_ColorDepth_24Bit  );
    BLK_Graph_set_render_method ( kBLK_RenderMethod_fill );

    BLK_Graph_set_penColor( M_COLOR_RED );
    BLK_Graph_circle_fill     ( 400, 240,  39,      IMG, NULL );

    BLK_Graph_set_penColor( M_COLOR_BLUE );
    BLK_Graph_set_penSize (20);
    BLK_Graph_rect_edged      (  30,  50, 130, 112, IMG, NULL );

    BLK_Graph_set_penColor(M_COLOR_AQUA);
    BLK_Graph_set_penSize (10);
    BLK_Graph_rect_round_raw  ( 104, 178, 200, 234, IMG, NULL );

    BLK_Graph_set_penColor(M_COLOR_RED);
    BLK_Graph_rect_raw        ( 300, 240, 307, 270, IMG, NULL );
    BLK_Graph_set_penColor(M_COLOR_AQUA);
    BLK_Graph_capsule_fill    ( 300, 240, 307, 270, IMG, NULL );


    BLK_Graph_set_penColor(M_COLOR_GREEN);
    BLK_Graph_rect_raw        ( 300, 240, 407, 370, IMG, NULL );
    BLK_Graph_rect_edged      ( 300, 240, 407, 370, IMG, NULL );
    BLK_Graph_rect_fill       ( 300, 240, 407, 370, IMG, NULL );
    BLK_Graph_rect_round_fill ( 300, 240, 407, 370, IMG, NULL );
    BLK_Graph_rect_round_raw  ( 300, 240, 407, 370, IMG, NULL );

    BLK_Graph_line_raw        ( 300, 240, 407, 370, IMG, NULL );
    BLK_Graph_line_edged      ( 300, 240, 407, 370, IMG, NULL );
    BLK_Graph_line_fill       ( 300, 240, 407, 370, IMG, NULL );
    BLK_Graph_line_sausage    ( 300, 240, 407, 370, IMG, NULL );
    
    BLK_Img888_out_bmp("/Users/randle_h/Desktop/screen.bmp", IMG);
    BLK_Img888_free(IMG);
}
    
#ifdef __cplusplus
}
#endif

