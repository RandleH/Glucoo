
#ifndef _BLK_DATA_H
#define _BLK_DATA_H

#include "RH_common.h"
#include "RH_config.h"
#ifdef __cplusplus
extern "C" {
#endif


/*=====================================================================
> Data Structure Reference
======================================================================*/
struct BLK_SRCT( LinkDB ){
    void*        object;
    const struct BLK_SRCT( LinkDB )* const pNext; // Can NOT be modified by user.
    const struct BLK_SRCT( LinkDB )* const pPrev; // Can NOT be modified by user.
};
typedef struct BLK_SRCT( LinkDB ) BLK_SRCT( LinkDB );

BLK_SRCT( LinkDB )* RH_RESULT   BLK_FUNC( LinkDB   , createHead        ) ( void* object );
BLK_SRCT( LinkDB )*             BLK_FUNC( LinkDB   , addTail           ) ( const BLK_SRCT( LinkDB ) *pHead , void* object );
BLK_SRCT( LinkDB )*             BLK_FUNC( LinkDB   , insert            ) ( const BLK_SRCT( LinkDB ) *pHead , void* Tobject, void* object );
void                            BLK_FUNC( LinkDB   , removeAll         ) (       BLK_SRCT( LinkDB ) *pHead );

struct BLK_SRCT(LinkLoop){
    void*        object;
    const struct BLK_SRCT(LinkLoop)* const pNext; // Can NOT be modified by user.
    const struct BLK_SRCT(LinkLoop)* const pPrev; // Can NOT be modified by user.
};
typedef struct BLK_SRCT(LinkLoop) BLK_SRCT(LinkLoop);

BLK_SRCT(LinkLoop)* RH_RESULT BLK_FUNC( LinkLoop , createHead        ) ( void* object );
BLK_SRCT(LinkLoop)*           BLK_FUNC( LinkLoop , add               ) ( const BLK_SRCT(LinkLoop) *pHead , void* object );
BLK_SRCT(LinkLoop)* RH_RESULT BLK_FUNC( LinkLoop , find              ) ( const BLK_SRCT(LinkLoop) *pHead , void* object );
void                          BLK_FUNC( LinkLoop , remove            ) (       BLK_SRCT(LinkLoop) *pHead , void* object );
BLK_SRCT(LinkLoop)*           BLK_FUNC( LinkLoop , insert            ) ( const BLK_SRCT(LinkLoop) *pHead , void* Tobject, void* object );
void                          BLK_FUNC( LinkLoop , removeAll         ) (       BLK_SRCT(LinkLoop) *pHead );
void                          BLK_FUNC( LinkLoop , printAllNodesAdr  ) ( const BLK_SRCT(LinkLoop) *pHead , int(*PRINTF_FUNC)(const char*,...));

struct BLK_SRCT(LinkBiTree){
    void*        object;
    const struct BLK_SRCT(LinkBiTree)* const pLeft;  // Can NOT be modified by user.
    const struct BLK_SRCT(LinkBiTree)* const pRight; // Can NOT be modified by user.
    const struct BLK_SRCT(LinkBiTree)* const pPrev;  // Can NOT be modified by user.
};
typedef struct BLK_SRCT(LinkBiTree) BLK_SRCT(LinkBiTree);

BLK_SRCT(LinkBiTree)* RH_RESULT BLK_FUNC( LinkBiTree , createHead    ) ( void* object );
BLK_SRCT(LinkBiTree)*           BLK_FUNC( LinkBiTree , add_l2r       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object );
BLK_SRCT(LinkBiTree)*           BLK_FUNC( LinkBiTree , add_l2l       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object );
BLK_SRCT(LinkBiTree)*           BLK_FUNC( LinkBiTree , add_r2l       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object );
BLK_SRCT(LinkBiTree)*           BLK_FUNC( LinkBiTree , add_r2r       ) ( const BLK_SRCT(LinkBiTree) *pHead , BLK_SRCT(LinkBiTree) *pTarget , void* object );
BLK_SRCT(LinkBiTree)* RH_RESULT BLK_FUNC( LinkBiTree , find          ) ( const BLK_SRCT(LinkBiTree) *pHead , void* object );

struct BLK_SRCT(Stack){
    const void*             const object;       // Can NOT be modified by user.
    const struct BLK_SRCT(Stack)* const pNext;  // Can NOT be modified by user.
    const struct BLK_SRCT(Stack)* const pPrev;  // Can NOT be modified by user.
};
typedef struct BLK_SRCT(Stack) BLK_SRCT(Stack);

BLK_SRCT(Stack)* RH_RESULT BLK_FUNC( Stack , createBase ) ( void* object );
BLK_SRCT(Stack)*           BLK_FUNC( Stack , push       ) ( const BLK_SRCT(Stack) *pBase , void *object );
void*            RH_RESULT BLK_FUNC( Stack , pop        ) ( const BLK_SRCT(Stack) *pBase );
size_t           RH_RESULT BLK_FUNC( Stack , size       ) ( const BLK_SRCT(Stack) *pBase );
void*            RH_RESULT BLK_FUNC( Stack , top        ) ( const BLK_SRCT(Stack) *pBase );
bool             RH_RESULT BLK_FUNC( Stack , empty      ) ( const BLK_SRCT(Stack) *pBase );
void*                      BLK_FUNC( Stack , deleteBase ) (       BLK_SRCT(Stack) *pBase );


struct BLK_SRCT(HashList){
    const size_t                     key;
    const void*                const object;
    const struct BLK_SRCT(HashList)* const pNext ;
};
typedef struct BLK_SRCT(HashList) BLK_SRCT(HashList);

struct BLK_SRCT(HashMap){
    const BLK_SRCT(HashList)*     const pList;
};
typedef struct BLK_SRCT(HashMap) BLK_SRCT(HashMap);

BLK_SRCT(HashMap)* RH_RESULT BLK_FUNC( Hash , createMap ) ( void );
void*                        BLK_FUNC( Hash , find      ) ( const BLK_SRCT(HashMap) *pHead, size_t key );
void                         BLK_FUNC( Hash , pair      ) ( const BLK_SRCT(HashMap) *pHead, size_t key , void* object );
void*                        BLK_FUNC( Hash , get       ) ( const BLK_SRCT(HashMap) *pHead, size_t key );
void*                        BLK_FUNC( Hash , remove    ) ( const BLK_SRCT(HashMap) *pHead, size_t key );
void                         BLK_FUNC( Hash , removeAll ) (       BLK_SRCT(HashMap) *pHead );
 
#ifdef __cplusplus
}
#endif

#endif

