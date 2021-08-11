#include "RH_common.h"
#include "RH_config.h"

#define M_UTILITY_ALIGN_LF        ((uint32_t)( 1<<0 ))
#define M_UTILITY_ALIGN_RH        ((uint32_t)( 1<<1 ))
#define M_UTILITY_ALIGN_UP        ((uint32_t)( 1<<2 ))
#define M_UTILITY_ALIGN_DN        ((uint32_t)( 1<<3 ))
#define M_UTILITY_ALIGN_HM        ((uint32_t)( 1<<4 ))
#define M_UTILITY_ALIGN_VM        ((uint32_t)( 1<<5 ))

void GLU_FUNC( Utility, area_align   )( const __Area_t* src, var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx );
void GLU_FUNC( Utility, screen_align )(                      var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx );


