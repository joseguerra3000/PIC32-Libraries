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
#ifndef _TEMPERATURE_COMMON_H    /* Guard against multiple inclusion */
#define _TEMPERATURE_COMMON_H    


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

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

    typedef enum {
        
        SENSOR_TEMPERATURE_UNIT_CELSIUS,
        SENSOR_TEMPERATURE_UNIT_KELVIN,
        SENSOR_TEMPERATURE_UNIT_FAHRENHEIT
                
    } SENSOR_TEMPERATURE_UNIT;
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
/* ------------------------------------------------------------ */
/*        inline float TEMPERATURE_ConvertCelsiusToKelvin( float celsius )
* 
*         Synopsis:
*           TEMPERATURE_ConvertCelsiusToKelvin( celsius );
*  
*         Parameters:
*           float celsius - a temperature value in degree celsius
* 
*         Return Values:
*           float - the temperature value in degree kelvin
*  
*         Description:
*           Convert a temperature value from degree celsius to degree kelvin
*           
*/
    inline float TEMPERATURE_ConvertCelsiusToKelvin( float celsius ){
        return celsius + 273.15;
    }
    
/* ------------------------------------------------------------ */
/*        inline float TEMPERATURE_ConvertCelsiusToFahrenheit( float celsius )
* 
*         Synopsis:
*           TEMPERATURE_ConvertCelsiusToFahrenheit( celsius );
*  
*         Parameters:
*           float celsius - a temperature value in degree celsius
* 
*         Return Values:
*           float - the temperature value in degree Fahrenheit
*  
*         Description:
*           Convert a temperature value from degree celsius to degree Fahrenheit
*           
*/
    inline float TEMPERATURE_ConvertCelsiusToFahrenheit( float celsius ){
        return (1,8*celsius + 32.0);
    }

    
    
    
/* ------------------------------------------------------------ */
/*        inline float TEMPERATURE_ConvertKelvinToCelsius( float kelvin )
* 
*         Synopsis:
*           TEMPERATURE_ConvertKelvinToCelsius( kelvin )
*  
*         Parameters:
*           float kelvin - a temperature value in degree kelvin
* 
*         Return Values:
*           float - the temperature value in degree celsius
*  
*         Description:
*           Convert a temperature value from degree kelvin to degree celsius
*           
*/
    inline float TEMPERATURE_ConvertKelvinToCelsius( float kelvin ){
        return kelvin - 273.15;
    }
    
/* ------------------------------------------------------------ */
/*        inline float TEMPERATURE_ConvertKelvinToFahrenheit( float kelvin )
* 
*         Synopsis:
*           TEMPERATURE_ConvertKelvinToFahrenheit( kelvin )
*  
*         Parameters:
*           float kelvin - a temperature value in degree kelvin
* 
*         Return Values:
*           float - the temperature value in degree fahrenheit
*  
*         Description:
*           Convert a temperature value from degree kelvin to degree fahrenheit
*           
*/
    inline float TEMPERATURE_ConvertKelvinToFahrenheit( float kelvin ){
        return (kelvin*9.0/5.0 - 459.67);
    }

    
    
/* ------------------------------------------------------------ */
/*        inline float TEMPERATURE_ConvertFahrenheitToCelsius( float fahrenheit )
* 
*         Synopsis:
*           TEMPERATURE_ConvertFahrenheitToCelsius( fahrenheit )
*  
*         Parameters:
*           float fahrenheit - a temperature value in degree fahrenheit
* 
*         Return Values:
*           float - the temperature value in degree celsius
*  
*         Description:
*           Convert a temperature value from degree fahrenheit to degree celsius
*           
*/    
    inline float TEMPERATURE_ConvertFahrenheitToCelsius( float fahrenheit ){
        return (fahrenheit - 32.0)/1.8;
    }

/* ------------------------------------------------------------ */
/*        inline float TEMPERATURE_ConvertFahrenheitToKelvin( float fahrenheit )
* 
*         Synopsis:
*           TEMPERATURE_ConvertFahrenheitToKelvin( fahrenheit )
*  
*         Parameters:
*           float fahrenheit - a temperature value in degree kelvin
* 
*         Return Values:
*           float - the temperature value in degree kelvin
*  
*         Description:
*           Convert a temperature value from degree fahrenheit to degree kelvin
*           
*/    
    inline float TEMPERATURE_ConvertFahrenheitToKelvin( float fahrenheit ){
        return (fahrenheit + 459.67)/1.8;
    }
    
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
