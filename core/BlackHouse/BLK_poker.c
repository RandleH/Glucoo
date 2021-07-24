
#include "BLK_poker.h"


static struct BLK_SRCT(PokerDeck) cache;

inline void __poker_print_cache( void ){
    BLK_FUNC( Poker, print )( &cache , printf );
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
        
        for( int8_t i=BLK_ENUM_MEMBER( kBLK_POKER_A ); i<=BLK_ENUM_MEMBER( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = BLK_ENUM_MEMBER( kBLK_POKER_SPADE   );
            cnt++;
        }
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 13 );
#endif

        for( int8_t i=BLK_ENUM_MEMBER( kBLK_POKER_A ); i<=BLK_ENUM_MEMBER( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = BLK_ENUM_MEMBER( kBLK_POKER_HEART   );
            cnt++;
        }
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 26 );
#endif

        for( int8_t i=BLK_ENUM_MEMBER( kBLK_POKER_A ); i<=BLK_ENUM_MEMBER( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = BLK_ENUM_MEMBER( kBLK_POKER_CLUB    );
            cnt++;
        }
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 39 );
#endif

        for( int8_t i=BLK_ENUM_MEMBER( kBLK_POKER_A ); i<=BLK_ENUM_MEMBER( kBLK_POKER_K ); i++ ){
            cache.cards[cnt].num  = i;
            cache.cards[cnt].suit = BLK_ENUM_MEMBER( kBLK_POKER_DIAMOND );
            cnt++;
        }
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 52 );
#endif
        
        cache.cards[ cnt   ].num  = BLK_ENUM_MEMBER( kBLK_POKER_JRED   );
        cache.cards[ cnt++ ].suit = BLK_ENUM_MEMBER( kBLK_POKER_JOKER  );
        
        cache.cards[ cnt   ].num  = BLK_ENUM_MEMBER( kBLK_POKER_JBLK   );
        cache.cards[ cnt++ ].suit = BLK_ENUM_MEMBER( kBLK_POKER_JOKER  );
        
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cnt == 54 );
#endif
        
    }
    
//    __poker_print_cache();
    
}

static void __poker_remove( int8_t idx ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( idx < cache.size );
#endif
    if( idx < cache.size-1 ){
        memmove( &cache.cards[idx], &cache.cards[idx+1], (cache.size-1-idx)*sizeof(cache.cards[0]));
    }
    cache.size--;
    
}


static int __compar( const void* p1, const void* p2 ){
    typedef int8_t var;
    if( *(var*)p2 > *(var*)p1 ){
        return 1;
    }else if( *(var*)p2 < *(var*)p1 ){
        return -1;
    }
    return 0;
}

static void __poker_remove_sp( int8_t* idx_list, size_t size ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( size <= 54 );
#endif
    qsort( idx_list, size, sizeof(*idx_list), __compar );
    
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( idx_list[0] < 54 );
#endif
    
    for( int8_t i=0; i<size; i++ ){
        __poker_remove( idx_list[i] );
    }
    
//    __poker_print_cache();
}

#if 0
static void __poker_remove_se( int8_t idx_s, int8_t idx_e ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( idx_e < cache.size && idx_s <= idx_e && idx_s >= 0 );
#endif
    if( idx_e < cache.size-1 ){
        memmove( &cache.cards[idx_s], &cache.cards[idx_e+1], (cache.size-1-idx_e)*sizeof(cache.cards[0]));
    }
    cache.size -= idx_e-idx_s+1;
}
#endif

static void __poker_delete( void ){
    BLK_POKER_FREE( cache.cards );
    cache.size  = 0;
    cache.cards = NULL;
}



