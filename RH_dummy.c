
#if 0==1

__UNION_PixelRGB888_t in_[6][6] = {
    {{.R =  90},{.R = 100},{.R = 100},{.R =  90},{.R = 100},{.R = 100}},
    {{.R = 100},{.R = 120},{.R =  80},{.R = 100},{.R = 120},{.R = 100}},
    {{.R = 100},{.R =  20},{.R = 100},{.R = 100},{.R = 120},{.R = 100}},
    {{.R =  90},{.R = 100},{.R = 100},{.R =  90},{.R = 100},{.R = 100}},
    {{.R = 100},{.R = 120},{.R =  70},{.R = 100},{.R = 120},{.R = 100}},
    {{.R = 100},{.R =  20},{.R = 100},{.R = 100},{.R = 120},{.R = 100}},
};
__UNION_PixelRGB888_t out_[3][3] = {0};

__ImageRGB888_t in = {
    .pBuffer = in_[0],
    .width   = 6,
    .height  = 6
};

__ImageRGB888_t out = {
    .pBuffer = out_[0],
    .width   = 3,
    .height  = 3
};
__Area_t AREA = {
    .xs = 2,
    .ys = 2,
    .width  = 3,
    .height = 3
};

__Blur_Average_ImgRGB888(&in,&out,&AREA,10,100);

#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )
            while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )
            while(1);
#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )
            __Blur_Average_ImgRGB888(pInfo, &GCFG.blur_tmp, &GCFG.blur_area, GCFG.blur_size, GCFG.blur_br_100);
#else
  #error "[RH_graphic]: Unknown color type."
#endif

const char* __restrict__ src  = "/Users/randle_h/desktop/lenna.bmp";
const char* __restrict__ des  = "/Users/randle_h/desktop/lenna_.bmp";

__ImageRGB888_t* IMG_IN  = __LoadBMP_ImgRGB888(src);
__Area_t         AREA    = {
    .xs = 1,
    .ys = 1,
    .width  = 300,
    .height = 300
};
__ImageRGB888_t* IMG_OUT = __Create_ImgRGB888(AREA.width, AREA.height);


__Blur_Average_ImgRGB888(IMG_IN,IMG_OUT,&AREA,40000,100);
__OutBMP_ImgRGB888(des, IMG_OUT);



( *applyPixelMethod [method] )(x1,y1,GCFG.penColor,pInfo);


long __pascal_triangle(int row, int col){
    __exitReturn( col>row || col<0 || row<0 , -1 );

    struct __Link{
        struct __Link* pNext;
        int*           data;
        size_t         row;
    };
    typedef struct __Link __Link;
    static struct __Link Head = {
        .pNext = NULL ,
        .data  = NULL ,
        .row   = 0
    };
    if( Head.data == NULL ){
        Head.data = (int*)malloc(sizeof(int));
        Head.data[0] = 1;
    }

    __Link* pIter = &Head;
    __Link* pOpti = &Head;
    __Link* pLast = &Head;
    
    long dis_row_min    = row - pIter->row;

    do{
        // 行差越小，需要迭代的次数就越少
        if( row > pIter->row && (row-pIter->row) < dis_row_min ){
            dis_row_min = row - pIter->row;
            pOpti = pIter;
        }
        // 如果就是那一行，即行差为0，则直接返回值
        if( pIter->row==row ){
            return ( pIter->data[col] );
        }
        // 继续迭代寻找
        pLast = pIter;
        pIter = pIter->pNext;
   
    }while( pIter != NULL );
    
    // 没有找到那一行，则从最接近那一行（pOpti->row）的数值开始向下相邻累加计算，并记录之
    // 此时 pOpti 代表最佳的那一行数据，pLast为链表最后节点末尾。
    __Link*  pasc_link = pLast;
    int*     last_data = pOpti->data;
    size_t   pasc_size = pOpti->row+2;                                 // 该行的元素个数为上一行行号+2
    
    while( dis_row_min-- ){
        pasc_link->pNext    = (__Link*)malloc( sizeof(__Link) );       // 新建一行
        pasc_link           = pasc_link->pNext;
        

        pasc_link->data     = (int*)malloc( pasc_size * sizeof(int));
        pasc_link->row      = pasc_size-1;                             // 该行行号为该行元素数量-1
        pasc_link->pNext    = NULL;
        
        pasc_link->data[pasc_size-1] = pasc_link->data[0] = 1;        // 该行边界均为1
        for( int i=1;i<=(pasc_size-1-i);i++ ){
            pasc_link->data[i] = pasc_link->data[pasc_size-1-i] = last_data[i] + last_data[i-1];
            
        }

        last_data           = pasc_link->data;
        pasc_size           = pasc_link->row+2;
    }

    return pasc_link->data[col];
}



#ifndef __RH_ASSERT_H
#define __RH_ASSERT_H

#ifdef __cpluplus
extern "C"{
#endif


#ifdef __cpluplus
}
#endif

#endif

