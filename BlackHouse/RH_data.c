
#include "RH_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/*=====================================================================
 > Data Structure Reference
======================================================================*/
      
E_Status_t __LINK_Loop_createHead        ( __LinkLoopNode **  ptr    , void* object ){
    *ptr =  (__LinkLoopNode*)__malloc(sizeof(__LinkLoopNode));
  
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,*ptr,pNext  ,*ptr);
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,*ptr,pPrev  ,*ptr);
    (*ptr)->object = object;

    return kStatus_Success;
}
      
E_Status_t __LINK_Loop_add               ( __LinkLoopNode **  ppHead , void* object ){
    __exitReturn(  ppHead == NULL  , kStatus_BadAccess);
    __exitReturn( *ppHead == NULL  , kStatus_BadAccess);

    __LinkLoopNode* pHeadNode = *ppHead;
    __LinkLoopNode* pNewNode  = (__LinkLoopNode*)__malloc( sizeof(__LinkLoopNode) );
    
    __exitReturn( pNewNode == NULL  , kStatus_NoSpace );
    pNewNode->object = object;

    // Things to do for the new Node.
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNewNode        ,pPrev,pHeadNode->pPrev   );
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pNewNode        ,pNext,pHeadNode          );

    // Things to do for the neighbour.
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pHeadNode->pPrev,pNext,pNewNode           );
    __SET_STRUCT_MB(__LinkLoopNode,__LinkLoopNode*,pHeadNode       ,pPrev,pNewNode           );

    return kStatus_Success;
}
    
E_Status_t __LINK_Loop_find              ( __LinkLoopNode **  ppHead , void* object ){
    __exitReturn(  ppHead == NULL || *ppHead==NULL , kStatus_BadAccess);
    
    __LinkLoopNode* pHeadNode = *ppHead;
    
    const __LinkLoopNode* pTmp  = pHeadNode;
    
    do{
        if (pTmp->object ==  object ) {
            return kStatus_Success;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHeadNode );
    return kStatus_NotFound;
}

E_Status_t __LINK_Loop_remove            ( __LinkLoopNode **  ppHead , void* object ){
    __exitReturn(  ppHead==NULL , kStatus_BadAccess );
    __exitReturn( *ppHead==NULL , kStatus_BadAccess );
    __LinkLoopNode* pHeadNode = *ppHead;
    const __LinkLoopNode* pTmp      = pHeadNode;
    
    do{
        if (pTmp->object ==  object ) {
            if( pTmp == *ppHead ){
                if( pTmp->pNext==pTmp->pPrev && pTmp->pPrev==*ppHead ){
                    *ppHead = NULL;
                    __free((void*)pTmp);
                }else{
                    *ppHead = (__LinkLoopNode*)( (*ppHead)->pNext );
                    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmp->pPrev, pNext, pTmp->pNext);
                    __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmp->pNext, pPrev, pTmp->pPrev);
                    __free((void*)pTmp);
                }
            }else{
                // Connect the neighbour and isolate the <pTarget>.
                __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmp->pPrev, pNext, pTmp->pNext);
                __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmp->pNext, pPrev, pTmp->pPrev);
                // Same Effect: pTarget->pPrev->pNext = pTarget->pNext; // But to cope with <const>.
                // Same Effect: pTarget->pNext->pPrev = pTarget->pPrev; // But to cope with <const>.
                
                __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmp, pNext, NULL);
                __SET_STRUCT_MB(__LinkLoopNode, __LinkLoopNode*, pTmp, pPrev, NULL);
                // Same Effect: pTarget->pNext = NULL; // But to cope with <const>.
                // Same Effect: pTarget->pPrev = NULL; // But to cope with <const>.
                __free((void*)pTmp);
            }

            return kStatus_Success;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHeadNode );
    
    return kStatus_NotFound;
}
    
E_Status_t __LINK_Loop_removeAll         ( __LinkLoopNode **  ppHead ){
    __exitReturn( !ppHead || !(*ppHead) , kStatus_BadAccess );
    
    const __LinkLoopNode* pTmp  = *ppHead;
    do{
        pTmp = pTmp->pNext;
        __free( (void*)(pTmp->pPrev) );
    }while( pTmp != *ppHead );
    
    return kStatus_Success;
}

