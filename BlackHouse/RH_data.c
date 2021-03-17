
#include "RH_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/*=====================================================================
 > Data Structure Reference
======================================================================*/
      
__LinkLoop_t * __LINK_Loop_createHead        ( void* object ){
    __LinkLoop_t *ptr = (__LinkLoop_t*)__malloc(sizeof(__LinkLoop_t));
#ifdef RH_DEBUG
    ASSERT( ptr );
#endif
    __SET_STRUCT_MB(__LinkLoop_t,__LinkLoop_t*,ptr,pNext  ,ptr);
    __SET_STRUCT_MB(__LinkLoop_t,__LinkLoop_t*,ptr,pPrev  ,ptr);
    ptr->object = object;

    return ptr;
}
      
__LinkLoop_t * __LINK_Loop_add               ( const __LinkLoop_t *pHead , void* object ){
#ifdef RH_DEBUG
    ASSERT( pHead );
#endif

    __LinkLoop_t* pNewNode  = (__LinkLoop_t*)__malloc( sizeof(__LinkLoop_t) );
#ifdef RH_DEBUG
    ASSERT( pNewNode );
#endif

    pNewNode->object = object;

    // Things to do for the new Node.
    __SET_STRUCT_MB(__LinkLoop_t,__LinkLoop_t*,pNewNode    ,pPrev,pHead->pPrev   );
    __SET_STRUCT_MB(__LinkLoop_t,__LinkLoop_t*,pNewNode    ,pNext,pHead          );

    // Things to do for the neighbour.
    __SET_STRUCT_MB(__LinkLoop_t,__LinkLoop_t*,pHead->pPrev,pNext,pNewNode           );
    __SET_STRUCT_MB(__LinkLoop_t,__LinkLoop_t*,pHead       ,pPrev,pNewNode           );
    
    return pNewNode;
}
    
__LinkLoop_t * __LINK_Loop_find              ( const __LinkLoop_t *pHead , void* object ){
#ifdef RH_DEBUG
    ASSERT( pHead );
#endif
    
    const __LinkLoop_t* pTmp  = pHead;
    
    do{
        if (pTmp->object ==  object ) {
            return (__LinkLoop_t*)pTmp;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHead );
    
    return NULL;
}
    
void           __LINK_Loop_remove            ( __LinkLoop_t *pHead , void* object ){

#ifdef RH_DEBUG
    ASSERT( pHead );
#endif

    const __LinkLoop_t* pTmp      = pHead;
    
    do{
        if (pTmp->object ==  object ) {
            if( pTmp == pHead ){
                if( pTmp->pNext==pTmp->pPrev && pTmp->pPrev==pHead ){
                    pHead = NULL;
                    __free((void*)pTmp);
                }else{
                    pHead = (__LinkLoop_t*)( pHead->pNext );
                    __SET_STRUCT_MB(__LinkLoop_t, __LinkLoop_t*, pTmp->pPrev, pNext, pTmp->pNext);
                    __SET_STRUCT_MB(__LinkLoop_t, __LinkLoop_t*, pTmp->pNext, pPrev, pTmp->pPrev);
                    __free((void*)pTmp);
                }
            }else{
                // Connect the neighbour and isolate the <pTarget>.
                __SET_STRUCT_MB(__LinkLoop_t, __LinkLoop_t*, pTmp->pPrev, pNext, pTmp->pNext);
                __SET_STRUCT_MB(__LinkLoop_t, __LinkLoop_t*, pTmp->pNext, pPrev, pTmp->pPrev);
                // Same Effect: pTarget->pPrev->pNext = pTarget->pNext; // But to cope with <const>.
                // Same Effect: pTarget->pNext->pPrev = pTarget->pPrev; // But to cope with <const>.
                
                __SET_STRUCT_MB(__LinkLoop_t, __LinkLoop_t*, pTmp, pNext, NULL);
                __SET_STRUCT_MB(__LinkLoop_t, __LinkLoop_t*, pTmp, pPrev, NULL);
                // Same Effect: pTarget->pNext = NULL; // But to cope with <const>.
                // Same Effect: pTarget->pPrev = NULL; // But to cope with <const>.
                __free((void*)pTmp);
            }

            return;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHead );
    
}
    
void           __LINK_Loop_removeAll         ( __LinkLoop_t *pHead ){

#ifdef RH_DEBUG
    ASSERT( pHead );
#endif
    const __LinkLoop_t* pTmp  = pHead;
    do{
        pTmp = pTmp->pNext;
        __free( (void*)(pTmp->pPrev) );
    }while( pTmp != pHead );
    
}

void           __LINK_Loop_printAllNodesAdr  ( const __LinkLoop_t *pHead , int(*PRINTF_FUNC)(const char*,...)){
  
#ifdef RH_DEBUG
    ASSERT( pHead );
#endif
    const __LinkLoop_t* pTmp      = pHead;
    size_t cnt = 0;
    do{
        (*PRINTF_FUNC)("NODE[%d]: %p\n",cnt,pTmp);
        cnt++;
        pTmp = pTmp->pNext;
    }while( pTmp != pHead );

}
    

    
__LinkBiTree_t* __LINK_BiTree_createHead     ( void* object ){
    __LinkBiTree_t* pNewHead = (__LinkBiTree_t*)__malloc(sizeof(__LinkBiTree_t));
#ifdef RH_DEBUG
    ASSERT( pNewHead );
#endif
    __SET_STRUCT_MB(__LinkBiTree_t, __LinkBiTree_t*,pNewHead,pLeft  ,NULL);
    __SET_STRUCT_MB(__LinkBiTree_t, __LinkBiTree_t*,pNewHead,pRight ,NULL);
    __SET_STRUCT_MB(__LinkBiTree_t, __LinkBiTree_t*,pNewHead,pPrev  ,NULL);
    pNewHead->object = object;

    return pNewHead;
}
    
__LinkBiTree_t* __LINK_BiTree_add_l2r        ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object ){

#ifdef RH_DEBUG
    ASSERT( pHead );
    ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    ASSERT( pTarget );
#endif
    __LinkBiTree_t* pNewNode = (__LinkBiTree_t*)__malloc(sizeof(__LinkBiTree_t));
#ifdef RH_DEBUG
    ASSERT( pNewNode );
#endif
    pNewNode->object = object;

    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode , pPrev , pTarget        );
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode , pRight, pTarget->pLeft );
    
    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget->pLeft, pPrev , pNewNode );
    
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget  , pLeft , pNewNode );
    
    return pNewNode;
}
    