BLK_SRCT(PokerDeck)* RH_RESULT BLK_FUNC( Poker, create ) ( void             ){
    __poker_create();
    
    int8_t             cnt    = 54;   // Number of cards that is valid.
    BLK_SRCT(PokerDeck)*     ptr    = NULL; // Result
    int8_t             rm     = 0;    // Number of cards need to be removed.
    int8_t*            rm_idx = alloca( cnt );
    
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( cache.opt < M_BLK_POKER_OPT_BAD );
#endif
    
    if( cache.opt != M_BLK_POKER_OPT_ALL ){
        if( cache.opt & M_BLK_POKER_OPT_NO_JOKER ){
            cnt    -= 2;
            rm     += 2;
            
            rm_idx[ rm-2 ] = 52;
            rm_idx[ rm-1 ] = 53;
        }
        
        if( cache.opt & M_BLK_POKER_OPT_NO_A ){
            cnt    -= 4;
            rm     += 4;
            
            rm_idx[ rm-4 ] = 0;
            rm_idx[ rm-3 ] = 13;
            rm_idx[ rm-2 ] = 26;
            rm_idx[ rm-1 ] = 39;
            //...//
        }
        
        if( cache.opt & M_BLK_POKER_OPT_NO_KING ){
            cnt    -= 3*4;
            rm     += 3*4;
            
            rm_idx[ rm-12] = 10;
            rm_idx[ rm-11] = 11;
            rm_idx[ rm-10] = 12;
            
            rm_idx[ rm-9 ] = 23;
            rm_idx[ rm-8 ] = 24;
            rm_idx[ rm-7 ] = 25;
            
            rm_idx[ rm-6 ] = 36;
            rm_idx[ rm-5 ] = 37;
            rm_idx[ rm-4 ] = 38;
            
            rm_idx[ rm-3 ] = 49;
            rm_idx[ rm-2 ] = 50;
            rm_idx[ rm-1 ] = 51;
            
            //...//
        }
        
        if( cache.opt & M_BLK_POKER_OPT_NO_SPADE ){
            switch( cache.opt & (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A) ){
                case 0:{
                    cnt -= 13;
                    rm  += 13;
                    for( int8_t i=0; i<13; i++ ){
                        rm_idx[ rm-i-1 ] = i;
                    }
                    break;
                }
                case M_BLK_POKER_OPT_NO_KING:
                    cnt -= 10;
                    rm  += 10;
                    for( int8_t i=0; i<10; i++ ){
                        rm_idx[ rm-i-1 ] = i;
                    }
                    break;
                case M_BLK_POKER_OPT_NO_A:
                    cnt -= 12;
                    rm  += 12;
                    for( int8_t i=1; i<13; i++ ){
                        rm_idx[ rm-i ] = i;
                    }
                    break;
                case (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A):
                    cnt -= 9;
                    rm  += 9;
                    for( int8_t i=1; i<10; i++ ){
                        rm_idx[ rm-i ] = i;
                    }
                    break;
                default:
                    BLK_POKER_ASSERT(0);
            }
            //...//
        }
        
        if( cache.opt & M_BLK_POKER_OPT_NO_HEART ){
            switch( cache.opt & (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A) ){
                case 0:{
                    cnt -= 13;
                    rm  += 13;
                    for( int8_t i=0; i<13; i++ ){
                        rm_idx[ rm-i-1 ] = 13+i;
                    }
                    break;
                }
                case M_BLK_POKER_OPT_NO_KING:
                    cnt -= 10;
                    rm  += 10;
                    for( int8_t i=0; i<10; i++ ){
                        rm_idx[ rm-i-1 ] = 13+i;
                    }
                    break;
                case M_BLK_POKER_OPT_NO_A:
                    cnt -= 12;
                    rm  += 12;
                    for( int8_t i=1; i<13; i++ ){
                        rm_idx[ rm-i ] = 13+i;
                    }
                    break;
                case (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A):
                    cnt -= 9;
                    rm  += 9;
                    for( int8_t i=1; i<10; i++ ){
                        rm_idx[ rm-i ] = 13+i;
                    }
                    break;
                default:
                    BLK_POKER_ASSERT(0);
            }
            //...//
        }
        
        if( cache.opt & M_BLK_POKER_OPT_NO_CLUB  ){
            switch( cache.opt & (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A) ){
                case 0:{
                    cnt -= 13;
                    rm  += 13;
                    for( int8_t i=0; i<13; i++ ){
                        rm_idx[ rm-i-1 ] = 26+i;
                    }
                    break;
                }
                case M_BLK_POKER_OPT_NO_KING:
                    cnt -= 10;
                    rm  += 10;
                    for( int8_t i=0; i<10; i++ ){
                        rm_idx[ rm-i-1 ] = 26+i;
                    }
                    break;
                case M_BLK_POKER_OPT_NO_A:
                    cnt -= 12;
                    rm  += 12;
                    for( int8_t i=1; i<13; i++ ){
                        rm_idx[ rm-i ] = 26+i;
                    }
                    break;
                case (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A):
                    cnt -= 9;
                    rm  += 9;
                    for( int8_t i=1; i<10; i++ ){
                        rm_idx[ rm-i ] = 26+i;
                    }
                    break;
                default:
                    BLK_POKER_ASSERT(0);
            }
            //...//
        }
        
        if( cache.opt & M_BLK_POKER_OPT_NO_DIAMOND ){
            switch( cache.opt & (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A) ){
                case 0:{
                    cnt -= 13;
                    rm  += 13;
                    for( int8_t i=0; i<13; i++ ){
                        rm_idx[ rm-i-1 ] = 39+i;
                    }
                    break;
                }
                case M_BLK_POKER_OPT_NO_KING:
                    cnt -= 10;
                    rm  += 10;
                    for( int8_t i=0; i<10; i++ ){
                        rm_idx[ rm-i-1 ] = 39+i;
                    }
                    break;
                case M_BLK_POKER_OPT_NO_A:
                    cnt -= 12;
                    rm  += 12;
                    for( int8_t i=1; i<13; i++ ){
                        rm_idx[ rm-i ] = 39+i;
                    }
                    break;
                case (M_BLK_POKER_OPT_NO_KING | M_BLK_POKER_OPT_NO_A):
                    cnt -= 9;
                    rm  += 9;
                    for( int8_t i=1; i<10; i++ ){
                        rm_idx[ rm-i ] = 39+i;
                    }
                    break;
                default:
                    BLK_POKER_ASSERT(0);
            }
            //...//
        }
        
        __poker_remove_sp( rm_idx, rm );
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

void                     BLK_FUNC( Poker, option ) ( uint8_t opt ){
    cache.opt = opt;
}



BLK_SRCT(PokerDeck)*           BLK_FUNC( Poker, wash   ) (       BLK_SRCT(PokerDeck)* deck){
    
    return 0;
}

void                     BLK_FUNC( Poker, print  ) ( const BLK_SRCT(PokerDeck)* deck, int (*print)(const char*,...) ){
    for( int8_t i=0; i<deck->size; i++ ){
        switch( deck->cards[i].suit ){
            case BLK_ENUM_MEMBER( kBLK_POKER_SPADE ):
                (*print)("♠ %d\n", deck->cards[i].num-1);
                break; // '♥','♠','♦','♣'
            case BLK_ENUM_MEMBER( kBLK_POKER_HEART ):
                (*print)("♥ %d\n", deck->cards[i].num-1);
                break;
            case BLK_ENUM_MEMBER( kBLK_POKER_DIAMOND ):
                (*print)("♦ %d\n", deck->cards[i].num-1);
                break;
            case BLK_ENUM_MEMBER( kBLK_POKER_CLUB ):
                (*print)("♣ %d\n", deck->cards[i].num-1);
                break;
            case BLK_ENUM_MEMBER( kBLK_POKER_JOKER ):
                (*print)("J \n");
                break;
            default:
                assert(0);
        }
    }
}

void                     BLK_FUNC( Poker, delete ) (       BLK_SRCT(PokerDeck)* deck ){
#ifdef RH_DEBUG
    BLK_POKER_ASSERT( deck );
    BLK_POKER_ASSERT( deck->cards );
#endif
    BLK_POKER_FREE( deck->cards );
    deck->cards = NULL;
    BLK_POKER_FREE( deck );
}

