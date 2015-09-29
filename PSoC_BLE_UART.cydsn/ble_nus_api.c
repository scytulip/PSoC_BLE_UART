/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "ble_nus_api.h"

/* Global Variables */
uint8 glb_uartNotification = 0;

/**
* @brief Send a string through BLE UART (NUS). String longer than 20 characters will be truncated.
* @param[in] str String to be sent.
*/
void nus_sendstr(char* str)
{   
    if (glb_uartNotification & NOTIFY_BIT_MASK)
    {
        char    str_snd[MAX_NTF_STR_LEN+1];
    
        int     str_len = strlen(str);
        str_len = (str_len>MAX_NTF_STR_LEN) ? MAX_NTF_STR_LEN : str_len;
       
        memcpy(str_snd, str, str_len+1);
        str_snd[MAX_NTF_STR_LEN] = '\0';
        
        /* 'notificationHandle' is handle to store notification data parameters */
        CYBLE_GATTS_HANDLE_VALUE_NTF_T notificationHandle; 
        
        /* Update Notification handle with new data*/
        notificationHandle.attrHandle = CYBLE_NORDIC_BLE_UART_NUX_RX_CHAR_HANDLE;
        notificationHandle.value.val = (uint8*) str_snd;
        notificationHandle.value.len = str_len;
        
        /* Report data to BLE component for sending data by notifications*/
        CyBle_GattsNotification(cyBle_connHandle, &notificationHandle);
        CyBle_ProcessEvents();
    }       
}

void nus_sendstr_cached()
{
}
/* [] END OF FILE */
