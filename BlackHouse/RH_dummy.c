double __cordic_tan(double a){
     const static uint16_t angle_256[] = {
        // When 1 deg = 256, then...
        
        11520 , // Φ = 45               tan(Φ) = 1/1
        6801  , // Φ = 26.565051177078  tan(Φ) = 1/2
        3593  , // Φ = 14.036243467927  tan(Φ) = 1/4
        1824  , // Φ = 26.565051177078  tan(Φ) = 1/8
        916   , // Φ = 26.565051177078  tan(Φ) = 1/16
        458   , // Φ = 26.565051177078  tan(Φ) = 1/32
        229   , // Φ = 26.565051177078  tan(Φ) = 1/64
        115   , // Φ = 26.565051177078  tan(Φ) = 1/128
        57    , // Φ = 26.565051177078  tan(Φ) = 1/256
        29    , // Φ = 26.565051177078  tan(Φ) = 1/512
        14    , // Φ = 26.565051177078  tan(Φ) = 1/1024
        7     , // Φ = 26.565051177078  tan(Φ) = 1/2048
        4     , // Φ = 26.565051177078  tan(Φ) = 1/4096
        2     , // Φ = 26.565051177078  tan(Φ) = 1/8192
        1       // Φ = 26.565051177078  tan(Φ) = 1/16384
    };

    long x = 0xffff;
    long y = 0;
    
    long angle_tar = lround(a*14667.719555349074144);
    long angle_sum = 0;
    long x_tmp = 0,y_tmp = 0;
    
    
//    uint8_t sgn = 0;
//    while(angle_tar > 23040){
//        angle_tar-=23040;
//        if( sgn >= 4 )
//            sgn = 0;
//        sgn++;
//    }
//
//    while(angle_tar < -23040){
//        angle_tar+=23040;
//        if( sgn >= 4 )
//            sgn = 0;
//        sgn++;
//    }
//
//    __exitReturn( angle_tar >  22810 , tan(a) ); // Accuracy cannot meet by this algorithm.
//    __exitReturn( angle_tar < -22810 , tan(a) );
//    printf("tar = %ld\n",angle_tar);
    
    for( int i=0; i<15; i++ ){
        if( angle_tar < angle_sum ){ // cw
            x_tmp = (x + (y>>i));
            y_tmp = (y - (x>>i));
            x  = x_tmp;
            y  = y_tmp;
            angle_sum -= angle_256[i];
        }else{ // ccw
            x_tmp = (x - (y>>i));
            y_tmp = (y + (x>>i));
            x  = x_tmp;
            y  = y_tmp;
            angle_sum += angle_256[i];
        }
    }
//    printf("%d\n",sgn);
    
//    switch(sgn){
//        case 0:
//        case 2:
//        case 4: return y/((double)(x));
//        case 1: return x/((double)(y));
//
//        case 3: return x/((double)(-y));
//
//        default:while(1); // error
//    }
    
    return y/((double)(x));
}
