

#include "BLK_math.h"

#ifdef __cplusplus
extern "C" {}
#endif
/*===========================================================================================================================
 > Algebra Reference
============================================================================================================================*/
long BLK_FUNC( Math, sign )(long x){
    return (x>=0)?(1):(-1);
}
      
long BLK_FUNC( Math, step )(long x){
    return (long)( x >= 0 );
}

long BLK_FUNC( Math, sqrt )(long x){
    if(x <= 0) return 0;
    long l   = 1;
    long r   = x;
    long res = 0;
    while(l <= r){
        long mid=(l+r)>>1;
        if(mid <= x/mid){
          l   = mid+1;
          res = mid;
      }else{
          r = mid-1;
      }
    }
    if( ((res+1)*(res+1) - x) > (x - res*res) )
        return res;
    return (res+1);
}

/*========================================================================================================
 > DEC                        RAD                          TAN
 =========================================================================================================
 > Φ = 45                     0.78539816339744828          tan(Φ) = 1/1    
 > Φ = 26.565051177078        0.46364760900080609          tan(Φ) = 1/2    
 > Φ = 14.0362434679265       0.24497866312686414          tan(Φ) = 1/4    
 > Φ = 7.1250163489018        0.12435499454676144          tan(Φ) = 1/8    
 > Φ = 3.57633437499735       0.06241880999595735          tan(Φ) = 1/16   
 > Φ = 1.78991060824607       0.031239833430268277         tan(Φ) = 1/32   
 > Φ = 0.8951737102111        0.015623728620476831         tan(Φ) = 1/64   
 > Φ = 0.4476141708606        0.0078123410601011111        tan(Φ) = 1/128  
 > Φ = 0.2238105003685        0.0039062301319669718        tan(Φ) = 1/256  
 > Φ = 0.1119056770662        0.0019531225164788188        tan(Φ) = 1/512  
 > Φ = 0.0559528918938        0.00097656218955931946       tan(Φ) = 1/1024 
 > Φ = 0.027976452617         0.00048828121119489829       tan(Φ) = 1/2048 
 > Φ = 0.01398822714227       0.00024414062014936177       tan(Φ) = 1/4096 
 > Φ = 0.006994113675353      0.00012207031189367021       tan(Φ) = 1/8192 
 > Φ = 0.003497056850704      0.000061035156174208773      tan(Φ) = 1/16384
//========================================================================================================*/
    
const static uint16_t angle_dec_256[] = {
    // When 1 deg = 256, then...
    11520 , 
    6801  , 
    3593  , 
    1824  , 
    916   , 
    458   , 
    229   , 
    115   , 
    57    , 
    29    , 
    14    , 
    7     , 
    4     , 
    2     , 
    1       
};


double        
BLK_FUNC( Math, tan           )( long   dec ){

    long x = 0xffff;
    long y = 0;
    long angle_tar = dec<<8;
    long angle_sum = 0;
    long x_tmp = 0,y_tmp = 0;
    
    for( int i=0; i<16; i++ ){
        if( angle_tar < angle_sum ){ // cw
            x_tmp = (x + (y>>i));
            y_tmp = (y - (x>>i));
            x  = x_tmp;
            y  = y_tmp;
            angle_sum -= angle_dec_256[i];
        }else if(angle_tar > angle_sum){ // ccw
            x_tmp = (x - (y>>i));
            y_tmp = (y + (x>>i));
            x  = x_tmp;
            y  = y_tmp;
            angle_sum += angle_dec_256[i];
        }else{
            break;
        }
    }
    return y/((double)(x));
}

double        
BLK_FUNC( Math, atan          )( long   y, long   x ){
    
    __exitReturn( x==0 && y==0 ,    0 );
    __exitReturn( x==0 && y<0  ,  -90 );
    __exitReturn( x==0 && y>0  ,   90 );
    __exitReturn( y==0 && x<0  ,    0 );
    __exitReturn( y==0 && x>0  ,    0 );
    __exitReturn( x==y         ,   45 );
    __exitReturn( x==-y        ,  -45 );

    long angle_sum = 0;
    long x_tmp,y_tmp;
    
    y<<=10;
    x<<=10;
    
    for( int i=0; i<15; i++ ){
        if( y>0 ){ // cw
            x_tmp = (x + (y>>i));
            y_tmp = (y - (x>>i));
            x  = x_tmp;
            y  = y_tmp;
            angle_sum += angle_dec_256[i];
        }else if(y<0){ // ccw
            x_tmp = (x - (y>>i));
            y_tmp = (y + (x>>i));
            x  = x_tmp;
            y  = y_tmp;
            angle_sum -= angle_dec_256[i];
        }
    }
    
    return (angle_sum/256.0);
}
      
