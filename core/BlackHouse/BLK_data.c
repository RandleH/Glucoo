
#include "BLK_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/*=====================================================================
 > Data Structure Reference
======================================================================*/
    
BLK_SRCT( LinkDB )*    BLK_FUNC( LinkDB, createHead )         ( void* object ){
    BLK_SRCT( LinkDB ) *ptr = (BLK_SRCT( LinkDB )*)RH_DATA_MALLOC(sizeof(BLK_SRCT( LinkDB )));
#ifdef RH_DEBUG
    RH_ASSERT( ptr );
#endif
    __SET_STRUCT_MB(BLK_SRCT( LinkDB ),BLK_SRCT( LinkDB )*,ptr,pNext  ,NULL);
    __SET_STRUCT_MB(BLK_SRCT( LinkDB ),BLK_SRCT( LinkDB )*,ptr,pPrev  ,NULL);
    ptr->object = object;
    
    return ptr;
}
    
BLK_SRCT( LinkDB )*    BLK_FUNC( LinkDB, addTail    )         ( const BLK_SRCT( LinkDB ) *pHead , void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    
    BLK_SRCT( LinkDB )* pNewNode  = (BLK_SRCT( LinkDB )*)RH_DATA_MALLOC( sizeof(BLK_SRCT( LinkDB )) );
#ifdef RH_DEBUG
    RH_ASSERT( pNewNode );
#endif
    pNewNode->object = object;
    
    const BLK_SRCT( LinkDB )* pIter = pHead;
    while( pIter->pNext != NULL ){
        pIter = pIter->pNext;
    }
    
    // Things to do for the new Node.
    __SET_STRUCT_MB(BLK_SRCT( LinkDB ),BLK_SRCT( LinkDB )*,pNewNode    ,pPrev,pIter    );
    __SET_STRUCT_MB(BLK_SRCT( LinkDB ),BLK_SRCT( LinkDB )*,pNewNode    ,pNext,NULL     );
    
    // Things to do for the neighbour.
    __SET_STRUCT_MB(BLK_SRCT( LinkDB ),BLK_SRCT( LinkDB )*,pIter       ,pNext,pNewNode );
    
    return pNewNode;
}
    
BLK_SRCT( LinkDB )*    BLK_FUNC( LinkDB, insert     )         ( const BLK_SRCT( LinkDB ) *pHead , void* Tobject, void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    
    BLK_SRCT( LinkDB )* pNewNode  = (BLK_SRCT( LinkDB )*)RH_DATA_MALLOC( sizeof(BLK_SRCT( LinkDB )) );

    const BLK_SRCT( LinkDB )* pTmp  = pHead;
    do{
        if (pTmp->object ==  Tobject ) {
            goto FOUND_TOBJ;
        }
        pTmp = pTmp->pNext;
    }while( pTmp );
#ifdef RH_DEBUG
    RH_ASSERT( false );
#endif
FOUND_TOBJ:

    // Things to do for the new Node.
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pNewNode    ,pPrev,pTmp        );
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pNewNode    ,pNext,pTmp->pNext );
    pNewNode->object = object;
    
    // Things to do for the neighbour.
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pTmp        ,pNext,pNewNode    );
    if( pTmp->pNext )
        __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pTmp->pNext ,pPrev,pNewNode    );
    
    return pNewNode;
}
    
void                    BLK_FUNC( LinkDB, removeAll  )         (       BLK_SRCT( LinkDB ) *pHead ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    const BLK_SRCT( LinkDB )* pTmp1  = pHead;
    const BLK_SRCT( LinkDB )* pTmp2  = pHead;
    do{
        pTmp2 = pTmp1->pNext;
        RH_DATA_FREE( (void*)(pTmp1) );
        pTmp1 = pTmp2;
    }while( pTmp1 );
}
    
      
BLK_SRCT(LinkLoop)*  BLK_FUNC( LinkLoop, createHead       ) ( void* object ){
    BLK_SRCT(LinkLoop) *ptr = (BLK_SRCT(LinkLoop)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(LinkLoop)));
#ifdef RH_DEBUG
    RH_ASSERT( ptr );
#endif
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,ptr,pNext  ,ptr);
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,ptr,pPrev  ,ptr);
    ptr->object = object;

    return ptr;
}
      
BLK_SRCT(LinkLoop) * BLK_FUNC( LinkLoop, add              ) ( const BLK_SRCT(LinkLoop) *pHead , void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif

    BLK_SRCT(LinkLoop)* pNewNode  = (BLK_SRCT(LinkLoop)*)RH_DATA_MALLOC( sizeof(BLK_SRCT(LinkLoop)) );
#ifdef RH_DEBUG
    RH_ASSERT( pNewNode );
#endif

    pNewNode->object = object;

    // Things to do for the new Node.
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pNewNode    ,pPrev,pHead->pPrev   );
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pNewNode    ,pNext,pHead          );

    // Things to do for the neighbour.
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pHead->pPrev,pNext,pNewNode           );
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pHead       ,pPrev,pNewNode           );
    
    return pNewNode;
}
    
BLK_SRCT(LinkLoop)*  BLK_FUNC( LinkLoop, insert           ) ( const BLK_SRCT(LinkLoop) *pHead , void* Tobject, void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    
    BLK_SRCT(LinkLoop)* pNewNode  = (BLK_SRCT(LinkLoop)*)RH_DATA_MALLOC( sizeof(BLK_SRCT(LinkLoop)) );

    const BLK_SRCT(LinkLoop)* pTmp  = pHead;
    do{
        if (pTmp->object ==  Tobject ) {
            goto FOUND_TOBJ;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHead );
#ifdef RH_DEBUG
    RH_ASSERT( false );
#endif
FOUND_TOBJ:

    // Things to do for the new Node.
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pNewNode    ,pPrev,pTmp        );
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pNewNode    ,pNext,pTmp->pNext );
    pNewNode->object = object;
    
    // Things to do for the neighbour.
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pTmp        ,pNext,pNewNode    );
    __SET_STRUCT_MB(BLK_SRCT(LinkLoop),BLK_SRCT(LinkLoop)*,pTmp->pNext ,pPrev,pNewNode    );
    
    return pNewNode;
}
    
