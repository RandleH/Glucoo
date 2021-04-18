
#include "RH_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define M_SWAP_4BIT(x)    ((0x0f)&((((x)&0x55)<<1|((x)>>1)&0x55)&0x33)<<2|((((x)&0x55)<<1|((x)>>1)&0x55)>>2)&0x33)
#define M_SWAP_8BIT(x)    ((M_SWAP_4BIT((x)&0x0f)<<4)|(M_SWAP_4BIT(((x)&0xf0)>>4)))
#define M_SWAP_16BIT(x)   ((M_SWAP_8BIT((x)&0x00ff)<<8)|(M_SWAP_8BIT(((x)&0xff00)>>8)))
#define M_SWAP_32BIT(x)   ((M_SWAP_16BIT((x)&0x0000ffff)<<16)|(M_SWAP_16BIT(((x)&0xffff0000)>>16)))
     
inline uint8_t    __swap_8BIT    (uint8_t  x){
    return (uint8_t)M_SWAP_8BIT((x&0xff));
}
     
inline uint16_t   __swap_16BIT   (uint16_t x){
    return (uint16_t)M_SWAP_16BIT((x&0xffff));
}
     
inline uint32_t   __swap_32BIT   (uint32_t x){
    return (uint32_t)M_SWAP_32BIT((x&0xffffffff));
}
     
inline uint32_t   __swap_nBIT    (uint32_t x,size_t n){
    return (uint32_t)( M_SWAP_32BIT(x)>>(32-n) );
}

inline uint32_t   __swap_DATA    (uint32_t x){
    int dummy = 32;
    while((--dummy)&&((1<<dummy)&(x&0xffffffff))==0);
    
    return (uint32_t)( M_SWAP_32BIT(x)>>(32-(dummy+1)) );
}
     
inline size_t     __sizeof_BINs  (uint32_t x){
    size_t cnt = 1;
    while(x>>=1){cnt++;}
    return cnt;
}
     
inline size_t     __sizeof_OCTs  (uint32_t x){
    size_t cnt = 1;
    while(x>>=3){cnt++;}
    return cnt;
}

inline size_t     __sizeof_DECs  (uint32_t x){
    size_t cnt = 1;
    while(x/=10){cnt++;}
    return cnt;
}

inline size_t     __sizeof_HEXs  (uint32_t x){
    size_t cnt = 1;
    while(x>>=4){cnt++;}
    return cnt;
}
      
inline uint32_t   __Gray2Bin     (uint32_t x){
    return (uint32_t)((x>>1)^x);
}
      
inline uint32_t   __Bin2Gray     (uint32_t x){
    return (uint32_t)((x>>1)^x);
}
    
const char*       __ftoa_BIN     (float    x){
    static char pTmp[(sizeof(float)<<3)+1] = {0};
    char* pTmp_iter = pTmp;
    
    uint8_t* pNum = ((uint8_t*)(&x))+sizeof(float) - 1;
    
    memset( pTmp , '\0' ,  (sizeof(float)<<3)+1 );
    size_t size = sizeof(float);
    
    while(size--){
        size_t byte = 8;
        while(byte--){
            (*pTmp_iter) = '0'+(((*(uint8_t*)(pNum))>>byte)&0x01);
            pTmp_iter++;
        }
        pNum--;
    }
    return pTmp;
}
    
const char*       __btoa_BIN     (uint8_t  x){
    static char pTmp[(sizeof(uint8_t)<<3)+1] = {0};
    
    memset( pTmp , '\0' ,  (sizeof(uint8_t)<<3)+1 );
    
    union{
        struct{
            uint8_t bit0 : 1;
            uint8_t bit1 : 1;
            uint8_t bit2 : 1;
            uint8_t bit3 : 1;
            uint8_t bit4 : 1;
            uint8_t bit5 : 1;
            uint8_t bit6 : 1;
            uint8_t bit7 : 1;
        };
        uint8_t x;
    }value;
    value.x = x;
    
    pTmp[0] = value.bit7 + '0';
    pTmp[1] = value.bit6 + '0';
    pTmp[2] = value.bit5 + '0';
    pTmp[3] = value.bit4 + '0';
    pTmp[4] = value.bit3 + '0';
    pTmp[5] = value.bit2 + '0';
    pTmp[6] = value.bit1 + '0';
    pTmp[7] = value.bit0 + '0';

    return pTmp;
}

