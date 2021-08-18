#ifndef _BLK_POKER_H
#define _BLK_POKER_H

#include "RH_config.h"
#include "RH_common.h"


#define M_BLK_POKER_OPT_ALL              (    0U )
#define M_BLK_POKER_OPT_NO_JOKER         ( 1<<0U )
#define M_BLK_POKER_OPT_NO_A             ( 1<<1U )
#define M_BLK_POKER_OPT_NO_KING          ( 1<<2U )
#define M_BLK_POKER_OPT_NO_SPADE         ( 1<<3U )
#define M_BLK_POKER_OPT_NO_HEART         ( 1<<4U )
#define M_BLK_POKER_OPT_NO_CLUB          ( 1<<5U )
#define M_BLK_POKER_OPT_NO_DIAMOND       ( 1<<6U )
#define M_BLK_POKER_OPT_BAD              ( 1<<7U )

enum BLK_ENUM(PokerVal){
    BLK_ENUM_MEMBER( kBLK_POKER_JRED  ),
    BLK_ENUM_MEMBER( kBLK_POKER_JBLK  ),
    BLK_ENUM_MEMBER( kBLK_POKER_A     ),
    BLK_ENUM_MEMBER( kBLK_POKER_2     ),
    BLK_ENUM_MEMBER( kBLK_POKER_3     ),
    BLK_ENUM_MEMBER( kBLK_POKER_4     ),
    BLK_ENUM_MEMBER( kBLK_POKER_5     ),
    BLK_ENUM_MEMBER( kBLK_POKER_6     ),
    BLK_ENUM_MEMBER( kBLK_POKER_7     ),
    BLK_ENUM_MEMBER( kBLK_POKER_8     ),
    BLK_ENUM_MEMBER( kBLK_POKER_9     ),
    BLK_ENUM_MEMBER( kBLK_POKER_10    ),
    BLK_ENUM_MEMBER( kBLK_POKER_J     ),
    BLK_ENUM_MEMBER( kBLK_POKER_Q     ),
    BLK_ENUM_MEMBER( kBLK_POKER_K     ),
};
typedef enum BLK_ENUM(PokerVal) BLK_ENUM(PokerVal);

enum BLK_ENUM(PokerSuit){
    BLK_ENUM_MEMBER( kBLK_POKER_SPADE   ),
    BLK_ENUM_MEMBER( kBLK_POKER_HEART   ),
    BLK_ENUM_MEMBER( kBLK_POKER_CLUB    ),
    BLK_ENUM_MEMBER( kBLK_POKER_DIAMOND ),
    BLK_ENUM_MEMBER( kBLK_POKER_JOKER   ),
    
};
typedef enum BLK_ENUM(PokerSuit) BLK_ENUM(PokerSuit);


struct BLK_SRCT(PokerCard){
    BLK_ENUM(PokerVal)   num;
    BLK_ENUM(PokerSuit)  suit;
};
typedef struct BLK_SRCT(PokerCard) BLK_SRCT(PokerCard);

struct BLK_SRCT(PokerDeck){
    uint8_t              opt;      // Use macro: M_BLK_POKER_OPT_xxxx
    BLK_SRCT(PokerCard)* cards;
    int8_t               size;
};
typedef struct BLK_SRCT(PokerDeck) BLK_SRCT(PokerDeck);

BLK_SRCT(PokerDeck)* RH_RESULT BLK_FUNC( Poker, create ) ( void      );
void                           BLK_FUNC( Poker, option ) ( uint8_t   );

BLK_SRCT(PokerDeck)*           BLK_FUNC( Poker, wash   ) (       BLK_SRCT(PokerDeck)* deck );//
void                           BLK_FUNC( Poker, delete ) (       BLK_SRCT(PokerDeck)* deck );
void                           BLK_FUNC( Poker, print  ) ( const BLK_SRCT(PokerDeck)* deck , int (*print)(const char*,...) );


#endif



