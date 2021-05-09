

#ifndef _RH_LIB_H
#define _RH_LIB_H

#include "RH_common.h"
#include "RH_config.h"
#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================================================================
 > Standard
============================================================================================================================*/
#define     __rm_BIT      ( x , n )    ((x)&(~(1<<(n))))
#define     __rm_LSB_BIT  ( x )        ((x)&((x)-1))
#define     __gt_LSB_BIT  ( x )        ((x)&((~(x))+1))


uint8_t     __swap_8BIT   (uint8_t   x);
uint16_t    __swap_16BIT  (uint16_t  x);
uint32_t    __swap_32BIT  (uint32_t  x);
uint32_t    __swap_nBIT   (uint32_t  x , size_t n);
uint32_t    __swap_DATA   (uint32_t  x);

 
size_t      __sizeof_BINs (uint32_t  x);
size_t      __sizeof_OCTs (uint32_t  x);
size_t      __sizeof_DECs (uint32_t  x);
size_t      __sizeof_HEXs (uint32_t  x);
 
uint32_t    __Bin2Gray    (uint32_t  x);
uint32_t    __Gray2Bin    (uint32_t  x); //

const char* __btoa_BIN    (uint8_t   x); // btoa_BIN
const char* __ldtoa_BIN   (uint32_t  x);
const char* __ftoa_BIN    (float     x); // ftoa_BIN

/*===========================================================================================================================
 > Sort Programming Reference
============================================================================================================================*/
int __insertsort (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
int __shellsort  (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

/*===========================================================================================================================
 > Memory Programming Reference
============================================================================================================================*/

extern size_t RH_Global_alloced_byte;
extern size_t RH_Global_free_byte;
void* __RH_Global_malloc ( size_t size  );
void* __RH_Global_calloc ( size_t count  , size_t size);
void  __RH_Global_free   ( void* ptr    );

extern size_t RH_Debug_alloced_byte;
extern size_t RH_Debug_free_byte;
void* __RH_Debug_malloc  ( size_t size               , char* FILE, int LINE, void* (*__malloc_func)( size_t         ) );
void* __RH_Debug_calloc  ( size_t count , size_t size, char* FILE, int LINE, void* (*__calloc_func)( size_t, size_t ) );
void  __RH_Debug_free    ( void*  ptr                , void  (*__free_func  )(void*  )          );

void* __RH_Debug_print_memory_info(void* ptr, int (*__print_func)(const char * restrict format, ...));
void  __RH_Debug_del_cache_info(void);


void* __memsetWORD  (void* __b, uint16_t value, size_t num);
void* __memsetDWORD (void* __b, uint32_t value, size_t num);
void* __memexch     (void* __a, void* __b, size_t size );

void* __memset_Area (void*                __b,int                      value,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);
void* __memcpy_Area (void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);
void* __memgrab_Area(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye);

#ifdef __cplusplus
}
#endif

#endif

