/* 
 * File:   adc.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 18 de mayo de 2018, 2:30
 * 
 * 
 * 
 * Summary:
 *  This file have the definition, constants and functions for use
 *  the ADC module with a low level of complexity.
 */

#ifndef _MY_ADC_CEREBOT32MX4_H
#define	_MY_ADC_CEREBOT32MX4_H

#include "../cerebot32MX4.h"
#include <xc.h>
#include <inttypes.h>

/*Constants*/
#define _ADC_DEFAULT_SAMPLES 16     /* Samples on each ADC_Read call    */
#define _ADC_DEFAULT_FREQ 5000000L  /* Default frequency for adc module */

#ifdef	__cplusplus
extern "C" {
#endif

/* CONSTANTS */

const uint8_t 
        A0  = 0x00, /* Analog Channel 0  */
        A1  = 0x01, /* Analog Channel 1  */
        A2  = 0x02, /* Analog Channel 2  */
        A3  = 0x03, /* Analog Channel 3  */
        A4  = 0x04, /* Analog Channel 4  */
        A5  = 0x05, /* Analog Channel 5  */
        A6  = 0x06, /* Analog Channel 6  */
        A7  = 0x07, /* Analog Channel 7  */
        A8  = 0x08, /* Analog Channel 8  */
        A9  = 0x09, /* Analog Channel 9  */
        A10 = 0x0A, /* Analog Channel 10 */
        A11 = 0x0B, /* Analog Channel 11 */
        A12 = 0x0C, /* Analog Channel 12 */
        A13 = 0x0D, /* Analog Channel 13 */
        A14 = 0x0E, /* Analog Channel 14 */
        A15 = 0x0F; /* Analog Channel 15 */
    
    
/* FUNCTIONS */    

/* ------------------------------------------------------------ */
/*        void ADC_SetUp( uint32_t desiredAdcClock )
**
**        Synopsis:
**          ADC_SetUp( ClockForAdcModule );
** 
**        Parameters:
**          uint32_t desiredAdcClock - Desired clock frequency for ADC module
**
**        Return Values:
**          None
**
**        Errors:
**          None
**        Description:
**          The function implements the configuration sequence for ADC 
**         module. This function only need be called one time.
**				
*/
void ADC_SetUp( uint32_t desiredAdcClock  );


/* ------------------------------------------------------------ */
/*        void ADC_SetUpDefault( )
**
**        Synopsis:
**          ADC_SetUp( );
** 
**        Parameters:
**          None
**
**        Return Values:
**          None
**
**        Errors:
**          None
**        Description:
**          The function execute ADC_SetUp function with a default value
**         for ADC frecuence.
**				
*/
inline void ADC_SetUpDefault(  ){
    ADC_SetUp( _ADC_DEFAULT_FREQ );
}


/* ------------------------------------------------------------ */
/*        uint16_t ADC_Read( uint8_t analogChannel)
**
**        Synopsis 
**          ADC_Read( aChannelToRead);
** 
**        Parameters
**          uint8_t aChannelToRead - the analog channel to read
**
**        Return Values
**          uint16_t - the value that was read => [0; 1023]
**
**        Errors:
**          None
** 
**        Preconditions:
**          ADC_SetUp or ADC_SetUpDefault function need be called before
**         call ADC_Read
** 
**        Description:
**          The function implements a ADC read sequence. 
**				
*/
uint16_t ADC_Read( uint8_t analogChannel);


/*        uint16_t analogRead( uint8_t analogChannel )
 *        
 *        Note:
 *          Just like ADC_Read function. See ADC_Read function for reference
 * 
 */
inline uint16_t analogRead( uint8_t analogChannel ){
    return ADC_Read( analogChannel );
}

#ifdef	__cplusplus
}
#endif

#endif	/* _MY_ADC_CEREBOT32MX4_H */