const char* path_in  = "D:\\Personal\\Desktop\\temp.bmp";
const char* path_out = "D:\\Personal\\Desktop\\out.bmp";
__ImageRGB565_t* IMG_IN  = __ImgRGB565_load_bmp(path_in);
__ImageRGB565_t* IMG_OUT = __ImgRGB565_create( IMG_IN->width , IMG_IN->height );
__ImgRGB565_copy( IMG_IN, IMG_OUT );
__ImgRGB565_out_bmp( path_out, IMG_OUT );



int iter = (int)(src->width*ys + xs);
        for(int n=ys; n < ys+half_order; n++, iter+=src->width){
//            int iter = (int)(src->width*n + xs);
            for(int m=xs; m < xs+half_order;m++, iter++){
                sum_R += pSrcData[iter].R;
                sum_G += pSrcData[iter].G;
                sum_B += pSrcData[iter].B;
            }
            iter-=half_order;
        }


#ifdef RH_DEBUG
    ASSERT(!fontFile);
#endif

FILE* fontFile = fopen( "/Users/randle_h/Desktop/Glucoo/Glucoo/Font/Courier New Bold.ttf" , "rb" );
#ifdef RH_DEBUG
ASSERT( fontFile );
#endif
__exitReturn( !fontFile, kStatus_BadAccess );

fseek(fontFile, 0, SEEK_END);
size_t size = ftell(fontFile);
fseek(fontFile, 0, SEEK_SET);

uint8_t* array = calloc(size, sizeof(uint8_t));

fread(array, size, sizeof(uint8_t), fontFile);
fclose(fontFile);



FILE* fontTxt = NULL;

fontTxt = fopen("/Users/randle_h/Desktop/Glucoo/Glucoo/Font/RH_font_CourierNewBold.c", "a");
char buf[10] = {0};

for(int i=0; i<size; i++){
    if(i%20 == 0 ){
        fprintf( fontTxt, "\n");
    }
    sprintf(buf, "0x%02X, ",array[i]);
    fprintf( fontTxt, "%s",buf);

}

fclose(fontTxt);

__GUI_Window_t cfg;
    cfg.area.xs     = 30;
    cfg.area.ys     = 40;
    cfg.area.height = 300;
    cfg.area.width  = 500;
    cfg.type        = kGUI_WindowType_macOS;
    cfg.size        = 40;
    cfg.appearance  = kGUI_Appearance_Dark;
    cfg.title       = "Text";

    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    ID_t ID_Window1 = GUI_create_window(&cfg);
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    GUI_insert_window( ID_Window1 );
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    GUI_RefreashScreen();
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);
    GUI_delete_window( ID_Window1 );
    
    printf("Alloced Memory: %ld B\n",RH_alloc_byte);


Simul_API_Init();

GUI_RefreashScreen();


__GUI_Window_t cfg2;
GUI_easySet_window(&cfg2);
cfg2.area.xs     = 100;
cfg2.area.ys     = 50;
cfg2.area.height = 360;
cfg2.area.width  = 600;
cfg2.type        = kGUI_WindowType_macOS;
cfg2.size        = 40;
cfg2.appearance  = kGUI_Appearance_Dark;
cfg2.title       = "To: Pr.WenKai";
cfg2.text_size   = 20;
cfg2.text_font   = kGUI_FontStyle_Arial_Unicode;//kGUI_FontStyle_NewYork;
cfg2.text        = "Hello, this is not a regular dialog box and either not a snapshot from my computer. It is a simple UI designed for my command desk which is a embedded device targeting on STM32. This UI project named ""Glucoo"". It has been published on my GitHub website and the link is attached in the E-mail. If you view carefully, you will find out an another secrete repository reference from 'Glucoo'. That's right-> BlackHouse!!! Honestly, Glucoo doesn't work very well. Those functions are still limited-useed or poor-proformance. Me now writting English as a Chinese friend is one of those that it doesn't support any charactor beyond the ASCII. Anyway, I made this simply not for any competition, rewords or research. I just assume that I am a novelist or king of my own Digital-Empire. I create my own data structure like building an architecture or managing a beautiful city. This sounds a little bit aggressive. I used to be solo and I tried to work togeither with friends, but maybe I laid the standard so high that no one can meet it even for myself. Anyway, It will be my honor if you take a look of my project. ";
ID_t ID_Window2 = GUI_create_window(&cfg2);

GUI_insert_window( ID_Window2 );
GUI_RefreashScreen();

GUI_delete_window( ID_Window2 );



#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF )

#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY )

#else
  #error "Unknown font data source."
#endif


typedef enum{
    kGUI_MenuType_macOS  ,
    kGUI_MenuType_win10  ,
    NUM_kGUI_MenuStyle   ,
}E_GUI_MenuStyle_t;

struct __GUI_MenuCFG_t{
    const char*          text;
};
typedef struct __GUI_MenuCFG_t __GUI_MenuCFG_t;

struct __GUI_Menu_t{
    __Area_t             area;
    E_GUI_MenuStyle_t    style;
    E_GUI_Appearance_t   appearance;
    size_t               size;
    