__LinkBiTree_t* __LINK_BiTree_add_l2l        ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object ){
#ifdef RH_DEBUG
    ASSERT( pHead );
    ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    ASSERT( pTarget );
#endif
    __LinkBiTree_t* pNewNode = (__LinkBiTree_t*)__malloc(sizeof(__LinkBiTree_t));
#ifdef RH_DEBUG
    ASSERT( pNewNode );
#endif
    pNewNode->object = object;
    
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode , pPrev , pTarget        );
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode , pLeft , pTarget->pLeft );
    
    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget->pLeft, pPrev , pNewNode );
    
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget, pLeft, pNewNode );
    
    return pNewNode;
}
    
__LinkBiTree_t* __LINK_BiTree_add_r2l        ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object ){
#ifdef RH_DEBUG
    ASSERT( pHead );
    ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    ASSERT( pTarget );
#endif
    __LinkBiTree_t* pNewNode = (__LinkBiTree_t*)__malloc(sizeof(__LinkBiTree_t));
#ifdef RH_DEBUG
    ASSERT( pNewNode );
#endif
    pNewNode->object = object;
    
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode , pPrev , pTarget        );
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode , pLeft , pTarget->pLeft );
    
    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget->pRight, pPrev , pNewNode );
    
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget, pRight, pNewNode );
    
    return pNewNode;
}
    
__LinkBiTree_t* __LINK_BiTree_add_r2r        ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object ){
#ifdef RH_DEBUG
    ASSERT( pHead );
    ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    ASSERT( pTarget );
#endif
    __LinkBiTree_t* pNewNode = (__LinkBiTree_t*)__malloc(sizeof(__LinkBiTree_t));
#ifdef RH_DEBUG
    ASSERT( pNewNode );
#endif
    pNewNode->object = object;
    
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode, pPrev , pTarget         );
    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pNewNode, pRight, pTarget->pRight );

    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget->pRight, pPrev , pNewNode );

    __SET_STRUCT_MB( __LinkBiTree_t, __LinkBiTree_t*, pTarget, pRight, pNewNode );

    return pNewNode;
}
    
__LinkBiTree_t* __LINK_BiTree_find           ( const __LinkBiTree_t *pHead , void* object ){
    
#ifdef RH_DEBUG
    ASSERT( pHead );
#endif
    
    __LinkBiTree_t* pTarget = NULL;
    
    if( pHead->object == object ){
        return (__LinkBiTree_t*)pHead;
    }else{
        pTarget = __LINK_BiTree_find( pHead->pLeft , object );
    }
    
    if( !pTarget ){
        pTarget = __LINK_BiTree_find( pHead->pLeft , object );
    }
    
    return pTarget;
}
    
    
E_Status_t __Stack_createBase  ( __Stack_t ** ptr  ){
    __exitReturn( !ptr   , kStatus_BadAccess );
    *ptr = (__Stack_t*)__malloc(sizeof(__Stack_t));
    __exitReturn( !(*ptr), kStatus_NoSpace   );
    __SET_STRUCT_MB(__Stack_t,__Stack_t*,*ptr,pPrev  ,*ptr);
    __SET_STRUCT_MB(__Stack_t,__Stack_t*,*ptr,pNext  ,*ptr);
    
    return kStatus_Success;
}
    
