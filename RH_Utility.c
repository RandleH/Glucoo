#include "RH_Utility.h"

int __sqrt(int x){
    if(x <= 0) return 0;
    int l   = 1;
    int r   = x;
    int res = 0;
    while(l <= r){
        int mid=(l+r)>>1;
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
// int __Point_toTriangle(int x1,int y1,int x2,int y2,int x3,int y3,int px,int py){

// }

// -1 = (px,py) is outside the circle
//  0 = (px,py) is at the edge of circle
//  1 = (px,py) is inside the circle
// int __Point_toCircle(int xc,int yc,int radius,int px,int py){

// }

// -1 = (px,py) is outside the rectangular
//  0 = (px,py) is at the edge of rectangular
//  1 = (px,py) is inside the rectangular
// int __Point_toRectangular(int x1,int y1,int x2,int y2,int x3,int y3,int px,int py){

// }



