#ifndef _RH_CONFIG_H
#define _RH_CONFIG_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RH_CFG_RECORD_VERSION

#define RH_CFG_GRAPHIC_COLOR_BIN              (0U)                          // < option >
#define RH_CFG_GRAPHIC_COLOR_RGB565           (1U)                          // < option >
#define RH_CFG_GRAPHIC_COLOR_RGB888           (2U)                          // < option >
#define RH_CFG_GRAPHIC_COLOR_TYPE             RH_CFG_GRAPHIC_COLOR_RGB888   // < select > < above option >

#define RH_CFG_FONT_DATA_EXTERN_TTF           (0U)                          // < option >
#define RH_CFG_FONT_DATA_LOCAL_ARRAY          (1U)                          // < option >
#define RH_CFG_FONT_DATA_LOCAL_BITMAP         (2U)                          // < option >
#define RH_CFG_FONT_DATA_TYPE                 (0U)                          // < select > < above option >

#define RH_CFG_OUTPUT_FONT_PNG                (1U)                          // < select > < 0=disable : 1=enable >

#define RH_CFG_FONT_STYLE__CourierNew         (1U)                          // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__CourierNew_Italic  (1U)                          // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__CourierNew_Bold    (1U)                          // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__NewYork            (1U)                          // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__NewYork_Italic     (1U)                          // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__Unscii             (1U)                          // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__Optima             (1U)                          // < select > < 0=disable : 1=enable >
#define RH_CFG_FONT_STYLE__Sign_Printer       (1U)                          // < select > < 0=disable : 1=enable >

#define RH_CFG_SCREEN_HEIGHT                  (480U)                        // < select >
#define RH_CFG_SCREEN_WIDTH                   (800U)                        // < select >

#define RH_CFG_GRAM_INTERNAL                  (0U)                          // < option >
#define RH_CFG_GRAM_EXTADDR                   (1U)                          // < option >
#define RH_CFG_GRAM_EXTSECT                   (2U)                          // < option >
#define RH_CFG_GRAM_EXTPTR                    (3U)                          // < option >
#define RH_CFG_GRAM_TYPE                      RH_CFG_GRAM_INTERNAL          // < select > < above option >

#define RH_CFG_GRAM_ADDRESS                   0x81C00000                    // <   ...  > < only useful when RH_CFG_GRAM_TYPE==RH_CFG_GRAM_EXTADDR >
#define RH_CFG_GRAM_SECTION                   "NonCacheable.init"           // <   ...  > < only useful when RH_CFG_GRAM_TYPE==RH_CFG_GRAM_EXTSECT >
#define RH_CFG_GRAM_POINTER                   s_psBufferLcd                 // <   ...  > < only useful when RH_CFG_GRAM_TYPE==RH_CFG_GRAM_EXTPTR  >
extern void* RH_CFG_GRAM_POINTER;

#define RH_CFG_MALLOC_SIZE__NONE              ((1U)<<0)                     // < option >
#define RH_CFG_MALLOC_SIZE__64B               ((1U)<<6)                     // < option > 
#define RH_CFG_MALLOC_SIZE__128B              ((1U)<<7)                     // < option > 
#define RH_CFG_MALLOC_SIZE__256B              ((1U)<<8)                     // < option >  
#define RH_CFG_MALLOC_SIZE__512B              ((1U)<<9)                     // < option >  
#define RH_CFG_MALLOC_SIZE__1KB               ((1U)<<10)                    // < option >
#define RH_CFG_MALLOC_SIZE__2KB               ((1U)<<11)                    // < option > 
#define RH_CFG_MALLOC_SIZE__4KB               ((1U)<<12)                    // < option > 
#define RH_CFG_MALLOC_SIZE__8KB               ((1U)<<13)                    // < option > 
#define RH_CFG_MALLOC_SIZE__16KB              ((1U)<<14)                    // < option > 
#define RH_CFG_MALLOC_SIZE__32KB              ((1U)<<15)                    // < option > 
#define RH_CFG_MALLOC_SIZE__64KB              ((1U)<<16)                    // < option > 
#define RH_CFG_MALLOC_SIZE__128KB             ((1U)<<17)                    // < option > 
#define RH_CFG_MALLOC_SIZE__256KB             ((1U)<<18)                    // < option > 
#define RH_CFG_MALLOC_SIZE__512KB             ((1U)<<19)                    // < option > 
#define RH_CFG_MALLOC_SIZE__1MB               ((1U)<<20)                    // < option > 
#define RH_CFG_MALLOC_SIZE__2MB               ((1U)<<21)                    // < option > 
#define RH_CFG_MALLOC_SIZE__4MB               ((1U)<<22)                    // < option > 
#define RH_CFG_MALLOC_SIZE__8MB               ((1U)<<23)                    // < option > 
#define RH_CFG_MALLOC_SIZE__16MB              ((1U)<<24)                    // < option > 
#define RH_CFG_MALLOC_SIZE__32MB              ((1U)<<25)                    // < option > 
#define RH_CFG_MALLOC_SIZE__64MB              ((1U)<<26)                    // < option > 
#define RH_CFG_MALLOC_SIZE__128MB             ((1U)<<27)                    // < option > 
#define RH_CFG_MALLOC_SIZE__256MB             ((1U)<<28)                    // < option > 
#define RH_CFG_MALLOC_SIZE__512MB             ((1U)<<29)                    // < option > 
#define RH_CFG_MALLOC_SIZE__1GB               ((1U)<<30)                    // < option > 
#define RH_CFG_MALLOC_SIZE                    RH_CFG_MALLOC_SIZE__NONE      // < select > < above option >

