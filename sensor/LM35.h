/* 
 * File:   AD22103.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 29 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the definition, constants and functions for use
 *  the LM35 Temperature Sensor with a low level of complexity.
 */

#ifndef _LM35_H    /* Guard against multiple inclusion */
#define _LM35_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../useful_lib/analog.h"
#include "temperature-common.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************
    
 
    typedef enum{
        LM35_RETURN_CODE_SUCCESSFUL,             // Attached successful
        LM35_RETURN_CODE_ANALOG_CHANNEL_INVALID, // Analog channel invalid
    } LM35_RETURN_CODE;
    
    
    // AD22103 Sensor class
    typedef struct {
        uint8_t analogChannel; // Analog channel for voltage read
    } LM35Sensor;
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
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
    LM35_RETURN_CODE AD22103_Attach( LM35Sensor *sensor, uint8_t analogChannel );
    
    
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
    inline uint16_t LM35_GetRawValue( LM35Sensor *sensor ){
        return analogRead( sensor->analogChannel );
    }
    
    
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
    float LM35_GetTemperature( LM35Sensor *sensor, SENSOR_TEMPERATURE_UNIT unit );
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
