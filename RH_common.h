
#ifndef _RH_COMMON_H
#define _RH_COMMON_H

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
#include <time.h>

#ifdef __x86_64
#include <memory.h>
#endif
//#include <malloc.h>
//#include "RH_config.h"

#include <alloca.h>
#include <unistd.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define RH_COM_RECORD_VERSION                 "RH_COMMON - 08/18/2021"


#if defined ( __CC_ARM )
#pragma anon_unions
#endif
 
#ifndef UNUSED
#define UNUSED(x)    (void)(x)
#endif

#define RH_DEBUG
 

#define RH_NULLABLE
#define RH_NONNULL
#define RH_ALLOCATED

typedef int16_t var;    // 泛指数值, 具体随项目规模或实际设备
typedef int num;
 
struct __Region_t{
    var    xs;
    var    ys;
    var    w;
    var    h;
};
typedef struct __Region_t __Region_t;
typedef struct __Region_t __Area_t;
 
struct __Range_t{
    int   val;
    int   max;
    int   min;
};
typedef struct __Range_t __Range_t;

 
#define RH_RESULT     __attribute__((warn_unused_result))
#define RH_PREMAIN    __attribute__((constructor))
#define RH_AFTMAIN    __attribute__((destructor))
#define RH_FUNCONST   __attribute__((const))
#define RH_WEAK       __attribute__((weak))
 
#define RH_RESTRICT   __restrict
 
#define RH_PROTOTYPE  //__attribute__((deprecated))

 extern const char* RH_DIR;           // 当前项目路径
 extern const char* RH_DIR_DESKTOP;
 extern const char* RH_TIME;          // 最后的编译时间

 