E_Status_t __Stack_push        ( __Stack_t ** ppBase , void* pObject){
    __exitReturn( !ppBase   , kStatus_BadAccess );
    __exitReturn( !*ppBase  , kStatus_BadAccess );
    __exitReturn( !pObject  , kStatus_BadAccess );
    __Stack_t* pNew = (__Stack_t*)__malloc(sizeof(__Stack_t));
    __exitReturn( !pNew     , kStatus_NoSpace   );
    
    __SET_STRUCT_MB(__Stack_t, void*     , pNew            , object, pObject          );
    __SET_STRUCT_MB(__Stack_t, __Stack_t*, pNew            , pPrev , (*ppBase)->pPrev );
    __SET_STRUCT_MB(__Stack_t, __Stack_t*, pNew            , pNext , (*ppBase)        );
    
    __SET_STRUCT_MB(__Stack_t, __Stack_t*, (*ppBase)->pPrev, pNext , pNew             );
    __SET_STRUCT_MB(__Stack_t, __Stack_t*, (*ppBase)       , pPrev , pNew             );
    
    return kStatus_Success;
}
    
E_Status_t __Stack_pop         ( __Stack_t ** ppBase , void     ** pObject){
    __exitReturn( !ppBase   , kStatus_BadAccess );
    __exitReturn( !*ppBase  , kStatus_BadAccess );
    __exitReturn( !pObject  , kStatus_BadAccess );
    __exitReturn((*ppBase)->pNext==(*ppBase)->pPrev && (*ppBase)->pNext==(*ppBase) , kStatus_Empty );
    
    void* dummy_ptr = (__Stack_t*)((*ppBase)->pPrev);
    
    *pObject = (void*)((*ppBase)->pPrev->object);
    
    __SET_STRUCT_MB(__Stack_t, __Stack_t*, (*ppBase)->pPrev->pPrev , pNext, (*ppBase)             );
    __SET_STRUCT_MB(__Stack_t, __Stack_t*, (*ppBase)               , pPrev, (*ppBase)->pPrev->pPrev );
    
    __free(dummy_ptr);
    
    return kStatus_Success;
}
    
E_Status_t __Stack_size        ( __Stack_t ** ppBase , size_t    *  result){
    __exitReturn( !ppBase   , kStatus_BadAccess );
    __exitReturn( !*ppBase  , kStatus_BadAccess );
    __exitReturn( !result   , kStatus_BadAccess );
    __Stack_t *p = *ppBase;
    *result      = 0;
    while(p->pNext!=*ppBase){
        (*result)++;
        p = (__Stack_t*)(p->pNext);
    }
    
    return kStatus_Success;
}
    
E_Status_t __Stack_top         ( __Stack_t ** ppBase , void     **  ppObj ){
    __exitReturn( !ppBase   , kStatus_BadAccess );
    __exitReturn( !*ppBase  , kStatus_BadAccess );
    __exitReturn( !ppObj    , kStatus_BadAccess );
    
    *ppObj = (void*)((*ppBase)->pPrev->object);
    return kStatus_Success;
}
    
E_Status_t __Stack_empty       ( __Stack_t ** ppBase ){
    __exitReturn( !ppBase   , kStatus_BadAccess );
    __exitReturn( !*ppBase  , kStatus_BadAccess );
    
    
    if( (*ppBase)->pNext==(*ppBase)->pPrev && (*ppBase)->pNext==(*ppBase) ){
        return kStatus_Empty;
    }
    
    return kStatus_Success;
}
    
E_Status_t __Stack_deleteBase  ( __Stack_t ** ptr    ){
    __exitReturn( !ptr   , kStatus_BadAccess );
    __exitReturn( !*ptr  , kStatus_BadAccess );
    __Stack_t *p = *ptr;
    if(p->pNext==*ptr){
        __free((void*)(p));
    }else{
        while(p->pNext!=*ptr){
            p = (__Stack_t*)(p->pNext);
            __free((void*)(p->pPrev));
            __SET_STRUCT_MB( __Stack_t, __Stack_t*, p, pPrev , NULL );
        }
    }
    *ptr = NULL;
    return kStatus_Success;
}
    
    
E_Status_t __Queue_createHead  ( __Queue_t ** ptr    ){
    
    return kStatus_Success;
}
    
    
static size_t __HashFunc( size_t key ){
    return (key%RH_HASH_MAP_SIZE);
}
    
