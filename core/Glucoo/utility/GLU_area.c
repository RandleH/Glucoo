#include "GLU_area.h"



void GLU_FUNC( Utility, area_align )( const __Area_t* src, var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx ){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    M_UTILITY_ALIGN_xx &= 0x0000003f;
    
    // Align right/left/middle can NOT be applied simultaniously.
    RH_ASSERT( !(   (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_RH) \
                 && (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_LF) \
                 && (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_HM) ) );
    // Align up/down/middle can NOT be applied simultaniously.
    RH_ASSERT( !(   (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_UP) \
                 && (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_DN) \
                 && (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_VM) ) );
    
    if      (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_LF) dst->xs = src->xs;
    else if (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_RH) dst->xs = src->xs+src->w-w;
    else if (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_HM) dst->xs = src->xs+( ((signed)(src->w)-(signed)(w))>>1 );
    
    if      (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_UP) dst->ys = src->ys;
    else if (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_DN) dst->ys = src->ys+src->h-h;
    else if (M_UTILITY_ALIGN_xx&M_UTILITY_ALIGN_VM) dst->ys = src->ys+( ((signed)(src->h)-(signed)(h))>>1 );
    
    dst->w = w;
    dst->h = h;
}

void GLU_FUNC( Utility, screen_align )( var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx ){
    __Area_t src = {.xs = 0, .ys = 0, .w = RH_CFG_SCREEN_WIDTH, .h = RH_CFG_SCREEN_HEIGHT };
    GLU_FUNC( Utility, area_align )( &src, w, h, dst, M_UTILITY_ALIGN_xx );
}




