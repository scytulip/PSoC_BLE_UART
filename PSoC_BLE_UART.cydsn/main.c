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
#include <stdio.h>
#include "ble_nus_api.h"

/* Macros */
#define printf(...)

uint8 snd_inc = 0; //Send string indicator

/* Pre-defined Functions */
void StackEventHandler( uint32 eventCode, void *eventParam );

/* Interrupt Processing */
void TimerIntHandler(void)
{
    if(CySysWdtGetInterruptSource() & CY_SYS_WDT_COUNTER1_INT)
    {
        snd_inc ++;
        CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_INT);
    }
}

/* Setup WatchDog */
void WDT_Start(void)
{
    /* Unlock the WDT registers for modification */
    CySysWdtUnlock(); 
    /* Setup ISR callback */
    WdtIsr_StartEx(TimerIntHandler);
    /* Write the mode to generate interrupt on match */
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER1, CY_SYS_WDT_MODE_INT);
    /* Configure the WDT counter clear on a match setting */
    CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER1, 1u);
    /* Configure the WDT counter match comparison value */
    CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1, 32767u);
    /* Reset WDT counter */
    CySysWdtResetCounters(CY_SYS_WDT_COUNTER1);
    /* Enable the specified WDT counter */
    CySysWdtEnable(CY_SYS_WDT_COUNTER1_MASK);
    /* Lock out configuration changes to the Watchdog timer registers */
    CySysWdtLock();    
}

int main()
{
    CyGlobalIntEnable;   /* Enable global interrupts */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    glb_uartNotification = 0;

    CyBle_Start( StackEventHandler );
    WDT_Start();
    
    for(;;)
    {
        switch(CyBle_GetState())
        {
            case CYBLE_STATE_CONNECTED:
                if (snd_inc)
                {
                    nus_sendstr("Hello.");
                    snd_inc = 0;
                }
                break;
            default:
                break;
        }
        
        /* Place your application code here */
        CyBle_ProcessEvents();
    }
}

