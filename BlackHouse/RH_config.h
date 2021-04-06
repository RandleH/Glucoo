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

#define RH_CFG_FONT_DATA_EXTERN_TTF           (0U)                          // < option >
#define RH_CFG_FONT_DATA_LOCAL_ARRAY          (1U)                          // < option >
#define RH_CFG_FONT_DATA_LOCAL_BITMAP         (2U)                          // < option >
#define RH_CFG_FONT_DATA_TYPE                 RH_CFG_FONT_DATA_LOCAL_ARRAY  // < select > < above option >



#define RH_CFG_FONT_STYLE__CourierNew         (0U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__CourierNew_Italic  (0U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__CourierNew_Bold    (0U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__NewYork            (0U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__NewYork_Italic     (0U)  // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__Arial_Unicode      (0U)  // < select > < 0=disable : 1=enable >


#define RH_CFG_MALLOC_SIZE__NONE              ((1U)<<0)                 // < option >
#define RH_CFG_MALLOC_SIZE__64B               ((1U)<<6)                 // < option > 
#define RH_CFG_MALLOC_SIZE__128B              ((1U)<<7)                 // < option > 
#define RH_CFG_MALLOC_SIZE__256B              ((1U)<<8)                 // < option >  
#define RH_CFG_MALLOC_SIZE__512B              ((1U)<<9)                 // < option >  
#define RH_CFG_MALLOC_SIZE__1KB               ((1U)<<10)                // < option >
#define RH_CFG_MALLOC_SIZE__2KB               ((1U)<<11)                // < option > 
#define RH_CFG_MALLOC_SIZE__4KB               ((1U)<<12)                // < option > 
#define RH_CFG_MALLOC_SIZE__8KB               ((1U)<<13)                // < option > 
#define RH_CFG_MALLOC_SIZE__16KB              ((1U)<<14)                // < option > 
#define RH_CFG_MALLOC_SIZE__32KB              ((1U)<<15)                // < option > 
#define RH_CFG_MALLOC_SIZE__64KB              ((1U)<<16)                // < option > 
#define RH_CFG_MALLOC_SIZE__128KB             ((1U)<<17)                // < option > 
#define RH_CFG_MALLOC_SIZE__256KB             ((1U)<<18)                // < option > 
#define RH_CFG_MALLOC_SIZE__512KB             ((1U)<<19)                // < option > 
#define RH_CFG_MALLOC_SIZE__1MB               ((1U)<<20)                // < option > 
#define RH_CFG_MALLOC_SIZE__2MB               ((1U)<<21)                // < option > 
#define RH_CFG_MALLOC_SIZE__4MB               ((1U)<<22)                // < option > 
#define RH_CFG_MALLOC_SIZE__8MB               ((1U)<<23)                // < option > 
#define RH_CFG_MALLOC_SIZE__16MB              ((1U)<<24)                // < option > 
#define RH_CFG_MALLOC_SIZE__32MB              ((1U)<<25)                // < option > 
#define RH_CFG_MALLOC_SIZE__64MB              ((1U)<<26)                // < option > 
#define RH_CFG_MALLOC_SIZE__128MB             ((1U)<<27)                // < option > 
#define RH_CFG_MALLOC_SIZE__256MB             ((1U)<<28)                // < option > 
#define RH_CFG_MALLOC_SIZE__512MB             ((1U)<<29)                // < option > 
#define RH_CFG_MALLOC_SIZE__1GB               ((1U)<<30)                // < option > 
#define RH_CFG_MALLOC_SIZE                    RH_CFG_MALLOC_SIZE__NONE  // < select > < above option >

#define RH_CFG_OUTPUT_FONT_PNG                (1U)                      // < select > < 0=disable : 1=enable >



#ifdef __cplusplus
}
#endif

#endif

