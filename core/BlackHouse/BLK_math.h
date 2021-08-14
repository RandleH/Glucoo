#ifndef _BLK_MATH_H
#define _BLK_MATH_H

#include "RH_common.h"
#include "RH_config.h"

#ifdef __cplusplus
extern "C" {
#endif
/*===========================================================================================================================
 > Algebra Reference
============================================================================================================================*/
struct BLK_SRCT(Kernel){
    uint16_t*   pBuffer; //  <- This buffer array should only be created by "__malloc".
    size_t      order;
    int32_t     sum;
};
typedef struct BLK_SRCT(Kernel)       BLK_SRCT(Kernel);

long                  BLK_FUNC( Math, sign          )   ( long   x);
long                  BLK_FUNC( Math, step          )   ( long   x);
long                  BLK_FUNC( Math, sqrt          )   ( long   x);
double                BLK_FUNC( Math, sigmold       )   ( double x);
      
int                   BLK_FUNC( Math, rand          )   ( void    );
int                   BLK_FUNC( Math, rand_in       )   ( int  min, int max );
      
unsigned long         BLK_FUNC( Math, combinatorial )   ( unsigned long n, unsigned long r );
      
double                BLK_FUNC( Math, tan           )   ( long   dec);
double                BLK_FUNC( Math, atan          )   ( long   y,long x     );

long                  BLK_FUNC( Math, gcd           )   ( long   a,long b     );
      
long                  BLK_FUNC( Math, factorial     )   ( long   x);
long                  BLK_FUNC( Math, fibonacci     )   ( long   n);
      
double                BLK_FUNC( Gussian, func_1D    )   ( long   x,long __miu  ,double __sigma);
double                BLK_FUNC( Gussian, func_2D    )   ( long   x,long y      ,double __sigma);
double                BLK_FUNC( Gussian, func_2D_XY )   ( long x,long y,double sigma_x,double sigma_y,double miu_x, double miu_y);
BLK_SRCT(Kernel)*     BLK_FUNC( Gussian, kernel     )   ( double __sigma,size_t order,BLK_SRCT(Kernel)* pKernel);

long                  BLK_FUNC( Pascal, triangle    )   ( long row , long col );

bool                  BLK_FUNC( Mandelbrot, set     )   ( float complex c, size_t nitersLimit );
void                  BLK_FUNC( Mandelbrot, image   )   ( float complex center, int img_w, int img_h, float scale_x, float scale_y, void* buf, void (*func)(int x,int y,uint32_t nIter, void* buf) );

/*===========================================================================================================================
> Geometry Reference
=============================================================================================================================*/
struct BLK_SRCT(Vector2D){
   int x;
   int y;
};
typedef struct BLK_SRCT(Vector2D) BLK_SRCT(Vector2D);
typedef struct BLK_SRCT(Vector2D) BLK_SRCT(Point2D);

struct BLK_SRCT(Vector3D){
   int x;
   int y;
   int z;
};
typedef struct BLK_SRCT(Vector3D) BLK_SRCT(Vector3D);
typedef struct BLK_SRCT(Vector3D) Point3D_t;

BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Ymax )( BLK_SRCT(Point2D)* pts, size_t size );
BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Ymin )( BLK_SRCT(Point2D)* pts, size_t size );
BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Xmax )( BLK_SRCT(Point2D)* pts, size_t size );
BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Xmin )( BLK_SRCT(Point2D)* pts, size_t size );


Point3D_t __findPoint_VectorDistance   (const Point3D_t* A        ,const Point3D_t* B     ,int    dist_AP );
Point3D_t __findPoint_VectorProportion (const Point3D_t* A        ,const Point3D_t* B     ,double scale   );


int                BLK_FUNC( Vector2D, dot   ) (const BLK_SRCT(Vector2D)* vect1   ,const BLK_SRCT(Vector2D)* vect2);
int                BLK_FUNC( Vector3D, dot   ) (const BLK_SRCT(Vector3D)* vect1   ,const BLK_SRCT(Vector3D)* vect2);
BLK_SRCT(Vector3D) BLK_FUNC( Vector3D, cross ) (const BLK_SRCT(Vector3D)* vect1   ,const BLK_SRCT(Vector3D)* vect2);

enum BLK_ENUM(CordRegion){
    kBLK_CordRegion_0_45   ,
    kBLK_CordRegion_45_90  ,
    kBLK_CordRegion_90_135 ,
    kBLK_CordRegion_135_180,
    kBLK_CordRegion_180_225,
    kBLK_CordRegion_225_270,
    kBLK_CordRegion_270_315,
    kBLK_CordRegion_315_360,
};
typedef enum BLK_ENUM(CordRegion) BLK_ENUM(CordRegion);

enum BLK_ENUM(PtPos){
    kBLK_PtPos_outside    = -1 ,
    kBLK_PtPos_righton    =  0 ,
    kBLK_PtPos_inside     =  1 ,
    kBLK_PtPos_above      =  2 ,
    kBLK_PtPos_beneath    =  3 ,
    kBLK_PtPos_at_orgin   =  4 ,
    kBLK_PtPos_at_cord1   =  5 ,
    kBLK_PtPos_at_cord2   =  6 ,
    kBLK_PtPos_at_cord3   =  7 ,
    kBLK_PtPos_at_cord4   =  8 ,
    kBLK_PtPos_at_axisXp  =  9 ,
    kBLK_PtPos_at_axisXm  =  10 ,
    kBLK_PtPos_at_axisYp  =  11 ,
    kBLK_PtPos_at_axisYm  =  12 ,
};
typedef enum BLK_ENUM(PtPos) BLK_ENUM(PtPos);

enum BLK_ENUM(Monotonicity){
    kBLK_Monotonicity_hor  ,  //  horizontal
    kBLK_Monotonicity_inc  ,  //  increase
    kBLK_Monotonicity_dec  ,  //  decrease
    kBLK_Monotonicity_ver     //  vertical
};
typedef enum BLK_ENUM(Monotonicity) BLK_ENUM(Monotonicity);

BLK_ENUM(Monotonicity)  BLK_FUNC( Math, dir_line )  (int x1,int y1,int x2,int y2);




long       BLK_FUNC( Math, area_triangle      )(int x1,int y1,int x2,int y2,int x3,int y3);
long       BLK_FUNC( Math, area_rectangular   )(int x1,int y1,int x2,int y2);

BLK_ENUM(PtPos)   BLK_FUNC( Math, pt_triangle )      (int x1,int y1,int x2,int y2,int x3,int y3, int px,int py);
BLK_ENUM(PtPos)   BLK_FUNC( Math, pt_line     )      (int x1,int y1,int x2,int y2,               int px,int py);
BLK_ENUM(PtPos)   BLK_FUNC( Math, pt_citcle   )      (int xc,int yc,int r,                       int px,int py);
BLK_ENUM(PtPos)   BLK_FUNC( Math, pt_cord2D   )      (                                           int px,int py);





#ifdef __cplusplus
}
#endif

#endif
