/* 
 * File:   serial.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 30 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the definition, constants and functions implementation 
 *  for use USART modules built-in a PIC32MX with a low level of complexity.
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "../serial.h"
#include <sys/attribs.h>
#include <stdint.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
/*extern SerialModule Serial1 = {
    USART_ID_1,
    SERIAL_DEFAULT_BAUD_RATE,
    USART_8N1,
    USART_RECEIVE_FIFO_ONE_CHAR,
    USART_TRANSMIT_FIFO_NOT_FULL,
    INT_VECTOR_UART1,
    INT_SOURCE_USART_1_RECEIVE,
    INT_SOURCE_USART_1_TRANSMIT,
    INT_SOURCE_USART_1_ERROR,
    128,
    128,
    0,
    0,
    (char *)NULL,
    (char *)NULL 
};*/

/*extern SerialModule Serial2 = {
    USART_ID_2,
    SERIAL_DEFAULT_BAUD_RATE,
    USART_8N1,
    USART_RECEIVE_FIFO_ONE_CHAR,
    USART_TRANSMIT_FIFO_NOT_FULL,
    INT_VECTOR_UART2,
    INT_SOURCE_USART_2_RECEIVE,
    INT_SOURCE_USART_2_TRANSMIT,
    INT_SOURCE_USART_2_ERROR,
    128,
    128,
    0,
    0,
    (char*)NULL,
    (char*)NULL
};*/

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*------------------------------------------------------------------------*/
/* Generic Serial Functions                                               */
/*------------------------------------------------------------------------*/
void Serial_SetConfiguration( SerialModule* serial, 
                                    uint32_t baudRate,
                                    SERIAL_LINECONTROL_MODE lineControlMode,
                                    SERIAL_RECEIVE_INTR_MODE rxInterruptionMode,
                                    SERIAL_TRANSMIT_INTR_MODE txInterruptionMode){
    serial->baudRate = baudRate;
    serial->lineControlMode = lineControlMode;
    serial->rxInterruptionMode = rxInterruptionMode;
    serial->txInterruptionMode = txInterruptionMode;
}

SERIAL_STATE Serial_Enable( SerialModule* serial, uint32_t baudRate ){
    serial->baudRate = baudRate;
    
    serial->txBuffer = (char *)malloc( sizeof(char)*(serial->txBufferSz) );
    serial->rxBuffer = (char *)malloc( sizeof(char)*(serial->txBufferSz) );
    
    if( serial->txBuffer == NULL || serial->rxBuffer == NULL )
        return SERIAL_STATE_NO_FREE_SPACE_FOR_BUFFER;
    
    // Disable USART module
    PLIB_USART_Disable( serial->moduleId );
    // Set the baud rate
    PLIB_USART_BaudRateSet( serial->moduleId, Pb_Clk, serial->baudRate );
    serial->baudRate = PLIB_USART_BaudRateGet( serial->moduleId, Pb_Clk );
    // Sets the USART data flow configuration
    PLIB_USART_LineControlModeSelect( serial->moduleId, serial->lineControlMode );
    
    PLIB_USART_InitializeOperation( serial->moduleId, serial->rxInterruptionMode, serial->txInterruptionMode, USART_ENABLE_TX_RX_USED );

    PLIB_INT_VectorPrioritySet( INT_ID_0, serial->intVector, INT_PRIORITY_LEVEL6 );
    PLIB_INT_VectorSubPrioritySet( INT_ID_0, serial->intVector, INT_SUBPRIORITY_LEVEL3 );
    
    // Clear all USART Source Flags
    PLIB_INT_SourceFlagClear( INT_ID_0, serial->txIntSource );
    PLIB_INT_SourceFlagClear( INT_ID_0, serial->rxIntSource );
    PLIB_INT_SourceFlagClear( INT_ID_0, serial->errorIntSource );
    
    // Enable Uart Transmit and receive interrupts
    PLIB_INT_SourceEnable( INT_ID_0, serial->txIntSource );
    PLIB_INT_SourceEnable( INT_ID_0, serial->rxIntSource );
    
    PLIB_USART_Enable( serial->moduleId );
    
    PLIB_USART_ReceiverEnable( serial->moduleId );
    return SERIAL_STATE_OK;
}


