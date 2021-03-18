#ifndef _RH_GUI_FONT_H
#define _RH_GUI_FONT_H

#define STB_TRUETYPE_IMPLEMENTATION

#include "RH_common.h"

#ifdef __cpluplus
extern "C"{
#endif


#define FONT_COURIERNEW          1
#define FONT_COURIERNEW_BOLD     1
#define FONT_COURIERNEW_ITALIC   0

extern uint8_t Font_TTF_CourierNew       [684624];
extern uint8_t Font_TTF_CourierNew_Bold  [691796];

typedef enum{
    kGUI_FontStyle_CourierNew        ,
    kGUI_FontStyle_CourierNew_Italic ,
    kGUI_FontStyle_CourierNew_Bold   ,
    kGUI_NUM_FontStyle
}E_GUI_FontStyle_t;

struct __GUI_Font_t{
    uint8_t* output;
    size_t   height;
    size_t   width;
    size_t   space;
    int      ascent;
    int      descent;
    int      lineGap;
};
typedef struct __GUI_Font_t __GUI_Font_t;

void                        MAKE_FUNC( Font, setStyle   )   ( E_GUI_FontStyle_t style   );
void                        MAKE_FUNC( Font, setSize    )    ( int               size    );

int                         MAKE_FUNC( Font, getSize    )  ( void );
E_GUI_FontStyle_t           MAKE_FUNC( Font, getStyle   )  ( void );

__GUI_Font_t*     RH_RESULT MAKE_FUNC( Font, exportChar )  ( uint16_t     unicode );
__GUI_Font_t*     RH_RESULT MAKE_FUNC( Font, exportStr  )  ( const char*  str     );


#ifdef __cpluplus
}
#endif


#endif
