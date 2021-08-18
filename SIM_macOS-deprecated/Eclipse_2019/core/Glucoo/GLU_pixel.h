#ifndef _GLU_PIXEL_H
#define _GLU_PIXEL_H

#include "RH_config.h"
#include "BLK_image.h"

#if   ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_BIN    )
typedef BLK_SRCT(ImgBin)       GLU_SRCT(Canvas);
typedef BLK_UION(PixelBin)     GLU_UION(Pixel);
typedef BLK_TYPE(PixelBin)     GLU_TYPE(Pixel);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB565 )
typedef BLK_SRCT(Img565)       GLU_SRCT(Canvas);
typedef BLK_UION(Pixel565)     GLU_UION(Pixel);
typedef BLK_TYPE(Pixel565)     GLU_TYPE(Pixel);
#elif ( RH_CFG_GRAPHIC_COLOR_TYPE == RH_CFG_GRAPHIC_COLOR_RGB888 )
typedef BLK_SRCT(Img888)       GLU_SRCT(Canvas);
typedef BLK_UION(Pixel888)     GLU_UION(Pixel);
typedef BLK_TYPE(Pixel888)     GLU_TYPE(Pixel);
#else
  #error "[RH_gui_config]: Unknown color type."
#endif



typedef uint32_t GLU_TYPE(Color);

#endif