    __GUI_MenuCFG_t*     config;
    size_t               nitems;
    
    
};
typedef struct __GUI_Menu_t __GUI_Menu_t;

__GUI_Window_t cfg;
GUI_window_quickSet(&cfg);
cfg.area.xs     = 20;
cfg.area.ys     = 20;
cfg.area.height = 40;
cfg.area.width  = 90;
cfg.type        = kGUI_WindowType_win10;
cfg.size        = 9;
cfg.appearance  = kGUI_Appearance_Light;
cfg.title       = "Text";
cfg.text        = NULL;
cfg.text_size   = 8;

ID_t ID_Window1 = GUI_window_create(&cfg);
GUI_window_insert( ID_Window1 );


__GUI_Object_t cfg_obj = {0};

GUI_object_quickSet(&cfg_obj);

cfg_obj.style       = kGUI_ObjStyle_num;
cfg_obj.area.xs     = 30;
cfg_obj.area.ys     = 30;
cfg_obj.area.height = 12;
cfg_obj.area.width  = 70;
cfg_obj.min         = 0;
cfg_obj.max         = 256;
cfg_obj.font        = kGUI_FontStyle_ArialRounded_Bold;
cfg_obj.text_color  = M_COLOR_RED;
cfg_obj.text        = "size:";
cfg_obj.text_size   = 8;
cfg_obj.text_align  = kGUI_FontAlign_Left;
cfg_obj.showFrame   = false;

cfg_obj.bk_color    = M_COLOR_TAN;

cfg_obj.val         = 129;

ID_t ID_Obj1 = GUI_object_create( &cfg_obj );
GUI_object_insert(ID_Obj1);
GUI_RefreashScreen();

GUI_object_frame(ID_Obj1,true);

GUI_object_adjust(ID_Obj1, 11);


GUI_RefreashScreen();



#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )

#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
#else
  #error "[RH_graphic]: Unknown color type."
#endif








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
                __read_ttf_file( font_ttf_path[style] );
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
    FCFG.size   = 8;
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

__GUI_Font_t*  __Font_exportStr( const char* str ){
    
    if( FCFG.info.img_buf ){
        RH_FREE(FCFG.info.img_buf);
        FCFG.info.img_buf = NULL;
    }
    
    size_t len = strlen(str);
    
    FCFG.info.img_h = FCFG.size;
    FCFG.info.img_w  = 0;
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
        FCFG.info.img_w += c_x[i];
        if(i!=0)
            xs[i]  = xs[i-1] + c_x[i-1];
        ys[i]  = FCFG.ascent + c_y1;

    }
    
    FCFG.info.img_buf = RH_CALLOC(FCFG.info.img_w*FCFG.info.img_h, sizeof(uint8_t));
    for(int i=0; i<len; i++){
        size_t byteOffset = 0;
        if( i!=0 ){
            byteOffset = ( lfB[i] + ys[i]*FCFG.info.img_w + xs[i] );
        }else{
            byteOffset = ( lfB[i] + ys[i]*FCFG.info.img_w + xs[i] );
        }
        (*FCFG.method->_MakeCodepointBitmap)(&FCFG.stb_info, FCFG.info.img_buf+byteOffset, c_x[i], c_y[i], (int)(FCFG.info.img_w), FCFG.scale, FCFG.scale, str[i]);
    }
    RH_FREE(xs);
    RH_FREE(ys);
    RH_FREE(c_x);
    RH_FREE(c_y);
    RH_FREE(adv);
    RH_FREE(lfB);
#ifdef STB_OUTPUT_FONT_PNG
    printf("ascent = %d\n"   , FCFG.ascent);
    printf("descent = %d\n"  , FCFG.descent);
    printf("lineGap = %d\n"   , FCFG.lineGap);
    
    printf("w = %ld\n", FCFG.info.img_w  );
    printf("h = %ld\n", FCFG.info.img_h );
    stbi_write_png("C:/Users/asus/Desktop/img_buf.png", (int)FCFG.info.img_w, (int)FCFG.info.img_h, 1, FCFG.info.img_buf, (int)FCFG.info.img_w);
    stbi_write_png("/Users/randle_h/Desktop/img_buf.png", (int)FCFG.info.img_w, (int)FCFG.info.img_h, 1, FCFG.info.img_buf, (int)FCFG.info.img_w);
#endif
    return &FCFG.info;
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

E_GUI_FontStyle_t __Font_getStyle(void){
    return FCFG.style;
}


static E_Status_t __read_ttf_file( const char* path, void** buf ){
    FILE* fontFile = fopen( path , "rb" );
#ifdef RH_DEBUG
    RH_ASSERT( fontFile );
#endif
    __exitReturn( !fontFile, MAKE_ENUM( kStatus_BadAccess ) );

    fseek(fontFile, 0, SEEK_END);
    size_t size = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);


    *buf = RH_CALLOC(size, sizeof(uint8_t));

    fread(*buf, size, sizeof(uint8_t), fontFile);
    fclose(fontFile);

    return MAKE_ENUM(kStatus_Success);
}