E_Status_t __LINK_Loop_printAllNodesAdr  ( __LinkLoopNode **  ppHead , int(*PRINTF_FUNC)(const char*,...)){
  
    __exitReturn(ppHead == NULL, kStatus_BadAccess);
    
    const __LinkLoopNode* pHeadNode = *ppHead;
    const __LinkLoopNode* pTmp      = pHeadNode;
    size_t cnt = 0;
    do{
        (*PRINTF_FUNC)("NODE[%d]: %p\n",cnt,pTmp);
        cnt++;
        pTmp = pTmp->pNext;
    }while( pTmp != pHeadNode );
        
    return kStatus_Success;
}
    
E_Status_t __LINK_BiTree_createNode            (__LinkBiTreeNode **  ptr ){
    __exitReturn(ptr==NULL, kStatus_BadAccess );
    
    *ptr = (__LinkBiTreeNode*)__malloc(sizeof(__LinkBiTreeNode));
    __exitReturn(*ptr==NULL, kStatus_NoSpace  );
    __SET_STRUCT_MB(__LinkBiTreeNode,__LinkBiTreeNode*,*ptr,pLeft  ,NULL);
    __SET_STRUCT_MB(__LinkBiTreeNode,__LinkBiTreeNode*,*ptr,pRight ,NULL);
    __SET_STRUCT_MB(__LinkBiTreeNode,__LinkBiTreeNode*,*ptr,pPrev  ,NULL);
    return kStatus_Success;
}
    
E_Status_t __LINK_BiTree_createHeadNode        (__LinkBiTreeNode **  ptr ){
    E_Status_t state = MAKE_FUNC(LINK_BiTree, createNode)(ptr);
    __exitReturn(state!=kStatus_Success,state);
    __SET_STRUCT_MB(__LinkBiTreeNode,__LinkBiTreeNode*,*ptr,pPrev  ,NULL);
    return kStatus_Success;
}
    
E_Status_t __LINK_BiTree_addNode_l2r           (__LinkBiTreeNode ** ppHead , __LinkBiTreeNode ** ppTarget , __LinkBiTreeNode ** ppNew){
    __exitReturn( ppHead==NULL || ppTarget==NULL || ppNew==NULL , kStatus_BadAccess );
    __exitReturn(*ppHead==NULL ||*ppTarget==NULL ||*ppNew==NULL , kStatus_BadAccess );
    
    // Head Node shouldn't have a previous node. So...Not a headnode.
    __exitReturn( (*ppHead)->pPrev!=NULL                        , kStatus_Denied    );
    
    // Target Node must exist in Tree.
    E_Status_t state = __LINK_BiTree_findNode (ppHead,ppTarget);
    __exitReturn( state!=kStatus_Success                        , state             );
    
    // New Node shouldn't be in Tree.
    state = __LINK_BiTree_findNode (ppHead,ppNew);
    __exitReturn(state==kStatus_Success                         , kStatus_Exist     );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pPrev , *ppTarget          );
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pRight, (*ppTarget)->pLeft );
    
    if( (*ppTarget)->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)->pLeft, pPrev , *ppNew             );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)       , pLeft , *ppNew             );
    
    return kStatus_Success;
}
    
E_Status_t __LINK_BiTree_addNode_l2l           (__LinkBiTreeNode ** ppHead , __LinkBiTreeNode ** ppTarget , __LinkBiTreeNode ** ppNew){
    __exitReturn( ppHead==NULL || ppTarget==NULL || ppNew==NULL , kStatus_BadAccess );
    __exitReturn(*ppHead==NULL ||*ppTarget==NULL ||*ppNew==NULL , kStatus_BadAccess );
    
    // Head Node shouldn't have a previous node. So...Not a headnode.
    __exitReturn( (*ppHead)->pPrev!=NULL                        , kStatus_Denied    );
    
    // Target Node must exist in Tree.
    E_Status_t state = __LINK_BiTree_findNode (ppHead,ppTarget);
    __exitReturn( state!=kStatus_Success                        , state             );
    
    // New Node shouldn't be in Tree.
    state = __LINK_BiTree_findNode (ppHead,ppNew);
    __exitReturn(state==kStatus_Success                         , kStatus_Exist     );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pPrev , *ppTarget          );
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pLeft , (*ppTarget)->pLeft );
    
    if( (*ppTarget)->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)->pLeft, pPrev , *ppNew             );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)       , pLeft , *ppNew             );
    
    return kStatus_Success;
}
    
