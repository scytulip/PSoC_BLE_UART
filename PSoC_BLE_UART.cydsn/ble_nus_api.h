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

#ifndef BLE_NUS_API_H
#define BLE_NUS_API_H
    
#include <project.h>

#define NOTIFY_BIT_MASK 0x01        // Notification bit mask
#define CCCD_VALID_BIT_MASK 0x03    // CCCD notification/indication bit mask
#define MAX_NTF_STR_LEN 20          // Maximum notification string length

/* Global Variables */
extern uint8 glb_uartNotification;
    
void nus_sendstr(char* str);   
    
#endif

/* [] END OF FILE */
