
#ifndef _RH_DATA_H
#define _RH_DATA_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RH_DATA_CALLOC(x,s)           calloc(x,s)
#define RH_DATA_MALLOC(x)             malloc(x)
#define RH_DATA_FREE(x)               free(x)


#define RH_DATA_HASH_CALLOC(x,s)      calloc(x,s)
#define RH_DATA_HASH_MALLOC(x)        malloc(x)
#define RH_DATA_HASH_FREE(x)          free(x)

/*=====================================================================
> Data Structure Reference
======================================================================*/
struct __LinkDB_t{
    void*        object;
    const struct __LinkDB_t* const pNext; // Can NOT be modified by user.
    const struct __LinkDB_t* const pPrev; // Can NOT be modified by user.
};
typedef struct __LinkDB_t __LinkDB_t;

__LinkDB_t* RH_RESULT MAKE_FUNC( LINK_DB , createHead       ) ( void* object );
__LinkDB_t*           MAKE_FUNC( LINK_DB , addTail          ) ( const __LinkDB_t *pHead , void* object );
__LinkDB_t*           MAKE_FUNC( LINK_DB , insert           ) ( const __LinkDB_t *pHead , void* Tobject, void* object );
void                  MAKE_FUNC( LINK_DB , removeAll        ) (       __LinkDB_t *pHead );

struct __LinkLoop_t{
    void*        object;
    const struct __LinkLoop_t* const pNext; // Can NOT be modified by user.
    const struct __LinkLoop_t* const pPrev; // Can NOT be modified by user.
};
typedef struct __LinkLoop_t __LinkLoop_t;

__LinkLoop_t* RH_RESULT MAKE_FUNC( LINK_Loop , createHead        ) ( void* object );
__LinkLoop_t*           MAKE_FUNC( LINK_Loop , add               ) ( const __LinkLoop_t *pHead , void* object );
__LinkLoop_t* RH_RESULT MAKE_FUNC( LINK_Loop , find              ) ( const __LinkLoop_t *pHead , void* object );
void                    MAKE_FUNC( LINK_Loop , remove            ) (       __LinkLoop_t *pHead , void* object );
__LinkLoop_t*           MAKE_FUNC( LINK_Loop , insert            ) ( const __LinkLoop_t *pHead , void* Tobject, void* object );
void                    MAKE_FUNC( LINK_Loop , removeAll         ) (       __LinkLoop_t *pHead );
void                    MAKE_FUNC( LINK_Loop , printAllNodesAdr  ) ( const __LinkLoop_t *pHead , int(*PRINTF_FUNC)(const char*,...));

struct __LinkBiTree_t{
    void*        object;
    const struct __LinkBiTree_t* const pLeft;  // Can NOT be modified by user.
    const struct __LinkBiTree_t* const pRight; // Can NOT be modified by user.
    const struct __LinkBiTree_t* const pPrev;  // Can NOT be modified by user.
};
typedef struct __LinkBiTree_t __LinkBiTree_t;

__LinkBiTree_t* RH_RESULT MAKE_FUNC( LINK_BiTree , createHead    ) ( void* object );
__LinkBiTree_t*           MAKE_FUNC( LINK_BiTree , add_l2r       ) ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object );
__LinkBiTree_t*           MAKE_FUNC( LINK_BiTree , add_l2l       ) ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object );
__LinkBiTree_t*           MAKE_FUNC( LINK_BiTree , add_r2l       ) ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object );
__LinkBiTree_t*           MAKE_FUNC( LINK_BiTree , add_r2r       ) ( const __LinkBiTree_t *pHead , __LinkBiTree_t *pTarget , void* object );
__LinkBiTree_t* RH_RESULT MAKE_FUNC( LINK_BiTree , find          ) ( const __LinkBiTree_t *pHead , void* object );

struct __Stack_t{
    const void*             const object; // Can NOT be modified by user.
    const struct __Stack_t* const pNext;  // Can NOT be modified by user.
    const struct __Stack_t* const pPrev;  // Can NOT be modified by user.
};
typedef struct __Stack_t __Stack_t;

__Stack_t* RH_RESULT MAKE_FUNC( Stack , createBase ) ( void* object );
__Stack_t*           MAKE_FUNC( Stack , push       ) ( const __Stack_t *pBase , void *object );
void*      RH_RESULT MAKE_FUNC( Stack , pop        ) ( const __Stack_t *pBase );
size_t     RH_RESULT MAKE_FUNC( Stack , size       ) ( const __Stack_t *pBase );
void*      RH_RESULT MAKE_FUNC( Stack , top        ) ( const __Stack_t *pBase );
bool       RH_RESULT MAKE_FUNC( Stack , empty      ) ( const __Stack_t *pBase );
void*                MAKE_FUNC( Stack , deleteBase ) (       __Stack_t *pBase );



struct __Queue_t{
    const void*             const object;
    const struct __Queue_t* const pNext ;
};
typedef struct __Queue_t __Queue_t;

E_Status_t MAKE_FUNC( Queue , createHead ) ( void* object );



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

__HashMap_t* RH_RESULT MAKE_FUNC( Hash , createMap ) ( void );
void*                  MAKE_FUNC( Hash , find      ) ( const __HashMap_t *pHead, size_t key );
void                   MAKE_FUNC( Hash , pair      ) ( const __HashMap_t *pHead, size_t key , void* object );
void*                  MAKE_FUNC( Hash , get       ) ( const __HashMap_t *pHead, size_t key );
void*                  MAKE_FUNC( Hash , remove    ) ( const __HashMap_t *pHead, size_t key );
void                   MAKE_FUNC( Hash , removeAll ) (       __HashMap_t *pHead );
 
#ifdef __cplusplus
}
#endif

#endif