E_Status_t __LINK_BiTree_addNode_r2l           (__LinkBiTreeNode ** ppHead , __LinkBiTreeNode ** ppTarget , __LinkBiTreeNode ** ppNew){
    __exitReturn( ppHead==NULL || ppTarget==NULL || ppNew==NULL , kStatus_BadAccess );
    __exitReturn(*ppHead==NULL ||*ppTarget==NULL ||*ppNew==NULL , kStatus_BadAccess );
    
    // Head Node shouldn't have a previous node. So...Not a headnode.
    __exitReturn( (*ppHead)->pPrev!=NULL                        , kStatus_Denied    );
    
    // Target Node must exist in Tree.
    E_Status_t state = __LINK_BiTree_findNode (ppHead,ppTarget);
    __exitReturn( state!=kStatus_Success                        , state             );
    
    // New Node shouldn't be in Tree.
    state = __LINK_BiTree_findNode (ppHead,ppNew);
    __exitReturn(state==kStatus_Success                         , kStatus_Exist     );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pPrev , *ppTarget          );
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pLeft , (*ppTarget)->pLeft );
    
    if( (*ppTarget)->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)->pRight, pPrev , *ppNew             );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)       , pRight, *ppNew             );
    
    return kStatus_Success;
}
    
E_Status_t __LINK_BiTree_addNode_r2r           (__LinkBiTreeNode ** ppHead , __LinkBiTreeNode ** ppTarget , __LinkBiTreeNode ** ppNew){
    __exitReturn( ppHead==NULL || ppTarget==NULL || ppNew==NULL , kStatus_BadAccess );
    __exitReturn(*ppHead==NULL ||*ppTarget==NULL ||*ppNew==NULL , kStatus_BadAccess );
    
    // Head Node shouldn't have a previous node. So...Not a headnode.
    __exitReturn( (*ppHead)->pPrev!=NULL                        , kStatus_Denied    );
    
    // Target Node must exist in Tree.
    E_Status_t state = __LINK_BiTree_findNode (ppHead,ppTarget);
    __exitReturn( state!=kStatus_Success                        , state             );
    
    // New Node shouldn't be in Tree.
    state = __LINK_BiTree_findNode (ppHead,ppNew);
    __exitReturn(state==kStatus_Success                         , kStatus_Exist     );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pPrev , *ppTarget          );
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppNew)          , pRight, (*ppTarget)->pRight);
    
    if( (*ppTarget)->pLeft!=NULL )
        __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)->pRight, pPrev , *ppNew             );
    
    __SET_STRUCT_MB( __LinkBiTreeNode, __LinkBiTreeNode*, (*ppTarget)       , pRight, *ppNew             );
    
    return kStatus_Success;
}
    
E_Status_t __LINK_BiTree_findNode              (__LinkBiTreeNode ** ppHead , __LinkBiTreeNode ** ppTarget ){
    __exitReturn( ppHead   == NULL                , kStatus_BadAccess );
    __exitReturn( ppTarget == NULL                , kStatus_BadAccess );
    __exitReturn(*ppHead==NULL || *ppTarget==NULL , kStatus_NotFound  );
    
    E_Status_t state = kStatus_NotFound;
    
    if(*ppHead == *ppTarget){
        return kStatus_Success;
    }else{
        __LinkBiTreeNode **p = (__LinkBiTreeNode **)(&((*ppHead)->pLeft));
        state =  CALL_FUNC( LINK_BiTree , findNode )( p , ppTarget );
    }
    
    if(state != kStatus_Success){
        __LinkBiTreeNode **p = (__LinkBiTreeNode **)(&((*ppHead)->pRight));
        state =  CALL_FUNC( LINK_BiTree , findNode )( p , ppTarget );
    }
    
    return state;
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
    
E_Status_t __Hash_removeAll   ( __HashMap_t** ptr  ){
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

