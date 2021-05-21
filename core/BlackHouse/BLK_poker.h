#ifndef _BLK_POKER_H
#define _BLK_POKER_H

#include "RH_common.h"



#define BLK_POKER_MALLOC(x)         malloc(x)
#define BLK_POKER_CALLOC(x,s)       calloc(x,s)
#define BLK_POKER_FREE(x)           free(x)
#define BLK_POKER_ASSERT(expr)      assert(expr)


typedef uint8_t E_PokerOpt_t;
#define M_BLK_POKER_OPT_ALL              (    0U )
#define M_BLK_POKER_OPT_NO_JOKER         ( 1<<0U )
#define M_BLK_POKER_OPT_NO_A             ( 1<<1U )
#define M_BLK_POKER_OPT_NO_KING          ( 1<<2U )
#define M_BLK_POKER_OPT_NO_SPADE         ( 1<<3U )
#define M_BLK_POKER_OPT_NO_HEART         ( 1<<4U )
#define M_BLK_POKER_OPT_NO_CLUB          ( 1<<5U )
#define M_BLK_POKER_OPT_NO_DIAMOND       ( 1<<6U )
#define M_BLK_POKER_OPT_BAD              ( 1<<7U )

enum E_PokerNum_t{
    BLK_ENUM( kBLK_POKER_JRED  ),
    BLK_ENUM( kBLK_POKER_JBLK  ),
    BLK_ENUM( kBLK_POKER_A     ),
    BLK_ENUM( kBLK_POKER_2     ),
    BLK_ENUM( kBLK_POKER_3     ),
    BLK_ENUM( kBLK_POKER_4     ),
    BLK_ENUM( kBLK_POKER_5     ),
    BLK_ENUM( kBLK_POKER_6     ),
    BLK_ENUM( kBLK_POKER_7     ),
    BLK_ENUM( kBLK_POKER_8     ),
    BLK_ENUM( kBLK_POKER_9     ),
    BLK_ENUM( kBLK_POKER_10    ),
    BLK_ENUM( kBLK_POKER_J     ),
    BLK_ENUM( kBLK_POKER_Q     ),
    BLK_ENUM( kBLK_POKER_K     ),
};
typedef enum E_PokerNum_t E_PokerNum_t;

enum E_PokerSuit_t{
    BLK_ENUM( kBLK_POKER_SPADE   ),
    BLK_ENUM( kBLK_POKER_HEART   ),
    BLK_ENUM( kBLK_POKER_CLUB    ),
    BLK_ENUM( kBLK_POKER_DIAMOND ),
    BLK_ENUM( kBLK_POKER_JOKER   ),
    
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

S_PokerDeck_t* RH_RESULT BLK_FUNC( Poker, create ) ( void           );
void                     BLK_FUNC( Poker, option ) ( E_PokerOpt_t   );


S_PokerDeck_t*           BLK_FUNC( Poker, wash   ) (       S_PokerDeck_t* deck );//
void                     BLK_FUNC( Poker, delete ) (       S_PokerDeck_t* deck );
void                     BLK_FUNC( Poker, print  ) ( const S_PokerDeck_t* deck , int (*print)(const char*,...) );


#endif



