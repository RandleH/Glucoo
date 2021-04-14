#ifndef _RH_MATH_H
#define _RH_MATH_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif
/*===========================================================================================================================
 > Algebra Reference
============================================================================================================================*/
struct __Kernel_t{
    uint16_t*   pBuffer; //  <- This buffer array should only be created by "__malloc".
    size_t      order;
    int32_t     sum;
};
typedef struct __Kernel_t       __Kernel_t;

long         __sign            (long   x);
long         __step            (long   x);
long         __sqrt            (long   x);
double       __sigmold         (double x);

double       __cordic_tan      (long   dec);
double       __cordic_atan     (long   y,long x     );

double       __gussian         (long   x,long __miu  ,double __sigma);
double       __gussian2D       (long   x,long y      ,double __sigma);
__Kernel_t*  __gussianKernel   (double __sigma,size_t order,__Kernel_t* pKernel);
 
long         __step_mul        (long   x);
long         __fibonacci       (long   n);

long         __pascal_triangle     ( long row , long col );
long*        __pascal_triangle_row ( long row , size_t* returnSize );

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

/*===========================================================================================================================
> Geometry Reference
=============================================================================================================================*/
struct Vector2D_t{
   int x;
   int y;
};
typedef struct Vector2D_t Vector2D_t;
typedef struct Vector2D_t Point2D_t;

struct Vector3D_t{
   int x;
   int y;
   int z;
};
typedef struct Vector3D_t Vector3D_t;
typedef struct Vector3D_t Point3D_t;

Point3D_t __findPoint_LineCross        (const Point3D_t  line1[2] ,const Point3D_t  line2[2]);
Point3D_t __findPoint_VectorDistance   (const Point3D_t* A        ,const Point3D_t* B     ,int    dist_AP );
Point3D_t __findPoint_VectorProportion (const Point3D_t* A        ,const Point3D_t* B     ,double scale   );


int        __Vect2D_Dot                (const Vector2D_t* vect1   ,const Vector2D_t* vect2);
int        __Vect3D_Dot                (const Vector3D_t* vect1   ,const Vector3D_t* vect2);
Vector3D_t __Vect3D_Cross              (const Vector3D_t* vect1   ,const Vector3D_t* vect2);


int        __Dir_Line                  (int xs,int ys,int xe,int ye);
int        __Point_toLine              (int xs,int ys,int xe,int ye,               int px,int py);
int        __Point_toTriangle          (int x1,int y1,int x2,int y2,int x3,int y3, int px,int py);
int        __Point_toCircle            (int xc,int yc,int radius,                  int px,int py);
int        __Point_toCord2D            (int px,int py);

#ifdef __cplusplus
}
#endif

#endif