#define RH_CFG_HASHTABLE_SIZE__64B            ((1U)<<6)                     // < option >
#define RH_CFG_HASHTABLE_SIZE__128B           ((1U)<<7)                     // < option >
#define RH_CFG_HASHTABLE_SIZE__256B           ((1U)<<8)                     // < option >
#define RH_CFG_HASHTABLE_SIZE__512B           ((1U)<<9)                     // < option >
#define RH_CFG_HASHTABLE_SIZE__1KB            ((1U)<<10)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__2KB            ((1U)<<11)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__4KB            ((1U)<<12)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__8KB            ((1U)<<13)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__16KB           ((1U)<<14)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__32KB           ((1U)<<15)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__64KB           ((1U)<<16)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__128KB          ((1U)<<17)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__256KB          ((1U)<<18)                    // < option >
#define RH_CFG_HASHTABLE_SIZE__512KB          ((1U)<<19)                    // < option >
#define RH_CFG_HASHTABLE_SIZE                 RH_CFG_HASHTABLE_SIZE__64B    // < select > < above option >


// Select or use your own function.
#ifndef RH_ASSERT
  #define RH_ASSERT( expr )                   assert( expr )
  #define STBTT_assert(expr)                  RH_ASSERT(expr)
#else
  #error " 'RH_ASSERT' has been defined. "
#endif

#ifndef RH_WAIT
#define RH_WAIT( expr )                       do{ if( expr ){\
                                                      printf("@%s Ln:%d\nPress <enter> to continue\n",__FILE__,__LINE__);\
                                                      getchar();\
                                                  }\
                                              }while(0)
#endif

#ifndef RH_CALLOC
  #define RH_CALLOC(x,size)                   calloc(x,size)//BLK_FUNC( Memory, debug_print )( BLK_FUNC( Memory, debug_calloc )(x,size,__FILE__,__LINE__,calloc), NULL )
#else
  #error " 'RH_CALLOC' has been defined. "
#endif

#ifndef RH_MALLOC
//#include "BLK_lib.h"
  #define RH_MALLOC(x)                        malloc(x)//BLK_FUNC( Memory, debug_print )( BLK_FUNC( Memory, debug_malloc )(x, __FILE__, __LINE__, malloc), NULL )

#else
  #error " 'RH_MALLOC' has been defined. "
#endif

#ifndef RH_FREE
  #define RH_FREE(x)                          free(x)//BLK_FUNC( Memory, debug_free )(x,free)
#else
  #error " 'RH_FREE' has been defined. "
#endif

#define BLK_POKER_CALLOC(x,s)          calloc(x,s)
#define BLK_POKER_MALLOC(x)            malloc(x)
#define BLK_POKER_FREE(x)              free(x)
#define BLK_POKER_ASSERT(expr)         assert(expr)

#define BLK_DATA_CALLOC(x,s)           calloc(x,s)
#define BLK_DATA_MALLOC(x)             malloc(x)
#define BLK_DATA_FREE(x)               free(x)
#define BLK_DATA_ASSERT(expr)          assert(expr)
#define BLK_DATA_HASH_CALLOC(x,s)      calloc(x,s)
#define BLK_DATA_HASH_MALLOC(x)        malloc(x)
#define BLK_DATA_HASH_FREE(x)          free(x)

#define BLK_DSP_CALLOC(x,s)            calloc(x,s)
#define BLK_DSP_MALLOC(x)              malloc(x)
#define BLK_DSP_FREE(x)                free(x)
#define BLK_DSP_ASSERT(expr)           assert(expr)

#define BLK_GRAPH_CALLOC(x,s)          calloc(x,s)
#define BLK_GRAPH_MALLOC(x)            malloc(x)
#define BLK_GRAPH_FREE(x)              free(x)
#define BLK_GRAPH_ASSERT(expr)         assert(expr)



#ifdef __cplusplus
}
#endif

#endif

