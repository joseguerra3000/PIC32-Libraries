/* 
 * File:   AD22103.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 28 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the functions implementation for use
 *  the AD22103 Temperature Sensor with a low level of complexity.
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "../AD22103.h"

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
/*        AD22103_RETURN_CODE AD22103_Attach( AD22103Sensor sensor, uint8_t analogChannel, float Vs )
* 
*         Synopsis:
*           AD22103_Attach( sensor, analogChannel, Vs );
*  
*         Parameters:
*           AD22103Sensor sensor - AD22103 sensor identifier
*           uint8_t analogChannel - analog channel to use.
*           float Vs - Supply source connected on AD22103 sensor ( Volts )
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
AD22103_RETURN_CODE AD22103_Attach( AD22103Sensor *sensor, uint8_t _analogChannel, float _Vs ){
    if( _analogChannel > 15 )
        return AD22103_RETURN_CODE_ANALOG_CHANNEL_INVALID;
    
    if( _Vs < 2.7 )
        return AD22103_RETURN_CODE_VS_SMALL; 
    if( _Vs > 3.6 )
        return AD22103_RETURN_CODE_VS_BIG;
    
    sensor->analogChannel = _analogChannel;
    
    sensor->vs = _Vs*1000;
    
    return AD22103_RETURN_CODE_SUCCESSFUL;
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
float AD22103_GetTemperature( AD22103Sensor *sensor, SENSOR_TEMPERATURE_UNIT unit ){
    uint32_t raw = analogRead( sensor->analogChannel );
    float Ta;
    //Ta = raw*3300*3300/(1024*28*sensor->vs);
    Ta = (raw*3300/(sensor->vs))*3300/(1024*28) - 10.0;
    
    if( unit == SENSOR_TEMPERATURE_UNIT_FAHRENHEIT )
        Ta = TEMPERATURE_ConvertCelsiusToFahrenheit( Ta );
    else if( unit == SENSOR_TEMPERATURE_UNIT_KELVIN )
        Ta = TEMPERATURE_ConvertCelsiusToKelvin( Ta );
    
    return Ta;
}
    

/* *****************************************************************************
 End of File
 */
