#include "./RH_common.h"



const char* RH_DIR_PRJ = NULL;
const char* RH_TIME    = NULL;

void RH_PREMAIN RH_init(void){
    
    // 获取时间
    RH_TIME = __TIME__;
    
    // 获取项目路径
    const char* str = __FILE__;
    size_t len = strlen(str);
    size_t cnt = 0;
    while( cnt<2 && len-- ){
        if( str[len] == '/') cnt++;
    }
    char* p = malloc(len+1);
    memcpy( p, str, len);
    p[len] = '\0';
    RH_DIR_PRJ = p;
    
//    printf("RH_PRJ_DIR: %s\n", RH_DIR_PRJ );
    
    // 获取桌面路径
    
    
}