BLK_SRCT(LinkLoop)*  BLK_FUNC( LinkLoop, find             ) ( const BLK_SRCT(LinkLoop) *pHead , void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    
    const BLK_SRCT(LinkLoop)* pTmp  = pHead;
    
    do{
        if (pTmp->object ==  object ) {
            return (BLK_SRCT(LinkLoop)*)pTmp;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHead );
    
    return NULL;
}
    
void           BLK_FUNC( LinkLoop, remove           ) (       BLK_SRCT(LinkLoop) *pHead , void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif

    const BLK_SRCT(LinkLoop)* pTmp      = pHead;
    
    do{
        if (pTmp->object ==  object ) {
            if( pTmp == pHead ){
                if( pTmp->pNext==pTmp->pPrev && pTmp->pPrev==pHead ){
                    pHead = NULL;
                    RH_DATA_FREE((void*)pTmp);
                }else{
                    pHead = (BLK_SRCT(LinkLoop)*)( pHead->pNext );
                    __SET_STRUCT_MB(BLK_SRCT(LinkLoop), BLK_SRCT(LinkLoop)*, pTmp->pPrev, pNext, pTmp->pNext);
                    __SET_STRUCT_MB(BLK_SRCT(LinkLoop), BLK_SRCT(LinkLoop)*, pTmp->pNext, pPrev, pTmp->pPrev);
                    RH_DATA_FREE((void*)pTmp);
                }
            }else{
                // Connect the neighbour and isolate the <pTarget>.
                __SET_STRUCT_MB(BLK_SRCT(LinkLoop), BLK_SRCT(LinkLoop)*, pTmp->pPrev, pNext, pTmp->pNext);
                __SET_STRUCT_MB(BLK_SRCT(LinkLoop), BLK_SRCT(LinkLoop)*, pTmp->pNext, pPrev, pTmp->pPrev);
                // Same Effect: pTarget->pPrev->pNext = pTarget->pNext; // But to cope with <const>.
                // Same Effect: pTarget->pNext->pPrev = pTarget->pPrev; // But to cope with <const>.
                
                __SET_STRUCT_MB(BLK_SRCT(LinkLoop), BLK_SRCT(LinkLoop)*, pTmp, pNext, NULL);
                __SET_STRUCT_MB(BLK_SRCT(LinkLoop), BLK_SRCT(LinkLoop)*, pTmp, pPrev, NULL);
                // Same Effect: pTarget->pNext = NULL; // But to cope with <const>.
                // Same Effect: pTarget->pPrev = NULL; // But to cope with <const>.
                RH_DATA_FREE((void*)pTmp);
            }

            return;
        }
        pTmp = pTmp->pNext;
    }while( pTmp != pHead );
    
}
    
void           BLK_FUNC( LinkLoop, removeAll        ) (       BLK_SRCT(LinkLoop) *pHead ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    const BLK_SRCT(LinkLoop)* pTmp  = pHead;
    do{
        pTmp = pTmp->pNext;
        RH_DATA_FREE( (void*)(pTmp->pPrev) );
    }while( pTmp != pHead );
    
}

void           BLK_FUNC( LinkLoop, printAllNodesAdr ) ( const BLK_SRCT(LinkLoop) *pHead , int(*PRINTF_FUNC)(const char*,...)){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    const BLK_SRCT(LinkLoop)* pTmp      = pHead;
    size_t cnt = 0;
    do{
        (*PRINTF_FUNC)("NODE[%d]: %p\n",cnt,pTmp);
        cnt++;
        pTmp = pTmp->pNext;
    }while( pTmp != pHead );

}
    

BLK_SRCT(LinkBiTree)* BLK_FUNC( LinkBiTree, createHead    ) ( void* object ){
    BLK_SRCT(LinkBiTree)* pNewHead = (BLK_SRCT(LinkBiTree)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(LinkBiTree)));
#ifdef RH_DEBUG
    RH_ASSERT( pNewHead );
#endif
    __SET_STRUCT_MB(BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*,pNewHead,pLeft  ,NULL);
    __SET_STRUCT_MB(BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*,pNewHead,pRight ,NULL);
    __SET_STRUCT_MB(BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*,pNewHead,pPrev  ,NULL);
    pNewHead->object = object;

    return pNewHead;
}
    
BLK_SRCT(LinkBiTree)* BLK_FUNC( LinkBiTree, add_l2r       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object ){

#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    RH_ASSERT( pTarget );
#endif
    BLK_SRCT(LinkBiTree)* pNewNode = (BLK_SRCT(LinkBiTree)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(LinkBiTree)));
#ifdef RH_DEBUG
    RH_ASSERT( pNewNode );
#endif
    pNewNode->object = object;

    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode , pPrev , pTarget        );
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode , pRight, pTarget->pLeft );
    
    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget->pLeft, pPrev , pNewNode );
    
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget  , pLeft , pNewNode );
    
    return pNewNode;
}
    
BLK_SRCT(LinkBiTree)* BLK_FUNC( LinkBiTree, add_l2l       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    RH_ASSERT( pTarget );
#endif
    BLK_SRCT(LinkBiTree)* pNewNode = (BLK_SRCT(LinkBiTree)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(LinkBiTree)));
#ifdef RH_DEBUG
    RH_ASSERT( pNewNode );
