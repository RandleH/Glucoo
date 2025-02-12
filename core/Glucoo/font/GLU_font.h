#ifndef _GLU_FONT_H
#define _GLU_FONT_H


#include "RH_common.h"
#include "RH_config.h"

#include "BLK_graphic.h"
#include "GLU_pixel.h"
// #include "GLU_render.h"
#include "GLU_glucoo.h"

#ifdef __cpluplus
extern "C"{
#endif



struct rhtt_fontinfo{
    uint8_t   h;
    uint8_t   w;
    char      c;
    uint8_t   *data;
};
typedef struct rhtt_fontinfo rhtt_fontinfo;


struct tGluFontImg{
    uint8_t* img_buf;
    var      img_h;
    var      img_w;
};
typedef struct tGluFontImg tGluFontImg;

void RH_PREMAIN glu_font_init(void);

void glu_font_set_style( tGluFontEnum font);
void glu_font_set_size( uint16_t size);
uint8_t glu_font_get_size (void);
tGluFontEnum glu_font_get_style(void);
void glu_font_backup_cache(void);
void glu_font_restore_cache(void);

tGluFontImg*  RH_RESULT RH_NULLABLE glu_font_out_chr_img ( uint16_t    chr);
tGluFontImg*  RH_RESULT RH_NULLABLE glu_font_out_str_img ( const char* str);
tGluFontImg*  RH_RESULT RH_NULLABLE glu_font_out_txt_img ( const char* str, size_t width, tGluTextAlignEnum align);

void glu_font_get_chr_img_info( var RH_NULLABLE *width, var RH_NULLABLE *height, char        c   );
void glu_font_get_str_img_info( var RH_NULLABLE *width, var RH_NULLABLE *height, const char* str );
int  glu_font_get_str_word_cnt( var width, const char* str );



#ifdef __cpluplus
}
#endif


#endif