double        
BLK_FUNC( Math, sigmold       )( double x ){
    return (double)(1.0/(1+exp(-x)));
}

long          
BLK_FUNC( Math, factorial     )( long   x ){ 
    // [!] Limitation: x should be smaller than 20
    __exitReturn(x<0 , -1);
    __exitReturn(x==0,  1);
    long res = 1;
    while(--x){
        res*=(x+1);
    }
    return res;
}
      
long          
BLK_FUNC( Math, fibonacci     )( long   n ){
    __exitReturn(n<0, -1);
    
    if(n==0)
        return 1;
    long res = 0;
    long fnm1 = 1,fnm2 = 0;
    for (int i=2; i<=n+1; i++) {
        res  = fnm1+fnm2;
        fnm2 = fnm1;
        fnm1 = res;
    }
    return res;
}
    
long
BLK_FUNC( Math, gcd           )( long   a, long b  ){
   
#define THIS  BLK_FUNC(Math, gcd)
    
    if( b>a )
        __swap(a, b);
    
    if( b==0 )
        return a;
    
    if( !(a&1) ){
        if( !(b&1) ) return (long)(THIS(a>>1, b>>1) <<1);
        else         return (long)(THIS(a>>1, b   )    );
    }else{
        if( !(b&1) ) return (long)(THIS(a   , b>>1)    );
        else         return (long)(THIS(a-b , b   )    );
    }
    
#undef THIS
    
}

unsigned long 
BLK_FUNC( Math, combinatorial )( unsigned long n, unsigned long r ){
    __exitReturn( r>n , 0 );
    #if 0
    { // 初级算法
        unsigned long son = 1, mum = 1;
        for(unsigned long i=0; i<r;  ){
            son*=(n-i);
            mum*=(++i);
        }
        return (unsigned long)(son/mum);
    }
    #elif 1
    { // 进阶算法 1
        uint16_t *temp = alloca(r*sizeof(uint16_t));
        for( uint16_t i=0; i<r; i++ ){
            temp[i] = (n-r+i+1);
        }
        
        unsigned long mum=1, son=1;
        // 先进行约分, 否则被除数太大
        for( int32_t i=(int32_t)(r-1); i>=0; i-- ){
            int32_t j=(int32_t)(r-1);
            
            for( ; j>=0; j-- ){
                if( temp[j]%(i+1)==0 ){
                    temp[j]/=(i+1);
                    break;
                }
            }
            if( j<0 )
                mum *= i+1;
        }
        
        for( uint16_t i=0; i<r; i++ ){
            son*=temp[i];
        }
        
        return (unsigned long)(son/mum);
    }
    
    #else // 进阶算法 2
    {
        unsigned long son = 1, mum = 1;
        for(unsigned long i=0; i<r;  ){
            son*=(n-i);
            mum*=(++i);
            long gcd = BLK_FUNC(Math, gcd)( son, mum );
            son /= gcd;
            mum /= gcd;
        }
        return son;
        
    }
    #endif
}
    
int           
BLK_FUNC( Math, rand          )( void    ){
    static uint32_t a = (uint32_t)M_MATH_SEED; /*Seed*/

    /*Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs"*/
    uint32_t x = a;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    a = x;

    return (int)a;
}
    
int           
BLK_FUNC( Math, rand_in       )( int min, int max ){
    return ( (unsigned)BLK_FUNC(Math, rand)() % (max - min + 1)) + min;
}

BLK_ENUM(Monotonicity)
BLK_FUNC( Math, dir_line      )( int x1,int y1,int x2,int y2 ){
    if(x1==x2)
        return kBLK_Monotonicity_ver;
    if(y1==y2)
        return kBLK_Monotonicity_hor;

    return ( (((x2-x1)<0)&&((y2-y1)<0)) || (((x2-x1)>0)&&((y2-y1)>0)) )?(kBLK_Monotonicity_inc):(kBLK_Monotonicity_dec);
}