int main(int argc, const char * argv[]) {

    Simul_API_Init();

    GLU_FUNC( GUI, init        )();
    GLU_FUNC( GUI, setPenSize  )(5);
    GLU_FUNC( GUI, setPenColor )(M_COLOR_WHITE);
    
    
    GLU_FUNC(Font, set_size)( 25 );
    
    // 前期准备工作(与字体和大小有关, 与具体字符无关)
    int fsize = 47; // 字体大小
    
    float scale;                      // 缩放
    int   ascent, descent,lineGap;    // 上边, 下边, 行间距
    
    // 读取ttf文件数据
    stbtt_fontinfo stb_info;
    void* fdata = NULL;
    __read_ttf_file( "/Users/randle_h/GitHub/Glucoo/core/Glucoo/font/Arial Rounded Bold.ttf", &fdata );
    stbtt_InitFont(&stb_info, fdata, 0);
    
    stbtt_GetFontVMetrics( &stb_info, &ascent, &descent, &lineGap );
    scale   = stbtt_ScaleForPixelHeight( &stb_info, fsize );
    ascent  = roundf( ascent  * scale);
    descent = roundf( descent * scale);
    
    uint8_t* img_buf = NULL;
    
    const char* str = "STB RandleH.";

#if 0
    printf( "scale   = %f\n", scale   );
    printf( "ascent  = %d\n", ascent  );
    printf( "descent = %d\n", descent );
    printf( "lineGap = %d\n\n", lineGap );
#endif
    
    // 迭代字符渲染
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
            stbtt_GetCodepointBitmapBox( &stb_info, str[cnt], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
            
            cw[cnt] = c_x2-c_x1;
            ch[cnt] = c_y2-c_y1;
            cy[cnt] = ascent + c_y1;
        }
        
        {// 字符横向间隙和宽度
            int advanceWidth,leftSideBearing;
            stbtt_GetCodepointHMetrics(&stb_info, str[cnt], &advanceWidth, &leftSideBearing );
            
            leftSideBearing = roundf( leftSideBearing*scale );
            advanceWidth    = roundf( advanceWidth*scale );
            
            cx[cnt]   += leftSideBearing;
            
            cx[cnt+1]  = cx[cnt] - leftSideBearing + advanceWidth + roundf( stbtt_GetCodepointKernAdvance( &stb_info, str[cnt], str[cnt+1] ) * scale) ;
        }
        cnt++;
    }
    // 确定绘制出这样的字符串至少需要的图像大小
    int img_w = cx[cnt];
    int img_h = ascent-descent+lineGap;
    img_buf = RH_CALLOC( img_w*img_h, sizeof(uint8_t) );
    
    cnt = 0;
    while( str[cnt]!='\0' ){
        uint8_t *pIter = img_buf + ( img_w*cy[cnt] ) + cx[cnt];
        stbtt_MakeCodepointBitmap( &stb_info, pIter, cw[cnt], ch[cnt], (int)img_w, scale, scale, str[cnt] );
        cnt++;
    }

    stbi_write_png("/Users/randle_h/Desktop/output.png", img_w, img_h, 1, img_buf, img_w);
    
    return 0;
}


