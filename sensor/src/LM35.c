/* 
 * File:   AD22103.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 29 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the functions implementation for use
 *  the LM35 Temperature Sensor with a low level of complexity.
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "../LM35.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */


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
LM35_RETURN_CODE LM35_Attach( LM35Sensor *sensor, uint8_t _analogChannel ){
    if( _analogChannel > 15 )
        return LM35_RETURN_CODE_ANALOG_CHANNEL_INVALID;

    sensor->analogChannel = _analogChannel;
    
    return LM35_RETURN_CODE_SUCCESSFUL;
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
float LM35_GetTemperature( LM35Sensor *sensor, SENSOR_TEMPERATURE_UNIT unit ){
    uint32_t raw = analogRead( sensor->analogChannel );
    float Ta = ((float)(raw*3300))/(10240.0);

    if( unit == SENSOR_TEMPERATURE_UNIT_FAHRENHEIT )
        Ta = TEMPERATURE_ConvertCelsiusToFahrenheit( Ta );
    else if( unit == SENSOR_TEMPERATURE_UNIT_KELVIN )
        Ta = TEMPERATURE_ConvertCelsiusToKelvin( Ta );
    
    return Ta;
}
    

/* *****************************************************************************
 End of File
 */
