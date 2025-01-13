#ifndef __NVM_H__
#define __NVM_H__

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <string.h>

#define CAN_DEFAULT_ID  0x426

uint16_t NVMCanIDRead(void);
void NVMCanIDWrite(uint16_t newid);
void NVMDump(int length);
void NVMErase(void);

#endif // end of __NVM_H__

/* *****************************************************************************
 End of File
 */