void StackEventHandler( uint32 eventCode, void *eventParam )
{
    CYBLE_API_RESULT_T apiResult;
    CYBLE_GATTS_WRITE_REQ_PARAM_T* wrReqParam;
    
    switch( eventCode )
    {
        /* Generic events */

        case CYBLE_EVT_HOST_INVALID:
        break;

        case CYBLE_EVT_STACK_ON:
            printf("Bluetooth ON.\n");
            apiResult = CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
            if ( apiResult != CYBLE_ERROR_OK )
            {
                printf("Advertisement Error: %x\n", apiResult);
            }
        break;

        case CYBLE_EVT_TIMEOUT:
        break;

        case CYBLE_EVT_HARDWARE_ERROR:
            printf("Hardware Error.\n");
        break;

        case CYBLE_EVT_HCI_STATUS:
        break;

        case CYBLE_EVT_STACK_BUSY_STATUS:
        break;

        case CYBLE_EVT_PENDING_FLASH_WRITE:
        break;


        /* GAP events */

        case CYBLE_EVT_GAP_AUTH_REQ:
        break;

        case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
        break;

        case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
        break;

        case CYBLE_EVT_GAP_AUTH_COMPLETE:
        break;

        case CYBLE_EVT_GAP_AUTH_FAILED:
        break;

        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            printf("Device is connected.\n");
        break;

        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            printf("Device is disconnected.\n");
            apiResult = CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
            if ( apiResult != CYBLE_ERROR_OK )
            {
                printf("Advertisement Error: %x\n", apiResult);
            }
        break;

        case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
        break;

        case CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE:
        break;

        case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
        break;


        /* GAP Peripheral events */

        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
        break;


        /* GAP Central events */

        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT:
        break;

        case CYBLE_EVT_GAPC_SCAN_START_STOP:
        break;


        /* GATT events */

        case CYBLE_EVT_GATT_CONNECT_IND:
        break;

        case CYBLE_EVT_GATT_DISCONNECT_IND:
        break;


        /* GATT Client events (CYBLE_EVENT_T) */

        case CYBLE_EVT_GATTC_ERROR_RSP:
        break;

        case CYBLE_EVT_GATTC_XCHNG_MTU_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BY_TYPE_RSP:
        break;

        case CYBLE_EVT_GATTC_FIND_INFO_RSP:
        break;

        case CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_BLOB_RSP:
        break;

        case CYBLE_EVT_GATTC_READ_MULTI_RSP:
        break;

        case CYBLE_EVT_GATTC_WRITE_RSP:
        break;

        case CYBLE_EVT_GATTC_EXEC_WRITE_RSP:
        break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF:
        break;

        case CYBLE_EVT_GATTC_HANDLE_VALUE_IND:
        break;


        /* GATT Client events (CYBLE_EVT_T) */

        case CYBLE_EVT_GATTC_INDICATION:
        break;

        case CYBLE_EVT_GATTC_SRVC_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_CHAR_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_DESCR_DISCOVERY_FAILED:
        break;

        case CYBLE_EVT_GATTC_SRVC_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_CHAR_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_DESCR_DUPLICATION:
        break;

        case CYBLE_EVT_GATTC_SRVC_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_INCL_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_CHAR_DISCOVERY_COMPLETE:
        break;

        case CYBLE_EVT_GATTC_DISCOVERY_COMPLETE:
        break;


        /* GATT Server events (CYBLE_EVENT_T) */

        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
        break;

        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            
            /* If the attribute hanlde of the characteristic written to
            * is equal to that of RX characteristic, then extract the 
            * UART Rx data. */
            if (CYBLE_NORDIC_BLE_UART_NUS_TX_CHAR_HANDLE ==
                wrReqParam -> handleValPair.attrHandle)
            {
                printf("Data recevied, length = %d\n",
                    wrReqParam -> handleValPair.value.len);
            }
            
            if (CYBLE_NORDIC_BLE_UART_NUX_RX_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE ==
                wrReqParam -> handleValPair.attrHandle)
            {
                /* Only the first and second lowest significant bit can be
                * set when writing on CCCD. If any other bit is set, then
                * send error code */
                if(0x00 == 
                    (wrReqParam->handleValPair.value.val
                        [CYBLE_NORDIC_BLE_UART_NUX_RX_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX] & 
                    (~CCCD_VALID_BIT_MASK)))
                {
                    /* Set flag for application to know status of notifications.
                    * Only one byte is read as it contains the set value. */
                    glb_uartNotification = 
                        wrReqParam->handleValPair.value.val
                        [CYBLE_NORDIC_BLE_UART_NUX_RX_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX];
                    /* Update GATT DB with latest CCCD value */
                    CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0,
                        &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                }
                else
                {
                    /* Send error response for Invalid PDU against Write
                    * request */
                    CYBLE_GATTS_ERR_PARAM_T err_param;

                    err_param.opcode = CYBLE_GATT_WRITE_REQ;
                    err_param.attrHandle = wrReqParam->handleValPair.attrHandle;
                    err_param.errorCode = CYBLE_GATT_ERR_INVALID_PDU; 
                    
                    /* Send Error Response */
                    (void)CyBle_GattsErrorRsp(cyBle_connHandle, &err_param);
                
                    /* Return to main loop */
                    return;
                }
            }
            /* Send response to the Write request */
            CyBle_GattsWriteRsp(cyBle_connHandle);
        break;

        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
        break;

        case CYBLE_EVT_GATTS_PREP_WRITE_REQ:
        break;

        case CYBLE_EVT_GATTS_EXEC_WRITE_REQ:
        break;

        case CYBLE_EVT_GATTS_HANDLE_VALUE_CNF:
        break;

        case CYBLE_EVT_GATTS_DATA_SIGNED_CMD_REQ:
        break;


        /* GATT Server events (CYBLE_EVT_T) */

        case CYBLE_EVT_GATTS_INDICATION_ENABLED:
        break;

        case CYBLE_EVT_GATTS_INDICATION_DISABLED:
        break;


        /* L2CAP events */

        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ:
        break;

        case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
        break;

        case CYBLE_EVT_L2CAP_COMMAND_REJ:
        break;

        case CYBLE_EVT_L2CAP_CBFC_CONN_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_CONN_CNF:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DISCONN_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DATA_READ:
        break;

        case CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND:
        break;

        case CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND:
        break;


        /* default catch-all case */

        default:
        break;
    }
}

