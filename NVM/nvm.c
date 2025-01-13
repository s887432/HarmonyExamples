#include "nvm.h"

// Define a constant array in Flash.
// It must be aligned to row boundary and size has to be in multiple of rows
const uint8_t nvm_user_start_address[NVMCTRL_FLASH_ROWSIZE] __attribute__((aligned(NVMCTRL_FLASH_ROWSIZE),keep,externally_visible,space(prog)))= {0};

#define NVM_POS_CANID   0x4
uint8_t *NVMCanIDptr = (uint8_t*)(nvm_user_start_address+NVM_POS_CANID);
uint8_t data [NVMCTRL_FLASH_PAGESIZE] = {0};

uint16_t NVMCanIDRead(void)
{
    uint16_t id = CAN_DEFAULT_ID;
        
    if( (NVMCanIDptr[0] != 0xFF || NVMCanIDptr[1] != 0xFF) && (NVMCanIDptr[0] != 0 || NVMCanIDptr[1] != 0) )
    {
        // get register ID
        id = NVMCanIDptr[0] * 256 + NVMCanIDptr[1];
    }
    
    return id;
}

void NVMCanIDWrite(uint16_t newid)
{
    memset(data, 0, NVMCTRL_FLASH_PAGESIZE);
    data[NVM_POS_CANID] = (newid / 256) & 0xFF;
    data[NVM_POS_CANID+1] = (newid & 0xFF);
        
    while(NVMCTRL_IsBusy());
    NVMCTRL_RowErase((uint32_t)nvm_user_start_address);
    while(NVMCTRL_IsBusy());
    NVMCTRL_PageWrite((uint32_t *)data, (uint32_t)nvm_user_start_address);
    while(NVMCTRL_IsBusy());
}

void NVMDump(int length)
{
    uint8_t *ptr = (uint8_t*)nvm_user_start_address;
    
    printf("[Dump] ");
    for(int i=0; i<length; i++)
    {
        printf("%02X ", ptr[i]);
        if ( i!=0 && i%16==0 )
        {
            printf("\r\n");
        }
    }
    
    printf("\r\n");
}

void NVMErase(void)
{
    while(NVMCTRL_IsBusy());
    /* Erase the row */
    NVMCTRL_RowErase((uint32_t)nvm_user_start_address);
    while(NVMCTRL_IsBusy());
}
/* *****************************************************************************
 End of File
 */
