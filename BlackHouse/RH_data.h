
#ifndef _RH_DATA_H
#define _RH_DATA_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif


/*=====================================================================
> Data Structure Reference
======================================================================*/
struct __LinkLoop_t{
    void*        object;
    const struct __LinkLoop_t* const pNext; // Can NOT be modified by user.
    const struct __LinkLoop_t* const pPrev; // Can NOT be modified by user.
};
typedef struct __LinkLoop_t __LinkLoop_t;

__LinkLoop_t* RH_RESULT MAKE_FUNC( LINK_Loop , createHead        ) ( void* object );
__LinkLoop_t*           MAKE_FUNC( LINK_Loop , add               ) ( __LinkLoop_t  *pHead , void* object );
__LinkLoop_t* RH_RESULT MAKE_FUNC( LINK_Loop , find              ) ( __LinkLoop_t  *pHead , void* object );
void                    MAKE_FUNC( LINK_Loop , remove            ) ( __LinkLoop_t  *pHead , void* object );
void                    MAKE_FUNC( LINK_Loop , removeAll         ) ( __LinkLoop_t  *pHead );
void                    MAKE_FUNC( LINK_Loop , printAllNodesAdr  ) ( __LinkLoop_t  *pHead , int(*PRINTF_FUNC)(const char*,...));

struct __LinkBiTree_t{
    void*        object;
    const struct __LinkBiTree_t* const pLeft;  // Can NOT be modified by user.
    const struct __LinkBiTree_t* const pRight; // Can NOT be modified by user.
    const struct __LinkBiTree_t* const pPrev;  // Can NOT be modified by user.
};
typedef struct __LinkBiTree_t __LinkBiTree_t;

__LinkBiTree_t* RH_RESULT MAKE_FUNC( LINK_BiTree , createHead    ) ( void* object );
__LinkBiTree_t*           MAKE_FUNC( LINK_BiTree , addNode_l2r   ) ( __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object);
E_Status_t                MAKE_FUNC( LINK_BiTree , addNode_l2l   ) ( __LinkBiTree_t ** ppHead , __LinkBiTree_t ** ppTarget , __LinkBiTree_t ** ppNew);//
E_Status_t                MAKE_FUNC( LINK_BiTree , addNode_r2l   ) ( __LinkBiTree_t ** ppHead , __LinkBiTree_t ** ppTarget , __LinkBiTree_t ** ppNew);//
E_Status_t                MAKE_FUNC( LINK_BiTree , addNode_r2r   ) ( __LinkBiTree_t ** ppHead , __LinkBiTree_t ** ppTarget , __LinkBiTree_t ** ppNew);//
E_Status_t                MAKE_FUNC( LINK_BiTree , findNode      ) ( __LinkBiTree_t ** ppHead , __LinkBiTree_t ** ppTarget );//

struct __Stack_t{
    const void*             const object; // Can NOT be modified by user.
    const struct __Stack_t* const pNext;  // Can NOT be modified by user.
    const struct __Stack_t* const pPrev;  // Can NOT be modified by user.
};
typedef struct __Stack_t __Stack_t;

E_Status_t MAKE_FUNC( Stack , createBase ) ( __Stack_t ** ptr    );
E_Status_t MAKE_FUNC( Stack , push       ) ( __Stack_t ** ppBase  , void      *  pObj  );
E_Status_t MAKE_FUNC( Stack , pop        ) ( __Stack_t ** ppBase  , void     **  ppObj );
E_Status_t MAKE_FUNC( Stack , size       ) ( __Stack_t ** ppBase  , size_t    *  result);
E_Status_t MAKE_FUNC( Stack , empty      ) ( __Stack_t ** ppBase );
E_Status_t MAKE_FUNC( Stack , top        ) ( __Stack_t ** ppBase  , void     **  ppObj );
E_Status_t MAKE_FUNC( Stack , deleteBase ) ( __Stack_t ** ptr    );//



struct __Queue_t{
    const void*             const object;
    const struct __Queue_t* const pNext ;
};
typedef struct __Queue_t __Queue_t;

E_Status_t MAKE_FUNC( Queue , createHead ) ( __Queue_t ** ptr    );


#define RH_HASH_MAP_SIZE              (256)
struct __HashList_t{
    const size_t                     key;
    const void*                const object;
    const struct __HashList_t* const pNext ;
};
typedef struct __HashList_t __HashList_t;

struct __HashMap_t{
    const __HashList_t*     const pList;
};
typedef struct __HashMap_t __HashMap_t;

E_Status_t MAKE_FUNC( Hash , createMap ) ( __HashMap_t** ptr  );
E_Status_t MAKE_FUNC( Hash , find      ) ( __HashMap_t** ppHead, size_t key );
E_Status_t MAKE_FUNC( Hash , put       ) ( __HashMap_t** ppHead, size_t key, void*  pObj  );
E_Status_t MAKE_FUNC( Hash , get       ) ( __HashMap_t** ppHead, size_t key, void** ppObj );
E_Status_t MAKE_FUNC( Hash , remove    ) ( __HashMap_t** ppHead, size_t key );
E_Status_t MAKE_FUNC( Hash , removeAll ) ( __HashMap_t** ptr  );//

#ifdef __cplusplus
}
#endif

#endif