void __Font_getStrSize( size_t *width, size_t *height, const char* str ){
    __exit( !str );
    if( width )
        *width = 0;
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





BLK_SRCT( Img888 )* IMG = BLK_FUNC( Img888, load_bmp )( "/Users/randle_h/Desktop/lenna.bmp" );
BLK_SRCT( ImgBin )* IMG1= BLK_FUNC( ImgBin, create   )( 300, 200 );

GLU_FUNC(Font, set_size )(45);
GLU_FUNC(Font, set_style)(kGLU_Font_NewYork);
GLU_SRCT(FontImg)* pFImg = GLU_FUNC(Font, out_str_Img)("Hello world.");

BLK_SRCT( ImgGry ) SCR = {
    .pBuffer = (BLK_UION(PixelGry)*)pFImg->img_buf ,
    .height  = pFImg->img_h   ,
    .width   = pFImg->img_w
};

BLK_FUNC( ImgGry, into_ImgBin )(&SCR, IMG1, 30, 30, 0xff       );
BLK_FUNC( ImgGry, into_Img888 )(&SCR, IMG , 30, 30, 0x00ff0000 );

BLK_FUNC( Img888, out_bmp )("/Users/randle_h/Desktop/out.bmp", IMG);
BLK_FUNC( ImgBin, out_bmp )("/Users/randle_h/Desktop/out1.bmp", IMG1);


__gui_insert_menu_title {
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        /* 字体图像像素遍历pIter */
        uint8_t* pIter = pF->img_buf;
        for( int y=0; y<pF->img_h&&y<config->area.height; y++ ){
            for( int x=0; x<pF->img_w; x++, pIter++ ){
                size_t index = ((y_fs+y)>>3)*(info_MainScreen.width)+(x_fs+x);
                if( (*pIter<128) ^ (config->color_title!=0) ){
                    info_MainScreen.pBuffer[ index ].data = __BIT_SET( info_MainScreen.pBuffer[ index ].data, (y_fs+y)%8 );
                }else{
                    info_MainScreen.pBuffer[ index ].data = __BIT_CLR( info_MainScreen.pBuffer[ index ].data, (y_fs+y)%8 );
                }
            
            }
        }
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        /* 字体图像像素遍历pIter */
        uint8_t       *pIterFont = pF->img_buf;
        GLU_UION(Pixel) *pIterScr  = info_MainScreen.pBuffer + (y_fs*info_MainScreen.width) + x_fs;
        
        for( int y=0; y<pF->img_h&&y<config->area.height; y++ ){
            register int x=0;
            for( ; x<pF->img_w; x++, pIterFont++, pIterScr++ ){
                if( *pIterFont>128 ){
                    pIterScr->data = config->color_title;
                }
            }
            pIterScr -= x;
            pIterScr += info_MainScreen.width;
        }
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        RH_ASSERT(0);
    #endif
}

__gui_insert_menu_bar{
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        /* 字体图像像素遍历pIter */
        uint8_t* pIter = pF->img_buf;
        for( int y=0; y<pF->img_h&&y<config->area.height; y++ ){
            for( int x=0; x<pF->img_w; x++, pIter++ ){
                size_t index = ((y_fs+y)>>3)*(info_MainScreen.width)+(x_fs+x);
                if( (*pIter<128) ^ (text_color.data!=0) ){
                    info_MainScreen.pBuffer[ index ].data = __BIT_SET( info_MainScreen.pBuffer[ index ].data, (y_fs+y)%8 );
                }else{
                    info_MainScreen.pBuffer[ index ].data = __BIT_CLR( info_MainScreen.pBuffer[ index ].data, (y_fs+y)%8 );
                }
            
            }
        }
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        /* 字体图像像素遍历pIterFont */
        uint8_t*       pIterFont = pF->img_buf;
        GLU_UION(Pixel)* pIterScr  = info_MainScreen.pBuffer + (y_fs*info_MainScreen.width) + x_fs;
        for( int y=0; y<pF->img_h&&y<config->area.height; y++ ){
            register int x=0;
            for( ; x<pF->img_w; x++, pIterFont++, pIterScr++ ){
                if( *pIterFont > 128 ){
                    *pIterScr = text_color;
                }
            }
            pIterScr -= x;
            pIterScr += info_MainScreen.width;
        }

    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        RH_ASSERT(0);
    #endif
}



__gui_insert_object_num{
    #if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
        uint8_t* pIter = pF->img_buf;
        for( int y=0; y<pF->img_h && y<config->area.height; y++ ){
            for( int x=0; x<pF->img_w; x++, pIter++ ){
                size_t index = ((y_fs+y)>>3)*(info_MainScreen.width)+(x_fs+x);
                if( (*pIter<128) ^ (color_text.data!=0) ){
                    info_MainScreen.pBuffer[ index ].data = __BIT_SET( info_MainScreen.pBuffer[ index ].data, (y_fs+y)%8 );
                }else{
                    info_MainScreen.pBuffer[ index ].data = __BIT_CLR( info_MainScreen.pBuffer[ index ].data, (y_fs+y)%8 );
                }
            
            }
        }
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
        for( int y=0; y<pF->img_h&&y<config->area.height; y++ ){
            for( int x=0; x<pF->img_w; x++ ){
                size_t index = (y_fs+y)*(info_MainScreen.width)+(x_fs+x);
                uint8_t pixWeight = pF->img_buf[y*pF->img_w+x];
                info_MainScreen.pBuffer[ index ].R = info_MainScreen.pBuffer[ index ].R + (( (color_text.R - info_MainScreen.pBuffer[ index ].R) * pixWeight )>>8);
                info_MainScreen.pBuffer[ index ].G = info_MainScreen.pBuffer[ index ].G + (( (color_text.G - info_MainScreen.pBuffer[ index ].G) * pixWeight )>>8);
                info_MainScreen.pBuffer[ index ].B = info_MainScreen.pBuffer[ index ].B + (( (color_text.B - info_MainScreen.pBuffer[ index ].B) * pixWeight )>>8);
            }
        }
    #elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
        RH_ASSERT(0);
    #else
         
    #endif
}

__gui_insert_object_fnum{
#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
    uint8_t*       pIterFont = pF->img_buf;
    
    GLU_UION(Pixel)* pIterScr  = info_MainScreen.pBuffer + (y_fs>>3)*(info_MainScreen.width)+x_fs;
    
    for( int y=0; y<pF->img_h && y<config->area.height; y++ ){
        for( int x=0; x<pF->img_w; x++, pIterFont++, pIterScr++ ){
            if( (*pIterFont<128) ^ (color_text.data!=0) ){
                pIterScr->data = __BIT_SET( pIterScr->data, (y_fs+y)%8 );
            }else{
                pIterScr->data = __BIT_CLR( pIterScr->data, (y_fs+y)%8 );
            }
        }
        
        pIterScr -= pF->img_w;
        if( ((y_fs+y+1)>>3) > ((y_fs+y)>>3) ){
            pIterScr += info_MainScreen.width;
        }
    }
    
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
    for( int y=0; y<pF->img_h&&y<config->area.height; y++ ){
        for( int x=0; x<pF->img_w; x++ ){
            size_t index = (y_fs+y)*(info_MainScreen.width)+(x_fs+x);
            uint8_t pixWeight = pF->img_buf[y*pF->img_w+x];
            info_MainScreen.pBuffer[ index ].R = info_MainScreen.pBuffer[ index ].R + (( (color_text.R - info_MainScreen.pBuffer[ index ].R) * pixWeight )>>8);
            info_MainScreen.pBuffer[ index ].G = info_MainScreen.pBuffer[ index ].G + (( (color_text.G - info_MainScreen.pBuffer[ index ].G) * pixWeight )>>8);
            info_MainScreen.pBuffer[ index ].B = info_MainScreen.pBuffer[ index ].B + (( (color_text.B - info_MainScreen.pBuffer[ index ].B) * pixWeight )>>8);
        }
    }
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
    RH_ASSERT(0);
#else
     
#endif
}


BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_leopard )( BLK_SRCT(Img888)* dst ){
    RH_ASSERT( dst          );
    RH_ASSERT( dst->pBuffer );
    RH_ASSERT( dst->height  );
    RH_ASSERT( dst->width   );
    
    int xc[5] = { (int)dst->width/5, \
                  (int)(dst->width<<1)/5,
                  (int)(dst->width*3)/5,
                  (int)(dst->width<<2)/5,
                  (int)(dst->width)
    };
    BLK_UION(Pixel888) color = {.data = M_COLOR_BLACK}; //
    
    // 引用画直线算法, 求颜色增量
    // 颜色的变化随绘制的横坐标有关
    int delta_x    = (int)( xc[0] );
    // 纵坐标为颜色深度
    int delta_y    = (int)( 0xff  );
    
    int8_t* delta_c = alloca(sizeof(int8_t)*delta_x); // 颜色增量数组
    memset( delta_c, 0, sizeof(int8_t)*delta_x);
    
    int j = 0;
    int e = 0;
    for(int i = 0;i < delta_x;i++){
        e += delta_y;
        while( 2*( e + delta_y ) > delta_x ){
            j++;
            delta_c[i]++;
            e -= delta_x;
        }
    }
    
    for( int x=0; x<=dst->width-1; x++ ){
        
        
        if( x<xc[0] ){
            if( color.R+delta_c[x]<=0xff )
                color.R += delta_c[x];
        }
        else if (x<xc[1]){
            if( color.G+delta_c[ x-xc[0] ]<=0xff )
                color.G += delta_c[ x-xc[0] ];
        }
        else if (x<xc[2]){
            if( color.R-delta_c[ x-xc[1] ]>0 )
                color.R -= delta_c[ x-xc[1] ];
            if( color.B+delta_c[ x-xc[1] ]<=0xff )
                color.B += delta_c[ x-xc[1] ];
        }
        else if (x<xc[3]){
            if( color.G-delta_c[ x-xc[2] ]>0 )
                color.G -= delta_c[ x-xc[2] ];
        }
        else if (x<xc[4]){
            if( color.B-delta_c[ x-xc[3] ]>0 )
                color.B -= delta_c[ x-xc[3] ];
        }
        
        int ys = rand()%(dst->height/3), ye = (int)(dst->height<<1)/3 + rand()%(dst->height/3);//
        
        float sigma = (ye-ys)/6.0;
        
        BLK_UION(Pixel888)* pIterUP = dst->pBuffer + ys*(dst->width) +x;
        BLK_UION(Pixel888)* pIterDN = dst->pBuffer + ye*(dst->width) +x;
        for( int y=ys; y<=ye; y++, pIterUP+=dst->width, pIterDN-=dst->width ){
            int tmp = (y-((ye-ys)>>1)-ys)*(y-((ye-ys)>>1)-ys);
            pIterUP->R = roundl( color.R* exp( -tmp/(2*sigma*sigma)));
            pIterUP->G = roundl( color.G* exp( -tmp/(2*sigma*sigma)));
            pIterUP->B = roundl( color.B* exp( -tmp/(2*sigma*sigma)));
        }
    }
    
    return dst;
}


