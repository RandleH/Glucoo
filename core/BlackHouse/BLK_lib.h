

#ifndef _BLK_LIB_H
#define _BLK_LIB_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================================================================
 > Standard
============================================================================================================================*/
#define     __rm_BIT      ( x , n )    ((x)&(~(1<<(n))))
#define     __rm_LSB_BIT  ( x )        ((x)&((x)-1))
#define     __gt_LSB_BIT  ( x )        ((x)&((~(x))+1))

uint8_t     BLK_FUNC( Bit, swap8    ) (uint8_t   x);
uint16_t    BLK_FUNC( Bit, swap16   ) (uint16_t  x);
uint32_t    BLK_FUNC( Bit, swap32   ) (uint32_t  x);
uint32_t    BLK_FUNC( Bit, swapN    ) (uint32_t  x , size_t n);
uint32_t    BLK_FUNC( Bit, swap     ) (uint32_t  x);

size_t      BLK_FUNC( Bit, BINs     ) (uint32_t  x);
size_t      BLK_FUNC( Bit, OCTs     ) (uint32_t  x);
size_t      BLK_FUNC( Bit, DECs     ) (uint32_t  x);
size_t      BLK_FUNC( Bit, HEXs     ) (uint32_t  x);
 
uint32_t    BLK_FUNC( Bit, bin2gray ) (uint32_t  x);
uint32_t    BLK_FUNC( Bit, gray2bin ) (uint32_t  x); //

const char* BLK_FUNC( Bin, itoa )   (uint8_t   x); // btoa_BIN
const char* BLK_FUNC( Bin, ltoa )   (uint32_t  x);
const char* BLK_FUNC( Bin, ftoa )   (float     x); // ftoa_BIN

/*===========================================================================================================================
 > Sort Programming Reference
============================================================================================================================*/
int BLK_FUNC( Sort, insert ) (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
int BLK_FUNC( Sort, shell  ) (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
int BLK_FUNC( Sort, quick  ) (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

/*===========================================================================================================================
 > Memory Programming Reference
============================================================================================================================*/

extern size_t BLK_GVAR( memoryAllocated );
extern size_t BLK_GVAR( memoryFree      );
extern size_t RH_Global_alloced_byte;
extern size_t RH_Global_free_byte;
void* BLK_FUNC( Memory, malloc ) ( size_t size  );
void* BLK_FUNC( Memory, calloc ) ( size_t count  , size_t size);
void  BLK_FUNC( Memory, free   ) ( void* ptr    );

extern size_t BLK_GVAR( debug_memoryAllocated );
extern size_t BLK_GVAR( debug_memoryFree      );
extern size_t RH_Debug_alloced_byte;
extern size_t RH_Debug_free_byte;
void* BLK_FUNC( Memory, debug_malloc   ) ( size_t size               , char* FILE, int LINE, void* (*__malloc_func)( size_t         ) );
void* BLK_FUNC( Memory, debug_calloc   ) ( size_t count , size_t size, char* FILE, int LINE, void* (*__calloc_func)( size_t, size_t ) );
void  BLK_FUNC( Memory, debug_free     ) ( void*  ptr                , void  (*__free_func  )(void*  )          );
void* BLK_FUNC( Memory, debug_print    ) ( void*  ptr                , int   (*__print_func )(const char * restrict format, ...));
void  BLK_FUNC( Memory, debug_delCache ) ( void );


void* __memsetWORD  (void* __b, uint16_t value, size_t num);
void* __memsetDWORD (void* __b, uint32_t value, size_t num);
void* __memexch     (void* __a, void* __b, size_t size );

void* __memset_Area (void*                __b,int                      value,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);
void* __memcpy_Area (void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);
void* __memgrab_Area(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);

#include "RH_config.h"

#ifdef __cplusplus
}
#endif

#endif

