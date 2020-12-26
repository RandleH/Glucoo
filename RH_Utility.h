#ifndef RH_UTILITY_H
#define RH_UTILITY_H 

#include <stddef.h>
#include <stdint.h>

#define __map(val,i_min,i_max,o_min,o_max)   (double)( ( ((double)o_max)*(((double)val)-((double)i_min))+((double)o_min)*((double)(i_max)-(double)(val)) )/((double)(i_max)-(double)(i_min)) )

#define __round(a)                           (int)((a)+0.5)>(int)(a)?((int)(a)+1):((int)(a))
#define __round1000(a)                       (double)((__round((a)*1000.0))/1000.0)
                    
#define _PI                                  (3.141592654) 
#define _2xPI                                (6.283185307)
#define _EXP                                 (2.718281828)

/*=====================================================================
 > Algebra Reference 
======================================================================*/
int     __sign    (int x);
int     __sqrt    (int x);

/*=====================================================================
 > Quantity Reference 
======================================================================*/
struct IntArray_t{
	size_t  index;
	int     value;
};
typedef struct IntArray_t IntArray_t;
IntArray_t __findMax_INT(const int* pValue,size_t num);
IntArray_t __findMin_INT(const int* pValue,size_t num);

struct UintArray_t{
	size_t        index;
	unsigned int  value;
};
typedef struct UintArray_t UintArray_t;

/*=====================================================================
 > Geometry Reference 
======================================================================*/
struct Vector2D_t{
	int x;
	int y;
};
typedef struct Vector2D_t Vector2D_t;
int        __Vect2D_Dot    (const Vector2D_t* vect1,const Vector2D_t* vect2);

struct Vector3D_t{
	int x;
	int y;
	int z;
};
typedef struct Vector3D_t Vector3D_t;
int        __Vect3D_Dot    (const Vector3D_t* vect1,const Vector3D_t* vect2);
int        __Vect3D_Dot    (const Vector3D_t* vect1,const Vector3D_t* vect2);
Vector3D_t __Vect3D_Cross  (const Vector3D_t* vect1,const Vector3D_t* vect2);


int        __Dir_Line        (int xs,int ys,int xe,int ye);
int        __Point_toLine    (int xs,int ys,int xe,int ye,               int px,int py);
int        __Point_toTriangle(int x1,int y1,int x2,int y2,int x3,int y3, int px,int py);
int        __Point_toCircle  (int xc,int yc,int radius,                  int px,int py);

/*=====================================================================
 > Memory Programming Reference 
======================================================================*/
typedef uint16_t WORD;
void* __memsetWORD(void* __b,WORD value,size_t num);

#endif