// 给定颜色链 居中画竖直色块
BLK_SRCT(Img888)* BLK_FUNC( Img888, draw_img_ )
( BLK_SRCT(Img888)* dst, const BLK_TYPE(Pixel888)* colors, size_t size ){
    RH_ASSERT( dst          );
    RH_ASSERT( dst->pBuffer );
    RH_ASSERT( dst->height  );
    RH_ASSERT( dst->width   );
    
    const int xs   = (int)dst->width>>2;
    const int xe   = (int)dst->width - xs +1;
    const int xl   = xe - xs + 1;
    
    // 获取色条的起始横坐标
    int* x_rect = alloca( (size+1)*sizeof(int) );
    memset(x_rect, 0, size*sizeof(int));
    x_rect[0]    = xs;
    x_rect[size] = xe;
    
    {
        int m   = (int) xl%size;
        int k   = (int) size - m;
        int len = (int) xl/size;
        
        for( int *p  = x_rect; m||k; p++ ){
            if( p == x_rect){
                *p = xs;
                k--;
                continue;
            }else{
                *p = *(p-1);
            }
            
            if(k){
                *p += len;
                k--;
            }else{
                *p += len +1;
                m--;
            }
            
        }
    }
    
    {
        int ys = (int)dst->height/5;
        int ye = (int)dst->height*4/5;
        const BLK_TYPE(Pixel888)* pIterColor = colors;
        for(int i=0; i<size; i++,pIterColor++){
            for(int x = x_rect[i];x <= x_rect[i+1];x++)
                dst->pBuffer[ ys*dst->width + x].data = *pIterColor;
            for(int y = ys+1;y <= ye;y++)
                memmove( (dst->pBuffer + y  * dst->width + x_rect[i]),\
                         (dst->pBuffer + ys * dst->width + x_rect[i]),\
                       ( (x_rect[i+1]-x_rect[i]+1)*sizeof(BLK_TYPE(Pixel888))) );
        }
    }
    
    return dst;
}


