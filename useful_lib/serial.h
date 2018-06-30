/* 
 * File:   serial.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 30 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the definition, constants and functions for use
 *  USART modules built-in a PIC32MX with a low level of complexity.
 */

#ifndef _SERIAL_H    /* Guard against multiple inclusion */
#define _SERIAL_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <peripheral/peripheral.h>
#include "../cerebot32MX4.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

    #define SERIAL_DEFAULT_BAUD_RATE 9600

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
    typedef USART_MODULE_ID SERIAL_MODULE_ID;
    typedef USART_LINECONTROL_MODE SERIAL_LINECONTROL_MODE;
    typedef USART_RECEIVE_INTR_MODE SERIAL_RECEIVE_INTR_MODE;
    typedef USART_TRANSMIT_INTR_MODE SERIAL_TRANSMIT_INTR_MODE;
    
    typedef enum{
        SERIAL_STATE_OK,
        SERIAL_STATE_TX_BUFFER_OVERFLOW,
        SERIAL_STATE_RX_BUFFER_OVERFLOW,
        SERIAL_STATE_NO_FREE_SPACE_FOR_BUFFER
    } SERIAL_STATE;
    
    // Serial class
    typedef struct {
        SERIAL_MODULE_ID moduleId;             // USART module Id
        uint32_t baudRate;
        SERIAL_LINECONTROL_MODE lineControlMode;
        
        SERIAL_RECEIVE_INTR_MODE rxInterruptionMode;
        SERIAL_TRANSMIT_INTR_MODE txInterruptionMode;
        
        INT_VECTOR intVector;
        
        
        INT_SOURCE rxIntSource,
                txIntSource,
                errorIntSource;
        
        uint8_t rxBufferSz, 
                txBufferSz;
        
        volatile uint8_t rxBufferRead;
        volatile uint8_t rxBufferEnd;
        
        volatile uint8_t txBufferRead;
        volatile uint8_t txBufferEnd;
                
        volatile char* rxBuffer;
        volatile char* txBuffer;
    } SerialModule;
    
    
    SerialModule Serial1 = {
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
    };


    SerialModule Serial2 = {
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
        (char *)NULL,
        (char *)NULL
    };


    
// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************
    
    
    /*------------------------------------------------------------------------*/
    /* Generic Serial Functions                                               */
    /*------------------------------------------------------------------------*/

    void Serial_SetConfiguration( SerialModule* serial, 
                                    uint32_t baudRate,
                                    SERIAL_LINECONTROL_MODE lineControlMode,
                                    SERIAL_RECEIVE_INTR_MODE rxInterruptionMode,
                                    SERIAL_TRANSMIT_INTR_MODE txInterruptionMode);

    SERIAL_STATE Serial_Enable( SerialModule* serial, uint32_t baudRate );

    SERIAL_STATE Serial_Print( SerialModule* serial, char *str, uint8_t len, bool endLine );

    uint8_t Serial_Read( SerialModule* serial, char *outBytes );

    void Serial_Disable( SerialModule* serial );
    
    
    /*------------------------------------------------------------------------*/
    /* Serial1 Interface Functions                                            */
    /*------------------------------------------------------------------------*/
    
    inline void Serial1_SetConfiguration( uint32_t baudRate,
                                  SERIAL_LINECONTROL_MODE lineControlMode,
                                  SERIAL_RECEIVE_INTR_MODE rxInterruptionMode,
                                  SERIAL_TRANSMIT_INTR_MODE txInterruptionMode){
        Serial_SetConfiguration( &Serial1, baudRate, lineControlMode, rxInterruptionMode, txInterruptionMode );
    }

    inline SERIAL_STATE Serial1_Enable( uint32_t baudRate ){
        return Serial_Enable( &Serial1, baudRate );
    }

    inline SERIAL_STATE Serial1_Print( char *str, uint8_t len, bool endLine ){
        return Serial_Print( &Serial1, str, len, endLine );
    }
        
    inline uint8_t Serial1_Read( char *outBytes ){
        return Serial_Read( &Serial1, outBytes );
    }
    
    inline void Serial1_Disable(){
        Serial_Disable( &Serial1 );
    }
    
    /*------------------------------------------------------------------------*/
    /* Serial2 Interface Functions                                               */
    /*------------------------------------------------------------------------*/

    inline void Serial2_SetConfiguration( uint32_t baudRate,
                                  SERIAL_LINECONTROL_MODE lineControlMode,
                                  SERIAL_RECEIVE_INTR_MODE rxInterruptionMode,
                                  SERIAL_TRANSMIT_INTR_MODE txInterruptionMode){
        Serial_SetConfiguration( &Serial2, baudRate, lineControlMode, rxInterruptionMode, txInterruptionMode );
    }

    inline SERIAL_STATE Serial2_Enable( uint32_t baudRate ){
        return Serial_Enable( &Serial2, baudRate );
    }

    inline SERIAL_STATE Serial2_Print( char *str, uint8_t len, bool endLine ){
        return Serial_Print( &Serial2, str, len, endLine );
    }
        
    inline uint8_t Serial2_Read( char *outBytes ){
        return Serial_Read( &Serial2, outBytes );
    }
    
    inline void Serial2_Disable(){
        Serial_Disable( &Serial2 );
    }

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
