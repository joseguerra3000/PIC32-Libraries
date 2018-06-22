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
        AN0  = 0x00, /* Analog Channel 0 --> CEREBOT JJ-01                   */
        AN1  = 0x01, /* Analog Channel 1 --> CEREBOT JJ-02                   */
        AN2  = 0x02, /* Analog Channel 2 --> CEREBOT JJ-03                   */
        AN3  = 0x03, /* Analog Channel 3 --> CEREBOT JJ-04                   */
        AN4  = 0x04, /* Analog Channel 4 --> CEREBOT JJ-07                   */
        AN5  = 0x05, /* Analog Channel 5 --> CEREBOT JJ-08                   */
        AN6  = 0x06, /* Analog Channel 6 --> CEREBOT Debug Circuit           */
        AN7  = 0x07, /* Analog Channel 7 --> CEREBOT Debug Circuit           */
        AN8  = 0x08, /* Analog Channel 8 --> CEREBOT JJ-09                   */
        AN9  = 0x09, /* Analog Channel 9 --> CEREBOT JJ-10                   */
        AN10 = 0x0A, /* Analog Channel 10 --> CEREBOT JK-01, Shared with LD1 */
        AN11 = 0x0B, /* Analog Channel 11 --> CEREBOT JK-02, Shared with LD2 */
        AN12 = 0x0C, /* Analog Channel 12 --> CEREBOT JK-03, Shared with LD3 */
        AN13 = 0x0D, /* Analog Channel 13 --> CEREBOT JK-04, Shared with LD4 */
        AN14 = 0x0E, /* Analog Channel 14 --> CEREBOT JB-10                  */
        AN15 = 0x0F; /* Analog Channel 15 --> CEREBOT JB-07                  */
    
    
/* FUNCTIONS */    

/* ------------------------------------------------------------ */
/*        void ADC_SetUp( uint32_t desiredAdcClock )
**
**        @Synopsis:
**          ADC_SetUp( ClockForAdcModule );
** 
**        @Parameters:
**          uint32_t desiredAdcClock - Desired clock frequency for ADC module
**
**        @Return Values:
**          None
**
**        @Errors:
**          None
**        
**        @Description:
**          The function implements the configuration sequence for ADC 
**         module. This function only need be called one time.
**				
*/
void ADC_SetUp( uint32_t desiredAdcClock  );


/* ------------------------------------------------------------ */
/*        void ADC_SetUpDefault( )
**
**        @Synopsis:
**          ADC_SetUp( );
** 
**        @Parameters:
**          None
**
**        @Return Values:
**          None
**
**        @Errors:
**          None
**        
**        @Description:
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
**        @Synopsis 
**          ADC_Read( aChannelToRead);
** 
**        @Parameters
**          uint8_t aChannelToRead - the analog channel to read
**
**        @Return Values
**          uint16_t - the value that was read => [0; 1023]
**
**        @Errors:
**          None
** 
**        @Preconditions:
**          ADC_SetUp or ADC_SetUpDefault function need be called before
**         call ADC_Read
** 
**        @Description:
**          The function implements a ADC read sequence. 
**				
*/
uint16_t ADC_Read( uint8_t analogChannel);


/*        uint16_t analogRead( uint8_t analogChannel )
 *        
 *        @Note:
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

