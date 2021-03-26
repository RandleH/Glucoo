

#include "RH_neuron.h"



void  __Neuron_set_bias ( __Perceptron_t* ptrons, int32_t bias ){
    __SET_STRUCT_MB(__Perceptron_t, int32_t, ptrons, bias, bias);
}

void  __Neuron_reset    ( __Perceptron_t* pcept ){
    
    
}

void  __Neuron_cal_out  ( __Perceptron_t* ptrons ){
#ifdef RH_DEBUG
    ASSERT( ptrons && ptrons->_in && ptrons->_out && ptrons->_w );
#endif
    ptrons->_out[0] = 0;
    if( ptrons->state != kNeuronSta_suspend ){
        for(int i=0; i<ptrons->_nIns; i++){
            ptrons->_out[0] += ptrons->_w[i]*ptrons->_in[i];
        }
        __memsetDWORD(ptrons->_out, ptrons->_out[0], ptrons->_nOuts);
        
        if( ptrons->_out[0] > 0 )
            ptrons->state = kNeuronSta_fired;
        else
            ptrons->state = kNeuronSta_quiecent;
    }else{
        __memsetDWORD(ptrons->_out, 0, ptrons->_nOuts);
    }
    
}






__FF_Layer_t* __FF_Layer_create_input ( size_t numPtrons ){
    
    __FF_Layer_t* pLayer_In = (__FF_Layer_t*)__LINK_DB_createHead(NULL); // __malloc( sizeof(__FF_Layer_t) );
    
#ifdef RH_DEBUG
    ASSERT(pLayer_In);
    ASSERT(sizeof(__FF_Layer_t)==sizeof(__LinkDB_t));
#endif
    
    pLayer_In->object = __malloc( sizeof(*(pLayer_In->object)) );
    
    __SET_STRUCT_MB(struct __FF_LayerInfo_t, size_t, pLayer_In->object, _nPtrons_thisLayer, numPtrons);
    __SET_STRUCT_MB(struct __FF_LayerInfo_t, size_t, pLayer_In->object, _nPtrons_prevLayer, 0        );
    // Same Effect: pLayer_In->object->_nPtrons_thisLayer = numPtrons;
    // Same Effect: pLayer_In->object->_nPtrons_prevLayer = 0;
    
    pLayer_In->object->_ptron             = __malloc( numPtrons*sizeof(__Perceptron_t) );
    pLayer_In->object->_in_data           = __malloc( numPtrons*1*sizeof(int32_t)      );
    
    return pLayer_In;
}

__FF_Layer_t* __FF_Layer_add_hidden ( __FF_Layer_t* prevLayer, size_t numPtrons ){
    
    __FF_Layer_t* pLayer_hidden = (__FF_Layer_t*)__LINK_DB_addTail((__LinkDB_t *)prevLayer, NULL);
    
#ifdef RH_DEBUG
    ASSERT( prevLayer                                );
    ASSERT( pLayer_hidden                            );
    ASSERT( sizeof(__FF_Layer_t)==sizeof(__LinkDB_t) );
#endif
    
    pLayer_hidden->object = __malloc( sizeof(*(pLayer_hidden->object)) );
    __SET_STRUCT_MB(struct __FF_LayerInfo_t, size_t, pLayer_hidden->object, _nPtrons_thisLayer, numPtrons                              );
    __SET_STRUCT_MB(struct __FF_LayerInfo_t, size_t, pLayer_hidden->object, _nPtrons_prevLayer, prevLayer->object->_nPtrons_thisLayer  );
    // Same Effect: pLayer_hidden->object->_nPtrons_thisLayer = numPtrons;
    // Same Effect: pLayer_hidden->object->_nPtrons_prevLayer = 0;
    
    pLayer_hidden->object->_ptron   = __malloc( numPtrons*sizeof(__Perceptron_t) );
    pLayer_hidden->object->_in_data = __malloc( numPtrons*prevLayer->object->_nPtrons_thisLayer*sizeof(int32_t) );
    
    return pLayer_hidden;
}




