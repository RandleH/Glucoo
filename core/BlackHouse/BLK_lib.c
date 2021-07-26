
#include "BLK_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define M_SWAP_4BIT(x)    ((0x0f)&((((x)&0x55)<<1|((x)>>1)&0x55)&0x33)<<2|((((x)&0x55)<<1|((x)>>1)&0x55)>>2)&0x33)
#define M_SWAP_8BIT(x)    ((M_SWAP_4BIT((x)&0x0f)<<4)|(M_SWAP_4BIT(((x)&0xf0)>>4)))
#define M_SWAP_16BIT(x)   ((M_SWAP_8BIT((x)&0x00ff)<<8)|(M_SWAP_8BIT(((x)&0xff00)>>8)))
#define M_SWAP_32BIT(x)   ((M_SWAP_16BIT((x)&0x0000ffff)<<16)|(M_SWAP_16BIT(((x)&0xffff0000)>>16)))
     
inline uint8_t    BLK_FUNC( Bit, swap8  )   (uint8_t  x){
    return (uint8_t)M_SWAP_8BIT((x&0xff));
}
     
inline uint16_t   BLK_FUNC( Bit, swap16 )   (uint16_t x){
    return (uint16_t)M_SWAP_16BIT((x&0xffff));
}
     
inline uint32_t   BLK_FUNC( Bit, swap32 )   (uint32_t x){
    return (uint32_t)M_SWAP_32BIT((x&0xffffffff));
}
     
inline uint32_t   BLK_FUNC( Bit, swapN  )   (uint32_t x,size_t n){
    return (uint32_t)( M_SWAP_32BIT(x)>>(32-n) );
}

inline uint32_t   BLK_FUNC( Bit, swap   )   (uint32_t x){
    int dummy = 32;
    while((--dummy)&&((1<<dummy)&(x&0xffffffff))==0);
    
    return (uint32_t)( M_SWAP_32BIT(x)>>(32-(dummy+1)) );
}
     
inline size_t     BLK_FUNC( Bit, BINs )  (uint32_t x){
    size_t cnt = 1;
    while(x>>=1){cnt++;}
    return cnt;
}
     
inline size_t     BLK_FUNC( Bit, OCTs )  (uint32_t x){
    size_t cnt = 1;
    while(x>>=3){cnt++;}
    return cnt;
}

inline size_t     BLK_FUNC( Bit, DECs )  (uint32_t x){
    size_t cnt = 1;
    while(x/=10){cnt++;}
    return cnt;
}

inline size_t     BLK_FUNC( Bit, HEXs )  (uint32_t x){
    size_t cnt = 1;
    while(x>>=4){cnt++;}
    return cnt;
}
      
inline uint32_t   BLK_FUNC( Bit, gray2bin )     (uint32_t x){
    RH_ASSERT(0);
    return (uint32_t)((x>>1)^x);
}
      
inline uint32_t   BLK_FUNC( Bit, bin2gray )     (uint32_t x){
    return (uint32_t)((x>>1)^x);
}
    
const char*       BLK_FUNC( Bin, ftoa )     (float    x){
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
    
const char*       BLK_FUNC( Bin, itoa )     (uint8_t  x){
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

const char*       BLK_FUNC( Bin, ltoa )    (uint32_t x){
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
 > Sort Programming Reference
============================================================================================================================*/

#if 0    
typedef int32_t var;
static int __compar( const void* p1, const void* p2 ){

   printf("%d,%d\n", *(var*)p1, *(var*)p2);
   if( *(var*)p2 > *(var*)p1 ){
       return 1;
   }else if( *(var*)p2 < *(var*)p1 ){
       return -1;
   }
   return 0;
}
#endif
    
int BLK_FUNC( Sort, insert ) (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)){
    __exitReturn(nel==0||nel==1, 0);
    
    uint8_t* ptr_iter = ((uint8_t*)base);
    for( long i=1; i<nel; i++, ptr_iter+=width ){
        uint8_t* ptr_tar = alloca(width);  
        uint8_t* ptr_tmp = ptr_iter;
        
        memmove(ptr_tar, (ptr_iter+width), width);
        for (long j=i-1; j>=0; --j, ptr_tmp-=width){
            if( (*compar)( ptr_tmp, ptr_tar )>=0 ){        // compare base[j] & base[i]
                memmove( ptr_tmp+width, ptr_tmp, width );
                continue;
            }
            break;
        }
        memmove( ptr_tmp+width, ptr_tar, width );
    }
    
    return 0;
}
    
int BLK_FUNC( Sort, shell  ) (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)){
    size_t inc = nel-1; // 希尔增量
    
    inc |= inc>>1;
    inc |= inc>>2;
    inc |= inc>>4;
    inc |= inc>>8;
    inc |= inc>>16;
    
    while( inc>1 ){
        inc = ((inc+1)>>1)-1;                             // 希尔增量递推关系式子(自行设定) 此处为 a[n] = 2^n - 1
        // 以下为对步长为 inc 所得到的子数组进行插入排序
        size_t   step     = inc*width;                    // 字节步长 = 单个元素字节数 x 数组步长
        uint8_t* ptr_iter = ((uint8_t*)base);             // 子数组首地址
        for( long i=inc; i<nel; i++, ptr_iter+=width ){
            uint8_t* ptr_tar = alloca(width);
            uint8_t* ptr_tmp = ptr_iter;
            memmove(ptr_tar, ptr_iter+step, width);       // 临时存放选中的元素值
            
            for (long j=i-inc; j>=0; j-=inc, ptr_tmp-=step){
                if( (*compar)( ptr_tmp, ptr_tar )>=0 ){        // compare base[j] & base[i]
                    memmove( ptr_tmp+step, ptr_tmp, width );
                    continue;
                }
                break;
            }
            memmove( ptr_tmp+step, ptr_tar, width );
        }
    }
    
    return 0;
}
    
int BLK_FUNC( Sort, quick  ) (void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)){
    qsort( base, nel, width, compar );
    return 0;
}

