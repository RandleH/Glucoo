
#include "BLK_utility.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

static const char** __message_buffer = NULL;

static size_t                 msgCnt = 0;

static char __dummy_message_buffer[MAX_CHARLOG_PER_TIME] = {0};
void __logMessage(const char* format,...){
    const char** p = (const char**)malloc((msgCnt+1)*sizeof(void*)); // 重新建指针数组
    va_list arg;
    va_start(arg, format);
    
    size_t len = vsprintf(__dummy_message_buffer, format, arg);      // 计算本次message字符个数
    
    if( __message_buffer != NULL){
        memmove(p, __message_buffer, msgCnt*sizeof(const char*));    // 拷贝之前存储的指针
        free(__message_buffer);
    }
    
    char* temp = (char*)malloc(len);
    strncpy(temp,__dummy_message_buffer,len);                        // 拷贝内容
    p[msgCnt] = temp;
    
    va_end(arg);

    msgCnt++;
    __message_buffer = p;
}
     
void __deleteMessage(void){
    
}

void __showMessage( int(*PRINTF_METHOD)(const char* ,...)  ){
    __exit( __message_buffer == NULL );
    const char** p = __message_buffer;
    while(msgCnt--){
        if(PRINTF_METHOD != NULL)
            (*PRINTF_METHOD)(*p);
        free((void*)(*p));
        p++;
    }
}
      
    
#ifdef __cplusplus
}
#endif

