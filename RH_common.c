
#include <unistd.h>
#include "RH_common.h"


const char* RH_DIR   = NULL;
const char* RH_TIME  = NULL;

void RH_PREMAIN RH_init(void){
    
    // 获取时间
    RH_TIME = __TIME__;
    
    // 获取项目路径
    char temp[1024] = {0};
    if( realpath( __FILE__, temp )==NULL ){
        // printf("Path is too long\n");
        while(1);
    }
    
    *(strstr( temp, "RH_common.c" )-1) = '\0';

    // Allocate enough space for coping string.    
    RH_DIR = strcpy( calloc(strlen(temp)+1, sizeof(char)), temp ); 
    
    // printf("RH_DIR: %s\n", RH_DIR );
    
    
}