#endif
    pNewNode->object = object;
    
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode , pPrev , pTarget        );
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode , pLeft , pTarget->pLeft );
    
    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget->pLeft, pPrev , pNewNode );
    
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget, pLeft, pNewNode );
    
    return pNewNode;
}
    
BLK_SRCT(LinkBiTree)* BLK_FUNC( LinkBiTree, add_r2l       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    RH_ASSERT( pTarget );
#endif
    BLK_SRCT(LinkBiTree)* pNewNode = (BLK_SRCT(LinkBiTree)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(LinkBiTree)));
#ifdef RH_DEBUG
    RH_ASSERT( pNewNode );
#endif
    pNewNode->object = object;
    
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode , pPrev , pTarget        );
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode , pLeft , pTarget->pLeft );
    
    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget->pRight, pPrev , pNewNode );
    
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget, pRight, pNewNode );
    
    return pNewNode;
}
    
BLK_SRCT(LinkBiTree)* BLK_FUNC( LinkBiTree, add_r2r       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( !(pHead->pPrev) );  // Head Node shouldn't have a previous node. So...Not a headnode.
    RH_ASSERT( pTarget );
#endif
    BLK_SRCT(LinkBiTree)* pNewNode = (BLK_SRCT(LinkBiTree)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(LinkBiTree)));
#ifdef RH_DEBUG
    RH_ASSERT( pNewNode );
#endif
    pNewNode->object = object;
    
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode, pPrev , pTarget         );
    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pNewNode, pRight, pTarget->pRight );

    if( pTarget->pLeft!=NULL )
        __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget->pRight, pPrev , pNewNode );

    __SET_STRUCT_MB( BLK_SRCT(LinkBiTree), BLK_SRCT(LinkBiTree)*, pTarget, pRight, pNewNode );

    return pNewNode;
}
    
BLK_SRCT(LinkBiTree)* BLK_FUNC( LinkBiTree, find          ) ( const BLK_SRCT(LinkBiTree) *pHead , void* object ){
    
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
#endif
    
    BLK_SRCT(LinkBiTree)* pTarget = NULL;
    
    if( pHead->object == object ){
        return (BLK_SRCT(LinkBiTree)*)pHead;
    }else{
        pTarget = BLK_FUNC( LinkBiTree, find )( pHead->pLeft , object );
    }
    
    if( !pTarget ){
        pTarget = BLK_FUNC( LinkBiTree, find )( pHead->pLeft , object );
    }
    
    return pTarget;
}
    
    
BLK_SRCT(Stack)*      BLK_FUNC( Stack, createBase         ) ( void* object ){
    BLK_SRCT(Stack) *ptr = (BLK_SRCT(Stack)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(Stack)));
#ifdef RH_DEBUG
    RH_ASSERT( ptr );
#endif
    __SET_STRUCT_MB( BLK_SRCT(Stack), BLK_SRCT(Stack)*, ptr, pPrev , ptr   );
    __SET_STRUCT_MB( BLK_SRCT(Stack), BLK_SRCT(Stack)*, ptr, pNext , ptr   );
    __SET_STRUCT_MB( BLK_SRCT(Stack), void*     , ptr, object, object);

    return ptr;
}
    
BLK_SRCT(Stack)*      BLK_FUNC( Stack, push               ) ( const BLK_SRCT(Stack) *pBase , void* object ){

#ifdef RH_DEBUG
    RH_ASSERT( pBase );
#endif
    
    BLK_SRCT(Stack)* pNew = (BLK_SRCT(Stack)*)RH_DATA_MALLOC(sizeof(BLK_SRCT(Stack)));
#ifdef RH_DEBUG
    RH_ASSERT( pNew );
#endif
    
    __SET_STRUCT_MB(BLK_SRCT(Stack), void*     , pNew            , object, object       );
    __SET_STRUCT_MB(BLK_SRCT(Stack), BLK_SRCT(Stack)*, pNew            , pPrev , pBase->pPrev );
    __SET_STRUCT_MB(BLK_SRCT(Stack), BLK_SRCT(Stack)*, pNew            , pNext , pBase        );
    
    __SET_STRUCT_MB(BLK_SRCT(Stack), BLK_SRCT(Stack)*, pBase->pPrev    , pNext , pNew         );
    __SET_STRUCT_MB(BLK_SRCT(Stack), BLK_SRCT(Stack)*, pBase           , pPrev , pNew         );
    
    return pNew;
}
    
