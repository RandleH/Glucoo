
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

#endif