const char*       __ldtoa_BIN    (uint32_t x){
    static char pTmp[(sizeof(uint32_t)<<3)+1] = {0};
    char* pTmp_iter = pTmp;
    
    uint8_t* pNum = ((uint8_t*)(&x))+sizeof(uint32_t) - 1;
    
    memset( pTmp , '\0' ,  (sizeof(uint32_t)<<3)+1 );
    size_t size = sizeof(uint32_t);
    
    while(size--){
        size_t byte = 8;
        while(byte--){
            (*pTmp_iter) = '0'+(((*(uint8_t*)(pNum))>>byte)&0x01);
            pTmp_iter++;
        }
        pNum--;
    }
    return pTmp;
}

/*===========================================================================================================================
 > Memory Programming Reference
============================================================================================================================*/

#if   ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__NONE )
#define RH_ALLOC_CHUNK_SIZE   (1)
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__64B )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__64B
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__128B )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__128B
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__256B )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__256B
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__512B )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__512B
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__1KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__1KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__2KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__2KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__4KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__4KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__8KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__8KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__16KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__16KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__32KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__32KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__64KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__64KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__128KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__128KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__256KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__256KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__512KB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__512KB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__1MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__1MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__2MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__2MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__4MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__4MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__8MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__8MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__16MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__16MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__32MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__32MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__64MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__64MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__128MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__128MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__256MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__256MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__512MB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__512MB
#elif ( RH_CFG_MALLOC_SIZE == RH_CFG_MALLOC_SIZE__1GB )
#define RH_ALLOC_CHUNK_SIZE   RH_CFG_MALLOC_SIZE__1GB
#else
#error "Unknown size for allocating memory. "
#endif
    
#ifndef M_ADR_OFFSET
#define M_ADR_OFFSET( ptr1 , ptr2 )   (size_t)((__abs(ptr2 - ptr1)) - 1)
#endif
         
#pragma pack(1)
unsigned char __VERTUAL_HEAP[ RH_ALLOC_CHUNK_SIZE ];//__attribute__((at()));


struct __MallocNode_t{
    unsigned long            index;
    size_t                   byte;
    void*                    ptr;
    struct __MallocNode_t*   pNextNode;
}*pHeapMemoryHeadNode = NULL;

    /*--------------------------------------------------------------------------------------------------------
     * Memory Node Should be odered by the member of index
     *
     *
     *    Node1     ->>   Node2       ->>     Node3             ->>      Node4       Nodes
     *    Memory1   ->>   Memory2     ->>     Memory3           ->>      Memory4     Used Memory
     *       |               |                   |                          |
     *       |               |                   |                          |
     * [ xxxxxxxxx________xxxxxxx_______xxxxxxxxxxxxxxxxxxx____________xxxxxxxxxxx________ ] Virtual Heap
     * index=0                                                                   index=32768
     *
     --------------------------------------------------------------------------------------------------------*/
    
size_t RH_Global_alloced_byte  = 0;
size_t RH_Global_free_byte     = RH_ALLOC_CHUNK_SIZE;
void* __RH_Global_malloc(size_t size){
    size_t size_need       = size;
    if( RH_Global_alloced_byte + size_need > RH_ALLOC_CHUNK_SIZE )
        return NULL;
    else{
        RH_Global_alloced_byte += size_need;
        // It doesn't mean there is enough space to allocate.
    }
    
    void* ptr = NULL;
    struct __MallocNode_t* pNode     = pHeapMemoryHeadNode;
    struct __MallocNode_t* pNewNode  = (struct __MallocNode_t*)malloc(sizeof(struct __MallocNode_t));
    struct __MallocNode_t* pForeward = NULL,*pBackward = NULL;
    size_t minDist                   = RH_ALLOC_CHUNK_SIZE;
    
    pNewNode->byte      = size_need;
    pNewNode->pNextNode = NULL;
    
    // Special Condition. There isn't any allocated memory.
    if(pNode == NULL){
        pHeapMemoryHeadNode = pNewNode;
        pNewNode->index     = 0;
        pNewNode->ptr       = ptr = &__VERTUAL_HEAP[pNewNode->index];
        RH_Global_free_byte -= size_need;
        return ptr;
    }
    
    // Search the optimal memory block for users.
    while(pNode != NULL){
        size_t size_free = 0;
        // All nodes should be ordered by the member of "index". Which means...
        // "pNode->index" is always ahead of "pNextNode->index" or there will be a problem.
        if(pNode->pNextNode != NULL){
            size_free = (pNode->pNextNode->index) - (pNode->index + pNode->byte);
        }else{
            size_free = (RH_ALLOC_CHUNK_SIZE-1) - ((pNode->index) + (pNode->byte));
        }
        if( size_free - size_need < minDist && size_free >= size_need ){
            minDist             = size_free - size_need;
            ptr                 = &__VERTUAL_HEAP[ (pNode->index + pNode->byte) ];

            pForeward           = pNode;
            pBackward           = pNode->pNextNode;
            pNewNode->index     = (pForeward->index + pForeward->byte);
            pNewNode->pNextNode = pBackward;
            pNewNode->ptr       = ptr;
        }
        // Continue to search...
        pNode = pNode->pNextNode;
    }
    
    if(ptr != NULL && pForeward != NULL && pNewNode != NULL){
        // Found enough space to allocate
        pForeward->pNextNode = pNewNode;
        pNewNode->pNextNode  = pBackward;
    }else{
        // Fail to find enough space to allocate
        free(pNewNode);
        RH_Global_alloced_byte -= size_need;
    }
    RH_Global_free_byte = RH_ALLOC_CHUNK_SIZE - RH_Global_alloced_byte;
    return ptr;
}