void*                 BLK_FUNC( Stack, pop                ) ( const BLK_SRCT(Stack) *pBase ){

#ifdef RH_DEBUG
    RH_ASSERT( pBase );
#endif
    
    __exitReturn(pBase->pNext==pBase->pPrev && pBase->pNext==pBase , (void*)pBase->object );
    
    void* dummy_ptr = (BLK_SRCT(Stack)*)(pBase->pPrev);
    
    void* object = (void*)(pBase->pPrev->object);
    
    __SET_STRUCT_MB(BLK_SRCT(Stack), BLK_SRCT(Stack)*, pBase->pPrev->pPrev , pNext, pBase               );
    __SET_STRUCT_MB(BLK_SRCT(Stack), BLK_SRCT(Stack)*, pBase               , pPrev, pBase->pPrev->pPrev );
    
    RH_DATA_FREE(dummy_ptr);
    
    return object;
}
    
size_t                BLK_FUNC( Stack, size               ) ( const BLK_SRCT(Stack) *pBase ){

#ifdef RH_DEBUG
    RH_ASSERT( pBase );
#endif
    size_t cnt = 0;
    const BLK_SRCT(Stack) *p = pBase;
    while(p->pNext != pBase){
        cnt++;
        p = p->pNext;
    }
    
    return cnt;
}
    
void*                 BLK_FUNC( Stack, top                ) ( const BLK_SRCT(Stack) *pBase ){

#ifdef RH_DEBUG
    RH_ASSERT( pBase );
#endif
    return (void*)(pBase->pPrev->object);
}
    
bool                  BLK_FUNC( Stack, empty              ) ( const BLK_SRCT(Stack) *pBase ){

#ifdef RH_DEBUG
    RH_ASSERT( pBase );
#endif
    return (pBase->pNext==pBase->pPrev && pBase->pNext==pBase);
}
    
void*                 BLK_FUNC( Stack, deleteBase         ) (       BLK_SRCT(Stack) *pBase ){

#ifdef RH_DEBUG
    RH_ASSERT( pBase );
#endif
    BLK_SRCT(Stack) *p = pBase;
    void* object = (void*)pBase->object;
    if(p->pNext==pBase){
        RH_DATA_FREE((void*)(p));
    }else{
        while(p->pNext!=pBase){
            p = (BLK_SRCT(Stack)*)(p->pNext);
            RH_DATA_FREE((void*)(p->pPrev));
            __SET_STRUCT_MB( BLK_SRCT(Stack), BLK_SRCT(Stack)*, p, pPrev , NULL );
        }
    }

    return object;
}
    
    
E_Status_t      __Queue_createHead           ( void* object ){
    
    return MAKE_ENUM( kStatus_Success );
}
    
    
#define RH_HASH_MAP_SIZE                     RH_CFG_HASHTABLE_SIZE
    
    
    
static size_t RH_FUNCONST __HashFunc         ( size_t key ){
    return (key&(RH_HASH_MAP_SIZE-1));
}
    
