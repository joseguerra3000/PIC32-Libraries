/* 
 * File:   spi.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 29 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the definition, constants and functions for use
 *  SPI modules built-in a PIC32MX with a low level of complexity.
 */

#ifndef _SPI_H    /* Guard against multiple inclusion */
#define _SPI_H


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

    #define SPI_DEFAULT_BAUD_RATE 1000000L

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************
    typedef SPI_COMMUNICATION_WIDTH SPI_DATA_WIDTH;
    // SPIMaster class
    typedef struct {
        SPI_MODULE_ID moduleId;             // SPI module Id
        PORTS_CHANNEL ssChannel;            // Slave Select Port
        PORTS_BIT_POS ssBitPos;             // Slave Select Bit
        SPI_DATA_WIDTH dataWidth;           // 8bits, 16bits or 32bits
        SPI_INPUT_SAMPLING_PHASE inPhase;   // instant to sample each bit on input line
        SPI_CLOCK_POLARITY polarity;        // select idle state
        SPI_OUTPUT_DATA_PHASE outPhase;     // select the edge to put each bit on output line
        uint32_t baudRate;                  // real Baud Rate
    } SPIMaster;
    
    
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
    
    /*------------------------------------------------------------------------*/
    /* SPI1 Interface Functions                                               */
    /*------------------------------------------------------------------------*/
    
    
    void SPI1_SetConfiguration( SPI_DATA_WIDTH datawidth,
                              SPI_INPUT_SAMPLING_PHASE inputPhase,
                              SPI_CLOCK_POLARITY polarity,
                              SPI_OUTPUT_DATA_PHASE outputPhase,
                              uint32_t baudRate);
    
    void SPI1_SetSlaveSelectorPin( PORTS_CHANNEL ssChannel,
                                  PORTS_BIT_POS ssBitPos );

    void SPI1_StartTransaction( );
    
    uint8_t SPI1_Transfer( uint8_t data );
    
    uint16_t SPI1_Transfer16bits( uint16_t data );
    
    uint32_t SPI1_Transfer32bits( uint32_t data );
    
    void SPI1_EndTransaction( );
    
    
    /*------------------------------------------------------------------------*/
    /* SPI2 Interface Functions                                               */
    /*------------------------------------------------------------------------*/
    
    
    void SPI2_SetConfiguration( SPI_DATA_WIDTH datawidth,
                              SPI_INPUT_SAMPLING_PHASE inputPhase,
                              SPI_CLOCK_POLARITY polarity,
                              SPI_OUTPUT_DATA_PHASE outputPhase,
                              uint32_t baudRate);
    
    void SPI2_SetSlaveSelectorPin( PORTS_CHANNEL ssChannel,
                                  PORTS_BIT_POS ssBitPos );

    void SPI2_StartTransaction( );
    
    uint8_t SPI2_Transfer( uint8_t data );
    
    uint16_t SPI2_Transfer16bits( uint16_t data );
    
    uint32_t SPI2_Transfer32bits( uint32_t data );
    
    void SPI2_EndTransaction( );
    
    
    
/* ------------------------------------------------------------ */
/*        LM35_RETURN_CODE LM35_Attach( LM35Sensor *sensor, uint8_t analogChannel )
* 
*         Synopsis:
*           LM35_Attach( &sensor, analogChannel );
*  
*         Parameters:
*           LM35Sensor* sensor - LM35 sensor identifier
*           uint8_t analogChannel - analog channel to use.
* 
*         Return Values:
*           LM35_RETURN_CODE
*  
*         Description:
*           Attach one LM35 temperature sensor on an specified analogChannel.
*           This function check that the analog channel is a valid channel and
*          store the configuration on 'sensor' var.
*           
*/
//    LM35_RETURN_CODE AD22103_Attach( LM35Sensor *sensor, uint8_t analogChannel );
    
    
/* ------------------------------------------------------------ */
/*        inline uint16_t LM35_GetRawValue( LM35Sensor sensor )
* 
*         Synopsis:
*           LM35_GetRawValue( sensor )
*  
*         Parameters:
*           LM35Sensor sensor - LM35 sensor identifier
*           
*         Return Values:
*           uint16_t - raw value on the analog input
*  
*         Description:
*           Return the raw value on the analog input.
*           
*/
 //   inline uint16_t LM35_GetRawValue( LM35Sensor *sensor ){
 //       return analogRead( sensor->analogChannel );
 //   }
   
    
/* ------------------------------------------------------------ */
/*        float LM35_GetTemperature( LM35Sensor sensor, SENSOR_TEMPERATURE_UNIT unit )
* 
*         Synopsis:
*           LM35_GetTemperature( sensor, unit );
*  
*         Parameters:
*           LM35Sensor sensor - LM35 sensor identifier
*           SENSOR_TEMPERATURE_UNIT unit - define the unit of returned value
*
*           
*         Return Values:
*           float - Temperature on the selected unit
*  
*         Description:
*           Return the temperature on the selected unit.
*           
*/
  //  float LM35_GetTemperature( LM35Sensor *sensor, SENSOR_TEMPERATURE_UNIT unit );
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