#define MAKE_ENUM(name)  RH_ENUM_ ## name
 typedef enum{
     MAKE_ENUM( kStatus_Success   )    ,
     MAKE_ENUM( kStatus_Busy      )    ,
     MAKE_ENUM( kStatus_BadAccess )    ,
     MAKE_ENUM( kStatus_Denied    )    ,
     MAKE_ENUM( kStatus_Exist     )    ,
     MAKE_ENUM( kStatus_NoSpace   )    ,
     MAKE_ENUM( kStatus_ErrorID   )    ,
     MAKE_ENUM( kStatus_NotFound  )    ,
     MAKE_ENUM( kStatus_Warning   )    ,
     MAKE_ENUM( kStatus_Empty     )
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
 
#ifndef M_MATH_SEED
#define M_MATH_SEED   (0x3A97BFE0U)                           /* seed for random function */
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
 
#ifndef __roll
  #define __roll(a, lowerbound, upperbound)    (((a) > (upperbound)) ? lowerbound : (((a) < (lowerbound)) ? (upperbound) : (a) ))
#endif

#ifndef RH_LIMIT
  #define RH_LIMIT(a, lowerbound, upperbound)   ((((signed)(a)) >= ((signed)(upperbound))) ? upperbound : (((signed)(a) <= ((signed)(lowerbound))) ? (lowerbound) : (a) ))
#else
  #error " 'RH_LIMIT' has been defined. "
#endif

#ifndef RH_MIN
  #define RH_MIN(a,b)                           (((a)<(b))?(a):(b))
#else
  // #pragma message (" '__min' has been defined. ")
#endif

#ifndef RH_MAX
  #define RH_MAX(a,b)                           (((a)>(b))?(a):(b))
#else
  // #pragma message (" '__max' has been defined. ")
#endif

#ifndef RH_MID
  #define RH_MID(a,b)                           (((a)<(b))?((a)+(((b)-(a)+1)>>1)):((b)+(((a)-(b)+1)>>1)) )
#else
  #error " 'RH_MID' has been defined. "
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
 

#define RH_RECORD_TIME(func, print_func)({ clock_t cs = clock();func;clock_t ce = clock();print_func("RECORD_TIME:%ld\n",ce-cs); })
#define __LOOP( cnt, things )({size_t _ = cnt;while(_--){things;}})
 
 
 
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
 
/*=========================================================================================================
 * Force to set a member in struct
 > s_type --- type name of your struct
 > m_type --- type name of your member in this struct. You should NOT add "const" or any other declartion.
 > s_ptr  --- pointer of this struct
 > s_mem  --- member of this struct
 > val    --- this value you want to set for this member
 =========================================================================================================*/
#define __SET_STRUCT_MB( s_type, m_type, s_ptr, s_mem, val )   *( (m_type*) ( ((unsigned char*)(s_ptr))+(offsetof(s_type, s_mem)) ) ) = (m_type)(val)
 
/*=========================================================================================================
 * Common utility for standard IO
 > BYTE  --- 8   Bit
 > WORD  --- 16  Bit
 > DWORD --- 32  Bit
 =========================================================================================================*/

#define RH_IN_BYTE   ( port )                 ( *((volatile uint8_t*  )(port)) )
#define RH_IN_WORD   ( port )                 ( *((volatile uint16_t* )(port)) )
#define RH_IN_DWORD  ( port )                 ( *((volatile uint32_t* )(port)) )

#define RH_IN_8BIT   ( port )                 RH_IN_BYTE  ( port )
#define RH_IN_16BIT  ( port )                 RH_IN_WORD  ( port )
#define RH_IN_32BIT  ( port )                 RH_IN_DWORD ( port )
      
#define RH_OUT_BYTE  ( port, val )            ( *((volatile uint8_t*  )(port)) = ((uint8_t )(val)) )
#define RH_OUT_WORD  ( port, val )            ( *((volatile uint16_t* )(port)) = ((uint16_t)(val)) )
#define RH_OUT_DWORD ( port, val )            ( *((volatile uint32_t* )(port)) = ((uint32_t)(val)) )

#define RH_OUT_8BIT  ( port, val )            RH_OUT_BYTE  ( port, val )
#define RH_OUT_16BIT ( port, val )            RH_OUT_WORD  ( port, val )
#define RH_OUT_32BIT ( port, val )            RH_OUT_DWORD ( port, val )
 
 
/*=========================================================================================================
 * Common terminology for each project
 > RH  --- General macro for all
 > GLU --- Glucoo
 > BLK --- Black House
 > SMP --- Smart Pi
 =========================================================================================================*/

#define BLK_ENUM_MEMBER( name )              kBLK_##name
#define GLU_ENUM_MEMBER( name )              kGLU_##name
#define SMP_ENUM_MEMBER( name )              kSMP_##name
 
#define BLK_GVAR( name )                     G_BLK_##name
#define GLU_GVAR( name )                     G_GLU_##name
#define SMP_GVAR( name )                     G_SMP_##name

#define BLK_FUNC( class, method )            BLK_##class##_##method
#define GLU_FUNC( class, method )            GLU_##class##_##method
#define SMP_FUNC( class, method )            SMP_##class##_##method
 
#define BLK_ENUM( enum )                     E_BLK_##enum##_t
#define GLU_ENUM( enum )                     E_GLU_##enum##_t
#define SMP_ENUM( enum )                     E_SMP_##enum##_t
 
#define BLK_SRCT( class )                    S_BLK_##class##_t
#define GLU_SRCT( class )                    S_GLU_##class##_t
#define SMP_SRCT( class )                    S_SMP_##class##_t
 
#define BLK_UION( union )                    U_BLK_##union##_t
#define GLU_UION( union )                    U_GLU_##union##_t
#define SMP_UION( union )                    U_SMP_##union##_t

#define BLK_TYPE( type )                     T_BLK_##type##_t
#define GLU_TYPE( type )                     T_GLU_##type##_t
#define SMP_TYPE( type )                     T_SMP_##type##_t
 
#define BLK_API
#define GLU_API
#define SMP_API
 
#if 0
#error "Read the following tips and remove this error first."

/*
 * Be careful with the memory allocate function in each file.
 *
 *
 */
 
#endif
 
#ifdef __cplusplus
 }
#endif


#endif