__HashMap_t*    __Hash_createMap             ( void ){

    __HashMap_t *pHashHead = RH_DATA_HASH_MALLOC( sizeof(__HashMap_t) );
#ifdef RH_DEBUG
    RH_ASSERT( pHashHead );
#endif
    
    __HashList_t* pHashList = RH_DATA_HASH_MALLOC(RH_HASH_MAP_SIZE*sizeof(__HashList_t));
#ifdef RH_DEBUG
    RH_ASSERT( pHashList );
#endif
    memset(pHashList, 0, RH_HASH_MAP_SIZE*sizeof(__HashList_t));
    
    __SET_STRUCT_MB(__HashMap_t, __HashList_t*, pHashHead, pList, pHashList);
    
    return pHashHead;
}
    
void*           __Hash_find                  ( const __HashMap_t *pHead, size_t key ){
#ifdef RH_DEBUG
    RH_ASSERT(pHead);
#endif
    
    const __HashList_t *pList = pHead->pList[ __HashFunc(key)].pNext ;
    
    while( pList != NULL ){
        if( pList->key == key )
            return (void*)(pList->object);
        pList = pList->pNext;
    }
    
    return NULL;
}
    
void            __Hash_pair                  ( const __HashMap_t *pHead, size_t key, void* object ){

#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( pHead->pList );
#endif
    
    
    const __HashList_t *pList     =  (pHead->pList[ __HashFunc(key) ].pNext);
    const __HashList_t *pList_old = &(pHead->pList[ __HashFunc(key) ]);
    while( pList != NULL ){
        if( pList->key == key ){
            __SET_STRUCT_MB(__HashList_t, void*, pList, object, object);
            return ;
        }
        pList_old = pList;
        pList     = (__HashList_t*)pList->pNext;
    }
    pList = pList_old;

    // This key is not exsist in current HashList.
    // Allocate a new node for this pair.
    __SET_STRUCT_MB(__HashList_t, __HashList_t* , pList       , pNext , RH_DATA_HASH_MALLOC(sizeof(__HashList_t)));
    __SET_STRUCT_MB(__HashList_t, size_t        , pList->pNext, key   , key);
    __SET_STRUCT_MB(__HashList_t, void*         , pList->pNext, object, object);
    __SET_STRUCT_MB(__HashList_t, void*         , pList->pNext, pNext , NULL);
    
}
    
void*           __Hash_get                   ( const __HashMap_t *pHead, size_t key ){

#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( pHead->pList );
#endif
    
    const __HashList_t *pList = pHead->pList[ (long)__HashFunc(key) ].pNext;
    
    while( pList != NULL ){
        if( pList->key == key ){
            return (void*)pList->object;
        }
        pList     = (__HashList_t*)pList->pNext;
    }
    
    return NULL;
}
    
void*           __Hash_remove                ( const __HashMap_t *pHead, size_t key ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( pHead->pList );
#endif
    const __HashList_t *pList     =  (pHead->pList[ (long)__HashFunc(key) ].pNext);
    const __HashList_t *pList_old = &(pHead->pList[ (long)__HashFunc(key) ]);
    while( pList != NULL ){
        if( pList->key == key ){
            void* object = (void*)pList->object;
            __SET_STRUCT_MB(__HashList_t, __HashList_t*, pList_old, pNext, pList->pNext);
            RH_DATA_HASH_FREE((void*)pList);
            return object;
        }
        pList_old = pList;
        pList     = pList->pNext;
    }
    
    return NULL;
}
    
void            __Hash_removeAll             (       __HashMap_t *pHead ){
#ifdef RH_DEBUG
    RH_ASSERT( pHead );
    RH_ASSERT( pHead->pList );
#endif
    
    size_t cnt = RH_HASH_MAP_SIZE;
    while(cnt--){
        const __HashList_t *pList_tmp = (pHead->pList[ cnt ].pNext);
        const __HashList_t *pList     = (pHead->pList[ cnt ].pNext);
        while( pList != NULL ){
            pList_tmp = pList->pNext;
            RH_DATA_HASH_FREE((void*)pList);
            pList = pList_tmp;
        }
    }
    RH_DATA_HASH_FREE( (void*)pHead->pList );

}
    
#ifdef __cplusplus
}
#endif

