#include "RH_common.h"
#include "RH_config.h"

#include "GLU_font.h"

#define M_UTILITY_ALIGN_LF        ((uint32_t)( 1<<0 ))
#define M_UTILITY_ALIGN_RH        ((uint32_t)( 1<<1 ))
#define M_UTILITY_ALIGN_UP        ((uint32_t)( 1<<2 ))
#define M_UTILITY_ALIGN_DN        ((uint32_t)( 1<<3 ))
#define M_UTILITY_ALIGN_HM        ((uint32_t)( 1<<4 ))
#define M_UTILITY_ALIGN_VM        ((uint32_t)( 1<<5 ))

void GLU_FUNC( Utility, align_area   )( const __Area_t* src, var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx );
void GLU_FUNC( Utility, align_screen )(                      var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx );

bool GLU_FUNC( Utility, pt_in_area   )( var x, var y, const __Area_t* pArea );

void GLU_FUNC( Utility, area_hdiv    )( const __Area_t* all, __Area_t sub[], size_t size );
void GLU_FUNC( Utility, area_vdiv    )( const __Area_t* all, __Area_t sub[], size_t size );//

void GLU_FUNC( Utility, optimal_text )( const __Area_t* src, const char* str, GLU_ENUM(Font) font, GLU_SRCT(Text)* dst );

