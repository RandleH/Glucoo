#ifndef _RH_NEURON_H
#define _RH_NEURON_H

#include "RH_common.h"
#include "RH_lib.h"
#include "RH_data.h"

typedef enum{
    kNeuronSta_quiecent ,
    kNeuronSta_fired    ,
    kNeuronSta_suspend
}E_PtronSta_t;


/*========================================================================================
* Data Structure --- Single Perceptron
*========================================================================================*/
struct __Perceptron_t{
    int32_t*       _in;      /* Input data stream       */ 
    int32_t*       _w;       /* Weight for each input   */
    size_t         _nIns;    /* Numbers of input        */
    
    const int32_t  bias;     /* Bias of this perceptron */
    E_PtronSta_t   state;    
    
    int32_t*       _out;     /* Output data stream      */ 
    size_t         _nOuts;   /* Numbers of output       */
};
typedef struct __Perceptron_t __Perceptron_t;

/*========================================================================================
* Data Structure --- FeedForward Neuron Network
*========================================================================================*/
struct __FF_Layer_t{
    struct __FF_LayerInfo_t{
        const int32_t**          _in_data;
        const __Perceptron_t*    _ptron;
        const size_t             _nPtrons_thisLayer;
        const size_t             _nPtrons_prevLayer;
    }*object;
    const struct __FF_Layer_t* const pNext;
    const struct __FF_Layer_t* const pPrev;
};
typedef struct __FF_Layer_t __FF_Layer_t;

__FF_Layer_t* RH_RESULT MAKE_FUNC( FF_Layer , create_input ) ( size_t numPtrons );
__FF_Layer_t* RH_RESULT MAKE_FUNC( FF_Layer , add_hidden   ) ( __FF_Layer_t* prevLayer, size_t numPtrons );



#endif





