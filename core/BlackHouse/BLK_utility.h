
#ifndef _BLK_DATA_H
#define _BLK_DATA_H

#include "RH_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CHARLOG_PER_TIME     100

void __logMessage     (const char* format,...);
void __deleteMessage  (void);
void __showMessage    (int(*PRINTF_METHOD)(const char* ,...));

#ifdef __cplusplus
}
#endif

#endif

