

#ifndef _RH_COMMON_H
#define _RH_COMMON_H
#define _BLACK_HOUSE_SUPPORT_

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>
#include <setjmp.h>
#include <signal.h>
#include <limits.h>
#include <math.h>
#include <complex.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

#ifdef __x86_64
#include <memory.h>
#endif
//#include <malloc.h>
#include "RH_config.h"

#ifdef __cplusplus
 extern "C" {
#endif
 
#pragma anon_unions
 
#define RH_DEBUG
 
typedef enum{
    kStatus_Success    ,
    kStatus_Busy       ,
    kStatus_BadAccess  ,
    kStatus_Denied     ,
    kStatus_Exist      ,
    kStatus_NoSpace    ,
    kStatus_ErrorID    ,
    kStatus_NotFound   ,
    kStatus_Warning    ,
    kStatus_Empty
}E_Status_t;
 
struct __Region_t{
    int    xs;
    int    ys;
    size_t width;
    size_t height;
};
typedef struct __Region_t __Region_t;
typedef struct __Region_t __Area_t;
 
 

 
#define RH_RESULT     __attribute__((warn_unused_result))
#define RH_PREMAIN    //__attribute__((constructor))
#define RH_AFTMAIN    __attribute__((destructor))
#define RH_FUNCONST   __attribute__((const))
#define RH_WEAK       __attribute__((weak))
 
#ifndef __restrict__
#define __restrict__ __restrict
#endif
 
#define MAKE_FUNC( class , method )          __##class##_##method  // Function like this: __XXXX_xxxxx();
#define CALL_FUNC                            MAKE_FUNC             // exactly the same but has semantic difference.
 
#ifndef M_2_SQRTPI
#define M_2_SQRTPI    1.12837916709551257389615890312154517   /* 2/sqrt(pi)     */
#endif

#ifndef M_SQRT2
#define M_SQRT2       1.41421356237309504880168872420969808   /* sqrt(2)        */
#endif
 
#ifndef M_2_PI
#define M_2_PI        6.28318530717958623199592693708837032   /* 2*pi           */
#endif

#ifndef M_PI
#define M_PI          3.14159265358979323846264338327950288   /* pi             */
#endif

#ifndef M_PI_2
#define M_PI_2        1.57079632679489661923132169163975144   /* pi/2           */
#endif

#ifndef M_PI_4
#define M_PI_4        0.785398163397448309615660845819875721  /* pi/4           */
#endif
 
#ifndef M_ATAN_1_2
#define M_ATAN_1_2    26.565051177078                         /* arctan(1/2)    */
#endif
 
#ifndef M_ATAN_1_4
#define M_ATAN_1_4    14.0362434679265                        /* arctan(1/4)    */
#endif
 
#ifndef M_ATAN_1_8
#define M_ATAN_1_8    7.1250163489018                         /* arctan(1/8)    */
#endif
 
#ifndef M_ATAN_1_16
#define M_ATAN_1_16   3.57633437499735                         /* arctan(1/16)  */
#endif

#ifndef M_ATAN_1_32
#define M_ATAN_1_32   1.78991060824607                        /* arctan(1/32)   */
#endif

#ifndef M_ATAN_1_64
#define M_ATAN_1_64   0.8951737102111                         /* arctan(1/64)   */
#endif

#ifndef M_ATAN_1_128
#define M_ATAN_1_128  0.4476141708606                         /* arctan(1/128)  */
#endif

#ifndef M_ATAN_1_256
#define M_ATAN_1_256  0.2238105003685                         /* arctan(1/256)  */
#endif


typedef uint8_t                 u8;
typedef uint16_t                u16;
typedef uint32_t                u32;
typedef uint64_t                u64;

typedef int8_t                  i8;
typedef int16_t                 i16;
typedef int32_t                 i32;
typedef int64_t                 i64;

typedef volatile int8_t         vi8;
typedef volatile int16_t        vi16;
typedef volatile int32_t        vi32;
typedef volatile int64_t        vi64;

typedef volatile uint8_t        vu8;
typedef volatile uint16_t       vu16;
typedef volatile uint32_t       vu32;
typedef volatile uint64_t       vu64;

 

 
#ifndef __map
  #define __map(val,i_min,i_max,o_min,o_max)   (double)( ( ((double)o_max)*(((double)val)-((double)i_min))+((double)o_min)*((double)(i_max)-(double)(val)) )/((double)(i_max)-(double)(i_min)) )
#else
  #error " '__map' has been defined. "
#endif

#ifndef __swap
  #define __swap(a,b)                          do{a=a^b;b=a^b;a=a^b;}while(0)
#else
  #error " '__swap' has been defined. "
#endif

#ifndef __abs
#define __abs(val)                             (((val)>0)?(val):(-(val)))
#else
  #error " '__abs' has been defined. "
#endif

#ifndef __limit
  #define __limit(a, lowerbound, upperbound)   (((a) >= (upperbound)) ? upperbound : (((a) <= (lowerbound)) ? (lowerbound) : (a) ))
#else
  #error " '__limit' has been defined. "
#endif

#ifndef __min
  #define __min(a,b)                           (((a)<(b))?(a):(b))
#else
  // #pragma message (" '__min' has been defined. ")
#endif

#ifndef __max
  #define __max(a,b)                           (((a)>(b))?(a):(b))
#else
  // #pragma message (" '__max' has been defined. ")
#endif

#ifndef __mid
  #define __mid(a,b)                           (((a)<(b))?((a)+(((b)-(a)+1)>>1)):((b)+(((a)-(b)+1)>>1)) )
#else
  #error " '__mid' has been defined. "
#endif
 
#ifndef __exit
  #define __exit(express)                      if( express )   return
#else
  #error " '__exit' has been defined. "
#endif

#ifndef __exitReturn
  #define __exitReturn(express,res)            if( express )   return res
#else
  #error " '__exitReturn' has been defined. "
#endif
 
#ifndef __abort
  #define __abort(express)                     if( express )   while(1)
#else
  #error " '__abort' has been defined. "
#endif

#ifndef __array1D
  #define __array1D(ptr,width,y,x)             (((ptr)+(width)*(y)+(x)))
#else
  #error " '__array1D' has been defined. "
#endif

#ifndef __array2D
  #define __array2D(ptr,width,y,x)             (((ptr[0])+(width)*(y)+(x)))
#else
  #error " '__array2D' has been defined. "
#endif
 



 
#define __BIT_GET( x , b )                   (((x)>>(b)) & 0x01   )
 
#define __BIT_SET( x , b )                   ((x) | (   1<<(b)    ) )
#define __BIT_CLR( x , b )                   ((x) & ( ~(1<<(b))   ) )
 
#define __MEM_BYTE( adr )                    ( (*( (uint8_t* )(adr) )) )
#define __MEM_WORD( adr )                    ( (*( (uint16_t*)(adr) )) )
       
#define __PTR_BYTE( var )                    ( (uint8_t*  ) (void* ) (&(var)) )
#define __PTR_WORD( var )                    ( (uint16_t* ) (void* ) (&(var)) )
#define __PTR_TYPE( var, type )              ( (type*     ) (void* ) (&(var)) )
      
#define __WORD_HI( var )                     (uint8_t ) ( (uint8_t ) ( (uint16_t)(var) >> 8     ) )
#define __WORD_LO( var )                     (uint8_t ) ( (uint8_t ) ( (uint16_t)(var) & 0xff   ) )
#define __DWORD_HI( var )                    (uint16_t) ( (uint16_t) ( (uint32_t)(var) >> 16    ) )
#define __DWORD_LO( var )                    (uint16_t) ( (uint16_t) ( (uint32_t)(var) & 0xffff ) )

#define __SWAP_WORD( var )                   ((uint16_t) ( (((uint16_t )(var)) << 8  )|( ((uint16_t)(var)) >> 8  ) ))
#define __SWAP_DWORD( var )                  ((uint32_t) (( __SWAP_WORD(((uint32_t)(var))&0x0000ffff)<<16 ) | ( __SWAP_WORD(((uint32_t)(var))>>16) )))
      
#define __RND4( x )                          ( ( ((x)+3)  >>2 )<<2 )
#define __RND8( x )                          ( ( ((x)+7)  >>3 )<<3 )
#define __RND16( x )                         ( ( ((x)+15) >>4 )<<4 )
      
#define __UPCASE( c )                        ( ((c) >= 'a' && (c) <= 'z') ? ((c)-0x20) : (c) )
      
#define __INC_SAT( val )                     ( ( ((val)+1) > (val) ) ? ((val)+1) : (val) )
 
#define __SET_STRUCT_MB( s_type, var_type, s_ptr, s_mem, val )   *( (var_type*) ( ((unsigned char*)(s_ptr))+(offsetof(s_type, s_mem)) ) ) = (var_type)(val)

#define __IN_BYTE   ( port )                 ( *((volatile uint8_t*  )(port)) )
#define __IN_WORD   ( port )                 ( *((volatile uint16_t* )(port)) )
#define __IN_DWORD  ( port )                 ( *((volatile uint32_t* )(port)) )

#define __IN_8BIT   ( port )                 __IN_BYTE  ( port )
#define __IN_16BIT  ( port )                 __IN_WORD  ( port )
#define __IN_32BIT  ( port )                 __IN_DWORD ( port )
      
#define __OUT_BYTE  ( port, val )            ( *((volatile uint8_t*  )(port)) = ((uint8_t )(val)) )
#define __OUT_WORD  ( port, val )            ( *((volatile uint16_t* )(port)) = ((uint16_t)(val)) )
#define __OUT_DWORD ( port, val )            ( *((volatile uint32_t* )(port)) = ((uint32_t)(val)) )

#define __OUT_8BIT  ( port, val )            __OUT_BYTE  ( port, val )
#define __OUT_16BIT ( port, val )            __OUT_WORD  ( port, val )
#define __OUT_32BIT ( port, val )            __OUT_DWORD ( port, val )


#ifdef __cplusplus
 }
#endif


#endif