long              
BLK_FUNC( Math, area_triangle )( int x1,int y1,int x2,int y2,int x3,int y3 ){
    
   /* 
     可用的测试用例:
     Params                  | Answers
    ========================================
     ( 20,50, -40,25,  15, 15)  = 987.5
     (-40,25,  20,50,  15, 15)  = ...
     (-40,25,  15,15,  20, 50)  = ...
     (-40,25,  15,15, -20,-60)  = 2237.5
     (-40,25, -20,-60, 15, 15)  = ...
     (-400,25, -200,-60, 150, 15)
   */
    
    int type = ((x1<x2)<<2) | ((x1<x3)<<1) | ((x2<x3)<<0);
    int area = -1;
    switch(type){
        case 0: // x1 >= x2 >= x3
            area = __abs(( (y2+y3)*(x2-x3)+(y1+y2)*(x1-x2)-(y1+y3)*(x1-x3) ));
            break;
        case 1: // x1 >= x3 >= x2
            area = __abs(( (y3+y2)*(x3-x2)+(y1+y3)*(x1-x3)-(y1+y2)*(x1-x2) ));
            break;
        default:// Should not be runned here.
        case 2: // impossible
            RH_ASSERT(0);
        case 3: // x3 >  x1 >= x2
            area = __abs(( (y1+y2)*(x1-x2)+(y3+y1)*(x3-x1)-(y3+y2)*(x3-x2) ));
            break;
        case 4: // x2 >  x1 >= x3
            area = __abs(( (y1+y3)*(x1-x3)+(y2+y1)*(x2-x1)-(y2+y3)*(x2-x3) ));
            break;
        case 5: // x2 >  x1 >= x3
            area = __abs(( (y1+y3)*(x1-x3)+(y2+y1)*(x2-x1)-(y2+y3)*(x2-x3) ));
            break;
        case 6: // x2 >  x3 >  x1
            area = __abs(( (y3+y1)*(x3-x1)+(y2+y3)*(x2-x3)-(y2+y1)*(x2-x1) ));
            break;
        case 7: // x3 >  x2 >  x1
            area = __abs(( (y2+y1)*(x2-x1)+(y3+y2)*(x3-x2)-(y3+y1)*(x3-x1) ));
            break;
    }

    return (int)((area>>1) + (area&0x00));    
}

long              
BLK_FUNC( Math, area_rectangular )(int x1,int y1,int x2,int y2){
    return __abs((x2-x1)*(y2-y1));
}

float
BLK_FUNC( Math, poisson          )( int xs, int xe, int lamda ){
    float res = 0.0;
    for( int i=xs; i<=xe; i++ ){
        res += powf(lamda,i)/(float)BLK_FUNC(Math,factorial)(i);
    }
    res *= exp(-lamda);
    return res;
}

double
BLK_FUNC( Gussian, func_1D    )( long x,long __miu,double __sigma ){
    // Same Effect but slower,only suitable when __sigma is a value of double.
    #if 1
    return ((__sigma==0)?(0):(double)((M_2_SQRTPI/((__sigma*2)*(M_SQRT2)))*exp(-(x-__miu)*(x-__miu)/(double)((__sigma*__sigma)*2))));
    #else
    return ((__sigma==0)?(0):(double)((M_2_SQRTPI/((__sigma<<1)*(M_SQRT2)))*exp(-(x-__miu)*(x-__miu)/(double)((__sigma*__sigma)<<1))));
    #endif
}

double
BLK_FUNC( Gussian, func_2D    )( long x,long y,double __sigma ){
    // Same Effect but slower,only suitable when __sigma is a value of double.
    #if 1
    return ((__sigma==0)?(0):((double)((1/(2*M_PI*__sigma*__sigma))*exp(-((x*x)+(y*y))/(double)((__sigma*__sigma)*2)))));
    #else
    return ((__sigma==0)?(0):((double)((1/(M_PI*__sigma*(__sigma<<1)))*exp(-((x*x)+(y*y))/(double)((__sigma*__sigma<<1))))));
    #endif
}

double
BLK_FUNC( Gussian, func_2D_XY )( long x,long y,double sigma_x,double sigma_y,double miu_x, double miu_y){
    double b = exp(-0.5*( ((x-miu_x)*(x-miu_x))/(sigma_x*sigma_x) + ((y-miu_y)*(y-miu_y))/(sigma_y*sigma_y) ));
    return (double)(b/(2.0*M_PI*sigma_x*sigma_y));
}

