

#include "RH_math.h"

#ifdef __cplusplus
extern "C" {
#endif
/*===========================================================================================================================
 > Algebra Reference
============================================================================================================================*/
long __sign(long x){
    return (x>=0)?(1):(-1);
}
      
long __step(long x){
    return (long)( x >= 0 );
}

long __sqrt(long x){
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
    
//const static uint16_t angle_rad_65535[] = {
//    // When 1 rad = 65535, then...
//    51471 , 
//    30385 , 
//    16055 , 
//    8150  , 
//    4091  , 
//    2047  , 
//    1024  , 
//    512   , 
//    256   , 
//    128   , 
//    64    , 
//    32    , 
//    16    , 
//    8     , 
//    4     , 
//    2
//};

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

double __cordic_tan(long dec){

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

double __cordic_atan(long y,long x){
    
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
      
double __sigmold(double x){
    return (double)(1.0/(1+exp(-x)));
}

double __gussian(long x,long __miu,double __sigma){
// Same Effect but slower,only suitable when __sigma is a value of double.
    return ((__sigma==0)?(0):(double)((M_2_SQRTPI/((__sigma*2)*(M_SQRT2)))*exp(-(x-__miu)*(x-__miu)/(double)((__sigma*__sigma)*2))));
//    return ((__sigma==0)?(0):(double)((M_2_SQRTPI/((__sigma<<1)*(M_SQRT2)))*exp(-(x-__miu)*(x-__miu)/(double)((__sigma*__sigma)<<1))));
}

double __gussian2D(long x,long y,double __sigma){
// Same Effect but slower,only suitable when __sigma is a value of double.
    return ((__sigma==0)?(0):((double)((1/(2*M_PI*__sigma*__sigma))*exp(-((x*x)+(y*y))/(double)((__sigma*__sigma)*2)))));
//    return ((__sigma==0)?(0):((double)((1/(M_PI*__sigma*(__sigma<<1)))*exp(-((x*x)+(y*y))/(double)((__sigma*__sigma<<1))))));
}

__Kernel_t* __gussianKernel(double __sigma,size_t order,__Kernel_t* pKernel){
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
    double coe        = 1.0/__gussian2D(half_order,half_order,__sigma); // Make sure every element is larger than 0.
    
    pKernel->order = order;
    pKernel->sum = 0;
    for(int x=0;x<=half_order;x++){
        for(int y=0;y<=x;y++){
            uint16_t temp = lround(coe*__gussian2D(x,y,__sigma));
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
      
long __pascal_triangle(long row, long col){
    __exitReturn( col>row || col<0 || row<0 , -1 );
    return (__pascal_triangle_row(row, NULL))[col];
}
    
long* __pascal_triangle_row( long row , size_t* returnSize ){
    __exitReturn( row<0 , NULL );
    if( returnSize )
        *returnSize = row+1;
    
    struct __Link{
        struct __Link* pNext;
        long*           data;
        size_t         row;
    };
    typedef struct __Link __Link;
    static struct __Link Head = {
        .pNext = NULL ,
        .data  = NULL ,
        .row   = 0
    };
    if( Head.data == NULL ){
        Head.data = (long*)malloc(sizeof(long));
        Head.data[0] = 1;
    }

    __Link* pIter = &Head;
    __Link* pOpti = &Head;
    __Link* pLast = &Head;
    
    long dis_row_min    = __abs(row - pIter->row);
    bool sgn            = (row > pIter->row);     // 标志,判断距离目标最近的那一行位于目标的上方还是下方 1 = 上方; 0 = 下方;
    do{
        // 行差越小，需要迭代的次数就越少
        if( __abs(row-pIter->row) < dis_row_min ){
            sgn = (row > pIter->row);
            dis_row_min = row - pIter->row;
            pOpti = pIter;
        }
        // 如果就是那一行，即行差为0，则直接返回值
        if( pIter->row==row ){
            return ( pIter->data );
        }
        // 继续迭代寻找
        pLast = pIter;
        pIter = pIter->pNext;
   
    }while( pIter != NULL );
    
    // 没有找到那一行，则从最接近那一行（pOpti->row）的数值开始向sgn方向计算，并记录之
    // 此时 pOpti 代表距离最近的那一行数据，pLast为链表最后节点末尾。
    __Link*  pasc_link = pLast;
    long*    last_data = pOpti->data;                                      // 从距离目标最近的那一行开始
    if( sgn == true ){ // =================================================// 距离最近的那一行位于目标上方
        long   pasc_size = (pOpti->row)+2;                                 // 该行的元素个数为上一行行号+2
        
        while( dis_row_min-- ){
            pasc_link->pNext    = (__Link*)malloc( sizeof(__Link) );       // 新建一行
            pasc_link           = pasc_link->pNext;
            

            pasc_link->data     = (long*)malloc( pasc_size * sizeof(long) );
            pasc_link->row      = pasc_size-1;                             // 该行行号为该行元素数量-1
            pasc_link->pNext    = NULL;
            
            pasc_link->data[pasc_size-1] = pasc_link->data[0] = 1;         // 该行边界均为1
            for( int i=1;i<=(pasc_size-1-i);i++ ){
                pasc_link->data[i] = pasc_link->data[pasc_size-1-i] = last_data[i] + last_data[i-1];
            }

            last_data           = pasc_link->data;
            pasc_size           = pasc_link->row+2;
        }
    }else{ // =============================================================// 距离最近的那一行位于目标下方
        long   pasc_size = (pOpti->row)-2;                                 // 该行的元素个数为下一行行号-2
        
        while( dis_row_min-- ){
            pasc_link->pNext    = (__Link*)malloc( sizeof(__Link) );       // 新建一行
            pasc_link           = pasc_link->pNext;
            
            pasc_link->data     = (long*)malloc( pasc_size * sizeof(long) );
            pasc_link->row      = pasc_size-1;                             // 该行行号为该行元素数量-1
            pasc_link->pNext    = NULL;
            
            pasc_link->data[pasc_size-1] = pasc_link->data[0] = 1;         // 该行边界均为1
            for( int i=1;i<=(pasc_size-1-i);i++ ){
                pasc_link->data[i] = pasc_link->data[pasc_size-1-i] = last_data[i] - pasc_link->data[i-1];
            }
            
            last_data           = pasc_link->data;
            pasc_size           = pasc_link->row-2;
        }
    }

    return pasc_link->data;
}
      
inline long __step_mul(long x){ // [!] Limitation: x should be smaller than 20
    __exitReturn(x<0, -1);
    
    long res = 1;
    while(--x){
        res*=(x+1);
    }
    return res;
}
      
long __comb(long num,long m){
    __exitReturn(m>num || m<0 || num<0 , -1);
    return __pascal_triangle(num, m);
}
      
long __fibonacci(long n){
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
    


/*===========================================================================================================================
 > Quantity Reference
============================================================================================================================*/
struct IntArray_t __findMax_INT(const int* pValue,size_t num){
    int max = *pValue;
    int cnt = 0;
    while(num--){
        if(*pValue > max)
            max = *pValue;
        pValue++;
        cnt++;
    }
    struct IntArray_t result = {.index = cnt,.value = max};
    return result;
}

struct IntArray_t __findMin_INT(const int* pValue,size_t num){
    int min = *pValue;
    int cnt = 0;
    while(num--){
        if(*pValue < min)
            min = *pValue;
        pValue++;
        cnt++;
    }
    struct IntArray_t result = {.index = cnt,.value = min};
    return result;
}
    
/*===========================================================================================================================
 > Geometry Reference
============================================================================================================================*/
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

int __Vect2D_Dot(const Vector2D_t* vect1,const Vector2D_t* vect2){
    return (int)((vect1->x*vect2->x)+(vect1->y*vect2->y));
}

int __Vect3D_Dot(const Vector3D_t* vect1,const Vector3D_t* vect2){
    return (int)((vect1->x*vect2->x)+(vect1->y*vect2->y)+(vect1->z*vect2->z));
}

Vector3D_t __Vect3D_Cross(const Vector3D_t* vect1,const Vector3D_t* vect2){
    Vector3D_t vecResult = {.x = ( vect1->y*vect2->z - vect1->z*vect2->y),\
                            .y = ( vect1->z*vect2->x - vect1->x*vect2->z),\
                            .z = ( vect1->x*vect2->y - vect1->y*vect2->x)};
    return vecResult;
}

 // -1    = Line is negative.
 //  0    = Line is horizontal.
 //  1    = Line is positive.
 // 65535 = Line is vertical.
int __Dir_Line(int xs,int ys,int xe,int ye){
    if(xs==xe)
        return 65535;
    if(ys==ye)
        return 0;

    return ((xe-xs)*(ye-ys)>0)?(1):(-1);
}

 // -1 = (px,py) is below the line.
 //  0 = (px,py) is at the line.
 //  1 = (px,py) is above the line.
int __Point_toLine(int xs,int ys,int xe,int ye,int px,int py){
    int param_1 = (xe>xs)?( (xe-xs)*py ):( (xs-xe)*py );
    int param_2 = (xe>xs)?( (ye-ys)*px+(ye*(xe-xs)-xe*(ye-ys)) ):( (ys-ye)*px+(ye*(xs-xe)-xe*(ys-ye)) );

    if(param_1 > param_2)
        return 1;
    else if(param_1 < param_2)
        return -1;
    else
        return 0;
}

 // -1 = (px,py) is outside the triangle
 //  0 = (px,py) is at the edge of triangle
 //  1 = (px,py) is inside the triangle
int __Point_toTriangle(int x1,int y1,int x2,int y2,int x3,int y3,int px,int py){
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
    struct Vector2D_t v0 = {.x = x3-x1,.y = y3-y1};
    struct Vector2D_t v1 = {.x = x2-x1,.y = y2-y1};
    struct Vector2D_t v2 = {.x = px-x1,.y = py-y1};

    int v00 = __Vect2D_Dot(&v0,&v0);
    int v01 = __Vect2D_Dot(&v0,&v1);
    int v02 = __Vect2D_Dot(&v0,&v2);
    int v11 = __Vect2D_Dot(&v1,&v1);
    int v12 = __Vect2D_Dot(&v1,&v2);

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
}

 // -1 = (px,py) is outside the circle
 //  0 = (px,py) is at the edge of circle
 //  1 = (px,py) is inside the circle
int __Point_toCircle(int xc,int yc,int radius,int px,int py){
    int key = (xc-px)*(xc-px)+(yc-py)*(yc-py);
    int r_2 = radius*radius;
    if(key > r_2)
        return -1;
    else if(key < r_2)
        return 1;
    else
        return 0;
}

    
 // 0 = origin
 // 1 = Cord 1
 // 2 = Cord 2
 // 3 = Cord 3
 // 4 = Cord 4
 // 5 = Axis +X
 // 6 = Axis -X
 // 7 = Axis +Y
 // 8 = Axis -Y
int __Point_toCord2D(int px,int py){
    if( px==0&&py==0 ) return 0;
    if( py==0 ){
        if( px>0 )  return 5;
        else        return 6;
    } 
    if( px==0 ){
        if( py>0 )  return 7;
        else        return 8;
    }
    uint8_t key = ((py<0)<<1)|(px<0);
    return (int)(((key>>1)^key) +1);
}
    
#ifdef __cplusplus
}
#endif
