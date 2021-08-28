#ifndef _GLU_IMAGE_H
#define _GLU_IMAGE_H

#include "RH_config.h"
#include "RH_common.h"
#include "GLU_pixel.h"
#include "GLU_glucoo.h"
#include "GLU_font.h"

#ifdef __cplusplus
extern "C"{
#endif

enum GLU_ENUM(ImageStyle){
    kGLU_ImageStyle_aurora ,
    kGLU_ImageStyle_blur   ,
    NUM_kGLU_ImageStyles   ,
};
typedef enum GLU_ENUM(ImageStyle) GLU_ENUM(ImageStyle);

void GLU_FUNC( Image, profile )( GLU_ENUM(ImageStyle) style, const GLU_TYPE(Color)* colors, uint8_t size, const GLU_SRCT(Text)* RH_NULLABLE text, uint8_t alpha_100 );




#ifdef __cplusplus
}
#endif

#endif
