//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/4/7.
//

#include <stdio.h>
#include <ctype.h>
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_color.h"
#include <time.h>

#include "RH_data.h"




struct __Element_t{
    int     val;
    size_t  idx;
};

int largestRectangleArea(int* heights, int heightsSize){
    typedef long var;
    
    
    int ans      = 0;                            // 最终结果
    
    __Stack_t* s = __Stack_createBase( NULL );   // 创建栈, 记录的数据为下标索引
    
    __Stack_push(s, (void*)(-1));                          // [边界问题] 初始化, 第一个入栈元素,下标为-1, 假设最开始元素高度为0
    
    for( size_t i=0; i<=heightsSize; i++ ){
        if( i!=heightsSize ){                              // [边界问题] 最后一个元素, 下标为heightsSize, 假设最后一个元素高度为0, 因此无需入栈了
            if( heights[(int)__Stack_top(s)] <= heights[i] ){  // 栈顶元素小于等于当前遍历的元素, 则入栈
                __Stack_push(s, (void*)i);
                continue;
            }
        }
        int h = (i==heightsSize)?0:heights[i];
        while( (var)__Stack_top(s)!=-1 && heights[(var)__Stack_top(s)] > h ){   // 直到栈顶元素比当前遍历的元素还要小,否则退栈并结算矩形面积
            var idx_pop = (var)__Stack_pop(s);                  // [关键] 该元素为当前栈顶存储的下标索引
            var idx_top = (var)__Stack_top(s);                  // [关键] 该元素为新栈顶存储的下标索引
            
            // idx_pop 与 idx_top 不一样
            
            
            if( heights[idx_pop] * (i-idx_top-1) > ans ) {      // 矩形面积 = 栈顶元素对应的高度 * (当前遍历元素的下标-退栈后新栈顶元素-1)
                ans = (int)( heights[idx_pop]*(i-idx_top-1) );
            }
            printf("ans=%ld h=%d L=%ld R=%ld\n",heights[idx_pop] * (i-idx_top-1), heights[idx_pop], idx_top, i);
        }
        
        __Stack_push(s, (void*)i);
    }
    
    return ans;
}

int array[] = { 2,1,5,6,2,3 };

int main(int argc, const char * argv[]) {

//    Simul_API_Init();
//
//    GUI_Init();
//    GUI_set_penSize(5);
//    GUI_set_penColor(M_COLOR_WHITE);

    
    largestRectangleArea( array, sizeof(array)/sizeof(*array) );
    return 0;
}
