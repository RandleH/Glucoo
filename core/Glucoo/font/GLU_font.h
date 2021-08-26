#ifndef _GLU_FONT_H
#define _GLU_FONT_H


#include "RH_common.h"
#include "RH_config.h"
#include "GLU_pixel.h"
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







struct GLU_SRCT(FontImg){
    uint8_t* img_buf;
    var      img_h;
    var      img_w;
};
typedef struct GLU_SRCT(FontImg) GLU_SRCT(FontImg);

void                RH_PREMAIN            GLU_FUNC( Font, init           ) ( void );
           
void                                      GLU_FUNC( Font, set_font       ) ( GLU_ENUM(Font) font   );
void                                      GLU_FUNC( Font, set_size       ) ( uint16_t       size   );
           
uint8_t                                   GLU_FUNC( Font, get_size       ) ( void );
GLU_ENUM(Font)                            GLU_FUNC( Font, get_font       ) ( void );
           
void                                      GLU_FUNC( Font, backupCache    ) ( void );
void                                      GLU_FUNC( Font, restoreCache   ) ( void );

GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC( Font, out_chr_Img    ) ( uint16_t    chr );
GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC( Font, out_str_Img    ) ( const char* str );
GLU_SRCT(FontImg)*  RH_RESULT RH_NULLABLE GLU_FUNC( Font, out_txt_Img    ) ( const char* str, size_t width, GLU_ENUM(Align) align );

void                                      GLU_FUNC( Font, get_chr_ImgInfo) ( var RH_NULLABLE *width, var RH_NULLABLE *height, char        c   );
void                                      GLU_FUNC( Font, get_str_ImgInfo) ( var RH_NULLABLE *width, var RH_NULLABLE *height, const char* str );
           
int                                       GLU_FUNC( Font, get_str_WordCnt) ( var width, const char* str );



#ifdef __cpluplus
}
#endif


#endif