SERIAL_STATE Serial_Print( SerialModule* serial, char *str, uint8_t len, bool endLine ){
    uint8_t i;
    char *nl = "\r\n";
    volatile uint8_t *end = &(serial->txBufferEnd);
    for( i = 0; i < len; i++ ){
        
        serial->txBuffer[ (*end)++ ] = str[i];
        
        if( *end == serial->txBufferSz )
            *end = 0;
        
        if( *end == serial->txBufferRead )
            return SERIAL_STATE_TX_BUFFER_OVERFLOW;
        
    }
    if( endLine ){
        for( i = 0; i < 2; i++ ){
            serial->txBuffer[ (*end)++ ] = nl[i];

            if( *end == serial->txBufferSz )
                *end = 0;
    
            if( *end == serial->txBufferRead )
                return SERIAL_STATE_TX_BUFFER_OVERFLOW;

        
        }
    }
    
    if( PLIB_USART_TransmitterIsEmpty( serial->moduleId ) ){
        PLIB_USART_TransmitterEnable( serial->moduleId );
        PLIB_INT_SourceFlagSet( INT_ID_0, serial->txIntSource );
    }
    
    return SERIAL_STATE_OK;
    
}

uint8_t Serial_Read( SerialModule* serial, char *outBytes ){
    int i = 0;
    while( serial->rxBufferRead != serial->rxBufferEnd ){
        outBytes[ i++ ] = serial->rxBuffer[ serial->rxBufferRead++ ];
    }
    outBytes[ i ] = '\0';
    
    return i; 
}


void Serial_Disable( SerialModule* serial ){
    PLIB_USART_Disable( USART_ID_1 );
    
    free( (void*)(serial->txBuffer) );
    free( (void*)(serial->rxBuffer) );

}


  
/*------------------------------------------------------------------------*/
/* Serial1 Interrupt Routine Function                                     */
/*------------------------------------------------------------------------*/

void __ISR( _UART_1_VECTOR, IPL6AUTO ) UART1_InterruptRoutine(){
    
    if( PLIB_INT_SourceFlagGet( INT_ID_0, INT_SOURCE_USART_1_TRANSMIT ) ){
        PLIB_INT_SourceFlagClear( INT_ID_0, INT_SOURCE_USART_1_TRANSMIT );
        
        if( Serial1.txBufferRead != Serial1.txBufferEnd ){
            PLIB_USART_TransmitterByteSend( USART_ID_1, Serial1.txBuffer[ Serial1.txBufferRead++ ] );
            if ( Serial1.txBufferRead == Serial1.txBufferSz )
                Serial1.txBufferRead = 0;
        }
    }
    
    if( PLIB_INT_SourceFlagGet( INT_ID_0, INT_SOURCE_USART_1_RECEIVE ) ){
        PLIB_INT_SourceFlagClear( INT_ID_0, INT_SOURCE_USART_1_RECEIVE );
        
        Serial1.rxBuffer[ Serial1.rxBufferEnd++ ] = PLIB_USART_ReceiverByteReceive( USART_ID_1 );
        if ( Serial1.rxBufferEnd == Serial1.rxBufferSz )
            Serial1.rxBufferEnd = 0;
    }


}


/*------------------------------------------------------------------------*/
/*  Serial2 Interrupt Routine Function                                    */
/*------------------------------------------------------------------------*/

void __ISR( _UART_2_VECTOR, IPL6AUTO ) UART2_InterruptRoutine(){
    
    if( PLIB_INT_SourceFlagGet( INT_ID_0, INT_SOURCE_USART_2_TRANSMIT ) ){
        PLIB_INT_SourceFlagClear( INT_ID_0, INT_SOURCE_USART_2_TRANSMIT );
        
        if( Serial2.txBufferRead != Serial2.txBufferEnd ){
            PLIB_USART_TransmitterByteSend( USART_ID_2, Serial2.txBuffer[ Serial2.txBufferRead++ ] );
            if ( Serial2.txBufferRead == Serial2.txBufferSz )
                Serial2.txBufferRead = 0;
        }
    }
    
    if( PLIB_INT_SourceFlagGet( INT_ID_0, INT_SOURCE_USART_2_RECEIVE ) ){
        PLIB_INT_SourceFlagClear( INT_ID_0, INT_SOURCE_USART_2_RECEIVE );
        
        Serial2.rxBuffer[ Serial2.rxBufferEnd++ ] = PLIB_USART_ReceiverByteReceive( USART_ID_2 );
        if ( Serial2.rxBufferEnd == Serial2.rxBufferSz )
            Serial2.rxBufferEnd = 0;
    }


}



/* *****************************************************************************
 End of File
 */
