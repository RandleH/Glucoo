#ifndef _BLK_POKER_H
#define _BLK_POKER_H

#include "RH_common.h"


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
    MAKE_ENUM( kBLK_POKER_JOKER ),
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
};
typedef enum E_PokerSuit_t E_PokerSuit_t;


struct S_PokerCard_t{
    E_PokerNum_t   num;
    E_PokerSuit_t  suit;
};
typedef struct S_PokerCard_t S_PokerCard_t;

struct S_PokerDeck_t{
    S_PokerCard_t* cards;
    size_t         size;
};
typedef struct S_PokerDeck_t S_PokerDeck_t;

S_PokerDeck_t* RH_RESULT MAKE_FUNC( Poker, init   ) ( void           );//
void                     MAKE_FUNC( Poker, option ) ( E_PokerOpt_t   );//
S_PokerDeck_t*           MAKE_FUNC( Poker, wash   ) ( S_PokerDeck_t* );//




#endif



