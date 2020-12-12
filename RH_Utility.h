#ifndef RH_UTILITY_H
#define RH_UTILITY_H 

#include <stddef.h>

#define __map(val,i_min,i_max,o_min,o_max)   (double)( ( ((double)o_max)*(((double)val)-((double)i_min))+((double)o_min)*((double)(i_max)-(double)(val)) )/((double)(i_max)-(double)(i_min)) )

#define __round(a)                           (int)((a)+0.5)>(int)(a)?((int)(a)+1):((int)(a))
#define __round1000(a)                       (double)((__round((a)*1000.0))/1000.0)
                    
#define _PI                                  (3.141592654) 
#define _2xPI                                (6.283185307)
#define _EXP                                 (2.718281828)

int     __sqrt    (int x);
// double  __sin     (int angle); 



struct IntArray_t{
	size_t  index;
	int     value;
};
typedef struct IntArray_t IntArray_t;
struct IntArray_t inline __findMax_INT(const int* pValue,size_t num);
struct IntArray_t inline __findMin_INT(const int* pValue,size_t num);

struct UintArray_t{
	size_t        index;
	unsigned int  value;
};
typedef struct UintArray_t UintArray_t;
// struct UintArray_t inline __findMax_INT(const unsigned int* pValue,size_t num);
// struct UintArray_t inline __findMin_INT(const unsigned int* pValue,size_t num);


int __Point_toLine  (int xs,int ys,int xe,int ye,                                 int px,int py);
// int __Point_toRect  (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,     int px,int py);


#endif

