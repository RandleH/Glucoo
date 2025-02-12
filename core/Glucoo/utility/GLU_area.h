#include "RH_common.h"
#include "RH_config.h"

#include "GLU_font.h"

#define M_UTILITY_ALIGN_LF        ((uint32_t)( 1<<0 ))
#define M_UTILITY_ALIGN_RH        ((uint32_t)( 1<<1 ))
#define M_UTILITY_ALIGN_UP        ((uint32_t)( 1<<2 ))
#define M_UTILITY_ALIGN_DN        ((uint32_t)( 1<<3 ))
#define M_UTILITY_ALIGN_HM        ((uint32_t)( 1<<4 ))
#define M_UTILITY_ALIGN_VM        ((uint32_t)( 1<<5 ))


void glu_util_align_area( const gluArea_t* src, var w, var h, gluArea_t* dst, uint32_t M_UTILITY_ALIGN_xx );
void glu_util_align_screen( var w, var h, gluArea_t* dst, uint32_t M_UTILITY_ALIGN_xx );

bool glu_util_is_pt_inside( var x, var y, const gluArea_t* pArea );

void glu_util_area_hdiv( const gluArea_t* all, gluArea_t sub[], size_t size );
void glu_util_area_vdiv( const gluArea_t* all, gluArea_t sub[], size_t size );//

void glu_util_optimal_text( const gluArea_t* src, const char* str, tGluFontEnum font, tGluTextInfo* dst );

