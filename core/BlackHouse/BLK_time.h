#ifndef _BLK_TIME_H
#define _BLK_TIME_H

//#include "RH_common.h"
//#include "RH_config.h"

#ifdef __cpluplus
extern "C"{
#endif

volatile const char* __PST2BJT( const char YYYYMMDD_HHMMSS[20] );
volatile const char* __BJT2PST( const char YYYYMMDD_HHMMSS[20] );


#ifdef __cpluplus
}
#endif


#endif
