/* 
 * File:   AD22103.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 28 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the definition, constants and functions for use
 *  the AD22103 Temperature Sensor with a low level of complexity.
 */

#ifndef _AD22103_H    /* Guard against multiple inclusion */
#define _AD22103_H


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
        AD22103_RETURN_CODE_SUCCESSFUL,             // Attached successful
        AD22103_RETURN_CODE_ANALOG_CHANNEL_INVALID, // Analog channel invalid
        AD22103_RETURN_CODE_VS_SMALL,               // VS is invalid (less that 2.7V)
        AD22103_RETURN_CODE_VS_BIG                  // Vs is invalid (more that 3.6V)
        
    } AD22103_RETURN_CODE;
    
    
    // AD22103 Sensor class
    typedef struct {
        uint8_t analogChannel; // Analog channel for voltage read
        float vs;              // Voltage Suply attached to the sensor
    } AD22103Sensor;
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
/* ------------------------------------------------------------ */
/*        AD22103_RETURN_CODE AD22103_Attach( AD22103Sensor sensor, uint8_t analogChannel, float Vs )
* 
*         Synopsis:
*           AD22103_Attach( sensor, analogChannel, Vs );
*  
*         Parameters:
*           AD22103Sensor sensor - AD22103 sensor identifier
*           uint8_t analogChannel - analog channel to use.
*           float Vs - Supply source connected on AD22103 sensor (Volts)
* 
*         Return Values:
*           AD22103_RETURN_CODE
*  
*         Description:
*           Attach one AD22103 temperature sensor on an specified analogChannel.
*           This function check that the analog channel and Vs have valids values
*          and reserve the necesary memory for store the sensors data.
*           
*/
    AD22103_RETURN_CODE AD22103_Attach( AD22103Sensor *sensor, uint8_t analogChannel, float Vs );
    
    
/* ------------------------------------------------------------ */
/*        inline uint16_t AD22103_GetRawValue( AD22103Sensor sensor )
* 
*         Synopsis:
*           AD22103_GetRawValue( sensor )
*  
*         Parameters:
*           AD22103Sensor sensor - AD22103 sensor identifier
*           
*         Return Values:
*           uint16_t - raw value on the analog input
*  
*         Description:
*           Return the raw value on the analog input.
*           
*/
    inline uint16_t AD22103_GetRawValue( AD22103Sensor *sensor ){
        return analogRead( sensor->analogChannel );
    }
    
    
/* ------------------------------------------------------------ */
/*        float AD22103_GetTemperature( AD22103Sensor sensor, SENSOR_TEMPERATURE_UNIT unit )
* 
*         Synopsis:
*           AD22103_GetTemperature( sensor, unit );
*  
*         Parameters:
*           AD22103Sensor sensor - AD22103 sensor identifier
*           SENSOR_TEMPERATURE_UNIT unit - define the unit of returned value

*           
*         Return Values:
*           float - Temperature on the selected unit
*  
*         Description:
*           Return the temperature on the selected unit.
*           
*/
    float AD22103_GetTemperature( AD22103Sensor *sensor, SENSOR_TEMPERATURE_UNIT unit );
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