/*===========================================================================================================================
 > Quantity Reference
============================================================================================================================*/
void BLK_FUNC( Array, max )(const int* array, size_t size, int* RH_NULLABLE returnVAL, size_t* RH_NULLABLE returnIDX){
    __exit( !array );

    int    VAL = *array;
    size_t IDX = 0;
    while(size--){
        if(*array > VAL)
            VAL = *array;
        array++;
        IDX++;
    }

    if( returnVAL ) (*returnVAL) = VAL;
    if( returnIDX ) (*returnIDX) = IDX;

}

void BLK_FUNC( Array, min )(const int* array, size_t size, int* RH_NULLABLE returnVAL, size_t* RH_NULLABLE returnIDX){
    __exit( !array );

    int    VAL = *array;
    size_t IDX = 0;
    while(size--){
        if(*array < VAL)
            VAL = *array;
        array++;
        IDX++;
    }

    if( returnVAL ) (*returnVAL) = VAL;
    if( returnIDX ) (*returnIDX) = IDX;

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
    
size_t BLK_GVAR( memoryAllocated )  = 0;
size_t BLK_GVAR( memoryFree      )  = RH_ALLOC_CHUNK_SIZE;
    
void* BLK_FUNC( Memory, malloc ) (size_t size){
    size_t size_need       = size;
    if( BLK_GVAR( memoryAllocated ) + size_need > RH_ALLOC_CHUNK_SIZE )
        return NULL;
    else{
        BLK_GVAR( memoryAllocated ) += size_need;
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
        BLK_GVAR( memoryFree ) -= size_need;
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
        BLK_GVAR( memoryAllocated ) -= size_need;
    }
    BLK_GVAR( memoryFree ) = RH_ALLOC_CHUNK_SIZE - BLK_GVAR( memoryAllocated );
    return ptr;
}

void* BLK_FUNC( Memory, calloc ) (size_t count, size_t size){
    size_t  byt = count*size;
    void*   ptr = BLK_FUNC( Memory, malloc )(byt);
#ifdef RH_DEBUG
    RH_ASSERT( ptr );
#else
    __exitReturn(ptr==NULL, ptr);
#endif
    
    return memset( ptr, 0, byt );
}

void  BLK_FUNC( Memory, free   ) (void* ptr){
    unsigned long index = (unsigned long)((unsigned char*)ptr - __VERTUAL_HEAP);
    struct __MallocNode_t* pNode     = pHeapMemoryHeadNode;
    struct __MallocNode_t* pForeward = NULL;
    while(pNode != NULL){
        if(pNode->index == index && pNode->ptr == ptr){
            if(pForeward != NULL){
                pForeward->pNextNode = pNode->pNextNode;
                BLK_GVAR( memoryAllocated ) -= pNode->byte;
                free(pNode);
            }else{
                // 前节点为空只可能pNode为pHeapMemoryHeadNode
            #ifdef RH_DEBUG
                RH_ASSERT( pNode == pHeapMemoryHeadNode );
                RH_ASSERT( pNode->ptr == __VERTUAL_HEAP );
            #endif
                BLK_GVAR( memoryAllocated ) -= pNode->byte;
                pHeapMemoryHeadNode = NULL;
                free(pNode);
            }
            break;
        }
        pForeward = pNode;
        pNode     = pNode->pNextNode;
    }
    BLK_GVAR( memoryFree ) = RH_ALLOC_CHUNK_SIZE - BLK_GVAR( memoryAllocated );
}    

    
    
#include "BLK_data.h"
size_t BLK_GVAR( debug_memoryAllocated ) = 0;
size_t BLK_GVAR( debug_memoryFree      ) = 0;
static BLK_SRCT(HashMap)* pHEAD_HASHMAP_size_2_ptr = NULL;
    
struct __RH_DebugMemoryInfo_t{
    size_t      byte;
    const char* FILE;
    uint32_t    LINE;
    void*       ptr;
};
    
void* BLK_FUNC( Memory, debug_malloc   )( size_t size, char* FILE, int LINE, void* (*__malloc_func)(size_t size) ){
    if( !pHEAD_HASHMAP_size_2_ptr )
        pHEAD_HASHMAP_size_2_ptr = BLK_FUNC(Hash, createMap)();
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
    
    BLK_GVAR( debug_memoryAllocated ) += pInfo->byte;
    BLK_FUNC(Hash, pair)(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr, pInfo);
    
    return ptr;
}

void* BLK_FUNC( Memory, debug_calloc   )( size_t count, size_t size, char* FILE, int LINE, void* (*__calloc_func)( size_t, size_t ) ){
    
    if( !pHEAD_HASHMAP_size_2_ptr )
        pHEAD_HASHMAP_size_2_ptr = BLK_FUNC(Hash, createMap)();
    
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
    
    BLK_GVAR( debug_memoryAllocated ) += pInfo->byte;
    BLK_FUNC(Hash, pair)(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr, pInfo);
    
    return ptr;
}

void  BLK_FUNC( Memory, debug_free     )( void* ptr, void (*__free_func)(void*)){
    struct __RH_DebugMemoryInfo_t* pInfo = (struct __RH_DebugMemoryInfo_t*)BLK_FUNC(Hash, get)(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr);
    BLK_GVAR( debug_memoryAllocated ) -= pInfo->byte;
         
    (*__free_func)(ptr);

}
    
void* BLK_FUNC( Memory, debug_print    )( void* ptr, int (*__print_func)(const char * restrict format, ...)){
    __exitReturn( __print_func==NULL, ptr);
    
    struct __RH_DebugMemoryInfo_t* pInfo = (struct __RH_DebugMemoryInfo_t*)BLK_FUNC(Hash, get)(pHEAD_HASHMAP_size_2_ptr, (size_t)ptr);
#ifdef RH_DEBUG
    RH_ASSERT( pInfo->ptr==ptr );
#endif
    size_t len = strlen("$DEBUG_MEM_INFO: [] [Ln ] [: byte]\n")+strlen(pInfo->FILE)+((sizeof(pInfo->LINE)+sizeof(pInfo->byte))<<3);
    char*  str = alloca( len + sizeof('\0') );
    
    snprintf(str, len, "$DEBUG_MEM_INFO: [%s] [Ln %d] [%zu:%zu Byte]\n",pInfo->FILE,pInfo->LINE,pInfo->byte,BLK_GVAR( debug_memoryAllocated ));
    
    (*__print_func)("%s",str);
    
    return ptr;
}
    
void  BLK_FUNC( Memory, debug_delCache )( void ){
    BLK_FUNC(Hash, removeAll)(pHEAD_HASHMAP_size_2_ptr);
    pHEAD_HASHMAP_size_2_ptr = NULL;
    BLK_GVAR( debug_memoryAllocated )    = 0;
}

void* BLK_FUNC( Memory, setWord        )(void* __b,uint16_t value,size_t num){
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

void* BLK_FUNC( Memory, setDWord       )(void* __b,uint32_t value,size_t num){
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
    
void* BLK_FUNC( Memory, exchange       )(void* __a, void* __b, size_t size ){
    uint8_t* a = __a;
    uint8_t* b = __b;
    while(size--){
        __swap(__MEM_BYTE(a), __MEM_BYTE(b));
        a++;
        b++;
    }
    
    return __b;
}

void* BLK_FUNC( Memory, setArea        )(void* __b,int value,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
    if(__b == NULL)
        return __b;
    
    const size_t num_objs = (xe-xs+1)*size;
    
    for(size_t y = ys;y <= ye;y++){
        size_t offset = size*(nmenb_line*y + xs);
        memset( ((char*)__b + offset) , value, num_objs );
    }
    
    return __b;
}
         
void* BLK_FUNC( Memory, cpyArea        )(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
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

void* BLK_FUNC( Memory, grbArea        )(void* __restrict__ __dst,const void* __restrict__ __src,size_t size,size_t nmenb_line,long xs,long ys,long xe,long ye){
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
    
#include <stdlib.h>
char* BLK_FUNC( Dir, realpath   ) (const char * RH_RESTRICT file_name, char *RH_RESTRICT resolved_name){
    return realpath(file_name, resolved_name);
}

char* BLK_FUNC( Dir, back       ) (const char * RH_RESTRICT path_name, char *RH_RESTRICT answer, size_t size, int backlevel ){
#warning "Got some problems here."
    
    if( !answer ) return NULL;

    char* str = alloca(strlen(path_name));
    realpath( path_name, str );
    size_t len = strlen(str);
    int cnt = 0;
    while( cnt<backlevel && len-- ){
        if( str[len] == '/') cnt++;
    }
    str[len] = '\0';
    return strcpy( answer, str);
}

#ifdef __cplusplus
}
#endif

