/* 
 * File:   pwm.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 21 de mayo de 2018, 1:17
 * 
 * Summary:
 *  This file have the definitions, constants and functions that provide an
 *  easy method to use the output compare modules for generate a PWM signal. 
 * 
 * 
 * Remarks:
 * +--------+-------------------------+---------------------------+----------------------------------+
 * |OC pin  |  CEREBOT32MX4 Connector | PIC32MX460F512L PORT, bit | Notes                            |  
 * +--------+-------------------------+---------------------------+----------------------------------+
 * |  1     |          JH-08          |      PORTD, 0             | Shared with SPI Port 1 Connector |
 * |  2     |          JD-02          |      PORTD, 1             |                                  |
 * |  3     |          JD-08          |      PORTD, 2             |                                  |
 * |  4     |          JE-08          |      PORTD, 3             |                                  |
 * |  5     |          JB-09          |      PORTD, 4             |                                  |
 * +--------+-------------------------+---------------------------+----------------------------------+
 */

#ifndef _PWM_H
#define	_PWM_H

#include "../cerebot32MX4.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//#include <peripheral/peripheral.h>
#include <xc.h>


#ifdef	__cplusplus
extern "C" {
#endif

/* MACROS define */
#define _PWM_PWM1_MASK 0x01 // Bit mask for pwm1
#define _PWM_PWM2_MASK 0x02 // Bit mask for pwm2
#define _PWM_PWM3_MASK 0x04 // Bit mask for pwm3
#define _PWM_PWM4_MASK 0x08 // Bit mask for pwm4
#define _PWM_PWM5_MASK 0x10 // Bit mask for pwm5


#define __PWM_MAX_TIMER_PERIOD 0xFFFF                           // Max timer period supported
#define _PWM_DEFAULT_FREQ  19530                                // Default frequency for timer 2 in Hz
#define _PWM_DEFAULT_MASK  0x1F                                 // Default pwm mask for PWM_SetUpDefault function
#define _PWM_DEFAULT_TIMER 1                                    // Default timer is Timer 2
#define PWM_DEFAULT_ARGS _PWM_DEFAULT_MASK, _PWM_DEFAULT_FREQ,1 //Default args for PWM_SetUpDefault function

/* CONSTANTS and ENUMS */

/* Address for OC Modules */
const static uint32_t __OC_address[] = {
    _OCMP1_BASE_ADDRESS,
    _OCMP2_BASE_ADDRESS,
    _OCMP3_BASE_ADDRESS,
    _OCMP4_BASE_ADDRESS,
    _OCMP5_BASE_ADDRESS,
    };

/* Errors Definitions for PWM library*/
typedef enum{
    PWM_RETURN_SUCCESSFUL = 0x0,        // Successful operation
    PWM_RETURN_ERROR_FREQ_LONGER,       // Frequency is to high
    PWM_RETURN_ERROR_FREQ_SMALLER,      // Frequency is to low
    PWM_RETURN_ERROR_WRONG_INDEX        // Invalid OC' index
} PWM_RETURN_FLAG;
    
/* ------------------------------------------------------------ */
/*        PWM_RETURN_FLAG PWM_SetUp( uint8_t pwmMask, uint16_t pwmFreq, bool useT2 )
 *
 *        Synopsis:
 *          PWM_SetUp( pwmMask, pwmFreq, useT2 );
 * 
 *        Parameters:
 *          uint8_t pwmMask - Is a bit mask that represent the OC module index
 *              to be configurated like PWM signal generator. It can be an or-ed
 *              combination of: _PWM_PWMx_MASK where 'x' is the OC's index.
 *              Example: _PWM_PWM2_MASK.
 *          uint16_t pwmFreq - Is the frequency to be used for all PWM signal
 *          bool useT2:
 *             - true for use Timer2
 *             - false for use Timer3
 *
 *        Return Values:
 *          PWM_RETURN_FLAG - It can be:
 *              - PWM_RETURN_SUCCESSFUL (Successful operation)
 *              - PWM_RETURN_ERROR_FREQ_LONGER (Frequency is to high)
 *              - PWM_RETURN_ERROR_FREQ_SMALLER (Frequency is to low)
 *
 *        Errors:
 *          See Return Values
 * 
 *        Description:
 *          The function configure the OCs's modules as a PWM Signal generator. 
 *          This function only need be called one time.
 *				
*/
PWM_RETURN_FLAG PWM_SetUp( uint8_t pwmMask, uint16_t pwmFreq, bool useT2 ); 

/* ------------------------------------------------------------ */
/*        PWM_RETURN_FLAG PWM_SetUpDefault( );
* 
*         Synopsis:
*           PWM_SetUpDefault();
*  
*         Parameters:
*           None
* 
*         Return Values:
*           PWM_RETURN_FLAG - It can be:
*               - PWM_RETURN_SUCCESSFUL (Successful operation)
*               - PWM_RETURN_ERROR_FREQ_LONGER (Frequency is to high)
*               - PWM_RETURN_ERROR_FREQ_SMALLER (Frequency is to low)
* 
*         Errors:
*           See Return Values
* 
*         Description:
*           The function execute PWM_SetUp function whit the default parameters:
*            - pwmMask = _PWM_DEFAULT_MASK
*            - pwmFreq = _PWM_DEFAULT_FREQ
* 			 - useT2   = _PWM_DEFAULT_TIMER	
*/
inline PWM_RETURN_FLAG PWM_SetUpDefault(){
    return PWM_SetUp( PWM_DEFAULT_ARGS  );
}


/* ------------------------------------------------------------ */
/*        PWM_RETURN_FLAG PWM_Start( uint8_t index )
* 
*         Synopsis:
*           PWM_Start( index )
*  
*         Parameters:
*           uint8_t index - Is the Pwm signal that we can enable to use.
*  
*         Return Values:
*           PWM_RETURN_FLAG - It can be:
*               - PWM_RETURN_SUCCESSFUL (Successful operation)
*               - PWM_RETURN_ERROR_WRONG_INDEX (Invalid OC' index)
*  
*         Errors:
*           See Return Values
*  
*         Description:
*           This function enable the OC module number 'index' and start
*           the timer if it is off.
* 				
*/
PWM_RETURN_FLAG PWM_Start( uint8_t index );



/* ------------------------------------------------------------ */
/*        inline PWM_RETURN_FLAG PWM_Stop( uint8_t index )
* 
*         Synopsis:
*           PWM_Stop( index )
*  
*         Parameters:
*           uint8_t index - Is the Pwm signal that we can disable.
*  
*         Return Values:
*           PWM_RETURN_FLAG - It can be:
*               - PWM_RETURN_SUCCESSFUL (Successful operation)
*               - PWM_RETURN_ERROR_WRONG_INDEX (Invalid OC' index)
*  
*         Errors:
*           See Return Values
*  
*         Description:
*           This function disable the OC module number 'index' 
* 				
*/
inline PWM_RETURN_FLAG PWM_Stop( uint8_t index ){
    if( index < 1 || index > 5 )
        return PWM_RETURN_ERROR_WRONG_INDEX;
    
    volatile __OC1CONbits_t *oc = (volatile __OC1CONbits_t *)__OC_address[index-1];
    
    oc->ON = 0;                     // Enable OC1
    return PWM_RETURN_SUCCESSFUL;
}

/* ------------------------------------------------------------ */
/*        inline void PWM_SetDutyCyclePercent( uint8_t index, uint8_t dutyCycle )
* 
*         Synopsis:
*           PWM_SetDutyCyclePercent( index, dutyCycle );
*  
*         Parameters:
*           uint8_t index - Is the Pwm signal that we can modify.
*           uint8_t dutyCycle - Is the dutyCycle(%) that we can set on
*              this module. dutyCycle = [ 0; 100].
*  
*         Return Values:
*           None
*  
*         Errors:
*           None
* 
*         Description:
*           This function set the duyt cycle for the oc module 'index'. 
* 				
*/
inline void PWM_SetDutyCyclePercent( uint8_t index, uint8_t dutyCycle ){
    uint32_t newOCxRS;
    volatile uint32_t *OCxRS = (volatile uint32_t *)(__OC_address[index-1]+0x20);
    volatile __OC1CONbits_t *oc = (volatile __OC1CONbits_t *)__OC_address[index-1];
    
    if( oc->OCTSEL == false )
        newOCxRS = PR2;
    else
        newOCxRS = PR3;
    
    newOCxRS = newOCxRS*(uint32_t)dutyCycle/100;

    *OCxRS = newOCxRS;
}


/* ------------------------------------------------------------ */
/*        inline uint8_t PWM_GetDutyCyclePercent( uint8_t index )
 * 
 *        Synopsis:
 *          PWM_GetDutyCyclePercent( index )
 * 
 *        Parameters:
 *          uint8_t index - Is the Pwm signal id.
 *          
 *        Return Values:
 *          uint8_t - It is a number in the range [ 0; 100].
 *              
 *        Errors:
 *          None
 * 
 *        Description:
 *          This function return the duty cycle of the oc module 'index'. 
 */
inline uint8_t PWM_GetDutyCyclePercent( uint8_t index ){
    volatile uint32_t *OCxRS = (volatile uint32_t *)(__OC_address[index-1] + 0x20);
    volatile __OC1CONbits_t *oc = (volatile __OC1CONbits_t *)__OC_address[index-1];
    if( oc->OCTSEL == false )
        return (*OCxRS)*100/PR2;
    
    return (*OCxRS)*100/PR3;
}


/* ------------------------------------------------------------ */
/*        inline uint16_t PWM_GetDutyCycleValueMax( uint8_t index )
 *
 *        Synopsis:
 *          PWM_GetDutyCycleValueMax( index )
 * 
 *        Parameters:
 *           uint8_t index - Is the Pwm signal id.
 *          
 *        Return Values:
 *          uint16_t - The maximum value for PWM_SetDutyCycleValue function.
 *              
 *        Errors:
 *          None
 * 
 *        Description:
 *          This function return the maximum value for PWM_SetDutyCycleValue function.
 *          For default configuration this function return 1023 ( 10 bit of resolution )
 *				
 */
inline uint16_t PWM_GetDutyCycleValueMax( uint8_t index ){
    volatile __OC1CONbits_t *oc = (volatile __OC1CONbits_t *)__OC_address[index-1];
    
    if( oc->OCTSEL == false )
        return PR2;
    return PR3;
}


/* ------------------------------------------------------------ */
/*        inline void PWM_SetDutyCycleValue( uint8_t index, uint16_t value );
 *
 *        Synopsis:
 *          PWM_SetDutyCycleValue( index, value );
 * 
 *        Parameters:
 *          uint8_t index - Is the Pwm signal that we can modify.
 *          uint8_t value - define de duty cycle of the signal in the
 *            next form: dutyCycle(%) = 100*value/PWM_GetDutyCycleValueMax()
 * 
 *        Return Values:
 *          None
 * 
 *        Errors:
 *          None
 * 
 *        Description:
 *          This function set the duyt cycle for the oc module 'index'.
 *          This function provide more precision. 
 *				
*/
inline void PWM_SetDutyCycleValue( uint8_t index, uint16_t value ){
    volatile uint32_t *OCxRS = (volatile uint32_t *)( __OC_address[index-1] + 0x20  );
    *OCxRS = value;        
}


/* ------------------------------------------------------------ */
/*        inline void analogWrite( uint8_t index, uint16_t value )
 *
 *        Synopsis:
 *          analogWrite( index,value );
 * 
 *        Parameters:
 *          uint8_t index - Is the Pwm signal that we can modify.
 *          uint8_t value - define de duty cycle of the signal in the
 *            next form: dutyCycle(%) = 100*value/PWM_GetDutyCycleValueMax()
 * 
 *        Return Values:
 *          None
 * 
 *        Errors:
 *          None
 * 
 *        Description:
 *          This function set the duyt cycle for the oc module 'index'.
 *          This function provide more precision. 
 *				
 */
inline void analogWrite( uint8_t index, uint16_t value ){
    volatile uint32_t *OCxRS = (volatile uint32_t *)( __OC_address[index-1] + 0x20  );
    *OCxRS = value;        
}
   
    
#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

