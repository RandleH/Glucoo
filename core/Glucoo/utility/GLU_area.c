#include "GLU_area.h"



void GLU_FUNC( Utility, align_area )( const __Area_t* src, var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx ){
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

void GLU_FUNC( Utility, align_screen )( var w, var h, __Area_t* dst, uint32_t M_UTILITY_ALIGN_xx ){
    __Area_t src = {.xs = 0, .ys = 0, .w = RH_CFG_SCREEN_WIDTH, .h = RH_CFG_SCREEN_HEIGHT };
    GLU_FUNC( Utility, align_area )( &src, w, h, dst, M_UTILITY_ALIGN_xx );
}

bool GLU_FUNC( Utility, pt_in_area   )( var x, var y, const __Area_t* pArea ){
    RH_ASSERT(pArea);
    
    return (bool)((x>=pArea->xs)&&(x<pArea->xs+pArea->w)&&(y>=pArea->ys)&&(y<pArea->ys+pArea->h));
}

void GLU_FUNC( Utility, area_hdiv    )( const __Area_t* total, __Area_t p[], size_t size ){
    RH_ASSERT(total);
    RH_ASSERT(p);
    
    if(size==1){
        GLU_Utility_align_area( total, p->w, p->h, p, M_UTILITY_ALIGN_VM );
        return;
    }
    
    uint32_t length = 0;
    {
        __Area_t *iter = p;
        for( size_t i=0; i<size; i++, iter++ ){
            length += iter->w;
        }
    }
    
    RH_ASSERT(length<total->w);
    
    int32_t remain = (signed)(total->w) - (signed)(length);
    {
        var        x    = total->xs;
        __Area_t *iter = p;
        
        for( size_t i=0; i<size; i++, iter++ ){
            iter->xs = x;

            x+= iter->w;
            if( (size-1-i) != 0 ){
                x      += remain/(size-1-i);
                remain -= remain/(size-1-i);
            }
            
            GLU_FUNC(Utility,align_area)( total, iter->w, iter->h, iter, M_UTILITY_ALIGN_VM );
        }
    }
}

void GLU_FUNC( Utility, optimal_text )( const __Area_t* src, const char* str, GLU_ENUM(Font) font, GLU_SRCT(Text)* dst ){
    RH_ASSERT(src);
    RH_ASSERT(dst);
    RH_ASSERT(str);
    
    dst->str  = str;
    dst->font = font;
    
    GLU_Font_backupCache();
    
    GLU_Font_set_font(font);
    
    var l=8,r=RH_MIN(src->w,src->h);
    dst->size = ((r+l)>>1);
    var w=0, h=0;
    while( r-l>1 ){
        
        GLU_Font_set_size(dst->size);
        GLU_Font_get_str_ImgInfo( &w, &h, str);
        if( w<((src->w*3)>>2) && h<((src->h*3)>>2) ){
            l = dst->size;
        }else{
            r = dst->size;
        }
        
        dst->size = ((r+l)>>1);
    }
    
    GLU_Font_restoreCache();
}

