

#include "RH_neuron.h"



void  __Neuron_set_bias ( __Perceptron_t* ptrons, var bias ){
    ptrons->_b = bias;
}

void  __Neuron_reset    ( __Perceptron_t* ptrons ){
    
    
}

//void  __Neuron_cal_out  ( __Perceptron_t* ptrons ){
//#ifdef RH_DEBUG
//    RH_ASSERT( ptrons && ptrons->_in && ptrons->_out && ptrons->_w );
//#endif
//    ptrons->_out[0] = 0;
//    if( ptrons->_sta != kNeuronSta_suspend ){
//        for(int i=0; i<ptrons->_nIns; i++){
//            ptrons->_out[0] += ptrons->_w[i]*ptrons->_in[i];
//        }
//        __memsetDWORD(ptrons->_out, ptrons->_out[0], ptrons->_nOuts);
//
//        if( ptrons->_out[0] > 0 )
//            ptrons->_sta = kNeuronSta_fired;
//        else
//            ptrons->_sta = kNeuronSta_quiecent;
//    }else{
//        __memsetDWORD(ptrons->_out, 0, ptrons->_nOuts);
//    }
//
//}




__FF_Layer_t* __FF_Net_create          ( size_t* arrPtron, size_t numLayer ){
    __FF_Layer_t* pL_in   = NULL;
    __FF_Layer_t* pL_prev = NULL;
    __FF_Layer_t* pL_out  = NULL;
    for( int i=0; i<numLayer; i++){
        if( i==0 ){
            pL_in   = __FF_Layer_create_input( arrPtron[i] );
            pL_prev = pL_in;
            continue;
        }
        if( i==numLayer-1){
            pL_out = NULL;
            continue;
        }
        pL_prev = __FF_Layer_add_hidden( pL_prev, arrPtron[i] );
        //...//
    }
    return pL_in;
}

__FF_Layer_t* __FF_Layer_create_input ( size_t numPtrons ){
    
    __FF_Layer_t* pLayer_In = (__FF_Layer_t*)__LINK_DB_createHead(NULL); 
    
#ifdef RH_DEBUG
    RH_ASSERT(pLayer_In);
    RH_ASSERT(sizeof(__FF_Layer_t)==sizeof(__LinkDB_t));
#endif
    
    pLayer_In->object = RH_MALLOC( sizeof(*(pLayer_In->object)) );
    
    pLayer_In->object->_nPtrons_thisLayer = numPtrons;
    pLayer_In->object->_nPtrons_prevLayer = 0;
    pLayer_In->object->_ptron             = RH_MALLOC( numPtrons*sizeof( __Perceptron_t ) );
    pLayer_In->object->_in_data           = RH_MALLOC( numPtrons*sizeof( var            ) );
    pLayer_In->object->_out_data          = RH_MALLOC( numPtrons*sizeof( var            ) );
    return pLayer_In;
}

__FF_Layer_t* __FF_Layer_add_hidden ( __FF_Layer_t* prevLayer, size_t numPtrons ){
    
    __FF_Layer_t* thisLayer = (__FF_Layer_t*)__LINK_DB_addTail((__LinkDB_t *)prevLayer, NULL);
    
#ifdef RH_DEBUG
    RH_ASSERT( prevLayer                                );
    RH_ASSERT( thisLayer                            );
    RH_ASSERT( sizeof(__FF_Layer_t)==sizeof(__LinkDB_t) );
#endif
    
    thisLayer->object = RH_MALLOC( sizeof(*(thisLayer->object)) );
    
    thisLayer->object->_nPtrons_thisLayer = numPtrons;
    thisLayer->object->_nPtrons_prevLayer = prevLayer->object->_nPtrons_thisLayer;
    thisLayer->object->_ptron    = RH_MALLOC( thisLayer->object->_nPtrons_thisLayer * sizeof( __Perceptron_t ) );
    thisLayer->object->_in_data  = prevLayer->object->_out_data;
    thisLayer->object->_out_data = RH_MALLOC( thisLayer->object->_nPtrons_thisLayer * sizeof( var            ) );
    return thisLayer;
}




