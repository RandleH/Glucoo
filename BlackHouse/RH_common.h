

#ifndef _RH_COMMON_H
#define _RH_COMMON_H
#define _BLACK_HOUSE_SUPPORT_

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <wchar.h>
#include <setjmp.h>
#include <signal.h>
#include <limits.h>
#include <math.h>
#include <complex.h>
#include <errno.h>

#ifdef __cplusplus
 extern "C" {
#endif
 
#pragma anon_unions
 
typedef enum{
    kStatus_Success    ,
    kStatus_Busy       ,
    kStatus_BadAccess  ,
    kStatus_Denied     ,
    kStatus_Exist      ,
    kStatus_NoSpace    ,
    kStatus_ErrorID    ,
    kStatus_NotFound   ,
}E_Status_t;
  
 
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
 
 
#define __map(val,i_min,i_max,o_min,o_max)   (double)( ( ((double)o_max)*(((double)val)-((double)i_min))+((double)o_min)*((double)(i_max)-(double)(val)) )/((double)(i_max)-(double)(i_min)) )

#define __abs(val)                           (((val)>0)?(val):(-(val)))
#define __limit(a, lowerbound, upperbound)   (((a) >= (upperbound)) ? upperbound : (((a) <= (lowerbound)) ? (lowerbound) : (a) ))

#ifndef __min
#define __min(a,b)                           (((a)<(b))?(a):(b))
#endif

#ifndef __max
#define __max(a,b)                           (((a)>(b))?(a):(b))
#endif

#ifndef __mid
#define __mid(a,b)                           (((a)<(b))?((a)+(((b)-(a)+1)>>1)):((b)+(((a)-(b)+1)>>1)) )
#endif
 
#ifndef __exit
#define __exit(express)                      if( express )   return
#endif

#ifndef __exitReturn
#define __exitReturn(express,res)            if( express )   return res
#endif
 
#define __array1D(ptr,width,y,x)             (((ptr)+(width)*(y)+(x)))
#define __array2D(ptr,width,y,x)             (((ptr[0])+(width)*(y)+(x)))

#define __malloc(x)                          malloc(x)  //__mallocHEAP(x)
#define __free(x)                            free(x)    //__freeHEAP(x)
 
 
#define __MEM_BYTE( adr )              ( (*( (uint8_t* )(adr) )) )
#define __MEM_WORD( adr )              ( (*( (uint16_t*)(adr) )) )
 
#define __PTR_BYTE( var )              ( (uint8_t* ) (void* ) (&(var)) )
#define __PTR_WORD( var )              ( (uint8_t* ) (void* ) (&(var)) )

#define __WORD_HI( var )               ( (uint8_t)( (uint16_t)(var) >> 8   ) )
#define __WORD_LO( var )               ( (uint8_t)( (uint16_t)(var) & 0xff ) )

#define __RND4 ( x )                   ( ( ((x)+3)  >>2 )<<2 )
#define __RND8 ( x )                   ( ( ((x)+7)  >>3 )<<3 )
#define __RND16( x )                   ( ( ((x)+15) >>4 )<<4 )

#define __UPCASE( c )                  ( ((c) >= 'a' && (c) <= 'z') ? ((c)-0x20) : (c) )

#define __INC_SAT( val )               ( ( ((val)+1) > (val) ) ? ((val)+1) : (val) )
 
#define __SET_STRUCT_MB( s_type, var_type, s_ptr, s_mem, val )   *( (var_type*) ( ((unsigned char*)(s_ptr))+(offsetof(s_type, s_mem)) ) ) = (var_type)(val)

#define __IN_BYTE  ( port )            ( *((volatile uint8_t*  )(port)) )
#define __IN_WORD  ( port )            ( *((volatile uint16_t* )(port)) )
#define __IN_DWORD ( port )            ( *((volatile uint32_t* )(port)) )

#define __OUT_BYTE  ( port, val )      ( *((volatile uint8_t*  )(port)) = ((uint8_t )(val)) )
#define __OUT_WORD  ( port, val )      ( *((volatile uint16_t* )(port)) = ((uint16_t)(val)) )
#define __OUT_DWORD ( port, val )      ( *((volatile uint32_t* )(port)) = ((uint32_t)(val)) )

#ifdef __cplusplus
 }
#endif


#endif
