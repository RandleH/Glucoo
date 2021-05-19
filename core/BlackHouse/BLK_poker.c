
#include "BLK_poker.h"


static struct S_PokerDeck_t cache;

static void __poker_print_cache( void ){

}

static void __poker_create( void ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( !cache.cards );
#endif
    
    cache.cards = BLK_POKER_MALLOC( 54*sizeof( *cache.cards ) );
    cache.size  = 54;
    
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cache.cards );
#endif
    
    {
        register int8_t cnt = 0;
        
        for( int8_t i=MAKE_ENUM( kBLK_POKER_A ); i<=MAKE_ENUM( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = MAKE_ENUM( kBLK_POKER_SPADE   );
            cnt++;
        }
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 13 );
#endif

        for( int8_t i=MAKE_ENUM( kBLK_POKER_A ); i<=MAKE_ENUM( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = MAKE_ENUM( kBLK_POKER_HEART   );
            cnt++;
        }
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 26 );
#endif

        for( int8_t i=MAKE_ENUM( kBLK_POKER_A ); i<=MAKE_ENUM( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = MAKE_ENUM( kBLK_POKER_CLUB    );
            cnt++;
        }
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 39 );
#endif

        for( int8_t i=MAKE_ENUM( kBLK_POKER_A ); i<=MAKE_ENUM( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = MAKE_ENUM( kBLK_POKER_DIAMOND );
            cnt++;
        }
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 52 );
#endif
        
        cache.cards[ cnt   ].num  = MAKE_ENUM( kBLK_POKER_JRED   );
        cache.cards[ cnt++ ].suit = MAKE_ENUM( kBLK_POKER_JOKER  );
        
        cache.cards[ cnt   ].num  = MAKE_ENUM( kBLK_POKER_JBLK   );
        cache.cards[ cnt++ ].suit = MAKE_ENUM( kBLK_POKER_JOKER  );
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 54 );
#endif
        
    }
    
    __poker_print_cache();
    
}

static void __poker_remove( int8_t idx ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( idx < cache.size );
#endif
    if( idx < cache.size-1 ){
        memmove( &cache.cards[idx], &cache.cards[idx+1], (cache.size-1-idx)*sizeof(cache.cards[0]));
    }
    cache.size--;
    
    __poker_print_cache();
}

static void __poker_remove_se( int8_t idx_s, int8_t idx_e ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( idx_e < cache.size && idx_s <= idx_e && idx_s >= 0 );
#endif
    if( idx_e < cache.size-1 ){
        memmove( &cache.cards[idx_s], &cache.cards[idx_e+1], (cache.size-1-idx_e)*sizeof(cache.cards[0]));
    }
    cache.size -= idx_e-idx_s+1;
    
}

static void __poker_delete( void ){
    BLK_POKER_FREE( cache.cards );
    cache.size  = 0;
    cache.cards = NULL;
}



S_PokerDeck_t* RH_RESULT MAKE_FUNC( Poker, create ) ( void           ){
    __poker_create();
    
    int8_t             cnt = 54;
    S_PokerDeck_t*     ptr = NULL;
    
    if( cache.opt != MAKE_ENUM( kBLK_POKER_ALL ) ){
        if( cache.opt & MAKE_ENUM( kBLK_POKER_NO_JOKER ) ){
            cnt-=2;
            __poker_remove_se(52,53);
        }
        
        if( cache.opt & MAKE_ENUM( kBLK_POKER_NO_A ) ){
            //...//
        }
        
        if( cache.opt & MAKE_ENUM( kBLK_POKER_NO_KING ) ){
            //...//
        }
        
        if( cache.opt & MAKE_ENUM( kBLK_POKER_NO_SPADE ) ){
            //...//
        }
        
        if( cache.opt & MAKE_ENUM( kBLK_POKER_NO_HEART ) ){
            //...//
        }
        
        if( cache.opt & MAKE_ENUM( kBLK_POKER_NO_CLUB  ) ){
            //...//
        }
        
        if( cache.opt & MAKE_ENUM( kBLK_POKER_NO_DIAMOND ) ){
            //...//
        }
        //...//
    }
    
    ptr = BLK_POKER_MALLOC( sizeof(*ptr) );
    ptr->size  = cnt;
    ptr->opt   = cache.opt;
    ptr->cards = BLK_POKER_MALLOC( cnt*sizeof( ptr->cards[0] ) );
    
    for( int8_t i=0; i<cnt; i++ ){
        int8_t idx = rand()%cache.size;
        ptr->cards[i] = cache.cards[ idx ];
        __poker_remove( idx );
    }
    
    
    
    //...//
    __poker_delete();
    return ptr;
}

void                     MAKE_FUNC( Poker, option ) ( E_PokerOpt_t opt ){
    cache.opt = opt;
}

S_PokerDeck_t*           MAKE_FUNC( Poker, wash   ) ( S_PokerDeck_t* );//

void                     MAKE_FUNC( Poker, print  ) ( const S_PokerDeck_t* deck, int (*print)(const char*,...) ){
    for( int8_t i=0; i<deck->size; i++ ){
        switch( deck->cards[i].suit ){
            case MAKE_ENUM( kBLK_POKER_SPADE ):
                (*print)("♠ %d\n", deck->cards[i].num-1);
                break; // '♥','♠','♦','♣'
            case MAKE_ENUM( kBLK_POKER_HEART ):
                (*print)("♥ %d\n", deck->cards[i].num-1);
                break;
            case MAKE_ENUM( kBLK_POKER_DIAMOND ):
                (*print)("♦ %d\n", deck->cards[i].num-1);
                break;
            case MAKE_ENUM( kBLK_POKER_CLUB ):
                (*print)("♣ %d\n", deck->cards[i].num-1);
                break;
            case MAKE_ENUM( kBLK_POKER_JOKER ):
                (*print)("J \n");
                break;
            default:
                assert(0);
        }
    }
}

void                     MAKE_FUNC( Poker, delete ) ( S_PokerDeck_t* deck ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( deck );
    BLK_POKER_ASSERT( deck->cards );
#endif
    BLK_POKER_FREE( deck->cards );
    deck->cards = NULL;
    BLK_POKER_FREE( deck );
}