E_Status_t __Hash_createMap  ( __HashMap_t** ptr  ){
    __exitReturn( !ptr , kStatus_BadAccess );
    
    *ptr = __malloc( sizeof(__HashMap_t) );
    
    __HashList_t* pHashList = __malloc(RH_HASH_MAP_SIZE*sizeof(__HashList_t));
    __exitReturn( !pHashList, kStatus_NoSpace );
    memset(pHashList, 0, RH_HASH_MAP_SIZE*sizeof(__HashList_t));
    
    __SET_STRUCT_MB(__HashMap_t, __HashList_t*, (*ptr), pList, pHashList);
//    (*ptr)->pList = pHashList;
    
    return kStatus_Success;
}
    
E_Status_t __Hash_find       ( __HashMap_t** ppHead, size_t key ){
    __exitReturn( !ppHead                          , kStatus_BadAccess );
    __exitReturn( !(*ppHead) || (!(*ppHead)->pList), kStatus_BadAccess );

    const __HashList_t *pList = (*ppHead)->pList[ __HashFunc(key)].pNext ;
    
    while( pList != NULL ){
        if( pList->key == key )
            return kStatus_Success;
        pList = pList->pNext;
    }
    
    return kStatus_NotFound;
}
    
E_Status_t __Hash_put        ( __HashMap_t** ppHead, size_t key, void*  pObj  ){
    __exitReturn( !ppHead                          , kStatus_BadAccess );
    __exitReturn( !(*ppHead) || (!(*ppHead)->pList), kStatus_BadAccess );
    
    const __HashList_t *pList     =  ((*ppHead)->pList[ __HashFunc(key) ].pNext);
    const __HashList_t *pList_old = &((*ppHead)->pList[ __HashFunc(key) ]);
    while( pList != NULL ){
        if( pList->key == key ){
            __SET_STRUCT_MB(__HashList_t, void*, pList, object, pObj);
            return kStatus_Success;
        }
        pList_old = pList;
        pList     = (__HashList_t*)pList->pNext;
    }
    pList = pList_old;

    // This key is not exsist in current HashList.
    // Allocate a new node for this pair.
    __SET_STRUCT_MB(__HashList_t, __HashList_t* , pList       , pNext , __malloc(sizeof(__HashList_t)));
    __SET_STRUCT_MB(__HashList_t, size_t        , pList->pNext, key   , key);
    __SET_STRUCT_MB(__HashList_t, void*         , pList->pNext, object, pObj);
    __SET_STRUCT_MB(__HashList_t, void*         , pList->pNext, pNext , NULL);
    return kStatus_Success;
}
    
E_Status_t __Hash_get        ( __HashMap_t** ppHead, size_t key, void** ppObj  ){
    __exitReturn( !ppHead                          , kStatus_BadAccess );
    __exitReturn( !(*ppHead) || (!(*ppHead)->pList), kStatus_BadAccess );
    __exitReturn( !ppObj                           , kStatus_BadAccess );
    
    const __HashList_t *pList = ((*ppHead)->pList[ (long)__HashFunc(key) ].pNext);
    
    *ppObj = NULL;
    while( pList != NULL ){
        if( pList->key == key ){
            (*ppObj) = (void*)pList->object;
            return kStatus_Success;
        }
        pList     = (__HashList_t*)pList->pNext;
    }
    
    return kStatus_NotFound;
}
    
E_Status_t __Hash_remove     ( __HashMap_t** ppHead, size_t key ){
    __exitReturn( !ppHead                          , kStatus_BadAccess );
    __exitReturn( !(*ppHead) || (!(*ppHead)->pList), kStatus_BadAccess );
    
    const __HashList_t *pList     =  ((*ppHead)->pList[ (long)__HashFunc(key) ].pNext);
    const __HashList_t *pList_old = &((*ppHead)->pList[ (long)__HashFunc(key) ]);
    while( pList != NULL ){
        if( pList->key == key ){
            __SET_STRUCT_MB(__HashList_t, __HashList_t*, pList_old, pNext, pList->pNext);
            __free((void*)pList);
            return kStatus_Success;
        }
        pList_old = pList;
        pList     = pList->pNext;
    }
    
    return kStatus_Success;
}
    
E_Status_t __Hash_removeAll  ( __HashMap_t** ptr  ){
    __exitReturn( !ptr                       , kStatus_BadAccess );
    __exitReturn( !(*ptr) || (!(*ptr)->pList), kStatus_BadAccess );
    
    size_t cnt = RH_HASH_MAP_SIZE;
    while(cnt--){
        const __HashList_t *pList_tmp = ((*ptr)->pList[ cnt ].pNext);
        const __HashList_t *pList     = ((*ptr)->pList[ cnt ].pNext);
        while( pList != NULL ){
            pList_tmp = pList->pNext;
            __free((void*)pList);
            pList = pList_tmp;
        }
    }
    __free( (void*)(*ptr)->pList );
    *ptr = NULL;
    return kStatus_Success;
}
    
#ifdef __cplusplus
}
#endif

