#ifndef _BLK_POKER_H
#define _BLK_POKER_H

#include "RH_common.h"



#define BLK_POKER_MALLOC(x)         malloc(x)
#define BLK_POKER_CALLOC(x)         calloc(x)
#define BLK_POKER_FREE(x)           free(x)
#define BLK_POKER_ASSERT(expr)      assert(expr)


enum E_PokerOpt_t{
    MAKE_ENUM( kBLK_POKER_ALL        ) = (    0U ),
    MAKE_ENUM( kBLK_POKER_NO_JOKER   ) = ( 1<<0U ),
    MAKE_ENUM( kBLK_POKER_NO_A       ) = ( 1<<1U ),
    MAKE_ENUM( kBLK_POKER_NO_KING    ) = ( 1<<2U ),
    MAKE_ENUM( kBLK_POKER_NO_SPADE   ) = ( 1<<3U ),
    MAKE_ENUM( kBLK_POKER_NO_HEART   ) = ( 1<<3U ),
    MAKE_ENUM( kBLK_POKER_NO_CLUB    ) = ( 1<<3U ),
    MAKE_ENUM( kBLK_POKER_NO_DIAMOND ) = ( 1<<3U ),
};
typedef enum E_PokerOpt_t E_PokerOpt_t;

enum E_PokerNum_t{
    MAKE_ENUM( kBLK_POKER_JRED  ),
    MAKE_ENUM( kBLK_POKER_JBLK  ),
    MAKE_ENUM( kBLK_POKER_A     ),
    MAKE_ENUM( kBLK_POKER_2     ),
    MAKE_ENUM( kBLK_POKER_3     ),
    MAKE_ENUM( kBLK_POKER_4     ),
    MAKE_ENUM( kBLK_POKER_5     ),
    MAKE_ENUM( kBLK_POKER_6     ),
    MAKE_ENUM( kBLK_POKER_7     ),
    MAKE_ENUM( kBLK_POKER_8     ),
    MAKE_ENUM( kBLK_POKER_9     ),
    MAKE_ENUM( kBLK_POKER_10    ),
    MAKE_ENUM( kBLK_POKER_J     ),
    MAKE_ENUM( kBLK_POKER_Q     ),
    MAKE_ENUM( kBLK_POKER_K     ),
};
typedef enum E_PokerNum_t E_PokerNum_t;

enum E_PokerSuit_t{
    MAKE_ENUM( kBLK_POKER_SPADE   ),
    MAKE_ENUM( kBLK_POKER_HEART   ),
    MAKE_ENUM( kBLK_POKER_CLUB    ),
    MAKE_ENUM( kBLK_POKER_DIAMOND ),
    MAKE_ENUM( kBLK_POKER_JOKER   ),
    
};
typedef enum E_PokerSuit_t E_PokerSuit_t;


struct S_PokerCard_t{
    E_PokerNum_t   num;
    E_PokerSuit_t  suit;
};
typedef struct S_PokerCard_t S_PokerCard_t;

struct S_PokerDeck_t{
    E_PokerOpt_t   opt;
    S_PokerCard_t* cards;
    int8_t         size;
};
typedef struct S_PokerDeck_t S_PokerDeck_t;

S_PokerDeck_t* RH_RESULT MAKE_FUNC( Poker, create ) ( void           );
void                     MAKE_FUNC( Poker, option ) ( E_PokerOpt_t   );


S_PokerDeck_t*           MAKE_FUNC( Poker, wash   ) (       S_PokerDeck_t* deck );//
void                     MAKE_FUNC( Poker, delete ) (       S_PokerDeck_t* deck );
void                     MAKE_FUNC( Poker, print  ) ( const S_PokerDeck_t* deck , int (*print)(const char*,...) );


#endif



