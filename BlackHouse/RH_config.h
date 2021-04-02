#ifndef _RH_CONFIG_H
#define _RH_CONFIG_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GRAPHIC_COLOR_BIN       (0U)  // < option >
#define GRAPHIC_COLOR_RGB565    (1U)  // < option >
#define GRAPHIC_COLOR_RGB888    (2U)  // < option >
#define GRAPHIC_COLOR_TYPE      GRAPHIC_COLOR_BIN // < select >



#define RH_CFG_RECORD_VERSION

#define RH_CFG_GRAPHIC_COLOR_BIN
#define RH_CFG_GRAPHIC_COLOR_RGB565
#define RH_CFG_GRAPHIC_COLOR_RGB888
#define RH_CFG_GRAPHIC_COLOR_TYPE

#define RH_CFG_FONT_DATA_EXTERN_TTF           (0U)  // < option >
#define RH_CFG_FONT_DATA_LOCAL_ARRAY          (1U)  // < option >
#define RH_CFG_FONT_DATA_TYPE                 RH_CFG_FONT_DATA_LOCAL_ARRAY  // < select > < above option >

#define RH_CFG_FONT_STYLE__CourierNew_Italic  (1U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__CourierNew_Bold    (1U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__NewYork            (1U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__NewYork_Italic     (1U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__Arial_Unicode      (1U)  // < select > < 0=disable : 1=enable >


#ifdef __cplusplus
}
#endif

#endif