BLK_SRCT(Kernel)*
BLK_FUNC( Gussian, kernel     )( double __sigma,size_t order,BLK_SRCT(Kernel)* pKernel ){
    if( pKernel == NULL || pKernel->pBuffer == NULL ){
        return NULL;
    }
    
    if( __sigma == 0){ // In case of divider being zero.
        memset(pKernel->pBuffer,0,order*order*sizeof(*(pKernel->pBuffer)));
        pKernel->order = order;
        pKernel->sum = 0;
        return pKernel;
    }
    
    size_t half_order = ((order-1)>>1); // The index of the middle element. eg:  x x x ^ x x x ,which is "3".
    uint16_t* pCenter = pKernel->pBuffer + (half_order * order) + half_order;
    double coe        = 1.0/BLK_FUNC( Gussian, func_2D )(half_order,half_order,__sigma); // Make sure every element is larger than 0.
    
    pKernel->order = order;
    pKernel->sum = 0;
    for(int x=0;x<=half_order;x++){
        for(int y=0;y<=x;y++){
            uint16_t temp = lround(coe*BLK_FUNC( Gussian, func_2D )(x,y,__sigma));
            *(pCenter + (y*order) + x) = temp;
            *(pCenter - (y*order) + x) = temp;
            *(pCenter + (y*order) - x) = temp;
            *(pCenter - (y*order) - x) = temp;
            *(pCenter + (x*order) + y) = temp;
            *(pCenter - (x*order) + y) = temp;
            *(pCenter + (x*order) - y) = temp;
            *(pCenter - (x*order) - y) = temp;
            if(x == 0 && y == 0)
                pKernel->sum += temp;
            else if( x==0 || y == 0 || x==y )
                pKernel->sum += (temp<<2);
            else
                pKernel->sum += (temp<<3);
            
        }
    }
    return pKernel;
}
      
long
BLK_FUNC( Pascal, triangle    )( long row, long col ){

    /*        

                1 --------------- row = 0
              1   1 ------------- row = 1    
            1   2   1 ----------- row = 2
          1   3   3   1 --------- row = 3
        1   4   6   4   1 ------- row = 4
        |      ...      |
        |               |
        |               |
        |               |
    col = 0         col = 4

    */


    __exitReturn( col>row || col<0 || row<0 , -1 );
    return BLK_FUNC(Math,combinatorial)(row,col);
}
      
bool
BLK_FUNC( Mandelbrot, set     )( float complex c, size_t nitersLimit ){
    __exitReturn( cabs(c)<= 0.25, true  );
    __exitReturn( cabs(c) > 2.0 , false );

    float complex z = 0 + 0*I;

    while( nitersLimit-- && cabs(z)<=2 ){
        z*=z;
        z+=c;
    }
    
    return (nitersLimit == 0)?true:false;
}

#include "BLK_image.h"
void 
BLK_FUNC( Mandelbrot, image   )( float complex center, int img_w, int img_h, float scale_x, float scale_y, void* buf, void (*func)(int x,int y,uint32_t nIter, void* buf) ){
    uint32_t nitersLimit = 0xff;

    float x0 = creal(center);
    float y0 = cimag(center);

    
    for( int y=0; y<img_h; y++){
        for ( int x=0; x<img_w; x++){
           
            double px = (x-(img_w>>1))*scale_x-x0;
            double py = (y-(img_h>>1))*scale_y-y0;
            
            if(x == 533 && y==462){
                printf("%.22f,%.22f\n",px,py);
            }
            float complex c = px + py*I;

            // 检查是否在集合内
            {
                float complex z      = 0 + 0*I;
                uint32_t      niters = nitersLimit;
                while( niters-- && cabs(z)<=2 ){
                    z*=z;
                    z+=c;
                }
                if(nitersLimit == 0){
                    (*func)(x,y,     -1, buf);
                }else{
                    (*func)(x,y, nitersLimit-niters, buf);
                }
            }
            
        }
    }

    BLK_SRCT(Img888)* dst = (BLK_SRCT(Img888)*)buf;

    (dst->ptr + (dst->h>>1)*dst->w + (dst->w>>1))->R = 0x00;
    (dst->ptr + (dst->h>>1)*dst->w + (dst->w>>1))->G = 0x00;
    (dst->ptr + (dst->h>>1)*dst->w + (dst->w>>1))->B = 0x00;

    
}

    
/*===========================================================================================================================
 > Geometry Reference
============================================================================================================================*/

BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Ymax )( BLK_SRCT(Point2D)* pts, size_t size ){
    RH_ASSERT(pts);
    RH_ASSERT(size);
    
    BLK_SRCT(Point2D) pt = {.x = pts->x, .y = pts->y};
    for(size_t i=0; i<size; i++,pts++){
        if( pts->y > pt.y ){
            pt = *pts;
        }
    }
    return pt;
}
BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Ymin )( BLK_SRCT(Point2D)* pts, size_t size ){
    RH_ASSERT(pts);
    RH_ASSERT(size);
    
    BLK_SRCT(Point2D) pt = {.x = pts->x, .y = pts->y};
    for(size_t i=0; i<size; i++,pts++){
        if( pts->y < pt.y ){
            pt = *pts;
        }
    }
    return pt;
}
BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Xmax )( BLK_SRCT(Point2D)* pts, size_t size ){
    RH_ASSERT(pts);
    RH_ASSERT(size);
    
    BLK_SRCT(Point2D) pt = {.x = pts->x, .y = pts->y};
    for(size_t i=0; i<size; i++,pts++){
        if( pts->x > pt.x ){
            pt = *pts;
        }
    }
    return pt;
}
BLK_SRCT(Point2D)  BLK_FUNC( Point2D, find_Xmin )( BLK_SRCT(Point2D)* pts, size_t size ){
    RH_ASSERT(pts);
    RH_ASSERT(size);
    
    BLK_SRCT(Point2D) pt = {.x = pts->x, .y = pts->y};
    for(size_t i=0; i<size; i++,pts++){
        if( pts->x < pt.x ){
            pt = *pts;
        }
    }
    return pt;
}


Point3D_t __findPoint_VectorDistance   (const Point3D_t*  A,const Point3D_t*  B,int dist_AP){
    long dist_AB = lroundl(sqrt( (B->x - A->x)*(B->x - A->x) + \
                                (B->y - A->y)*(B->y - A->y) + \
                                (B->z - A->z)*(B->z - A->z)  ));
    Point3D_t result = {
        .x = (B->x - A->x)*dist_AP/dist_AB + A->x ,
        .y = (B->y - A->y)*dist_AP/dist_AB + A->y ,
        .z = (B->z - A->z)*dist_AP/dist_AB + A->z ,
    };

    return result;
}

Point3D_t __findPoint_VectorProportion (const Point3D_t*  A,const Point3D_t*  B,double scale){
    Point3D_t result = {
        .x = (B->x - A->x)*scale + A->x ,
        .y = (B->y - A->y)*scale + A->y ,
        .z = (B->z - A->z)*scale + A->z ,
    };
    return result;
}

int
BLK_FUNC( Vector2D, dot       )( const BLK_SRCT(Vector2D)* vect1,const BLK_SRCT(Vector2D)* vect2){
    return (int)((vect1->x*vect2->x)+(vect1->y*vect2->y));
}

int
BLK_FUNC( Vector3D, dot       )( const BLK_SRCT(Vector3D)* vect1,const BLK_SRCT(Vector3D)* vect2){
    return (int)((vect1->x*vect2->x)+(vect1->y*vect2->y)+(vect1->z*vect2->z));
}

BLK_SRCT(Vector3D)
BLK_FUNC( Vector3D, cross     )( const BLK_SRCT(Vector3D)* vect1,const BLK_SRCT(Vector3D)* vect2){
    BLK_SRCT(Vector3D) vecResult = {.x = ( vect1->y*vect2->z - vect1->z*vect2->y),\
                            .y = ( vect1->z*vect2->x - vect1->x*vect2->z),\
                            .z = ( vect1->x*vect2->y - vect1->y*vect2->x)};
    return vecResult;
}

BLK_ENUM(PtPos)
BLK_FUNC( Math, pt_citcle     )( int xc,int yc,int r,                       int px,int py){
    long key = (xc-px)*(xc-px)+(yc-py)*(yc-py);
    long r_2 = r*r;
    if(key > r_2)
        return kBLK_PtPos_outside;
    else if(key < r_2)
        return kBLK_PtPos_inside;
    else
        return kBLK_PtPos_righton;
}

BLK_ENUM(PtPos)
BLK_FUNC( Math, pt_line       )( int x1,int y1,int x2,int y2,               int px,int py ){
    int param_1 = (x2>x1)?( (x2-x1)*py ):( (x1-x2)*py );
    int param_2 = (x2>x1)?( (y2-y1)*px+(y2*(x2-x1)-x2*(y2-y1)) ):( (y1-y2)*px+(y2*(x1-x2)-x2*(y1-y2)) );

    if(param_1 > param_2)
        return kBLK_PtPos_above;
    else if(param_1 < param_2)
        return kBLK_PtPos_beneath;
    else
        return kBLK_PtPos_righton;
}
    

