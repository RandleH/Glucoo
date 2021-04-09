
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

#if   ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_BIN    )

#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB565 )

#elif ( GRAPHIC_COLOR_TYPE == GRAPHIC_COLOR_RGB888 )

#else
  #error "[RH_graphic]: Unknown color type."
#endif

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

#endif



