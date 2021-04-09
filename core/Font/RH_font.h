#ifndef _RH_GUI_FONT_H
#define _RH_GUI_FONT_H


#include "RH_common.h"
#include "RH_config.h"

#ifdef __cpluplus
extern "C"{
#endif


#if   ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_EXTERN_TTF )

#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_ARRAY )
    extern uint8_t Font_TTF_ArialRoundedBold [49296];
    #if RH_CFG_FONT_STYLE__CourierNew
    extern uint8_t Font_TTF_CourierNew       [684624];
    #endif
    #if RH_CFG_FONT_STYLE__CourierNew_Bold
    extern uint8_t Font_TTF_CourierNew_Bold  [691796];
    #endif
#elif ( RH_CFG_FONT_DATA_TYPE == RH_CFG_FONT_DATA_LOCAL_BITMAP )

#else

  #error "Unknown font data source."
#endif


struct rhtt_fontinfo{
    uint8_t   h;
    uint8_t   w;
    char      c;
    uint8_t   *data; 
};
typedef struct rhtt_fontinfo rhtt_fontinfo;

typedef enum{
    kGUI_FontStyle_ArialRounded_Bold ,
    
#if RH_CFG_FONT_STYLE__CourierNew
    kGUI_FontStyle_CourierNew        ,
#endif
#if RH_CFG_FONT_STYLE__CourierNew_Italic
    kGUI_FontStyle_CourierNew_Italic ,
#endif
#if RH_CFG_FONT_STYLE__CourierNew_Bold
    kGUI_FontStyle_CourierNew_Bold   ,
#endif
#if RH_CFG_FONT_STYLE__NewYork
    kGUI_FontStyle_NewYork           ,
#endif
#if RH_CFG_FONT_STYLE__NewYork_Italic
    kGUI_FontStyle_NewYork_Italic    ,
#endif
#if RH_CFG_FONT_STYLE__Arial_Unicode
    kGUI_FontStyle_Arial_Unicode     ,
#endif
    kGUI_NUM_FontStyle
}E_GUI_FontStyle_t;

typedef enum{
    kGUI_FontAlign_Right   ,
    kGUI_FontAlign_Left    ,
    kGUI_FontAlign_Middle  ,
    kGUI_FontAlign_Justify
}E_GUI_FontAlign_t;

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

void             RH_PREMAIN MAKE_FUNC( Font, init           ) (void);

void                        MAKE_FUNC( Font, setStyle       ) ( E_GUI_FontStyle_t style   );
void                        MAKE_FUNC( Font, setSize        ) ( size_t            size    );

size_t                      MAKE_FUNC( Font, getSize        ) ( void );
E_GUI_FontStyle_t           MAKE_FUNC( Font, getStyle       ) ( void );

void                        MAKE_FUNC( Font, backup_config  ) (void);
void                        MAKE_FUNC( Font, restore_config ) (void);

__GUI_Font_t*     RH_RESULT MAKE_FUNC( Font, exportChar     ) ( uint16_t     unicode );
__GUI_Font_t*     RH_RESULT MAKE_FUNC( Font, exportStr      ) ( const char*  str     );

void                        MAKE_FUNC( Font, getCharSize    ) ( size_t *width, size_t *height, char c );
int                         MAKE_FUNC( Font, getWordNum     ) ( const size_t width, const char* str   );

__GUI_Font_t*               MAKE_FUNC( Font, exportText_Justify )( const char* str, size_t width );

#ifdef __cpluplus
}
#endif


#endif