BLK_ENUM(PtPos)
BLK_FUNC( Math, pt_cord2D     )( int px,int py){
    if( px==0&&py==0 ) return kBLK_PtPos_at_orgin;
    if( py==0 ){
        if( px>0 )  return kBLK_PtPos_at_axisXp;
        else        return kBLK_PtPos_at_axisXm;
    } 
    if( px==0 ){
        if( py>0 )  return kBLK_PtPos_at_axisYp;
        else        return kBLK_PtPos_at_axisYm;
    }
    uint8_t key = ((py<0)<<1)|(px<0);
    return (BLK_ENUM(PtPos))(((key>>1)^key) +4);
}

BLK_ENUM(PtPos)
BLK_FUNC( Math, pt_triangle   )( int x1,int y1,int x2,int y2,int x3,int y3, int px,int py ){
 #if 0
    // Condition:
    // P = A + u*(CA) + v*(BA)
    // u >= 0 && v >= 0 && u+v <= 1
    
    // Any point can be represented by: (PA) = u*(CA) + v*(BA)
    //
    // When both multiply by (CA) and (BA):
    // (PA)·(CA) = u*[(CA)·(CA)] + v*[(BA)·(CA)]
    // (PA)·(BA) = u*[(BA)·(CA)] + v*[(BA)·(BA)]
    
    // Then:
    //         [(BA)·(BA)]*[(PA)·(CA)] - [(BA)·(CA)]*[(PA)·(BA)]
    // u = ---------------------------------------------------------
    //         [(CA)·(CA)]*[(BA)·(BA)] - [(CA)·(BA)]*[(BA)·(CA)]
    
    //         [(CA)·(CA)]*[(PA)·(BA)] - [(CA)·(CA)]*[(PA)·(CA)]
    // v = ---------------------------------------------------------
    //         [(CA)·(CA)]*[(BA)·(BA)] - [(CA)·(BA)]*[(BA)·(CA)]
    
    // Assume A = (x1,y1) | B = (x2,y2) | C = (x3,y3) :
    struct BLK_SRCT(Vector2D) v0 = {.x = x3-x1,.y = y3-y1};
    struct BLK_SRCT(Vector2D) v1 = {.x = x2-x1,.y = y2-y1};
    struct BLK_SRCT(Vector2D) v2 = {.x = px-x1,.y = py-y1};

    int v00 = BLK_FUNC(Vector2D, dot)(&v0,&v0);
    int v01 = BLK_FUNC(Vector2D, dot)(&v0,&v1);
    int v02 = BLK_FUNC(Vector2D, dot)(&v0,&v2);
    int v11 = BLK_FUNC(Vector2D, dot)(&v1,&v1);
    int v12 = BLK_FUNC(Vector2D, dot)(&v1,&v2);

    int u = v11*v02-v01*v12;
    int v = v00*v12-v01*v02;
    int d = v00*v11-v01*v01;
    if(u<0 || v<0)
        return -1;
    else if(u==0 || v==0)
        return 0;

    if(u+v > d)
        return -1;
    else if(u+v < d)
        return 1;
    else
        return 0;
 #endif

 #if 0 // Wrong
    int signOfTrig = (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
    int signOfAB   = (x2 - x1)*(py - y1) - (y2 - y1)*(px - x1);
    int signOfCA   = (x1 - x3)*(py - y3) - (y1 - y3)*(px - x3);
    int signOfBC   = (x3 - x2)*(py - y3) - (y3 - y2)*(px - x2);
  
    bool d1 = (signOfAB<0&&signOfTrig<0) || (signOfAB>0&&signOfTrig>0);
    bool d2 = (signOfCA<0&&signOfTrig<0) || (signOfCA>0&&signOfTrig>0);
    bool d3 = (signOfBC<0&&signOfTrig<0) || (signOfBC>0&&signOfTrig>0);
    
    return d1 && d2 && d3;
    
 #endif
 #if 1
    long p_area = BLK_FUNC(Math,area_triangle)( px,py, x1,y1, x2,y2  ) + \
                  BLK_FUNC(Math,area_triangle)( px,py, x2,y2, x3,y3  ) + \
                  BLK_FUNC(Math,area_triangle)( px,py, x1,y1, x3,y3  ) ;
    long t_area = BLK_FUNC(Math,area_triangle)( x1,y1, x2,y2, x3,y3  );
    
    if( p_area > t_area )
        return kBLK_PtPos_outside;
    else
        return kBLK_PtPos_inside;
    
 #endif
}

    
#ifdef __cplusplus
}
#endif
