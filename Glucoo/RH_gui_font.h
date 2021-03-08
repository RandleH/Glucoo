#ifndef _RH_GUI_FONT_H
#define _RH_GUI_FONT_H

#define STB_TRUETYPE_IMPLEMENTATION

#include "RH_common.h"

#ifdef __cpluplus
extern "C"{
#endif

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

void              GUI_SetFontStyle   ( E_GUI_FontStyle_t style   );
void              GUI_SetFontSize    ( int               size    );

int               GUI_GetFontSize    ( void );
E_GUI_FontStyle_t GUI_GetFontStyle   ( void );

__GUI_Font_t*     __attribute__((warn_unused_result)) GUI_ExportFontChar ( uint16_t          unicode );
__GUI_Font_t*     __attribute__((warn_unused_result)) GUI_ExportFontStr  ( const char*       str     );


#ifdef __cpluplus
}
#endif


#endif