void* __RH_Global_calloc(size_t count, size_t size){
    size_t  byt = count*size;
    void*   ptr = __RH_Global_malloc(byt);
#ifdef RH_DEBUG
    RH_ASSERT( ptr );
#else
    __exitReturn(ptr==NULL, ptr);
#endif
    
    return memset( ptr, 0, byt );
}

void __RH_Global_free(void* ptr){
    unsigned long index = (unsigned long)((unsigned char*)ptr - __VERTUAL_HEAP);
    struct __MallocNode_t* pNode     = pHeapMemoryHeadNode;
    struct __MallocNode_t* pForeward = NULL;
    while(pNode != NULL){
        if(pNode->index == index && pNode->ptr == ptr){
            if(pForeward != NULL){
                pForeward->pNextNode = pNode->pNextNode;
                RH_Global_alloced_byte -= pNode->byte;
                free(pNode);
            }else{
                // 前节点为空只可能pNode为pHeapMemoryHeadNode
            #ifdef RH_DEBUG
                RH_ASSERT( pNode == pHeapMemoryHeadNode );
                RH_ASSERT( pNode->ptr == __VERTUAL_HEAP );
            #endif
                RH_Global_alloced_byte -= pNode->byte;
                pHeapMemoryHeadNode = NULL;
                free(pNode);
            }
            break;
        }
        pForeward = pNode;
        pNode     = pNode->pNextNode;
    }
    RH_Global_free_byte = RH_ALLOC_CHUNK_SIZE - RH_Global_alloced_byte;
}    

    
    
#include "RH_data.h"
size_t RH_Debug_alloced_byte = 0;
size_t RH_Debug_free_byte    = 0;
static __HashMap_t* pHEAD_HASHMAP_size_2_ptr = NULL;
    
struct __RH_DebugMemoryInfo_t{
    size_t      byte;
    const char* FILE;
    uint32_t    LINE;
    void*       ptr;
};
    
void* __RH_Debug_malloc( size_t size, char* FILE, int LINE, void* (*__malloc_func)(size_t size) ){
    if( !pHEAD_HASHMAP_size_2_ptr )
        pHEAD_HASHMAP_size_2_ptr = __Hash_createMap();
//    size_t* pSize = malloc(sizeof(size_t));
//    *pSize = size;
    
    struct __RH_DebugMemoryInfo_t* pInfo = malloc(sizeof(struct __RH_DebugMemoryInfo_t));
    
    void* ptr = (*__malloc_func)(size);
#ifdef RH_DEBUG
    RH_ASSERT( ptr );
    RH_ASSERT( pInfo );
#endif
    pInfo->ptr  = ptr;
    pInfo->FILE = FILE;
    pInfo->LINE = LINE;
    pInfo->byte = size;
    
    RH_Debug_alloced_byte += pInfo->byte;
    __Hash_pair(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr, pInfo);
    
    return ptr;
}

void* __RH_Debug_calloc( size_t count, size_t size, char* FILE, int LINE, void* (*__calloc_func)( size_t, size_t ) ){
    
    if( !pHEAD_HASHMAP_size_2_ptr )
        pHEAD_HASHMAP_size_2_ptr = __Hash_createMap();
    
    struct __RH_DebugMemoryInfo_t* pInfo = malloc(sizeof(struct __RH_DebugMemoryInfo_t));
    void* ptr = (*__calloc_func)( count,size );
#ifdef RH_DEBUG
    RH_ASSERT( ptr );
    RH_ASSERT( pInfo );
#endif
    
    pInfo->ptr  = ptr;
    pInfo->FILE = FILE;
    pInfo->LINE = LINE;
    pInfo->byte = count*size;
    
    RH_Debug_alloced_byte += pInfo->byte;
    __Hash_pair(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr, pInfo);
    
    return ptr;
}