BLK_SRCT(Img888)* BLK_FUNC( Img888, load_png )    (const char* __restrict__ path){
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
    
    BLK_SRCT(Img888)* pIMG = RH_MALLOC(sizeof(BLK_SRCT(Img888)));
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

static void Img888_line( int x1, int y1, int x2, int y2, BLK_SRCT(Img888)* dst, void (*func)(BLK_SRCT(Img888)* dst, int x, int y) ){
    int dx = __abs( x2-x1 );
    int dy = __abs( y2-y1 );
    
    int type = (int)( ((y2-y1<0)<<2) | ( (x2-x1<0)<<1) | (dy > dx));
    
    /* About this <type> : 通过平移, 将(x1,y1)移到原点, 此时(x2,y2)的位置决定type.
    
                      Y
          *           |           *
            *  type=3 | type=1  *
              *       |       *
                *     |     *
        type=2    *   |   *    type=0
                    * | *
    ------------------+------------------ X
                    * | *
        type=6    *   |   *    type=4
                *     |     *
              *       |       *
            *  type=7 | type=5  *
          *           |           *
     
     测试用例:
         type 0:   30,  30 ,    150,  90
         type 1: -150,-150 ,   -134,  69
         type 2:  -50,  10 ,   -100,  20
         type 3:   30,  30 ,     10, 100
         type 4:   50, -20 ,    150, -50
         type 5:   20, -40 ,     60,-100
         type 6:  150,  90 ,     30,  30
         type 7:  -20, -40 ,    -40,-120
         
    */
    
    switch(type){
        case 0:
            break;
        case 2: x2 = -x2;
                x1 = -x1;
            break;
        case 1: __swap(x2, y2);
                __swap(x1, y1);
            break;
        case 6: y2 = -y2;
                y1 = -y1;
                x2 = -x2;
                x1 = -x1;
            break;
        case 3: x2 = -x2;
                x1 = -x1;
                __swap(x2, y2);
                __swap(x1, y1);
            break;
        case 7: __swap(x2,y2);
                __swap(x1,y1);
                x2 = -x2; x1 = -x1;
                y2 = -y2; y1 = -y1;
            break;
        case 5: y2 = -y2;
                y1 = -y1;
                __swap(x2,y2);
                __swap(x1,y1);
            break;
        case 4: y2 = -y2;
                y1 = -y1;
            break;
    }
    
# if 1
    printf("type=%d\n",type);
    { // 检查是否成功转换, 此段可注释
        int dx = __abs( x2-x1 );
        int dy = __abs( y2-y1 );
        int type1 = (int)( ((y2-y1<=0)<<2) | ( (x2-x1<=0)<<1) | (dy > dx));
        assert( type1 == 0 );
    }
#endif

    dx = x2-x1 ;
    dy = y2-y1 ;
    
    int d  = dy*2 -dx;
    int x = x1, y = y1;
    int res_x, res_y;
    while( x <= x2 ){
        
        res_x = x; res_y = y;
            switch(type){
                case 0: break;
                case 2: res_x = -res_x;
                    break;
                case 1: __swap(res_x, res_y);
                    break;
                case 6: res_y = -res_y;
                        res_x = -res_x;
                    break;
                case 3: __swap(res_x,res_y);
                        res_x = -res_x;
                    break;
                case 7: __swap(res_x,res_y);
                        res_x = -res_x;
                        res_y = -res_y;
                    break;
                case 5: res_y = -res_y;
                        __swap(res_x,res_y);
                    break;
                case 4: res_y = -res_y;
                    break;
            }
        
            (*func)( dst, res_x, res_y );
        
        if( d < 0 || y>=y2 ){
            d += 2*dy;
        }else{
            d += (dy-dx)*2;
            y++;
        }
        x++;
    }
    
}


volatile long*        __pascal_triangle_row ( long row , size_t* returnSize );
volatile long* __pascal_triangle_row( long row , size_t* returnSize ){
    __exitReturn( row<0 , NULL );
    if( returnSize )
        *returnSize = row+1;
    
    struct __Link{
        struct __Link* pNext;
        long*           data;
        size_t         row;
    };
    typedef struct __Link __Link;
    static struct __Link Head = {
        .pNext = NULL ,
        .data  = NULL ,
        .row   = 0
    };
    if( Head.data == NULL ){
        Head.data = (long*)malloc(sizeof(long));
        Head.data[0] = 1;
    }

    __Link* pIter = &Head;
    __Link* pOpti = &Head;
    __Link* pLast = &Head;
    
    long dis_row_min    = __abs(row - pIter->row);
    bool sgn            = (row > pIter->row);     // 标志,判断距离目标最近的那一行位于目标的上方还是下方 1 = 上方; 0 = 下方;
    do{
        // 行差越小，需要迭代的次数就越少
        if( __abs(row-pIter->row) < dis_row_min ){
            sgn = (row > pIter->row);
            dis_row_min = row - pIter->row;
            pOpti = pIter;
        }
        // 如果就是那一行，即行差为0，则直接返回值
        if( pIter->row==row ){
            return ( pIter->data );
        }
        // 继续迭代寻找
        pLast = pIter;
        pIter = pIter->pNext;
   
    }while( pIter != NULL );
    
    // 没有找到那一行，则从最接近那一行（pOpti->row）的数值开始向sgn方向计算，并记录之
    // 此时 pOpti 代表距离最近的那一行数据，pLast为链表最后节点末尾。
    __Link*  pasc_link = pLast;
    long*    last_data = pOpti->data;                                      // 从距离目标最近的那一行开始
    if( sgn == true ){ // =================================================// 距离最近的那一行位于目标上方
        long   pasc_size = (pOpti->row)+2;                                 // 该行的元素个数为上一行行号+2
        
        while( dis_row_min-- ){
            pasc_link->pNext    = (__Link*)malloc( sizeof(__Link) );       // 新建一行
            pasc_link           = pasc_link->pNext;
            

            pasc_link->data     = (long*)malloc( pasc_size * sizeof(long) );
            pasc_link->row      = pasc_size-1;                             // 该行行号为该行元素数量-1
            pasc_link->pNext    = NULL;
            
            pasc_link->data[pasc_size-1] = pasc_link->data[0] = 1;         // 该行边界均为1
            for( int i=1;i<=(pasc_size-1-i);i++ ){
                pasc_link->data[i] = pasc_link->data[pasc_size-1-i] = last_data[i] + last_data[i-1];
            }

            last_data           = pasc_link->data;
            pasc_size           = pasc_link->row+2;
        }
    }else{ // =============================================================// 距离最近的那一行位于目标下方
        long   pasc_size = (pOpti->row)-2;                                 // 该行的元素个数为下一行行号-2
        
        while( dis_row_min-- ){
            pasc_link->pNext    = (__Link*)malloc( sizeof(__Link) );       // 新建一行
            pasc_link           = pasc_link->pNext;
            
            pasc_link->data     = (long*)malloc( pasc_size * sizeof(long) );
            pasc_link->row      = pasc_size-1;                             // 该行行号为该行元素数量-1
            pasc_link->pNext    = NULL;
            
            pasc_link->data[pasc_size-1] = pasc_link->data[0] = 1;         // 该行边界均为1
            for( int i=1;i<=(pasc_size-1-i);i++ ){
                pasc_link->data[i] = pasc_link->data[pasc_size-1-i] = last_data[i] - pasc_link->data[i-1];
            }
            
            last_data           = pasc_link->data;
            pasc_size           = pasc_link->row-2;
        }
    }

    return pasc_link->data;
}


// Sample for <GLU_Utility_align_screen> <GLU_Utility_area_hdiv>
__Area_t a = { .xs = 500, .ys = 500, .w = 300, .h = 400 };
__Area_t b = { 0 };

GLU_Utility_align_screen( 400, 300, &b, M_UTILITY_ALIGN_VM | M_UTILITY_ALIGN_HM );

GLU_GUI_autoDisplay(false);


__Area_t c[10] = {
    {.w=10,.h=10},{.w=20,.h=10},{.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10},\
    {.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10},{.w=10,.h=10}
};


GLU_Utility_area_hdiv( &a, c, 10);

GLU_GUI_EX_rect_raw(&a);

GLU_GUI_setPenColor(M_COLOR_RED);
for (int i=0; i<10; i++) {
    GLU_GUI_EX_rect_fill(&c[i]);
    printf("(%d,%d)\n",c[i].xs,c[i].ys);
}
GLU_GUI_refreashScreen();

#endif
