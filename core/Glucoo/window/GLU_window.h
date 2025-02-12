#ifndef _GLU_WINDOW_H
#define _GLU_WINDOW_H

#include "GLU_font.h"
#include "GLU_glucoo.h"





struct tGluWindow{
    __Area_t             area;
    E_GUI_WindowStyle_t  type;
    tGluThemeEnum   appearance;
    var                  size;
    
    const char*          title;
    GLU_ENUM(Font)       title_font;
    
    const char*          text;
    GLU_ENUM(Font)       text_font;
    GLU_ENUM(Align)    text_align;
    var                  text_size;
    //...//
    
    const void*  const   text_bitMap;  // DO NOT MODIFY
    const var            text_bitH;    // DO NOT MODIFY
    const var            text_bitW;    // DO NOT MODIFY
    const var            text_rs;      // DO NOT MODIFY
    const var            text_margin;  // DO NOT MODIFY
    
    const var            win_edge;     // DO NOT MODIFY
    
    void (*insert_func)(struct tGluWindow*);  // DO NOT MODIFY
    void (*remove_func)(struct tGluWindow*);  // DO NOT MODIFY
};
typedef struct tGluWindow tGluWindow;


#endif