void __RH_Debug_free(void* ptr, void (*__free_func)(void*)){
    struct __RH_DebugMemoryInfo_t* pInfo = (struct __RH_DebugMemoryInfo_t*)__Hash_get(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr);
    RH_Debug_alloced_byte -= pInfo->byte;
         
    (*__free_func)(ptr);

}
    
void* __RH_Debug_print_memory_info(void* ptr, int (*__print_func)(const char * restrict format, ...)){
    __exitReturn( __print_func==NULL, ptr);
    
    struct __RH_DebugMemoryInfo_t* pInfo = (struct __RH_DebugMemoryInfo_t*)__Hash_get(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr);
#ifdef RH_DEBUG
    RH_ASSERT( pInfo->ptr==ptr );
#endif
    size_t len = strlen("$DEBUG_MEM_INFO: [] [Ln ] [: byte]\n")+strlen(pInfo->FILE)+((sizeof(pInfo->LINE)+sizeof(pInfo->byte))<<3);
    char*  str = alloca( len + sizeof('\0') );
    
    snprintf(str, len, "$DEBUG_MEM_INFO: [%s] [Ln %d] [%zu:%zu Byte]\n",pInfo->FILE,pInfo->LINE,pInfo->byte,RH_Debug_alloced_byte);
    
    (*__print_func)("%s",str);
    
    return ptr;
}
    
void __RH_Debug_del_memory_info(void){
    __Hash_removeAll(pHEAD_HASHMAP_size_2_ptr);
    pHEAD_HASHMAP_size_2_ptr = NULL;
    RH_Debug_alloced_byte    = 0;
}

void* __memsetWORD(void* __b,uint16_t value,size_t num){
    uint16_t* src = (uint16_t*)__b;
#if !defined( __CC_ARM )
    if( sizeof(wchar_t) == sizeof(uint16_t) ){
        wmemset((wchar_t*)src, value, num);
    }else
#endif
    {
        size_t remain = num;
        (*((uint16_t*)src)) = value;
        remain--;
        while(1){
            if(num<(remain<<1)){
                memmove((src+(num-remain)),src, (num-remain)*sizeof(uint16_t));
                remain-=(num-remain);
            }else{
                memmove((src+(num-remain)),src, remain*sizeof(uint16_t));
                break;
            }
        }
    }
    return __b;
}

void* __memsetDWORD(void* __b,uint32_t value,size_t num){
    uint32_t* src = (uint32_t*)__b;
#if !defined( __CC_ARM )
    if( sizeof(wchar_t) == sizeof(uint32_t) ){
        wmemset((wchar_t*)src, (int)value, num);
    }else
#endif
    {
        size_t remain = num;
        (*((uint32_t*)src)) = (uint32_t)value;
        remain--;
        while(1){
            if(num<(remain<<1)){
                memmove((src+(num-remain)),src, (num-remain)*sizeof(uint32_t));
                remain-=(num-remain);
            }else{
                memmove((src+(num-remain)),src, remain*sizeof(uint32_t));
                break;
            }
        }
    }
    return __b;
}
    
void* __memexch     (void* __a, void* __b, size_t size ){
    uint8_t* a = __a;
    uint8_t* b = __b;
    while(size--){
        __swap(__MEM_BYTE(a), __MEM_BYTE(b));
        a++;
        b++;
    }
    
    return __b;
}

void* __memset_Area(void* __b,int value,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
    if(__b == NULL)
        return __b;
    
    const size_t num_objs = (xe-xs+1)*size;
    
    for(size_t y = ys;y <= ye;y++){
        size_t offset = size*(nmenb_line*y + xs);
        memset( ((char*)__b + offset) , value, num_objs );
    }
    
    return __b;
}
         
void* __memcpy_Area(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
    if (__dst == NULL){
        return __dst;
    }

    const size_t num_objs = (xe-xs+1)*size;

    for(size_t y = ys;y <= ye;y++){
        size_t offset = size*(nmenb_line*y + xs);
        memcpy( ((char*)__dst + offset) , ((char*)__src + offset), num_objs );
    }

    return __dst;
}

void* __memgrab_Area(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
    __exitReturn( __dst==NULL || __src==NULL , NULL);
    __exitReturn( xs < 0 || xe < 0 || ys < 0 || ye < 0 , NULL);

    const size_t num_objs = (xe-xs+1)*size;
    char* p = __dst;
    for(size_t y = ys;y <= ye;y++){
        size_t offset = size*(nmenb_line*y + xs);
        memmove( p , ((char*)__src+offset), num_objs );
        p += num_objs;
    }
    
    return __dst;
}



#ifdef __cplusplus
}
#endif

